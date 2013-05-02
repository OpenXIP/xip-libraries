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
#include "SoXipImage.h"

#include <Inventor/actions/SoActions.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoSFEnum.h>

#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipLutElement.h>


SO_KIT_SOURCE( SoXipImage );


SoXipImage::SoXipImage()
{
    mApplyLut = 0;
    mTexture = 0;
    mMatrix = 0;
    mQuad = 0;
    mTextureMode = 0;
    mConnectionsSet = false;
    mImageDirty = true;
    mHasLut = false;

    SO_KIT_CONSTRUCTOR(SoXipImage);

    SO_NODE_ADD_FIELD(image, (NULL));

    SO_KIT_ADD_CATALOG_ENTRY(top,      SoSeparator,          FALSE, this, \x0, FALSE);
    SO_KIT_ADD_CATALOG_ENTRY(applylut, SoXipApplyLutToImage, FALSE,  top, \x0, FALSE);
    SO_KIT_ADD_CATALOG_ENTRY(texture,  SoXipTexture,         FALSE,  top, \x0, FALSE);
    SO_KIT_ADD_CATALOG_ENTRY(matrix,   SoMatrixTransform,    FALSE,  top, \x0, FALSE);
    SO_KIT_ADD_CATALOG_ENTRY(quad,     SoXipQuad,            FALSE,  top, \x0, FALSE);

    SO_KIT_INIT_INSTANCE();

    mImageSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
    mImageSensor->setPriority(0);
    mImageSensor->attach(&image);
}

SoXipImage::~SoXipImage()
{
    if (mImageSensor)
        delete mImageSensor;

    mImageSensor = 0;
}

void SoXipImage::initClass()
{
    SO_KIT_INIT_CLASS(SoXipImage, SoBaseKit, "BaseKit");
}


bool SoXipImage::setKitConnections()
{
    mApplyLut = SoBaseKit::getAnyPart("applylut", TRUE);
    mTexture  = SoBaseKit::getAnyPart("texture", TRUE);
    mMatrix   = SoBaseKit::getAnyPart("matrix", TRUE);
    mQuad     = SoBaseKit::getAnyPart("quad", TRUE);

    SoField * field = mTexture->getField("model");
    mTextureMode = mMatrix ? dynamic_cast<SoSFEnum*>(field) : 0;

    bool valid = (mApplyLut && mTexture && mMatrix && mQuad && mTextureMode);

    if (!valid)
    {
        SoDebugError::post("SoXipImage", "Failed to retrieve kit pointers");
        return false;
    }

    valid = valid && connectField(mApplyLut, "image", &image, true);
    valid = valid && connectFields(mApplyLut, "output", mTexture, "image");
    valid = valid && connectFields(mTexture, "modelMatrix", mMatrix, "matrix");

    if (!valid)
    {
        SoDebugError::post("SoXipImage", "Failed to set kit field connections");
        return false;
    }

    imageChanged();

    return valid;
}

void SoXipImage::imageChanged()
{
    mImageDirty = true;
}

void SoXipImage::GLRender(SoGLRenderAction * action)
{
    try
    {
        if (!mConnectionsSet)
            mConnectionsSet = setKitConnections();

	SoXipData * eltLut = (SoXipData *)SoXipLutElement::get(action->getState());

        // If LUT presence change, or image is dirty, update texture mode
        bool updateTexMode = ((eltLut == 0) == mHasLut) || mImageDirty;

        mHasLut = (eltLut != 0);        // Rememeber if we had a LUT or not

        if (updateTexMode && mTextureMode) {
            // This is a hack to keep same behavior as previous SoXipImage
            if (mHasLut) {
                mTextureMode->set("REPLACE");
            }
            else {
                SoXipDataImage * dip = image.getValue();
                SbXipImage *     ip = dip ? dip->get() : 0;

                if (ip) {
                    if (ip->getComponents() > 2) {
                        mTextureMode->set("REPLACE");
                    }
                    else {
                        mTextureMode->set("MODULATE");
                    }
                }
            }

            mImageDirty = false;
        }

        if (mConnectionsSet)
            SoBaseKit::GLRender(action);
    }
    catch (...)
    {
        SoError::post(__FILE__, "Unknown error while rendering image");
    }
}

void SoXipImage::getBoundingBox(SoGetBoundingBoxAction *action)
{
    mMatrix->getBoundingBox(action);
    mQuad->getBoundingBox(action);
}

void SoXipImage::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
    SoXipImage * me = reinterpret_cast<SoXipImage *>(user);

    if (me) me->imageChanged();
}

/*
  These internal functions should be removed and instead moved to
  a common utility package to simplify setups similar to this.

  9/8/2009 - Patric Ljung
*/

bool SoXipImage::connectFields(SoNode * fromNode, SbName fromField,
                               SoNode * toNode, SbName toField)
{
    if (fromNode && toNode)
    {
        SoField * fromF = fromNode->getField(fromField);
        SoField * toF = toNode->getField(toField);

        if (fromF && toF)
            return toF->connectFrom( fromF ) == TRUE;
    }

    return false;
}

bool SoXipImage::connectField(SoNode * fromNode, SbName fromField,
                              SoField * toField, bool invert)
{
    if (fromNode && toField)
    {
        SoField * fromF = fromNode->getField(fromField);
        if (fromF)
        {
            if (invert)
                return fromF->connectFrom( toField ) == TRUE;
            else
                return toField->connectFrom( fromF ) == TRUE;
        }
    }

    return false;
}

bool SoXipImage::setField(SoNode * node, SbName field, const char * value)
{
    if (node)
    {
        SoField * fp = node->getField(field);
        if (fp)
            return fp->set( value ) == TRUE;
    }

    return false;
}
