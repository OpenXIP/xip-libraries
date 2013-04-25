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

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include "SoXipPolygon.h"

SO_NODE_SOURCE( SoXipPolygon );

SoXipPolygon::SoXipPolygon()
{
	SO_NODE_CONSTRUCTOR( SoXipPolygon );
}

SoXipPolygon::~SoXipPolygon()
{

}

void
SoXipPolygon::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPolygon, SoXipEditableShape, "SoXipEditableShape" );
}

SbBool
SoXipPolygon::canClose( const SbVec3f& pos ) const
{
	// Do not need to close the shape if already closed
	if( isClosed() )
		return FALSE;

	// The number of points should be at least 4.
	// The 4th point corresponds to the one which is moving.
	if( point.getNum() > 3 )
	{
		// minimum size for contour is given, check if the last point
		// is very close to the start point so we can close the contour
		SbVec3f screenPt[2];
		mViewVolume.projectToScreen( point[0], screenPt[0] );
		mViewVolume.projectToScreen(      pos, screenPt[1] );

		SbVec3f d = screenPt[0] - screenPt[1];
		d[0] *= mViewport.getViewportSizePixels()[0];
		d[1] *= mViewport.getViewportSizePixels()[1];
		d[2] = 0;

		return d.length() < CLOSING_MIN_PIXEL_DISTANCE;
	}

	return FALSE;
}

SbBool
SoXipPolygon::isConsistent() const
{
	// check if the contour size is greater than the minimum size.
	const SbVec3f* pointPtr = point.getValues(0);

	SbBox3f bbox;
	for( int i = 0; i < point.getNum(); ++ i )
		bbox.extendBy( pointPtr[i] );

	SbVec3f bbSize;
	bbox.getSize(bbSize[0], bbSize[1], bbSize[2]);

	float screenScale = mViewVolume.getHeight() / mViewport.getViewportSizePixels()[1];
	float bbLengthPix = bbSize.length() / screenScale;

	return ( bbLengthPix >= (2 * CLOSING_MIN_PIXEL_DISTANCE) );
}

void
SoXipPolygon::translate( const SbVec3f& offset )
{
	SbVec3f* pointPtr = point.startEditing();
	for( int i = 0; i < point.getNum(); ++ i )
		(*pointPtr ++) += offset;
	point.finishEditing();
}

void
SoXipPolygon::mouseUp( const SbVec3f& newPos )
{
	if( isEditing() )
		return ;

	// If the shape can be closed and is consitent (big enough)
	if( canClose( newPos ) && isConsistent() )
	{
		closed.setValue( TRUE );

		// Remove the last point corresponding to the moving point.
		point.setNum( point.getNum() - 1 );

		// Creation is done
		status.setValue( NONE );
	}
	
	// If user keeps the mouse button pressed, then a point should
	// be added when the mouse is released.
	// But to prevent artefact points due to a fast click & move,
	// point are only added if the event is not considered as a
	// click.
	else if( (mMouseUpTime - mMouseDownTime) > mClickTime )
	{
		if (*point.getValues(point.getNum() - 1) != newPos)
			point.set1Value( point.getNum(), newPos );
	}	
}

void
SoXipPolygon::mouseMove( const SbVec3f& newPos )
{
	if( isEditing() )
	{
		if( mControlPointId != -1 )
			point.set1Value( mControlPointId, newPos );
	}
	else
	{
		// Look if the mouse cursor is near the starting point.
		// If so it gets anchored to its position, and the user will be
		// able to close the shape later
		if( canClose( newPos ) )
			point.set1Value( point.getNum() - 1, point[0] );
		else
			point.set1Value( point.getNum() - 1, newPos );
	}
}

void
SoXipPolygon::mouseDown( const SbVec3f& newPos )
{
	if( !isEditing() )
	{
		if( point.getNum() == 0 )
			point.set1Value( point.getNum(), newPos );

		// If the shape can be closed and is consitent (big enough)
		if( canClose( newPos ) && isConsistent() )
		{
			closed.setValue( TRUE );

			// Remove the last point corresponding to the moving point.
			point.setNum( point.getNum() - 1 );

			// Creation is done
			status.setValue( NONE );
		}
		else
		{
			point.set1Value( point.getNum(), newPos );
		}
	}
}

void
SoXipPolygon::mouseDouble( const SbVec3f& newPos )
{
	if( point.getNum() > 3 )
	{
		if( closeOnDblClick.getValue() )
			closed.setValue( TRUE );

		// Remove last point added by the mouseDown event, since events
		// are no more delayed!
		point.setNum( point.getNum() - 1 );

		// Creation is done
		status.setValue( NONE );
		return ;
	}

	point.set1Value( point.getNum(), newPos );
}