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
#include <Inventor/projectors/SbPlaneProjector.h>
#include "SoXipRectangle.h"
#include  <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipRectangle );

SoXipRectangle::SoXipRectangle()
{
	SO_NODE_CONSTRUCTOR( SoXipRectangle );

	SO_XIP_SHAPE_ADD_FIELD( p0, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( p1, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( p2, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( p3, (0, 0, 0) );

	mHasFirstPoint = false;
}

SoXipRectangle::~SoXipRectangle()
{

}

void
SoXipRectangle::initClass()
{
	SO_NODE_INIT_CLASS( SoXipRectangle, SoXipManipulableShape, "SoXipManipulableShape" );
}

SbBool
SoXipRectangle::isClosed() const
{
	return TRUE;
}

void
SoXipRectangle::beforeCreation()
{
	SoXipManipulableShape::beforeCreation();

	mHasFirstPoint = false;

	p0.setValue( 0, 0, 0 );
	p1.setValue( 0, 0, 0 );
	p2.setValue( 0, 0, 0 );
	p3.setValue( 0, 0, 0 );
}

void
SoXipRectangle::translate( const SbVec3f& offset )
{
	mFirstPoint += offset;
	p0 = p0.getValue() + offset;
	p1 = p1.getValue() + offset;
	p2 = p2.getValue() + offset;
	p3 = p3.getValue() + offset;
}

void
SoXipRectangle::mouseUp( const SbVec3f& newPos )
{	
	if( (newPos - p0.getValue()).length() > 5 * projectScreenOffsetToWorld( SbVec2s(1, 1) ).length() )
	{
		status.setValue( NONE );
	}
}

void
SoXipRectangle::mouseMove( const SbVec3f& newPos )
{
	SbVec3f u = projectScreenOffsetToWorld( SbVec2s(1, 0) );
	SbVec3f v = projectScreenOffsetToWorld( SbVec2s(0, 1) );
	
	SbVec3f widthVec = newPos - SbLine( newPos, newPos + u ).getClosestPoint( mFirstPoint );
	SbVec3f heightVec = newPos - SbLine( newPos, newPos + v ).getClosestPoint( mFirstPoint );

	// If shift is down, make the rectangle a square: use the smallest edge
	// for both width and height
	if( mHandleEventAction->getEvent()->wasShiftDown() )
	{
		float width = widthVec.length();
		float height = heightVec.length();

		if( width < height )
			heightVec *= (width / height);
		else
			widthVec *= (height / width);
	}
	
	// If Ctrl is down, center the rectangle on first point
	if( mHandleEventAction->getEvent()->wasCtrlDown() )
	{
		p0.setValue( mFirstPoint - widthVec/2 - heightVec/2 );
		p1.setValue( mFirstPoint + widthVec/2 - heightVec/2 );
		p2.setValue( mFirstPoint + widthVec/2 + heightVec/2 );
		p3.setValue( mFirstPoint - widthVec/2 + heightVec/2 );
	}
	else
	{
		p0.setValue( mFirstPoint );	
		p1.setValue( p0.getValue() + widthVec );
		p2.setValue( p0.getValue() + widthVec + heightVec );
		p3.setValue( p0.getValue() + heightVec );
	}
}

void
SoXipRectangle::mouseDown( const SbVec3f& newPos )
{
	if( mHasFirstPoint )
	{
		status.setValue( NONE );
		return ;		
	}
    
    mFirstPoint = newPos;

	p0.setValue( newPos );
	p1.setValue( newPos );
	p2.setValue( newPos );
	p3.setValue( newPos );

	mHasFirstPoint = true;
}

void 
SoXipRectangle::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Rectangles are always closed
	closed = TRUE;

	// Set 4 rectangle corners
	point.setNum(4);
	point.set1Value( 0, p0.getValue() );
	point.set1Value( 1, p1.getValue() );
	point.set1Value( 2, p2.getValue() );
	point.set1Value( 3, p3.getValue() );
	
	// Set indices
	XipOverlayUtils::fillCoordIndex( point, closed, coordIndex );
}

void 
SoXipRectangle::transform( const SbMatrix& matrix )
{
	SbVec3f pt;
	matrix.multVecMatrix( p0.getValue(), pt );
	p0.setValue( pt );
	matrix.multVecMatrix( p1.getValue(), pt );
	p1.setValue( pt );
	matrix.multVecMatrix( p2.getValue(), pt );
	p2.setValue( pt );
	matrix.multVecMatrix( p3.getValue(), pt );
	p3.setValue( pt );
}