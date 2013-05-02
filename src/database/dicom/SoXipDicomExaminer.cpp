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

#include "SoXipDicomExaminer.h"

#include <dcmtk/dcmdata/dctk.h>

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/dicom/SoXipSFDatadicom.h>
#include <xip/inventor/core/SoXipDataImageElement.h>
#include <xip/inventor/dicom/SoXipDataDicomElement.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>

#include "SoXipConvertDicom.h"
#include "SoXipDicomExtractSlice.h"

SO_NODE_SOURCE( SoXipDicomExaminer );

SoXipDicomExaminer::SoXipDicomExaminer()
{
	SO_NODE_CONSTRUCTOR( SoXipDicomExaminer );

	SO_XIP_KIT_ADD_ENTRY( mCamera, SoOrthographicCamera, this );
	SO_XIP_KIT_ADD_ENTRY( mImageSwitch, SoSwitch, this );
	SO_XIP_KIT_ADD_ENTRY( mImage, SoXipImage, mImageSwitch );

	SO_NODE_DEFINE_ENUM_VALUE( ModeType, NONE );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, PANZOOM );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, SHIFT );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, SCROLL );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, SHIFTSCROLL );
	SO_NODE_SET_SF_ENUM_TYPE( mode, ModeType );

	SO_NODE_ADD_FIELD(       drawImage, (TRUE) );
	SO_NODE_ADD_FIELD(          images, (0) );
	SO_NODE_ADD_FIELD(      imageIndex, (0) );
	SO_NODE_ADD_FIELD(   previousImage, () );
	SO_NODE_ADD_FIELD(       nextImage, () );
	SO_NODE_ADD_FIELD(      sliceIndex, (-1) );
	SO_NODE_ADD_FIELD(   previousSlice, () );
	SO_NODE_ADD_FIELD(       nextSlice, () );
	SO_NODE_ADD_FIELD(         viewAll, () );
	SO_NODE_ADD_FIELD(    viewAllScale, (0.8) );
	SO_NODE_ADD_FIELD(            mode, (NONE) );
	SO_NODE_ADD_FIELD(     boundingBox, (SbMatrix::identity()) );
	SO_NODE_ADD_FIELD( viewBoundingBox, ());
	SO_NODE_ADD_FIELD( planeSlice, (SbPlane(SbVec3f(1, 0, 0), 0)));

	SoField* fields[8] = { &viewAll, &viewBoundingBox, &nextImage, &previousImage, &nextSlice, &previousSlice, &images, &mode };
	for( int i = 0; i < 8; ++ i )
	{
		mFieldSensors[i] = new SoFieldSensor( &fieldSensorCB, this );
		mFieldSensors[i]->attach( fields[i] );
	}

	mSelectionEngine = new SoXipConvertMFDicomToSFDicom;
	mSelectionEngine->ref();

	mDicomExtract = new SoXipDicomExtractSlice;
	mDicomExtract->ref();

	mSelectionEngine->input.connectFrom(&images);
	mSelectionEngine->index.connectFrom(&imageIndex);

	mDicomExtract->image.connectFrom(&mSelectionEngine->output);
	mDicomExtract->sliceIndex.connectFrom(&sliceIndex);
	numSlices.connectFrom( &mDicomExtract->numSlices );

	((SoXipSFDataImage *)mImage->getField(SbName("image")))->connectFrom(&mDicomExtract->output);

	// Create a field sensor on the internal image to update the camera
	mImageSensor = new SoFieldSensor( &fieldSensorCB, this );
	mImageSensor->attach( (SoXipSFDataImage *)mImage->getField(SbName("image")) );
	mImageSensor->setPriority(0);

	// Initialize the animation members to null
	mAnimate = FALSE;
	mAnimateHStep = 0;
	mAnimateHPosition = 0;
	mAnimateVStep = 0;
	mAnimateVPosition = 0;
	mAnimateChange = 0;
	mAnimationSensor = 0;

	mViewAll = TRUE;
	mPan = FALSE;
	mViewBoundingBox = FALSE;
}

