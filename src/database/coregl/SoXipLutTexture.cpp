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
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/errors/SoErrors.h>
#include "SoXipLutTexture.h"

SO_NODE_SOURCE(SoXipLutTexture);

/**
 *	Constructor
 */	
SoXipLutTexture::SoXipLutTexture()
{
	SO_NODE_CONSTRUCTOR(SoXipLutTexture);

	SO_NODE_ADD_FIELD(interpolation, (TRUE));
	SO_NODE_ADD_FIELD(preMultiplyRGB, (TRUE));
	SO_NODE_ADD_FIELD(opacityCorrection, (TRUE));
	SO_NODE_ADD_FIELD(samplingRate, (1.0f));
	SO_NODE_ADD_FIELD(useComplexity, (FALSE));
	SO_NODE_ADD_FIELD(textureSize, (SbVec2s(0, 0)));
    SO_NODE_ADD_FIELD(nodeUpdated, ());

	mTextureId = 0;
    mLutId = 0;
	mBuf = 0;
	mTexSize = SbVec2s(0,0);
}

/**
 *	Destructor
 */	
SoXipLutTexture::~SoXipLutTexture()
{
	if (mTextureId)
		glDeleteTextures(1, &mTextureId);
	if (mBuf)
		delete[] mBuf;
}

/**	
 *	Initializes the class
 */
void SoXipLutTexture::initClass()
{
	SO_NODE_INIT_CLASS(SoXipLutTexture, SoNode,  "Node");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction,	SoXipMultiTextureElement);
	SO_ENABLE(SoGLRenderAction, SoXipLutElement);
	SO_ENABLE(SoGLRenderAction, SoComplexityElement);
}

void SoXipLutTexture::GLRender(SoGLRenderAction *action)
{
	SoState *state = action->getState();
	if (!state)
		return;

	try
    {
		// Create the texture id 
		if (!mTextureId)
			glGenTextures(1, &mTextureId);

		//	Get the current LUT element
	    SoXipDataImage* image = (SoXipDataImage *) SoXipLutElement::get(state);
    	
	    if (image)
	    {
			glPushAttrib(GL_ENABLE_BIT);
			//	Enable OpenInventor texture
			SoGLTextureEnabledElement::set(state, TRUE);
			// Bind the texture
			SoXipMultiTextureElement::bindTexture(state, GL_TEXTURE_2D, mTextureId);

		    if (!image->isOfType(SoXipDataImage::getClassTypeId()))
		    {
			    SoDebugError::post(__FILE__, "Invalid Lut Image");
				glPopAttrib();
			    return;
		    }
			
			bool preMultiply = preMultiplyRGB.getValue() == TRUE;
			bool alphaCorrection = opacityCorrection.getValue() == TRUE;
			float sRate = samplingRate.getValue();
			if (useComplexity.getValue())
			{
				float complexity = SoComplexityElement::get(state);
				// Inventor complexity usually ranges from 0.1 -> 0.5, remap to 0.2 -> 1.0
				sRate *= 2.f * complexity;
			}
			
			bool update = false;
			if (preMultiply != mPreMultiply ||
				alphaCorrection != mAlphaCorrection)
			{
				update = true;
				mPreMultiply = preMultiply;
				mAlphaCorrection = alphaCorrection;
			}
			if (mAlphaCorrection && sRate != mSampleRate)
			{
				update = true;
				mSampleRate = sRate;
			}
		 
			//	New LUT
		    if (update || image->getDataId() != mLutId)
		    {
				// update lut id for next time
			    mLutId = image->getDataId();

				SbXipImage *img = image->get();
				if (img)
				{
					SbVec2s texSize;
					// Get the number of elements and make sure it's valid
					int totLutElements = img->getDimStored()[0];
					if (!totLutElements)
					{
						SoDebugError::postInfo(__FILE__, "Invalid LUT Image: 0 elements");
						glPopAttrib();
						return;
					}
					else if (totLutElements <= 4096)
						texSize = SbVec2s(totLutElements, 1);
					else if (totLutElements == 65536)
						texSize = SbVec2s(256, 256);
					else
					{
						SoDebugError::postInfo(__FILE__, "Invalid LUT Image: %d elements", totLutElements);
						glPopAttrib();
						return;
					}				

					// Resize texture if different number of elements
					if (mTexSize != texSize)
					{
						mTexSize = texSize;
						textureSize.setValue(mTexSize);
						resizeTexture(img);
					}
					updateTexture(img);
				}
			}
			glPopAttrib();
		}
    }
	//	Handle exceptions
    catch (...)
    {
        SoDebugError::post(__FILE__, "Unknown Exception");
        return;
    }
}


void	SoXipLutTexture::resizeTexture(SbXipImage *image)
{
	glTexImage2D(GL_TEXTURE_2D,		// target
		       0,					// level
		       GL_RGBA_FLOAT16_ATI,	// internal
		       mTexSize[0],			// width
		       mTexSize[1],			// height
		       0,					// border
		       GL_RGBA,				// format
		       GL_FLOAT,			// type
		       0);

	//	set the texture parameters for OpenGL
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GLint intr = interpolation.getValue() ? GL_LINEAR : GL_NEAREST;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, intr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, intr);

	if (mBuf)
		delete mBuf;
	mBuf = new float[mTexSize[0] * mTexSize[1] * 4];
}

void	SoXipLutTexture::updateTexture(SbXipImage *image)
{
	if (image->getType() != SbXipImage::FLOAT ||
		image->getComponentLayoutType() != SbXipImage::RGBA)
	{
		SoDebugError::postInfo(__FILE__, "Invalid LUT Image: expecting RGBA Float");
		return;
	}
	
	//	Get the pixel buffer of the LUT
	const float* buf = (float *) image->refBufferPtr();
	if (!buf)
		return;

	float factor = 1.0f / mSampleRate; // baseline (HQ) factor
	
	// Pre-multiply colors by alpha
	for (int i = 0; i < image->getDimStored()[0]; ++i)
	{
		float alpha = buf[(i << 2) + 3];
		if (mAlphaCorrection)
			alpha = 1.0f - pow(1.0f - alpha, factor);
		mBuf[(i << 2) + 0] = buf[(i << 2) + 0] * (mPreMultiply ? alpha : 1.0f);
		mBuf[(i << 2) + 1] = buf[(i << 2) + 1] * (mPreMultiply ? alpha : 1.0f);
		mBuf[(i << 2) + 2] = buf[(i << 2) + 2] * (mPreMultiply ? alpha : 1.0f);
		mBuf[(i << 2) + 3] = alpha;
	}
	image->unrefBufferPtr();

	// Save unpack alignment
	int align;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &align);
	// Set optimal unpack alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, getPackAlignment(mTexSize[0]));
	// Upload texture
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mTexSize[0], mTexSize[1], GL_RGBA, GL_FLOAT, mBuf);	
	// Restore unpack alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, align);

    //Indicate that everything has updated
    nodeUpdated.touch();
}



