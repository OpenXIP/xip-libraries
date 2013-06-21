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
*	@file    SoXipPolyLine.h
*	@brief   Declaration of the SoXipPolyLine class
*	@author  Julien Gein
**/

#ifndef SOXIPPOLYLINE_H
#define SOXIPPOLYLINE_H

#include <Inventor/fields/SoMFVec3f.h>
#include <xip/inventor/overlay/SoXipHandlerShape.h>

/**
*	@class SoXipPolyLine
*
* This node is used to create a set of connected lines.
* It is a permanent overlay. User may use multiple instances of this node
* to perform multiple measures, or use this class as a parameter of the
* overlay manager (cf. SoXipOverlayManager)
*
*	@see SoXipOverlayManager
*
**/
class SoXipPolyLine : public SoXipHandlerShape
{
	SO_NODE_HEADER( SoXipPolyLine );
    
	// List of points
    SO_XIP_SHAPE_FIELD( point, SoMFVec3f );

public:
	/// Constructor
	SoXipPolyLine();

	/// Open Inventor class initialization
	static void initClass();

    /**
    *   @brief  Translate the shape by the given offset
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void translate( const SbVec3f& offset );

    /**
    *   @brief  Extract the shape geometries
    *
    * This method is called by the base class to retrieve the segments
    * defining the polyline. 
    *
    *   @param point		output array of points
    *   @param coordIndex   output array of point indices
    *   @param closed		is the shape closed?
	*
    **/
	virtual void extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed );

    /**
    *	@brief Callback triggered when one handler point is being moved by a
    * a SoXipOverlayHandlerManip.
    *
    *	@param id        index of the handler point being moved
    *	@param newPos    new position of the handler point
    **/
	virtual void moveHandlerPoint( int id, const SbVec3f& newPos );

    /**
    *   @brief  Apply the given transformation
	*
    *   @param  matrix  transformation matrix
    **/
	virtual void transform( const SbMatrix& matrix );

    /**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

protected:
	/// Destructor
	~SoXipPolyLine();

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
	*	@brief	Compute the position of the annotation
	*
	*	@param	computed position
	*
	**/
	virtual void updateAnnotationPosition( SoSFVec3f& position );

	/**
	*	@brief	Compute the position of the enumeration
	*
	*	@param	computed position
	*
	**/
	virtual void updateEnumerationPosition( SoSFVec3f& position );

};

#endif // SOXIPPOLYLINE_H
