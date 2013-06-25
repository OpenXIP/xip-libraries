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

#ifndef SOXIPIMAGE_H
#define SOXIPIMAGE_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <xip/inventor/core/SoXipSFDataImage.h>

class SoSFEnum;
class SoFieldSensor;


class SoXipImage : public SoBaseKit
{
    SO_KIT_HEADER(SoXipImage);

public:
    /// Constructor
    SoXipImage();

    /// Open Inventor class initialization
    static void initClass();

    /// Image to be displayed
    SoXipSFDataImage	image;

public:
    /// Node kit catalog
    SO_KIT_CATALOG_ENTRY_HEADER(top);
    SO_KIT_CATALOG_ENTRY_HEADER(applylut);
    SO_KIT_CATALOG_ENTRY_HEADER(texture);
    SO_KIT_CATALOG_ENTRY_HEADER(matrix);
    SO_KIT_CATALOG_ENTRY_HEADER(quad);

protected:
    /// Destructor
    virtual ~SoXipImage();

protected:
    /// GL render call
    virtual void GLRender(SoGLRenderAction * action);
    virtual void getBoundingBox(SoGetBoundingBoxAction * action);

protected:
    bool connectFields(SoNode * fromNode, SbName fromField,
                       SoNode * toNode, SbName toField);
    bool connectField(SoNode * fromNode, SbName fromField,
                      SoField * toField, bool invert = false);
    bool setField(SoNode * node, SbName field, const char * value);

    SoNode *    mApplyLut;
    SoNode *    mTexture;
    SoNode *    mMatrix;
    SoNode *    mQuad;
    SoSFEnum *  mTextureMode;
    bool        mImageDirty;
    bool        mHasLut;

private:
    static void fieldSensorCBFunc(void *user, SoSensor *sensor);
    void imageChanged();

    SoFieldSensor * mImageSensor;

    bool setKitConnections();
    bool mConnectionsSet;
};

#endif // SOXIPIMAGE_H

