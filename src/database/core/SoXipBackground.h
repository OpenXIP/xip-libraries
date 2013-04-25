#ifndef _SO_XIP_BACKGROUND_H_
#define _SO_XIP_BACKGROUND_H_

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>

class SoXipBackground : public SoNode
{
	SO_NODE_HEADER(SoXipBackground);

public:
	SoMFColor color;
	SoMFFloat alpha;

	SoXipBackground();
	static void initClass();

protected:
	virtual ~SoXipBackground();

	virtual void GLRender(SoGLRenderAction *action);
};


#endif // SoXipBackground_H
