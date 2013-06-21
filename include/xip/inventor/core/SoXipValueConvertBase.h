/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/#ifndef SoXipValueConvertBase_H
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
