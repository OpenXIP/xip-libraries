#include "SoRefXipSlicer.h"

#include <QString>
#include <QStringList>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>

#include "SoRefXipTexture.h"
#include "SoSFEnumExtended.h"
#include "definitions.h"

SoRefXipSlicer::SoRefXipSlicer(QString nodeName, SoRefXipTexture* ref)
{
    fldMode = 0;
    fldNumSlices = 0;
    refTextureNode = ref;

    SoNode* fldContainer = SoNode::getByName(SbName(nodeName.toAscii()));
    if (fldContainer)
    {
        CONNECTFIELD(fldContainer, "mode", fldMode, SoSFEnumExtended);
        CONNECTFIELD(fldContainer, "numSlices", fldNumSlices, SoSFInt32);
    }
}

SoRefXipSlicer::~SoRefXipSlicer()
{
}

void SoRefXipSlicer::setMode(QString mode)
{
    if (!fldMode) return;

    if (refTextureNode)
    {
        if (mode == "MPR")
        {
            refTextureNode->setWrapS("CLAMP_TO_BORDER");
            refTextureNode->setWrapT("CLAMP_TO_BORDER");
            refTextureNode->setWrapR("CLAMP_TO_BORDER");
        }
        else
        {
            refTextureNode->setWrapS("CLAMP_TO_EDGE");
            refTextureNode->setWrapT("CLAMP_TO_EDGE");
            refTextureNode->setWrapR("CLAMP_TO_EDGE");
        }
    }
    fldMode->setValue(SbName(mode.toAscii()));
}

void SoRefXipSlicer::setNumSlices(int numSlices)
{
    if (!fldNumSlices) return;
    fldNumSlices->setValue(numSlices);
}

QString SoRefXipSlicer::getMode()
{
    if (!fldMode) return QString();
    SbString tmpVal;
    fldMode->get(tmpVal);
    return QString(tmpVal.getString());
}

int SoRefXipSlicer::getNumSlices()
{
    if (!fldNumSlices) return 0;
    return fldNumSlices->getValue();
}

QStringList SoRefXipSlicer::getModeList()
{
	if (!fldMode) return QStringList();
	return fldMode->getAllEnums();
}
