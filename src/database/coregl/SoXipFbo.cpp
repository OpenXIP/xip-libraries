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
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include "SoXipFbo.h"
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>


const GLenum SoXipFbo::avaliableColorTargets[16] = 
        { GL_COLOR_ATTACHMENT0_EXT,  GL_COLOR_ATTACHMENT1_EXT,
          GL_COLOR_ATTACHMENT2_EXT,  GL_COLOR_ATTACHMENT3_EXT,
          GL_COLOR_ATTACHMENT4_EXT,  GL_COLOR_ATTACHMENT5_EXT,
          GL_COLOR_ATTACHMENT6_EXT,  GL_COLOR_ATTACHMENT7_EXT,
          GL_COLOR_ATTACHMENT8_EXT,  GL_COLOR_ATTACHMENT9_EXT,
          GL_COLOR_ATTACHMENT10_EXT, GL_COLOR_ATTACHMENT11_EXT,
          GL_COLOR_ATTACHMENT12_EXT, GL_COLOR_ATTACHMENT13_EXT,
          GL_COLOR_ATTACHMENT14_EXT, GL_COLOR_ATTACHMENT15_EXT };

SO_NODE_SOURCE(SoXipFbo);

SoXipFbo::SoXipFbo() {
	SO_NODE_CONSTRUCTOR(SoXipFbo);

	SO_NODE_ADD_FIELD(width, (0));
	SO_NODE_ADD_FIELD(height, (0));
	SO_NODE_ADD_FIELD(autoSize,  (false));

	SO_NODE_ADD_FIELD(colorAttachments, (0));
	SO_NODE_ADD_FIELD(colorFormat, (RGBA));
	SO_NODE_ADD_FIELD(colorInternal, (RGBA8));

    SO_NODE_ADD_FIELD(useDepthBuffer, (true));

    SO_NODE_ADD_FIELD(colorHandlesOutput, (0));
    //SO_NODE_ADD_FIELD(outFboSetup, (0));

	SO_NODE_DEFINE_ENUM_VALUE(Format, ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, INTENSITY);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGB);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGBA);
	SO_NODE_SET_SF_ENUM_TYPE(colorFormat, Format);

	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, ALPHA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, ALPHA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, ALPHA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, ALPHA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, ALPHA32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE4_ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE6_ALPHA2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE8_ALPHA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE12_ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE12_ALPHA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE16_ALPHA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE_ALPHA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, LUMINANCE_ALPHA32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, INTENSITY4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, INTENSITY8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, INTENSITY12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, INTENSITY16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, INTENSITY16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, INTENSITY32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, R3_G3_B2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB5);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB10);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGBA2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGBA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB5_A1);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGBA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGB10_A2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGBA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGBA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGBA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalColorFormat, RGBA32F_ARB);
	SO_NODE_SET_SF_ENUM_TYPE(colorInternal, InternalColorFormat);

    SoField* fields[] = { &colorFormat, &colorInternal, &useDepthBuffer };
	SoField* fieldsOut[] = { &colorHandlesOutput };

    // Attach input sensor to input fields
	mNumFields = sizeof(fields) / sizeof(fields[0]);
	mSensors = new SoFieldSensor*[mNumFields];
	for (int i = 0; i < mNumFields; i++) {
		mSensors[i] = new SoFieldSensor(sensorCB, this);
		mSensors[i]->attach(fields[i]);
	}

    // Attach output sensor to output fields
	mNumFieldsOut = sizeof(fieldsOut) / sizeof(fieldsOut[0]);
	mSensorsOut = new SoFieldSensor*[mNumFieldsOut];
	for (int i = 0; i < mNumFieldsOut; i++) {
		mSensorsOut[i] = new SoFieldSensor(sensorOutCB, this);
		mSensorsOut[i]->attach(fieldsOut[i]);
	}

    mColorAttachmentsSensor = new SoFieldSensor(sensorCB, this);
    mColorAttachmentsSensor->attach(&colorAttachments);

    mNumColorHandles = 0;
    for (int i = 0; i < 16; i++)
        mColorHandles[i] = 0;
    mDepthHandle = 0;

    mMaxBuffers = 0;
    mErrorInSetup = false;
	mNeedsUpdate = true;
	mIsAllocated = false;
    mIsColorsAllocated = false;
    mIsDepthAllocated = false;

    mDefaultWrap = GL_CLAMP;
    mDefaultFilter = GL_LINEAR;
    mDefaultDepthFormat = GL_DEPTH_COMPONENT24;
}

