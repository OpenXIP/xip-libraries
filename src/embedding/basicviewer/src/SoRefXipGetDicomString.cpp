#include "SoRefXipGetDicomString.h"

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