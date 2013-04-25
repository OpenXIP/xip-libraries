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
#include <xip/inventor/overlay/SoXipHandlerShape.h>
#include "SoXipOverlayHandlerManip.h"
#include <xip/inventor/overlay/SoXipOverlayManipulatedElement.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipOverlayHandlerManip );

SoXipOverlayHandlerManip::SoXipOverlayHandlerManip()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayHandlerManip );

	SO_NODE_DEFINE_ENUM_VALUE( ModeType, NONE );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, MOVE );

	SO_NODE_SET_SF_ENUM_TYPE( mode, ModeType );

	SO_NODE_ADD_FIELD( mode, (NONE) );

	mControlPointsSeparator = 0;

	create();

	mControlPointId = -1;
}

SoXipOverlayHandlerManip::~SoXipOverlayHandlerManip()
{
	if( mControlPointsSeparator )
		mControlPointsSeparator->unref();
	mControlPointsSeparator = 0;
}

void
SoXipOverlayHandlerManip::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlayHandlerManip, 
		SoXipOverlayManipBase, "SoXipOverlayManipBase" );
}

void
SoXipOverlayHandlerManip::create()
{
	mControlPointsCoords = new SoCoordinate3;

	mControlPointsStyle = new SoDrawStyle;
	mControlPointsStyle->pointSize.setValue(5);
	mControlPointsStyle->lineWidth.setValue(1);

	SoBaseColor* pColor = new SoBaseColor;
	pColor->rgb.setValue( 1, 1, 1 );	

	SoBaseColor* secondColor = new SoBaseColor;
	secondColor->rgb.setValue( 0.5, 0.5, 0.5 );

	SoDrawStyle* secondStyle = new SoDrawStyle;
	secondStyle->pointSize.setValue(3);

	mTransform = new SoMatrixTransform;
	mTransform->matrix.setValue( SbMatrix::identity() );

	if( mControlPointsSeparator )
		mControlPointsSeparator->unref();

	mControlPointsSeparator = new SoSeparator;
	mControlPointsSeparator->addChild( mTransform );
	mControlPointsSeparator->addChild( mControlPointsCoords );
	mControlPointsSeparator->addChild( mControlPointsStyle );
	mControlPointsSeparator->addChild( pColor );
	mControlPointsSeparator->addChild( new SoPointSet );
	mControlPointsSeparator->addChild( mControlPointsCoords );
	mControlPointsSeparator->addChild( secondStyle );
	mControlPointsSeparator->addChild( secondColor );
	mControlPointsSeparator->addChild( new SoPointSet );

	mControlPointsSeparator->ref();
}

void
SoXipOverlayHandlerManip::handleEvent( SoHandleEventAction* action )
{
	if ( !on.getValue() )
		return;
	
	SoXipOverlayManipBase::handleEvent( action );
	if( action->isHandled() )
		return ;

	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) ) 
	{
		if( action->getGrabber() == this )
		{
			mode.setValue( NONE );

			SoNodeList shapes = XipOverlayUtils::getManipulableShapes( mActionNode, TRUE );
			for( int i = 0; i < shapes.getLength(); ++ i )
			{
				SoXipHandlerShape* shape = (SoXipHandlerShape *) shapes[i];
				if( shape->isOfType( SoXipHandlerShape::getClassTypeId() ) )
					shape->invalidateGeometries();
			}

			action->setHandled();
			action->releaseGrabber();
		}
	}
	else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		if( action->getGrabber() == this )
		{
			SbVec3f pos;
			if( getPoint( action, pos ) )
			{
				SoNodeList shapes = XipOverlayUtils::getManipulableShapes( mActionNode, TRUE );

				for( int i = 0; i < shapes.getLength(); ++ i )
				{
					SoXipHandlerShape* shape = (SoXipHandlerShape *) shapes[i];
					if( shape->isOfType( SoXipHandlerShape::getClassTypeId() ) )
					{
						shape->moveHandlerPoint( mControlPointId, pos );
						shape->invalidateGeometries();
					}
				}
				action->setHandled();
			}
		}
		else
		{
			const SoFullPath* path = (SoFullPath *) action->getCurPath();
			mActionNode = path->getNodeFromTail( numNodesUpToContainer.getValue() );

			if( pickControlPoint( action ) != -1 )
			{
				SoXipCursor::setCursor( "MOVE" );
				action->setHandled();
			}
		}	
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		const SoFullPath* path = (SoFullPath *) action->getCurPath();
		mActionNode = path->getNodeFromTail( numNodesUpToContainer.getValue() );

		if( getPoint( action, mTransformationOrigin ) )
		{
			mControlPointId = pickControlPoint( action );
			if( mControlPointId != -1 )
			{
				mode.setValue( MOVE );

				action->setHandled();
				action->setGrabber( this );
			}
		}
	}
}

void
SoXipOverlayHandlerManip::GLRender( SoGLRenderAction* action )
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

		const SoFullPath* path = (SoFullPath *) action->getCurPath();
		SoNode* searchRoot = path->getNodeFromTail( numNodesUpToContainer.getValue() );

		SoNodeList shapes = XipOverlayUtils::getManipulableShapes( searchRoot, TRUE );

		// If there is only one shape selected, then we can apply the handler manipulator.
		// Otherwise, the transform box manipulator will show the bounding box of the
		// selected shapes, and manipulate them all.
		//
		if( shapes.getLength() == 1 )
		{
			SoXipHandlerShape* shape = (SoXipHandlerShape *) shapes[0];

			if( shape->isOfType( SoXipHandlerShape::getClassTypeId() ) )
			{
				mTransform->matrix.setValue( shape->getTransform() );

				shape->getHandlerPoints( mControlPointsCoords->point );

				glPushAttrib( GL_ENABLE_BIT );
				glDisable( GL_DEPTH_TEST );

				SoXipOverlayManipulatedElement::set( state, this, TRUE );

				mControlPointsSeparator->GLRender( action );

				glPopAttrib();
			}
		}
	}
}

int
SoXipOverlayHandlerManip::pickControlPoint( SoHandleEventAction* action )
{
	SbVec2f mousePt = action->getEvent()->getNormalizedPosition( action->getViewportRegion() );
	SbVec3f screenPt;

	// Get const pointer to the shape points
	const SbVec3f* coordPtr = mControlPointsCoords->point.getValues(0);

	int numPoints = mControlPointsCoords->point.getNum();
	for( int i = 0; i < numPoints; ++ i )
	{
		mViewVolume.projectToScreen( coordPtr[i], screenPt );

		SbVec2f d = SbVec2f( screenPt[0], screenPt[1] ) - mousePt;
		if( d.length() < 0.01 )
			return i;
	}
	return -1;
}