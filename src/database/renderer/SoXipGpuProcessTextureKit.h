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
#ifndef SO_XIP_GPU_PROCESS_TEXTURE_KIT_H
#define SO_XIP_GPU_PROCESS_TEXTURE_KIT_H

//#pragma once  // This is Windows VC specific, and not needed with protection above

#include <xip/system/GL/gl.h>
#include <Inventor/nodekits/SoSeparatorKit.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/errors/SoDebugError.h>

#include <vector>


class SoXipGpuProcessTextureKit: public SoBaseKit
{
    SO_KIT_HEADER(SoXipGpuProcessTextureKit);
    //	Nodes:
    //				    top
    //	       |					|
    //	     xipFbo				iterator
    //	       |
    //	switchDimension
    //	       |
    //	attachColor3D
#if 0 /*CODE REVIEW Stefan Lindholm*/
    SO_KIT_CATALOG_ENTRY_HEADER(top);
    SO_KIT_CATALOG_ENTRY_HEADER(switchDimension);
    SO_KIT_CATALOG_ENTRY_HEADER(ortho);
    SO_KIT_CATALOG_ENTRY_HEADER(xipFbo);
    SO_KIT_CATALOG_ENTRY_HEADER(xipClearFbo);
    SO_KIT_CATALOG_ENTRY_HEADER(iterator);
    SO_KIT_CATALOG_ENTRY_HEADER(attachColor3D);
#else
    SO_KIT_CATALOG_ENTRY_HEADER(top);
    SO_KIT_CATALOG_ENTRY_HEADER(xipFbo);
    SO_KIT_CATALOG_ENTRY_HEADER(switchDimension);
    SO_KIT_CATALOG_ENTRY_HEADER(attachColor3D);
    SO_KIT_CATALOG_ENTRY_HEADER(clearFbo);
    SO_KIT_CATALOG_ENTRY_HEADER(iterator);
#endif

public:

    // Fields:
    SoSFBool		useGeomShader;
    SoSFTrigger		reload;
    SoMFInt32	    colorAttachments;
    SoMFInt32	    colorHandlesOutput;
    SoSFBool	    autoSize;
    //SoSFVec3f		outputTextureSize;
    SoSFShort		outputTextureSizeX;
    SoSFShort		outputTextureSizeY;
    SoSFShort		outputTextureSizeZ;
    SoSFFloat		detail; 
    SoSFEnum		textureDimension;	 

    enum TextureDimension
    {
        TEXTURE_1D = GL_TEXTURE_1D,
        TEXTURE_2D = GL_TEXTURE_2D,
        TEXTURE_3D = GL_TEXTURE_3D,
        AUTO,
    };

    // constructor
    SoXipGpuProcessTextureKit();
    static void		initClass();

private:
    virtual ~SoXipGpuProcessTextureKit();

    int                 mNodeId;
    bool                mConnectionsSet;
    bool                mChanged;
    bool                mMode3D;
#if 0 /*CODE REVIEW Stefan Lindholm*/
    SoFieldSensor *     mTriggerSensor;
#endif

protected:

    virtual void GLRender(SoGLRenderAction * action);
    void setupConnections();
    void setupFramebufferObject();
    void updateFields();

#if 0 /*CODE REVIEW Stefan Lindholm*/
    int mNumFields;
    static void hasChangedCB(void * data, SoSensor*) { ((SoXipGpuProcessTextureKit *)data)->setHasChanged(); };

    inline void		setHasChanged()
    {
        this->mChanged = true;
    }

    std::vector<SoFieldSensor *> mInputSensors;
#endif
};


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

#endif // SO_XIP_GPU_PROCESS_TEXTURE_KIT_H
