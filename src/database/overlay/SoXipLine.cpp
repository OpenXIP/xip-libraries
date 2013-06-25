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
#include "SoXipLine.h"

SO_NODE_SOURCE( SoXipLine );

SoXipLine::SoXipLine()
{
	SO_NODE_CONSTRUCTOR( SoXipLine );
}

SoXipLine::~SoXipLine()
{

}

void
SoXipLine::initClass()
{
	SO_NODE_INIT_CLASS( SoXipLine, SoXipPolyLine, "SoXipPolyLine" );
}

void
SoXipLine::mouseDouble( const SbVec3f& newPos )
{
	if( point.getNum() > 2 )
	{
		// Remove the last point resulting from the mouse down event
		point.setNum( point.getNum() - 1 );
	}

	if( point.getNum() == 2 &&
		(point[0] - point[1]).length() > 2 * projectScreenOffsetToWorld( SbVec2s(1, 1) ).length() )
	{
		// Creation is done
		status.setValue( NONE );
	}
}

void
SoXipLine::mouseUp( const SbVec3f& newPos )
{
	if( isCreating() )
	{
		// This is to prevent artefact points due a fast mouse move
		if( (mMouseUpTime - mMouseDownTime) > mClickTime &&
			(newPos - point[0]).length() > 2 * projectScreenOffsetToWorld( SbVec2s(1, 1) ).length() )
		{
			// Creation is done
			status.setValue( NONE );
		}
	}
}

void
SoXipLine::mouseDown( const SbVec3f& newPos )
{
	if( point.getNum() == 0 )
	{
		point.set1Value( point.getNum(), newPos );
		point.set1Value( point.getNum(), newPos );
	}
	else if( point.getNum() == 2 &&
		(newPos - point[0]).length() > 2 * projectScreenOffsetToWorld( SbVec2s(1, 1) ).length() )
	{
		status.setValue( NONE );
	}
}
