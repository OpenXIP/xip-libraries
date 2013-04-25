/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */


#include "SoXipPingPong.h"
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>


SO_NODE_SOURCE(SoXipPingPong);

SoXipPingPong::SoXipPingPong()
{
	SO_NODE_CONSTRUCTOR(SoXipPingPong);

    SO_NODE_ADD_FIELD(handleOutput, (0));
    SO_NODE_ADD_FIELD(opUnitOutput, (0));

    // Attach output sensor to output fields
	mSensorOut = new SoFieldSensor(sensorOutCB, this);
    mSensorOut->attach(&handleOutput);
    mSensorOut->attach(&opUnitOutput);

    for (int i = 0; i < 16; i++)
        mColorHandles[i] = 0;
    for (int i = 0; i < 16; i++)
        mPingPongUnits[i] = 0;

    mDepthHandle = 0;
    mNodeId = 0;

    mFboIn.clear();
    mFboOut.clear();
}

/**
 *  Destructor.
 */
SoXipPingPong::~SoXipPingPong()
{
    delete mSensorOut;
}

/**
 *  Class initiator.
 */
void SoXipPingPong::initClass() {
	SO_NODE_INIT_CLASS(SoXipPingPong, SoNode, "SoNode");

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipDrawBuffersElement);
    SO_ENABLE(SoGLRenderAction, SoXipFboElement);
}



/**
 *  Run a check and output any errors.
 */
bool SoXipPingPong::checkFramebufferStatus()
{
    bool isOk = false;
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            isOk = true;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            SoDebugError::post("SoXipPingPong", "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            SoDebugError::post("SoXipPingPong", "GL_FRAMEBUFFER_UNSUPPORTED_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            SoDebugError::post("SoXipPingPong", "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            SoDebugError::post("SoXipPingPong", "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            SoDebugError::post("SoXipPingPong", "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            SoDebugError::post("SoXipPingPong", "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            SoDebugError::post("SoXipPingPong", "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT");
            break;
        default:
            SoDebugError::post("SoXipPingPong", "UNKNWON frambuffer fault");
    }
    return isOk;
} 



/**
 *  Creates color attachment.
 */
void SoXipPingPong::allocateColors()
{
    if (mFboOut.numColorAttachments)
    {
        if (mFboOut.colorStorage == GL_TEXTURE_2D)
        {
            // Generate textures
            glGenTextures(mNumAttachments, mColorHandles);
            for (int i = 0; i < mNumAttachments; i++)
            {
                glBindTexture(GL_TEXTURE_2D, mColorHandles[i]);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mFboOut.colorWrap);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mFboOut.colorWrap);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFboOut.colorFilter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFboOut.colorFilter);
                glTexImage2D(GL_TEXTURE_2D, 0, mFboOut.internalColorFormat, mFboOut.width, mFboOut.height,
                    0, mFboOut.colorFormat, GL_UNSIGNED_BYTE, NULL);
            }
	        glBindTexture(GL_TEXTURE_2D, 0);
        }
        else if (mFboOut.colorStorage == GL_RENDERBUFFER_EXT)
        {
            // Generate renderbuffers
            glGenRenderbuffersEXT(mNumAttachments, mColorHandles);
            for (int i = 0; i < mNumAttachments; i++)
            {
                glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mColorHandles[i]);
                glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, mFboOut.internalColorFormat, mFboOut.width, mFboOut.height);
            }
            glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
        }
    }
    else
        for (int i = 0; i < 16; i++)
            mColorHandles[i] = 0;

	for (int i = 0; i < 16; i++)
		mFboOut.colorHandles[i] = mColorHandles[i];
}

/**
 *  Creates depth attachment.
 */
void SoXipPingPong::allocateDepth()
{
    if (mFboOut.numDepthAttachments)
    {
        if (mFboOut.depthStorage == GL_TEXTURE_2D)
        {
            // Generate textures
            glGenTextures(1, &mDepthHandle);
            glBindTexture(GL_TEXTURE_2D, mDepthHandle);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mFboOut.depthWrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mFboOut.depthWrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFboOut.depthFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFboOut.depthFilter);
            glTexImage2D(GL_TEXTURE_2D, 0, mFboOut.internalDepthFormat, mFboOut.width, mFboOut.height,
                0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	        glBindTexture(GL_TEXTURE_2D, 0);
        }
        else if (mFboOut.depthStorage == GL_RENDERBUFFER_EXT)
        {
            // Generate renderbuffers
            glGenRenderbuffersEXT(1, &mDepthHandle);
            glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mDepthHandle);
            glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, mFboOut.internalDepthFormat, mFboOut.width, mFboOut.height);
            glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
        }
    }
    else
        mDepthHandle = 0;

	mFboOut.depthHandle = mDepthHandle;
}


