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
*	@file	SoXipEditableShape.h
*	@brief	Base class for all editable shapes
*	@author	Julien Gein
**/

#ifndef SOXIPEDITABLESHAPE_H
#define SOXIPEDITABLESHAPE_H

#include <xip/inventor/overlay/SoXipSubShape.h>
#include  <xip/inventor/overlay/xipivoverlay.h>
/**
*	@class SoXipEditableShape
*
* Base class for all editable shapes
*
**/
class XIPIVOVERLAY_API SoXipEditableShape : public SoXipManipulableShape
{
	SO_NODE_ABSTRACT_HEADER( SoXipEditableShape );

	SO_XIP_KIT_ENTRY_HEADER( mControlPointsSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mControlPointsSeparator );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mControlPointsCoords, SoCoordinate3 );
	SO_XIP_KIT_ENTRY_HEADER( mControlPointsStyle );
	SO_XIP_KIT_ENTRY_HEADER( mControlPointsSet );
    
	// List of editable points
    SO_XIP_SHAPE_FIELD( point, SoMFVec3f );
	// Is the shape opened or closed ?
    SO_XIP_SHAPE_FIELD( closed, SoSFBool );

public:
	/// Constructor
	SoXipEditableShape();

	/// should the shape be closed on double click?
	SoSFBool			closeOnDblClick;

	/// Open Inventor class initialization
	static void initClass();

	/// is the shape opened or closed?
	virtual SbBool isClosed() const;

	/**
	*	@brief	Extract the shape geometries based on the shape
	* characteristics.
	*
	**/
	virtual void updateGeometries();

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

	/// Apply the given transformation to the editable points
	virtual void transform( const SbMatrix& matrix );

	/// Pick a control point. Return its id.
	virtual int  pickControlPoint( SoHandleEventAction* action );

	/// Add a control point on the editable shape
	virtual void addPoint( SoNode* node, const SbVec2s& screenPt );

	/// Delete a control point from the editable shape at given position
	virtual void deletePoint( int id );

    /**
    *   @brief  Callback function called before the shape editing
    *
    **/
	virtual void startEditing();

    /**
    *   @brief  Callback function called after the shape editing
    *
    **/
	virtual void finishEditing();

    /**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();
	
    /**
    *   @brief  Extract the shape geometries
    *
    * This method is called by the base class to retrieve the points and segments
    * defining the shape. 
    *
    *   @param point			output array of points
    *   @param coordIndex		output array of point indices
	*	@param closed			is the shape closed?
	*
    **/
	virtual void extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed );

protected:
	/// Destructor
	~SoXipEditableShape();

	/// Event handler method
	virtual void handleEvent( SoHandleEventAction* action );

	/// return wheter a point belong to the contour or not
	virtual bool belongsToContour( const SbVec3f& worldPt, int &id );
	
	/**
    *   @brief  Map a displayed line index to its preceding control point.
	*
    * This method is called when the shape is edited and a control point
	* needs to be added. The editor only knows about the extracted point, not
	* the control points.
    *
    *   @param id	index 
	*
	*	@return	index of the preceding control point
	**/
	virtual int  getPreviousControlPoint( int id ) const;

    /**
    *   @brief  Extract control points that are used to edit the shape
    *
    *   @param points   output array of points
    **/
	virtual void extractControlPoints( SoMFVec3f& points );

	/// Picked shape
	SoXipShape*			mPickedShape;
	/// Id of the control point picked
	int					mControlPointId;

};

#endif // SOXIPEDITABLESHAPE_H
