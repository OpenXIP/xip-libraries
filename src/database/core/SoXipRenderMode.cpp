#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoMemoryError.h> 
#include <Inventor/actions/SoActions.h> 
#include <xip/inventor/core/SoXipRenderModeElement.h>
#include "SoXipRenderMode.h"


SO_NODE_SOURCE(SoXipRenderMode);


SoXipRenderMode::SoXipRenderMode()
{
	SO_NODE_CONSTRUCTOR(SoXipRenderMode);

    SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, MPR);
	SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, MAXIP);
	SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, MINIP);
	SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, SSD);
    SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, COLORSSD);
	SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, VRT);
    SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, DRR);
	SO_NODE_SET_SF_ENUM_TYPE(mode, render_mode_t);

	SO_NODE_ADD_FIELD(mode, (MPR));
}


void SoXipRenderMode::initClass()
{
	SO_NODE_INIT_CLASS(SoXipRenderMode, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipRenderModeElement);
	SO_ENABLE(SoPickAction,     SoXipRenderModeElement);
	SO_ENABLE(SoCallbackAction, SoXipRenderModeElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipRenderModeElement);
}


void SoXipRenderMode::doAction(SoAction * action)
{
	SoXipRenderModeElement::set(action->getState(), this, 
		(SoXipRenderModeElement::RenderModes) mode.getValue());
}
