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

#include <xip/inventor/core/SoXipMprActiveElement.h>

SO_ELEMENT_SOURCE(SoXipMprActiveElement);

////////////////////////////////////////////////////////////////////////

SoXipMprActiveElement::~SoXipMprActiveElement()
{
}


void
SoXipMprActiveElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipMprActiveElement, SoReplacedElement);	
}

void
SoXipMprActiveElement::init(SoState *)
{
	mprId = 0;
	mprIdField = 0;
}


void
SoXipMprActiveElement::set(SoState *state, SoNode *node, const int32_t index, SoSFInt32* indexField)
{
    SoXipMprActiveElement	*elt;

    // get an instance we can change (pushing if necessary)
    elt = (SoXipMprActiveElement *)	getElement(state, classStackIndex, node);

    if ( (elt != NULL) )
	{
		elt->mprId = index;
		elt->mprIdField = indexField;
	}
}

SoSFInt32*  
SoXipMprActiveElement::getMprFieldIndex(SoState *state) 
{
	const SoXipMprActiveElement *elt;
    elt = (const SoXipMprActiveElement *)getConstElement(state, classStackIndex);
	
	if ( (elt != NULL) )
		return elt->mprIdField;
	else
		return NULL;

}


const int32_t
SoXipMprActiveElement::getMprIndex(SoState *state) 

{
    const SoXipMprActiveElement *elt;
    elt = (const SoXipMprActiveElement *)getConstElement(state, classStackIndex);
    
	if ( (elt != NULL) )
		return elt->mprId;
	else
		return 0;


}

//
//    Overrides this method to compare attenuation values.
//
SbBool
SoXipMprActiveElement::matches(const SoElement *elt) const
{
   
	SbBool  match = FALSE;
	if ( (mprIdField == ((const SoXipMprActiveElement *) elt)->mprIdField)
		&& (mprId == ((const SoXipMprActiveElement *) elt)->mprId) )
			match = TRUE;

	return match;
	
}

//
//     Create a copy of this instance suitable for calling matches() 
//     
SoElement *
SoXipMprActiveElement::copyMatchInfo() const
{
    SoXipMprActiveElement *result = (SoXipMprActiveElement *)getTypeId().createInstance();

	if(result)
	{
		result->mprId = mprId;

		return result;
	}
	else
		return NULL;
}

