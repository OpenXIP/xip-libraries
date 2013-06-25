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

#include <xip/inventor/core/SoXipClipPlaneElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/errors/SoDebugError.h>

SO_ELEMENT_SOURCE(SoXipClipPlaneElement);

//
// This structure contains all information needed for a clipping
// plane. Pointers to instances of this structure are stored in the
// "planes" SbPList.
//

struct So_ClipPlane {
    SbPlane	objPlane;	// World-space clipping plane
    SbPlane	worldPlane;	// World-space clipping plane
    SbMatrix	objToWorld;	// Converts object space to world space
    SbBool	worldPlaneValid;// TRUE if worldPlane was computed
};

void SoXipClipPlaneElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipClipPlaneElement, SoAccumulatedElement);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor.
//
// Use: private

SoXipClipPlaneElement::~SoXipClipPlaneElement()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Initializes element.
//
// Use: public

void
SoXipClipPlaneElement::init(SoState *)
//
////////////////////////////////////////////////////////////////////////
{
    planes.truncate(0);
    startIndex = 0;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Adds a clip plane to the current set in the state.
//
// Use: public, static

void
SoXipClipPlaneElement::add(SoState *state, SoNode *node, const SbPlane &plane)
//
////////////////////////////////////////////////////////////////////////
{
    SoXipClipPlaneElement	*elt;

    // Get an instance we can change (pushing if necessary)
    elt = (SoXipClipPlaneElement *) getElement(state, classStackIndex);

    if (elt != NULL) {
	elt->addToElt(plane, SoModelMatrixElement::get(state));

	// Update node id list in element
	elt->addNodeId(node);
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Override push to copy the existing planes from the previous
//    element.
//
// Use: public

void
SoXipClipPlaneElement::push(SoState *)
//
////////////////////////////////////////////////////////////////////////
{
    const SoXipClipPlaneElement *elt =
	(const SoXipClipPlaneElement *) getNextInStack();

    // Use SbPList::operator = to copy the pointers to the existing
    // planes. Since the previous element can't be destroyed before
    // this one is, there is no problem with using pointers to
    // existing plane structures. However, any new ones we add have to
    // be freed up when this instance goes away, so we save the
    // starting index to allow us to fix this in pop().
    planes = elt->planes;
    startIndex = planes.getLength();
    nodeIds = elt->nodeIds;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Override pop to free up plane structures that were created in
//    the instance that was removed from the state.
//
// Use: public

void
SoXipClipPlaneElement::pop(SoState *, const SoElement *prevTopElement)
//
////////////////////////////////////////////////////////////////////////
{
    const SoXipClipPlaneElement *prevElt =
	(const SoXipClipPlaneElement *) prevTopElement;

    // Free up any plane structures that were created by prevElt
    for (int i = prevElt->startIndex; i < prevElt->planes.getLength(); i++)
	delete (So_ClipPlane *) prevElt->planes[i];
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns the first (top) instance of the element in the state.
//
// Use: public, static

const SoXipClipPlaneElement *
SoXipClipPlaneElement::getInstance(SoState *state)
//
////////////////////////////////////////////////////////////////////////
{
    return (const SoXipClipPlaneElement *)
	getConstElement(state, classStackIndex);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns the number of planes in the element
//
// Use: public

int
SoXipClipPlaneElement::getNum() const
//
////////////////////////////////////////////////////////////////////////
{
    return planes.getLength();
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns the nth plane stored in an instance in object or world
//    space.
//
// Use: public

const SbPlane &
SoXipClipPlaneElement::get(int index, SbBool inWorldSpace) const
//
////////////////////////////////////////////////////////////////////////
{
#ifdef DEBUG
    if (index < 0 || index >= planes.getLength())
	SoDebugError::post("SoXipClipPlaneElement::get",
			   "Index (%d) is out of range 0 - %d",
			   index, planes.getLength() - 1);
#endif /* DEBUG */

    So_ClipPlane *plane = (So_ClipPlane *) planes[index];

    if (! inWorldSpace)
	return plane->objPlane;

    // Transform plane into world space if necessary
    if (! plane->worldPlaneValid) {
	plane->worldPlane = plane->objPlane;
	plane->worldPlane.transform(plane->objToWorld);
    }
    return plane->worldPlane;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Prints element for debugging.
//
// Use: public
//
////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
void
SoXipClipPlaneElement::print(FILE *fp) const
{
    SoAccumulatedElement::print(fp);
}
#else  /* DEBUG */
void
SoXipClipPlaneElement::print(FILE *) const
{
}
#endif /* DEBUG */

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Adds clipping plane to element.
//
// Use: protected, virtual

void
SoXipClipPlaneElement::addToElt(const SbPlane &plane,
			     const SbMatrix &modelMatrix)
//
////////////////////////////////////////////////////////////////////////
{
    So_ClipPlane *newPlane = new So_ClipPlane;

    newPlane->objPlane		= plane;
    newPlane->objToWorld	= modelMatrix;
    newPlane->worldPlaneValid	= FALSE;

    planes.append(newPlane);
}
