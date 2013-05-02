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

#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/overlay/SoXipShape.h>

SO_NODE_ABSTRACT_SOURCE( SoXipShape );

SoXipShape::SoXipShape()
{
	SO_NODE_CONSTRUCTOR( SoXipShape );

	SO_NODE_DEFINE_ENUM_VALUE( StatusType, NONE );
	SO_NODE_DEFINE_ENUM_VALUE( StatusType, CREATE );
	SO_NODE_DEFINE_ENUM_VALUE( StatusType, EDIT );
	SO_NODE_DEFINE_ENUM_VALUE( StatusType, CLEAR );


	SO_NODE_SET_SF_ENUM_TYPE( status, StatusType );	

	SO_NODE_ADD_FIELD(           on, (TRUE) );
	SO_NODE_ADD_FIELD(       status, (CREATE) );
	SO_NODE_ADD_FIELD(        order, (-1) );
	SO_NODE_ADD_FIELD(         rank, (-1) );
	SO_NODE_ADD_FIELD(        label, ("") );
	SO_NODE_ADD_FIELD(      caption, ("") );

	SoField* fields[5] = { &on, &status, &label, &rank, &caption };
	for( int i = 0; i < 5; ++ i )
	{
		mFieldSensors[i] = new SoFieldSensor( fieldSensorCallback, this );
		mFieldSensors[i]->attach( fields[i] );
	}

	mPlaneProj		= new SbPlaneProjector(FALSE);
	mPlaneProj->setPlane( SbPlane( SbVec3f(0, 0, 1), 0 ) );

	mIsSelected		= FALSE;
}

SoXipShape::~SoXipShape()
{
	if( mPlaneProj )
	{
		delete mPlaneProj;
		mPlaneProj = 0;
	}

	for( int i = 0; i < 5; ++ i )
	{
		if( mFieldSensors[i] )
		{
			delete mFieldSensors[i];
			mFieldSensors[i] = 0;
		}
	}
}

void
SoXipShape::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipShape, SoXipKit, "SoXipKit" );
}

void 
SoXipShape::setLabel( const SoMFString& label )
{
	this->label.copyFrom( label );
}

void 
SoXipShape::setRank( int rank )
{
	this->rank.setValue( rank );
}

void 
SoXipShape::setCaption( const SbString& caption )
{
	this->caption.setValue( caption );
}

SbBool
SoXipShape::isEditing() const
{
	return status.getValue() == EDIT;
}

SbBool
SoXipShape::isCreating() const
{
	return status.getValue() == CREATE;
}

SbBool 
SoXipShape::isSelected() const
{
	return mIsSelected;
}

SbBool
SoXipShape::isDeleted() const
{
	return status.getValue() == CLEAR;
}
	
void 
SoXipShape::select( SbBool state )
{
	mIsSelected = state;

	// Because the selection state is not a field, the node won't be flagged as
	// modified, so we need to call startNotify() to force a re-rendering of the
	// scene
	startNotify();
}

void
SoXipShape::fieldSensorCallback( void* userData, SoSensor* sensor )
{
	SoField* whichField = ((SoFieldSensor *) sensor)->getAttachedField();

	SoXipShape* self = (SoXipShape *) userData;

	if( whichField == &self->status )
	{
		switch( self->status.getValue() )
		{
		case EDIT:
			self->select( FALSE );
			self->startEditing();
			break ;

		case CREATE:
			self->beforeCreation();
			self->finishEditing();
			break ;

		case NONE:
			self->afterCreation();
			self->finishEditing();
			break ;

		case CLEAR:
			self->beforeCreation();
			self->select(FALSE);
			break;
		}
	}
	else if( whichField == &self->on )
	{
		// Unselect the shape if necessary
		if( self->on.getValue() == FALSE && self->isSelected() )
			self->select( FALSE );
	}

	// Dirty fix to force re-rendering when setting the label, caption, rank from the outside
	// (required for SoXipOverlayProperties). Needs clean-up!
	else if( whichField == &self->label || whichField == &self->caption  || whichField == &self->rank )
	{
		self->startNotify();
	}
}

