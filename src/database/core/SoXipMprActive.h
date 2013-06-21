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

#ifndef SOXIPMPRACTIVE_H
#define SOXIPMPRACTIVE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFBool.h>


/**
 * Simple node that will set / read the index of the active MPRElement
 */
class SoXipMprActive : public SoNode
{
	SO_NODE_HEADER(SoXipMprActive);
 
public:
	static void initClass();
	SoXipMprActive();
	SoSFInt32 id;
	SoSFBool on;

protected:	
	virtual void callback(SoCallbackAction* action);
	virtual void GLRender(SoGLRenderAction* action);
	virtual void pick(SoPickAction* action);
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);
	virtual void handleEvent(SoHandleEventAction *action);
	virtual void doAction(SoAction* action);
	
private:
	~SoXipMprActive();
};


#endif // SOXIPMPRACTIVE_H


