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

#ifndef SOXIPLUT_H
#define SOXIPLUT_H

#include <vector>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/actions/SoActions.h>
#include <xip/inventor/core/SoXipSFDataImage.h>

class SoFieldSensor;
class SoXipDataImage;
struct colorRGBA;


class SoXipLut : public SoNode
{
	SO_NODE_HEADER(SoXipLut);

public:
	static void initClass();
	SoXipLut();

    enum InputType {
		RAMP,
		TRAPEZOID,
		FILE,
		ARRAY,
		RAMP_FILE,
        RAMP_ARRAY
    };

    enum OutputType {
		COLOR_ALPHA,
		COLOR,
		LUMINANCE
    };

	enum FileType {
		FLOAT_COMMA,
		FLOAT_SPACE,
		BYTE_COMMA,
		BYTE_SPACE
    };

	enum AlphaType {
		DEFAULT,
		CONSTANT,
		INTENSITY,
		RAMP_MINMAX,
		STEP_RAMP,
		STEP_CENTER,
		STEP_SECOND
    };

    // the data image as field
    SoXipSFDataImage LUTDataImage;

    SoSFEnum inputMode;
	SoSFEnum alphaMode;

	SoSFEnum fileMode;
	SoSFEnum outputMode;
	SoSFShort bitsUsed;

	// ramp parameters
	SoSFFloat rampWidth;
	SoSFFloat rampCenter;
	SoSFFloat alphaFactor;
	SoSFFloat slopeWidth;
	SoSFFloat slopeCenter;

	SoSFColor colorBottom;
	SoSFColor colorMiddle;
	SoSFColor colorTop;

	// file parameters
	SoSFString fileIn;
	SoSFInt32 fileEntries;
	
	// array parameters
	SoMFColor arrayColor;
	SoMFFloat arrayAlpha;

	// flag
	SoSFBool invertColor;

protected:
	virtual ~SoXipLut();
	virtual void loadFromFile(void *buffer);
	virtual void updateColorAlpha();
	virtual void updateColor();
	virtual void updateGray();

	virtual void doAction(SoAction * action);
	virtual void GLRender(SoGLRenderAction * action) { doAction(action); }
	virtual void callback(SoCallbackAction * action) { doAction(action); }
	virtual void pick(SoPickAction * action) { doAction(action); }
	
	virtual void adjustAlpha(colorRGBA* rgbaBuffer, int numElements, int start, int end);

	int mNumElements;
	SoXipDataImage *mLutData;
	unsigned int mNodeId;
};

#endif // SOXIPLUT_H


