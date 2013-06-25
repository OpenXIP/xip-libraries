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
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>

#include "SoXipGpuProcessTextureKit.h"

// Safe Field Connection template
template <class SrcType, class DstType>
inline bool connectField(SrcType * srcObj, const char * srcName,
			 DstType * dstObj, const char * dstName)
{
    if (!srcObj || !dstObj)
    {
        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Null pointer for src/dst objects for "
                               "field connection %s.%s -> %s.%s",
                               srcObj ? "src" : "NULL", srcName,
                               dstObj ? "dst" : "NULL", dstName);
        return false;
    }

    SoField * srcField = srcObj->getField(srcName);
    SoField * dstField = dstObj->getField(dstName);

    if (!srcField || !dstField)
    {
        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Null pointer for src/dst field for "
                               "field connection %s (%s) -> %s (%s)",
                               srcName, srcField ? "valid" : "NULL",
                               dstName, dstField ? "valid" : "NULL");
        return false;
    }

    // Returns an SbBool...
    if (!dstField->connectFrom(srcField))
    {
        const char * srcClass = srcObj->getClassTypeId().getName().getString();
        const char * dstClass = dstObj->getClassTypeId().getName().getString();

        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Failed to connect fields %s.%s -> %s.%s",
                               srcClass ? srcClass : "<unknown>", srcName,
                               dstClass ? dstClass : "<unknown>", dstName);
        return false;
    }

    return true;
}


// Safe Field Connection template
template <class DstType>
inline bool connectField(SoField & srcField, const char * srcName,
			 DstType * dstObj, const char * dstName)
{
    if (!dstObj)
    {
        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Null pointer for destination object for "
                               "field connection %s -> %s.%s",
                               srcName, "NULL", dstName);
        return false;
    }

    SoField * dstField = dstObj->getField(dstName);

    if (!dstField)
    {
        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Null pointer for src/dst field for "
                               "field connection %s (%s) -> %s (%s)",
                               srcName, "valid",
                               dstName, dstField ? "valid" : "NULL");
        return false;
    }

    // Returns an SbBool...
    if (!dstField->connectFrom(&srcField))
    {
        const char * dstClass = dstObj->getClassTypeId().getName().getString();

        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Failed to connect fields %s -> %s.%s",
                               srcName, dstClass ? dstClass : "<unknown>", dstName);
        return false;
    }

    return true;
}

// Safe Field Connection template
template <class SrcType>
inline bool connectField(SrcType * srcObj, const char * srcName,
			 SoField & dstField, const char * dstName)
{
    if (!srcObj)
    {
        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Null pointer for src object for "
                               "field connection %s.%s -> %s",
                               "NULL", srcName, dstName);
        return false;
    }

    SoField * srcField = srcObj->getField(srcName);

    if (!srcField)
    {
        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Null pointer for src/dst field for "
                               "field connection %s (%s) -> %s (%s)",
                               srcName, srcField ? "valid" : "NULL",
                               dstName, "valid");
        return false;
    }

    // Returns an SbBool...
    if (!dstField.connectFrom(srcField))
    {
        const char * srcClass = srcObj->getClassTypeId().getName().getString();

        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Failed to connect fields %s.%s -> %s",
                               srcClass ? srcClass : "<unknown>", srcName,
                               dstName);
        return false;
    }

    return true;
}

template <class Type>
inline bool setFieldValue(Type * obj, const char * name, const char * value)
{
    if (!obj)
    {
        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Null pointer for object with "
                               "field \"%s\" and value \"%s\"",
                               name, value);
        return false;
    }

    SoField * field = obj->getField(name);

    if (!field)
    {
        const char * className = obj->getClassTypeId().getName().getString();

        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Field not found for %s.%s",
                               className ? className : "<unknown>", name);
        return false;
    }

    // Returns an SbBool...
    if (!field->set(value))
    {
        const char * className = obj->getClassTypeId().getName().getString();

        SoDebugError::postInfo("SoXipGpuProcessTextureKit",
                               "Failed to set field value %s.%s = %s",
                               className ? className : "<unknown>", name, value);
        return false;
    }
  
    return true;
}


SO_KIT_SOURCE(SoXipGpuProcessTextureKit);
 

