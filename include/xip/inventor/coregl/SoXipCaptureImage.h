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
 *	Node class for texture handling
 */

#ifndef SO_XIP_CAPTURE_IMAGE_H
#define SO_XIP_CAPTURE_IMAGE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/system/GL/gl.h>
#include <xip/inventor/coregl/xipivcoregl.h>

class XIPIVCOREGL_API SoXipCaptureImage : public SoNode {
	SO_NODE_HEADER(SoXipCaptureImage);

public:
	SoXipCaptureImage();
	~SoXipCaptureImage();
	static void initClass();

	enum Format {
		COLOR_INDEX = GL_COLOR_INDEX,
		STENCIL_INDEX = GL_STENCIL_INDEX,
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		RED = GL_RED,
		GREEN = GL_GREEN,
		BLUE = GL_BLUE,
		ALPHA = GL_ALPHA,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		LUMINANCE = GL_LUMINANCE,
		LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA
	};

	enum Type {
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		BYTE = GL_BYTE,
		BITMAP = GL_BITMAP,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		SHORT = GL_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		INT = GL_INT,
		FLOAT = GL_FLOAT
	};

	SoSFEnum format;
	SoSFEnum type;
	SoSFTrigger capture;
	SoSFBool autoCapture;
	SoXipSFDataImage image;

	SoXipDataImage* mDataImage;

	bool mNeedCapture;

protected:
	void GLRender(SoGLRenderAction* action);
	void captureImage();
	
	SoFieldSensor *mSensorCapture;

private:
	static void sensorCaptureCB(void *usr, SoSensor *sensor);
};


#endif 



