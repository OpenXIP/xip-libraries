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
*/#include "SoRefXipTexture.h"

#include <QString>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>

#include "definitions.h"

SoRefXipTexture::SoRefXipTexture(QString nodeName)
{
    fldWrapS = 0;
    fldWrapT = 0;
    fldWrapR = 0;

    SoNode* fldContainer = SoNode::getByName(SbName(nodeName.toAscii()));
    if (fldContainer)
    {
        CONNECTFIELD(fldContainer, "wrapS", fldWrapS, SoSFEnum);
        CONNECTFIELD(fldContainer, "wrapT", fldWrapT, SoSFEnum);
        CONNECTFIELD(fldContainer, "wrapR", fldWrapR, SoSFEnum);
    }
}

SoRefXipTexture::~SoRefXipTexture()
{
}

void SoRefXipTexture::setWrapS(QString wrapS)
{
    if (!fldWrapS) return;
    fldWrapS->setValue(SbName(wrapS.toAscii()));
}

void SoRefXipTexture::setWrapT(QString wrapT)
{
    if (!fldWrapT) return;
    fldWrapT->setValue(SbName(wrapT.toAscii()));
}

void SoRefXipTexture::setWrapR(QString wrapR)
{
    if (!fldWrapR) return;
    fldWrapR->setValue(SbName(wrapR.toAscii()));
}

QString SoRefXipTexture::getWrapS()
{
    if (!fldWrapS) return QString();
    SbString tmpVal;
    fldWrapS->get(tmpVal);
    return QString(tmpVal.getString());
    
}

QString SoRefXipTexture::getWrapT()
{
    if (!fldWrapT) return QString();
    SbString tmpVal;
    fldWrapT->get(tmpVal);
    return QString(tmpVal.getString());
}

QString SoRefXipTexture::getWrapR()
{
    if (!fldWrapR) return QString();
    SbString tmpVal;
    fldWrapR->get(tmpVal);
    return QString(tmpVal.getString());
}
