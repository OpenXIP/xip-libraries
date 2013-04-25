#ifndef SOXIPANTIALIASING_H
#define SOXIPANTIALIASING_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor\actions\SoGLRenderAction.h>


// node to set the AntiAliasing Element
class SoXipAntiAliasing : public SoNode
{
	SO_NODE_HEADER(SoXipAntiAliasing);

public:

	SoSFBool active;

	SoXipAntiAliasing();
	static void initClass();

	virtual void GLRender(SoGLRenderAction *action);

protected:
	virtual ~SoXipAntiAliasing();

	SbBool					mActive;
	SoGLRenderAction::TransparencyType		mTransparencyType;
};


#endif // SOXIPANTIALIASING_H