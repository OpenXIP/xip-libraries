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

#include <xip/system/standard.h>

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipDataImageElement.h>
#include "SoXipImageExaminerBase.h"

#include <algorithm>

SO_NODE_ABSTRACT_SOURCE( SoXipImageExaminerBase );

SoXipImageExaminerBase::SoXipImageExaminerBase()
{
	SO_NODE_CONSTRUCTOR( SoXipImageExaminerBase );

	SO_XIP_KIT_ADD_ENTRY( mCamera, SoOrthographicCamera, this );
	SO_XIP_KIT_ADD_ENTRY( mImageSwitch, SoSwitch, this );
	SO_XIP_KIT_ADD_ENTRY( mImage, SoXipImage, mImageSwitch );

	SO_NODE_DEFINE_ENUM_VALUE( ModeType, NONE );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, PANZOOM );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, SHIFT );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, SCROLL );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, SHIFTSCROLL );
	SO_NODE_SET_SF_ENUM_TYPE( mode, ModeType );

	SO_NODE_DEFINE_ENUM_VALUE( ScrollScopeType, ALL_IMAGES );
	SO_NODE_DEFINE_ENUM_VALUE( ScrollScopeType, CURRENT_IMAGE );
	SO_NODE_SET_SF_ENUM_TYPE( scrollScope, ScrollScopeType );

	SO_NODE_ADD_FIELD(       drawImage, (TRUE) );
	SO_NODE_ADD_FIELD(      imageIndex, (0) );
	SO_NODE_ADD_FIELD(   previousImage, () );
	SO_NODE_ADD_FIELD(       nextImage, () );
	SO_NODE_ADD_FIELD(      sliceIndex, (-1) );
	SO_NODE_ADD_FIELD(   previousSlice, () );
	SO_NODE_ADD_FIELD(       nextSlice, () );
	SO_NODE_ADD_FIELD(     scrollScope, (ALL_IMAGES) );
	SO_NODE_ADD_FIELD(         viewAll, () );
	SO_NODE_ADD_FIELD(    viewAllScale, (0.8) );
	SO_NODE_ADD_FIELD(            mode, (NONE) );
	SO_NODE_ADD_FIELD(			 plane, (SbMatrix::identity()));

	SoField* fields[6] = { &viewAll, &nextImage, &previousImage, &nextSlice, &previousSlice, &mode };
	for( int i = 0; i < 6; ++ i )
	{
		mFieldSensors[i] = new SoFieldSensor( &fieldSensorCB, this );
		mFieldSensors[i]->attach( fields[i] );
	}

	// Create a field sensor on the internal image to update the camera
	mImageSensor = new SoFieldSensor( &fieldSensorCB, this );
	mImageSensor->attach( (SoXipSFDataImage *) mImage->getField( SbName("image") ) );
	mImageSensor->setPriority(0);

	// Initialize the animation members to null
	mAnimate = FALSE;
	mAnimateStep = SbVec2f(0, 0);
	mAnimatePosition = SbVec2f(0, 0);
	mAnimateChange = 0;
	mAnimationSensor = 0;
	mShiftOrScroll = 0;
    mAnimateLock[0] = FALSE;
    mAnimateLock[1] = FALSE;

	mViewAll = TRUE;
	mPan = FALSE;
}

SoXipImageExaminerBase::~SoXipImageExaminerBase()
{
	for( int i = 0; i < 6; ++ i )
	{
		if( mFieldSensors[i] )
		{
			delete mFieldSensors[i];
			mFieldSensors[i] = 0;
		}
	}

	if( mImageSensor )
	{
		delete mImageSensor;
		mImageSensor = 0;
	}

	if( mAnimationSensor )
	{
		delete mAnimationSensor;
		mAnimationSensor = 0;
	}
}

void 
SoXipImageExaminerBase::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipImageExaminerBase, SoXipKit, "SoXipKit" );

	SO_ENABLE( SoGLRenderAction,		SoXipDataImageElement );
	SO_ENABLE( SoHandleEventAction,		SoXipDataImageElement );
	SO_ENABLE( SoRayPickAction,			SoXipDataImageElement );
}

