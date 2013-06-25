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
#include <xip/inventor/itk/SbItkNodeContainer.h>

SbItkNodeContainer::SbItkNodeContainer() : mNumElements( 0 )
{
    
}

SbItkNodeContainer::SbItkNodeContainer( int numElements ) : mNumElements( numElements )
{
    mSeeds.resize( numElements );
    mLabels.resize( numElements );
}

SbItkNodeContainer::~SbItkNodeContainer()
{

}

bool
SbItkNodeContainer::isEmpty() const
{
    return mNumElements == 0;
}

int
SbItkNodeContainer::getNumElements() const
{
    return mNumElements;
}

const SbVec3f&
SbItkNodeContainer::getSeed( int index ) const
{
	return mSeeds[ index ];
}

float
SbItkNodeContainer::getLabel( int index ) const
{
	return mLabels[ index ];
}

void
SbItkNodeContainer::insertNode( int index, SbVec3f seed, float label )
{
	mSeeds[index] = seed;
	mLabels[index] = label;
}

bool 
SbItkNodeContainer::operator ==( const SbItkNodeContainer& rhs ) const
{
	int index;

	if( mNumElements != rhs.mNumElements )
	{
		return false;
	}
	for( index = 0; index < mNumElements; ++ index )
	{
		if( mLabels[index] != rhs.mLabels[index] )
			return false;
	}
	for( index = 0; index < mNumElements; ++ index )
	{
		if( mSeeds[index] != rhs.mSeeds[index] )
			return false;
	}
	return true;
}
