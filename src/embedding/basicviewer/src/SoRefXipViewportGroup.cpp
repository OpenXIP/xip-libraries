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
*/#include "SoRefXipViewportGroup.h"

#include <QString>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFBool.h>

#include "definitions.h"

SoRefXipViewportGroup::SoRefXipViewportGroup(QString nodeName)
{
    fldCurrent = 0;
    fldMaximized = 0;

    SoNode* fldContainer = SoNode::getByName(SbName(nodeName.toAscii()));
    if (fldContainer)
    {
        CONNECTFIELD(fldContainer, "current", fldCurrent, SoSFInt32);
        CONNECTFIELD(fldContainer, "maximized", fldMaximized, SoSFBool);
    }
}

SoRefXipViewportGroup::~SoRefXipViewportGroup()
{
}

void SoRefXipViewportGroup::setWindow0Maximized()
{
    this->setCurrent(0);
    this->setMaximized(true);
}

void SoRefXipViewportGroup::setWindow1Maximized()
{
    this->setCurrent(1);
    this->setMaximized(true);
}

void SoRefXipViewportGroup::setWindow2Maximized()
{
    this->setCurrent(2);
    this->setMaximized(true);
}

void SoRefXipViewportGroup::setWindow3Maximized()
{
    this->setCurrent(3);
    this->setMaximized(true);
}

void SoRefXipViewportGroup::setNormalState()
{
    this->setCurrent(3);
    this->setMaximized(false);
    this->setCurrent(2);
    this->setMaximized(false);
    this->setCurrent(1);
    this->setMaximized(false);
    this->setCurrent(0);
    this->setMaximized(false);
}

void SoRefXipViewportGroup::setCurrent(int current)
{
    if (!fldCurrent) return;
    fldCurrent->setValue(current);
}

void SoRefXipViewportGroup::setMaximized(bool maximized)
{
    if (!fldMaximized) return;
    fldMaximized->setValue(maximized);
}

int SoRefXipViewportGroup::getCurrent()
{
    if (!fldCurrent) return 0;
    return fldCurrent->getValue();
}

bool SoRefXipViewportGroup::getMaximized()
{
    if (!fldMaximized) return 0;
    return fldMaximized->getValue();
}
