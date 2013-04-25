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

#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoPointSet.h>
#include <xip/inventor/overlay/SoXipEditableShape.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include "geomutils.h"

SO_NODE_ABSTRACT_SOURCE( SoXipEditableShape );


SoXipEditableShape::SoXipEditableShape()
{
	SO_NODE_CONSTRUCTOR( SoXipEditableShape );

	SO_XIP_KIT_ADD_ENTRY( mControlPointsSwitch, SoSwitch, mTopSeparator );
	SO_XIP_KIT_ADD_ENTRY( mControlPointsSeparator, SoSeparator, mControlPointsSwitch );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mControlPointsCoords, SoCoordinate3, mControlPointsSeparator );
	SO_XIP_KIT_ADD_ENTRY( mControlPointsStyle, SoDrawStyle, mControlPointsSeparator );
	SO_XIP_KIT_ADD_ENTRY( mControlPointsSet, SoPointSet, mControlPointsSeparator );

	SO_XIP_SHAPE_ADD_FIELD( point, (0, 0, 0) );
	point.setNum(0);
	SO_XIP_SHAPE_ADD_FIELD( closed, (FALSE) );

	SO_NODE_ADD_FIELD( closeOnDblClick,  (TRUE) );

	mControlPointsCoords->point.setNum(0);
	mControlPointsStyle->set( "pointSize 3" );

	mControlPointId				= -1;
}

SoXipEditableShape::~SoXipEditableShape()
{

}

void
SoXipEditableShape::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipEditableShape, SoXipManipulableShape, "SoXipManipulableShape" );
}

SbBool
SoXipEditableShape::isClosed() const
{
	return closed.getValue();
}

void
SoXipEditableShape::beforeCreation()
{
	SoXipManipulableShape::beforeCreation();
		
	point.setNum(0);
	closed.setValue( FALSE );
}

void
SoXipEditableShape::extractControlPoints( SoMFVec3f& points )
{
	points.setNum( point.getNum() );
	if (point.getNum() > 0)
		points.setValues( 0, point.getNum(), point.getValues(0) );
}

void 
SoXipEditableShape::transform( const SbMatrix& matrix )
{
	int numPoints = point.getNum();
	SbVec3f* pts = point.startEditing();
	for( int i = 0;i < numPoints; ++ i )
		matrix.multVecMatrix( pts[i], pts[i] );
	point.finishEditing();
}

int
SoXipEditableShape::pickControlPoint( SoHandleEventAction* action )
{	
	SbVec3f worldPt;
	if( getPoint( action, worldPt ) )
	{
		float maxDist = 2 * projectScreenOffsetToWorld( SbVec2s( 1, 1 ) ).length();

		// Get a const pointer to the shape points
		const SbVec3f* coordPtr = mControlPointsCoords->point.getValues(0);

		int numPoints = mControlPointsCoords->point.getNum();		
		for( int i = 0; i < numPoints; ++ i )
		{
			if( (coordPtr[i] - worldPt).length() < maxDist )
				return i;
		}
	}
	return -1;	
}

void
SoXipEditableShape::addPoint( SoNode* node, const SbVec2s& screenPt )
{
	int id;
	SbVec3f worldPt;
	if( getPoint( node, screenPt, worldPt ) && belongsToContour( worldPt, id ) )
	{
		// Add one point
		point.insertSpace( id + 1, 1 );
		point.set1Value( id + 1, worldPt );
	}
}

void
SoXipEditableShape::deletePoint( int id )
{
	point.setValues( id, point.getNum() - id - 1, point.getValues( id + 1 ) );	
	point.setNum( point.getNum() - 1 );	
}

