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
#include "SoRefXipLoadDicom.h"

#include <QString>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/fields/SoMFString.h>

#include "definitions.h"

SoRefXipLoadDicom::SoRefXipLoadDicom(QString nodeName)
{
    fldName = 0;

    SoEngine* fldContainer = SoEngine::getByName(SbName(nodeName.toAscii()));
    if (fldContainer)
    {
        CONNECTFIELD(fldContainer, "name", fldName, SoMFString);
    }
}

SoRefXipLoadDicom::~SoRefXipLoadDicom()
{
}

void SoRefXipLoadDicom::setName(QString name)
{
    if (!fldName) return;
    fldName->setValue(name.toAscii());
}

QString SoRefXipLoadDicom::getName()
{
    if (!fldName) return QString();
    return QString(fldName->getValues(0)->getString()).replace("/", "\\");
}

void SoRefXipLoadDicom::setNameCB(SoSensorCB* func, void* data)
{
    if (!fldName) return;
    senName = new SoFieldSensor(func, data);
    if (senName) senName->attach(fldName);
}
