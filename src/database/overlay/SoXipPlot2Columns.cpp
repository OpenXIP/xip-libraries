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
*	@file	SoXipPlot2Columns.cpp
*	@brief	Implementation of the SoXipPlot2Columns class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipPlot2Element.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipPlot2Columns.h"

SO_KIT_SOURCE( SoXipPlot2Columns );

SoXipPlot2Columns::SoXipPlot2Columns()
{
	SO_KIT_CONSTRUCTOR( SoXipPlot2Columns );

	SO_KIT_ADD_CATALOG_ENTRY( mMainSeparator, SoSeparator, FALSE, this, \x0, TRUE );

	SO_KIT_ADD_CATALOG_ENTRY( mVertices, SoCoordinate3, FALSE, mMainSeparator, \x0, FALSE );

	SO_KIT_ADD_CATALOG_ENTRY( mFaceSeparator, SoSeparator, FALSE, mMainSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mFaceMaterial, SoMaterial, FALSE, mFaceSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mFaces, SoFaceSet,  FALSE, mFaceSeparator, \x0, FALSE );

	SO_KIT_ADD_CATALOG_ENTRY( mBorderSeparator, SoSeparator,  FALSE, mMainSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mBorderColor, SoBaseColor,  FALSE, mBorderSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mBorderStyle, SoDrawStyle,  FALSE, mBorderSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mBorderLines, SoLineSet,  FALSE, mBorderSeparator, \x0, FALSE );

	SO_NODE_ADD_FIELD( label, ("Columns") );
	SO_NODE_ADD_FIELD( data, (0) );
	data.setNum(0);
	SO_NODE_ADD_FIELD( faceColor, (0.2, 0.2, 0.2) );
	SO_NODE_ADD_FIELD( faceTransparency, (0) );
	SO_NODE_ADD_FIELD( borderColor, (0, 0, 0) );
	SO_NODE_ADD_FIELD( borderWidth, (1) );

	SO_KIT_INIT_INSTANCE();
	
	setVertices();

	mDataSensor = new SoFieldSensor( dataSensorCB, this );
	mDataSensor->attach( &data );

	setUpConnections( TRUE, TRUE );
}

void 
SoXipPlot2Columns::initClass()
{
	SO_KIT_INIT_CLASS( SoXipPlot2Columns, SoBaseKit, "BaseKit" );
}

SoXipPlot2Columns::~SoXipPlot2Columns()
{
	if( mDataSensor )
	{
		delete mDataSensor;
		mDataSensor = 0;
	}
}

void
SoXipPlot2Columns::dataSensorCB( void* userData, SoSensor* )
{
	((SoXipPlot2Columns *) userData)->setVertices();
}

SbBool
SoXipPlot2Columns::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if( !doItAlways && connectionsSetUp == onOff )
		return onOff;

	try
	{
		if ( onOff )
		{
			// We connect AFTER base class.
			SoBaseKit::setUpConnections( onOff, FALSE );

			SoMaterial* faceMaterial = SO_GET_ANY_PART( this, "mFaceMaterial", SoMaterial );
			if( faceMaterial )
			{
				faceMaterial->diffuseColor.connectFrom( &faceColor );
				faceMaterial->transparency.connectFrom( &faceTransparency );
			}

			SoBaseColor* borderBaseColor = SO_GET_ANY_PART( this, "mBorderColor", SoBaseColor );
			if( borderBaseColor )
			{
				borderBaseColor->rgb.connectFrom( &borderColor );
			}

			SoDrawStyle* borderStyle = SO_GET_ANY_PART( this, "mBorderStyle", SoDrawStyle );
			if( borderStyle )
			{
				borderStyle->lineWidth.connectFrom( &borderWidth );
			}
		}
		else
		{
			SoMaterial* faceMaterial = SO_GET_ANY_PART( this, "mFaceMaterial", SoMaterial );
			if( faceMaterial )
			{
				faceMaterial->diffuseColor.disconnect();
				faceMaterial->transparency.disconnect();
			}

			SoBaseColor* borderBaseColor = SO_GET_ANY_PART( this, "mBorderColor", SoBaseColor );
			if( borderBaseColor )
			{
				borderBaseColor->rgb.disconnect();
			}

			SoDrawStyle* borderStyle = SO_GET_ANY_PART( this, "mBorderStyle", SoDrawStyle );
			if( borderStyle )
			{
				borderStyle->lineWidth.disconnect();
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
SoXipPlot2Columns::setVertices()
{
	SoCoordinate3* vertices = SO_GET_ANY_PART( this, "mVertices", SoCoordinate3 );
	SoFaceSet* faces = SO_GET_ANY_PART( this, "mFaces", SoFaceSet );
	SoLineSet* lines = SO_GET_ANY_PART( this, "mBorderLines", SoLineSet );

	if( vertices && faces && lines )
	{
		int numData = data.getNum();

		vertices->point.setNum( 4 * numData );	
		faces->numVertices.setNum( numData );
		lines->numVertices.setNum( numData );

		SbVec3f* verticesPtr = vertices->point.startEditing();
		for( int i = 0; i < numData; ++ i )
		{
			verticesPtr[4*i    ] = SbVec3f( i + .9,       0, 0 );			
			verticesPtr[4*i + 1] = SbVec3f( i + .9, data[i], 0 );
			verticesPtr[4*i + 2] = SbVec3f( i + .1, data[i], 0 );
			verticesPtr[4*i + 3] = SbVec3f( i + .1,       0, 0 );			

			faces->numVertices.set1Value( i, 4 );
			lines->numVertices.set1Value( i, 4 );
		}
		vertices->point.finishEditing();	
	}
}

void
SoXipPlot2Columns::GLRender( SoGLRenderAction* action )
{
	SoXipPlot2Element::add(
		action->getState(),
		this,
		label.getValue(),
		borderColor.getValue(),
		faceColor.getValue() );

	SoState* state = action->getState();
	
	state->push();

	// Make sure the DrawStyle is set to FILLED
	SoDrawStyleElement::set( state, SoDrawStyleElement::FILLED ); 

	SoBaseKit::GLRender( action );

	state->pop();
}
