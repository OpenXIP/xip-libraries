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
#include "geomutils.h"
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include "SoXipPolygonArea.h"

SO_ENGINE_SOURCE( SoXipPolygonArea );

SoXipPolygonArea::SoXipPolygonArea()
{
	SO_ENGINE_CONSTRUCTOR( SoXipPolygonArea );

	SO_ENGINE_ADD_INPUT(      point, (0, 0, 0) );
	SO_ENGINE_ADD_INPUT( coordIndex,       (0) );
	coordIndex.setNum(0);

	SO_ENGINE_ADD_OUTPUT(      area, SoSFFloat );
}

SoXipPolygonArea::~SoXipPolygonArea()
{

}

void
SoXipPolygonArea::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipPolygonArea, SoEngine, "Engine" );
}

void
SoXipPolygonArea::evaluate()
{
	SO_ENGINE_OUTPUT( area, SoSFFloat, setValue(0) );

    if( point.getNum() <= 3 )
        return ;
	SbVec3f normal = (point[0] - point[1]).cross( point[0] - point[2] );
	normal.normalize();

	if( coordIndex.getNum() )
	{
		SO_ENGINE_OUTPUT( area, SoSFFloat, setValue( areaPolygon3D( point, coordIndex, normal )));
	}
	else
	{
		SO_ENGINE_OUTPUT( area, SoSFFloat, setValue( areaPolygon3D( point, normal )));
	}
}