/**
 *  Destructor.
 */
SoXipFbo::~SoXipFbo() {
	for (int i = 0; i < mNumFields; i++) {
		delete mSensors[i];
	}
	delete [] mSensors;

	for (int i = 0; i < mNumFieldsOut; i++) {
		delete mSensorsOut[i];
	}
	delete [] mSensorsOut;

	if (mIsAllocated)
		deallocate();

    delete mColorAttachmentsSensor;
}

/**
 *  Class initiator.
 */
void SoXipFbo::initClass() {
	SO_NODE_INIT_CLASS(SoXipFbo, SoGroup, "SoGroup");

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipFboElement);
    SO_ENABLE(SoGLRenderAction, SoXipDrawBuffersElement);
}


/**
 *  Run a check and output any errors.
 */
bool SoXipFbo::checkFramebufferStatus() {
    bool isOk = false;
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            isOk = true;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            SoDebugError::post("SoXipFbo", "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            SoDebugError::post("SoXipFbo", "GL_FRAMEBUFFER_UNSUPPORTED_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            //SoDebugError::post("SoXipFbo", "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT");
            SoDebugError::post("SoXipFbo", "The fbo will be incomplete without color attachments");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            SoDebugError::post("SoXipFbo", "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            SoDebugError::post("SoXipFbo", "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            //SoDebugError::post("SoXipFbo", "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT");
            if (!mFboOut.numColorAttachments)
                SoDebugError::post("SoXipFbo", "The fbo will be incomplete without color attachments");
            SoDebugError::post("SoXipFbo", "One or more render targets have no attached buffer(s)");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            SoDebugError::post("SoXipFbo", "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT");
            break;
        default:
            SoDebugError::post("SoXipFbo", "UNKNWON frambuffer fault");
    }

    return isOk;
} 


/**
 *  Clamp attachment number field between 0 and context maximum.
 *  Max is extracted from context via glGet with GL_MAX_COLOR_ATTACHMENTS
 */
void SoXipFbo::checkMaxNumBuffers()
{
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &mMaxBuffers);

    int val = colorAttachments.getValue();
    int max = mMaxBuffers;
    if (val < 0 || val > max) {
        val = (val < 0) ? 0 : (val > max) ? max : val;
        colorAttachments.setValue(val);
        SoDebugError::postInfo("SoXipDBO", "Valid range of attachments are [0,%d]", max);
    }
}


/**
 *  Allocates and sets up the Fbo.
 *  @see allocateInternalColors()
 *  @see allocateInternalDepth()
 */
void SoXipFbo::allocateFbo()
{
    glGenFramebuffersEXT(1, &mFboIn.fboHandle);
    mIsAllocated = true;
    mFboIn.width = width.getValue();
    mFboIn.height = height.getValue();
    mFboIn.numColorAttachments = colorAttachments.getValue();
    mFboIn.numDepthAttachments = (useDepthBuffer.getValue()) ? 1 : 0;
    mFboIn.colorStorage = GL_TEXTURE_2D;
    mFboIn.depthStorage = GL_RENDERBUFFER_EXT;
    mFboIn.internalColorFormat = colorInternal.getValue();
    mFboIn.internalDepthFormat = GL_DEPTH_COMPONENT24;
    mFboIn.colorFormat = colorFormat.getValue();
    mFboIn.colorWrap = GL_CLAMP;
    mFboIn.colorFilter = GL_LINEAR;
    mFboIn.hasModColors = false;
    mFboIn.hasModDepth = false;
    mFboIn.isComplete = false;
    mFboIn.isDirty = true;
}


/**
 *  Creates color attachment(s).
 *  Allocates only, the binding/attaching takes place in elsewhere.
 *  @see allocateInternalDepth()
 *  @see allocateFbo()
 */
