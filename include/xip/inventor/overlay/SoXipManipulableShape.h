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
*	@file	SoXipManipulableShape.h
*	@brief	Base class for all manipulable shapes
*	@author	Julien Gein
**/

#ifndef SOXIPMANIPULABLESHAPE_H
#define SOXIPMANIPULABLESHAPE_H

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <xip/inventor/overlay/SoXipShape.h>

/**
*	@class SoXipManipulableShape
*
* Base class for all manipulable shapes
*
**/
class XIPIVOVERLAY_API SoXipManipulableShape : public SoXipShape
{
	SO_NODE_ABSTRACT_HEADER( SoXipManipulableShape );

	SO_XIP_KIT_ENTRY_HEADER( mMainSeparator );

	SO_XIP_KIT_TYPE_ENTRY_HEADER( mColor, SoMaterial );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mDrawStyle, SoDrawStyle );

	// Enumeration
	SO_XIP_KIT_ENTRY_HEADER( mEnumerationSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mEnumerationSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mEnumerationPickStyle );
	SO_XIP_KIT_ENTRY_HEADER( mEnumerationOffset );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mEnumerationText, SoXipText2 );

	// Text annotation
	SO_XIP_KIT_ENTRY_HEADER( mAnnotationSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mAnnotationSeparator );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mAnnotationTransform, SoMatrixTransform );
	SO_XIP_KIT_ENTRY_HEADER( mAnnotationOffset );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mAnnotation, SoXipEditText2 );

	// Top Separator	
	SO_XIP_KIT_ENTRY_HEADER( mTopSeparator );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mTransform, SoMatrixTransform );

	// Shadows
	SO_XIP_KIT_ENTRY_HEADER( mShadowSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mShadowSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mShadowMaterial );
	SO_XIP_KIT_ENTRY_HEADER( mShadowOffset );

	// Geometries
	SO_XIP_KIT_ENTRY_HEADER( mLinesSeparator );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mLinesCoords, SoCoordinate3 );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mLinesIndices, SoIndexedLineSet );

public:
	/// Constructor
	SoXipManipulableShape();

	/// Is the text anchored to the shape ?
	SoSFBool		textAnchored;
	/// Position of the text (world coordinates) if not anchored
	SoSFVec3f		textPosition;

	/// Open Inventor class initialization
	static void initClass();

	/// Is the mouse button pressed ?
	virtual SbBool isButtonPressed() const;

	/// Has the text been picked ?
	virtual SbBool isTextPicked() const;

	/// Is the text anchored (attached) to the shape, or does it have
	/// and independent position
	virtual SbBool isTextAnchored() const;

	/// Is the shape closed or opened?
	virtual SbBool isClosed() const;

	/// Get the view transform
	virtual const SbMatrix& getTransform() const;

	/**
	*	@brief	Add a transformation matrix in the view before the shape
	* geometries.
	*
	*	@param viewMatrix	transformation matrix
	*
	**/
	virtual void setViewTransform( const SbMatrix& viewMatrix );

	/**
	*	@brief	Apply the given transformation to the shape geometries
	*
	*	@param	matrix		transformation matrix
	*
	**/
	virtual void applyViewTransform( const SbMatrix& viewMatrix );
	virtual void transform( const SbMatrix& matrix ) = 0;

	/**
	*	@brief	Compute the shape in-plane bounding box
	*
	*	@param bbox		bounding box with attached transformation
	*
	**/
	virtual void computeXBoundingBox( SbXfBox3f& bbox );

	/**
	*	@brief	Invalidate the shape geometries.
	*
	* This will result in a call to updateGeometries in the next
	* rendering loop.
	*
	**/
	virtual void invalidateGeometries();	

	/**
	*	@brief	Callback for invalidating the shape geometries
	* (e.g a field sensor attached to one of the shape field will
	* be directed here)
	*
	**/
	static void invalidateGeometriesCB( void* userData, SoSensor* );
	
	/**
    *   @brief  Extract shape geometries
    *
    *   @param point		output array of points
    *   @param coordIndex	output array of point indices
    *   @param closed		is the shape closed?
    **/
	virtual void extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed ) = 0;

	static SbTime getDoubleClickTime()
	{
		return mDoubleClickTime;
	}

	static void setDoubleClickTime(SbTime time)
	{ 
		mDoubleClickTime = time;
	}

	virtual void editText();
	virtual void editText( SoHandleEventAction* action );

    /**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

	/**
    *   @brief  Callback function called after the shape creation
    *
    **/
	virtual void afterCreation();

