#include "SoRefXipMprExaminer.h"

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