void 
SoXipImageExaminerBase::animationSensorCB( void* userData, SoSensor* )
{
	((SoXipImageExaminerBase *) userData)->onAnimationTimer();
}

void 
SoXipImageExaminerBase::fieldSensorCB( void* userData, SoSensor* sensor)
{
	SoField* triggeredField = ((SoFieldSensor *) sensor)->getAttachedField();

	((SoXipImageExaminerBase*) userData)->inputChanged( triggeredField );
}

void 
SoXipImageExaminerBase::inputChanged( SoField* whichField )
{
	// Displayed image (or image used to configure the camera)
	if( whichField == (SoXipSFDataImage *) mImage->getField( SbName("image") ) )
	{
		// After switching to a different image, reposition the camera
		updateCamera();
	}

	// View all flag
	else if( whichField == &viewAll )
	{
		mViewAll = TRUE;	
	}

	// Previous image sensor
	else if( whichField == &previousImage )
	{
		decreaseImageIndex(1);
	}

	// Next image sensor
	else if( whichField == &nextImage )
	{
		increaseImageIndex(1);
	}

	// Previous slice sensor
	else if( whichField == &previousSlice )
	{
		decreaseSliceIndex(1);
	}

	// Next slice sensor
	else if( whichField == &nextSlice )
	{
		increaseSliceIndex(1);
	}

	// Stop the animation when user switches between modes
	else if( whichField == &mode )
	{
		if( mAnimate )
			stopAnimation();
	}
}

void
SoXipImageExaminerBase::onAnimationTimer()
{
	if( mode.getValue() == SHIFT || mode.getValue() == SCROLL || mode.getValue() == SHIFTSCROLL )
	{
		SbBool forward[2];
		forward[0] = mAnimateStep[0] >= 0;
		forward[1] = mAnimateStep[1] >= 0;

		SbVec2f abs_step;
		abs_step[0] = fabs( mAnimateStep[0] );
		abs_step[1] = fabs( mAnimateStep[1] );
		
		if (abs_step[0] <= 0 || abs_step[1] <= 0)
		{
			SoDebugError::postInfo(__FILE__, "Animate step must be strictly positive");
			return;
		}
        
        if( mode.getValue() == SHIFTSCROLL && !mAnimateLock[0] && !mAnimateLock[1] )
		{
			float ratio = abs_step[0] / abs_step[1];

			if( ratio < 0.2 )
				mAnimateLock[1] = TRUE;
			else if( ratio > 5 )
				mAnimateLock[0] = TRUE;
		}

		SbVec2f newPosition = mAnimatePosition;
		newPosition[0] += abs_step[0];
		newPosition[1] += abs_step[1];

        SbVec2s inc;
		inc[0] = (int) newPosition[0] - (int) mAnimatePosition[0];
		inc[1] = (int) newPosition[1] - (int) mAnimatePosition[1];

		if( (mShiftOrScroll == 1) && !mAnimateLock[1] && inc[0] > 0 )
		{
			if( forward[0] )
				increaseImageIndex( inc[0] );
			else
				decreaseImageIndex( inc[0] );
		}
		if( (mShiftOrScroll == 2) && !mAnimateLock[0] && inc[1] > 0 )
		{
			if( forward[1] )
				increaseSliceIndex( inc[1] );
			else
				decreaseSliceIndex( inc[1] );
		}

		mAnimatePosition = newPosition;
	}
	else
	{
		stopAnimation();
	}
}

void 
SoXipImageExaminerBase::startAnimation( const SbVec2f& step )
{
	mAnimate = TRUE;
	mAnimatePosition = SbVec2f(0, 0);
	mAnimateStep = step;
	
	if( !mAnimationSensor )
	{
		mAnimationSensor = new SoTimerSensor( animationSensorCB, this );
		mAnimationSensor->setInterval( .05 );
	}

	mAnimationSensor->schedule();
}

