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
*	@file	SoXipPlot2Curve.cpp
*	@brief	Implementation of the SoXipPlot2Curve class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipPlot2Element.h>
#include <xip/inventor/overlay/SoXipPlot2AreaElement.h>
#include <xip/inventor/overlay/SbXipMarkerShapes.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/elements/SoPointSizeElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipPlot2Curve.h"
#include "XipBSpline.h"
#include "XipHermiteSpline.h"

SO_KIT_SOURCE( SoXipPlot2Curve );

SoXipPlot2Curve::SoXipPlot2Curve()
{
	SO_KIT_CONSTRUCTOR( SoXipPlot2Curve );

	/// Define the kit structure

	SO_KIT_ADD_CATALOG_ENTRY( mMainSeparator, SoSeparator, TRUE, this, \x0, TRUE );

	SO_KIT_ADD_CATALOG_ENTRY( mSwitch, SoSwitch, FALSE, mMainSeparator, \x0, FALSE );

	SO_KIT_ADD_CATALOG_ENTRY( mAreaSeparator, SoSeparator, FALSE, mSwitch, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mAreaMaterial, SoMaterial, FALSE, mAreaSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mAreaCoord, SoCoordinate3, FALSE, mAreaSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mAreaFaceSet, SoIndexedFaceSet, FALSE, mAreaSeparator, \x0, FALSE );

	SO_KIT_ADD_CATALOG_ENTRY( mCurveSeparator, SoSeparator, FALSE, mSwitch, \x0, FALSE );

	SO_KIT_ADD_CATALOG_ENTRY( mLineSeparator, SoSeparator, FALSE, mCurveSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mLineColor, SoBaseColor, FALSE, mLineSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mLineCoord, SoCoordinate3, FALSE, mLineSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mLineSet, SoLineSet, FALSE, mLineSeparator, \x0, FALSE );

	SO_KIT_ADD_CATALOG_ENTRY( mMarkerSeparator, SoSeparator, FALSE, mCurveSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mMarkerMaterial, SoMaterial, FALSE, mMarkerSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mMarkerCoord, SoCoordinate3, FALSE, mMarkerSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mMarkerSet, SoXipMarkerSet, FALSE, mMarkerSeparator, \x0, FALSE );

	/// Define fields

	SO_NODE_DEFINE_ENUM_MARKER_VALUES( markerEnumType );
	SO_NODE_SET_SF_ENUM_TYPE( markerType, markerEnumType );	

	SO_NODE_DEFINE_ENUM_VALUE( LineSmoothingType, NONE );
	SO_NODE_DEFINE_ENUM_VALUE( LineSmoothingType, HERMITE_SPLINE );
	SO_NODE_DEFINE_ENUM_VALUE( LineSmoothingType, B_SPLINE );

	SO_NODE_SET_SF_ENUM_TYPE( lineSmoothing, LineSmoothingType );	

	SO_NODE_ADD_FIELD( label, ("Line" ) );
	SO_NODE_ADD_FIELD( data, (0, 0) );	
	SO_NODE_ADD_FIELD( markerType, (0) );
	SO_NODE_ADD_FIELD( markerColor, (0, 0, 0) );
	SO_NODE_ADD_FIELD( markerTransparency, (0) );
	SO_NODE_ADD_FIELD( lineColor, (0, 0, 0) );
	SO_NODE_ADD_FIELD( lineSmoothing, (NONE) );
	SO_NODE_ADD_FIELD( filled, (FALSE) );

	SO_KIT_INIT_INSTANCE();

	mDataSensors[0] = new SoFieldSensor( dataSensorCB, this );
	mDataSensors[0]->attach( &data );

	mDataSensors[1] = new SoFieldSensor( dataSensorCB, this );
	mDataSensors[1]->attach( &lineSmoothing );

	mFilledSensor = new SoFieldSensor( filledSensorCB, this );
	mFilledSensor->attach( &filled );

	setUpConnections( TRUE, TRUE );

	filledSensorCB( this, 0 );
}

void 
SoXipPlot2Curve::initClass()
{
	SO_KIT_INIT_CLASS( SoXipPlot2Curve, SoBaseKit, "BaseKit" );

	SO_ENABLE( SoGLRenderAction, SoXipPlot2Element );
}

SoXipPlot2Curve::~SoXipPlot2Curve()
{
	if( mDataSensors[0] )
	{
		delete mDataSensors[0];
		mDataSensors[0] = 0;
	}

	if( mDataSensors[1] )
	{
		delete mDataSensors[1];
		mDataSensors[1] = 0;
	}

	if( mFilledSensor )
	{
		delete mFilledSensor;
		mFilledSensor = 0;
	}
}

