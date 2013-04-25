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


#include <xip/system/GL/gl.h>
#include "SoXipFboAttachColor3D.h"
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>


SO_NODE_SOURCE(SoXipFboAttachColor3D);

SoXipFboAttachColor3D::SoXipFboAttachColor3D()
{
	SO_NODE_CONSTRUCTOR(SoXipFboAttachColor3D);

	SO_NODE_ADD_FIELD(multiplicity, (1));
    SO_NODE_ADD_FIELD(sizeX, (256));
    SO_NODE_ADD_FIELD(sizeY, (256));
    SO_NODE_ADD_FIELD(sizeZ, (256));
	SO_NODE_ADD_FIELD(format, (RGBA));
	SO_NODE_ADD_FIELD(internalFormat, (RGBA8));
	SO_NODE_ADD_FIELD(wrap, (CLAMP_TO_BORDER));
	SO_NODE_ADD_FIELD(filter, (NEAREST));

	SO_NODE_ADD_FIELD(handleOutput, (0));

	SO_NODE_DEFINE_ENUM_VALUE(Format, ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, INTENSITY);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGB);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGBA);
	SO_NODE_SET_SF_ENUM_TYPE(format, Format);

	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE4_ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE6_ALPHA2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE8_ALPHA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12_ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12_ALPHA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16_ALPHA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE_ALPHA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE_ALPHA32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, R3_G3_B2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB5);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB10);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB5_A1);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB10_A2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA32F_ARB);
	SO_NODE_SET_SF_ENUM_TYPE(internalFormat, InternalFormat);

	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 REPEAT);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,  CLAMP);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 CLAMP_TO_BORDER);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,  CLAMP_TO_EDGE);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 MIRRORED_REPEAT);
	SO_NODE_SET_SF_ENUM_TYPE(wrap, Wrap);

	SO_NODE_DEFINE_ENUM_VALUE(Filter, NEAREST);
	SO_NODE_DEFINE_ENUM_VALUE(Filter, LINEAR);
	SO_NODE_SET_SF_ENUM_TYPE(filter, Filter);

    // Attach output sensor to output fields
	mSensorOut = new SoFieldSensor(sensorOutCB, this);
    mSensorOut->attach(&handleOutput);

    mNumAttachments = 0;
    mMaxAttachments = 0;

    for (int i = 0; i < 16; i++)
        mHandles[i] = 0;

    mFboIn.clear();
    mFboOut.clear();
    mNodeId = 0;
}

/**
 *  Destructor.
 */
SoXipFboAttachColor3D::~SoXipFboAttachColor3D()
{
    if (mIsAllocated)
        deallocate();
    delete mSensorOut;
}

/**
 *  Class initiator.
 */
void SoXipFboAttachColor3D::initClass() {
	SO_NODE_INIT_CLASS(SoXipFboAttachColor3D, SoNode, "SoNode");

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipDrawBuffersElement);
    SO_ENABLE(SoGLRenderAction, SoXipFboElement);
}



/**
 *  Run a check and output any errors.
 */
bool SoXipFboAttachColor3D::checkFramebufferStatus()
{
    bool isOk = false;
    int db[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int tp[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            isOk = true;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            SoDebugError::post("SoXipFboAttachColor3D", "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            SoDebugError::post("SoXipFboAttachColor3D", "GL_FRAMEBUFFER_UNSUPPORTED_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            SoDebugError::post("SoXipFboAttachColor3D", "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            SoDebugError::post("SoXipFboAttachColor3D", "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            SoDebugError::post("SoXipFboAttachColor3D", "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            // Extract buffer setup
            for (int i = 0; i < mMaxAttachments; i++)
                glGetIntegerv(GL_DRAW_BUFFER0 + i, db + i);
            // Extract type setup
            for (int i = 0; i < mMaxAttachments; i++)
                glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,
                                                 GL_COLOR_ATTACHMENT0_EXT + i,
                                                 GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT,
                                                 tp + i);
            // Print
            SoDebugError::post("SoXipFboAttachColor3D", "Incomplete Draw Buffer: draw (%d %d %d %d) type (%d %d %d %d)",
                db[0], db[1], db[2], db[3], tp[0], tp[1], tp[2], tp[3]);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            SoDebugError::post("SoXipFboAttachColor3D", "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT");
            break;
        default:
            SoDebugError::post("SoXipFboAttachColor3D", "UNKNWON frambuffer fault");
    }
    return isOk;
} 



/**
 *  Clamp attachment number field between 0 and context maximum.
 */
void SoXipFboAttachColor3D::checkMaxNumAttachments()
{
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &mMaxAttachments);

    int val = multiplicity.getValue();
    int max = mMaxAttachments;
    if (val < 1 || val > max) {
        val = (val < 1) ? 1 : (val > max) ? max : val;
        multiplicity.setValue(val);
        SoDebugError::postInfo("SoXipDBOAttachColor", "Valid range of attachments are [1,%d]", max);
    }
}


/**
 *  Replacing existing color attachments with new user defined ones.
 */
void SoXipFboAttachColor3D::allocate()
{
    glEnable(GL_TEXTURE_3D);

    // Generate textures
    glGenTextures(mNumAttachments, mHandles);
    for (int i = 0; i < mNumAttachments; i++)
    {
        glBindTexture(GL_TEXTURE_3D, mHandles[i]);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, mFboOut.colorWrap);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, mFboOut.colorWrap);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, mFboOut.colorWrap);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, mFboOut.colorFilter);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, mFboOut.colorFilter);
