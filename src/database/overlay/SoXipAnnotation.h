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
*	@file	SoXipAnnotation.h
*	@brief	Node to annotate an object in the current view.
*	@author	Julien Gein
**/

#ifndef SOXIPANNOTATION_H
#define SOXIPANNOTATION_H

#include <Inventor/fields/SoSFFloat.h>
#include "SoXipLine.h"

/**
*   @class SoXipAnnotation
*
* This node is used to annotate an object in the current view.
* It is a permanent overlay. User may use multiple instances of this node
* to have as many annotations as required, or use this class as a parameter
* of the overlay manager (cf. SoXipOverlayManager).
*
*   @see SoXipOverlayManager
*
**/
class SoXipAnnotation : public SoXipLine
{
	SO_NODE_HEADER( SoXipAnnotation );

	SO_XIP_KIT_ENTRY_HEADER( mArrowSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mArrowTransform );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mArrowCoords, SoCoordinate3 );
	SO_XIP_KIT_ENTRY_HEADER( mLinesStyle );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mArrowIndices, SoIndexedLineSet );	

	SO_XIP_SHAPE_FIELD( angle, SoSFFloat );
	SO_XIP_SHAPE_FIELD( length, SoSFFloat );

public:
    /// Constructor
	SoXipAnnotation();

    /// Open Inventor class initialization
	static void initClass();

    /**
    *   @brief  Set temporary a transformation
    *
    *   @param  matrix  transformation matrix
    **/
	virtual void setViewTransform( const SbMatrix& viewMatrix );

    /**
    *   @brief  Apply the given transformation
    *
    *   @param  matrix  transformation matrix
    **/
	virtual void transform( const SbMatrix& matrix );

    /**
    *   @brief  Compute the position of the enumeration
    *
    *   @param  position    computed position
    **/
	virtual void updateEnumerationPosition( SoSFVec3f& position );

    /**
    *   @brief  Compute the position of the shape annotation
    *
    *   @param  position    computed position
    **/
    virtual void updateAnnotationPosition( SoSFVec3f& position );

	/**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

protected:
    /// Destructor
	~SoXipAnnotation();

    /**
    *   @brief  Send a Mouse Up event to the annotation
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseUp( const SbVec3f& pos );

	/// Rendering method
	virtual void GLRender( SoGLRenderAction* action );

private:
    /**
    *   @brief  Callback triggered when the text has been edited
    *
    *   @param userData     user data
    **/    
	static void finishTextEditingCB( void* userData, SoSensor* );

    /// Sensor triggered when the text has been edited
	SoFieldSensor*	mFinishTextEditingSensor;

};

#endif // SOXIPANNOTATION_H
