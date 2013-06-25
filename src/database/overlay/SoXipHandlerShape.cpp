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
#include <xip/inventor/overlay/SoXipHandlerShape.h>

SO_NODE_ABSTRACT_SOURCE( SoXipHandlerShape );

SoXipHandlerShape::SoXipHandlerShape()
{
	SO_NODE_CONSTRUCTOR( SoXipHandlerShape );
}

SoXipHandlerShape::~SoXipHandlerShape()
{

}

void
SoXipHandlerShape::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipHandlerShape, SoXipManipulableShape, "SoXipManipulableShape" );
}

void 
SoXipHandlerShape::getHandlerPoints( SoMFVec3f& handlerPoint )
{
	SoMFInt32 dummyCoordIndex;
	SbBool dummyClosed;
	extractGeometries( handlerPoint, dummyCoordIndex, dummyClosed );
}
