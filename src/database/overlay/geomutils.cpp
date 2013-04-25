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

#include "geomutils.h"
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/errors/SoDebugError.h>

bool isZero( double value )
{
	return fabs( value ) < ZERO_TOLERANCE;
}

double area2( const SbVec3f& p1, const SbVec3f& p2, const SbVec3f& p3 )
{
	double acx, bcx, acy, bcy;

    acx = p1[0] - p3[0];
    bcx = p2[0] - p3[0];
    acy = p1[1] - p3[1];
    bcy = p2[1] - p3[1];

    return (acx * bcy - acy * bcx);
}

bool isCollinear( const SbVec3f& p1, const SbVec3f& p2, const SbVec3f& p3 )
{
	return isZero( area2( p1, p2, p3 ) );
}

bool isBetween( const SbVec3f& p1, const SbVec3f& p2, const SbVec3f& p3 )
{
	if(! isCollinear( p1, p2, p3 ) )
		return false;

	if( !isZero( p1[0] - p2[0] ) ) 
		return ( p1[0] <= p3[0] && p3[0] <= p2[0] ) || ( p1[0] >= p3[0] && p3[0] >= p2[0] );
	else 
		return ( p1[1] <= p3[1] && p3[1] <= p2[1] ) || ( p1[1] >= p3[1] && p3[1] >= p2[1] );
}

double 
areaPolygon3D( const SoMFVec3f& point, const SbVec3f& normal )
{
	int numPoints = point.getNum();
	if( numPoints < 3 )
		return 0;
    
    // select largest abs coordinate to ignore for projection
    double ax = (normal[0] > 0 ? normal[0] : -normal[0]);     // abs x-coord
    double ay = (normal[1] > 0 ? normal[1] : -normal[1]);     // abs y-coord
    double az = (normal[2] > 0 ? normal[2] : -normal[2]);     // abs z-coord

    // scale to get area before projection
    double an = sqrt( ax * ax + ay * ay + az * az);  // length of normal vector
	double area = 0;

    if( ax > ay )
	{
        if( ax > az )
		{
			// [ignore x-coord]
			for( int i = numPoints - 1, j = 0, k = numPoints - 2; j < numPoints; k = i, i = j ++ )
				area += point[i][1] * (point[j][2] - point[k][2]);

	        return fabs( area * 0.5 * an / ax );
		}
    }
    else if( ay > az )
	{
		// [ignore y-coord]
		for( int i = numPoints - 1, j = 0, k = numPoints - 2; j < numPoints; k = i, i = j ++ )
			area += point[i][0] * (point[j][2] - point[k][2]);
	
		return fabs( area * 0.5 * an / ay );
	}

	// [ignore z-coord]
	for( int i = numPoints - 1, j = 0, k = numPoints - 2; j < numPoints; k = i, i = j ++ )
		area += point[i][0] * (point[j][1] - point[k][1]);

	return fabs( area * 0.5 * an / az );
}

double 
areaPolygon3D( const SoMFVec3f& point, const SoMFInt32& indices, const SbVec3f& normal )
{
	int numIndices = indices.getNum();
	if( numIndices < 3 )
		return 0;

	double area = 0;

	SoMFVec3f tmpPoint;
	const int* iPtr = indices.getValues(0);
	for( int i = 0; i < numIndices; ++ i, ++ iPtr )
	{
		if( *iPtr == -1 )
		{
			area += areaPolygon3D( tmpPoint, normal );
			tmpPoint.setNum(0);
		}
		else
		{
			tmpPoint.set1Value( tmpPoint.getNum(), point[*iPtr] );
		}
	}

	return area;
}

bool
intersect( const SbVec3f& p0, const SbVec3f& p1,
		   const SbVec3f& q0, const SbVec3f& q1,
		   SbVec3f& intersectPoint )
{
	if( SbLine(p0, p1).getClosestPoints( SbLine(q0, q1), intersectPoint, intersectPoint ) )
	{
		return	belongToSegment( intersectPoint, p0, p1 ) &&
				belongToSegment( intersectPoint, q0, q1 );
	}
	return false;
}

/*
void
intersect( const SoMFVec3f& point, SbMatrix model )
{
	SbMatrix inv = model.inverse();

	for( int i = 0; i < coordIndex.getNum(); ++ i )
	{
		int index = coordIndex[i];
		if( index != -1 )
		{
			SbVec3f pt = point[ coordIndex[i] ];

			SbVec3f out;
			inv.multVecMatrix( pt, out );

			if( out[0] >= 0 && out[0] <= 1 && out[1] >= 0 && out[1] <= 1 )
			{
				// FINE
			}
			else
			{
				// OUTSIDE IMAGE, NEED TO FIND INTERSECTIONS ON neighboring segments

				SbVec3f prevPt;
				if( i > 0 )
					prevPt = point[ coordIndex[i-1] ];
				else
					prevPt = point[ coordIndex[i-1] ];


			}
		}
	}
}
*/

SbBool
selfIntersect( const SoMFVec3f& point, SbBool isClosed )
{
	SbVec3f pt;

	int numPoints = point.getNum();

	for( int i = 0; i < numPoints - 1; ++ i )
	for( int j = i + 2; j < numPoints - 1; ++ j )
	{
		if( intersect( point[i], point[i+1], point[j], point[j+1], pt ) )
			return TRUE;	
	}

	if( isClosed )
	{
		for( int j = 1; j < numPoints - 2; ++ j )
		{
			if( intersect( point[numPoints - 1], point[0], point[j], point[j+1], pt ) )
				return TRUE;
		}
	}

	return FALSE;
}

