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
#include <xip/inventor/itk/SoItkSFNodeContainer.h>
#include "SoItkNodeContainer.h"

SO_ENGINE_SOURCE( SoItkNodeContainer )

SoItkNodeContainer::SoItkNodeContainer()
{
	SO_ENGINE_CONSTRUCTOR( SoItkNodeContainer );

	SO_ENGINE_ADD_INPUT( DefaultLabel, (0) );

	SO_ENGINE_ADD_INPUT( Seeds, (0, 0, 0) );
	SO_ENGINE_ADD_INPUT( Labels, (0) );

	Seeds.setNum( 0 );
	Labels.setNum( 0 );

	SO_ENGINE_ADD_OUTPUT( NodeContainer, SoItkSFNodeContainer );
}

SoItkNodeContainer::~SoItkNodeContainer()
{

	
}

void
SoItkNodeContainer::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkNodeContainer, SoEngine, "Engine" );	
}

void
SoItkNodeContainer::inputChanged( SoField* field )
{
	try
	{
		if( field == &Labels )
		{
			unsigned int oldSize = Seeds.getNum();
			unsigned int newSize = Labels.getNum();
			Seeds.setNum( newSize );
			for( unsigned int i = oldSize; i < newSize; ++ i )
				Seeds.set1Value( i, SbVec3f( 0, 0, 0 ) );
		}
		else if ( field == &Seeds )
		{
			unsigned int oldSize = Labels.getNum();
			unsigned int newSize = Seeds.getNum();
			Labels.setNum( newSize );
			for( unsigned int i = oldSize; i < newSize; ++ i )
				Labels.set1Value( i, DefaultLabel.getValue() );
		}
	}
	catch(...)
	{
		SoError::post( "SoItkNodeContainer: unexpected error in inputChanged()" );
	}
}

void
SoItkNodeContainer::evaluate()
{
	try
	{
		int numElements = Labels.getNum();

		SbItkNodeContainer nodeContainer( numElements );

		for( int i = 0; i < numElements; ++ i )
			nodeContainer.insertNode( i, Seeds[i], Labels[i] );

		SO_ENGINE_OUTPUT( NodeContainer, SoItkSFNodeContainer, setValue( nodeContainer ) );
	}
	catch(...)
	{
		SoError::post( "SoItkNodeContainer: unexpected error in evaluate()" );

		SO_ENGINE_OUTPUT( NodeContainer, SoItkSFNodeContainer, setValue( SbItkNodeContainer() ) );
	}	
}
