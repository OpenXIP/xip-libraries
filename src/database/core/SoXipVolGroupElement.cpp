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
#include <xip/inventor/core/SoXipVolGroupElement.h>
#include <Inventor/errors/SoDebugError.h>

SO_ELEMENT_SOURCE(SoXipVolGroupElement);


/*! \struct So_VolGroup
 * \brief This structure contains a simple node pointer
 *
 * Pointers to instances of this structure are stored in the
 * "mVolGroups" SbPList.
 */
struct So_VolGroup 
{
	SoNode *node;
};


/*! \fn SoXipVolGroupElement::~SoXipVolGroupElement()
* Destructor, cleans up internal data
* \return None
*/
SoXipVolGroupElement::~SoXipVolGroupElement()
{
}

/*! \fn SoXipVolGroupElement::initClass()
* Initializes this class. Called on dll initialization.
* \return void
*/
void SoXipVolGroupElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipVolGroupElement, SoAccumulatedElement);
}



/*! \fn SoXipVolGroupElement::init(SoState *state)
* Initializes the element
* \param state - the current state pointer, unused
* \return void
*/
void SoXipVolGroupElement::init(SoState *state)
{
	mVolGroups.truncate(0);
	mStartIndex = 0;
}


/*! \fn SoXipVolGroupElement::add(SoState *state, SoNode *node, So_IvtRenderParam *renderParam)
 * Adds the a node to the current state
 * \param state - the current state pointer
 * \param node - the current node
 * \return void
 */
void SoXipVolGroupElement::add(SoState *state, SoNode *node)
{
	SoXipVolGroupElement* elt = (SoXipVolGroupElement *) getElement(state, classStackIndex);

	if (elt) 
	{
		elt->addToElt(node);

		// Update node id list in element
		elt->addNodeId(node);
	}
}


/*! \fn SoXipVolGroupElement::push(SoState *state)
 * Override push to copy the existing rendering parameter from the previous
 * \param state - the current state pointer
 * \return void
 */
void SoXipVolGroupElement::push(SoState *state)
{
	const SoXipVolGroupElement *elt = (const SoXipVolGroupElement *) getNextInStack();

	// Use SbPList::operator = to copy the pointers to the existing
	// planes. Since the previous element can't be destroyed before
	// this one is, there is no problem with using pointers to
	// existing plane structures. However, any new ones we add have to
	// be freed up when this instance goes away, so we save the
	// starting index to allow us to fix this in pop().
	mVolGroups = elt->mVolGroups;
	mStartIndex = mVolGroups.getLength();
	nodeIds = elt->nodeIds;
}


/*! \fn SoXipVolGroupElement::pop(SoState *state, const SoElement *prevTopElement)
 * Override pop to free up render parameter that were created in the instance that was removed from the state.
 * \param state - the current state pointer
 * \param prevTopElement - the previous top element
 * \return void
 */
void SoXipVolGroupElement::pop(SoState *, const SoElement *prevTopElement)
{
	const SoXipVolGroupElement *prevElt = (const SoXipVolGroupElement *) prevTopElement;

	// Free up any plane structures that were created by prevElt
	for (int i = prevElt->mStartIndex; i < prevElt->mVolGroups.getLength(); i++)
	{
		delete (So_VolGroup*) prevElt->mVolGroups[i];
	}
}


/*! \fn SoXipVolGroupElement::getInstance(SoState *state)
 * Returns the first (top) instance of the element in the state.
 * \param state - the current state pointer
 * \return pointer to element instance
 */
SoXipVolGroupElement* SoXipVolGroupElement::getInstance(SoState *state)
{
	return (SoXipVolGroupElement *) getConstElement(state, classStackIndex);
}



/*! \fn SoXipVolGroupElement::getNum() const
 * Returns the number of nodes in the element
 * \return number of nodes in the accumulated state
 */
int SoXipVolGroupElement::getNum() const
{
	return mVolGroups.getLength();
}


// Returns the nth plane matrix stored in an instance.

/*! \fn SoIvtRenderParamElement::getSceneObject(int index) const
 * Returns the generic parameter with the given index
 * \param index - the index to get
 * \return pointer to generic parameter structure
 */
const SoNode* SoXipVolGroupElement::getNode(int index) const
{
    if (index < 0 || index >= mVolGroups.getLength())
    {
        SoError::post("SoXipVolGroupElement::get",
            "Index (%d) is out of range 0 - %d",
            index, mVolGroups.getLength() - 1);
        return (NULL);
    }

	So_VolGroup *volGroup = (So_VolGroup *) mVolGroups[index];

	return volGroup->node;
}


/*! \fn SoXipVolGroupElement::addToElt(ivtSceneObj *sceneObj)
 * Adds a node to the element
 * \param node - the node pointer
 * \return void
 */
void SoXipVolGroupElement::addToElt(SoNode *node)
{
	So_VolGroup *newPlane = new So_VolGroup;

	newPlane->node = node;

	mVolGroups.append(newPlane);
}
