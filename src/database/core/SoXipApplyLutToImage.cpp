/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


#include <xip/system/standard.h>
#include "SoXipApplyLutToImage.h"
//#include "SoXipSFDataImageToSFImage.h"

#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoActions.h>
//#include <Inventor/SoPrimitiveVertex.h>
//#include <Inventor/elements/SoTextureCoordinateElement.h>
//#include <Inventor/nodes/SoMatrixTransform.h>

#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SbXipImageAdaptor.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <xip/inventor/core/SoXipDataImage.h>
//#include <xip/inventor/core/SoXipTexture.h>










SO_NODE_SOURCE( SoXipApplyLutToImage );


SoXipApplyLutToImage::SoXipApplyLutToImage()
{
	SO_NODE_CONSTRUCTOR( SoXipApplyLutToImage );

	SO_NODE_ADD_FIELD( image,  (NULL) );
	SO_NODE_ADD_FIELD( output, (NULL) );

	mCurrentImage = 0;
	mImageId = 0;
	mLutId = 0;

	mImageSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
	mImageSensor->setPriority(0);
	mImageSensor->attach(&image);
}

SoXipApplyLutToImage::~SoXipApplyLutToImage()
{
	if (mImageSensor)
	{
		delete mImageSensor;
		mImageSensor = 0;
	}

	if (mCurrentImage)
	{
		mCurrentImage->unref();
		mCurrentImage = 0;
	}
}

void SoXipApplyLutToImage::initClass()
{
	SO_NODE_INIT_CLASS( SoXipApplyLutToImage, SoNode, "Node" );

	SO_ENABLE(SoGLRenderAction,         SoXipLutElement);
	SO_ENABLE(SoPickAction,             SoXipLutElement);
	SO_ENABLE(SoCallbackAction,         SoXipLutElement);
	SO_ENABLE(SoGetBoundingBoxAction,   SoXipLutElement);
}

void SoXipApplyLutToImage::imageChanged()
{
	mImageId = 0;
	mLutId = 0;
}

void SoXipApplyLutToImage::loadTexture(SbXipImage *img, SbXipImage *lut)
{
	SbXipImage * tex = 0;

	if (mCurrentImage)
	{
		mCurrentImage->unref();
		mCurrentImage = 0;
	}

	if (lut)
		tex = createImage8Lut(img, lut);
	else
		tex = createImage8(img);

	if (tex)
	{
		// need a reference counted wrapper for this image so SoRadTexture can free by unref() after use
		mCurrentImage = new SoXipDataImage();
		if (mCurrentImage)
		{
			mCurrentImage->ref();
			mCurrentImage->set(tex);
		}
		else
		{
			// allocation of wrapper failed, need to delete image myself
			delete tex;
		}
	}
}

void SoXipApplyLutToImage::updateTexture(SoAction *action)
{
	if (!image.getValue())
	{
		mImageId = 0;

		if (mCurrentImage)
		{
			mCurrentImage->unref();
			mCurrentImage = 0;
		}
		return;
	}

	SoXipData * eltLut = (SoXipData *)SoXipLutElement::get(action->getState());

	if (image.getValue()->getDataId() == mImageId)
	{
		// if no lut or lut and image are same then no update is needed
		if (!eltLut && !mLutId)
			return;

		if (eltLut)
		{
			if (eltLut->getDataId() == mLutId)
				return;
		}
	}

	if (mCurrentImage)
	{
		mCurrentImage->unref();
		mCurrentImage = 0;
	}

	mImageId = image.getValue()->getDataId();
	mLutId = eltLut ? eltLut->getDataId() : 0;

	SbXipImage *img = image.getValue()->get();
	if (!img)
		return;

	SbXipImage *lut = 0;
	if (img->getComponents() == 1)
	{
		if (eltLut)
		{
			if (!eltLut->isOfType(SoXipDataImage::getClassTypeId()))
				return;

			lut = ((SoXipDataImage*) eltLut)->get();
		}
	}

	loadTexture(img, lut);

    if (output.getDataValue() != (SoXipData *)mCurrentImage)
        output.setDataValue((SoXipData *)mCurrentImage);
}

void SoXipApplyLutToImage::GLRender(SoGLRenderAction * action)
{
    try
    {
   		updateTexture(action);
	}
	catch (...)
    {
        SoError::post(__FILE__, "Unknown error while rendering image");
	}
}

