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


#include "SoXipBindTextures.h"
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>


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

    // add input fields
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
    mNeedsUpdate = true;
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
            SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, mTexHandles[i]);
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
            bindTextures(action);
            syncOutput();
            mNeedsUpdate = false;
            mNeedsSync = true;
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