void 
SoXipImageExaminerBase::stopAnimation()
{
	mAnimate = FALSE;
	mAnimatePosition = SbVec2f(0, 0);
	mAnimateStep = SbVec2f(0, 0);
	mAnimateChange = 0;

	if( mAnimationSensor )
		mAnimationSensor->unschedule();
}

void 
SoXipImageExaminerBase::increaseImageIndex( int count )
{
	int numImage = getNumImages();
	int currentImage = imageIndex.getValue();
	imageIndex.setValue(std::min( numImage - 1, currentImage + count ) );

	int numOfSlices = getNumSlices( imageIndex.getValue() );
	if( sliceIndex.getValue() >= numOfSlices )
	{
		sliceIndex.setValue( numOfSlices - 1 );
	}
}

void 
SoXipImageExaminerBase::decreaseImageIndex( int count )
{
	int currentImage = imageIndex.getValue();
	imageIndex.setValue( currentImage - count > 0 ? currentImage - count : 0 );	

	int numOfSlices = getNumSlices( imageIndex.getValue() );	
	if( sliceIndex.getValue() >= numOfSlices )
	{
		sliceIndex.setValue( numOfSlices - 1 );
	}
}

void 
SoXipImageExaminerBase::increaseSliceIndex( int count )
{
	int newSliceIndex = sliceIndex.getValue();
	int newImageIndex = imageIndex.getValue();

	if( newImageIndex < 0 || newImageIndex >= static_cast<int>(getNumImages()) ||
		newSliceIndex < 0 || newSliceIndex >= static_cast<int>(getNumSlices( newImageIndex )) )
	{
		SoDebugError::post( __FILE__, "Invalid index" );
		return ;
	}

	while( count > 0 )
	{
		if( newSliceIndex < static_cast<int>(getNumSlices( newImageIndex )) - 1 )
			++ newSliceIndex;

		else if (scrollScope.getValue() == ALL_IMAGES)
		{			
			// If in LOOP mode, look if there any image after we
			// could switch to (and load its first slice)
			if( newImageIndex < static_cast<int>(getNumImages()) - 1 )
			{
				++ newImageIndex;
			}
			else
			{
				newImageIndex = 0;			
			}

			newSliceIndex = 0;
		}

		-- count;
	}

	if( imageIndex.getValue() != newImageIndex )
		imageIndex.setValue( newImageIndex );

	sliceIndex.setValue( newSliceIndex );
}

void 
SoXipImageExaminerBase::decreaseSliceIndex( int count )
{
	int newSliceIndex = sliceIndex.getValue();
	int newImageIndex = imageIndex.getValue();

	if( newImageIndex < 0 || newImageIndex >= static_cast<int>(getNumImages()) ||
		newSliceIndex < 0 || newSliceIndex >= static_cast<int>(getNumSlices( newImageIndex )) )
	{
		SoDebugError::post( __FILE__, "Invalid index" );
		return ;
	}

	while( count > 0 )
	{
		if( newSliceIndex > 0 )
			-- newSliceIndex;

		else if (scrollScope.getValue() == ALL_IMAGES)
		{			
			// If in LOOP mode, look if there any image before we
			// could switch to (and load its last slice)
			if( newImageIndex > 0 )
			{
				-- newImageIndex;
			}
			else
			{
				newImageIndex = static_cast<int>(getNumImages()) - 1;
			}
			
			newSliceIndex = static_cast<int>(getNumSlices( newImageIndex )) - 1;
		}

		-- count;
	}

	if( imageIndex.getValue() != newImageIndex )
		imageIndex.setValue( newImageIndex );

	sliceIndex.setValue( newSliceIndex );
}

SoOrthographicCamera* 
SoXipImageExaminerBase::getCamera()
{
	return (SoOrthographicCamera *) mCamera;
}

