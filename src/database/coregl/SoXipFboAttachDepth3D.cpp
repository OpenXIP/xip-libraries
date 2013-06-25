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
#include <xip/system/GL/gl.h>
#include "SoXipFboAttachDepth3D.h"
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>

SO_NODE_SOURCE(SoXipFboAttachDepth3D);

SoXipFboAttachDepth3D::SoXipFboAttachDepth3D()
{
	SO_NODE_CONSTRUCTOR(SoXipFboAttachDepth3D);
    
	SO_NODE_ADD_FIELD(sizeX, (256));
    SO_NODE_ADD_FIELD(sizeY, (256));
    SO_NODE_ADD_FIELD(sizeZ, (256));

    SO_NODE_ADD_FIELD(bufferStorage, (TEXTURE));
	SO_NODE_ADD_FIELD(internalFormat, (DEPTH_COMPONENT24));
	SO_NODE_ADD_FIELD(wrap, (CLAMP_TO_BORDER));
	SO_NODE_ADD_FIELD(filter, (NEAREST));

	SO_NODE_ADD_FIELD(handleOutput, (0));

	SO_NODE_DEFINE_ENUM_VALUE(BufferStorage, TEXTURE);
	SO_NODE_DEFINE_ENUM_VALUE(BufferStorage, RENDERBUFFER);
	SO_NODE_SET_SF_ENUM_TYPE(bufferStorage, BufferStorage);

	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, DEPTH_COMPONENT16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, DEPTH_COMPONENT24);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, DEPTH_COMPONENT32);
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

    mHandle = 0;
    mNodeId = 0;

    mFboIn.clear();
    mFboOut.clear();
}

/**
 *  Destructor.
 */
SoXipFboAttachDepth3D::~SoXipFboAttachDepth3D()
{
    if (mIsAllocated)
        deallocate();
    delete mSensorOut;
}

/**
 *  Class initiator.
 */
void SoXipFboAttachDepth3D::initClass() {
	SO_NODE_INIT_CLASS(SoXipFboAttachDepth3D, SoNode, "SoNode");

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipDrawBuffersElement);
    SO_ENABLE(SoGLRenderAction, SoXipFboElement);
}



/**
 *  Run a check and output any errors.
 */
bool SoXipFboAttachDepth3D::checkFramebufferStatus()
{
    bool isOk = false;
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            isOk = true;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            SoDebugError::post("SoXipFboAttachDepth3D", "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            SoDebugError::post("SoXipFboAttachDepth3D", "GL_FRAMEBUFFER_UNSUPPORTED_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            SoDebugError::post("SoXipFboAttachDepth3D", "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            SoDebugError::post("SoXipFboAttachDepth3D", "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            SoDebugError::post("SoXipFboAttachDepth3D", "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            SoDebugError::post("SoXipFboAttachDepth3D", "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            SoDebugError::post("SoXipFboAttachDepth3D", "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT");
            break;
        default:
            SoDebugError::post("SoXipFboAttachDepth3D", "UNKNWON frambuffer fault");
    }
    return isOk;
} 


/**
 *  Replacing existing color attachments with new user defined ones.
 */
void SoXipFboAttachDepth3D::allocate()
{
	// glEnable(GL_TEXTURE_3D);	

	if (bufferStorage.getValue() == TEXTURE)
    {
        // Generate textures
        glGenTextures(1, &mHandle);
        glBindTexture(GL_TEXTURE_3D, mHandle);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, mFboOut.depthWrap);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, mFboOut.depthWrap);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, mFboOut.depthFilter);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, mFboOut.depthFilter);
#if 1
        glTexImage3D(GL_TEXTURE_3D, 0, mFboOut.internalDepthFormat,
            sizeX.getValue(), sizeY.getValue(), sizeZ.getValue(),
            0, mFboOut.depthFormat, GL_UNSIGNED_BYTE, NULL);
#else
        glTexImage2D(GL_TEXTURE_3D, 0, mFboOut.internalDepthFormat, mFboOut.width, mFboOut.height,
            0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
#endif
	    glBindTexture(GL_TEXTURE_3D, 0);
	    // glDisable(GL_TEXTURE_3D);
    }
    else if (bufferStorage.getValue() == RENDERBUFFER)
    {
        // Generate renderbuffers
        glGenRenderbuffersEXT(1, &mHandle);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mHandle);
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, mFboOut.internalDepthFormat, mFboOut.width, mFboOut.height);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
    }

    mIsAllocated = true;
}

