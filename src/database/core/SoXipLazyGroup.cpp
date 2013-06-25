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


#include <Inventor/actions/SoGLRenderAction.h>
#include "SoXipLazyGroup.h"


SO_NODE_SOURCE( SoXipLazyGroup );

SoXipLazyGroup::SoXipLazyGroup()
{
    SO_NODE_CONSTRUCTOR(SoXipLazyGroup);

    mNodeID = 0;
}

void SoXipLazyGroup::initClass()
{
    SO_NODE_INIT_CLASS(SoXipLazyGroup, SoGroup, "Group")
}

void SoXipLazyGroup::GLRender(SoGLRenderAction *action)
{
    if(mNodeID != getNodeId())
    {
        mNodeID = getNodeId();
        SoGroup::GLRender(action); // traverse children...
    }
}