void 
SoXipImageExaminerBase::updateCamera()
{
	SoXipDataImage* xipImage = ((SoXipSFDataImage *)mImage->getField(SbName("image")))->getValue();
	if( !xipImage )
		return ;

	SbXipImage* image = xipImage->get();
	if( image )
	{
		SbVec3f newImagePos = image->getModelMatrix()[3];
		SbVec3f oldImagePos = mImageModelMatrix[3];

		SbVec3f cameraTranslation = (newImagePos - oldImagePos);

		getCamera()->position.setValue( getCamera()->position.getValue() + cameraTranslation );
		
		mImageModelMatrix = image->getModelMatrix();
	}

	updatePlane();
}

void 
SoXipImageExaminerBase::adjustCamera( SoGLRenderAction*, const SbMatrix& model )
{
	SbVec3f imageAxis[3];
	imageAxis[0] = model[0];
	imageAxis[1] = model[1];
	imageAxis[1].negate();
	imageAxis[2] = imageAxis[0].cross( imageAxis[1] );

	float width  = imageAxis[0].length();
	float height = imageAxis[1].length();

	SbRotation rotation = SbRotation( SbVec3f(0, 0, -1), -imageAxis[2] );
	getCamera()->orientation.setValue( rotation );

	SbMatrix orientationMatrix;
	orientationMatrix = getCamera()->orientation.getValue();
	tiltCamera( SbRotation( orientationMatrix[1], imageAxis[1] ) );

	getCamera()->viewAll( mImage, mViewport );
	getCamera()->height = ( width > height ? width : height ) / viewAllScale.getValue();

	const float d = 2.0;
	SbVec3f imageCenter = model[3] + imageAxis[0] / d - imageAxis[1] / d;
	float focalDistance = (getCamera()->position.getValue() - imageCenter).length();

	SbVec3f diff = (getCamera()->position.getValue() - imageCenter) / focalDistance;
		
	getCamera()->position.setValue( imageCenter );

	getCamera()->focalDistance.setValue( 0 );
	getCamera()->nearDistance.setValue( -1 );
	getCamera()->farDistance.setValue( 1. );
	
	updatePlane();
}


void 
SoXipImageExaminerBase::updatePlane()
{
	// update mpr plane
	SbMatrix matrix = mImageModelMatrix;

	// when using get/setTransform, the rotation is derived from normal vector
	// but for gantry tilt, we need to compute normal from row and column vector
	SbVec3f rot[3];
	rot[0] = SbVec3f(matrix[0][0], matrix[0][1], matrix[0][2]);
	rot[1] = SbVec3f(matrix[1][0], matrix[1][1], matrix[1][2]);
	rot[2] = rot[0].cross(rot[1]);

	rot[0].normalize();
	rot[1].normalize();
	rot[2].normalize();

	float h = getCamera()->height.getValue();
	rot[0] *= h;
	rot[1] *= h;
	rot[2] *= h;

	SbVec3f p = getCamera()->position.getValue();
	matrix = SbMatrix(
		rot[0][0], rot[0][1], rot[0][2], 0,
		rot[1][0], rot[1][1], rot[1][2], 0,
		rot[2][0], rot[2][1], rot[2][2], 0,
		p[0], p[1], p[2], 1);

	// flip default viewing direction: the view direction must point to the 
	// opposite direction of the normal of the image
	SbMatrix tmp = SbMatrix::identity();
	tmp.setRotate(SbRotation(SbVec3f(1, 0, 0), M_PI));
	matrix = tmp * matrix;

	plane.setValue(matrix);
}

void 
SoXipImageExaminerBase::tiltCamera( const SbRotation& rot )
{
	SbMatrix m;
	m = getCamera()->orientation.getValue();

	SbVec3f camy;
	rot.multVec( SbVec3f( m[1][0], m[1][1], m[1][2] ), camy );
	m[1][0] = camy[0];
	m[1][1] = camy[1];
	m[1][2] = camy[2];
	
	SbVec3f camx;
	rot.multVec( SbVec3f( m[0][0], m[0][1], m[0][2] ), camx );
	m[0][0] = camx[0];
	m[0][1] = camx[1];
	m[0][2] = camx[2];

	getCamera()->orientation.setValue( SbRotation(m) );
}

