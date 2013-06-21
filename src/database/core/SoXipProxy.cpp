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

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoActions.h>
#include <xip/inventor/core/SoXipClipPlaneElement.h>
#include "SoXipProxy.h"

SO_NODE_SOURCE(SoXipProxy);

////////////////////////////////////////////////////////////////////////
//
void SoXipProxy::initClass()
{
	SO_NODE_INIT_CLASS(SoXipProxy, SoNode, "SoNode");
}

////////////////////////////////////////////////////////////////////////
//
SoXipProxy::SoXipProxy()
{
    SO_NODE_CONSTRUCTOR(SoXipProxy);

    // Name of node to be proxied
    SO_NODE_ADD_FIELD(proxiedNodeName, (""));    
    
    mProxyNode = 0;
    mNameChanged = false;

    mSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
    mSensor->attach(&proxiedNodeName);
    mSensor->setPriority(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipProxy::fieldSensorCBFunc(void *usr, SoSensor *sensor)
{
    if (((SoXipProxy*)usr)->proxiedNodeName.getValue() != ((SoXipProxy*)usr)->mProxiedNodeName)
    {
        ((SoXipProxy*)usr)->mProxiedNodeName = ((SoXipProxy*)usr)->proxiedNodeName.getValue();
	    ((SoXipProxy*)usr)->mNameChanged = true;
    }
}

////////////////////////////////////////////////////////////////////////
//
SoXipProxy::~SoXipProxy()
{
    if (mProxyNode)
        mProxyNode->unref();
}

////////////////////////////////////////////////////////////////////////
//
void    SoXipProxy::getProxy()
{
    if (mProxyNode)
    {
        mProxyNode->unref();
        mProxyNode = 0;
    }
    mProxyNode = SoNode::getByName(mProxiedNodeName.getString());
    if (mProxyNode)
    {
        mProxyNode->ref();
        mNameChanged = false;
    }
}
#define LOG
//#define LOG SoDebugError::postInfo(__FUNCTION__, "")
#define PROXYFUNCA(FUNC, ACTION) void SoXipProxy::FUNC(ACTION *action) { LOG; if (mNameChanged) getProxy(); if (mProxyNode) mProxyNode->FUNC(action); }
#define PROXYFUNC(FUNC) void SoXipProxy::FUNC() { LOG; if (mNameChanged) getProxy(); if (mProxyNode) mProxyNode->FUNC(); }

PROXYFUNCA(doAction, SoAction)
PROXYFUNCA(GLRender, SoGLRenderAction)
PROXYFUNCA(callback, SoCallbackAction)
PROXYFUNCA(getBoundingBox, SoGetBoundingBoxAction)
PROXYFUNCA(getMatrix, SoGetMatrixAction)
PROXYFUNCA(handleEvent, SoHandleEventAction)
PROXYFUNCA(pick, SoPickAction)
PROXYFUNCA(rayPick, SoRayPickAction)
#ifdef TGS_VERSION
PROXYFUNCA(getPrimitiveCount, SoGetPrimitiveCountAction)
PROXYFUNCA(distribute, SoDistributeAction)
#endif
PROXYFUNCA(GLRenderBelowPath, SoGLRenderAction)
PROXYFUNCA(GLRenderInPath, SoGLRenderAction)
PROXYFUNCA(GLRenderOffPath, SoGLRenderAction)
PROXYFUNC(grabEventsSetup)
PROXYFUNC(grabEventsCleanup)