protected:
	/// Destructor
	~SoXipManipulableShape();

	/**
	*	@brief	Extract the shape geometries based on the shape
	* characteristics.
	*
	**/
	virtual void updateGeometries();

	/**
	*	@brief update the annotation position and enumeration position
	* (see updateAnnotationPosition and updateEnumerationPosition)
	*
	**/
	virtual void updateViewDependentGeometries();	

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

	/**
	*	@brief	togle on/off the display of the shape enumeration
	*
	**/
	virtual void toggleEnumerationOnOff( SbBool flag );

	/**
	*	@brief	togle on/off the display of the shape annotation
	*
	**/
	virtual void toggleAnnotationOnOff( SbBool flag );

	virtual SbBool readInstance( SoInput *in, unsigned short );

	virtual void GLRender( SoGLRenderAction* action );

	virtual void handleEvent( SoHandleEventAction* action );

	virtual void rayPick( SoRayPickAction* action );

	/**
    *   @brief  Translate the shape by the given offset
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void translate( const SbVec3f& offset ) {}

    /**
    *   @brief  Send a Mouse Down event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseDown( const SbVec3f& pos ) {}

    /**
    *   @brief  Send a Mouse Move event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseMove( const SbVec3f& pos ) {}

    /**
    *   @brief  Send a Mouse Up event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseUp( const SbVec3f& pos ) {}

    /**
    *   @brief  Send a Mouse Double event to the shape
    *
    *   @param pos  projection of the mouse position in the view
    **/    
	virtual void mouseDouble( const SbVec3f& pos ) {}

	/// Should the shape enumeration be displayed ?
	SbBool					mShowEnumeration;
	/// Should the shape annotation be displayed ?
	SbBool					mShowAnnotation;
	/// Should the geometries be updated ?
	SbBool					mUpdateGeometries;
	/// Is the view initialized ?
	SbBool					mIsViewInitialized;
	/// Is the mouse button pressed ?
	SbBool					mIsButtonPressed;
	/// Is the shape currently being manipulated ?
	SbBool					mIsManipulated;
	/// Has the shape annotation been picked ?
	SbBool					mIsTextPicked;
	/// Has the shape enumeration been picked ?
	SbBool					mIsEnumPicked;
	/// Position of the mouse (screen coordinates) when the mouse button was pressed
	SbVec2s					mMouseDownPos;
	/// Time when the mouse button was pressed
	SbTime					mMouseDownTime;
	/// Position of the mouse (screen coordinates) when the mouse button was released
	SbVec2s					mMouseUpPos;
	/// Time when the mouse button was released
	SbTime					mMouseUpTime;
	/// Access to the handle event action
	SoHandleEventAction*	mHandleEventAction;
	/// is the space bar key pressed
	SbBool					mIsSpacePressed;
	/// Position when the space bar was hit
	SbVec3f					mSpacePosition;
	/// Distance beyond which two separate mouse clicks are interpreted as independant
	/// mouse down events
	static int				mDoubleClickMaxJump;
	/// Maximum time between two mouse clicks
	static SbTime			mDoubleClickTime;
	/// Time for one mouse click
	static SbTime			mClickTime;

};

#endif // SOXIPMANIPULABLESHAPE_H
