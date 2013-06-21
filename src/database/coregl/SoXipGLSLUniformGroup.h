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

#ifndef SO_XIP_GLSL_UNIFORM_GROUP_H
#define SO_XIP_GLSL_UNIFORM_GROUP_H

#include<xip/system/standard.h>

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoMFString.h>


/*! \class SoXipGLSLUniformGroup
*  \brief A volume group for collecting nodes relevant to a volume
*/
class SoXipGLSLUniformGroup : public SoGroup 
{
	SO_NODE_HEADER(SoXipGLSLUniformGroup);

public:
    /// Constructor, initilaize fields and defaults
    SoXipGLSLUniformGroup();

    /// Initializes the SoXipVolDataElement class
	static void initClass();

    /// field enable/disables this group
    SoMFString          prgTags;

protected:
    /// Destructor, dereference data
	virtual ~SoXipGLSLUniformGroup();

    /// Performs the action, sets the crop box data
	virtual void groupUpdate(SoAction * action);

    /// Performs the action, sets the crop box data
	virtual void doAction(SoAction * action);

    /// Performs GL render action
	virtual void GLRender(SoGLRenderAction * action);

    /// Performs the callback
	virtual void callback(SoCallbackAction * action);

private:

    unsigned int mNodeId;
    int mNumPrograms;
    __uint64 * mProgramTimeStamps;
    bool mNeedsUpdate;
};

#endif // SO_XIP_GLSL_UNIFORM_GROUP_H
