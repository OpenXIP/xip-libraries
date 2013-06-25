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

#ifndef  SOXIPTRANSPARENTGEOMETRYGROUPELEMENT_H
#define  SOXIPTRANSPARENTGEOMETRYGROUPELEMENT_H

#include <Inventor/SbPList.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <xip/inventor/core/xipivcore.h>



/*! \class SoXipTransparentGeometryGroupElement
*  \brief An accumulate element for storing a generic volume group
*
* An accumulate element type for storing properties for a volume.  This is used
* to group all nodes and property relevant to a particular volume under
* one group such that a processing node can apply the corresponding
* properties to the corresponding volume, e.g. in a fusion scenario
*/
class XIPIVCORE_API SoXipTransparentGeometryGroupElement : public SoAccumulatedElement 
{
	SO_ELEMENT_HEADER(SoXipTransparentGeometryGroupElement);

public:
    /// Initializes the SoXipTransparentGeometryGroupElement class
	static void initClass();

    /// Initializes element
    virtual void init(SoState *state);

    /// Returns the top group object element from the state
    static SoXipTransparentGeometryGroupElement* getInstance(SoState *state);

    /// Adds an element to the accumulated scene
    static void	add(SoState *state, SoNode *node);

    /// Overrides push() method to copy values from next instance in the stack
    virtual void push(SoState *state);

    /// Overrides pop() method to free up previous elements that were added
    virtual void pop(SoState *state, const SoElement *prevTopElement);

    /// Returns the number of parameters in an instance
    virtual int  getNum() const;

    /// returns the indexed node within the group
    virtual const SoNode *getNode(int index) const;

protected:
    /// Destructor, cleans up element data
	virtual ~SoXipTransparentGeometryGroupElement();

    /// Adds to an instance. Takes the new node
	virtual void addToElt(SoNode *node);

	SbPList mVolGroups;
	int	mStartIndex;
};

#endif // SOXIPTRANSPARENTGEOMETRYGROUPELEMENT_H