void
SoXipGpuProcessTextureKit::initClass()
{
    SO_KIT_INIT_CLASS(SoXipGpuProcessTextureKit, SoBaseKit, "BaseKit");
    // enable Elements 
    SO_ENABLE(SoGLRenderAction, SoXipFboElement);
}


SoXipGpuProcessTextureKit::SoXipGpuProcessTextureKit()
{
    SO_KIT_CONSTRUCTOR(SoXipGpuProcessTextureKit);

    // Set up enumerations for texture model
    SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, AUTO);
    SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_2D);
    SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_3D); 

    // Set up info in enumerated type field
    SO_NODE_SET_SF_ENUM_TYPE(textureDimension, TextureDimension);

    // fields
    SO_NODE_ADD_FIELD(textureDimension, (AUTO));
    SO_NODE_ADD_FIELD(colorHandlesOutput, (0));
    SO_NODE_ADD_FIELD(autoSize, (TRUE));	
    SO_NODE_ADD_FIELD(outputTextureSizeX, (1));
    SO_NODE_ADD_FIELD(outputTextureSizeY, (1));
    SO_NODE_ADD_FIELD(outputTextureSizeZ, (1));
    //SO_NODE_ADD_FIELD(outputTextureSize, (SbVec3f(1, 1, 1)));
    SO_NODE_ADD_FIELD(colorAttachments, (1));
    SO_NODE_ADD_FIELD(detail, (1));
    SO_NODE_ADD_FIELD(useGeomShader, (FALSE));
    SO_NODE_ADD_FIELD(reload, ());
	
    // nodes 
    /*SO_KIT_ADD_CATALOG_ENTRY(partName, partClassName, null, parent, right, public);*/

    SO_KIT_ADD_CATALOG_ENTRY(top, SoSeparator, FALSE, this, \0, TRUE );
    SO_KIT_ADD_CATALOG_ENTRY(iterator, SoXipGpuProcessTexture, FALSE, top, \x0, TRUE );
    SO_KIT_ADD_CATALOG_ENTRY(clearFbo, SoXipClearFbo, FALSE, top, iterator, TRUE);
    SO_KIT_ADD_CATALOG_ENTRY(xipFbo, SoXipFbo, FALSE, top, clearFbo, TRUE);
    SO_KIT_ADD_CATALOG_ENTRY(switchDimension, SoSwitch, FALSE, xipFbo, \x0, TRUE);
    SO_KIT_ADD_CATALOG_ENTRY(attachColor3D, SoXipFboAttachColor3D, FALSE, switchDimension, \x0, TRUE);
	
    SO_KIT_INIT_INSTANCE();

    mNodeId = 0;
    mMode3D = FALSE;
    mChanged = true;
    mConnectionsSet = FALSE;
}


SoXipGpuProcessTextureKit::~SoXipGpuProcessTextureKit()
{
}


void SoXipGpuProcessTextureKit::GLRender(SoGLRenderAction * action)
{
    if (mNodeId != getNodeId()) 
    {
        setupConnections();
        mChanged = FALSE;
    }

    if (mConnectionsSet)
        SoBaseKit::GLRender(action); 

    mNodeId = getNodeId();
}


