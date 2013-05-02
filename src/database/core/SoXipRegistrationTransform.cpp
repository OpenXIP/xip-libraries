#include "SoXipRegistrationTransform.h"
#include <xip/inventor/core/SoXipRegistrationElement.h>

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/elements/SoModelMatrixElement.h>

#include <xip/common/XipDebug.h>

SO_NODE_SOURCE(SoXipRegistrationTransform);

SoXipRegistrationTransform::SoXipRegistrationTransform()
{
	SO_NODE_CONSTRUCTOR(SoXipRegistrationTransform);
	SO_NODE_ADD_FIELD(matrix, (SbMatrix::identity()));
}

SoXipRegistrationTransform::~SoXipRegistrationTransform()
{
}

void
SoXipRegistrationTransform::initClass()
{
	SO_NODE_INIT_CLASS(SoXipRegistrationTransform, SoNode, "Node");

	SO_ENABLE(SoHandleEventAction, SoXipRegistrationElement);	
	SO_ENABLE(SoGLRenderAction, SoXipRegistrationElement);
	SO_ENABLE(SoPickAction,     SoXipRegistrationElement);
	SO_ENABLE(SoCallbackAction, SoXipRegistrationElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipRegistrationElement);
}

void
SoXipRegistrationTransform::doAction(SoAction *action)
{
	if (! matrix.isIgnored() && ! matrix.isDefault())
	{
		//SoModelMatrixElement::mult(action->getState(), this, matrix.getValue());
		SoState *state = action->getState();
		SbMatrix mat = matrix.getValue();
		//mat[3][1] = -mat[3][1];
		//mat[3][2] = -mat[3][2];

		//XipDebug::output("%f %f %f %f", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
		//const float fM_PI = static_cast<float>(M_PI);
		//SbMatrix rot;
		//rot.setRotate(SbRotation(SbVec3f(1, 0, 0), fM_PI));
		//mat = mat * rot;

		//XipDebug::output("%f %f %f %f", mat[12], mat[13], mat[14], mat[15]);

		//SbMatrix mat = SoModelMatrixElement::get(state);
		//mat *= matrix.getValue();
		SoXipRegistrationElement::set(state, this, mat);
		//SoXipRegistrationElement::set(state, this, matrix.getValue());
	}
}

void
SoXipRegistrationTransform::callback(SoCallbackAction *action)
{
	SoXipRegistrationTransform::doAction(action);
}

void
SoXipRegistrationTransform::GLRender(SoGLRenderAction *action)
{
	SoXipRegistrationTransform::doAction(action);
}

void
SoXipRegistrationTransform::getBoundingBox(SoGetBoundingBoxAction *action)
{
	SoXipRegistrationTransform::doAction(action);
}

void
SoXipRegistrationTransform::getMatrix(SoGetMatrixAction *action)
{
	if (! matrix.isIgnored() && ! matrix.isDefault()) 
	{
		SbMatrix	&ctm = action->getMatrix();
		SbMatrix	&inv = action->getInverse();
		SbMatrix	m, mInv;

		m = matrix.getValue();
		ctm.multLeft(m);
		mInv = m.inverse();
		inv.multRight(mInv);
	}
}

void
SoXipRegistrationTransform::pick(SoPickAction *action)
{
	SoXipRegistrationTransform::doAction(action);
}

void
SoXipRegistrationTransform::handleEvent(SoHandleEventAction *action)
{
	SoXipRegistrationTransform::doAction(action);
}