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
#ifndef  SOXIPCLIPPLANEELEMENT_H
#define  SOXIPCLIPPLANEELEMENT_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/SbPList.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXipClipPlaneElement
//
//  Element that stores the current set of clipping planes, specified
//  as SbPlanes.
//
//  When a plane is added, this element gets the current model matrix
//  from the state and stores it in the instance. This allows the
//  get() method to return the clip plane in object space (the plane
//  as originally defined) or world space (after being transformed by
//  the model matrix).
//
//////////////////////////////////////////////////////////////////////////////

class XIPIVCORE_API SoXipClipPlaneElement : public SoAccumulatedElement {

    SO_ELEMENT_HEADER(SoXipClipPlaneElement);

  public:
    // Initializes element
    virtual void	init(SoState *state);

    // Adds a clip plane to the current set in the state
    static void		add(SoState *state, SoNode *node,
			    const SbPlane &plane);

    // Overrides push() method to copy values from next instance in the stack
    virtual void	push(SoState *state);

    // Overrides pop() method to free up planes that were added
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

    // Returns the top (current) instance of the element in the state
    static const SoXipClipPlaneElement * getInstance(SoState *state);

    // Returns the number of planes in an instance
    int			getNum() const;

    // Returns the indexed plane an element as an SbPlane. The plane
    // can be returned in object or world space.
    const SbPlane &	get(int index, SbBool inWorldSpace = TRUE) const;

    // Prints element (for debugging)
    virtual void	print(FILE *fp) const;

  public:
    // Initializes the SoXipClipPlaneElement class
    static void		initClass();

  protected:
    SbPList		planes;		// List of plane structures
    int			startIndex;	// Index of 1st plane created
					// in this instance

    // Adds the clipping plane to an instance. Takes the new plane and
    // the current model matrix
    virtual void	addToElt(const SbPlane &plane,
				 const SbMatrix &modelMatrix);

    virtual ~SoXipClipPlaneElement();
};

#endif // SOXIPCLIPPLANEELEMENT_H