void SoXipFbo::allocateInternalColors()
{
    if (mFboOut.numColorAttachments)
    {
        glGenTextures(mFboOut.numColorAttachments, mFboOut.colorHandles);
        //SoDebugError::postInfo("SoXipFbo", "Allocated internal colors");
    }

    for (unsigned int i = mFboOut.numColorAttachments; i < 16; i++)
        mFboOut.colorHandles[i] = 0;

    for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++)
    {
        glBindTexture(GL_TEXTURE_2D, mFboOut.colorHandles[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mFboOut.colorWrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mFboOut.colorWrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFboOut.colorFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFboOut.colorFilter);
        glTexImage2D(GL_TEXTURE_2D, 0, mFboOut.internalColorFormat, mFboOut.width, mFboOut.height,
            0, mFboOut.colorFormat, GL_UNSIGNED_BYTE, NULL);
    }
	glBindTexture(GL_TEXTURE_2D, 0);

    for (int i = 0; i < 16; i++)
        mColorHandles[i] = mFboOut.colorHandles[i];

    mNumColorHandles = mFboOut.numColorAttachments;
    mIsColorsAllocated = true;
}



/**
 *  Creates depth attachment.
 *  Allocates only, the binding/attaching takes place elsewhere.
 *  @see allocateInternalColors()
 *  @see allocateFbo()
 */
void SoXipFbo::allocateInternalDepth()
{
    if (mFboOut.numDepthAttachments)
    {
        glGenRenderbuffersEXT(mFboOut.numDepthAttachments, &mFboOut.depthHandle);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mFboOut.depthHandle);
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, mFboOut.internalDepthFormat, mFboOut.width, mFboOut.height);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
        //SoDebugError::postInfo("SoXipFbo", "Allocated internal depth");
    }
    else
        mFboOut.depthHandle = 0;

    mDepthHandle = mFboOut.depthHandle;
    mIsDepthAllocated = true;
}


/**
 *  Deallocation of a internal color buffers.
 */
void SoXipFbo::deallocateInternalColors()
{
    if (mNumColorHandles)
    {
        glDeleteTextures(mNumColorHandles, mColorHandles);
        //SoDebugError::postInfo("SoXipFbo", "Deallocated internal colors");
    }
    
    for (int i = 0; i < 16; i++)
		mColorHandles[i] = 0;
    mNumColorHandles = 0;
    mIsColorsAllocated = false;
}

/**
 *  Deallocation of internal depth buffer.
 */
void SoXipFbo::deallocateInternalDepth()
{
    if (mDepthHandle)
    {
        glDeleteRenderbuffersEXT(1, &mDepthHandle);
        //SoDebugError::postInfo("SoXipFbo", "Deallocated internal depth");
    }

    mDepthHandle = 0;
    mIsDepthAllocated = false;
}



/**
 *  Full deallocation.
 */
void SoXipFbo::deallocate()
{
	glDeleteFramebuffersEXT(1, &mFboOut.fboHandle);
    if (mIsColorsAllocated)
        deallocateInternalColors();
    if (mIsDepthAllocated)
        deallocateInternalDepth();

    mFboOut.fboHandle = 0;
    mNumColorHandles = 0;
    for (int i = 0; i < 16; i++)
		mColorHandles[i] = 0;
    mDepthHandle = 0;

    mIsColorsAllocated = false;
    mIsDepthAllocated = false;
	mIsAllocated = false;
}



/**
 *  AttachColors.
 */
void SoXipFbo::attachColors()
{
    // Attach colors
    if (mFboOut.colorStorage == GL_TEXTURE_2D)
    {
        for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++)
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, GL_TEXTURE_2D, mFboOut.colorHandles[i], 0);
        for (unsigned int i = mFboOut.numColorAttachments; i < (unsigned int)mMaxBuffers; i++)
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, GL_TEXTURE_2D, 0, 0);
        //SoDebugError::postInfo("SoXipFbo", "Attaching 2D color targets %d %d", mFboOut.colorHandles[0], mFboOut.colorHandles[1]);
    }
    else if (mFboOut.colorStorage == GL_TEXTURE_3D)
    {
        for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++)
            glFramebufferTextureEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, mFboOut.colorHandles[i], 0);
        for (unsigned int i = mFboOut.numColorAttachments; i < (unsigned int)mMaxBuffers; i++)
            glFramebufferTextureEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, 0, 0);
        //SoDebugError::postInfo("SoXipFbo", "Attaching 3D color targets %d %d", mFboOut.colorHandles[0], mFboOut.colorHandles[1]);
    }
    else if (mFboOut.colorStorage == GL_RENDERBUFFER_EXT)
    {
        for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++)
            glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, GL_RENDERBUFFER_EXT, mFboOut.colorHandles[i]);
        for (unsigned int i = mFboOut.numColorAttachments; i < (unsigned int)mMaxBuffers; i++)
            glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, GL_RENDERBUFFER_EXT, 0);
    }
}

