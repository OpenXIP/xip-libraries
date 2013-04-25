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
#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoSwitch.h>
#include <xip/inventor/overlay/SoXipManipulableShape.h>
#include <xip/inventor/overlay/SoXipOverlayManipulatedElement.h>
#include "SoXipOverlayFilterElement.h"
#include "SoXipOverlayTransformBoxManip.h"
#include  <xip/inventor/overlay/XipOverlayUtils.h>
#include "geomutils.h"

SO_NODE_SOURCE( SoXipOverlayTransformBoxManip );

SoXipOverlayTransformBoxManip::SoXipOverlayTransformBoxManip()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayTransformBoxManip );
	
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, NONE );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, ROTATION );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, SCALE );

	SO_NODE_SET_SF_ENUM_TYPE( mode, ModeType );

	SO_NODE_ADD_FIELD( mode, (NONE) );

	mControlPointsSwitch = 0;

	create();

	mControlPointId = -1;
}

SoXipOverlayTransformBoxManip::~SoXipOverlayTransformBoxManip()
{
	if( mControlPointsSwitch )
		mControlPointsSwitch->unref();
	mControlPointsSwitch = 0;
}

void
SoXipOverlayTransformBoxManip::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlayTransformBoxManip, 
		SoXipOverlayManipBase, "SoXipOverlayManipBase" );

	SO_ENABLE( SoGLRenderAction, SoXipOverlayFilterElement);
}

void
SoXipOverlayTransformBoxManip::create()
{
	mControlPointsCoords = new SoCoordinate3;
	mControlPointsCoords->point.setNum(8);
	mControlPointsCoords->point.set1Value( 0, SbVec3f( -0.5,  0.5, 0 ) );
	mControlPointsCoords->point.set1Value( 1, SbVec3f(    0,  0.5, 0 ) );
	mControlPointsCoords->point.set1Value( 2, SbVec3f(  0.5,  0.5, 0 ) );
	mControlPointsCoords->point.set1Value( 3, SbVec3f(  0.5,    0, 0 ) );
	mControlPointsCoords->point.set1Value( 4, SbVec3f(  0.5, -0.5, 0 ) );
	mControlPointsCoords->point.set1Value( 5, SbVec3f(    0, -0.5, 0 ) );
	mControlPointsCoords->point.set1Value( 6, SbVec3f( -0.5, -0.5, 0 ) );
	mControlPointsCoords->point.set1Value( 7, SbVec3f( -0.5,    0, 0 ) );

	mControlPointsStyle = new SoDrawStyle;
	mControlPointsStyle->pointSize.setValue(5);
	mControlPointsStyle->lineWidth.setValue(1);

	SoBaseColor* pColor = new SoBaseColor;
	pColor->rgb.setValue( 1, 1, 1 );	

	mBBoxTransform = new SoMatrixTransform;
	mBBoxTransform->matrix.setValue( SbMatrix::identity() );

	SoBaseColor* secondColor = new SoBaseColor;
	secondColor->rgb.setValue( 0.5, 0.5, 0.5 );

	SoDrawStyle* secondStyle = new SoDrawStyle;
	secondStyle->pointSize.setValue(3);

	if( mControlPointsSwitch )
		mControlPointsSwitch->unref();

	SoSeparator* controlPointsSeparator = new SoSeparator;
	controlPointsSeparator->addChild( mBBoxTransform );
	controlPointsSeparator->addChild( mControlPointsCoords );
	controlPointsSeparator->addChild( mControlPointsStyle );
	controlPointsSeparator->addChild( pColor );
	controlPointsSeparator->addChild( new SoPointSet );
	controlPointsSeparator->addChild( mControlPointsCoords );
	controlPointsSeparator->addChild( secondStyle );
	controlPointsSeparator->addChild( secondColor );
	controlPointsSeparator->addChild( new SoPointSet );

	mControlPointsSwitch = new SoSwitch;
	mControlPointsSwitch->addChild( controlPointsSeparator );
	mControlPointsSwitch->ref();
}

