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
*/#include "SoRefXipLut.h"

#include <QString>
#include <QColor>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>

#include "definitions.h"

SoRefXipLut::SoRefXipLut(QString nodeName)
{
    fldColorTop = 0;
    fldColorMiddle = 0;
    fldColorBottom = 0;

    SoNode* fldContainer = SoNode::getByName(SbName(nodeName.toAscii()));
    if (fldContainer)
    {
        CONNECTFIELD(fldContainer, "colorBottom", fldColorBottom, SoSFColor);
        CONNECTFIELD(fldContainer, "colorMiddle", fldColorMiddle, SoSFColor);
        CONNECTFIELD(fldContainer, "colorTop", fldColorTop, SoSFColor);
        CONNECTFIELD(fldContainer, "rampWidth", fldRampWidth, SoSFFloat);
        CONNECTFIELD(fldContainer, "rampCenter", fldRampCenter, SoSFFloat);
    }
}

SoRefXipLut::~SoRefXipLut()
{
}

void SoRefXipLut::setColorTop(QColor topColor)
{
    if (!fldColorTop) return;
    fldColorTop->setValue(SbColor(topColor.redF(), topColor.greenF(), topColor.blueF()));
}

void SoRefXipLut::setColorMiddle(QColor middleColor)
{
    if (!fldColorMiddle) return;
    fldColorMiddle->setValue(SbColor(middleColor.redF(), middleColor.greenF(), middleColor.blueF()));
}

void SoRefXipLut::setColorBottom(QColor bottomColor)
{
    if (!fldColorBottom) return;
    fldColorBottom->setValue(SbColor(bottomColor.redF(), bottomColor.greenF(), bottomColor.blueF()));
}

void SoRefXipLut::setRampWidth(float width)
{
    if (!fldRampWidth) return;
    fldRampWidth->setValue(width);
}

void SoRefXipLut::setRampCenter(float center)
{
    if (!fldRampCenter) return;
    fldRampCenter->setValue(center);
}

void SoRefXipLut::setRampWidthCB(SoSensorCB* func, void* data)
{
    if (!fldRampWidth) return;
    senRampWidth = new SoFieldSensor(func, data);
    if (senRampWidth) senRampWidth->attach(fldRampWidth);
}

void SoRefXipLut::setRampCenterCB(SoSensorCB* func, void* data)
{
    if (!fldRampCenter) return;
    senRampCenter = new SoFieldSensor(func, data);
    if (senRampCenter) senRampCenter->attach(fldRampCenter);
}

void SoRefXipLut::setColorBottomCB(SoSensorCB* func, void* data)
{
    if (!fldColorBottom) return;
    senColorBottom = new SoFieldSensor(func, data);
    if (senColorBottom) senColorBottom->attach(fldColorBottom);
}

void SoRefXipLut::setColorMiddleCB(SoSensorCB* func, void* data)
{
    if (!fldColorMiddle) return;
    senColorMiddle = new SoFieldSensor(func, data);
    if (senColorMiddle) senColorMiddle->attach(fldColorMiddle);
}

void SoRefXipLut::setColorTopCB(SoSensorCB* func, void* data)
{
    if (!fldColorTop) return;
    senColorTop = new SoFieldSensor(func, data);
    if (senColorTop) senColorTop->attach(fldColorTop);
}

QColor SoRefXipLut::getColorTop()
{
    if (!fldColorTop) return QColor();
    QColor returnColor;
    returnColor.setRedF(fldColorTop->getValue()[0]);
    returnColor.setGreenF(fldColorTop->getValue()[1]);
    returnColor.setBlueF(fldColorTop->getValue()[2]);
    return returnColor;
}

QColor SoRefXipLut::getColorMiddle()
{
    if (!fldColorMiddle) return QColor();
    QColor returnColor;
    returnColor.setRedF(fldColorMiddle->getValue()[0]);
    returnColor.setGreenF(fldColorMiddle->getValue()[1]);
    returnColor.setBlueF(fldColorMiddle->getValue()[2]);
    return returnColor;
}

QColor SoRefXipLut::getColorBottom()
{
    if (!fldColorBottom) return QColor();
    QColor returnColor;
    returnColor.setRedF(fldColorBottom->getValue()[0]);
    returnColor.setGreenF(fldColorBottom->getValue()[1]);
    returnColor.setBlueF(fldColorBottom->getValue()[2]);
    return returnColor;
}

float SoRefXipLut::getRampWidth()
{
    if (!fldRampWidth) return 0;
    return fldRampWidth->getValue();
}

float SoRefXipLut::getRampCenter()
{
    if (!fldRampCenter) return 0;
    return fldRampCenter->getValue();
}
