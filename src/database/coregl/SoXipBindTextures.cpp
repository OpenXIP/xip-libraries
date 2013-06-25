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

#include "SoXipBindTextures.h"
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

//#include <xip/inventor/coregl/FramebufferObject.h>
//#include <xip/inventor/coregl/FramebufferObject.h>
//#include <xip/inventor/coregl/SoXipFboElement.h>
//#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>

const GLenum SoXipBindTextures::avaliableColorTargets[16] = 
        { GL_COLOR_ATTACHMENT0_EXT,  GL_COLOR_ATTACHMENT1_EXT,
          GL_COLOR_ATTACHMENT2_EXT,  GL_COLOR_ATTACHMENT3_EXT,
          GL_COLOR_ATTACHMENT4_EXT,  GL_COLOR_ATTACHMENT5_EXT,
          GL_COLOR_ATTACHMENT6_EXT,  GL_COLOR_ATTACHMENT7_EXT,
          GL_COLOR_ATTACHMENT8_EXT,  GL_COLOR_ATTACHMENT9_EXT,
          GL_COLOR_ATTACHMENT10_EXT, GL_COLOR_ATTACHMENT11_EXT,
          GL_COLOR_ATTACHMENT12_EXT, GL_COLOR_ATTACHMENT13_EXT,
          GL_COLOR_ATTACHMENT14_EXT, GL_COLOR_ATTACHMENT15_EXT };

SO_NODE_SOURCE(SoXipBindTextures);


/**
 *  Constructor.
 */
SoXipBindTextures::SoXipBindTextures()
{
    SO_NODE_CONSTRUCTOR(SoXipBindTextures);

	SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_1D);
	SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_2D);
	SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_3D);
	SO_NODE_SET_SF_ENUM_TYPE(textureDimension, TextureDimension);

    // add input fields
    SO_NODE_ADD_FIELD(textureDimension,  (TEXTURE_2D));
    SO_NODE_ADD_FIELD(attachmentHandles, (0));

    // add output fields
    SO_NODE_ADD_FIELD(texture0Output, (-1));
    SO_NODE_ADD_FIELD(texture1Output, (-1));
    SO_NODE_ADD_FIELD(texture2Output, (-1));
    SO_NODE_ADD_FIELD(texture3Output, (-1));
    SO_NODE_ADD_FIELD(texture4Output, (-1));
    SO_NODE_ADD_FIELD(texture5Output, (-1));
    SO_NODE_ADD_FIELD(texture6Output, (-1));
    SO_NODE_ADD_FIELD(texture7Output, (-1));

    //attachmentHandles.deleteValues(0);
    mNumTextures = attachmentHandles.getNum();

    for (int i = 0; i < 16; i++) {
        mTexHandles[i] = 0;
        mTexUnits[i] = 0;
    }

    mNodeId = 0;
    mNeedsSync = true;
}

/**
 *  Destructor.
 */
SoXipBindTextures::~SoXipBindTextures()
{
}


/**
 *  Class initiation.
 */
void SoXipBindTextures::initClass()
{
    SO_NODE_INIT_CLASS(SoXipBindTextures, SoNode, "Node");
	SO_ENABLE(SoGLRenderAction, SoXipMultiTextureElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);

//    SO_ENABLE(SoGLRenderAction, SoXipFboElement);
//    SO_ENABLE(SoGLRenderAction, SoXipDrawBuffersElement);
}


/**
 *  Updates internal handles according to input.
 */
void SoXipBindTextures::assignTextures(SoGLRenderAction* action)
{
    GLuint unit     = 0;
    GLuint texture  = 0;

    for (int i = 0; i < mNumTextures; i++)
    {
        if (mTexHandles[i] != attachmentHandles[i])
            mTexHandles[i] = attachmentHandles[i];
        if (mTexHandles[i] != 0 && !glIsTexture(mTexHandles[i]))
            SoDebugError::postWarning("SoXipFboUseTex", "Supplied handle is not a valid texture (could be a renderbuffer)");
    }

    for (int i = mNumTextures; i < 16; i++)
        mTexHandles[i] = 0;
}