/**
 *  Deallocation of textures and renderbuffers.
 */
void SoXipFboAttachDepth3D::deallocate()
{
    if (mFboOut.colorStorage == TEXTURE)
        glDeleteTextures(1, &mHandle);
    else if (mFboOut.colorStorage == RENDERBUFFER)
        glDeleteRenderbuffersEXT(1, &mHandle);

    mHandle = 0;
    mIsAllocated = false;
}



/**
 *  Synchronize output.
 *  Field kept as multi field due to compatability with color version
 *  and UseTextures node.
 */
void SoXipFboAttachDepth3D::syncOutput()
{
    bool outputDirty = false;

    // Resize if neccesary
    if (handleOutput.getNum() < 1)
    {
        handleOutput.set1Value(0, 0);
        outputDirty = true;
    }

    // Update entries if changed
    if (handleOutput[0] != static_cast<int>(mHandle))
    {
        //SoDebugError::post("", "handle mismatch %d (%d %d)", i, handleOutput[i], mHandles[i]);
        handleOutput.set1Value(0, static_cast<int>(mHandle));
        outputDirty = true;
    }

    // Remove absolete entries
    if (handleOutput.getNum() > 1)
    {
        //SoDebugError::post("", "length mismatch");
        handleOutput.deleteValues(1);
        outputDirty = true;
    }

    mNodeId = getNodeId();
}


/**
 *  Sets up the buffers, saves the state and pushes the effected attributes.
 *  Allocates buffer if need be and performs most functionallity.
 */
void SoXipFboAttachDepth3D::GLRender(SoGLRenderAction* action)
{
    FboSetup * fbo = SoXipFboElement::getActive(action->getState(), this);

    if (!fbo->isOpen)
        return;

    if (*fbo != mFboIn || fbo->isDirty)
    {
        if (fbo->numDepthAttachments != 0)
            SoDebugError::postInfo("SoXipFboAttachDepth3D",
                "Replacing existing depth attachment, please uncheck depth checkbox in Fbo node");
        mFboIn = *fbo;
        mFboIn.isDirty = false;
        mNeedsUpdate = true;
        //SoDebugError::postInfo("SoXipFboAttachDepth3D", "mFboIn != fbo");
    }

    if (mNodeId != getNodeId())
    {
        mNodeId = getNodeId();
        mFboIn = *fbo;
        mNeedsUpdate = true;
        //SoDebugError::postInfo("SoXipFboAttachDepth3D", "mNodeId != nodeId");
    }

    if (mNeedsUpdate)
    {
        if (mIsAllocated)
            deallocate();

        // Update setup according to fields
        mFboOut = mFboIn;
        mFboOut.numDepthAttachments = 1;
        mFboOut.depthStorage = bufferStorage.getValue();
        mFboOut.internalDepthFormat = internalFormat.getValue();
        mFboOut.depthWrap = wrap.getValue();
        mFboOut.depthFilter = filter.getValue();

        if (mFboOut.depthStorage == TEXTURE)
        {
            // Reserve a unit for setting up the fbo textures
            GLuint unit = SoXipMultiTextureElement::getFreeUnit(action->getState());
            SoXipMultiTextureElement::setUnit(action->getState(), unit);
            SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_3D, mHandle);
        }

        allocate();
        syncOutput();

        mFboOut.isDirty = true;
        mNeedsUpdate = false;
    }
    else
        mFboOut.isDirty = false;

    // Update settings
    mFboOut.numDepthAttachments = 1;
    mFboOut.depthHandle = mHandle;
    mFboOut.hasModDepth = true;

    // Upload to element
    SoXipFboElement::set(action->getState(), this, mFboOut);
}

void SoXipFboAttachDepth3D::sensorOutCB(void *usr, SoSensor *sensor) {
    SoXipFboAttachDepth3D * thisObj = reinterpret_cast<SoXipFboAttachDepth3D *>(usr);
    thisObj->syncOutput();
}


