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
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipAngle.h"
#include "SoXipLine.h"
#include "geomutils.h"

SO_NODE_SOURCE( SoXipAngle );

SoXipAngle::SoXipAngle()
{
	SO_NODE_CONSTRUCTOR( SoXipAngle );

	addChild( new SoXipLine );
	addChild( new SoXipLine );

	setCreationChild(1);

	setUpConnections( TRUE, TRUE );
}

SoXipAngle::~SoXipAngle()
{

}

void 
SoXipAngle::initClass()
{
	SO_NODE_INIT_CLASS( SoXipAngle, SoXipShapeGroup, "SoXipShapeGroup" );
}	

void
SoXipAngle::GLRender( SoGLRenderAction* action )
{
	if( !on.getValue() )
		return ;

	computeAngle();

	SoXipShapeGroup::GLRender( action );
}

void
SoXipAngle::computeAngle()
{
	SoXipLine* line0 = (SoXipLine *) getChild(0);
	SoXipLine* line1 = (SoXipLine *) getChild(1);

	if( line0->point.getNum() == 2 && line1->point.getNum() == 2 )
	{
		SbVec3f u = line0->point[1] - line0->point[0];
		SbVec3f v = line1->point[1] - line1->point[0];

		float angle = 0;
		if( u.length() && v.length() )
		{
			angle = angleBetweenVectors( u, v, u.cross(v) );
		}

		// Convert to degrees
		angle = angle * 180. / M_PI; 

		if(angle > 180)
			angle = 360 - angle;

		char stringName[1024];
		sprintf( stringName, "%.0f deg.", angle);
		line0->caption.setValue( stringName );
	}
}

void 
SoXipAngle::setRank( int rank )
{
	((SoXipShape *) getChild(1))->rank.setValue( rank );
}

void 
SoXipAngle::setCaption( const SbString& caption )
{
	((SoXipShape *) getChild(1))->caption.setValue( caption );
}