void
SoXipEditableShape::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;

	if( !isEditing() )
	{
		SoXipManipulableShape::handleEvent( action );		
		return ;
	}

	const SoEvent* event = action->getEvent();
	if( !event )
		return ;

	SbVec3f worldPt;
	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() )
	{
		action->releaseGrabber();
		action->setHandled();
	}
	else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		if( action->getGrabber() == this)
		{
			if( getPoint( action, worldPt ) )
				mouseMove( worldPt );
		}

		if( ! action->getGrabber() )
		{
			int cIndex = pickControlPoint( action );
			if( cIndex != -1 )
			{
				SoXipCursor::setCursor( "MOVEPOINT" );
				action->setHandled();
			}		
			else 
			{
				int id;				
				if( getPoint( action, worldPt ) && belongsToContour( worldPt, id ) )
				{
					SoXipCursor::setCursor( "ADDPOINT" );
					action->setHandled();
				}
			}
		}
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		if( getPoint( action, worldPt ) )
		{
			mControlPointId = -1;
			if( ( mControlPointId = pickControlPoint( action ) ) != -1 )
			{
				action->setHandled();
				action->setGrabber( this );

				mIsButtonPressed = true;
				mouseDown( worldPt );
			}
			else
			{
				int id;
				if( belongsToContour( worldPt, id ) )
				{
					// Add one point
					point.insertSpace( id + 1, 1 );
					point.set1Value( id + 1, worldPt );

					// Set this point as the one being modified
					mControlPointId = id + 1;

					action->setHandled();
					action->setGrabber( this );

					mIsButtonPressed = true;

					SoXipCursor::setCursor( "MOVEPOINT" );
				}
				else
				{
					action->releaseGrabber();
					status.setValue( NONE );
				}			
			}
		}
	}

	if( action->getGrabber() == this )
	{
		updateGeometries();
	}
}

void
SoXipEditableShape::updateGeometries()
{
	if (mControlPointsCoords && mControlPointsSet)
	{
		extractControlPoints( mControlPointsCoords->point );

		((SoPointSet *) mControlPointsSet)->numPoints.setValue( 
			mControlPointsCoords->point.getNum() );
	}
	
	SoXipManipulableShape::updateGeometries();
}

void 
SoXipEditableShape::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Read information from shape
	closed = this->closed.getValue();

	// Set the points
	point.copyFrom( this->point );

	// Set the coordinate indices
	XipOverlayUtils::fillCoordIndex( point, closed, coordIndex );
}

void
SoXipEditableShape::startEditing()
{
	toggleEnumerationOnOff( FALSE );
	toggleAnnotationOnOff( FALSE );

	((SoSwitch *) mControlPointsSwitch)->whichChild.setValue(0);
}

void
SoXipEditableShape::finishEditing()
{
	((SoSwitch *) mControlPointsSwitch)->whichChild.setValue(-1);

	toggleEnumerationOnOff( TRUE );
	toggleAnnotationOnOff( TRUE );
}

bool
SoXipEditableShape::belongsToContour( const SbVec3f& worldPt, int &id )
{
	if( !mLinesCoords )
		return false;

	float maxDist = 2 * projectScreenOffsetToWorld( SbVec2s( 1, 1 ) ).length();

	// Get a const pointer to the shape points
	const SbVec3f* coordPtr = mLinesCoords->point.getValues(0);
	
	int numPoints = mLinesCoords->point.getNum();	
	for( int i = 0; i < numPoints; ++ i )
	{
		const SbVec3f& origin = coordPtr[i];
		const SbVec3f& dest = coordPtr[ (i + 1) % numPoints];

		SbLine line( origin, dest );
	
		SbVec3f proj = line.getClosestPoint( worldPt );
		if( (proj - worldPt).length() > maxDist )
			continue ;

		float dist = (origin - dest).length();
		if( (proj - origin).length() > dist || (proj - dest).length() > dist )
			continue ;

		id = getPreviousControlPoint( i );
		return true;
	}
	return false;
}

int
SoXipEditableShape::getPreviousControlPoint( int id ) const
{
	return id;
}

void 
SoXipEditableShape::updateAnnotationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() )
	{
		mAnnotation->justification.setValue( SoXipText2::RIGHT );
		mAnnotation->vAlignment.setValue( SoXipText2::TOP );
		
		SbXfBox3f bbox;
		computeXBoundingBox( bbox );

		SbVec3f bboxMin, bboxMax, refPt;
		bbox.getBounds( bboxMin, bboxMax );
		bbox.getTransform().multVecMatrix( bboxMin, refPt );

		int id = closestPoint( point, refPt );

		SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 5 ) );
		offset[2] = 0;
		
		position.setValue( point[id] - offset );
	}
}

void 
SoXipEditableShape::updateEnumerationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() )
	{
		mEnumerationText->justification.setValue( SoXipText2::LEFT );
		mEnumerationText->vAlignment.setValue( SoXipText2::BOTTOM );
		
		SbXfBox3f bbox;
		computeXBoundingBox( bbox );

		SbVec3f bboxMin, bboxMax, refPt;
		bbox.getBounds( bboxMin, bboxMax );
		bbox.getTransform().multVecMatrix( bboxMax, refPt );

		int id = closestPoint( point, refPt );

		SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 5 ) );
		offset[2] = 0;
		
		position.setValue( point[id] + offset );
	}
}