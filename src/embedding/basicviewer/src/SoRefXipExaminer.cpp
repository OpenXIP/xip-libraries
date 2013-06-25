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
*/#include "SoRefXipExaminer.h"

#include <QString>
#include <QStringList>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFTrigger.h>

#include "SoSFEnumExtended.h"
#include "definitions.h"

SoRefXipExaminer::SoRefXipExaminer(QString nodeName)
{
    fldOrientation = 0;
    fldMode = 0;

    triViewOrientation = 0;
    triViewAll = 0;

    senMode = 0;

    SoNode* fldContainer = SoNode::getByName(SbName(nodeName.toAscii()));
    if (fldContainer)
    {
        CONNECTFIELD(fldContainer, "orientation", fldOrientation, SoSFEnumExtended);
        CONNECTFIELD(fldContainer, "viewOrientation", triViewOrientation, SoSFTrigger);
        CONNECTFIELD(fldContainer, "viewAll", triViewAll, SoSFTrigger);
        CONNECTFIELD(fldContainer, "mode", fldMode, SoSFEnumExtended);
    }

	if (fldMode)
		maxModes = fldMode->getNumEnums() - 1;
	else
		maxModes = 0;
}

SoRefXipExaminer::~SoRefXipExaminer()
{
}

QStringList SoRefXipExaminer::getModeList()
{
	if (!fldMode) return QStringList();
	return fldMode->getAllEnums();
}

QStringList SoRefXipExaminer::getOrientationList()
{
	if (!fldOrientation) return QStringList();
	return fldOrientation->getAllEnums();
}

void SoRefXipExaminer::setOrientation(QString newOrientation)
{
    if (!fldOrientation) return;
    fldOrientation->setValue(SbName(newOrientation.toAscii()));
}

void SoRefXipExaminer::triggerViewOrientation()
{
    if (!triViewOrientation) return;
    triViewOrientation->setValue();
}

void SoRefXipExaminer::triggerViewAll()
{
    if (!triViewAll) return;
    triViewAll->setValue();
}

void SoRefXipExaminer::switchModes()
{
    if (!fldMode) return;
    if (fldMode->getValue() >= maxModes)
        fldMode->setValue(0);
    else
        fldMode->setValue(fldMode->getValue() + 1);
}

void SoRefXipExaminer::resetView(QString newOrientation)
{
    this->setOrientation(newOrientation);
    this->triggerViewOrientation();
    this->triggerViewAll();
}

void SoRefXipExaminer::setModeCB(SoSensorCB* func, void* data)
{
    if (!fldMode) return;
    senMode = new SoFieldSensor(func, data);
    if (senMode)
        senMode->attach(fldMode);
}

void SoRefXipExaminer::setMode(QString mode)
{
    if (!fldMode) return;
    fldMode->setValue(SbName(mode.toAscii()));
}

QString SoRefXipExaminer::getMode()
{
    if (!fldMode) return QString();
    SbString tmpVal;
    fldMode->get(tmpVal);
    return QString(tmpVal.getString());
}
