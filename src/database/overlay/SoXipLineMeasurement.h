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
*	@file	SoXipLineMeasurement.h
*	@brief	Declaration of the SoXipLineMeasurement class
*	@author	Julien Gein
**/

#ifndef SOXIPLINEMEASUREMENT_H
#define SOXIPLINEMEASUREMENT_H

#include "SoXipLine.h"

/**
*	@class SoXipLineMeasurement
*
* This node is used to perform a distance measurement in the current view.
* It is a permanent overlay. User may use multiple instances of this node
* to have as many distance lines as required, or use this class as a
* parameter of the overlay manager (cf. SoXipOverlayManager).
*
*	@see SoXipOverlayManager
*
**/
class SoXipLineMeasurement : public SoXipLine
{
	SO_NODE_HEADER( SoXipLineMeasurement );

public:
    /// Constructor
	SoXipLineMeasurement();

    /// Open Inventor class initialization
	static void initClass();

protected:
    /// Destructor
	~SoXipLineMeasurement();
    
	/**
	*	@brief	Implementation of the MouseMove event.
	*
	*	@param	pos			projection of the mouse position in 3D.
	**/
	virtual void mouseMove( const SbVec3f& pos );

    /**
    *	@brief Callback triggered when one handler point is being moved by a
    * a SoXipOverlayHandlerManip.
    *
    *	@param id        index of the handler point being moved
    *	@param newPos    new position of the handler point
    **/
	virtual void moveHandlerPoint( int id, const SbVec3f& newPos );
};

#endif //  SoXipLineMeasurement_H
