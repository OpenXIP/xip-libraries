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
/**
 *	Node class to create an OpenGL texture from a
 *	lookup table
 */

#ifndef _SO_XIP_LUT_TEXTURE_H
#define _SO_XIP_LUT_TEXTURE_H

#include <xip/inventor/core/SoXipDataImage.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 *	SoXipLutTexture. An Open Inventor node to create
 *	an OpenGL texture from a lookup table
 */
class SoXipLutTexture : public SoNode
{
	SO_NODE_HEADER( SoXipLutTexture );

public:

	// Perform linear interpolation on the texture
	SoSFBool	interpolation;
	// Perform RGB pre-multiplication by the alpha (used for front to back VR)
	SoSFBool	preMultiplyRGB;
	// Perform opacity correction (used for VR)
	SoSFBool	opacityCorrection;
	// Sampling rate (used for opacity correction)
	SoSFFloat	samplingRate;
	// Should the sampling rate be affected by complexity element?
	SoSFBool	useComplexity;
    // Trigger to indicate update
    SoSFTrigger nodeUpdated;
	// Output field that shows what the LUT texture size is
	SoSFVec2s	textureSize;

	// Constructor
	SoXipLutTexture();

	// Initializes the class
	static void initClass();

protected:

	// Destructor
	~SoXipLutTexture();
	//
	void	GLRender(SoGLRenderAction *action);
	void	resizeTexture(SbXipImage *image);
	void	updateTexture(SbXipImage *image);


	// The OpenGL texture's Id
	unsigned int		mTextureId;
	// The Lookup Table image's DataId
	unsigned int        mLutId;
	// internal buffer
	float				*mBuf;
	SbVec2s				mTexSize;

	bool				mPreMultiply;
	bool				mAlphaCorrection;
	float				mSampleRate;
};

#endif


