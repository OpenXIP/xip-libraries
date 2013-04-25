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

#include <xip/system/standard.h>
#include "geomutils.h"
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipAnnotation.h"

SO_NODE_SOURCE( SoXipAnnotation );

SoXipAnnotation::SoXipAnnotation()
{
	SO_NODE_CONSTRUCTOR( SoXipAnnotation );

	SO_XIP_KIT_ADD_ENTRY( mArrowSeparator, SoSeparator, this );
	SO_XIP_KIT_ADD_ENTRY( mArrowTransform, SoMatrixTransform, mArrowSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mArrowCoords, SoCoordinate3, mArrowSeparator );
	SO_XIP_KIT_ADD_ENTRY( mLinesStyle, SoDrawStyle, mArrowSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mArrowIndices, SoIndexedLineSet, mArrowSeparator );	

	// Also attach the geometries to the shadow separator
	((SoSeparator *) mShadowSeparator)->addChild( mArrowSeparator );

	SO_XIP_SHAPE_ADD_FIELD(  angle, (15) );
	SO_XIP_SHAPE_ADD_FIELD( length, (10) );

	mArrowCoords->point.setNum(0);
	mArrowIndices->coordIndex.setNum(0);

	mFinishTextEditingSensor = new SoFieldSensor( finishTextEditingCB, this );
}

SoXipAnnotation::~SoXipAnnotation()
{
	if( mFinishTextEditingSensor )
	{
		delete mFinishTextEditingSensor;
		mFinishTextEditingSensor = 0;
	}
}

void
SoXipAnnotation::initClass()
{
	SO_NODE_INIT_CLASS( SoXipAnnotation, SoXipLine, "SoXipLine" );
}

void
SoXipAnnotation::beforeCreation()
{
	SoXipLine::beforeCreation();

	mArrowCoords->point.setNum(0);
	mArrowIndices->coordIndex.setNum(0);
}

void
SoXipAnnotation::finishTextEditingCB( void* userData, SoSensor* )
{
	SoXipAnnotation* annot = (SoXipAnnotation *) userData;

	if( annot->mAnnotation->isEditing.getValue() == FALSE )
	{
		annot->caption.setValue( annot->mAnnotation->string.getValue() );
		annot->mFinishTextEditingSensor->detach();
	}
}

void
SoXipAnnotation::mouseUp( const SbVec3f& pos )
{
	SoXipLine::mouseUp( pos );

	// Edit the text
	editText();

	mFinishTextEditingSensor->attach( &mAnnotation->isEditing );
}

void 
SoXipAnnotation::GLRender( SoGLRenderAction* action )
{
	if( mIsViewInitialized && point.getNum() == 2 && point[0] != point[1] )
	{
		float angleValue = angle.getValue() * M_PI / 180.;

		SbVec3f screenPt[2];
		mViewVolume.projectToScreen( point[0], screenPt[0] );
		mViewVolume.projectToScreen( point[1], screenPt[1] );

		float lineAngle = angleBetweenVectors( SbVec3f(1, 0, 0), (screenPt[1] - screenPt[0]) );
		if( screenPt[0][1] > screenPt[1][1] )
			lineAngle = 2 * M_PI - lineAngle;

		float arrowLengthPix = length.getValue();

		SbVec3f offsetUp = projectScreenOffsetToWorld( SbVec2s( 
			arrowLengthPix * cos( lineAngle - angleValue ),
			arrowLengthPix * sin( lineAngle - angleValue ) ) );

		SbVec3f offsetDown = projectScreenOffsetToWorld( SbVec2s( 
			arrowLengthPix * cos( lineAngle + angleValue ),
			arrowLengthPix * sin( lineAngle + angleValue ) ) );

		mArrowCoords->point.setNum(3);
		mArrowCoords->point.set1Value( 0, point[0] );
		mArrowCoords->point.set1Value( 1, point[0] + offsetUp );
		mArrowCoords->point.set1Value( 2, point[0] + offsetDown );
		
		int indices[6] = {0, 1, -1, 0, 2, -1};
		mArrowIndices->coordIndex.setNum(6);
		mArrowIndices->coordIndex.setValues( 0, 6, indices );
	}

	SoXipManipulableShape::GLRender( action );
}

void 
SoXipAnnotation::setViewTransform( const SbMatrix& matrix )
{	
	SoXipLine::setViewTransform( matrix );

	// FIXME : needs to find the good transformation for the
	//         arrow
	if( !isTextPicked() )
		((SoMatrixTransform *) mArrowTransform)->matrix.setValue( matrix );
}

void 
SoXipAnnotation::transform( const SbMatrix& matrix )
{
	SoXipLine::transform( matrix );

	((SoMatrixTransform *) mArrowTransform)->matrix.setValue( SbMatrix::identity() );
}

void
SoXipAnnotation::updateEnumerationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() >= 2 )
	{
		const SbVec3f& p0 = point[0];
		const SbVec3f& p1 = point[1];
		
		SbVec3f u = SbVec3f( 1, 0, 0 );
		SbVec3f v = p1 - p0;
		SbVec3f normal = mViewVolume.getPlane(0).getNormal();

		double a = angleBetweenVectors( u, v, normal );
		bool pos_cos = cos(a) > 0;
		bool pos_sin = sin(a) > 0;

		mEnumerationText->justification.setValue( pos_cos ? SoXipText2::LEFT : SoXipText2::RIGHT );
		mEnumerationText->vAlignment.setValue( pos_sin ? SoXipText2::TOP : SoXipText2::BOTTOM );

		SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 5 ) );
		SbVec3f middle;
		middle[0] = (  pos_cos ? offset[0] : -offset[0] ) + ( p0[0] + p1[0] ) / 2.;
		middle[1] = ( !pos_sin ? offset[1] : -offset[1] ) + ( p0[1] + p1[1] ) / 2.;
		middle[2] = ( p0[2] + p1[2] ) / 2.;

		position.setValue( middle );
	}
}

void
SoXipAnnotation::updateAnnotationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() == 2 )
	{
		SbVec3f screenPt[2];
		mViewVolume.projectToScreen( point[0], screenPt[0] );
		mViewVolume.projectToScreen( point[1], screenPt[1] );

		if( screenPt[0][0] < screenPt[1][0] )
		{
			mAnnotation->justification.setValue( SoXipText2::LEFT );
			position.setValue( point[1] + projectScreenOffsetToWorld( SbVec2s( 5, 0 ) ) );
		}
		else
		{
			mAnnotation->justification.setValue( SoXipText2::RIGHT );
			position.setValue( point[1] - projectScreenOffsetToWorld( SbVec2s( 5, 0 ) ) );
		}

		mAnnotation->vAlignment.setValue( SoXipText2::TOP );
	}
}
