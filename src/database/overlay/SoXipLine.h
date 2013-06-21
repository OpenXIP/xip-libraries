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
*	@file	SoXipLine.h
*	@brief	Declaration of the SoXipLine class
*	@author	Julien Gein
**/

#ifndef SOXIPLINE_H
#define SOXIPLINE_H

#include <Inventor/fields/SoSFVec3f.h>
#include "SoXipPolyLine.h"

/**
*	@class SoXipLine
*
* This node is used to create a line overlay in the current view.
* It is a permanent overlay. User may use multiple instances of this node
* to have as many lines as required, or use this class as a parameter
* of the overlay manager (cf. SoXipOverlayManager).
*
*	@see SoXipOverlayManager
*
**/
class SoXipLine : public SoXipPolyLine
{
	SO_NODE_HEADER( SoXipLine );

public:
	/// Constructor
	SoXipLine();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipLine();

	/**
	*	@brief	Implementation of the MouseDown event.
	*
	*	@param	pos			projection of the mouse position in 3D.
	**/
	virtual void mouseDown( const SbVec3f& pos );

	/**
	*	@brief	Implementation of the MouseUp event.
	*
	*	@param	pos			projection of the mouse position in 3D.
	**/
	virtual void mouseUp( const SbVec3f& pos );

	/**
	*	@brief	Implementation of the MouseDouble event.
	*
	*	@param	pos			projection of the mouse position in 3D.
	**/
	virtual void mouseDouble( const SbVec3f& pos );

};

#endif // SOXIPLINE_H
