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

#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/fields/SoMFInt32.h>
#include <xip/inventor/overlay/SoXipEllipse.h>
#include <xip/inventor/overlay/SoXipText2.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipEllipse );

SoXipEllipse::SoXipEllipse()
{
	SO_NODE_CONSTRUCTOR( SoXipEllipse );

	SO_XIP_SHAPE_ADD_FIELD( center, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( a, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( b, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( precision, (8) );

	mHasFirstPoint = false;
}

SoXipEllipse::~SoXipEllipse()
{

}

void
SoXipEllipse::initClass()
{
	SO_NODE_INIT_CLASS( SoXipEllipse, SoXipManipulableShape, "SoXipManipulableShape" );
}

SbBool
SoXipEllipse::isClosed() const
{
	return TRUE;
}

void
SoXipEllipse::beforeCreation()
{
	SoXipManipulableShape::beforeCreation();

	mHasFirstPoint = false;

	center.setValue( 0, 0, 0 );
	a.setValue( 0, 0, 0 );
	b.setValue( 0, 0, 0 );
}

void
SoXipEllipse::translate( const SbVec3f& offset )
{
	mFirstPoint += offset;
	center = center.getValue() + offset;
}

void
SoXipEllipse::mouseUp( const SbVec3f& newPos )
{
	if( (newPos - mFirstPoint).length() > 5 * projectScreenOffsetToWorld( SbVec2s(1, 1) ).length() )
	{
		status.setValue( NONE );
	}
}

void
SoXipEllipse::mouseMove( const SbVec3f& newPos )
{
	SbVec3f u = projectScreenOffsetToWorld( SbVec2s(1, 0) );
	SbVec3f v = projectScreenOffsetToWorld( SbVec2s(0, 1) );
	
	SbVec3f pos[2];
	pos[0] = SbLine( newPos, newPos + u ).getClosestPoint( mFirstPoint );
	pos[1] = SbLine( newPos, newPos + v ).getClosestPoint( mFirstPoint );

	SbVec3f aTmp = ( newPos - pos[1] ) / 2.f;
	SbVec3f bTmp = ( newPos - pos[0] ) / 2.f;

	// If shift is down, make the ellipse a circle: use the smallest radius
	// in both directions
	if( mHandleEventAction->getEvent()->wasShiftDown() )
	{
		float hRadius = bTmp.length();
		float vRadius = aTmp.length();

		if( hRadius < vRadius )
			aTmp *= ( hRadius / vRadius );
		else
			bTmp *= ( vRadius / hRadius );
	}

	// If Ctrl is down, center the ellipse on first point
	if( mHandleEventAction->getEvent()->wasCtrlDown() )
	{
		a		= 2 * aTmp;
		b		= 2 * bTmp;
		center	= mFirstPoint;
	}
	else
	{
		a		= aTmp;
		b		= bTmp;
		center	= mFirstPoint + aTmp + bTmp;
	}
}

void
SoXipEllipse::mouseDown( const SbVec3f& newPos )
{
	if( mHasFirstPoint )
	{
		status.setValue( NONE );
		return ;		
	}

	mFirstPoint = newPos;
	mHasFirstPoint = true;
}

void 
SoXipEllipse::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Set the points
	int numPoints = 4 * precision.getValue();
	point.setNum( numPoints );	

	SbVec3f* pointPtr = point.startEditing();
	{
		// Ellipse center, horizontal and vertical radiuses
		const SbVec3f& c = center.getValue();
		const SbVec3f& hRadius = a.getValue();
		const SbVec3f& vRadius = b.getValue();

		float angle;
		float angleIncrement = 0.5f * M_PI / (float) precision.getValue();

		for( int i = 0; i < numPoints; ++ i )
		{
			angle = i * angleIncrement;
			pointPtr[i] = c + hRadius * cos( angle ) + vRadius * sin( angle );
		}
	}	
	point.finishEditing();

	// Set the coordinate indices
	XipOverlayUtils::fillCoordIndex( point, TRUE, coordIndex );

	// Ellipses are always closed
	closed = TRUE;
}

void 
SoXipEllipse::transform( const SbMatrix& matrix )
{
	SbVec3f scale;
	SbVec3f translate;
	SbRotation rot;
	SbRotation rottemp;
	matrix.getTransform( translate, rot, scale, rottemp );

	SbVec3f newA;	
	matrix.multVecMatrix( a.getValue(), newA );
	a.setValue( newA - translate );

	SbVec3f newB;
	matrix.multVecMatrix( b.getValue(), newB );
	b.setValue( newB - translate );
	
	SbVec3f	newCenter;
	matrix.multVecMatrix( center.getValue(), newCenter );
	center.setValue( newCenter );
}