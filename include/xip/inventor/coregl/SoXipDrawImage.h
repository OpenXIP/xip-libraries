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
#ifndef SO_XIP_DRAW_IMAGE_H
#define SO_XIP_DRAW_IMAGE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/system/GL/gl.h>
#include <xip/inventor/coregl/xipivcoregl.h>

class XIPIVCOREGL_API SoXipDrawImage : public SoNode {
	SO_NODE_HEADER(SoXipDrawImage);

public:
	SoXipDrawImage();
	
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

	SoSFEnum format;
	SoXipSFDataImage inputImage;

protected:
	void GLRender(SoGLRenderAction* action);
	void drawImage(SbXipImage* image);
};


#endif 



