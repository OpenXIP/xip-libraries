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
*	@file    SoXipPoint.h
*	@brief   Declaration of the SoXipPoint class
*	@author  Julien Gein
**/


#ifndef SOXIPPOINT_H
#define SOXIPPOINT_H

#include <xip/inventor/overlay/SoXipHandlerShape.h>

/**
*	@class SoXipPoint
*
* This node is used to create a point.
* It is a permanent overlay. User may use multiple instances of this node
* to perform multiple measures, or use this class as a parameter of the
* overlay manager (cf. SoXipOverlayManager)
*
*	@see SoXipOverlayManager
*
**/
class SoXipPoint : public SoXipHandlerShape
{
	SO_NODE_HEADER( SoXipPoint );

	SO_XIP_KIT_ENTRY_HEADER( mPointSeparator );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mPointCoords, SoCoordinate3 );
	SO_XIP_KIT_ENTRY_HEADER( mPointStyle );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mPointIndices, SoIndexedLineSet );

	// Point
    SO_XIP_SHAPE_FIELD( point, SoMFVec3f );

public:
	/// Constructor
	SoXipPoint();

	/// Open Inventor class initialization
	static void initClass();

    /**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

	/**
    *	@brief Callback triggered when one handler point is being moved by a
    * a SoXipOverlayHandlerManip.
    *
    *	@param id        index of the handler point being moved
    *	@param newPos    new position of the handler point
    **/
	virtual void moveHandlerPoint( int id, const SbVec3f& newPos );

	/// Transform the point by the given transformation
	/// matrix
	virtual void transform( const SbMatrix& matrix );

    /**
    *   @brief  Extract shape geometries
    *
    * This method is called by the base class to retrieve the points and segments
    * defining the shape. 
    *
    *   @param point		output array of points
    *   @param coordIndex	output array of point indices
    *   @param closed		is the shape closed?
	*
    **/
	virtual void extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed );

protected:
	/// Destructor
	~SoXipPoint();

	/// Rendering method
	virtual void GLRender( SoGLRenderAction* action );

    /**
    *   @brief  Send a Mouse Down event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseDown( const SbVec3f& pos );

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

#endif // SOXIPPOINT_H