void
SoXipOverlayTransformBoxManip::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;
	
	SoXipOverlayManipBase::handleEvent( action );
	if( action->isHandled() )
		return ;

	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) ) 
	{
		if( action->getGrabber() == this )
		{
			applyTransform( mActionNode );

			mode.setValue( NONE );

			mTransformationMatrix = SbMatrix::identity();

			action->setHandled();
			action->releaseGrabber();
		}
	}
	else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		if( action->getGrabber() == this )
		{
			switch( mode.getValue() )
			{
				case ROTATION:
					rotate( action );
					break ;

				case SCALE:
					scale( action );
					break ;
			}
			action->setHandled();
		}
		else
		{
			int cIndex = pickControlPoint( action );
			if( action->getEvent()->wasShiftDown() )
			{
				if( cIndex % 2 == 0 )
				{
					SoXipCursor::setCursor( "ROTATE_POINT" );
					action->setHandled();
				}
			}
			else
			{
				switch( cIndex )
				{
					case 0:
					case 4: 
						SoXipCursor::setCursor( "UPRIGHT" );
						break ;

					case 2:
					case 6:
						SoXipCursor::setCursor( "DOWNRIGHT" );
						break ;

					case 1: 
					case 5:
						SoXipCursor::setCursor( "UPDOWN" ); 
						break ;

					case 3:	
					case 7:
						SoXipCursor::setCursor( "LEFTRIGHT" ); 
						break ;

					default:
						return ;
				}
				action->setHandled();
			}
		}	
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		if( getPoint( action, mTransformationOrigin ) )
		{
			mControlPointId = pickControlPoint( action );
			if( mControlPointId != -1 )
			{
				ModeType newMode;
				if( action->getEvent()->wasShiftDown() )
					newMode = mControlPointId % 2 == 0 ? ROTATION : SCALE;
				else
					newMode = SCALE;

				if( mode.getValue() != newMode )
					mode.setValue( newMode );

				action->setHandled();
				action->setGrabber( this );
			}
		}
	}
}

SbBool
SoXipOverlayTransformBoxManip::computeSelectionXBoundingBox( SoGLRenderAction* action )
{
	mXBoundingBox.makeEmpty();

	const SoFullPath* path = (SoFullPath *) action->getCurPath();
	SoNode* searchRoot = path->getNodeFromTail( numNodesUpToContainer.getValue() );
	SoNodeList shapes = XipOverlayUtils::getManipulableShapes( searchRoot, TRUE );

	int numShapes = shapes.getLength();

	// Don't display if the shape the transformBox is applied to is filtered
	if ( (numShapes == 1) && 
		!SoXipOverlayFilterElement::isOn( action->getState(), ((SoXipManipulableShape *)shapes[0])->label ) )
	{
		return mXBoundingBox.isEmpty();
	}
	

	for( int i = 0; i < numShapes; ++ i )
	{
		SoXipManipulableShape* shape = (SoXipManipulableShape *) shapes[i];

		SbXfBox3f newbox;
		shape->computeXBoundingBox( newbox );

		mXBoundingBox.extendBy( newbox );
	}

	return !mXBoundingBox.isEmpty();
}

void
SoXipOverlayTransformBoxManip::GLRender( SoGLRenderAction* action )
{
	
	if (!on.getValue())
		return;
	
	SoState *state = action->getState();
	if( state )
	{
		if( SoXipActiveViewportElement::get( state ) == false ||
			SoXipOverlayManipulatedElement::get( state ) )
		{
			return ;
		}

		if( mode.getValue() == NONE )
		{
			if( computeSelectionXBoundingBox( action ) )
			{
				SbVec3f bboxMin;
				SbVec3f bboxMax;
				mXBoundingBox.getBounds( bboxMin, bboxMax );

				SbVec3f corners[4];
				corners[0] = SbVec3f( bboxMin[0], bboxMin[1], bboxMin[2] );
				corners[1] = SbVec3f( bboxMax[0], bboxMin[1], bboxMin[2] );
				corners[2] = SbVec3f( bboxMax[0], bboxMax[1], bboxMin[2] );
				corners[3] = SbVec3f( bboxMin[0], bboxMax[1], bboxMin[2] );
			
				SbVec3f inPlaneCorners[4];
				mXBoundingBox.getTransform().multVecMatrix( corners[0], inPlaneCorners[0] );
				mXBoundingBox.getTransform().multVecMatrix( corners[1], inPlaneCorners[1] );
				mXBoundingBox.getTransform().multVecMatrix( corners[2], inPlaneCorners[2] );
				mXBoundingBox.getTransform().multVecMatrix( corners[3], inPlaneCorners[3] );

				mControlPointsCoords->point.set1Value( 0, inPlaneCorners[0] );
				mControlPointsCoords->point.set1Value( 1, (inPlaneCorners[0] + inPlaneCorners[1]) / 2. );
				mControlPointsCoords->point.set1Value( 2, inPlaneCorners[1] );
				mControlPointsCoords->point.set1Value( 3, (inPlaneCorners[1] + inPlaneCorners[2]) / 2. );
				mControlPointsCoords->point.set1Value( 4, inPlaneCorners[2] );
				mControlPointsCoords->point.set1Value( 5, (inPlaneCorners[2] + inPlaneCorners[3]) / 2. );
				mControlPointsCoords->point.set1Value( 6, inPlaneCorners[3] );
				mControlPointsCoords->point.set1Value( 7, (inPlaneCorners[3] + inPlaneCorners[0]) / 2. );
		
				glPushAttrib( GL_ENABLE_BIT );
				glDisable( GL_DEPTH_TEST );

				SoXipOverlayManipulatedElement::set( state, this, TRUE );

				if( mControlPointsSwitch->whichChild.getValue() != 0 )
					mControlPointsSwitch->whichChild.setValue(0);

				mControlPointsSwitch->GLRender( action );

				glPopAttrib();
				return ;
			}
		}
		else
		{		
			SoXipOverlayManipulatedElement::set( state, this, TRUE );		
		}
	}

	if( mControlPointsSwitch->whichChild.getValue() != -1 )
		mControlPointsSwitch->whichChild.setValue(-1);
}

