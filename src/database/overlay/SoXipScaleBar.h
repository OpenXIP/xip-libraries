// SoXipScaleBar.h: interface for the SoXipScaleBar class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SOXIPSCALEBAR_H
#define SOXIPSCALEBAR_H


#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/fields/SoSFBool.h>

class SoSeparator;
class SoOrthographicCamera;
class SoXipText2;
class SoScale;
class SoTranslation;
class SoSwitch;
class SoBaseColor;


/** ***********************************************************
 **
 **  Name: SoXipScaleBar
 **
 **  Description: Class required to display scale bar on the image
 **
 ** **********************************************************/
class SoXipScaleBar : public SoNode  
{
	SO_NODE_HEADER(SoXipScaleBar);

public:
	SoXipScaleBar();
	static void initClass();

	SoSFBool on;

protected:
	virtual ~SoXipScaleBar();
	virtual void GLRender(SoGLRenderAction *action);
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);

	SoSeparator *mTopSeparator;
	SoOrthographicCamera *mCamera;
	SoTranslation *mTranslation; 
	SoXipText2 *mText;
	SoScale *mScale;
	SoSwitch *mScaleSwitch;
	SoSwitch *mShadowSwitch;
	SoTranslation *mShadowTranslation; 
	SoBaseColor *mShadowColor; 
};

#endif // SOXIPSCALEBAR_H

