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

#ifndef SO_XIP_PING_PONG_H
#define SO_XIP_PING_PONG_H


/**
 *  Component       : XIP
 *  Name            : SoXipPingPong
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Creates a copy of the current framebuffer
 *                      object and use the two instances for
 *                      ping pong rendering. Buffer flipping is
 *                      done with flip node.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

#include <xip/inventor/coregl/SoXipFboElement.h>
#include <xip/inventor/coregl/FramebufferObject.h>


class SoXipPingPong : public SoNode
{
	SO_NODE_HEADER(SoXipPingPong);

public:

	SoXipPingPong();
	void        GLRender(SoGLRenderAction* action);
	static void initClass();

    // "input" fields

    // "output" fields
	SoMFInt32   handleOutput;
	SoMFInt32   opUnitOutput;

protected:

    SoFieldSensor  *mSensorOut;
    int             mNumFields;
    int             mNumFieldsOut;

private:
	~SoXipPingPong();
    bool        checkFramebufferStatus();

#if USE_SENSORS
	static void sensorCB(void *usr, SoSensor *sensor);
#endif
    static void     sensorOutCB(void *usr, SoSensor *sensor);
	bool            mNeedsUpdate;

    void            allocateColors();
    void            allocateDepth();
    void            allocateFbo(SoAction * action);
    void            allocate(SoAction * action);
    void            deallocate();
    void            assignPingPongUnits(SoAction * action);
    void            syncHandleOutput();
    void            syncUnitOutput();

    FboSetup        mFboIn;
    FboSetup        mFboOut;

    GLuint          mColorHandles[16];
    GLuint          mDepthHandle;
    int             mNumAttachments;
    int             mMaxAttachments;
    unsigned int    mPingPongUnits[16];

    unsigned int    mNodeId;
    bool            mIsAllocated;
};


#endif // SO_XIP_FRAMEBUFFER_ATTACHMENTS_H
