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

#ifndef  SOXIPPROXY_H
#define  SOXIPPROXY_H

#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/sensors/SoFieldSensor.h>

/**
 * This node sets up the SoXipPlaneElement and adds it to the state.
 * Rendering nodes can read this element and clip the data accordingly.
 */
class SoXipProxy : public SoNode
{

    SO_NODE_HEADER(SoXipProxy);

  public:
   
    /// Constructor
    SoXipProxy();

    SoSFString  proxiedNodeName;

  SoEXTENDER public:
   
    virtual void        doAction(SoAction *action);
    virtual void        GLRender(SoGLRenderAction *action);
    virtual void        callback(SoCallbackAction *action);
    virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void        getMatrix(SoGetMatrixAction *action);
    virtual void        handleEvent(SoHandleEventAction *action);
    virtual void        pick(SoPickAction *action);
    virtual void        rayPick(SoRayPickAction *action);
    //virtual void        search(SoSearchAction *action);
    //virtual void        write(SoWriteAction *action); // We only want to write the real object once
#ifdef TGS_VERSION
    virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
    virtual void        distribute(SoDistributeAction *action);
#endif
    virtual void        GLRenderBelowPath(SoGLRenderAction *action);
    virtual void        GLRenderInPath(SoGLRenderAction *action);
    virtual void        GLRenderOffPath(SoGLRenderAction *action);
    virtual void        grabEventsSetup();
    virtual void        grabEventsCleanup();

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual         ~SoXipProxy();
    void            getProxy();
    static void     fieldSensorCBFunc(void *usr, SoSensor *sensor);

    bool                mNameChanged;
    SbName              mProxiedNodeName;
    SoNode              *mProxyNode;
    SoFieldSensor       *mSensor;
};

#endif // SOXIPPROXY_H
