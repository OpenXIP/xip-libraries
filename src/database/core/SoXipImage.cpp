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
