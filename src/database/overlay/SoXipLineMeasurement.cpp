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
#include <xip/system/standard.h>
#include "geomutils.h"
#include "SoXipLineMeasurement.h"

SO_NODE_SOURCE( SoXipLineMeasurement );

SoXipLineMeasurement::SoXipLineMeasurement()
{
	SO_NODE_CONSTRUCTOR( SoXipLineMeasurement );
}

SoXipLineMeasurement::~SoXipLineMeasurement()
{

}

void
SoXipLineMeasurement::initClass()
{
	SO_NODE_INIT_CLASS( SoXipLineMeasurement, SoXipLine, "SoXipLine" );
}

void
SoXipLineMeasurement::mouseMove( const SbVec3f& pos )
{
	SoXipLine::mouseMove( pos );

	char strDistance[30];
	sprintf(strDistance, "%s", formatLength((point[0] - point[1]).length()));
	caption.setValue(strDistance);

	mShowAnnotation = TRUE;
}

void 
SoXipLineMeasurement::moveHandlerPoint( int id, const SbVec3f& newPos )
{
	SoXipLine::moveHandlerPoint( id, newPos );

	char strDistance[30];
	sprintf(strDistance, "%s", formatLength((point[0] - point[1]).length()));
	caption.setValue(strDistance);	
}
