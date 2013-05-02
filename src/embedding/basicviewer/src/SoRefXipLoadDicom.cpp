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
