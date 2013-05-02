#include <xip/inventor/core/SoXipValueConvertBase.h>
#include <xip/inventor/core/SoXipValueConvertElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>

SO_NODE_SOURCE( SoXipValueConvertBase );

SoXipValueConvertBase::SoXipValueConvertBase()
{
	SO_NODE_CONSTRUCTOR( SoXipValueConvertBase);
}

void SoXipValueConvertBase::initClass()
{
	SO_NODE_INIT_CLASS( SoXipValueConvertBase, SoNode, "Node" );

	SO_ENABLE(SoHandleEventAction,	SoXipValueConvertElement	);
	SO_ENABLE(SoGLRenderAction,		SoXipValueConvertElement	);
}

float SoXipValueConvertBase::getValueConverted(float val_in)
{
	//base class just return the input
	return val_in;
}

void
SoXipValueConvertBase::GLRender(SoGLRenderAction *action)
{
	doAction(action);
}

void
SoXipValueConvertBase::handleEvent(SoGLRenderAction *action)
{
	doAction(action);
}

void
SoXipValueConvertBase::doAction(SoGLRenderAction *action)
{
	if (this!=SoXipValueConvertElement::getConvertObject(action->getState()))
		SoXipValueConvertElement::setConvertObject(action->getState(), this, this);
}