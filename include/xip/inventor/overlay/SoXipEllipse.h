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
*  @file	SoXipEllipse.h
*  @brief	Declaration of the SoXipEllipse overlay class
*  @author	Julien Gein
**/

#ifndef SOXIPELLIPSE_H
#define SOXIPELLIPSE_H

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/overlay/SoXipSubShape.h>


/**
*	@class SoXipEllipse
*
* This node is used to draw an ellipse in the current view.
* It is a permanent overlay. User may use multiple instances of this node
* to perform multiple measures, or use this class as a parameter of the
* overlay manager (cf. SoXipOverlayManager)
*
* This overlay can be used as a base class for measurements.
*
*	@see SoXipOverlayManager
*
**/
class XIPIVOVERLAY_API SoXipEllipse : public SoXipManipulableShape
{
	SO_NODE_HEADER( SoXipEllipse );

    /// Center
	SO_XIP_SHAPE_FIELD( center, SoSFVec3f );
    /// Horizontal radius vector
	SO_XIP_SHAPE_FIELD( a, SoSFVec3f );
    /// Vertical radius vector
	SO_XIP_SHAPE_FIELD( b, SoSFVec3f );
    /// Precision: how many points per circle quarter
	SO_XIP_SHAPE_FIELD( precision, SoSFShort );

public:
    /// Constructor
	SoXipEllipse();

    /// Open Inventor class initialization
	static void initClass();

    /**
    *   @brief  Returns wheter the shape is closed or not. Always true for an
    * ellipse.
    *
    *   @return true if the shape is closed, false otherwise
    **/
	virtual SbBool isClosed() const;

    /**
    *   @brief  Apply the given transformation
    *
    * The transformation is applied to the ellipse's center and the scale and
    * rotation extracted from the matrix are applied to the radius vectors.
    *
    *   @param  matrix  transformation matrix
    **/
    virtual void transform( const SbMatrix& matrix );
    
    /**
    *   @brief  Translate the shape by the given offset
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void translate( const SbVec3f& offset );

    /**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

    /**
    *   @brief  Extract shape geometries
    *
    * This method is called by the base class to retrieve the points and segments
    * defining the ellipse. 
    *
    *   @param point		output array of points
    *   @param coordIndex	output array of point indices
    *   @param closed		is the shape closed?
	*
    **/
	virtual void extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed );
	
protected:
    /// Destructor
	~SoXipEllipse();

    /**
    *   @brief  Send a Mouse Down event to the ellipse
    *
    *   @param pos  projection of the mouse position in the view
    **/
	virtual void mouseDown( const SbVec3f& pos );

    /**
    *   @brief  Send a Mouse Move event to the ellipse
    *
    *   @param pos  projection of the mouse position in the view
    **/
	virtual void mouseMove( const SbVec3f& pos );

    /**
    *   @brief  Send a Mouse Move event to the ellipse
    *
    *   @param pos  projection of the mouse position in the view
    **/    
    virtual void   mouseUp( const SbVec3f& pos );

    /// First point defined by the user, used to compute the ellipse's center
    /// and radius
	SbVec3f			mFirstPoint;
    /// Tell wheter the first point has been defined or not
	bool			mHasFirstPoint;

};

#endif // SOXIPELLIPSE_H
