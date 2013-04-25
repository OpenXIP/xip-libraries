/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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
