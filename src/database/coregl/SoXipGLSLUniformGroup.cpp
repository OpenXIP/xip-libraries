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
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>

#include "SoXipGLSLUniformGroup.h"
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/misc/SoChildList.h>


#define GLSL_MAX_NUM_SHADERS 256


SO_NODE_SOURCE(SoXipGLSLUniformGroup);

/** \fn SoXipGLSLUniformGroup::SoXipGLSLUniformGroup()
* All input and output fields are added and initialized here. 
* \return none
*/
SoXipGLSLUniformGroup::SoXipGLSLUniformGroup(void)
{
	SO_NODE_CONSTRUCTOR(SoXipGLSLUniformGroup);
    SO_NODE_ADD_FIELD(prgTags,(""));

    mNumPrograms = 0;
    mProgramTimeStamps = (__uint64*)calloc(GLSL_MAX_NUM_SHADERS, sizeof(__uint64));
    mNodeId = 0;
    mNeedsUpdate = true;
}


/*! \fn SoXipGLSLUniformGroup::~SoXipGLSLUniformGroup()
 * \brief Destructor, cleans up internal data
 * \return None
 */
SoXipGLSLUniformGroup::~SoXipGLSLUniformGroup()
{
    if (mProgramTimeStamps)
        free(mProgramTimeStamps);
    mProgramTimeStamps = 0;
}


/*! \fn SoXipGLSLUniformGroup::initClass()
 * Initializes this class. Called on dll initialization.
 * \return void
 */
void SoXipGLSLUniformGroup::initClass(void)
{
	SO_NODE_INIT_CLASS(SoXipGLSLUniformGroup, SoGroup, "Group");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement );
	SO_ENABLE(SoGLRenderAction, SoXipGLSLShaderProgramElement );
}


/*! \fn SoXipGLSLUniformGroup::doAction(SoAction * action)
 *  Adds a node to the SoXipGLSLUniformGroupElement in the current state
 *  \param action - the current state action, no action taken if input action is NULL
 *  \return void
 */
void SoXipGLSLUniformGroup::doAction(SoAction * action)
{
    SoChildList * children = this->getChildren();
    children->traverse(action);
}

/*! \fn SoXipGLSLUniformGroup::doAction(SoAction * action)
 *  Adds a node to the SoXipGLSLUniformGroupElement in the current state
 *  \param action - the current state action, no action taken if input action is NULL
 *  \return void
 */
void SoXipGLSLUniformGroup::groupUpdate(SoAction * action)
{
    SoChildList * children = this->getChildren();
    GLint prg = SoXipGLSLShaderProgramElement::get(action->getState());

    if (mNumPrograms > GLSL_MAX_NUM_SHADERS)
    {
        SoDebugError::postWarning(__FUNCTION__, "supports %i shaders (requested %d)", GLSL_MAX_NUM_SHADERS, mNumPrograms);
        mNumPrograms = GLSL_MAX_NUM_SHADERS;
    }

    for (int i = 0; i < mNumPrograms; i++)
    {
/*
    To prevent uniforms from updating every frame
    we only update the uniform if the time stamp
    of the selected shader is out of date or if
    anything has changed among the uniforms such
    as names or values.

    TODO: This fix do not work since we have no
    way of knowing if other instances of this
    node also changes the same uniforms. Since
    this will not change the timestamp in the
    manager the uniform remains as last updated
    and fix don't work.

    No solution to the problem yet!
    Stefan Lindholm
*/
#if 0
        int handle = SoXipGLSLShaderProgramElement::getProgramID(action->getState(), prgTags[i].getString());
        if (glIsProgram(handle))
        {
            SoXipGLSLShaderProgramElement::set(action->getState(), prgTags[i].getString());
            children->traverse(action);
        }
#else
        __uint64 currTime = SoXipGLSLShaderProgramElement::getTimeStamp(action->getState(), prgTags[i].getString());
        if (currTime != mProgramTimeStamps[i] || mNeedsUpdate)
        {
            SoXipGLSLShaderProgramElement::set(action->getState(), prgTags[i].getString());
            children->traverse(action);
            mProgramTimeStamps[i] = currTime;
        }
#endif
    }

    SoXipGLSLShaderProgramElement::set(action->getState(), prg);
    mNeedsUpdate = false;
}








/*! \fn SoXipGLSLUniformGroup::GLRender(SoGLRenderAction * action) 
*  Derived inventor GLRender method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipGLSLUniformGroup::GLRender(SoGLRenderAction * action)
{
    if (mNodeId != getNodeId())
    {
        mNodeId = getNodeId();
        mNumPrograms = prgTags.getNum();
        mNeedsUpdate = true;
    }

	groupUpdate(action);
}


/*! \fn SoXipGLSLUniformGroup::callback(SoCallbackAction * action) 
*  Derived inventor callback method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipGLSLUniformGroup::callback(SoCallbackAction * action)
{
	doAction(action);
}