/**
 *  Binds internal handles to texture units.
 */
void SoXipBindTextures::bindTextures(SoGLRenderAction* action)
{
    GLuint unit = 0;
    for (int i = 0; i < mNumTextures; i++)
    {
        if (glIsTexture(mTexHandles[i])) {
            unit = SoXipMultiTextureElement::getFreeUnit(action->getState());
            SoXipMultiTextureElement::setUnit(action->getState(), unit);
            SoXipMultiTextureElement::bindTexture(action->getState(), textureDimension.getValue(), mTexHandles[i]);
            if (mTexUnits[i] != unit) {
                mTexUnits[i] = unit;
                mNeedsSync = true;
            }
        }
        else {
            mTexUnits[i] = 0;
            mNeedsSync = true;
        }
    }

    for (int i = mNumTextures; i < 16; i++)
        mTexUnits[i] = 0;
}

/**
 *  Synchronizing newly bound handles with output unit fields.
 */
void SoXipBindTextures::syncOutput()
{
    if (mNeedsSync)
    {
        if (texture0Output.getValue() != mTexUnits[0])
            texture0Output.setValue(mTexUnits[0]);
        if (texture1Output.getValue() != mTexUnits[1])
            texture1Output.setValue(mTexUnits[1]);
        if (texture2Output.getValue() != mTexUnits[2])
            texture2Output.setValue(mTexUnits[2]);
        if (texture3Output.getValue() != mTexUnits[3])
            texture3Output.setValue(mTexUnits[3]);
        if (texture4Output.getValue() != mTexUnits[4])
            texture4Output.setValue(mTexUnits[4]);
        if (texture5Output.getValue() != mTexUnits[5])
            texture5Output.setValue(mTexUnits[5]);
        if (texture6Output.getValue() != mTexUnits[6])
            texture6Output.setValue(mTexUnits[6]);
        if (texture7Output.getValue() != mTexUnits[7])
            texture7Output.setValue(mTexUnits[7]);

        mNodeId = getNodeId();
        mNeedsSync = false;
    }
}


/**
 *  GLRender, updates and checks handles if necessary.
 *  If node id has changed (ie, if anything in the node has changed)
 *  an update is performed, otherwise it binds the stored handles to units.
 */
void SoXipBindTextures::GLRender(SoGLRenderAction* action)
{
    if (attachmentHandles.getNum() > 16) {
        SoDebugError::post("SoXipBindTextures", "cant process more than 16 handles");
        return;
    }

    bool dbgPrint = false;
    if (mNodeId != getNodeId())
    {
        mNodeId = getNodeId();

        // Check if any handles have changed
        bool handlesChanged = false;
        for (int i = 0; i < attachmentHandles.getNum(); i++) {
            if (mTexHandles[i] != attachmentHandles[i]) {
                handlesChanged = true;
            }
        }

        // If something has changed we process
        if (mNumTextures != attachmentHandles.getNum() || handlesChanged)
        {
            mNumTextures = attachmentHandles.getNum();
	        assignTextures(action);
            dbgPrint = true;
        }
    }

    bindTextures(action);
    syncOutput();

#ifdef a_DEBUG
    if (dbgPrint)
    {
        dbgPrint = false;
        // Debug printout
        FboSetup * fbo = SoXipFboElement::getActive(action->getState(), this);
        int col = fbo->numColorAttachments;
        int dep = fbo->numDepthAttachments;
        SoDebugError::postInfo("SoXipBindTextures", "(fbo %d %d %d) binding %d %d %d on %d %d %d",
            fbo->fboHandle, col, dep, mTexHandles[0], mTexHandles[1], mTexHandles[2],
                                      mTexUnits[0],   mTexUnits[1],   mTexUnits[2]);
    }
#endif
}