SbBool
SoXipPlot2Curve::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if( !doItAlways && connectionsSetUp == onOff )
		return onOff;

	try
	{
		if ( onOff )
		{
			// We connect AFTER base class.
			SoBaseKit::setUpConnections( onOff, FALSE );

			SoXipMarkerSet* markers = SO_GET_ANY_PART( this, "mMarkerSet", SoXipMarkerSet );
			if( markers )
			{
				markers->marker.connectFrom( &markerType );
			}

			SoMaterial* markerMaterial = SO_GET_ANY_PART( this, "mMarkerMaterial", SoMaterial );
			if( markerMaterial )
			{
				markerMaterial->diffuseColor.connectFrom( &markerColor );
				markerMaterial->transparency.connectFrom( &markerTransparency );
			}

			SoMaterial* areaMaterial = SO_GET_ANY_PART( this, "mAreaMaterial", SoMaterial );
			if( areaMaterial )
			{
				areaMaterial->diffuseColor.connectFrom( &markerColor );
				areaMaterial->transparency.connectFrom( &markerTransparency );
			}

			SoBaseColor* baseColor = SO_GET_ANY_PART( this, "mLineColor", SoBaseColor );
			if( baseColor )
			{
				baseColor->rgb.connectFrom( &lineColor );
			}
		}
		else
		{
			SoXipMarkerSet* markers = SO_GET_ANY_PART( this, "mMarkerSet", SoXipMarkerSet );
			if( markers )
			{
				markers->marker.disconnect();
			}

			SoMaterial* markerMaterial = SO_GET_ANY_PART( this, "mMarkerMaterial", SoMaterial );
			if( markerMaterial )
			{
				markerMaterial->diffuseColor.disconnect();
				markerMaterial->transparency.disconnect();
			}

			SoMaterial* areaMaterial = SO_GET_ANY_PART( this, "mAreaMaterial", SoMaterial );
			if( areaMaterial )
			{
				areaMaterial->diffuseColor.disconnect();
				areaMaterial->transparency.disconnect();
			}

			SoBaseColor* baseColor = SO_GET_ANY_PART( this, "mLineColor", SoBaseColor );
			if( baseColor )
			{
				baseColor->rgb.disconnect();
			}

			SoBaseKit::setUpConnections( onOff, FALSE );
		}
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Cannot setup connections" );
		return true;
	}

    return !( connectionsSetUp = onOff );
}

void 
SoXipPlot2Curve::getBoundingBox( SoGetBoundingBoxAction* action )
{
	if( data.getNum() >= 2 )
	{
		SoBaseKit::getBoundingBox( action );
	}
}

void 
SoXipPlot2Curve::GLRender( SoGLRenderAction* action )
{
	if( data.getNum() )
	{
		if( filled.getValue() )
		{
			SoXipPlot2Element::add(
				action->getState(),
				this,
				label.getValue(),
				lineColor.getValue(),
				markerColor.getValue() );

			float yMin = SoXipPlot2AreaElement::getBBox( action->getState() ).getMin()[1];

			SoCoordinate3* areaCoord = SO_GET_ANY_PART( this, "mAreaCoord", SoCoordinate3 );
			if( areaCoord )
			{
				int numCoord = areaCoord->point.getNum();
				SbVec3f* verticesPtr = areaCoord->point.startEditing();
				for( int i = numCoord/2; i < numCoord; ++ i )
				{
					verticesPtr[i][1] = yMin;
				}
				areaCoord->point.finishEditing();
			}
		}
		else
		{
			float pointSize = SoPointSizeElement::get( action->getState() );
			float lineWidth = SoLineWidthElement::get( action->getState() );
			unsigned short linePattern = SoLinePatternElement::get( action->getState() );

			SoXipPlot2Element::add(
				action->getState(),
				this,
				label.getValue(),
				lineWidth, linePattern, lineColor.getValue(),
				markerType.getValue(), pointSize, markerColor.getValue() );
		}
	}

	SoState* state = action->getState();
	
	state->push();

	// Make sure the DrawStyle is set to FILLED
	SoDrawStyleElement::set( state, SoDrawStyleElement::FILLED ); 

	if( data.getNum() >= 2 )
	{
		SoBaseKit::GLRender( action );
	}

	state->pop();
}

void
SoXipPlot2Curve::dataSensorCB( void* userData, SoSensor* )
{
	SoXipPlot2Curve* plot = (SoXipPlot2Curve *) userData;

	plot->extractMarkerCoords();
	plot->extractCurveCoords();

	if( plot->filled.getValue() )
	{
		plot->extractAreaFaces();
	}
}

