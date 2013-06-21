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
#include <xip/inventor/core/SoXipMprPlaneElement.h>
#include <xip/inventor/core/XipGeomUtils.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/errors/SoDebugError.h>

SO_ELEMENT_SOURCE(SoXipMprPlaneElement);


//
// This structure contains all information needed for a MPR
// plane. Pointers to instances of this structure are stored in the
// "mMprPlanes" SbPList.
//
struct So_MprPlane 
{
	SbMatrix    planeMatrix;
	SbVec3f     center;
	SbColor     color;
	SoSFMatrix* planeField;
	SoSFVec3f*  centerField;
	int         id;
	float		stepSize;
	float		thickness;
};


void SoXipMprPlaneElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipMprPlaneElement, SoAccumulatedElement);
}


SoXipMprPlaneElement::~SoXipMprPlaneElement()
{
}


void SoXipMprPlaneElement::init(SoState *)
{
	mMprPlanes.truncate(0);
	mStartIndex = 0;
}


void SoXipMprPlaneElement::add(SoState *state, SoNode *node, const SbMatrix &planeMatrix, const SbVec3f &center, const SbColor &color, int id, float stepSize, float thickness, SoSFMatrix *planeField, SoSFVec3f *centerField)
{
	SoXipMprPlaneElement* elt = (SoXipMprPlaneElement *) getElement(state, classStackIndex);

	if (elt) 
	{
		elt->addToElt(planeMatrix, center, color, id, stepSize, thickness, planeField, centerField);

		// Update node id list in element
		elt->addNodeId(node);
	}
}


// Override push to copy the existing mMprPlanes from the previous element.
void SoXipMprPlaneElement::push(SoState *state)
{
	const SoXipMprPlaneElement *elt = (const SoXipMprPlaneElement *) getNextInStack();

	// Use SbPList::operator = to copy the pointers to the existing
	// mMprPlanes. Since the previous element can't be destroyed before
	// this one is, there is no problem with using pointers to
	// existing plane structures. However, any new ones we add have to
	// be freed up when this instance goes away, so we save the
	// starting index to allow us to fix this in pop().
	mMprPlanes = elt->mMprPlanes;
	mStartIndex = mMprPlanes.getLength();
	nodeIds = elt->nodeIds;
}


// Override pop to free up plane structures that were created in
// the instance that was removed from the state.
void SoXipMprPlaneElement::pop(SoState *, const SoElement *prevTopElement)
{
	const SoXipMprPlaneElement *prevElt = (const SoXipMprPlaneElement *) prevTopElement;

	// Free up any plane structures that were created by prevElt
	for (int i = prevElt->mStartIndex; i < prevElt->mMprPlanes.getLength(); i++)
	{
		delete (So_MprPlane*) prevElt->mMprPlanes[i];
	}
}


// Returns the first (top) instance of the element in the state.
SoXipMprPlaneElement* SoXipMprPlaneElement::getInstance(SoState *state)
{
	return (SoXipMprPlaneElement *) getConstElement(state, classStackIndex);
}


// Returns the number of MPR mMprPlanes in the element
int SoXipMprPlaneElement::getNum() const
{
	return mMprPlanes.getLength();
}


// Returns the nth plane matrix stored in an instance.
const SbMatrix& SoXipMprPlaneElement::getMatrix(int index) const
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getMatrix",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->planeMatrix;
}


// Returns the nth plane color stored in an instance.
const SbColor& SoXipMprPlaneElement::getColor(int index) const
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getColor",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->color;
}


// Returns the nth plane id stored in an instance.
const int SoXipMprPlaneElement::getId(int index) const
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getId",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->id;
}


// Returns the nth plane step size stored in an instance.
const float SoXipMprPlaneElement::getStepSize(int index) const
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getStepSize",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->stepSize;
}


// Returns the nth plane thickness stored in an instance.
const float SoXipMprPlaneElement::getThickness(int index) const
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getThickness",
		"Index (%d) is out of range 0 - %d",
		index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->thickness;
}


void SoXipMprPlaneElement::setMatrix(int index, const SbMatrix &matrix)
{
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getMatrix",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];
	if (plane)
	{
		// set new matrix and update field if any changes
		plane->planeMatrix = matrix;
		if (plane->planeField)
		{
			if (!plane->planeField->getValue().equals(matrix, XIP_FLT_EPSILON))
			{
				plane->planeField->setValue(matrix);
			}
		}

		// compute new center of rotation, which must be located on the plane
		SbPlane pl = XipGeomUtils::planeFromMatrix(matrix);
		SbLine ln(plane->center, pl.getNormal());
		pl.intersect(ln, plane->center);
		if (plane->centerField)
		{
			if (!plane->centerField->getValue().equals(plane->center, XIP_FLT_EPSILON))
			{
				plane->centerField->setValue(plane->center);
			}
		}
	}
}


void SoXipMprPlaneElement::setCenter(int index, const SbVec3f &center)
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::setCenter",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];
	if (plane)
	{
		plane->center = center;

		// make sure that the new center of rotation is located on the plane
		SbPlane pl = XipGeomUtils::planeFromMatrix(plane->planeMatrix);
		SbLine ln(plane->center, pl.getNormal());
		pl.intersect(ln, plane->center);
		if (plane->centerField)
		{
			if (!plane->centerField->getValue().equals(plane->center, XIP_FLT_EPSILON))
			{
				plane->centerField->setValue(plane->center);
			}
		}
	}
}


const SbVec3f& SoXipMprPlaneElement::getCenter(int index) const
{

#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getCenter",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->center;
}


// Returns the nth plane matrix field stored in an instance.
SoSFMatrix * SoXipMprPlaneElement::getMatrixField(int index) const
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getMatrixField",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif /* DEBUG */

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->planeField;
}


SoSFVec3f * SoXipMprPlaneElement::getCenterField(int index) const
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getCenterField",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif /* DEBUG */

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->centerField;
}


// Adds MprPlane properties to the MprPlaneElement
void SoXipMprPlaneElement::addToElt(const SbMatrix &planeMatrix, const SbVec3f &center, const SbColor &color, int id, float stepSize, float thickness, SoSFMatrix *planeField, SoSFVec3f *centerField)
{
	So_MprPlane *newPlane = new So_MprPlane;
	if (newPlane)
	{
		newPlane->planeMatrix = planeMatrix;
		newPlane->center = center;
		newPlane->color = color;
		newPlane->planeField = planeField;
		newPlane->centerField = centerField;
		newPlane->id = id;
		newPlane->stepSize = stepSize;
		newPlane->thickness = thickness;

		mMprPlanes.append(newPlane);
	}
}
