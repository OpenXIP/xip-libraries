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

#ifndef SOXIPMPRPLANE_H
#define SOXIPMPRPLANE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>

class SoFieldSensor;

/**
 * The SoXipMprPlane node is used to set the values of SoXipMprPlaneElement and to add it to the state.
 */
class SoXipMprPlane : public SoNode 
{
	SO_NODE_HEADER(SoXipMprPlane);

public:
	///	toggles MPR plane on and off. If on is false, the plane is not added to the state.
	SoSFBool   on;
	///	Matrix representation of the Mpr plane. The first two columns span the plane, the third is the resulting plane normal. 
	/// The fourth column is the center of the plane.
	SoSFMatrix plane;
	/// when 3 mpr planes are defined in the state, their intersection point is stored in the center field.
	SoSFVec3f  center;
//	SoSFBool   clip;
	///	sets the color attribute of the mpr plane. can be used to color the boarder frame of an mpr.
	SoSFColor  color;
	///	identifyier of the mpr plane. has to be set by user.
	SoSFInt32  id;
	///	read by SoXipMprExaminer to translate Mpr plane by stepSize. (only used by DogEarButton 10/23/2008)
	SoSFFloat  stepSize;
	SoSFFloat  thickness;
	
	/**
	 * initiliazation of class. Register node with open inventor DB.
	 */
	static void initClass();
	/**
	 * constructor initializes field values with default values.
	 */
	SoXipMprPlane();

protected:
	/**
	 * destructor.
	 */
	virtual ~SoXipMprPlane();
	/**
	 * sets values of SoXipMprPlaneElement and adds it to the state.
	 * \param action pointer to an Open Inventor action.
	 */
	virtual void doAction(SoAction * action);
	/**
	 * called when scene graph is rendered. calls doAction.
	 */
	virtual void GLRender(SoGLRenderAction * action);
	/**
	 * calls doAction.
	 */
	virtual void callback(SoCallbackAction * action);
	/**
	 * called when SoPickAction is processed, for picking scene objects. calls doAction.
	 */
	virtual void pick(SoPickAction * action);
	/**
	 * handles user input, like mouse and keyboeard events. calls doAction.
	 */
	virtual void handleEvent(SoHandleEventAction *action);
};

#endif // SOXIPMPRPLANE_H