void 
SoXipOverlayTransformBoxManip::rotate( SoHandleEventAction* action )
{
	SbVec3f projPt;
	getPoint( action, projPt );
	
	const SbVec3f* point = mControlPointsCoords->point.getValues(0);

	SbVec3f center = (point[0] + point[4]) / 2.;

	SbVec3f rotateFrom	= point[mControlPointId] - center;
	SbVec3f rotateTo	= projPt - center;

	SbVec3f normal = mViewVolume.getPlane(0).getNormal();
	
	SbRotation rotation;
	rotation.setValue( normal, angleBetweenVectors( rotateFrom, rotateTo, normal ) );
	
	SbMatrix centerMatrix;
	centerMatrix.setTranslate( center );

	SbMatrix rotationMatrix;
	rotationMatrix.setRotate( rotation );

	mTransformationMatrix = centerMatrix.inverse() * rotationMatrix * centerMatrix;
	transform( mActionNode );
}

void 
SoXipOverlayTransformBoxManip::scale( SoHandleEventAction* action )
{
	// Extract the rotation matrix from the view matrix
	SbMatrix rotationMatrix = extractRotationMatrix( mXBoundingBox.getInverse() );

	// Get the two control points involved in the computation of the scale
	// matrix (the one initially picked by the user and its opposit control
	// point.
	const SbVec3f& cp3d = mControlPointsCoords->point[ mControlPointId ];
	const SbVec3f& opp_cp3d = mControlPointsCoords->point[ (mControlPointId + 4) % 8 ];

	// Get the projection in the world of the current mouse position 
	SbVec3f p3d;
	getPoint( action, p3d );

	// Project the control points and the mouse world position on a xy plane
	SbVec3f p2d, cp2d, opp_cp2d;
	rotationMatrix.multVecMatrix( cp3d, cp2d );
	rotationMatrix.multVecMatrix( opp_cp3d, opp_cp2d );
	rotationMatrix.multVecMatrix( p3d, p2d );

	SbVec3f refVec = cp2d - opp_cp2d;
	SbVec3f movVec = p2d - opp_cp2d;	

	SbVec3f scaleVec(1, 1, 1);
	for( int i = 0; i < 3; ++ i )
	{
		if( fabs( refVec[i] ) > 0.001 )
			scaleVec[i] = movVec[i] / refVec[i];
	}

	// Compute the 2D scale matrix
	SbMatrix scaleMatrix2D;
	scaleMatrix2D.setScale( scaleVec );

	// Use the opposit control point to center the shape (scale only regarding
	// the picked control point)
	SbMatrix centerMatrix;
	centerMatrix.setTranslate( opp_cp3d );

	mTransformationMatrix =  centerMatrix.inverse()		// Translate a point to the origin
		* rotationMatrix								// Rotate the plane to a xy aligned plane
		* scaleMatrix2D									// Scale the point in this plane
		* rotationMatrix.inverse()						// Rotate back to initial plane
		* centerMatrix;									// Undo the first translation

	transform( mActionNode );
}

int
SoXipOverlayTransformBoxManip::pickControlPoint( SoHandleEventAction* action )
{
	if( mControlPointsSwitch->whichChild.getValue() != -1 )
	{
		SbVec2f mousePt = action->getEvent()->getNormalizedPosition( action->getViewportRegion() );
		SbVec3f screenPt;

		const SbVec3f* point = mControlPointsCoords->point.getValues(0);

		int numPoints = mControlPointsCoords->point.getNum();
		for( int i = 0; i < numPoints; ++ i )
		{
			mViewVolume.projectToScreen( point[i], screenPt );

			SbVec2f d = SbVec2f( screenPt[0], screenPt[1] ) - mousePt;
			if( d.length() < 0.01 )
				return i;
		}
	}
	return -1;
}
