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
#include <xip/inventor/core/SoXipValueConvertElement.h>
#include <xip/inventor/core/SbXipValueConvertBase.h>
#include <Inventor/errors/SoErrors.h>

SO_ELEMENT_SOURCE( SoXipValueConvertElement );



/*! \class SbXipValueConvertBase 
 *  \brief A base pure virtual interface for value converter classes.
 *
 *  This class serves as the base interface for converting a given
 *  input value to an output value.  Derive classes are to implement 
 *  the given interfaces.
 */
class XIPIVCORE_API SbXipValueConvertContainer
{
public:
	/// Constructor
    SbXipValueConvertContainer();
    virtual ~SbXipValueConvertContainer();

    SbXipValueConvertBase* convObj;

};

SbXipValueConvertContainer::SbXipValueConvertContainer()
: convObj(0)
{
}
SbXipValueConvertContainer::~SbXipValueConvertContainer()
{
    delete convObj;
    convObj = NULL;
}


SoXipValueConvertElement::~SoXipValueConvertElement()
{
}

void SoXipValueConvertElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipValueConvertElement, SoAccumulatedElement );
}

void SoXipValueConvertElement::init( SoState* )
{
	mConvObjs.truncate(0);
    mStartIndex = 0;
}


/*! \fn SoXipValueConvertElement::add(SoState *state, SoNode *node, const SbXipValueConvertBase& obj)
 * Adds a converter obejct to the elements.
 * \param state - the current state pointer
 * \param node - the current node
 * \param obj - the value converter object
 */
void
SoXipValueConvertElement::add(SoState *state, SoNode *node, const SbXipValueConvertBase* obj)
{
    SoXipValueConvertElement	*elt;

    // Get an instance we can change (pushing if necessary)
    elt = (SoXipValueConvertElement *) getElement(state, classStackIndex);

    if (elt != NULL) 
    {
        elt->addToElt(obj);

	    // Update node id list in element
	    elt->addNodeId(node);
    }
}



/*! \fn SoXipValueConvertElement::addToElt(const SbXipValueConvertBase& obj)
* Adds converter object to element
* \param obj - the converter object
* \return void
*/
void
SoXipValueConvertElement::addToElt(const SbXipValueConvertBase* obj)
{
    if (!obj)
        return;

    SbXipValueConvertContainer *convContainer = new SbXipValueConvertContainer;

    if (!convContainer)
    {
        SoMemoryError::post("SoXipValueConvertElement allocation failed");
        return;
    }	

    convContainer->convObj = obj->clone();

    mConvObjs.append(convContainer);
}



/*! \fn SoXipValueConvertElement::push(SoState *state)
* Override push to copy the existing converter object from the previous
* \param state - the current state pointer
* \return void
*/
void
SoXipValueConvertElement::push(SoState *state)
{
    const SoXipValueConvertElement *elt =
	(const SoXipValueConvertElement *) getNextInStack();

    // Use SbPList::operator = to copy the pointers to the existing
    // planes. Since the previous element can't be destroyed before
    // this one is, there is no problem with using pointers to
    // existing plane structures. However, any new ones we add have to
    // be freed up when this instance goes away, so we save the
    // starting index to allow us to fix this in pop().
    mConvObjs = elt->mConvObjs;
    mStartIndex = mConvObjs.getLength();
    nodeIds = elt->nodeIds;
}

/*! \fn SoXipValueConvertElement::pop(SoState *state, const SoElement *prevTopElement)
 * Override pop to free up converter object structures that were created in the instance that was removed from the state.
 * \param state - the current state pointer
 * \param prevTopElement - the previous top element
 * \return void
 */
void
SoXipValueConvertElement::pop(SoState *state, const SoElement *prevTopElement)
{
    const SoXipValueConvertElement *prevElt =
	(const SoXipValueConvertElement *) prevTopElement;

    // Free up any plane structures that were created by prevElt
    for (int i = prevElt->mStartIndex; i < prevElt->mConvObjs.getLength(); i++)
    {
	    delete (SbXipValueConvertContainer*) prevElt->mConvObjs[i];
        prevElt->mConvObjs[i] = 0;
    }
}



/*! \fn SoXipValueConvertElement::getInstance(SoState *state)
* Returns the first (top) instance of the element in the state.
* \param state - the current state pointer
* \return pointer to element instance
*/
const SoXipValueConvertElement *
SoXipValueConvertElement::getInstance(SoState *state)
{
    return (const SoXipValueConvertElement *)
	getConstElement(state, classStackIndex);
}


/*! \fn SoXipValueConvertElement::getNum() const
* Returns the number of converter objects in the element
* \return number of converter objects in the accumulated state
*/
int
SoXipValueConvertElement::getNum() const
{
    return mConvObjs.getLength();
}


/*! \fn SoXipValueConvertElement::get(int index) const
* \brief Returns the indexed converter object of the given index in the state
* \param index - the index to get
* \return pointer to object 
*/
const SbXipValueConvertBase *
SoXipValueConvertElement::get(int index) const
{
#ifdef _DEBUG
    if (index < 0 || index >= mConvObjs.getLength())
	SoDebugError::post("SoXipValueConvertElement::get",
			   "Index (%d) is out of range 0 - %d",
			   index, mConvObjs.getLength() - 1);
#endif /* DEBUG */

    SbXipValueConvertContainer *obj = (SbXipValueConvertContainer *) mConvObjs[index];

	return obj->convObj;

}


