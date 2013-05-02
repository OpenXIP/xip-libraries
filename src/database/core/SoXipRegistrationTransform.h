#pragma once

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFMatrix.h>

class SoXipRegistrationTransform : public SoNode
{
	SO_NODE_HEADER(SoXipRegistrationTransform);

public:
	// Fields
	SoSFMatrix		matrix;

	SoXipRegistrationTransform();

	static void initClass();

	virtual void doAction(SoAction *action);

	virtual void callback(SoCallbackAction *action);

	virtual void GLRender(SoGLRenderAction *action);

	virtual void handleEvent(SoHandleEventAction *action);
	
	virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
	
	virtual void	getMatrix(SoGetMatrixAction *action);
	
	virtual void	pick(SoPickAction *action);

protected:
	virtual ~SoXipRegistrationTransform();
};