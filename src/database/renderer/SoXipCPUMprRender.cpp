
#include <xip/inventor/coregl/SoXipGlowElement.h>

#include "SoXipCPUMprRender.h"
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <assert.h>
#include <limits>


SO_NODE_SOURCE(SoXipCPUMprRender);

// Fast Floor for 3 values
inline void floor_int3 (float x, float y, float z, int &xi, int &yi, int &zi)
{
#if defined(WIN32) && !defined(WIN64)
  const float round_towards_m_i = -0.5f;
  int rx, ry, rz;
//#ifndef __POWERPC__ // FIXME: We must code for PPC arch
  __asm
    {
	fld x
	fadd st, st (0)
	fadd round_towards_m_i
	fistp rx
	sar rx, 1
	fld y
	fadd st, st (0)
	fadd round_towards_m_i
	fistp ry
	sar ry, 1
	fld z
	fadd st, st (0)
	fadd round_towards_m_i
	fistp rz
	sar rz, 1
    }
//#endif /* __POWERPC__ */
  xi = rx;
  yi = ry;
  zi = rz;
#else // WIN32
  xi = int(x);
  yi = int(y);
  zi = int(z);
#endif // WIN32
}

//////////////////////////////////////////////////////////////////////////////////////////
// float based trilinear interpolated 3d lookup
template <class T>
inline T sample3Di(T *buf, float *coord, int width, int sliceSize, float *neighbours, int &lastBaseOffset)
{
	// Get the coordinates
	float x = coord[0];
	float y = coord[1];
	float z = coord[2];
	
	// Get the floor
	int fx, fy, fz;
	floor_int3(x, y, z, fx, fy, fz);
	
	// Compute the base offset into the data with this floor
	int baseOffset = sliceSize * fz + width * fy + fx;

	// If the offset hasn't changed, we can use the cached neighbours
	if (baseOffset != lastBaseOffset)
	{
		lastBaseOffset = baseOffset;

		/*int cx = ceil_int(x) - fx;
		int cy = (ceil_int(y) - fy) * width;
		int cz = (ceil_int(z) - fz) * sliceSize;*/
		int cx = 1;
		int cy = width;
		int cz = sliceSize;

		buf += baseOffset;
		neighbours[0] = buf[0];
		neighbours[2] = buf[cx];
		neighbours[1] = buf[cy];
		neighbours[3] = buf[cy + cx];
		neighbours[4] = buf[cz]				- neighbours[0];
		neighbours[6] = buf[cz + cx]		- neighbours[2];
		neighbours[5] = buf[cz + cy]		- neighbours[1];
		neighbours[7] = buf[cz + cy + cx]	- neighbours[3];
	}

	// Get the fractional part of the coordinate
	float xd = x - fx;
	float yd = y - fy;
	float zd = z - fz;

	// Compute trilinear interpolation
	float i1 = neighbours[0] + zd * neighbours[4];
	float i2 = neighbours[1] + zd * neighbours[5];
	float j1 = neighbours[2] + zd * neighbours[6];
	float j2 = neighbours[3] + zd * neighbours[7];
	float w1 = i1 + yd * (i2 - i1);
	float w2 = j1 + yd * (j2 - j1);
	float res = w1 + xd * (w2 - w1);

	return (T)res;
}


//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipCPUMprRender::initClass()
{
	SO_NODE_INIT_CLASS(SoXipCPUMprRender, SoShape, "Shape");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoViewVolumeElement);
	SO_ENABLE(SoGLRenderAction, SoModelMatrixElement);
	SO_ENABLE(SoGLRenderAction, SoViewportRegionElement);
	SO_ENABLE(SoGLRenderAction, SoXipMultiTextureElement);
}

