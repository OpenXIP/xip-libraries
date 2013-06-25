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
*/#ifndef SOXIPVALUECONVERTELEMENT_H
#define SOXIPVALUECONVERTELEMENT_H

#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/SbPList.h>

#include "xipivcore.h"

class SbXipValueConvertBase; 
struct So_ValueConvert;

/*! \class SoXipValueConvertElement 
 *  \brief An value converter container element
 *
 *  An element that stores the current set converter objects that can be used
 *  by subsequent nodes to convert pixel values and scales to real world units (for example).
 *
 */
class XIPIVCORE_API SoXipValueConvertElement : public SoAccumulatedElement	//I 
{
	SO_ELEMENT_HEADER( SoXipValueConvertElement );

public:
	static void initClass();

	// Initializes element
	virtual void init(SoState* state);

    // Adds a clip plane to the current set in the state
    static void		add(SoState *state, SoNode *node, const SbXipValueConvertBase* obj);

    // Overrides push() method to copy values from next instance in the stack
    virtual void	push(SoState *state);

    // Overrides pop() method to free up element that were added
    virtual void	pop(SoState *state, const SoElement *prevTopElement);

    // Returns the top (current) instance of the element in the state
    static const SoXipValueConvertElement * getInstance(SoState *state);

    // Returns the number of converter objects in an instance
    int			getNum() const;


    // Returns the indexed object an element as an SoXipValueConvertBase*. 
    const SbXipValueConvertBase*	get(int index) const;



protected:
    SbPList mConvObjs;
    int     mStartIndex;

    /// Adds to an instance
    virtual void addToElt( const SbXipValueConvertBase* obj);

	virtual ~SoXipValueConvertElement();
};

#endif // SOXIPVALUECONVERTELEMENT_H