void 
SoXipImageExaminerBase::GLRender( SoGLRenderAction* action )
{
	SbXipImage* image = 0;

	if (!mImage)
		return;

	SoField* imageField = mImage->getField( SbName("image") );

	if (!imageField)
		return;

	SoXipDataImage* dataImage = ((SoXipSFDataImage *) imageField)->getValue();
	if( dataImage )
		image = dataImage->get();

	if( mViewAll && image )
	{
		adjustCamera( action, image->getModelMatrix() );
		
		// Store the information of the current displayed image
		mImageModelMatrix = image->getModelMatrix();

		mViewAll = FALSE;
	}

	// Set the Image Element
	setElement( action );

	if (mImageSwitch)
	{
		mImageSwitch->enableNotify( FALSE );
		((SoSFInt32 *) mImageSwitch->getField(SbName("whichChild")))->setValue( drawImage.getValue() ? 0 : -1 );
		mImageSwitch->enableNotify( TRUE );
	}
	
	SoXipKit::GLRender( action );
}

void 
SoXipImageExaminerBase::rayPick( SoRayPickAction* action )
{
	// Set the Image Element
	setElement( action );

	action->getState()->push();
	action->traverse( getCamera() );
	
	action->setObjectSpace();

	const SbViewVolume& viewVolume = getCamera()->getViewVolume();
	const SbLine& line = action->getLine();

	// Intersect the focal plane with the picking ray
	SbPlane plane = viewVolume.getPlane(-0.0001f);

	SbVec3f intersection;
	if( plane.intersect( line, intersection ) )
		action->addIntersection( intersection );
	
	action->getState()->pop();

	SoXipKit::rayPick( action );
}