//////////////////////////////////////////////////////////////////////////////////////////
///
SoXipCPUMprRender::SoXipCPUMprRender()
{
	SO_NODE_CONSTRUCTOR(SoXipCPUMprRender);

	SO_NODE_ADD_FIELD(minMaxSize, (SbVec2s(128, 1024)));
	SO_NODE_ADD_FIELD(volume, (NULL));
	SO_NODE_ADD_FIELD(blendOn, (FALSE));

	mMPRTexId = 0;
	mMPRSize = SbVec2s(0, 0);
	mMPRCache = 0;
	mNumCacheElems = 0;
	mMPRBuf = 0;
	mVolDataId = 0;
	mUpdateFlag = 0;
	mVolBuf = 0;
	mLutBuf = 0;
	mLutSize = 0;
	mLutDataId = 0;
    mTexInternalFormat = 0;
    mTexType = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
///
SoXipCPUMprRender::~SoXipCPUMprRender()
{
#ifdef _CRT_ALLOCATION_DEFINED
	if (mMPRBuf)
		_aligned_free(mMPRBuf);
	if (mMPRCache)
		_aligned_free(mMPRCache);
#else
	if (mMPRBuf)
		delete[] mMPRBuf;
	if (mMPRCache)
		delete[] mMPRCache;
#endif

	if (mMPRTexId)
		glDeleteTextures(1, &mMPRTexId);
}

//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipCPUMprRender::readyBuffers(SoState *state)
{
	SbXipImageDimensions dim(0, 0, 0);
	SoXipDataImage *imgData = 0;
	SbXipImage *image = 0;

	// Volume
	imgData = volume.getValue();
	dim = SbXipImageDimensions(0,0,0);
	if (imgData && (image = imgData->get()))
	{
		// If data has changed, update MPR
		if (imgData->getDataId() != mVolDataId)
		{
			mVolDataId = imgData->getDataId();
			mUpdateFlag |= UPDATE_MPR;
		}
		if (mVolDataType != image->getType() || mVolBitsUsed != image->getBitsStored())
		{
			mVolDataType = image->getType();
			mVolBitsUsed = image->getBitsStored();
			mMPRSize = SbVec2s(-1, -1); // force buffer resizing
		}
		mVolBuf = image->refBufferPtr();
		dim = imgData->get()->getDimAllocated();
		// If dimensions have changed, update Cache
		if (dim != mVolDim)
		{
			mVolDim = dim;
			mUpdateFlag |= UPDATE_MPRCACHE;
		}
	}
	else
	{
		mVolBuf = 0;
		mVolDim = dim;
		mVolDataId = 0;
	}

	// Transfer function LUT
	imgData = (SoXipDataImage *) SoXipLutElement::get(state);
	if (imgData && (image = imgData->get()) &&
		image->getType() == SbXipImage::FLOAT &&
		image->getComponentLayoutType() == SbXipImage::RGBA)
	{
		// If there was no LUT before, resize buffers
		if (!mLutBuf)
			mMPRSize = SbVec2s(-1, -1);
		mLutSize = image->getDimStored()[0];
		mLutBuf = (float*) image->refBufferPtr();

		// If data has changed, update MPR
		if (imgData->getDataId() != mLutDataId)
		{
			mLutDataId = imgData->getDataId();
			mUpdateFlag |= UPDATE_MPR;
		}
	}
	else
	{
		// If there was a LUT before, force resizing
		if (mLutBuf)
			mMPRSize = SbVec2s(-1, -1);
		mLutBuf = 0;
		mLutSize = 0;
		mLutDataId = 0;
	}
}




//////////////////////////////////////////////////////////////////////////////////////////////////
/// Resize buffers and opengl texture
void	SoXipCPUMprRender::resizeBuffers(SbVec2s &size)
{
	mMPRSize = size;

#ifdef _CRT_ALLOCATION_DEFINED
	if (mMPRBuf)
		_aligned_free(mMPRBuf);
	if (mMPRCache)
		_aligned_free(mMPRCache);
#else
	if (mMPRBuf)
		delete[] mMPRBuf;
	if (mMPRCache)
		delete[] mMPRCache;
#endif


	if (!mMPRTexId)
		glGenTextures(1, &mMPRTexId);

	int volBytes = 1;
	if (mLutBuf)
	{
		volBytes =  sizeof(float) * 4;
		mTexInternalFormat = GL_RGBA8;
		mTexType = GL_FLOAT;
	}
	else
		switch (mVolDataType)
		{
		case SbXipImage::UNSIGNED_BYTE:
			mTexInternalFormat = GL_LUMINANCE8;
			mTexType = GL_UNSIGNED_BYTE;
			break;
		case SbXipImage::BYTE:
			mTexInternalFormat = GL_LUMINANCE8;
			mTexType = GL_BYTE;
			break;
		case SbXipImage::UNSIGNED_SHORT:
			mTexInternalFormat = GL_LUMINANCE16;
			mTexType = GL_UNSIGNED_SHORT;
			volBytes = 2;
			break;
		case SbXipImage::SHORT:
			mTexInternalFormat = GL_LUMINANCE16;
			mTexType = GL_SHORT;
			volBytes = 2;
			break;
		case SbXipImage::UNSIGNED_INT:
			mTexInternalFormat = GL_LUMINANCE16;
			mTexType = GL_UNSIGNED_INT;
			volBytes = 4;
			break;
		case SbXipImage::INT:
			mTexInternalFormat = GL_LUMINANCE16;
			mTexType = GL_INT;
			volBytes = 4;
			break;
		case SbXipImage::FLOAT:
			mTexInternalFormat = GL_LUMINANCE16;
			mTexType = GL_FLOAT;
			volBytes = 4;
			break;
		case SbXipImage::DOUBLE:
			mTexInternalFormat = GL_LUMINANCE16;
			mTexType = GL_DOUBLE;
			volBytes = 8;
			break;
		default:
            mTexInternalFormat = 0;
            mTexType = 0;
            SoDebugError::postInfo("SoXipCPUMprRender::resizeBuffers", "Unsupported image type: %d!", mVolDataType);
            return;
		}
		
		
#ifdef _CRT_ALLOCATION_DEFINED 
	mMPRBuf = _aligned_malloc(size[0] * size[1] * volBytes, 16);
	mMPRCache = (mprCacheElem*) _aligned_malloc(sizeof(mprCacheElem) * size[0] * size[1], 16);
#else
	mMPRBuf = (void*) new char[size[0] * size[1] * volBytes];
	mMPRCache = new mprCacheElem[size[0] * size[1]];
#endif
	
	glBindTexture(GL_TEXTURE_2D, mMPRTexId);
	glTexImage2D(GL_TEXTURE_2D, 0, mTexInternalFormat, size[0], size[1], 0, mLutBuf ? GL_RGBA : GL_LUMINANCE, mTexType, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///
template <class T>
void	computeMPRCache(SoXipCPUMprRender *mprRender, T *volBuf, SoState *state)
{
	// Clear the contents of the mpr buffer
	memset(mprRender->mMPRBuf, 0, (int)mprRender->mMPRSize[0] * (int)mprRender->mMPRSize[1] * sizeof(T));

	// Get some constant sizes ready
	const int volWidth = mprRender->mVolDim[0];
	const int volHeight = mprRender->mVolDim[1];
	const int volDepth = mprRender->mVolDim[2];
	const int volSliceSize = volWidth * volHeight;
	const float boundX = volWidth - 1.0f;
	const float boundY = volHeight - 1.0f;
	const float boundZ = volDepth - 1.0f;

	// Get bounding box span and start from model matrix
	SbMatrix modelMat = SoModelMatrixElement::get(state);
	SbVec3f wSpan, wStart;
	SbRotation dummy;
	modelMat.getTransform(wStart, dummy, wSpan, dummy);

	SbMatrix inv = modelMat.inverse();

	// Convert the corner points from worldspace to model space
	SbVec3f	corners[4];
	short i;
	for (i = 0; i < 4; ++i)
	{
		inv.multVecMatrix( mprRender->mCorners[i], corners[i] );
		corners[i][0] *= boundX;
		corners[i][1] *= boundY;
		corners[i][2] *= boundZ;

	}

	SbVec3f vGrad1((corners[0] - corners[3]) / (mprRender->mMPRSize[1] - 1.0f));
	SbVec3f vGrad2((corners[1] - corners[2]) / (mprRender->mMPRSize[1] - 1.0f));
	SbVec3f vIntrp1 = corners[3];
	SbVec3f vIntrp2 = corners[2];
	
	SbVec3f hGrad;
	SbVec3f pos;

	// Prepare data cache stuff
	float neighboursVol[8];
	int	lastBaseOffsetVol = -1;	
	
	int bitRatio = (int)(powf(2, sizeof(T) * 8) / powf(2, mprRender->mVolBitsUsed));
	//
	mprCacheElem *cacheElem = mprRender->mMPRCache;
	T *mprVal = (T*) mprRender->mMPRBuf;

	for (i = 0; i < mprRender->mMPRSize[1]; ++i)
	{
		hGrad = (vIntrp2 - vIntrp1) / (mprRender->mMPRSize[0] - 1.0f);
		pos = vIntrp1;
		for (short j = 0; j < mprRender->mMPRSize[0]; ++j)
		{
			// Check if coord is out of bounds
			if (pos[0] >= 0 && pos[0] < boundX &&
				pos[1] >= 0 && pos[1] < boundY &&
				pos[2] >= 0 && pos[2] < boundZ)
			{

				cacheElem->volCoord[0] = pos[0];
				cacheElem->volCoord[1] = pos[1];
				cacheElem->volCoord[2] = pos[2];

				*mprVal = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighboursVol, lastBaseOffsetVol) * bitRatio);
				
				cacheElem->mprOffset = mprVal - (T*) mprRender->mMPRBuf;
				cacheElem++;
			}
			mprVal++;
			pos += hGrad;
		}
		vIntrp1 += vGrad1;
		vIntrp2 += vGrad2;
	}
	mprRender->mNumCacheElems = cacheElem - mprRender->mMPRCache;
}

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
// Nearest neighbour LUT lookup
template <class T>
void sampleLut(float *mprVal, T val, float *lutBuf, unsigned int lutSize)
{
	double texCoord = val / (double)std::numeric_limits<T>::max();
    texCoord = MIN(MAX(texCoord, 0.0f), 1.0f);

	unsigned int lutIndex = texCoord * (lutSize - 1);
	mprVal[0] = lutBuf[(lutIndex << 2) + 0];
	mprVal[1] = lutBuf[(lutIndex << 2) + 1];
	mprVal[2] = lutBuf[(lutIndex << 2) + 2];
	mprVal[3] = lutBuf[(lutIndex << 2) + 3];
}
// Special cases for float and double, where we assume that range is between 0 and 1
// Todo: add float min/max field in case people want to use float data with different range than 0..1
template <>
void sampleLut(float *mprVal, float val, float *lutBuf, unsigned int lutSize)
{
    unsigned int lutIndex = val * (lutSize - 1);
	mprVal[0] = lutBuf[(lutIndex << 2) + 0];
	mprVal[1] = lutBuf[(lutIndex << 2) + 1];
	mprVal[2] = lutBuf[(lutIndex << 2) + 2];
	mprVal[3] = lutBuf[(lutIndex << 2) + 3];
}
template <>
void sampleLut(float *mprVal, double val, float *lutBuf, unsigned int lutSize)
{
    unsigned int lutIndex = val * (lutSize - 1);
	mprVal[0] = lutBuf[(lutIndex << 2) + 0];
	mprVal[1] = lutBuf[(lutIndex << 2) + 1];
	mprVal[2] = lutBuf[(lutIndex << 2) + 2];
	mprVal[3] = lutBuf[(lutIndex << 2) + 3];
}


//////////////////////////////////////////////////////////////////////////////////////////////////
///
template <class T>
void	computeMPRCacheLUT(SoXipCPUMprRender *mprRender, T *volBuf, SoState *state)
{
	// Clear the contents of the mpr buffer
	memset(mprRender->mMPRBuf, 0, (int)mprRender->mMPRSize[0] * (int)mprRender->mMPRSize[1] * sizeof(float) * 4);

	// Get some constant sizes ready
	const int volWidth = mprRender->mVolDim[0];
	const int volHeight = mprRender->mVolDim[1];
	const int volDepth = mprRender->mVolDim[2];
	const int volSliceSize = volWidth * volHeight;
	const float boundX = volWidth - 1.0f;
	const float boundY = volHeight - 1.0f;
	const float boundZ = volDepth - 1.0f;

	// Get bounding box span and start from model matrix
	SbMatrix modelMat = SoModelMatrixElement::get(state);
	SbVec3f wSpan, wStart;
	SbRotation dummy;
	modelMat.getTransform(wStart, dummy, wSpan, dummy);

	SbMatrix inv = modelMat.inverse();

	// Convert the corner points from worldspace to model space
	SbVec3f	corners[4];
	short i;
	for (i = 0; i < 4; ++i)
	{
		inv.multVecMatrix( mprRender->mCorners[i], corners[i] );
		corners[i][0] *= boundX;
		corners[i][1] *= boundY;
		corners[i][2] *= boundZ;

	}

	SbVec3f vGrad1((corners[0] - corners[3]) / (mprRender->mMPRSize[1] - 1.0f));
	SbVec3f vGrad2((corners[1] - corners[2]) / (mprRender->mMPRSize[1] - 1.0f));
	SbVec3f vIntrp1 = corners[3];
	SbVec3f vIntrp2 = corners[2];
	
	SbVec3f hGrad;
	SbVec3f pos;

	// Prepare data cache stuff
	float neighboursVol[8];
	int	lastBaseOffsetVol = -1;	
	
	int bitRatio = (int)(powf(2, sizeof(T) * 8) / powf(2, mprRender->mVolBitsUsed));
	//
	mprCacheElem *cacheElem = mprRender->mMPRCache;
	float *mprVal = (float*) mprRender->mMPRBuf;

	for (i = 0; i < mprRender->mMPRSize[1]; ++i)
	{
		hGrad = (vIntrp2 - vIntrp1) / (mprRender->mMPRSize[0] - 1.0f);
		pos = vIntrp1;
		for (short j = 0; j < mprRender->mMPRSize[0]; ++j)
		{
			// Check if coord is out of bounds
			if (pos[0] >= 0 && pos[0] < boundX &&
				pos[1] >= 0 && pos[1] < boundY &&
				pos[2] >= 0 && pos[2] < boundZ)
			{

				cacheElem->volCoord[0] = pos[0];
				cacheElem->volCoord[1] = pos[1];
				cacheElem->volCoord[2] = pos[2];

				T val = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighboursVol, lastBaseOffsetVol) * bitRatio);

				sampleLut(mprVal, val, mprRender->mLutBuf, mprRender->mLutSize);
				
				cacheElem->mprOffset = mprVal - (float*) mprRender->mMPRBuf;
				cacheElem++;
			}
			mprVal += 4;
			pos += hGrad;
		}
		vIntrp1 += vGrad1;
		vIntrp2 += vGrad2;
	}
	mprRender->mNumCacheElems = cacheElem - mprRender->mMPRCache;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///