void
SoXipPlot2Curve::filledSensorCB( void* userData, SoSensor* )
{
	SoXipPlot2Curve* plot = (SoXipPlot2Curve *) userData;

	// Set the switch child
	SoSwitch* geomSwitch = SO_GET_ANY_PART( plot, "mSwitch", SoSwitch );
	if( geomSwitch )
	{
		geomSwitch->whichChild.setValue( plot->filled.getValue() ? 0 : 1 );		
	}

	if( plot->filled.getValue() )
	{
		plot->extractAreaFaces();
	}
}

void
SoXipPlot2Curve::extractMarkerCoords()
{	
	SoCoordinate3* markerCoord = SO_GET_ANY_PART( this, "mMarkerCoord", SoCoordinate3 );
	if( markerCoord )
	{
		markerCoord->point.setNum(0);

		int numCoord = data.getNum();
		if( numCoord < 2 )
			return ;
		
		markerCoord->point.setNum( numCoord );
		
		SbVec3f* verticesPtr = markerCoord->point.startEditing();
		for( int i = 0; i < numCoord; ++ i )
		{
			verticesPtr[i] = SbVec3f( data[i][0], data[i][1], 0 );
		}
		markerCoord->point.finishEditing();
	}
}

void
SoXipPlot2Curve::extractCurveCoords()
{	
	SoCoordinate3* markerCoord = SO_GET_ANY_PART( this, "mMarkerCoord", SoCoordinate3 );
	if( markerCoord )
	{
		if( lineSmoothing.getValue() == NONE )
		{
			mCurvePoints.setNum( markerCoord->point.getNum() );
			mCurvePoints.setValues( 0, markerCoord->point.getNum(), markerCoord->point.getValues(0) );
		}
		else if( lineSmoothing.getValue() == HERMITE_SPLINE )
		{
			// number of interpolated points per segment
			const int interpSamples = 10;

			XipHermiteSpline spline( markerCoord->point, FALSE );
			spline.interpolateContour( interpSamples, mCurvePoints );
		}
		else if( lineSmoothing.getValue() == B_SPLINE )
		{
			// number of interpolated points per segment
			const int order = 3;
			const int interpSamples = 10;

			XipBSpline spline( markerCoord->point, 3, FALSE );			
			spline.interpolateContour( interpSamples, mCurvePoints );
		}
	}

	SoCoordinate3* lineCoord = SO_GET_ANY_PART( this, "mLineCoord", SoCoordinate3 );
	if( lineCoord )
	{
		if( mCurvePoints.getNum() >= 2 )
		{
			lineCoord->point.setNum( mCurvePoints.getNum() );
			lineCoord->point.setValues( 0, mCurvePoints.getNum(), mCurvePoints.getValues(0) );
		}
		else
		{
			lineCoord->point.setNum(0);
		}
	}
}

void
SoXipPlot2Curve::extractAreaFaces()
{
	SoCoordinate3* lineCoord = SO_GET_ANY_PART( this, "mLineCoord", SoCoordinate3 );
	SoCoordinate3* areaCoord = SO_GET_ANY_PART( this, "mAreaCoord", SoCoordinate3 );
	SoIndexedFaceSet* faces = SO_GET_ANY_PART( this, "mAreaFaceSet", SoIndexedFaceSet );

	if( areaCoord && lineCoord && faces )
	{
		areaCoord->point.setNum(0);
		faces->coordIndex.setNum(0);

		int numLineVertices = lineCoord->point.getNum();
		if( !numLineVertices )
			return ;

		areaCoord->point.setNum( 2 * numLineVertices );
		areaCoord->point.setValues( 0, numLineVertices, lineCoord->point.getValues(0) );

		SbVec3f* verticesPtr = areaCoord->point.startEditing();

		float minY = verticesPtr[0][1];
		for( int i = 1; i < numLineVertices; ++ i )
		{
			if( verticesPtr[i][1]  < minY )
				minY = verticesPtr[i][1];
		}

		for( int j = 0; j < numLineVertices; ++ j )
		{
			verticesPtr[j+numLineVertices] = SbVec3f( verticesPtr[j][0], minY, 0 );
		}

		areaCoord->point.finishEditing();

		faces->coordIndex.setNum( 8*(numLineVertices-1) );

		int* indPtr = faces->coordIndex.startEditing();

		for( int k = 0; k < numLineVertices-1; ++ k )
		{
			indPtr[ 8*k     ] = k + numLineVertices;
			indPtr[ 8*k + 1 ] = k + 1;
			indPtr[ 8*k + 2 ] = k;
			indPtr[ 8*k + 3 ] = -1;

			indPtr[ 8*k + 4 ] = k + numLineVertices;
			indPtr[ 8*k + 5 ] = k + numLineVertices + 1;
			indPtr[ 8*k + 6 ] = k + 1;
			indPtr[ 8*k + 7 ] = -1;
		}

		faces->coordIndex.finishEditing();
	}
}