/**
 *  Creates FBO.
 */
void SoXipPingPong::allocateFbo(SoAction * action)
{
	// Allocate framebuffer
    glGenFramebuffersEXT(1, &mFboOut.fboHandle);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFboOut.fboHandle);
    SoXipDrawBuffersElement::set(action->getState(), this, mFboOut.numColorAttachments);

    // Attach colors
    if (mFboOut.colorStorage == GL_TEXTURE_2D) {
        for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++)
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, GL_TEXTURE_2D, mColorHandles[i], 0);
    }
    else if (mFboOut.colorStorage == GL_RENDERBUFFER_EXT) {
        for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++)
            glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, GL_RENDERBUFFER_EXT, mColorHandles[i]);
    }

    // Attach depth
    if (mFboOut.numDepthAttachments) {
        if (mFboOut.depthStorage == GL_TEXTURE_2D)
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, mDepthHandle, 0);
        else if (mFboOut.depthStorage == GL_RENDERBUFFER_EXT)
            glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mDepthHandle);
    }

    mFboOut.isComplete = checkFramebufferStatus();

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFboIn.fboHandle);
    SoXipDrawBuffersElement::set(action->getState(), this, mFboIn.numColorAttachments);
}

/**
 *  Frame buffer object allocation.
 *  Allocates FBO's according to user/engine/state variables.
 */
void SoXipPingPong::allocate(SoAction * action)
{
	// Check for size 0 framebuffer
    if (mFboOut.width == 0 || mFboOut.height == 0) {
		SoDebugError::post(__FUNCTION__, "Tried to initialize a framebuffer of size 0");
		return;
	}

	// Check for necessary GLOW extension
	if (!GLOW_EXT_framebuffer_object) {
		SoDebugError::post(__FUNCTION__, "Driver does not support necessary extensions\n");
		return;
	}

    allocateColors();
    allocateDepth();
    allocateFbo(action);

#ifdef a_DEBUG
    if (mFboOut.isComplete)
        SoDebugError::postInfo("SoXipPingPong", "Secondary fbo complete with (%d %d %d)",
            mFboOut.fboHandle, mFboOut.numColorAttachments, mDepthHandle);
    else
        SoDebugError::postInfo("SoXipPingPong", "Secondary fbo incomplete with (%d %d %d)",
            mFboOut.fboHandle, mFboOut.numColorAttachments, mDepthHandle);
#endif

	mIsAllocated = true;
}

/**
 *  Deallocation of a buffer.
 */
void SoXipPingPong::deallocate()
{
	glDeleteFramebuffersEXT(1, &mFboOut.fboHandle);
    glDeleteTextures(mFboOut.numColorAttachments, mColorHandles);
    glDeleteRenderbuffersEXT(mFboOut.numColorAttachments, &mDepthHandle);

    mFboOut.fboHandle = 0;
    mDepthHandle = 0;
	for (int i = 0; i < 16; i++)
		mColorHandles[i] = 0;
	for (int i = 0; i < 16; i++)
		mPingPongUnits[i] = 0;

	mIsAllocated = false;
	//SoDebugError::postInfo(__FUNCTION__, "Released resources");
}


/**
 *  Get free texture units for pingpong.
 */
void SoXipPingPong::assignPingPongUnits(SoAction * action)
{
    int freeUnit = 0;
    unsigned int dummyHandle = 0;
    glGenTextures(1, &dummyHandle);

    // Get the n next free units
    for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++)
    {
        freeUnit = SoXipMultiTextureElement::getFreeUnit(action->getState());
        SoXipMultiTextureElement::setUnit(action->getState(), freeUnit);
        SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, dummyHandle);
        mPingPongUnits[i] = freeUnit;
    }
    // Bind them back from dummyhanlde to 0 ?
    for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++)
    {
        SoXipMultiTextureElement::setUnit(action->getState(), mPingPongUnits[i]);
        SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, 0);
    }

    glDeleteTextures(1, &dummyHandle);
}


/**
 *  Synchronize output.
 *  Field kept as multi field due to compatability with color version
 *  and UseTextures node.
 */
void SoXipPingPong::syncHandleOutput()
{
    bool outputDirty = false;
    
    if (!mColorHandles || mFboOut.numColorAttachments > 16)
        SoDebugError::post("SoXipPingPong", "invalid pointer or more than 16 handles");
    else {
        // Expand list by padding with zeros if to short
        if (handleOutput.getNum() < (int)mFboOut.numColorAttachments) {
            for (int i = handleOutput.getNum(); i < (int)mFboOut.numColorAttachments; i++) {
                handleOutput.set1Value(i, 0);
                outputDirty = true;
            }
        }

        // Update entries if changed
        for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++) {
            if (handleOutput[i] != mColorHandles[i]) {
                handleOutput.set1Value(i, static_cast<int>(mColorHandles[i]));
                outputDirty = true;
            }
        }

        // Remove absolete entries
        if (handleOutput.getNum() > (int)mFboOut.numColorAttachments) {
            handleOutput.deleteValues(mFboOut.numColorAttachments);
            outputDirty = true;
        }
    }

    mNodeId = getNodeId();
}


