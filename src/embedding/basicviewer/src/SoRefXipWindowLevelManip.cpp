#include "SoRefXipWindowLevelManip.h"

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