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
#ifndef SOXIPREMOTELUT_H
#define SOXIPREMOTELUT_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>

#include <xip/inventor/remote/XipRequestManager.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoSFNode.h>
#include <xip/inventor/remote/XipRenderActionParams.h>
#include "SoXipDataConnection.h"
#include <vector>


class SoXipRemoteLut : public SoNode
{

    SO_NODE_HEADER(SoXipRemoteLut);

public:
    SoSFString          lutName;
    SFXipConnection     connection;

    // Constructor
    SoXipRemoteLut();

    static void initClass();

	/////////////////////////////////////
    enum InputType {
		RAMP,
		TRAPEZOID,
		FILE,
		ARRAY,
		RAMP_FILE
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
	SoSFString  fileIn;
	SoSFInt32   fileEntries;
	/////////////////////////////////////

protected:
    virtual ~SoXipRemoteLut();

    virtual void inputChanged(SoField *whichField);

    void update();
    int sendAll();
    int sendInputMode();
    int sendAlphaMode();
    int sendFileMode();
    int sendOutputMode();
    int sendBitsUsed();
    int sendRampWidth();
    int sendRampCenter();
    int sendAlphaFactor();
    int sendSlopeWidth();
    int sendSlopeCenter();
    int sendColorBottom();
    int sendColorMiddle();
    int sendColorTop();
    int sendFileIn();
    int sendFileEntries();

    void doAction(SoAction *action);
    void GLRender(SoGLRenderAction * action);

    XipStreamBase           *mStream;
    XipTreeRequestSender    mReqSender;
    XipTreeRequestReceiver  mReqReceiver;

    std::vector<SoFieldSensor*>     mInputSensors;
    static void fieldSensorCBFunc(void *usr, SoSensor *sensor);

    bool m_bHasChangedValues;
};

#endif
