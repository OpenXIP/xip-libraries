#ifndef SoXipValueConvertBase_H
#define SoXipValueConvertBase_H

#include <Inventor/nodes/SoSubNode.h> 
#include "xipivCore.h"

class XIPIVCORE_API SoXipValueConvertBase : public SoNode	
{
	SO_NODE_HEADER( SoXipValueConvertBase );

public:	
	SoXipValueConvertBase();	

	static void initClass();

	virtual float getValueConverted(float val_in);
protected:
	
	//~SoXipValueConvertBase();
	
	void GLRender(SoGLRenderAction *action);

	void handleEvent(SoGLRenderAction *action);
	
	void doAction(SoGLRenderAction *action);
};

#endif //SoXipValueConvertBase_H