void SoXipGpuProcessTextureKit::setupConnections()
{	
    // SoXipFbo Node and settings
    SoNode * fboObj = getAnyPart("xipFbo", true);

    if (!fboObj)
    {
        SoDebugError::postInfo(__FUNCTION__, "could not load necessary node SoXipFBO");
        return;
    }

    bool connects =
        connectField(colorAttachments, "colorAttachments", fboObj, "colorAttachments") &
        // connectField(useDepthBuffer, "useDepthBuffer", fboObj, "useDepthBuffer") &
        connectField(outputTextureSizeX, "outputTextureSizeX", fboObj, "width") &
        connectField(outputTextureSizeY, "outputTextureSizeY", fboObj, "height");

    bool setValues =
        setFieldValue(fboObj, "useDepthBuffer", "FALSE") &
        setFieldValue(fboObj, "autoSize", "FALSE");

    if (!connects || !setValues)
    {
        SoDebugError::postInfo(__FUNCTION__, "Failed to connect and/or set fields"
                               "of nodes");
        return;
    }

    // SoXipProcessImage Node + connections
    SoNode * itObj = getAnyPart("iterator", true);
    SoNode * switchObj = getAnyPart("switchDimension", true);

    if (!itObj || !switchObj)
    {
        SoDebugError::postInfo(__FUNCTION__, "could not load necessary nodes "
                               "SoXipGpuProcessTexture or SoSwitch");
        return;
    }

    // setting the texture dimension according to the input texture
    if (textureDimension.getValue() == AUTO)
    {	
        GLint old2DHandle = 0;
        GLint old3DHandle = 0;
        glGetIntegerv(GL_TEXTURE_BINDING_3D, &old3DHandle);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &old2DHandle);

        if (old2DHandle != 0)
        {
            mMode3D = false;
        }
        else if (old3DHandle != 0)
        {
            mMode3D = true;
        }
    }
    else
    {
        connects = connectField(textureDimension, "textureDimension",
                                itObj, "textureDimension");

        if (!connects)
        {
            SoDebugError::postInfo(__FUNCTION__, "Failed to connect and/or set fields"
                                   "of nodes");
            return;
        }
    }

    if (textureDimension.getValue() == TEXTURE_3D || mMode3D)
    {
        mMode3D = true;

        setValues =
            setFieldValue(fboObj, "colorAttachments", "0") &
            setFieldValue(itObj, "textureDimension", "TEXTURE_3D") &
            setFieldValue(switchObj, "whichChild", "0");
    }
    else
    {
        mMode3D = false;

        setValues =
            setFieldValue(itObj, "textureDimension", "TEXTURE_2D") &
            setFieldValue(switchObj, "whichChild", "1");
    }

    if (!setValues)
    {
        SoDebugError::postInfo(__FUNCTION__, "Failed to connect and/or set fields"
                               "of nodes");
        return;
    }

    // setting the size of the output volume for SoXipAttachTexture3D automatically
    if (autoSize.getValue())
    {
        int size[3] = { 0, 0, 0 };
        float scale = detail.getValue();

        if (mMode3D)
        {
            glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_WIDTH, size);
            glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_HEIGHT, size+1);
            glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_DEPTH, size+2);

            size[0] = int(size[0] * scale);
            size[1] = int(size[1] * scale);
            size[2] = int(size[2] * scale);
        }
        else
        {
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, size);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, size+1);

            size[0] = int(size[0] * scale);
            size[1] = int(size[1] * scale);
            size[2] = 1;
        }

        outputTextureSizeX.setValue(size[0]);
        outputTextureSizeY.setValue(size[1]);
        outputTextureSizeZ.setValue(size[2]);
    }

    connects =
        connectField(useGeomShader, "useGeomShader", itObj, "useGeomShader") &
        connectField(reload, "reload", itObj, "reload");

    // SoXipAttachColor3D Node + connections
    SoNode * atObj = getAnyPart("attachColor3D", true);

    if (!atObj)
    {
        SoDebugError::postInfo(__FUNCTION__, "SoXipAttachColor3D Node could not be loaded");
        return;
    }

    if (mMode3D)
    {
        connects &=
            connectField(atObj, "handleOutput", colorHandlesOutput, "colorHandlesOutput") &
            connectField(outputTextureSizeX, "outputTextureSizeX", atObj, "sizeX") &
            connectField(outputTextureSizeY, "outputTextureSizeY", atObj, "sizeY") &
            connectField(outputTextureSizeZ, "outputTextureSizeZ", atObj, "sizeZ") &
            connectField(colorAttachments, "colorAttachments", atObj, "multiplicity");
        
        setValues = setFieldValue(atObj, "filter", "LINEAR");
    }
    else
    {
        connects &=
            connectField(fboObj, "colorHandlesOutput", colorHandlesOutput, "colorHandlesOutput");
        setValues = true;
    }

    if (!setValues || !connects)
    {
        SoDebugError::postInfo(__FUNCTION__, "Failed to connect and/or set fields"
                               "of nodes");
        return;
    }

    // SoXipClearFbo Node
    SoNode * clearObj = getAnyPart("clearFbo", true);

    if (!clearObj)
    {
        SoDebugError::postInfo(__FUNCTION__, "could not load necessary node SoClearFbo");
        return;
    }

    setValues = setFieldValue(clearObj, "clearDepthBuffer", "FALSE");

    if (!setValues)
    {
        SoDebugError::postInfo(__FUNCTION__, "Failed to connect and/or set fields"
                               "of nodes");
        return;
    }

    mConnectionsSet = true;
}


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