double
angleBetweenVectors( const SbVec3f& u, const SbVec3f& v, const SbVec3f& normal )
{
	double cosAngle = v.dot( u ) / ( u.length() * v.length() );
	float     angle = acos( cosAngle );

	// FIXME: Check if this is required
	//
	SbVec3f cross  = u.cross( v );
	
	if( cross.dot( normal ) < 0 )
		angle = 2 * M_PI - angle;
	//

	return angle;
}

double
angleBetweenVectors( const SbVec3f& u, const SbVec3f& v )
{
	double cosAngle = v.dot( u ) / ( u.length() * v.length() );

	return acos( cosAngle );
}

int
closestPoint( const SoMFVec3f& point, const SbVec3f& ref )
{
	if( point.getNum() )		
	{
		int i_min = 0;
		double dist_min = (point[0] - ref).length();

		int numPoints = point.getNum();
		for( int i = 1; i < numPoints; ++ i )
		{
			float dist = (point[i] - ref).length();
			if( dist < dist_min )
			{
				i_min = i;
				dist_min = dist;
			}		
		}

		return i_min;
	}

	return -1;
}

void
removeClosePoints( SoMFVec3f& point, float minDist )
{
	int numPoints = point.getNum();
	if( numPoints >= 2 )
	{		
		for( int ni = numPoints - 1, i = 0; i < numPoints; )
		{
			if( (point[ni] - point[i]).length() <= minDist )
			{
				point.deleteValues( i, 1 );
				-- numPoints;
			}
			else // move forward
			{
				ni = i ++;
			}
		}
	}
}

void
removeClosePoints( const SoMFVec3f& point, SoMFVec3f& cleanPoints, float minDist )
{
	cleanPoints.setNum( point.getNum() );
	cleanPoints.setValues( 0, point.getNum(), point.getValues(0) );

	int numPoints = cleanPoints.getNum();
	if( cleanPoints.getNum() >= 2 )
	{		
		for( int ni = numPoints - 1, i = 0; i < numPoints; )
		{
			if( (cleanPoints[ni] - cleanPoints[i]).length() <= minDist )
			{
				cleanPoints.deleteValues( i, 1 );
				-- numPoints;
			}
			else // move forward
			{
				ni = i ++;
			}
		}
	}
}

bool
belongToSegment( const SbVec3f& pt, const SbVec3f& s0, const SbVec3f& s1 )
{
	float length = (s0 - s1).length();

	return (pt - s0).length() <= length && (pt - s1).length() <= length;
}

bool
isInsideContour( const SbVec3f& point, const SoMFVec3f& vertices, const SoMFInt32& indices )
{
	SoDebugError::post( __FILE__, "the function isInsideContour() is not supported yet." );
	SoDebugError::post( __FILE__, "Use isInsideClosedContour() instead." );

	return false;
}

bool 
isInsideClosedContour( const SbVec3f& pt, const SoMFVec3f& point )
{
	bool oddNodes = false;

	int numPoints = point.getNum();
	if( numPoints )
	{
		// Shift the vertices so that 'pt' is the origin
		SoMFVec3f tmpPoint;
		tmpPoint.setValues( 0, numPoints, point.getValues(0) );

		SbVec3f* ptr = tmpPoint.startEditing();
		for( int k = 0; k < numPoints; ++ k )
		{
			ptr[k] -= pt;

			if( isZero( ptr[k][0] ) && isZero( ptr[k][1] ) )
				return true;
		}
		
		for( int i = 0, j = numPoints - 1; i < numPoints; j = i ++ )
		{
			if( ptr[i][1] < 0 && ptr[j][1] >= 0 || ptr[j][1] < 0 && ptr[i][1] >= 0 )
			{
				if( ptr[i][0] < ptr[i][1] / (ptr[j][1] - ptr[i][1]) * (ptr[j][0] - ptr[i][0]) )
					oddNodes = !oddNodes;
			}
		}
		tmpPoint.finishEditing();
	}
	
	return oddNodes;
}

SbString 
formatLength( float length )
{
	char tmp[30];

	if (length > 100.f)
	{
		sprintf(tmp, "%.3f cm", length / 10.f);
	}
	else if (length < 0.010f)
	{
		sprintf(tmp, "%.3f µm", length * 1000.f);
	}
	else
	{
		sprintf(tmp, "%.3f mm", length);
	}

	return SbString(tmp);
}

SbMatrix
extractRotationMatrix( const SbMatrix& matrix )
{
	SbVec3f t, s;
	SbRotation r, so;
	matrix.getTransform( t, r, s, so );

	SbMatrix rotationMatrix;
	rotationMatrix.setRotate(r);

	return rotationMatrix;
}

void getScreenPixelVectors(SoGLRenderAction *action, const SbVec3f position, SbVec3f &xPixelVec, SbVec3f &yPixelVec) 
{
	// To compute correct offset in world space we project width of text onto a plane parallel
	// to the near plane of the camera that goes through the current translation of the model matrix.
	SoState *state = action->getState();
	SbPlaneProjector planeProj(FALSE);
	SbViewVolume viewVolume = SoViewVolumeElement::get(state);
	SbViewportRegion viewport = SoViewportRegionElement::get(state);

	planeProj.setViewVolume(viewVolume);
	planeProj.setPlane(SbPlane(viewVolume.getPlane(0.f).getNormal(), position));

	float pixelWidth = 1.f / (float) viewport.getViewportSizePixels()[0];
	float pixelHeight = 1.f / (float) viewport.getViewportSizePixels()[1];

	SbVec3f p1 = planeProj.project(SbVec2f(0, 0));
	SbVec3f p2 = planeProj.project(SbVec2f(pixelWidth, 0));
	xPixelVec = (p2 - p1);

	p2 = planeProj.project(SbVec2f(0, pixelHeight));
	yPixelVec = (p2 - p1);
}