void
SoXipShape::saveViewInformation( SoAction* action )
{
	SoState* state = action->getState();
	if( !state )
		return ;

	SbBool canSave = FALSE;
	if( action->isOfType( SoGLRenderAction::getClassTypeId() ) )
	{
		// FIXME: see if we need to test for active viewport!!
		if( SoXipActiveViewportElement::get(state) && status.getValue()==NONE)
			canSave = TRUE;
	}

	if( action->isOfType( SoHandleEventAction::getClassTypeId() ) )
	{
		// make sure no grabber is active
		if( !((SoHandleEventAction*) action)->getGrabber() )
			canSave = TRUE;
	}

	if( canSave )
	{
		mOverlaySettings = SoXipOverlayElement::get( state );

		// Save the view volume element
		mViewVolume = SoViewVolumeElement::get( state );

		// Save the viewport
		mViewport = SoViewportRegionElement::get( state );

		// NEAR_PLANE : move slighty inwards of nearplane to ensure proper drawing
		float distance = 0.001;
		if( mOverlaySettings.getLocation() == SoXipOverlayElement::FOCAL_PLANE )
			distance = mViewVolume.getDepth() / 2.f;

		mPlaneProj->setViewVolume( mViewVolume );
		mPlaneProj->setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + distance ) );
	}
}

const SbVec2f
SoXipShape::getNormalizedPosition( const SbVec2s& screenPt ) const
{
    const SbVec2s& pixSize = mViewport.getViewportSizePixels();
	const SbVec2s& origin = mViewport.getViewportOriginPixels();
    SbVec2s pos = screenPt - origin;

	SbVec2f normalizedScreenPt;
	if ( pixSize[0] == 0 )
		normalizedScreenPt[0] = 0.;
    else
		normalizedScreenPt[0] = (float) pos[0] / (float) pixSize[0];

	if ( pixSize[1] == 0 )
		normalizedScreenPt[1] = 0.;
    else
		normalizedScreenPt[1] = (float) pos[1] / (float) pixSize[1];

    return normalizedScreenPt;
}

SbBool
SoXipShape::getPoint( SoNode* node, const SbVec2s& screenPt, SbVec3f& worldPt )
{
	if( mOverlaySettings.getLocation() == SoXipOverlayElement::FOCAL_PLANE ||
		mOverlaySettings.getLocation() == SoXipOverlayElement::NEAR_PLANE )
	{
		worldPt = mPlaneProj->project( getNormalizedPosition( screenPt ) );
		return TRUE;
	}
	else if( mOverlaySettings.getLocation() == SoXipOverlayElement::PICKING )
	{
		SoRayPickAction pa( mViewport );
		pa.setPoint( screenPt );
		pa.setRadius( 1 );
		pa.enableCulling( FALSE );
		pa.apply( node );

		if( pa.getPickedPoint() )
		{
			worldPt = pa.getPickedPoint()->getPoint();
			return TRUE;
		}
	}
	else
	{
		SoError::post( "SoXipOverlayElement: Unknown location" );
	}

	return FALSE;
}

SbBool
SoXipShape::getPoint( SoHandleEventAction* action, SbVec3f& point )
{
	const SoEvent* event = action->getEvent();
	if( !event )
		return FALSE;
	
	return getPoint( action->getNodeAppliedTo(), 
		action->getEvent()->getPosition(), point );	
}

void
SoXipShape::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;

	SoXipKit::handleEvent( action );

	// Once you set the grabber, the scene is not going to be traversed
	// for the next events. Need to save any view information prior.
	//	
	if( !action->getGrabber() )
		saveViewInformation( action );
}

SbVec3f
SoXipShape::projectScreenOffsetToWorld( const SbVec2s& pixelOffset ) const
{
	SbVec2f normOffset = SbVec2f(
		pixelOffset[0] / (float) mViewport.getViewportSizePixels()[0],
		pixelOffset[1] / (float) mViewport.getViewportSizePixels()[1] );

	return mPlaneProj->project( normOffset ) - mPlaneProj->project( SbVec2f( 0, 0 ) );
}


