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
/**
*	@file	SoXipAngle.h
*	@brief	Node to perform an angle measurement in the current view
*	@author	Julien Gein
**/

#ifndef SOXIPANGLE_H
#define SOXIPANGLE_H

#include "SoXipShapeGroup.h"

/**
*	@class SoXipAngle
*
* This node is used to perform an angle measurement in the current view.
* It is a permanent overlay. User may use multiple instances of this node
* to perform multiple measures, or use this class as a parameter of the
* overlay manager (cf. SoXipOverlayManager)
*
* This node combines two line overlays (cf. SoXipLine). The parent class
* SoXipShapeGroup is used to group the two lines into one single overlay
* node. These two lines are not yet exposed to the user.
*
*	@see SoXipOverlayManager
*	@see SoXipLine
*
**/
class SoXipAngle : public SoXipShapeGroup
{
	SO_NODE_HEADER( SoXipAngle );

public:
	/// Constructor
	SoXipAngle();

	/// Module initialization
	static void initClass();

	/**
	*	@brief	set the rank (enumeration) of the shape
	*
	* This method overwrites SoXipShape::setRank() as we want the enumeration
	* to be displayed for the second line only.
	*
	*	@param rank			enumeration
	**/
	virtual void setRank( int rank );

	/**
	*	@brief	set the caption (annotation) of the shape
	*
	* This method overwrites SoXipShape::setCaption() as we want the annot
	* to be displayed for the second line only.
	*
	*	@param caption		shape annotation
	**/
	virtual void setCaption( const SbString& caption );
	
protected:
	/// Destructor
	~SoXipAngle();

	/// Rendering method
	virtual void GLRender( SoGLRenderAction* action );

	/**
	*	@brief	compute the angle given the two lines defined in the shape group
	*
	* The computed angle is used as an annotation.
	*
	**/
	virtual void computeAngle();

};

#endif // SOXIPANGLE_H
