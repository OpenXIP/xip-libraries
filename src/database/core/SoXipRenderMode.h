#ifndef SOXIPRENDERMODE_H
#define SOXIPRENDERMODE_H

#include <vector>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/actions/SoActions.h>
#include <xip/inventor/core/SoXipRenderModeElement.h>
#include <xip/inventor/core/XipInventorUtils.h>


class SoFieldSensor;

class XIPIVCORE_API SoXipRenderMode : public SoNode
{
	SO_NODE_HEADER(SoXipRenderMode);

public:
	enum render_mode_t {
        MPR			= SoXipRenderModeElement::MPR,
        MAXIP		= SoXipRenderModeElement::MAXIP,
        MINIP		= SoXipRenderModeElement::MINIP,
        SSD			= SoXipRenderModeElement::SSD,
		COLORSSD	= SoXipRenderModeElement::SSD_COLOR,
        VRT			= SoXipRenderModeElement::VRT_COLOR,
		DRR			= SoXipRenderModeElement::DRR
	};

	SoSFEnum mode;

	static void initClass();
	SoXipRenderMode();

protected:
	XIP_DOACTION_HEADER();
};

#endif // SOXIPRENDERMODE_H