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
*/#ifndef SOREFXIPLUT_H
#define SOREFXIPLUT_H

#include <Inventor/sensors/SoFieldSensor.h>

class QString;
class QColor;
class SoSFColor;
class SoSFFloat;

class SoRefXipLut
{
public:
    SoRefXipLut(QString nodeName);
    ~SoRefXipLut();

    void setColorTop(QColor topColor);
    void setColorMiddle(QColor middleColor);
    void setColorBottom(QColor bottomColor);
    void setRampWidth(float width);
    void setRampCenter(float center);

    void setRampWidthCB(SoSensorCB* func, void* data);
    void setRampCenterCB(SoSensorCB* func, void* data);
    void setColorBottomCB(SoSensorCB* func, void* data);
    void setColorMiddleCB(SoSensorCB* func, void* data);
    void setColorTopCB(SoSensorCB* func, void* data);

    QColor getColorTop();
    QColor getColorMiddle();
    QColor getColorBottom();
    float getRampWidth();
    float getRampCenter();

private:
    SoSFColor* fldColorBottom;
    SoSFColor* fldColorMiddle;
    SoSFColor* fldColorTop;

    SoSFFloat* fldRampWidth;
    SoSFFloat* fldRampCenter;

    SoFieldSensor* senRampWidth;
    SoFieldSensor* senRampCenter;
    SoFieldSensor* senColorBottom;
    SoFieldSensor* senColorMiddle;
    SoFieldSensor* senColorTop;
};

#endif
