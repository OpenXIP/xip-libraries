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
#include "SoXipHermiteSpline.h"
#include "XipHermiteSpline.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include "geomutils.h"

SO_NODE_SOURCE( SoXipHermiteSpline );

SoXipHermiteSpline::SoXipHermiteSpline()
{
	SO_NODE_CONSTRUCTOR( SoXipHermiteSpline );

	SO_NODE_ADD_FIELD( alpha, (10) );

	// By default, make the spline closed
	closed.setValue( TRUE );
}

SoXipHermiteSpline::~SoXipHermiteSpline()
{

}

void
SoXipHermiteSpline::initClass()
{
	SO_NODE_INIT_CLASS( SoXipHermiteSpline, SoXipPolygon, "SoXipPolygon" );
}

void
SoXipHermiteSpline::beforeCreation()
{
	SoXipManipulableShape::beforeCreation();
		
	point.setNum(0);
}

void 
SoXipHermiteSpline::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Read close property from the shape
	closed = this->closed.getValue();

	SoMFVec3f cleanPoints;
#if !defined(linux)
	removeClosePoints( this->point, cleanPoints, 0.001 );
#endif // !defined(linux)
	XipHermiteSpline spline( cleanPoints, closed );
	spline.interpolateContour( alpha.getValue(), point );

	// Set the coordinate indices
	XipOverlayUtils::fillCoordIndex( point, closed, coordIndex );
}

int
SoXipHermiteSpline::getPreviousControlPoint( int id ) const
{
	return id / alpha.getValue();
}


