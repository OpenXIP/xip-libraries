/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipOverlayExtractContour.h"
#include "SoXipShapeList.h"
#include  <xip/inventor/overlay/SoXipManipulableShape.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_ENGINE_SOURCE( SoXipOverlayExtractContour );

SoXipOverlayExtractContour::SoXipOverlayExtractContour()
{
	SO_ENGINE_CONSTRUCTOR( SoXipOverlayExtractContour );

	SO_ENGINE_ADD_INPUT(   overlays,       (0) );
	SO_ENGINE_ADD_INPUT(    extract,        () );
	overlays.setNum(0);

	SO_ENGINE_ADD_OUTPUT(      point, SoMFVec3f );
	SO_ENGINE_ADD_OUTPUT( coordIndex, SoMFInt32 );
}

SoXipOverlayExtractContour::~SoXipOverlayExtractContour()
{

}

void
SoXipOverlayExtractContour::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipOverlayExtractContour, SoEngine, "Engine" );
}

void
SoXipOverlayExtractContour::inputChanged( SoField* whichField )
{
	if( whichField == &extract )
	{
		point.enable( TRUE );
		coordIndex.enable( TRUE );
	}
}

void
SoXipOverlayExtractContour::evaluate()
{
	SoMFVec3f pointTmp;
	SoMFInt32 coordIndexTmp;

	for( int i = 0; i < overlays.getNum(); ++ i )
	{
		SoXipShapeList* shapeList = (SoXipShapeList *) overlays[i];
		if( !shapeList )
		{
			SoDebugError::post( __FILE__, "Warning. Should not have NULL pointer in list of overlays" );
			continue ;
		}

		int numShapes = shapeList->getNumChildren();
		for( int j = 0; j < numShapes; ++ j )
		{
			SoXipManipulableShape* shape = (SoXipManipulableShape *) shapeList->getChild(j);
			if( !shape )
			{
				SoDebugError::post( __FILE__, "Warning. Should not have NULL pointer in list of overlays" );
				continue ;
			}

			appendContour( shape, pointTmp, coordIndexTmp );
		}
	}

	SO_ENGINE_OUTPUT( point, SoMFVec3f, copyFrom( pointTmp ) );
	SO_ENGINE_OUTPUT( coordIndex, SoMFInt32, copyFrom( coordIndexTmp ) );
}

void 
SoXipOverlayExtractContour::appendContour( SoXipManipulableShape* shape,
										   SoMFVec3f& accumulatePoint, SoMFInt32& accumulateCoordIndex )
{
	if( !shape->isClosed() )
	{
		SoDebugError::post( __FILE__, "Contour extraction does not operate on shapes with opened contours" );
		return ;
	}

	int oldNumPoints = accumulatePoint.getNum();
	int oldNumIndices = accumulateCoordIndex.getNum();
	
	SoMFVec3f linePoints;
	SoMFInt32 lineIndices;
	SbBool closed;
	shape->extractGeometries( linePoints, lineIndices, closed );

	accumulatePoint.setValues( oldNumPoints, linePoints.getNum(), linePoints.getValues(0) );
	accumulateCoordIndex.setValues( oldNumIndices, lineIndices.getNum(), lineIndices.getValues(0) );

	int* indPtr = accumulateCoordIndex.startEditing() + oldNumIndices;
	for( int i = 0; i < lineIndices.getNum(); ++ i, ++ indPtr )
	{
		if( *indPtr != -1 )
			*indPtr += oldNumPoints;		
	}
	accumulateCoordIndex.finishEditing();
}
