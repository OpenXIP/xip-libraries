#ifndef SOXIPLOGGLSTATE_H
#define SOXIPLOGGLSTATE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>

class SoXipLogGLState : public SoNode
{
SO_NODE_HEADER(SoXipLogGLState);

public:

	SoSFBool	log;
	SoSFString	filename;
	
	static void initClass();
	SoXipLogGLState();

protected:
	~SoXipLogGLState();

	virtual void GLRender(SoGLRenderAction * action);

	int mCount;
};

#endif