void 
SoXipImageExaminerBase::handleEvent( SoHandleEventAction* action )
{
	// Set the Image Element
	setElement( action );

	// Call base class first
	SoXipKit::handleEvent( action );
	if( action->isHandled() )
		return ;

	// Save the view information (so we can have access to it
	// while the event is grabbed)
	saveViewInformation( action );

	const SoEvent* event = action->getEvent();
	if( !event )
		return ;
	
	if( mode.getValue() == NONE )
		return ;

	if( SO_MOUSE_PRESS_EVENT( event, BUTTON1 ) &&
        !action->getEvent()->wasCtrlDown() &&
        !action->getEvent()->wasShiftDown() &&
		!action->getEvent()->wasAltDown() )
	{
		// Stop the animation as soon as we get a mouse down event
		stopAnimation();

		mLastMousePosition = event->getNormalizedPosition( mViewport );

		action->setHandled();
		action->setGrabber( this );

		mPan = SbBox2f(0.2, 0.2, 0.8, 0.8).intersect( mLastMousePosition );
	}
	else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		SbVec2f mousePos = event->getNormalizedPosition( mViewport );

		if( action->getGrabber() != this )
		{
			if( mousePos[0] >= 0 && mousePos[0] <= 1.f &&
				mousePos[1] >= 0 && mousePos[1] <= 1.f )
			{
				if( mode.getValue() == SHIFT )
				{
					SoXipCursor::setCursor( "SHIFT" );
				}
				else if( mode.getValue() == SCROLL )
				{
					SoXipCursor::setCursor( "SCROLL" );
				}
				else if( mode.getValue() == SHIFTSCROLL )
				{
					SoXipCursor::setCursor( "SHIFTSCROLL" );
				}
				else if( mode.getValue() == PANZOOM )
				{
					SbBox2f panBox( 0.2, 0.2, 0.8, 0.8 );
					if( panBox.intersect( event->getNormalizedPosition( mViewport ) ) )
						SoXipCursor::setCursor( "SEL_PAN" );
					else
						SoXipCursor::setCursor( "SEL_ZOOM" );
				}
				
				action->setHandled();
			}
		}
		else if( mode.getValue() == PANZOOM )
		{
			if( mPan )
			{
				// The user starts dragging in the center of the image
				// Apply a translation to the view matrix
				//				
				SbVec3f pos1 = mPlaneProj.project( mousePos );
				SbVec3f pos2 = mPlaneProj.project( mLastMousePosition );

				getCamera()->position.setValue( getCamera()->position.getValue() - pos1 + pos2 );

				mLastMousePosition = mousePos;

				SoXipCursor::setCursor( "SEL_PAN" );				
			}
			else
			{
				// The user starts dragging from the view border
				// Apply a zoom factor to the image
				//
				getCamera()->scaleHeight( 1.f + ( mLastMousePosition[1] - mousePos[1] ) );

				mLastMousePosition = mousePos;

				SoXipCursor::setCursor( "SEL_ZOOM" );
			}

			action->setHandled();
		}
		else if( mode.getValue() == SHIFT || mode.getValue() == SCROLL || mode.getValue() == SHIFTSCROLL )
		{
			SbVec2f step(0, 0);

			if( mode.getValue() == SHIFT || mode.getValue() == SHIFTSCROLL )
			{
				step[1] = ( mousePos[1] - mLastMousePosition[1] ) * (float) mViewport.getViewportSizePixels()[1] / 200.;
			}
			if( mode.getValue() == SCROLL || mode.getValue() == SHIFTSCROLL )
			{
				step[0] = ( mousePos[0] - mLastMousePosition[0] ) * (float) mViewport.getViewportSizePixels()[0] / 200.;
			}
			if (mShiftOrScroll == 0 && mode.getValue() == SHIFTSCROLL)
			{
				mShiftOrScroll = (fabs(step[0]) > fabs(step[1])) ? 1 : 2;
			}

			// Change in direction: stop
			if( !mAnimateLock[0] && mAnimateStep[1] < 0 && step[1] > 0 ||
				!mAnimateLock[0] && mAnimateStep[1] > 0 && step[1] < 0 ||
				!mAnimateLock[1] && mAnimateStep[0] < 0 && step[0] > 0 ||
				!mAnimateLock[1] && mAnimateStep[0] > 0 && step[0] < 0 )
			{
				// Change in direction: stop
				stopAnimation();
				mAnimateChange = 10;
			}
			else 
			{
				if( mAnimateStep[1] == 0 && mAnimateStep[0] == 0 )
				{
					if( mAnimateChange <= 0 )
					{
						// Start new shift
						startAnimation( step );
					}
					else
						-- mAnimateChange;
				}
				else
				{
					// Speed up a little
					mAnimateStep += step;
				}
			}

			mLastMousePosition = mousePos;
			action->setHandled();
			
			if( mode.getValue() == SHIFT )
				SoXipCursor::setCursor( "SHIFT" );
			else if( mode.getValue() == SCROLL )
				SoXipCursor::setCursor( "SCROLL" );
			else if( mode.getValue() == SHIFTSCROLL )
				SoXipCursor::setCursor( "SHIFTSCROLL" );
		}
	}
	else if( SO_MOUSE_RELEASE_EVENT( event, BUTTON1 ) && action->getGrabber() == this ) 
	{
		stopAnimation();
        
        // Keep lock until mouse is released
        mAnimateLock[0] = FALSE;
        mAnimateLock[1] = FALSE;
		mShiftOrScroll = 0;

		action->releaseGrabber();
		action->setHandled();
	}
}

void 
SoXipImageExaminerBase::setElement( SoAction* action )
{
	SoXipDataImage* imageData = ((SoXipSFDataImage *) mImage->getField(SbName("image")))->getValue();

	SoXipDataImageElement::set( action->getState(), imageData,
		imageIndex.getValue(),
		sliceIndex.getValue(),
		getNumImages(),
		getNumSlices( imageIndex.getValue() ) );
}

void 
SoXipImageExaminerBase::saveViewInformation( SoHandleEventAction* action )
{
	SoState* state = action->getState();

	if( state && !action->getGrabber() )
	{
		mViewVolume		= SoViewVolumeElement::get( state );
		mViewport		= SoViewportRegionElement::get( state );

		float distance = mViewVolume.getDepth() / 2.f;
		mPlaneProj.setViewVolume( mViewVolume );
		mPlaneProj.setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + distance ) );
	}
}

