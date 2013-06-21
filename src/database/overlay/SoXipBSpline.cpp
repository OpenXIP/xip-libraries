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
#include "SoXipBSpline.h"
#include "XipBSpline.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include "geomutils.h"

SO_NODE_SOURCE( SoXipBSpline );

SoXipBSpline::SoXipBSpline()
{
	SO_NODE_CONSTRUCTOR( SoXipBSpline );

	SO_NODE_ADD_FIELD( degree, (3) );
	SO_NODE_ADD_FIELD( alpha, (10) );

	// By default, make the spline closed
	closed.setValue( TRUE );
}

SoXipBSpline::~SoXipBSpline()
{

}

void
SoXipBSpline::initClass()
{
	SO_NODE_INIT_CLASS( SoXipBSpline, SoXipPolygon, "SoXipPolygon" );
}

void
SoXipBSpline::beforeCreation()
{
	SoXipManipulableShape::beforeCreation();
		
	point.setNum(0);
}

void 
SoXipBSpline::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Read information from the shape
	closed = this->closed.getValue();

	// Remove points that are too close from each other
	SoMFVec3f cleanPoints;
	removeClosePoints( this->point, cleanPoints, 0.001 );

	XipBSpline spline( cleanPoints, degree.getValue(), closed );
	spline.interpolateContour( alpha.getValue(), point );

	// Set the coordinate indices
	XipOverlayUtils::fillCoordIndex( point, closed, coordIndex );
}

int
SoXipBSpline::getPreviousControlPoint( int id ) const
{
	return id / alpha.getValue();
}
