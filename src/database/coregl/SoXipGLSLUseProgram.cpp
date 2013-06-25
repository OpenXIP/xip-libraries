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
#include <xip/inventor/coregl/ShaderProgramManager.h>
#include "SoXipGLSLUseProgram.h"

#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/SoXipShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>

#undef DEBUG
#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif


SO_NODE_SOURCE(SoXipGLSLUseProgram);


SoXipGLSLUseProgram::SoXipGLSLUseProgram()
{
	SO_NODE_CONSTRUCTOR(SoXipGLSLUseProgram);
	
    SO_NODE_ADD_FIELD(prgTag, (""));

	mPrgSensor = new SoFieldSensor(hasChangedCB, this);
	mPrgSensor->attach(&this->prgTag);
	mHasChanged = true;
}

void SoXipGLSLUseProgram::updateSensorCB(void *data, SoSensor *sensor)
{
	// cast editor object
	SoXipGLSLUseProgram *thisObj = (SoXipGLSLUseProgram*)data;
	thisObj->UpdateAction();
}

void SoXipGLSLUseProgram::UpdateAction(){
    updateProgramHandle();
}

/**
 *	Destructor.
 */	
SoXipGLSLUseProgram::~SoXipGLSLUseProgram()
{
    // Delete self
	delete mPrgSensor;
}

/**	
 *	Initializes the class.
 */
void SoXipGLSLUseProgram::initClass()
{
	SO_NODE_INIT_CLASS(SoXipGLSLUseProgram, SoNode, "SoNode");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipShaderProgramElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLSLShaderProgramElement);
}

/**
 * Binds the shader associated witg requested tag.
 * Outputs Info/Warnings depending on level of success.
 */
void SoXipGLSLUseProgram::updateProgramHandle()
{
    // If empty string, bind program 0
    if (prgTag.getValue() == "")
    {
        mProgramHandle = 0;
        //SoDebugError::postInfo("Use program","No shader bound\n");
    }
    else
    {
        // Retrieve information
        mProgramTag = prgTag.getValue().getString();
        ShaderProgramManager * manager = ShaderProgramManager::getInstance();
        // Store information
        if (manager)
        {
            mProgramHandle = manager->getProgramHandle(mProgramTag);

            if (mProgramHandle)
                if (!glIsProgram(mProgramHandle))
                    manager->removeEntry(mProgramTag);
        }
#if 0
        if(mProgramHandle)
            SoDebugError::postInfo("Bound shader",prgTag.getValue().getString());
        else
            SoDebugError::postWarning("Use Program","Error when binding shader, no shader bound\n");
#endif
    }
}

/**
 * GLRender.
 * Check if changed, if so than update then render otherwise just render.
 */
void SoXipGLSLUseProgram::GLRender(SoGLRenderAction *action)
{
#if 1
    int handle = SoXipGLSLShaderProgramElement::get(action->getState());
    updateProgramHandle();
    if (handle != (int)mProgramHandle)
	    SoXipGLSLShaderProgramElement::set(action->getState(), mProgramHandle);
#else
	if (mHasChanged)
	{
		useProgram();
		mHasChanged = false;
	}
	SoXipGLSLShaderProgramElement::set(action->getState(), mProgramHandle);
#endif
}


