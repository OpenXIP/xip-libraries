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
*/

#ifndef SOXIPANCHOR_H
#define SOXIPANCHOR_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>


// simple node to anchor graphics to any side of the viewport
class SoXipAnchor : public SoNode
{
	SO_NODE_HEADER(SoXipAnchor);

public:

	SoSFBool left;
	SoSFBool top;
	SoSFBool right;
	SoSFBool bottom;

	SoXipAnchor();
	static void initClass();

	virtual void doAction(SoAction *action);

	virtual void handleEvent(SoHandleEventAction *action);
	virtual void GLRender(SoGLRenderAction *action);
	virtual void callback(SoCallbackAction *action);
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);
	virtual void pick(SoPickAction *action);

protected:
	virtual ~SoXipAnchor();

	SbVec3f mTranslation;
};


#endif // SOXIPANCHOR_H
