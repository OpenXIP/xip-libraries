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
*/#ifndef SOREFXIPEXAMINER_H
#define SOREFXIPEXAMINER_H

class QString;
class SoSFEnum;
class SoSFTrigger;
class QStringList;
class SoSFEnumExtended;

#include <Inventor/sensors/SoFieldSensor.h>

class SoRefXipExaminer
{
public:
    SoRefXipExaminer(QString nodeName);
    ~SoRefXipExaminer();

    void setOrientation(QString newOrientation);
    void triggerViewOrientation();
    void triggerViewAll();
    void resetView(QString newOrientation);

    void setMode(QString mode);
    QString getMode();
	
    QStringList getModeList();
	QStringList getOrientationList();

    void switchModes();

    void setModeCB(SoSensorCB* func, void* data);

private:
    SoSFEnumExtended* fldOrientation;
    SoSFTrigger* triViewOrientation;
    SoSFTrigger* triViewAll;
    SoSFEnumExtended* fldMode;

    SoFieldSensor* senMode;

    int maxModes;
};

#endif
