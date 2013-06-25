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
*/#include "SoRefXipMprExaminer.h"

#include <QString>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFTrigger.h>

#include "definitions.h"

SoRefXipMprExaminer::SoRefXipMprExaminer(QString nodeName)
{
    fldOrientation = 0;
    triViewOrientation = 0;
    triViewAll = 0;

    SoNode* fldContainer = SoNode::getByName(SbName(nodeName.toAscii()));
    if (fldContainer)
    {
        CONNECTFIELD(fldContainer, "orientation", fldOrientation, SoSFEnum);
        CONNECTFIELD(fldContainer, "viewOrientation", triViewOrientation, SoSFTrigger);
        CONNECTFIELD(fldContainer, "viewAll", triViewAll, SoSFTrigger);
    }
}

SoRefXipMprExaminer::~SoRefXipMprExaminer()
{
}

void SoRefXipMprExaminer::setOrientation(QString newOrientation)
{
    if (!fldOrientation) return;
    fldOrientation->setValue(SbName(newOrientation.toAscii()));
}

void SoRefXipMprExaminer::triggerViewOrientation()
{
    if (!triViewOrientation) return;
    triViewOrientation->setValue();
}

void SoRefXipMprExaminer::triggerViewAll()
{
    if (!triViewAll) return;
    triViewAll->setValue();
}

void SoRefXipMprExaminer::resetView(QString newOrientation)
{
    this->setOrientation(newOrientation);
    this->triggerViewOrientation();
    this->triggerViewAll();
}
