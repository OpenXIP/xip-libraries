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
#include <xip/inventor/dicom/SoXipDataDicomElement.h>

SO_ELEMENT_SOURCE(SoXipDataDicomElement);

SoXipDataDicomElement::~SoXipDataDicomElement()
{
}

void SoXipDataDicomElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipDataDicomElement, SoElement );
}

void SoXipDataDicomElement::init( SoState* )
{
	mSliceIndex = 0;
	mDicomObject = 0;
}

void SoXipDataDicomElement::set( SoState* state, SoXipDataDicom* dataDicom, int sliceIndex )
{
    SoXipDataDicomElement *elt = (SoXipDataDicomElement *) getElement(state, classStackIndex);
    if (elt)
	{
		elt->mDicomObject = dataDicom;
		elt->mSliceIndex = sliceIndex;
	}
}

SoXipDataDicom* SoXipDataDicomElement::get( SoState* state )
{
	const SoXipDataDicomElement* elt = (const SoXipDataDicomElement *)
													getConstElement( state, classStackIndex );

	if (elt)
		return (SoXipDataDicom *) elt->mDicomObject;

	return NULL;
}

int SoXipDataDicomElement::getSliceIndex( SoState* state )
{
	const SoXipDataDicomElement* elt = (const SoXipDataDicomElement *)
													getConstElement( state, classStackIndex );

	if (elt)
		return elt->mSliceIndex;

	return (-1);
}


SbBool SoXipDataDicomElement::matches(const SoElement *elt) const
{
	return ((mDicomObject == ((const SoXipDataDicomElement*) elt)->mDicomObject) &&
			(mSliceIndex == ((const SoXipDataDicomElement*) elt)->mSliceIndex));
}

SoElement *SoXipDataDicomElement::copyMatchInfo() const
{
	SoXipDataDicomElement *result = (SoXipDataDicomElement*) getTypeId().createInstance();
	result->mDicomObject = mDicomObject;
	result->mSliceIndex = mSliceIndex;

	return result;
}


