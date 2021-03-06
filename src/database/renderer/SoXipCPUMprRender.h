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

#ifndef SOXIPCPUMPRRENDER_H
#define SOXIPCPUMPRRENDER_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoSensor.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SbXipImage.h>

#define PI 3.1415926535897932384626433
#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

class SoFieldSensor;

#define UPDATE_MPR			1
#define UPDATE_MPRCACHE		2

struct mprCacheElem
{
	unsigned int	mprOffset;
	float			volCoord[3];
};

class SoXipCPUMprRender : public SoShape
{
SO_NODE_HEADER(SoXipCPUMprRender);

public:
	
	/// Static method providing Open Inventor runtype type information.
	static void initClass();

	///	Default constructor
	SoXipCPUMprRender();

	// Fields
	SoSFBool			blendOn;
	SoSFVec2s			minMaxSize;
	SoXipSFDataImage	volume;


protected:
	/// Default destructor
	virtual ~SoXipCPUMprRender();
	

protected:
	virtual void GLRender(SoGLRenderAction * action);
	virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
	virtual void generatePrimitives(SoAction *action) { };

	void	resizeBuffers(SbVec2s &size);
	void	updateTexture();
	void	renderMPR(int texUnit);
	void	readyBuffers(SoState *state);


public:
	//	Scan-conversion table
	mprCacheElem	*mMPRCache;
	unsigned int	mNumCacheElems;

	// Mpr buffer
	void			*mMPRBuf;
	int				mTexInternalFormat;
	int				mTexType;

	// Mpr texture ID
	unsigned int	mMPRTexId;
	// Size of mpr/scanconv
	SbVec2s			mMPRSize;
	
	// Data ids for detecting changes
	uint32_t		mVolDataId;	
	uint32_t		mLutDataId;

	// Volume info
	void					*mVolBuf;
	SbXipImageDimensions	mVolDim;
	SbXipImage::DataType	mVolDataType;
	int						mVolBitsUsed;

	// Lut info
	float					*mLutBuf;
	int						mLutSize;
	
	// MPR corners
	SbVec3f	mCorners[4];

	// Flags
	unsigned char	mUpdateFlag;
};


#endif //SOXIPCPUMPRRENDER_H
