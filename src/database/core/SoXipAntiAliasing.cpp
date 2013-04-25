#include "SoXipAntiAliasing.h"

#include <xip\inventor\core\SoXipAntiAliasingElement.h>


SO_NODE_SOURCE(SoXipAntiAliasing);


void SoXipAntiAliasing::initClass()
{
	SO_NODE_INIT_CLASS(SoXipAntiAliasing, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipAntiAliasingElement);
}


SoXipAntiAliasing::SoXipAntiAliasing()
{
	SO_NODE_CONSTRUCTOR(SoXipAntiAliasing);
	SO_NODE_ADD_FIELD(active, (FALSE));

	mActive = !active.getValue();
}


SoXipAntiAliasing::~SoXipAntiAliasing()
{
}

void SoXipAntiAliasing::GLRender(SoGLRenderAction *action)
{
//	SoXipAntiAliasingElement::set(action->getState(), this, active.getValue());

//	if (mActive != active.getValue())
//	{
		if (active.getValue())
		{
//			mTransparencyType = action->getTransparencyType();
//			action->setTransparencyType(SoGLRenderAction::TransparencyType::SCREEN_DOOR);
			action->setSmoothing(1);
		}
		else
		{
			action->setSmoothing(0);
//			action->setTransparencyType(SoGLRenderAction::TransparencyType::BLEND);
		}
//	}
}