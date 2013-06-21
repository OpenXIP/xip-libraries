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
*  @file	SoXipContour.h
*  @brief	Declaration of the SoXipContour overlay node
*  @author	Julien Gein
**/

#ifndef SOXIPCONTOUR_H
#define SOXIPCONTOUR_H

#include "SoXipPolygon.h"

/**
*	@class SoXipContour
*
* This node is used to draw a free-hand contour in the current view.
* It is a permanent overlay. User may use multiple instances of this node
* to perform multiple measures, or use this class as a parameter of the
* overlay manager (cf. SoXipOverlayManager)
* 
* Points keep being added to the contour on Mouse Down. On Mouse Click, 
* SoXipContour inherits its behavior from SoXipPolygon.
*
* This overlay can be used as a base class for measurements.
*
*	@see SoXipOverlayManager
*
**/
class SoXipContour : public SoXipPolygon
{
	SO_NODE_HEADER( SoXipContour );

public:
    /// Constructor
	SoXipContour();

    /// Open Inventor class initialization
	static void initClass();

protected:
    /// Destructor
	~SoXipContour();

    /**
    *   @brief  Send a Mouse Move event to the ellipse
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseMove( const SbVec3f& pos );

    /**
	*	@brief	Can the contour be closed at the given position ?
	*
	* Tell wheter the cursor is close enough from the contour
    * starting point. If so, the user mouse position, gets anchored
    * to the starting point, and the contour can the be closed with
    * a Mouse Click.
	*
	*	@param pos		position
	**/
	virtual SbBool canClose( const SbVec3f& pos ) const;

};

#endif // SOXIPCONTOUR_H