/**
 *  Synchronize output.
 *  Field kept as multi field due to compatability with color version
 *  and UseTextures node.
 */
void SoXipPingPong::syncUnitOutput()
{
    bool outputDirty = false;
    
    if (!mColorHandles || mFboOut.numColorAttachments > 16)
        SoDebugError::post("SoXipPingPong", "invalid pointer or more than 16 handles");
    else {
        // Expand list by padding with zeros if to short
        if (opUnitOutput.getNum() < (int)mFboOut.numColorAttachments) {
            for (int i = opUnitOutput.getNum(); i < (int)mFboOut.numColorAttachments; i++) {
                opUnitOutput.set1Value(i, 0);
                outputDirty = true;
            }
        }

        // Update entries if changed
        for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++) {
            if (opUnitOutput[i] != mPingPongUnits[i]) {
                opUnitOutput.set1Value(i, static_cast<int>(mPingPongUnits[i]));
                outputDirty = true;
            }
        }

        // Remove absolete entries
        if (opUnitOutput.getNum() > (int)mFboOut.numColorAttachments) {
            opUnitOutput.deleteValues(mFboOut.numColorAttachments);
            outputDirty = true;
        }
    }

    mNodeId = getNodeId();
}


/**
 *  Sets up the buffers, saves the state and pushes the effected attributes.
 *  Allocates buffer if need be and performs most functionallity.
 */
void SoXipPingPong::GLRender(SoGLRenderAction* action)
{
    FboSetup * fbo = SoXipFboElement::getActive(action->getState(), this);

    if (*fbo != mFboIn || fbo->isDirty) {
        mFboIn = *fbo;
        mFboIn.isDirty = false;
        mNeedsUpdate = true;
        //SoDebugError::postInfo("SoXipPingPong", "mFboIn != fbo %d ... fbo->isDirty %d", (*fbo != mFboIn), (fbo->isDirty));
    }

    if (mNodeId != getNodeId()) {
        mNodeId = getNodeId();
        mNeedsUpdate = true;
        //SoDebugError::postInfo("SoXipPingPong", "mNodeId != nodeId");
    }

    if (mNeedsUpdate)
    {
        if (glIsFramebufferEXT(mFboIn.fboHandle) && mFboIn.colorStorage != GL_TEXTURE_3D)
        {
            if (mIsAllocated)
                deallocate();

            // Update setup
            mFboOut = mFboIn;
            mFboOut.fboHandle = 0;
            mNumAttachments = mFboOut.numColorAttachments;

            if (mFboOut.depthStorage == GL_TEXTURE_2D) {
                // Reserve a unit for setting up the fbo textures
                GLuint unit = SoXipMultiTextureElement::getFreeUnit(action->getState());
                SoXipMultiTextureElement::setUnit(action->getState(), unit);
                SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, 0);
            }

            int currUnit = SoXipMultiTextureElement::getCurrentUnit(action->getState());
            int freeUnit = SoXipMultiTextureElement::getFreeUnit(action->getState());
            SoXipMultiTextureElement::setUnit(action->getState(), freeUnit);

            allocate(action);
            assignPingPongUnits(action);
            syncHandleOutput();
            syncUnitOutput();

            SoXipMultiTextureElement::setUnit(action->getState(), currUnit);
        }
        else
        {
            mFboOut = mFboIn;
            if (mFboIn.colorStorage == GL_TEXTURE_3D)
                SoDebugError::postWarning("SoXipPingPong",
                    "PingPong not supported for 3D targets");
            else
                SoDebugError::postWarning("SoXipPingPong",
                    "Can't enable pingpong without valid and bound fbo %d", fbo->fboHandle);
        }

        mFboOut.isDirty = true;
        mNeedsUpdate = false;
    }
    else
        mFboOut.isDirty = false;

    // Upload to element
    if (glIsFramebufferEXT(mFboOut.fboHandle) && mFboIn.colorStorage != GL_TEXTURE_3D)
        SoXipFboElement::setPingPong(action->getState(), this, mFboOut, mPingPongUnits);
}

void SoXipPingPong::sensorOutCB(void *usr, SoSensor *sensor) {
    SoXipPingPong * thisObj = reinterpret_cast<SoXipPingPong *>(usr);
    thisObj->syncHandleOutput();
    thisObj->syncUnitOutput();
}
