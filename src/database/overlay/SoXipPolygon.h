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
*	@file    SoXipPolygon.h
*	@brief   Declaration of the SoXipPolygon class
*	@author  Julien Gein
**/

#ifndef SOXIPPOLYGON_H
#define SOXIPPOLYGON_H

#define CLOSING_MIN_PIXEL_DISTANCE 6

#include <xip/inventor/overlay/SoXipEditableShape.h>

/**
*	@class SoXipPolygon
*
* This node is used to create a polygon.
* It is a permanent overlay. User may use multiple instances of this node
* to perform multiple measures, or use this class as a parameter of the
* overlay manager (cf. SoXipOverlayManager)
*
*	@see SoXipOverlayManager
*
**/
class SoXipPolygon : public SoXipEditableShape
{
	SO_NODE_HEADER( SoXipPolygon );

public:
	/// Constructor
	SoXipPolygon();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipPolygon();

	/**
    *   @brief  Translate the shape by the given offset
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void translate( const SbVec3f& offset );

    /**
    *   @brief  Send a Mouse Down event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseDown( const SbVec3f& pos );

    /**
    *   @brief  Send a Mouse Move event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseMove( const SbVec3f& pos );

    /**
    *   @brief  Send a Mouse Up event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseUp( const SbVec3f& pos );

    /**
    *   @brief  Send a Mouse Double event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseDouble( const SbVec3f& pos );

    /**
	*	@brief	Can the polygon be closed at the given position ?
	*
	* Tell wheter the cursor is close enough from the contour
    * starting point. If so, the user mouse position, gets anchored
    * to the starting point, and the contour can the be closed with
    * a Mouse Click.
	*
	*	@param pos		position
	**/
	virtual SbBool canClose( const SbVec3f& pos ) const;

	/// Is the polygon consistent ?
	virtual SbBool isConsistent() const;
};

#endif // SOXIPPOLYGON_H