/**
 *  Deallocation of a buffer.
 */
void SoXipFbo::attachDepth()
{
    // Attach new depth buffer
    if (mFboOut.depthStorage == GL_TEXTURE_2D)
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, mFboOut.depthHandle, 0);
	else if (mFboOut.depthStorage == GL_TEXTURE_3D)
		glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_3D, mFboOut.depthHandle, 0, 0);
    else if (mFboOut.depthStorage == GL_RENDERBUFFER_EXT)
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mFboOut.depthHandle);
}


/**
 *  Synchronize the output field with the attachment handles.
 */
void SoXipFbo::syncOutputHandles()
{
    bool outputDirty = false;
    
    if (!mColorHandles || mFboOut.numColorAttachments > 16)
        SoDebugError::post("SoXipFbo", "invalid pointer or more than 16 handles");
    else {
        // Expand list by padding with zeros if to short
        if (colorHandlesOutput.getNum() < (int)mFboOut.numColorAttachments) {
            for (int i = colorHandlesOutput.getNum(); i < (int)mFboOut.numColorAttachments; i++) {
                colorHandlesOutput.set1Value(i, 0);
                outputDirty = true;
            }
        }

        // Update entries if changed
        for (unsigned int i = 0; i < mFboOut.numColorAttachments; i++) {
            if (colorHandlesOutput[i] != mColorHandles[i]) {
                colorHandlesOutput.set1Value(i, static_cast<int>(mColorHandles[i]));
                outputDirty = true;
            }
        }

        // Remove absolete entries
        if (colorHandlesOutput.getNum() > (int)mFboOut.numColorAttachments) {
            colorHandlesOutput.deleteValues(mFboOut.numColorAttachments);
            outputDirty = true;
        }
    }
}

/**
 *  Process any change in color setup.
 *  The clauses could cause the attachments to be bound every frame
 *  but since we only end up in this function when something has
 *  changed this wount happen.
 */
void SoXipFbo::processColorMods()
{
    if (mFboMod.hasModColors)
    {
        if (mIsColorsAllocated)
            deallocateInternalColors();
        attachColors();
        syncOutputHandles();
        //SoDebugError::postInfo("SoXipFbo", "Attached external colors");
    }
    else if (!mFboMod.hasModColors)
    {
        if (!mIsColorsAllocated)
        {
            allocateInternalColors();
            attachColors();
            syncOutputHandles();
            //SoDebugError::postInfo("SoXipFbo", "Attached internal colors");
        }
    }
}


/**
 *  Process any change in depth setup.
 *  The clauses could cause the attachments to be bound every frame
 *  but since we only end up in this function when something has
 *  changed this wount happen.
 */
void SoXipFbo::processDepthMods()
{
    if (mFboMod.hasModDepth)
    {
        if (mIsDepthAllocated)
            deallocateInternalDepth();
        attachDepth();
        //SoDebugError::postInfo("SoXipFbo", "Attached external depth");
    }
    else if (!mFboMod.hasModDepth)
    {
        if (!mIsDepthAllocated)
        {
            allocateInternalDepth();
            attachDepth();
            //SoDebugError::postInfo("SoXipFbo", "Attached internal depth");
        }
    }
}

/**
 *  Sets up and binds the FBO.
 *  1: Set element according to fields.
 *  2: Let children manipulate setup.
 *  3: Allocate/deallocate if need be.
 *  4: Set element according to finished Fbo
 */
