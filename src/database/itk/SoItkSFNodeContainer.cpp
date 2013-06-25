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

SO_SFIELD_SOURCE( SoItkSFNodeContainer, SbItkNodeContainer, const SbItkNodeContainer& );

void
SoItkSFNodeContainer::initClass()
{
	SO_SFIELD_INIT_CLASS( SoItkSFNodeContainer, SoSField );
}

void
SoItkSFNodeContainer::setValue()
{
    value = SbItkNodeContainer();    
}

SbBool
SoItkSFNodeContainer::readValue( SoInput* in )
{
	int numElements;

	// Read the values from the input
	if( !in->read( numElements ) )
		return FALSE;

	// Create an ItkArray object that will allocate the array memory
	value = SbItkNodeContainer( numElements );

	// Fill the internal array with the values read from the input
	if( in->isBinary() )
	{
		for( int i = 0; i < numElements; ++ i )
		{
			float values[3];
			float label;

			if( !in->readBinaryArray( values, 3 ) ) return FALSE;
			if( !in->read( label ) ) return FALSE;

			value.insertNode( i, SbVec3f( values ), label );
		}
	}
	else
	{
		char comma, bracket;
		SbVec3f seed;
		float label;

		for( int i = 0; i < numElements; ++ i )
		{
			if( !in->read( comma ) ) return FALSE;
			if( !in->read( bracket ) ) return FALSE;

			for( unsigned int pos = 0; pos < 3; ++ pos )
			{
				if( !in->read( seed[pos] ) ) return FALSE;
			}

			if( !in->read( bracket ) ) return FALSE;
			if( !in->read( label ) ) return FALSE;

			value.insertNode( i, seed, label );		
		}
	}
	return TRUE;
}

void
SoItkSFNodeContainer::writeValue( SoOutput* out ) const
{
	int numElements = value.getNumElements();
	out->write( numElements );	

	if( out->isBinary() )
	{
		for( int i = 0; i < numElements; ++ i )
		{
			out->writeBinaryArray( const_cast< float* >( value.getSeed( i ).getValue() ), 3 );
			out->write( value.getLabel( i ) );
		}
	}
	else
	{
		for( int i = 0; i < numElements; ++ i )
		{
			SbVec3f seed = value.getSeed( i );

			out->write( ", [ " );
			out->write( seed[0] );
			out->write( " " );
			out->write( seed[1] );
			out->write( " " );
			out->write( seed[2] );
			out->write( " ] " );
			out->write( value.getLabel( i ) );
		}
	}
}	
