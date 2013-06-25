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
*	@file    SoXipRectangle.h
*	@brief   Declaration of the SoXipRectangle class
*	@author  Julien Gein
**/

#ifndef SOXIPRECTANGLE_H
#define SOXIPRECTANGLE_H

#include <Inventor/fields/SoSFVec3f.h>
#include <xip/inventor/overlay/SoXipSubShape.h>


/**
*	@class SoXipRectangle
*
* This node is used to create a rectangle.
* It is a permanent overlay. User may use multiple instances of this node
* to perform multiple measures, or use this class as a parameter of the
* overlay manager (cf. SoXipOverlayManager)
*
*	@see SoXipOverlayManager
*
**/
class SoXipRectangle : public SoXipManipulableShape
{
	SO_NODE_HEADER( SoXipRectangle );

	// Rectangle coordinates
	SO_XIP_SHAPE_FIELD( p0, SoSFVec3f );
	SO_XIP_SHAPE_FIELD( p1, SoSFVec3f );
	SO_XIP_SHAPE_FIELD( p2, SoSFVec3f );
	SO_XIP_SHAPE_FIELD( p3, SoSFVec3f );

public:
	/// Constructor
	SoXipRectangle();

	/// Open Inventor class initialization
	static void initClass();

	/// Is the shape closed ? (always true for rectangle)
	virtual SbBool isClosed() const;

	/// Transform the rectangle coordinates by the given transformation
	/// matrix
	virtual void transform( const SbMatrix& matrix );

    /**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

    /**
    *   @brief  Extract the shape geometries
    *
    * This method is called by the base class to retrieve the segments
    * defining the rectangle 
    *
    *   @param point		output array of points
    *   @param coordIndex   output array of point indices
    *   @param closed		is the shape closed?
    **/
	virtual void extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed );

protected:
	/// Destructor
	~SoXipRectangle();

	/**
    *   @brief  Translate the shape by the given offset
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void translate( const SbVec3f& offset );

    /**
    *   @brief  Send a Mouse Down event to the rectangle
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseDown( const SbVec3f& pos );

    /**
    *   @brief  Send a Mouse Move event to the rectangle
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseMove( const SbVec3f& pos );

    /**
    *   @brief  Send a Mouse Up event to the rectangle
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseUp( const SbVec3f& pos );

	/// First point defined by the user, used to backup the rectangle's center
    /// for when the CTRL key is pressed
	SbVec3f			mFirstPoint;
    
	/// Has the first point already been defined ?
	bool			mHasFirstPoint;

};

#endif // SOXIPRECTANGLE_H