SoXipDicomExaminer::~SoXipDicomExaminer()
{
	for( int i = 0; i < 8; ++ i )
	{
		if( mFieldSensors[i] )
		{
			delete mFieldSensors[i];
			mFieldSensors[i] = 0;
		}
	}

	if (mSelectionEngine)
	{
		mSelectionEngine->unref();
		mSelectionEngine = 0;
	}

	if (mDicomExtract)
	{
		mDicomExtract->unref();
		mDicomExtract = 0;
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

void SoXipDicomExaminer::initClass()
{
	SO_NODE_INIT_CLASS( SoXipDicomExaminer, SoXipKit, "SoXipKit" );

	SO_ENABLE( SoGLRenderAction,		SoXipDataDicomElement );
	SO_ENABLE( SoWriteAction,			SoXipDataDicomElement );
	SO_ENABLE( SoHandleEventAction,		SoXipDataDicomElement );
	SO_ENABLE( SoRayPickAction,			SoXipDataDicomElement );

	SO_ENABLE( SoGLRenderAction,		SoXipDataImageElement );
	SO_ENABLE( SoWriteAction,			SoXipDataImageElement );
	SO_ENABLE( SoHandleEventAction,		SoXipDataImageElement );
	SO_ENABLE( SoRayPickAction,			SoXipDataImageElement );
}

void SoXipDicomExaminer::animationSensorCB( void* userData, SoSensor* )
{
	((SoXipDicomExaminer *) userData)->onAnimationTimer();
}

void SoXipDicomExaminer::fieldSensorCB( void* userData, SoSensor* sensor)
{
	SoField* triggeredField = ((SoFieldSensor *) sensor)->getAttachedField();

	((SoXipDicomExaminer*) userData)->inputChanged( triggeredField );
}

void SoXipDicomExaminer::inputChanged( SoField* whichField )
{
	// Displayed image (or image used to configure the camera)
	if( whichField == (SoXipSFDataImage *)mImage->getField(SbName("image")) )
	{
		// After switching to a different image, reposition the camera
		updateCamera();
	}

	// Images field
	else if( whichField == &images )
	{
		int numImages = images.getNum();
		if( numImages <= 0 )
		{
			imageIndex.setValue(-1);
			sliceIndex.setValue(-1);
		}
		else
		{
			int prevImageId = imageIndex.getValue();
			int prevSliceId = sliceIndex.getValue();

			if( prevImageId < 0 || prevImageId >= numImages )
				imageIndex.setValue(0);

			int numOfSlices = numSlices.getValue();

			if( prevSliceId < 0 || prevSliceId >= numOfSlices )
				sliceIndex.setValue(0);

			mViewAll = TRUE;
		}		
	}

	// View all flag
	else if( whichField == &viewAll )
	{
		mViewAll = TRUE;	
	}

	// View bounding box flag
	else if( whichField == &viewBoundingBox )
	{
		mViewBoundingBox = TRUE;	
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

int SoXipDicomExaminer::getNumSlices( SoXipDataDicom* dicomData )
{
	if (dicomData)
	{
		return dicomData->getNumSlices();
	}

	return 0;	
}

void SoXipDicomExaminer::onAnimationTimer()
{
	if( mode.getValue() == SHIFT || mode.getValue() == SCROLL || mode.getValue() == SHIFTSCROLL )
	{
		SbBool animateVForward = mAnimateVStep >= 0;
		float vStep = fabs(mAnimateVStep);

		mAnimateVPosition += vStep;

		if( mAnimateVPosition >= 1 )
		{
			if( animateVForward )
				increaseSliceIndex( (int) mAnimateVPosition );
			else
				decreaseSliceIndex( (int) mAnimateVPosition );

			mAnimateVPosition -= (int) mAnimateVPosition;
		}

		SbBool animateHForward = mAnimateHStep >= 0;
		float hStep = fabs(mAnimateHStep);

		mAnimateHPosition += hStep;

		if( mAnimateHPosition >= 1 )
		{
			if( animateHForward )
				increaseImageIndex( (int) mAnimateHPosition );
			else
				decreaseImageIndex( (int) mAnimateHPosition );

			mAnimateHPosition -= (int) mAnimateHPosition;
		}
	}
	else
	{
		stopAnimation();
	}
}

void SoXipDicomExaminer::startAnimation( float hStep, float vStep )
{
	mAnimate = TRUE;
	mAnimateHPosition = 0;
	mAnimateHStep = hStep;
	mAnimateVPosition = 0;
	mAnimateVStep = vStep;
	
	if( !mAnimationSensor )
	{
		mAnimationSensor = new SoTimerSensor( animationSensorCB, this );
		mAnimationSensor->setInterval( .05 );
	}

	mAnimationSensor->schedule();
}

void SoXipDicomExaminer::stopAnimation()
{
	mAnimate = FALSE;
	mAnimateHPosition = 0;
	mAnimateHStep = 0;
	mAnimateVPosition = 0;
	mAnimateVStep = 0;
	mAnimateChange = 0;

	if( mAnimationSensor )
		mAnimationSensor->unschedule();
}

void SoXipDicomExaminer::increaseImageIndex( int count )
{
	int currentImage = imageIndex.getValue();
	imageIndex.setValue( min( images.getNum() - 1, currentImage + count ) );	

	int numOfSlices = numSlices.getValue();
	if( sliceIndex.getValue() >= numOfSlices )
	{
		sliceIndex.setValue( numOfSlices - 1 );
	}
}

void SoXipDicomExaminer::decreaseImageIndex( int count )
{
	int currentImage = imageIndex.getValue();
	imageIndex.setValue( currentImage - count > 0 ? currentImage - count : 0 );	

	int numOfSlices = numSlices.getValue();	
	if( sliceIndex.getValue() >= numOfSlices )
	{
		sliceIndex.setValue( numOfSlices - 1 );
	}
}

void SoXipDicomExaminer::increaseSliceIndex( int count )
{
	int newSliceIndex = sliceIndex.getValue();
	int newImageIndex = imageIndex.getValue();

	if( newSliceIndex == -1 || newImageIndex == -1 )
		return ;

	while( count > 0 )
	{
		if( newSliceIndex < getNumSlices( images[newImageIndex] ) - 1 )
			++ newSliceIndex;

		else 
		{			
			// If in LOOP mode, look if there any image after we
			// could switch to (and load its first slice)
			if( newImageIndex < images.getNum() - 1 )
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

void SoXipDicomExaminer::decreaseSliceIndex( int count )
{
	int newSliceIndex = sliceIndex.getValue();
	int newImageIndex = imageIndex.getValue();

	if( newSliceIndex == -1 || newImageIndex == -1 )
		return ;

	while( count > 0 )
	{
		if( newSliceIndex > 0 )
			-- newSliceIndex;

		else //if( dogEarScope.getValue() == ALL_IMAGES )
		{			
			// If in LOOP mode, look if there any image before we
			// could switch to (and load its last slice)
			if( newImageIndex > 0 )
			{
				-- newImageIndex;
			}
			else
			{
				newImageIndex = images.getNum() - 1;
			}
			
			newSliceIndex = getNumSlices( images[newImageIndex] ) - 1;
		}

		-- count;
	}

	if( imageIndex.getValue() != newImageIndex )
		imageIndex.setValue( newImageIndex );

	sliceIndex.setValue( newSliceIndex );

}

SoOrthographicCamera* SoXipDicomExaminer::getCamera()
{
	return (SoOrthographicCamera *) mCamera;
}

void SoXipDicomExaminer::updateCamera()
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
		
		SbVec3f t, s, normal;
		SbRotation r, so;
		mImageModelMatrix.getTransform(t, r, s, so);
		normal = SbVec3f(mImageModelMatrix[2][0], mImageModelMatrix[2][1], mImageModelMatrix[2][2]);
		normal.normalize();

		SbPlane plane ( normal, t );

		planeSlice.setValue ( plane ) ;
	}
}

void SoXipDicomExaminer::adjustCamera( SoGLRenderAction* action, const SbMatrix& model )
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
	//getCamera()->nearDistance.setValue( -0.1 );
	//getCamera()->farDistance.setValue( 0.1 );
}

void SoXipDicomExaminer::tiltCamera( const SbRotation& rot )
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

void SoXipDicomExaminer::GLRender( SoGLRenderAction* action )
{
	if (mViewAll)
	{
		SoXipDataImage* xipImage = ((SoXipSFDataImage *)mImage->getField(SbName("image")))->getValue();
		if( !xipImage )
			return ;

		SbXipImage* image = xipImage->get();
		if( image )
			adjustCamera( action, image->getModelMatrix() );

		// Store the information of the current displayed image
		mImageModelMatrix = image->getModelMatrix();

		mViewAll = FALSE;
	}

	if( mViewBoundingBox )
	{
		adjustCamera( action, boundingBox.getValue() );

		mViewBoundingBox = false;
	}

	// Set the Dicom Element
	setElement( action );

	mImageSwitch->enableNotify( FALSE );
	((SoSFInt32 *)mImageSwitch->getField(SbName("whichChild")))->setValue( drawImage.getValue() ? 0 : -1 );
	mImageSwitch->enableNotify( TRUE );
	
	SoXipKit::GLRender( action );
}

void SoXipDicomExaminer::rayPick( SoRayPickAction* action )
{
	// Set the Dicom Element
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

void SoXipDicomExaminer::handleEvent( SoHandleEventAction* action )
{
	// Set the Dicom Element
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

	if( SO_MOUSE_PRESS_EVENT( event, BUTTON1 ) )
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
			float hStep = 0;
			float vStep = 0;

			if( mode.getValue() == SHIFT || mode.getValue() == SHIFTSCROLL )
			{
				vStep = ( mousePos[1] - mLastMousePosition[1] ) * (float) mViewport.getViewportSizePixels()[1] / 60.;
			}
			if( mode.getValue() == SCROLL || mode.getValue() == SHIFTSCROLL )
			{
				hStep = ( mousePos[0] - mLastMousePosition[0] ) * (float) mViewport.getViewportSizePixels()[0] / 60.;
			}

			// Change in direction: stop
			if( mAnimateVStep < 0 && vStep > 0 ||
				mAnimateVStep > 0 && vStep < 0 ||
				mAnimateHStep < 0 && hStep > 0 ||
				mAnimateHStep > 0 && hStep < 0 )
			{
				// Change in direction: stop
				stopAnimation();
				mAnimateChange = 10;
			}
			else 
			{
				if( mAnimateVStep == 0 && mAnimateHStep == 0 )
				{
					if( mAnimateChange <= 0 )
					{
						// Start new shift
						startAnimation( hStep, vStep );
					}
					else
						-- mAnimateChange;
				}
				else
				{
					// Speed up a little
					mAnimateHStep += hStep;
					mAnimateVStep += vStep;
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

		action->releaseGrabber();
		action->setHandled();
	}
}
void SoXipDicomExaminer::setElement( SoAction* action )
{
	int numImages = images.getNum();
	int currentImage = imageIndex.getValue();

	if( numImages && currentImage >= 0 && currentImage < numImages )
	{
		SoXipDataDicom* dicomData = images[ currentImage ];

		int currentSlice = sliceIndex.getValue();
		SoXipDataDicomElement::set( action->getState(), dicomData, currentSlice );
		SoXipDataImageElement::set( action->getState(), ((SoXipSFDataImage *)mImage->getField(SbName("image")))->getValue() );
	}
}


void SoXipDicomExaminer::saveViewInformation( SoHandleEventAction* action )
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