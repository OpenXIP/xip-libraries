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
#include <xip/inventor/core/SoXipVolDataElement.h>


SO_ELEMENT_SOURCE(SoXipVolDataElement);


/*! \fn SoXipVolDataElement::~SoXipVolDataElement()
* Destructor, cleans up internal data
* \return None
*/
SoXipVolDataElement::~SoXipVolDataElement()
{
}

/*! \fn SoXipVolDataElement::initClass()
* Initializes this class. Called on dll initialization.
* \return void
*/
void SoXipVolDataElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipVolDataElement, SoReplacedElement);
}

/*! \fn SoXipVolDataElement::init(SoState *state)
* Initializes the element
* \param state - the current state pointer
* \return void
*/
void SoXipVolDataElement::init(SoState *state)
{
	mData = getDefault();
}

/*! \fn SoXipVolDataElement::set(SoState *state, SoNode *node, SoXipData *volume)
 * Sets the volume data to the element from the state, replaces any previous
 * \param state - the current state pointer
 * \param node - the current node
 * \param volume - the generic data volume pointer
 * \return void
 */
void SoXipVolDataElement::set(SoState *state, SoNode *node, SoXipData *volume)
{
	// Get an instance we can change 
	SoXipVolDataElement *elt = (SoXipVolDataElement *) getElement(state, classStackIndex, node);
	if (elt) 
	{
		elt->mData = volume;

	} // else do nothing
}

/*! \fn SoXipVolDataElement::get(SoState *state)
* Returns the current volume data from the state
* \return SoXipData * pointer 
*/
SoXipData *SoXipVolDataElement::get(SoState *state)
{
	SoXipVolDataElement * elt = (SoXipVolDataElement*) getConstElement(state, classStackIndex);

	return elt->mData;
}

/*! \fn SoXipVolDataElement::getDefault()
 * Returns a default NULL pointer
 * \return SoXipData * pointer 
 */
SoXipData *SoXipVolDataElement::getDefault()
{
	return 0; 
}