#if 1
        glTexImage3D(GL_TEXTURE_3D, 0, mFboOut.internalColorFormat,
            sizeX.getValue(), sizeY.getValue(), sizeZ.getValue(),
            0, mFboOut.colorFormat, GL_UNSIGNED_BYTE, NULL);
#else
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB8, sizeX.getValue(), sizeY.getValue(), sizeZ.getValue(),
            0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
#endif
    }
    glBindTexture(GL_TEXTURE_3D, 0);
    glDisable(GL_TEXTURE_3D);

    mIsAllocated = true;
}


/**
 *  Deallocation of textures and renderbuffers.
 */
void SoXipFboAttachColor3D::deallocate()
{
    glDeleteTextures(mNumAttachments, mHandles);

    mNumAttachments = 0;
    for (int i = 0; i < 16; i++)
        mHandles[i] = 0;

    mIsAllocated = false;
}


/**
 *  Frame buffer object allocator.
 *  Allocates and re-allocates FBO's according to user/engine/state variables.
 */
void SoXipFboAttachColor3D::syncOutput()
{
    bool outputDirty = false;
    
    if (!mHandles || mNumAttachments > 16)
        SoDebugError::post("SoXipFbo", "invalid pointer or more than 16 handles");
    else {
        // Expand list by padding with zeros if to short
        if (handleOutput.getNum() < static_cast<int>(mNumAttachments)) {
            for (int i = handleOutput.getNum(); i < mNumAttachments; i++) {
                //SoDebugError::post("", "num mismatch %d (%d %d)", i, handleOutput.getNum(), mNumAttachments);
                handleOutput.set1Value(i, 0);
                outputDirty = true;
            }
        }

        // Update entries if changed
        for (int i = 0; i < mNumAttachments; i++) {
            if (handleOutput[i] != static_cast<int>(mHandles[i])) {
                //SoDebugError::post("", "handle mismatch %d (%d %d)", i, handleOutput[i], mHandles[i]);
                handleOutput.set1Value(i, static_cast<int>(mHandles[i]));
                outputDirty = true;
            }
        }

        // Remove absolete entries
        if (handleOutput.getNum() > static_cast<int>(mNumAttachments)) {
            //SoDebugError::post("", "length mismatch");
            handleOutput.deleteValues(mNumAttachments);
            outputDirty = true;
        }
    }

    mNodeId = getNodeId();
}


/**
 *  Sets up the buffers, saves the state and pushes the effected attributes.
 *  Allocates buffer if need be and performs most functionallity.
 */
void SoXipFboAttachColor3D::GLRender(SoGLRenderAction* action)
{
    FboSetup * fbo = SoXipFboElement::getActive(action->getState(), this);

    if (!fbo->isOpen)
        return;

    if (*fbo != mFboIn || fbo->isDirty)
    {
        if (fbo->numColorAttachments != 0)
            SoDebugError::postInfo("SoXipFboAttachColor3D",
                "Replacing existing color attachments, please set 0 attachments in Fbo node");
        mFboIn = *fbo;
        mFboIn.isDirty = false;
        mNeedsUpdate = true;
        //SoDebugError::postInfo("SoXipFboAttachColor3D", "mFboIn != fbo");
    }

    if (mNodeId != getNodeId()) {
        mNodeId = getNodeId();
        mFboIn = *fbo;
        mNeedsUpdate = true;
        //SoDebugError::postInfo("SoXipFboAttachColor3D", "mNodeId != nodeId");
    }

    if (mNeedsUpdate)
    {
        if (mIsAllocated)
            deallocate();

        checkMaxNumAttachments();

        // Update setup according to fields
        mNumAttachments = multiplicity.getValue();
        mFboOut = mFboIn;
        mFboOut.colorStorage = GL_TEXTURE_3D;
        mFboOut.numColorAttachments = mNumAttachments;
        mFboOut.width = sizeX.getValue();
        mFboOut.height = sizeY.getValue();
        mFboOut.colorFormat = format.getValue();
        mFboOut.internalColorFormat = internalFormat.getValue();
        mFboOut.colorWrap = wrap.getValue();
        mFboOut.colorFilter = filter.getValue();

        // Reserve a unit for setting up the fbo textures
        GLuint unit = SoXipMultiTextureElement::getFreeUnit(action->getState());
        SoXipMultiTextureElement::setUnit(action->getState(), unit);
        SoXipMultiTextureElement::bindTexture(action->getState(), mFboOut.colorStorage, 0);

        allocate();
        syncOutput();

        mFboOut.isDirty = true;
        mNeedsUpdate = false;
    }
    else
        mFboOut.isDirty = false;

    // Update settings
    mFboOut.numColorAttachments = mNumAttachments;
    for (int i = 0; i < mNumAttachments; i++)
        mFboOut.colorHandles[i] = mHandles[i];
    mFboOut.hasModColors = true;

    // Upload to element
    SoXipFboElement::set(action->getState(), this, mFboOut);
}

void SoXipFboAttachColor3D::sensorOutCB(void *usr, SoSensor *sensor) {
    SoXipFboAttachColor3D * thisObj = reinterpret_cast<SoXipFboAttachColor3D *>(usr);
    thisObj->syncOutput();
}