template <class T>
void	computeMPR(SoXipCPUMprRender *mprRender, T *volBuf)
{
	unsigned int i;
	float neighbours[8];
	int	lastBaseOffset = -1;

	int volWidth = mprRender->mVolDim[0];
	int volSliceSize = volWidth * mprRender->mVolDim[1];

	mprCacheElem *cacheElem = mprRender->mMPRCache;

	int bitRatio = (int)(powf(2, sizeof(T) * 8) / powf(2, mprRender->mVolBitsUsed));

	if (bitRatio == 1)
	{
		// 4-iteration unrolled loop
		unsigned int batch = mprRender->mNumCacheElems / 4;
		for (i = 0; i < batch; ++i)
		{
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			cacheElem++;
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			cacheElem++;
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			cacheElem++;
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			cacheElem++;
		}
		// Leftovers
		unsigned int leftovers = mprRender->mNumCacheElems % 4;
		for (i = 0; i < leftovers; ++i)
		{
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			cacheElem++;
		}
	}
	else
	{
		// 4-iteration unrolled loop
		unsigned int batch = mprRender->mNumCacheElems / 4;
		for (i = 0; i < batch; ++i)
		{
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			cacheElem++;
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			cacheElem++;
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			cacheElem++;
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			cacheElem++;
		}
		// Leftovers
		unsigned int leftovers = mprRender->mNumCacheElems % 4;
		for (i = 0; i < leftovers; ++i)
		{
			((T*)mprRender->mMPRBuf)[cacheElem->mprOffset] = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			cacheElem++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///
template <class T>
void	computeMPRLUT(SoXipCPUMprRender *mprRender, T *volBuf)
{
	unsigned int i;
	float neighbours[8];
	int	lastBaseOffset = -1;

	int volWidth = mprRender->mVolDim[0];
	int volSliceSize = volWidth * mprRender->mVolDim[1];

	mprCacheElem *cacheElem = mprRender->mMPRCache;

	int bitRatio = (int)(powf(2, sizeof(T) * 8) / powf(2, mprRender->mVolBitsUsed));

	T val;

	if (bitRatio == 1)
	{
		// 4-iteration unrolled loop
		unsigned int batch = mprRender->mNumCacheElems / 4;
		for (i = 0; i < batch; ++i)
		{
			val = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
			val = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
			val = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
			val = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
		}
		// Leftovers
		unsigned int leftovers = mprRender->mNumCacheElems % 4;
		for (i = 0; i < leftovers; ++i)
		{
			val = sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
		}
	}
	else
	{
		// 4-iteration unrolled loop
		unsigned int batch = mprRender->mNumCacheElems / 4;
		for (i = 0; i < batch; ++i)
		{
			val = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
			val = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
			val = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
			val = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
		}
		// Leftovers
		unsigned int leftovers = mprRender->mNumCacheElems % 4;
		for (i = 0; i < leftovers; ++i)
		{
			val = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighbours, lastBaseOffset) * bitRatio);
			sampleLut(((float*)mprRender->mMPRBuf) + cacheElem->mprOffset, val, mprRender->mLutBuf, mprRender->mLutSize);
			cacheElem++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///
void	SoXipCPUMprRender::updateTexture()
{
	int align;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &align);
	// Update the texture
	glBindTexture(GL_TEXTURE_2D, mMPRTexId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, getPackAlignment((int)mMPRSize[0]));
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, (int)mMPRSize[0], (int)mMPRSize[1], mLutBuf ? GL_RGBA : GL_LUMINANCE, mTexType, mMPRBuf);
	glPixelStorei(GL_UNPACK_ALIGNMENT, align);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///
void	SoXipCPUMprRender::renderMPR(int texUnit)
{
	
	// If fragment program is present, get available texture stage and
	// bind it to "tex" in the FP.
	int fp;
	glGetIntegerv(GL_CURRENT_PROGRAM, &fp);
	if (fp && GLOW_ARB_fragment_shader)
	{
		GLhandleARB	programObject = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
#ifndef DARWIN
		GLint loc	= glGetUniformLocation(programObject,  "tex");
#else /* DARWIN */
		GLint loc	= glGetUniformLocationARB(programObject,  "tex");
#endif /* DARWIN */
		if (loc != -1)
			glUniform1i(loc, texUnit);
	}
	
	GLboolean depthTestEnabled, texture2DEnabled, lightingEnabled,blendEnabled;
	depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
	texture2DEnabled = glIsEnabled(GL_TEXTURE_2D);
	lightingEnabled = glIsEnabled(GL_LIGHTING);	
	blendEnabled = glIsEnabled(GL_BLEND);	
	
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	glDisable(GL_LIGHTING);
	
	if ( blendOn.getValue() )
		glEnable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
	// Draw a quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(-1, -1);
	glTexCoord2f(1, 0);
    glVertex2f(1, -1);
	glTexCoord2f(1, 1);
	glVertex2f(1, 1);
	glTexCoord2f(0, 1);
	glVertex2f(-1, 1);
    glEnd();

	//restore some previous openGL states
	depthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	texture2DEnabled ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	lightingEnabled ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);	
	blendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);

	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipCPUMprRender::GLRender(SoGLRenderAction * action)
{
	SoState *state = action->getState();
	SbViewportRegion vpRegion = SoViewportRegionElement::get(state);
	SbVec2s vpSize = vpRegion.getViewportSizePixels();

	// Don't do anything if 0 size
	if (!vpSize[0] || !vpSize[1])
		return;

	// Bind texture to available texture stage
	if (!mMPRTexId)
		glGenTextures(1, &mMPRTexId);

	int texUnit = SoXipMultiTextureElement::getFreeUnit(state);
	SoXipMultiTextureElement::setUnit(state, texUnit);
	SoXipMultiTextureElement::bindTexture(state, GL_TEXTURE_2D, mMPRTexId);

	// Check the size against min/max
	SbVec2s minmax = minMaxSize.getValue();
	int which = (vpSize[0] > vpSize[1]) ? 0 : 1;
	float ratio = (float) vpSize[which] / (float) vpSize[1 - which];
	// If smallest dim is < min
	if (vpSize[1 - which] < minmax[0])
	{
		// Clamp to min and change biggest dim according to aspect ratio
		vpSize[1 - which] = minmax[0];
		vpSize[which] = (short) (ratio * vpSize[1 - which]);
	}
	// If biggest dim is > max
	if (vpSize[which] > minmax[1])
	{
		// Clamp to max and change smallest dim according to aspect ratio
		vpSize[which] = minmax[1];
		vpSize[1 - which] = (short) (vpSize[which] / ratio);
	}

	// Ready the buffers
	readyBuffers(state);

	if (vpSize[0] == 0 || vpSize[1] == 0)
		return;

	// Check if mpr texture must be resized
	if (mMPRSize != vpSize)
	{
		resizeBuffers(vpSize);
		mUpdateFlag |= UPDATE_MPRCACHE;
    }
    
    // Exit if unsupported image type
    if (mTexInternalFormat == 0 ||
        mTexType == 0)
        return;

	// Check if orientation has changed
	SbVec3f	corners[4];
	SbViewVolume viewVolume = SoViewVolumeElement::get(state);
	float dist = viewVolume.getNearDist() + viewVolume.getDepth() * 0.5f;
	corners[0] = viewVolume.getPlanePoint(dist, SbVec2f(0, 1));
	corners[1] = viewVolume.getPlanePoint(dist, SbVec2f(1, 1));
	corners[2] = viewVolume.getPlanePoint(dist, SbVec2f(1, 0));
	corners[3] = viewVolume.getPlanePoint(dist, SbVec2f(0, 0));
	if (corners[0] != mCorners[0] ||
		corners[1] != mCorners[1] ||
		corners[2] != mCorners[2] ||
		corners[3] != mCorners[3])
	{
		mCorners[0] = corners[0];
		mCorners[1] = corners[1];
		mCorners[2] = corners[2];
		mCorners[3] = corners[3];
		mUpdateFlag |= UPDATE_MPRCACHE;
	}

	
	//
	if (mUpdateFlag & UPDATE_MPRCACHE)
	{
		// Compute new cache table and mpr
		switch (mVolDataType)
		{
		case SbXipImage::UNSIGNED_BYTE:
			mLutBuf ? computeMPRCacheLUT(this, (unsigned char*)mVolBuf, state) : computeMPRCache(this, (unsigned char*)mVolBuf, state);
			break;
		case SbXipImage::BYTE:
			mLutBuf ? computeMPRCacheLUT(this, (char*)mVolBuf, state) : computeMPRCache(this, (char*)mVolBuf, state);
			break;
		case SbXipImage::UNSIGNED_SHORT:
			mLutBuf ? computeMPRCacheLUT(this, (unsigned short*)mVolBuf, state) : computeMPRCache(this, (unsigned short*)mVolBuf, state);
			break;
		case SbXipImage::SHORT:
			mLutBuf ? computeMPRCacheLUT(this, (short*)mVolBuf, state) : computeMPRCache(this, (short*)mVolBuf, state);
			break;
		case SbXipImage::UNSIGNED_INT:
			mLutBuf ? computeMPRCacheLUT(this, (unsigned int*)mVolBuf, state) : computeMPRCache(this, (unsigned int*)mVolBuf, state);
			break;
		case SbXipImage::INT:
			mLutBuf ? computeMPRCacheLUT(this, (int*)mVolBuf, state) : computeMPRCache(this, (int*)mVolBuf, state);
			break;
		case SbXipImage::FLOAT:
			mLutBuf ? computeMPRCacheLUT(this, (float*)mVolBuf, state) : computeMPRCache(this, (float*)mVolBuf, state);
			break;
		case SbXipImage::DOUBLE:
			mLutBuf ? computeMPRCacheLUT(this, (double*)mVolBuf, state) : computeMPRCache(this, (double*)mVolBuf, state);
			break;
		default:
            // will never come here cause we already checked for it in resize
			break;	
		}
		// Update mpr texture
		updateTexture();
	}
	else if (mUpdateFlag & UPDATE_MPR)
	{
		// Compute new mpr
		switch (mVolDataType)
		{
		case SbXipImage::UNSIGNED_BYTE:
			mLutBuf ? computeMPRLUT(this, (unsigned char*)mVolBuf) : computeMPR(this, (unsigned char*)mVolBuf);
			break;
		case SbXipImage::BYTE:
			mLutBuf ? computeMPRLUT(this, (char*)mVolBuf) : computeMPR(this, (char*)mVolBuf);
			break;
		case SbXipImage::UNSIGNED_SHORT:
			mLutBuf ? computeMPRLUT(this, (unsigned short*)mVolBuf) : computeMPR(this, (unsigned short*)mVolBuf);
			break;
		case SbXipImage::SHORT:
			mLutBuf ? computeMPRLUT(this, (short*)mVolBuf) : computeMPR(this, (short*)mVolBuf);
			break;
		case SbXipImage::UNSIGNED_INT:
			mLutBuf ? computeMPRLUT(this, (unsigned int*)mVolBuf) : computeMPR(this, (unsigned int*)mVolBuf);
			break;
		case SbXipImage::INT:
			mLutBuf ? computeMPRLUT(this, (int*)mVolBuf) : computeMPR(this, (int*)mVolBuf);
			break;
		case SbXipImage::FLOAT:
			mLutBuf ? computeMPRLUT(this, (float*)mVolBuf) : computeMPR(this, (float*)mVolBuf);
			break;
		case SbXipImage::DOUBLE:
			mLutBuf ? computeMPRLUT(this, (double*)mVolBuf) : computeMPR(this, (double*)mVolBuf);
			break;
		default:
            // will never come here cause we already checked for it in resize
			break;	
		}
		// Update mpr texture
		updateTexture();
	}

	// Render mpr to a quad
	renderMPR(texUnit);

	// Reset update flag
	mUpdateFlag = 0;
}



//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipCPUMprRender::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
	center.setValue(0.5, 0.5, 0.5);
	box.setBounds(0, 0, 0, 1, 1, 1);
}
