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
*/#include "SoRefXipWindowLevelManip.h"

#include <QDebug>
#include <QString>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFFloat.h>

#include "definitions.h"

SoRefXipWindowLevelManip::SoRefXipWindowLevelManip(QString nodeName)
{
	fldWindow = 0;
	fldLevel = 0;

    senWindow = 0;
    senLevel = 0;

    SoNode* fldContainer = SoNode::getByName(SbName(nodeName.toAscii()));
    if (fldContainer)
    {
        CONNECTFIELD(fldContainer, "window", fldWindow, SoSFFloat);
        CONNECTFIELD(fldContainer, "level", fldLevel, SoSFFloat);
    }

    initialWindow = this->getWindow();
    initialLevel = this->getLevel();
}

SoRefXipWindowLevelManip::~SoRefXipWindowLevelManip()
{
}

void SoRefXipWindowLevelManip::setWindowCB(SoSensorCB* func, void* data)
{
    if (!fldWindow) return;
    senWindow = new SoFieldSensor(func, data);
    if (senWindow) senWindow->attach(fldWindow);
}

void SoRefXipWindowLevelManip::setLevelCB(SoSensorCB* func, void* data)
{
    if (!fldLevel) return;
    senLevel = new SoFieldSensor(func, data);
    if (senLevel) senLevel->attach(fldLevel);
}

void SoRefXipWindowLevelManip::setWindow(float newWindow)
{
    if (!fldWindow) return;
    fldWindow->setValue(newWindow);
}

void SoRefXipWindowLevelManip::setLevel(float newLevel)
{
    if (!fldLevel) return;
    fldLevel->setValue(newLevel);
}

float SoRefXipWindowLevelManip::getWindow()
{
    if (!fldWindow) return 0;
    return fldWindow->getValue();
}

float SoRefXipWindowLevelManip::getLevel()
{
    if (!fldLevel) return 0;
    return fldLevel->getValue();
}

void SoRefXipWindowLevelManip::resetValues()
{
    this->setWindow(initialWindow);
    this->setLevel(initialLevel);
}
