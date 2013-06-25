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

#include <Inventor/engines/SoEngine.h>
#include <Inventor/nodes/SoNode.h>
#include "OIVUtils.h"

SoNode*
createNode( const SbString& className )
{
	SoType type = SoType::fromName( className );
	if( type.isBad() || !type.canCreateInstance() )
		return 0;

	if( type.isDerivedFrom( SoNode::getClassTypeId() ) )
		return (SoNode *) type.createInstance();

	return 0;
}

SoEngine*
createEngine( const SbString& className )
{
	SoType type = SoType::fromName( className );
	if( type.isBad() || !type.canCreateInstance() )
		return 0;

	if( type.isDerivedFrom( SoEngine::getClassTypeId() ) )
		return (SoEngine *) type.createInstance();

	return 0;
}