void SoXipFbo::GLRender(SoGLRenderAction* action)
{
    //SoDebugError::postInfo(__FUNCTION__, "(1) in mod out (%d %d %d)", mFboIn.isDirty, mFboMod.isDirty, mFboOut.isDirty);

    if (autoSize.getValue()) {
		const SbVec2s &viewportSize = action->getViewportRegion().getViewportSizePixels();
		if (viewportSize != SbVec2s(width.getValue(), height.getValue())) {
			SoDebugError::postInfo("SoXipFbo", "Autosetting FBO size to (%d, %d)", viewportSize[0], viewportSize[1]);
			width.setValue(viewportSize[0]);
			height.setValue(viewportSize[1]);
			mNeedsUpdate = true;
		}
	}

	// Can't use sensors if fields are changed while traversing tree, such as by parent size changing
    if (width.getValue() != mFboIn.width  || height.getValue() != mFboIn.height)
		mNeedsUpdate = true;

    if (mNeedsUpdate)
    {
        // Check number of buffers
        checkMaxNumBuffers();
        // Dealloc if allocated
        if (mIsAllocated)
            deallocate();

        mFboIn.clear();
        mFboMod.clear();
        mFboOut.clear();

        int currUnit = SoXipMultiTextureElement::getCurrentUnit(action->getState());
        int freeUnit = SoXipMultiTextureElement::getFreeUnit(action->getState());
        SoXipMultiTextureElement::setUnit(action->getState(), freeUnit);

        allocateFbo();

        SoXipMultiTextureElement::setUnit(action->getState(), currUnit);

        //SoDebugError::postInfo(__FUNCTION__, "Allocated new Fbo (dirty)");
        mNeedsUpdate = false;
    }
    else
        mFboIn.isDirty = false;

    mFboMod.isDirty = false;

    //SoDebugError::postInfo(__FUNCTION__, "(2) in mod out (%d %d %d)", mFboIn.isDirty, mFboMod.isDirty, mFboOut.isDirty);

    // Send to element and render children to allow modification
    mFboIn.isOpen = true;
    SoXipFboElement::set(action->getState(), this, mFboIn);
    SoXipFboElement::bind(action->getState(), this);
    if (!glIsFramebufferEXT(mFboIn.fboHandle))
        SoDebugError::postWarning("SoXipFbo", "Something is wrong with the handle");

    //////////
    /// Traverse children
    SoGroup::GLRender(action);
    /// Traverse children
    //////////

    FboSetup * fbo = SoXipFboElement::getActive(action->getState(), this);
    
    // Detect any change in fbo handle
    if (mFboIn.fboHandle != fbo->fboHandle)
        SoDebugError::postWarning("SoXipFbo",
            "Keep Fbo bound during traversal (%d %d)", mFboIn.fboHandle, fbo->fboHandle);

    //SoDebugError::postInfo(__FUNCTION__, "(3) in mod out (%d %d %d)", mFboIn.isDirty, mFboMod.isDirty, mFboOut.isDirty);

    // Reflect changes if change since last run
    if (mFboMod != *fbo)
    {
        mFboMod = *fbo;
        mFboOut = *fbo;

        int currUnit = SoXipMultiTextureElement::getCurrentUnit(action->getState());
        int freeUnit = SoXipMultiTextureElement::getFreeUnit(action->getState());
        SoXipMultiTextureElement::setUnit(action->getState(), freeUnit);

        processColorMods();
        processDepthMods();

        SoXipMultiTextureElement::setUnit(action->getState(), currUnit);

        mErrorInSetup = false;
    }
    else
        mFboOut.isDirty = false;

    //SoDebugError::postInfo(__FUNCTION__, "(4) in mod out (%d %d %d)", mFboIn.isDirty, mFboMod.isDirty, mFboOut.isDirty);

    SoXipDrawBuffersElement::set(action->getState(), this, mFboOut.numColorAttachments);

    // Everything is now attached so test completeness
    if (!mErrorInSetup)
        mFboOut.isComplete = checkFramebufferStatus();
    if (!mFboOut.isComplete)
        mErrorInSetup = true;

    // Activate FBO element (also sets draw buffer element)
    mFboOut.isOpen = false;
    SoXipFboElement::set(action->getState(), this, mFboOut);

    //SoDebugError::postInfo(__FUNCTION__, "(5) in mod out (%d %d %d)", mFboIn.isDirty, mFboMod.isDirty, mFboOut.isDirty);

    if (!mFboOut.isComplete)
        SoXipDrawBuffersElement::set(action->getState(), this, 0);
}

void SoXipFbo::sensorCB(void *usr, SoSensor *sensor) {
	SoXipFbo * thisObj = reinterpret_cast<SoXipFbo *>(usr);
    thisObj->mNeedsUpdate = true;
#if 0
    if (sensor == thisObj->mColorAttachmentsSensor)
        if (thisObj->colorAttachments.getValue() == 0 && thisObj->mIsAllocated)
            SoDebugError::postWarning("SoXipFbo", "Fbo will be Incomplete without any color attachments");
#endif
}

void SoXipFbo::sensorOutCB(void *usr, SoSensor *sensor) {
    SoXipFbo * fbo = reinterpret_cast<SoXipFbo *>(usr);
    fbo->syncOutputHandles();
}


