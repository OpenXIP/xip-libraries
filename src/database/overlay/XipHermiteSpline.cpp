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

#include "XipHermiteSpline.h"

XipHermiteSpline::XipHermiteSpline( const SoMFVec3f& controlPoints, SbBool closed )
	: mClosed( closed )
{
	mControlPoints.copyFrom( controlPoints );
}

XipHermiteSpline::~XipHermiteSpline()
{

}

void
XipHermiteSpline::interpolateSegment( const SbVec3f& p0, const SbVec3f& p1,
									  const SbVec3f& m0, const SbVec3f& m1,
									  SbVec3f* curvePointPtr, int numPoints )
{
	float dt = 1.0f / (float) (numPoints - 1);
	float  t = 0;

	for( int i = 0; i < numPoints; ++ i, t += dt )
	{
		float t2 = t * t;
		float t3 = t * t2;

		float h00 =  2*t3 - 3*t2 + 1;
		float h10 =    t3 - 2*t2 + t;
		float h01 = -2*t3 + 3*t2;
		float h11 =    t3 - t2;

		*curvePointPtr ++ = h00 * p0 + h10 * m0 + h01 * p1 + h11 * m1;
	}
}

void
XipHermiteSpline::interpolateContour( int numPointsPerSegment, SoMFVec3f& output )
{
	int numControlPoints = mControlPoints.getNum();
	if( numControlPoints <= 2 )
	{
		output.setNum( numControlPoints );
		output.setValues( 0, numControlPoints, mControlPoints.getValues(0) );
		return ;
	}
	
	int numSegments = numControlPoints - 1;
	if( mClosed )
		++ numSegments;
	
	output.setNum( numSegments * numPointsPerSegment );

	SbVec3f* outputPtr = output.startEditing();
	for( int i = 0; i < numSegments; ++ i )
	{
		const SbVec3f* P[4];
		P[0] = &mControlPoints[ ( i + numControlPoints - 1 ) % numControlPoints ];
		P[1] = &mControlPoints[ i ];
		P[2] = &mControlPoints[ ( i + 1 ) % numControlPoints ];
		P[3] = &mControlPoints[ ( i + 2 ) % numControlPoints ];

		float d = (*P[2] - *P[1]).length();

		// When points are very close, the traditionnal tangent computation leads to
		// bad results. A looping artefact results from the fact that the tangent of
		// the first point is much longer than the segments we want to interpolate.
		// Therefore, the tangent length is set according to this segment distance.
		// The shorter the segment is, the shorter the tangent is.
		// That's why we need to remove points which are very close from each other,
		// to avoid division by zero (which would lead to huge tangents).
		//
		// default tangents equation:
		// T[i] = ½[P(i) - P(i-1)] + ½[P(i+1) - P(i)]
		//
		SbVec3f T[2] = {
			.5 * ( *P[2] - *P[1] ) + .5 * ( *P[1] - *P[0] ) * d / (*P[1] - *P[0]).length(),
			.5 * ( *P[2] - *P[1] ) + .5 * ( *P[3] - *P[2] ) * d / (*P[3] - *P[2]).length()
		};

		if( !mClosed && i == 0 )
		{
			T[0] = .5 * ( *P[2] - *P[1] );
		}
		else if( !mClosed && i == numControlPoints - 2 )
		{
			T[1] = .5 * ( *P[2] - *P[1] );
		}

		interpolateSegment( *P[1], *P[2], T[0], T[1], outputPtr, numPointsPerSegment );

		outputPtr += numPointsPerSegment;
	}
	output.finishEditing();
}