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

#include <Inventor/SbBox.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include "SoXipOverlaySelectionFrame.h"
#include  <xip/inventor/overlay/SoXipManipulableShape.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include "geomutils.h"

SO_NODE_SOURCE( SoXipOverlaySelectionFrame );

SoXipOverlaySelectionFrame::SoXipOverlaySelectionFrame()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlaySelectionFrame );

	mTopSeparator	= 0;
	mIsDragging		= FALSE;

	create();
}

SoXipOverlaySelectionFrame::~SoXipOverlaySelectionFrame()
{
	if( mTopSeparator )
		mTopSeparator->unref();
	mTopSeparator = 0;	
}

void
SoXipOverlaySelectionFrame::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlaySelectionFrame,
		SoXipOverlayManipBase, "SoXipOverlayManipBase" );
}

void
SoXipOverlaySelectionFrame::create()
{
	SoDrawStyle* lineStyle = new SoDrawStyle;
	lineStyle->lineWidth.setValue(1);
	lineStyle->linePattern.setValue( 0xf0f0 );

	SoBaseColor* lineColor = new SoBaseColor;
	lineColor->rgb.setValue( 1, 1, 1 );

	int indices[6] = {0, 1, 2, 3, 0, -1};

	SoIndexedLineSet* lineIndices = new SoIndexedLineSet;
	lineIndices->coordIndex.setValues( 0, 6, indices );

	SoSeparator* lineSeparator = new SoSeparator;
	lineSeparator->addChild( lineStyle );
	lineSeparator->addChild( lineColor );
	lineSeparator->addChild( lineIndices );

 	mLinesCoords = new SoCoordinate3;	
	mLinesCoords->point.setNum(4);

	// Top Separator
	//
	mTopSeparator = new SoSeparator;
	mTopSeparator->addChild( mLinesCoords );
	mTopSeparator->addChild( lineSeparator );
	mTopSeparator->ref();
}

void
SoXipOverlaySelectionFrame::handleEvent( SoHandleEventAction* action )
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
			mIsDragging = FALSE;

			startNotify();

			action->releaseGrabber();
			action->setHandled();

			updateSelection();
		}
	}
	else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		SbVec3f newPoint;
		if( action->getGrabber() == this && getPoint( action, newPoint ) )
		{
			SbVec3f u = projectScreenOffsetToWorld( SbVec2s(1, 0) );
			SbVec3f v = projectScreenOffsetToWorld( SbVec2s(0, 1) );
	
			SbVec3f* points = mLinesCoords->point.startEditing();	

			SbVec3f pos[2];
			pos[0] = SbLine( newPoint, newPoint + u ).getClosestPoint( points[0] );
			pos[1] = SbLine( newPoint, newPoint + v ).getClosestPoint( points[0] );

			points[1] = pos[0];
			points[2] = newPoint;
			points[3] = pos[1];
			mLinesCoords->point.finishEditing();

			mIsDragging = TRUE;

			startNotify();

			action->setHandled();
		}		
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		SbVec3f newPoint;
		if( getPoint( action, newPoint ) )
		{
			mLinesCoords->point.set1Value( 0, newPoint );
			mLinesCoords->point.set1Value( 1, newPoint );
			mLinesCoords->point.set1Value( 2, newPoint );
			mLinesCoords->point.set1Value( 3, newPoint );
	
			action->setGrabber( this );
			action->setHandled();
		}		
	}
}

void
SoXipOverlaySelectionFrame::GLRender( SoGLRenderAction* action )
{
	if( !on.getValue() || mIsDragging == FALSE )
		return ;

	glPushAttrib( GL_ENABLE_BIT );
	glDisable( GL_DEPTH_TEST );

	mTopSeparator->GLRender( action );

	glPopAttrib();
}

void
SoXipOverlaySelectionFrame::updateSelection()
{
	if( mLinesCoords->point.getNum() != 4 )
	{
		SoDebugError::post( __FILE__, "Invalid number of points" );
		return ;
	}

	SoNodeList shapes = XipOverlayUtils::getManipulableShapes( mActionNode, FALSE );
	for( int i = 0; i < shapes.getLength(); ++ i )
	{
		SoXipManipulableShape* shape = (SoXipManipulableShape *) shapes[i];

		SbXfBox3f shapeXBox;
		shape->computeXBoundingBox( shapeXBox );

		SbXfBox3f selectionXBox;
		selectionXBox.setTransform( shapeXBox.getTransform() );
		selectionXBox.extendBy( mLinesCoords->point[0] );
		selectionXBox.extendBy( mLinesCoords->point[1] );
		selectionXBox.extendBy( mLinesCoords->point[2] );
		selectionXBox.extendBy( mLinesCoords->point[3] );

		SbVec3f selectionXMin, selectionXMax;
		selectionXBox.getBounds( selectionXMin, selectionXMax );

		SbVec3f shapeXMin, shapeXMax;
		shapeXBox.getBounds( shapeXMin, shapeXMax );

		SbBox2f selection2DBox ( 
			selectionXMin[0], selectionXMin[1], 
			selectionXMax[0], selectionXMax[1] );
		SbVec2f shapeMin( shapeXMin[0], shapeXMin[1] );
		SbVec2f shapeMax( shapeXMax[0], shapeXMax[1] );

		shape->select( selection2DBox.intersect( shapeMin ) && selection2DBox.intersect( shapeMax ) );
	}
}