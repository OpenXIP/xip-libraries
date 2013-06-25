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

#include <xip/inventor/core/SoXipDataImageElement.h>

SO_ELEMENT_SOURCE( SoXipDataImageElement );

SoXipDataImageElement::~SoXipDataImageElement()
{

}

void 
SoXipDataImageElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipDataImageElement, SoElement );
}

void 
SoXipDataImageElement::init( SoState* )
{
	mImage = 0;
	mImageIndex = -1;
	mSliceIndex = -1;
	mNumImages = -1;
	mNumSlices = -1;
}

void 
SoXipDataImageElement::set( SoState* state, SoXipDataImage* dataImage )
{
	SoXipDataImageElement* elt = (SoXipDataImageElement *) getElement( state, classStackIndex );
	if( elt )
	{
		elt->mImage = dataImage;
		elt->mImageIndex = -1;
		elt->mSliceIndex = -1;
		elt->mNumImages = -1;
		elt->mNumSlices = -1;
	}
}

void 
SoXipDataImageElement::set( SoState* state, SoXipDataImage* dataImage,
						    unsigned int imageIndex, unsigned int sliceIndex,
							unsigned numImages, unsigned int numSlices )
{
	SoXipDataImageElement* elt = (SoXipDataImageElement *) getElement( state, classStackIndex );
	if( elt )
	{
		elt->mImage = dataImage;
		elt->mImageIndex = imageIndex;
		elt->mSliceIndex = sliceIndex;
		elt->mNumImages = numImages;
		elt->mNumSlices = numSlices;
	}
}

SoXipDataImage* 
SoXipDataImageElement::get( SoState* state )
{
	const SoXipDataImageElement* elt = (const SoXipDataImageElement *)
		getConstElement( state, classStackIndex );

	if( elt )
		return elt->mImage;

	return NULL;
}

unsigned int
SoXipDataImageElement::getSliceIndex( SoState* state )
{
	const SoXipDataImageElement* elt = (const SoXipDataImageElement *)
		getConstElement( state, classStackIndex );

	if( elt )
		return elt->mSliceIndex;

	return -1;
}

unsigned int
SoXipDataImageElement::getImageIndex( SoState* state )
{
	const SoXipDataImageElement* elt = (const SoXipDataImageElement *)
		getConstElement( state, classStackIndex );

	if( elt )
		return elt->mImageIndex;

	return -1;
}

unsigned int
SoXipDataImageElement::getNumSlices( SoState* state )
{
	const SoXipDataImageElement* elt = (const SoXipDataImageElement *)
		getConstElement( state, classStackIndex );

	if( elt )
		return elt->mNumSlices;

	return -1;
}

unsigned int
SoXipDataImageElement::getNumImages( SoState* state )
{
	const SoXipDataImageElement* elt = (const SoXipDataImageElement *)
		getConstElement( state, classStackIndex );

	if( elt )
		return elt->mNumImages;

	return -1;
}

SbBool 
SoXipDataImageElement::matches( const SoElement* elt ) const
{
	const SoXipDataImageElement* other = (const SoXipDataImageElement *) elt;

	return 
		mImage == other->mImage &&
		mImageIndex == other->mImageIndex &&
		mSliceIndex == other->mSliceIndex &&
		mNumImages == other->mNumImages &&
		mNumSlices == other->mNumSlices;
}

SoElement*
SoXipDataImageElement::copyMatchInfo() const
{
	SoXipDataImageElement* result = (SoXipDataImageElement *) getTypeId().createInstance();
	result->mImage = mImage;
	result->mImageIndex = mImageIndex;
	result->mSliceIndex = mSliceIndex;
	result->mNumImages = mNumImages;
	result->mNumSlices = mNumSlices;

	return result;
}
