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

#ifndef SO_XIP_APPLY_LUT_TO_IMAGE_H
#define SO_XIP_APPLY_LUT_TO_IMAGE_H

#include <Inventor/nodes/SoSubNode.h>
#include <xip/inventor/core/SoXipSFDataImage.h>

class SoFieldSensor;
class SbXipImage;
class SoXipDataImage;
class SoXipTexture;
class SoMatrixTransform;

class SoXipApplyLutToImage : public SoNode
{
	SO_NODE_HEADER( SoXipApplyLutToImage );

public:

	/// Constructor
	SoXipApplyLutToImage();

	/// Open Inventor class initialization
	static void initClass();

	/// Image to be displayed
	SoXipSFDataImage	image;
	SoXipSFDataImage	output;

protected:

	/// Destructor
	virtual ~SoXipApplyLutToImage();

    /// GL render call
	virtual void GLRender(SoGLRenderAction * action);

	//virtual void callback(SoCallbackAction * action);
	//virtual void pick(SoPickAction * action);
	//virtual void rayPick (SoRayPickAction *action);
	//virtual void handleEvent (SoHandleEventAction *action);
	//virtual void getBoundingBox(SoGetBoundingBoxAction *action);

	virtual void imageChanged();
	virtual void updateTexture(SoAction *action);
	virtual void loadTexture(SbXipImage *img, SbXipImage *lut);

protected:

	SoXipDataImage    * mCurrentImage;
	SoFieldSensor     * mImageSensor;

private:

    SbXipImage * createImage8(SbXipImage *in);
    SbXipImage * createImage8Lut(SbXipImage *in, SbXipImage *lut);


	static void fieldSensorCBFunc(void *user, SoSensor *sensor);

	uint32_t        mImageId;
	uint32_t        mLutId;
};

#endif // SoXipApplyLutToImage_H
