/*
*  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
*  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
*  (XIP) was created with NCI funding and is part of the caBIG(tm) 
*  initiative. The software subject to this notice and license 
*  includes both human readable source code form and machine 
*  readable, binary, object code form (the "caBIG(tm) Software").
*  
*  This caBIG(tm) Software License (the "License") is between 
*  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
*  person or an entity, and all other entities that control, are 
*  controlled by, or are under common control with the entity.  
*  "Control" for purposes of this definition means (i) the direct or 
*  indirect power to cause the direction or management of such 
*  entity, whether by contract or otherwise, or (ii) ownership of 
*  fifty percent (50%) or more of the outstanding shares, or (iii) 
*  beneficial ownership of such entity.
*  
*  LICENSE.  Provided that You agree to the conditions described 
*  below, caBIG(tm) Participant grants You a non-exclusive, 
*  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
*  transferable and royalty-free right and license in its rights in 
*  the caBIG(tm) Software, including any copyright or patent rights 
*  therein that may be infringed by the making, using, selling, 
*  offering for sale, or importing of caBIG(tm) Software, to (i) 
*  use, install, access, operate, execute, reproduce, copy, modify, 
*  translate, market, publicly display, publicly perform, and 
*  prepare derivative works of the caBIG(tm) Software; (ii) make, 
*  have made, use, practice, sell, and offer for sale, and/or 
*  otherwise dispose of caBIG(tm) Software (or portions thereof); 
*  (iii) distribute and have distributed to and by third parties the 
*  caBIG(tm) Software and any modifications and derivative works 
*  thereof; and (iv) sublicense the foregoing rights set out in (i), 
*  (ii) and (iii) to third parties, including the right to license 
*  such rights to further third parties.  For sake of clarity, and 
*  not by way of limitation, caBIG(tm) Participant shall have no 
*  right of accounting or right of payment from You or Your 
*  sublicensees for the rights granted under this License.  This 
*  License is granted at no charge to You.  Your downloading, 
*  copying, modifying, displaying, distributing or use of caBIG(tm) 
*  Software constitutes acceptance of all of the terms and 
*  conditions of this Agreement.  If you do not agree to such terms 
*  and conditions, you have no right to download, copy, modify, 
*  display, distribute or use the caBIG(tm) Software.
*  
*  1.	Your redistributions of the source code for the caBIG(tm) 
*      Software must retain the above copyright notice, this list 
*      of conditions and the disclaimer and limitation of 
*      liability of Article 6 below.  Your redistributions in 
*      object code form must reproduce the above copyright notice, 
*      this list of conditions and the disclaimer of Article 6 in 
*      the documentation and/or other materials provided with the 
*      distribution, if any.
*  2.	Your end-user documentation included with the 
*      redistribution, if any, must include the following 
*      acknowledgment: "This product includes software developed 
*      by Siemens Corporate Research Inc."  If You do not include 
*      such end-user documentation, You shall include this 
*      acknowledgment in the caBIG(tm) Software itself, wherever 
*      such third-party acknowledgments normally appear.
*  3.	You may not use the names "Siemens Corporate Research, 
*      Inc.", "The National Cancer Institute", "NCI", "Cancer 
*      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
*      products derived from this caBIG(tm) Software.  This 
*      License does not authorize You to use any trademarks, 
*  	service marks, trade names, logos or product names of 
*      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
*      required to comply with the terms of this License.
*  4.	For sake of clarity, and not by way of limitation, You may 
*      incorporate this caBIG(tm) Software into Your proprietary 
*      programs and into any third party proprietary programs.  
*      However, if You incorporate the caBIG(tm) Software into 
*      third party proprietary programs, You agree that You are 
*      solely responsible for obtaining any permission from such 
*      third parties required to incorporate the caBIG(tm) 
*      Software into such third party proprietary programs and for 
*      informing Your sublicensees, including without limitation 
*      Your end-users, of their obligation to secure any required 
*      permissions from such third parties before incorporating 
*      the caBIG(tm) Software into such third party proprietary 
*      software programs.  In the event that You fail to obtain 
*      such permissions, You agree to indemnify caBIG(tm) 
*      Participant for any claims against caBIG(tm) Participant by 
*      such third parties, except to the extent prohibited by law, 
*      resulting from Your failure to obtain such permissions.
*  5.	For sake of clarity, and not by way of limitation, You may 
*      add Your own copyright statement to Your modifications and 
*      to the derivative works, and You may provide additional or 
*      different license terms and conditions in Your sublicenses 
*      of modifications of the caBIG(tm) Software, or any 
*      derivative works of the caBIG(tm) Software as a whole, 
*      provided Your use, reproduction, and distribution of the 
*      Work otherwise complies with the conditions stated in this 
*      License.
*  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
*      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
*      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
*      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
*      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
*      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
*      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
*      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
*      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
*      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
*      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
*      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
*      THE POSSIBILITY OF SUCH DAMAGE.
*  
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


void SoXipMprPlaneElement::add(SoState *state, SoNode *node, const SbMatrix &planeMatrix, const SbVec3f &center, const SbColor &color, int id, float stepSize, SoSFMatrix *planeField, SoSFVec3f *centerField)
{
	SoXipMprPlaneElement* elt = (SoXipMprPlaneElement *) getElement(state, classStackIndex);

	if (elt) 
	{
		elt->addToElt(planeMatrix, center, color, id, stepSize, planeField, centerField);

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
		SoDebugError::post("SoXipMprPlaneElement::getMatrix",
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
		SoDebugError::post("SoXipMprPlaneElement::getMatrix",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->id;
}


// Returns the nth plane id stored in an instance.
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


void SoXipMprPlaneElement::setMatrix(int index, const SbMatrix &matrix)
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getMatrix",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

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
		SoDebugError::post("SoXipMprPlaneElement::getMatrix",
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
		SoDebugError::post("SoXipMprPlaneElement::getMatrix",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->center;
}


// Returns the nth plane filed stored in an instance.
SoSFMatrix * SoXipMprPlaneElement::getMatrixField(int index) const
{
#ifdef _DEBUG
	if (index < 0 || index >= mMprPlanes.getLength())
		SoDebugError::post("SoXipMprPlaneElement::getField",
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
		SoDebugError::post("SoXipMprPlaneElement::getField",
			   "Index (%d) is out of range 0 - %d",
			   index, mMprPlanes.getLength() - 1);
#endif /* DEBUG */

	So_MprPlane *plane = (So_MprPlane *) mMprPlanes[index];

	return plane->centerField;
}


// Adds clipping plane to element.
void SoXipMprPlaneElement::addToElt(const SbMatrix &planeMatrix, const SbVec3f &center, const SbColor &color, int id, float stepSize, SoSFMatrix *planeField, SoSFVec3f *centerField)
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

		mMprPlanes.append(newPlane);
	}
}