void SoXipApplyLutToImage::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
	((SoXipApplyLutToImage*) user)->imageChanged();
}


















// creates an UNSIGNED_BYTE image of any given input image
SbXipImage * SoXipApplyLutToImage::createImage8(SbXipImage *in)
{
	const SbXipImageDimensions dim = in->getDimStored();
	const int components = in->getComponents();

	SbXipImage::ComponentLayoutType compLayout;
	switch (components)
	{
	case 1:	compLayout = SbXipImage::LUMINANCE; break;
	case 2:	compLayout = SbXipImage::LUMINANCE_ALPHA; break;
	case 3:	compLayout = SbXipImage::RGB; break;
	case 4:	compLayout = SbXipImage::RGBA; break;
	default:
		// unsupported
		return 0;
	}

	SbXipImage *out = new SbXipImage(dim, SbXipImage::UNSIGNED_BYTE, 8, components, 
		SbXipImage::INTERLEAVED, compLayout, in->getModelMatrix());
	SbXipImageInterleavedPixelPtr<unsigned char> outPtr(out);

	switch (in->getType())
	{
	case SbXipImage::UNSIGNED_BYTE:
		{
			SbXipImageInterleavedPixelPtr<unsigned char> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c);
		} break;
	case SbXipImage::BYTE:
		{
			SbXipImageInterleavedPixelPtr<char> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c) + 128;
		} break;
	case SbXipImage::UNSIGNED_SHORT:
		{
			int shift = in->getBitsStored() - 8;
			SbXipImageInterleavedPixelPtr<unsigned short> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c) >> shift;
		} break;
	case SbXipImage::SHORT:
		{
			int shift = in->getBitsStored() - 8;
			SbXipImageInterleavedPixelPtr<short> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = (inPtr(y, x, c) + 32768) >> shift;
		} break;
	case SbXipImage::FLOAT:
		{
			SbXipImageInterleavedPixelPtr<float> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c) * 255.f;
		} break;
	case SbXipImage::DOUBLE:
		{
			SbXipImageInterleavedPixelPtr<double> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c) * 255.;
		} break;
	}

	return out;
}

// creates an UNSIGNED_BYTE image of any given input image
SbXipImage * SoXipApplyLutToImage::createImage8Lut(SbXipImage *in, SbXipImage *lut)
{
	// convert LUT into UNSIGNED BYTE
	SbXipImage *lut8 = createImage8(lut);
	
	if (!lut8)
	{
		SoDebugError::postInfo(__FILE__, "createImage8 failed");
		return 0;
	}
	
	unsigned char *lut8Ptr = (unsigned char *) lut8->refBufferPtr();

	const SbXipImageDimensions dim = in->getDimStored();
	const int components = lut->getComponents();

	SbXipImage::ComponentLayoutType compLayout;
	switch (components)
	{
	case 1:	compLayout = SbXipImage::LUMINANCE; break;
	case 2:	compLayout = SbXipImage::LUMINANCE_ALPHA; break;
	case 3:	compLayout = SbXipImage::RGB; break;
	case 4:	compLayout = SbXipImage::RGBA; break;
	default:
		// unsupported
		return 0;
	}

	SbXipImage *out = new SbXipImage(dim, SbXipImage::UNSIGNED_BYTE, 8, components, 
		SbXipImage::INTERLEAVED, compLayout, in->getModelMatrix());
	SbXipImageInterleavedPixelPtr<unsigned char> outPtr(out);

	switch (in->getType())
	{
	case SbXipImage::UNSIGNED_BYTE:
		{
			SbXipImageInterleavedPixelPtr<unsigned char> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
				{
					unsigned char val = inPtr(y, x);
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = lut8Ptr[components * val + c];
				}
		} break;
	case SbXipImage::UNSIGNED_SHORT:
		{
			SbXipImageInterleavedPixelPtr<unsigned short> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
				{
					unsigned short val = inPtr(y, x);
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = lut8Ptr[components * val + c];
				}
		} break;
	case SbXipImage::SHORT:
		{
			SbXipImageInterleavedPixelPtr<short> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
				{
					unsigned short val = (inPtr(y, x) + 32768);
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = lut8Ptr[components * val + c];
				}
		} break;
	}

	lut8->unrefBufferPtr();
	delete lut8;

	return out;
}


