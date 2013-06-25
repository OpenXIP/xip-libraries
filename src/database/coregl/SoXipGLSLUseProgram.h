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

#ifndef SO_XIP_GLSL_USE_PROGRAM_H
#define SO_XIP_GLSL_USE_PROGRAM_H


/**
 *  Component       : XIP
 *  Name            : SoXipGLSLUseProgram
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Wrapping of glUseProgram().
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include <Inventor/sensors/SoNodeSensor.h>

// Forward declaration
class SoGLRenderAction;

// Class declaration
class SoXipGLSLUseProgram : public SoNode
{
	SO_NODE_HEADER(SoXipGLSLUseProgram);
public:
	SoXipGLSLUseProgram();
	static void initClass();

    SoSFString	prgTag;

protected:
	~SoXipGLSLUseProgram();
	virtual void GLRender(SoGLRenderAction *action);
	inline void setHasChanged()	{this->mHasChanged = true;}
    static void updateSensorCB(void *data, SoSensor *sensor);
	void UpdateAction();

	SoFieldSensor *updateFieldSensor;

private:
    GLuint                      mProgramHandle;
    const char *                mProgramTag;
    bool						mHasChanged;
    SoFieldSensor				*mPrgSensor;

    // Main functionality method
    void updateProgramHandle();

    // Callback for the sensor attached to the fields
	static void	hasChangedCB(void * data,SoSensor*) { ((SoXipGLSLUseProgram *)data)->setHasChanged(); };
};

#endif // SO_RAD_LOAD_SHADERS
