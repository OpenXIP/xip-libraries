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
*/#include "SoRefXipGetDicomString.h"

#include <QString>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoMFString.h>

#include "definitions.h"

SoRefXipGetDicomString::SoRefXipGetDicomString(QString nodeName)
{
    fldGroup = 0;
    fldElement = 0;
    fldOutput = 0;

    SoEngine* fldContainerEngine = SoEngine::getByName(SbName(nodeName.toAscii()));
    if (fldContainerEngine)
    {
        CONNECTFIELD(fldContainerEngine, "group", fldGroup, SoSFUShort);
        CONNECTFIELD(fldContainerEngine, "element", fldElement, SoSFUShort);
    }
    SoNode* fldContainerNode = SoNode::getByName("dicomText");
    if (fldContainerNode)
        CONNECTFIELD(fldContainerNode, "string", fldOutput, SoMFString);
}

SoRefXipGetDicomString::~SoRefXipGetDicomString()
{
}

void SoRefXipGetDicomString::setGroup(unsigned short group)
{
    if (!fldGroup) return;
    fldGroup->setValue(group);
}

unsigned short SoRefXipGetDicomString::getGroup()
{
    if (!fldGroup) return 0;
    return fldGroup->getValue();
}

void SoRefXipGetDicomString::setElement(unsigned short element)
{
    if (!fldElement) return;
    fldElement->setValue(element);
}

unsigned short SoRefXipGetDicomString::getElement()
{
    if (!fldElement) return 0;
    return fldElement->getValue();
}

QString SoRefXipGetDicomString::getOutput()
{
    if (!fldOutput) return QString();
    const SbString* test = fldOutput->getValues(0);
    if (test) return QString(test->getString());
    return "------";
}
