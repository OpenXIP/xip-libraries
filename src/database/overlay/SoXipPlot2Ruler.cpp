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
*	@file	SoXipPlot2Ruler.cpp
*	@brief	Implementation of the SoXipPlot2Ruler class
*	@author	Julien Gein
**/

#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/overlay/SoXipPlot2AreaElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include "SoXipPlot2Ruler.h"

SO_NODE_SOURCE( SoXipPlot2Ruler );

SoXipPlot2Ruler::SoXipPlot2Ruler()
{
	SO_NODE_CONSTRUCTOR( SoXipPlot2Ruler );

	SO_NODE_DEFINE_ENUM_VALUE( RulerType,  HORIZONTAL );
	SO_NODE_DEFINE_ENUM_VALUE( RulerType,  VERTICAL );
	SO_NODE_SET_SF_ENUM_TYPE( type, RulerType );

	SO_NODE_ADD_FIELD( type, (VERTICAL) );
	SO_NODE_ADD_FIELD( value, (0) );
	value.setNum(0);

	mCoord = new SoCoordinate3;
	mCoord->point.setNum(0);
	mCoord->ref();

	mLineSet = new SoLineSet;
	mLineSet->numVertices.setValue(0);
	mLineSet->ref();

	mSelectedValue = -1;
}

SoXipPlot2Ruler::~SoXipPlot2Ruler()
{
	mCoord->unref();
	mLineSet->unref();
}

void
SoXipPlot2Ruler::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPlot2Ruler, SoNode, "Node" );
}

void
SoXipPlot2Ruler::GLRender( SoGLRenderAction* action )
{
	SoState* state = action->getState();
	if( !state )
		return ;

	state->push();

	mBBox = SoXipPlot2AreaElement::getBBox( state );

	int numValues = value.getNum();
	mCoord->point.setNum( 2 * numValues );
	mLineSet->numVertices.setNum( numValues );

	if( type.getValue() == HORIZONTAL )
	{
		for( int i = 0; i < numValues; ++ i )
		{
			mCoord->point.set1Value(     2*i, SbVec3f( mBBox.getMin()[0], value[i], 0 ) );
			mCoord->point.set1Value( 1 + 2*i, SbVec3f( mBBox.getMax()[0], value[i], 0 ) );
			mLineSet->numVertices.set1Value( i, 2 );
		}
	}
	else
	{
		for( int i = 0; i < numValues; ++ i )
		{
			mCoord->point.set1Value(     2*i, SbVec3f( value[i], mBBox.getMin()[1], 0 ) );
			mCoord->point.set1Value( 1 + 2*i, SbVec3f( value[i], mBBox.getMax()[1], 0 ) );
			mLineSet->numVertices.set1Value( i, 2 );
		}
	}
	
	action->traverse( mCoord );
	action->traverse( mLineSet );

	state->pop();
}

void
SoXipPlot2Ruler::saveViewInformation( SoHandleEventAction* action )
{
	mViewportRegion = SoViewportRegionElement::get( action->getState() );

	mViewVolume = SoViewVolumeElement::get( action->getState() );	

	mPlaneProj.setViewVolume( mViewVolume );
	mPlaneProj.setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + 0.001 ) );
}

SbVec3f
SoXipPlot2Ruler::projectScreenOffsetToWorld( const SbVec2s& pixelOffset )
{
	SbVec2f normOffset = SbVec2f(
		pixelOffset[0] / (float) mViewportRegion.getViewportSizePixels()[0],
		pixelOffset[1] / (float) mViewportRegion.getViewportSizePixels()[1] );

	return mPlaneProj.project( normOffset ) - mPlaneProj.project( SbVec2f( 0, 0 ) );
}

void
SoXipPlot2Ruler::handleEvent( SoHandleEventAction* action )
{
	const SoEvent* event = action->getEvent();

	if( action->getGrabber() == this )
	{
		if( SO_MOUSE_RELEASE_EVENT( event, BUTTON1 ) )
		{
			action->releaseGrabber();
			action->setHandled();
		}
		else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
		{
			SbVec3f proj = mPlaneProj.project( event->getNormalizedPosition( mViewportRegion ) );

			if( type.getValue() == HORIZONTAL )
			{
				SoXipCursor::setCursor( "UPDOWN" );

				float val = proj[1];
				if( val < mBBox.getMin()[1] )
					val = mBBox.getMin()[1];
				else if( val > mBBox.getMax()[1] )
					val = mBBox.getMax()[1];

				value.set1Value( mSelectedValue, val );
			}
			else
			{
				SoXipCursor::setCursor( "LEFTRIGHT" );
				
				float val = proj[0];
				if( val < mBBox.getMin()[0] )
					val = mBBox.getMin()[0];
				else if( val > mBBox.getMax()[0] )
					val = mBBox.getMax()[0];

				value.set1Value( mSelectedValue, val );
			}

			action->setHandled();
		}
	}
	else if( !action->getGrabber() )
	{		
		saveViewInformation( action );

		if( SO_MOUSE_PRESS_EVENT( event, BUTTON1 ) )
		{
			SbVec3f proj = mPlaneProj.project( event->getNormalizedPosition( mViewportRegion ) );
			
			if( type.getValue() == HORIZONTAL )
			{
				float minDist = projectScreenOffsetToWorld( SbVec2s(0, 3) ).length();
				int numValues = value.getNum();
				for( int i = 0; i < numValues; ++ i )
				{
					if( fabs( proj[1] - value[i] ) < minDist )
					{
						action->setHandled();
						action->setGrabber( this );
						break ;
					}
				}
			}
			else if( type.getValue() == VERTICAL )
			{
				float minDist = projectScreenOffsetToWorld( SbVec2s(3, 0) ).length();
				int numValues = value.getNum();
				for( int i = 0; i < numValues; ++ i )
				{
					if( fabs( proj[0] - value[i] ) < minDist )
					{
						action->setHandled();
						action->setGrabber( this );
					}
				}
			}
		}
		else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
		{
			SbVec3f proj = mPlaneProj.project( event->getNormalizedPosition( mViewportRegion ) );
			
			if( type.getValue() == HORIZONTAL )
			{
				float minDist = projectScreenOffsetToWorld( SbVec2s(0, 3) ).length();
				int numValues = value.getNum();
				for( int i = 0; i < numValues; ++ i )
				{
					if( fabs( proj[1] - value[i] ) < minDist )
					{
						mSelectedValue = i;
						SoXipCursor::setCursor( "UPDOWN" );
						action->setHandled();
						break ;
					}
				}
			}
			else if( type.getValue() == VERTICAL )
			{
				float minDist = projectScreenOffsetToWorld( SbVec2s(3, 0) ).length();
				int numValues = value.getNum();
				for( int i = 0; i < numValues; ++ i )
				{
					if( fabs( proj[0] - value[i] ) < minDist )
					{
						mSelectedValue = i;
						SoXipCursor::setCursor( "LEFTRIGHT" );
						action->setHandled();
						break ;
					}
				}
			}
		}
	}
}