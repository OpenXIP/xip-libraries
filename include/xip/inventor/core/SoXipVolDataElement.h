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
*/#ifndef SOXIPVOLDATAELEMENT_H
#define SOXIPVOLDATAELEMENT_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/elements/SoReplacedElement.h>

class SoXipData;

/*! \class SoXipVolDataElement
 *  \brief A replace element for storing a generic volume data 
 *
 * A replace element type for storing a general volume.  This
 * element is typically used by volume rendering nodes.  This
 * element does not specify the type of volume, the volume can
 * be binary, gray, color etc. as long as it is derived from
 * the SoXipData type.  It is up to the user to query the specific
 * data type.
 */
class XIPIVCORE_API SoXipVolDataElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER(SoXipVolDataElement);

public:
	/// Initializes the SoXipVolDataElement class
	static void initClass();

	/// Initializes element
	virtual void init(SoState *state);

	/// Sets the current state with the given volume data
	static void set(SoState *state, SoNode *node, SoXipData *volume);

	/// Returns the current generic volume data pointer from the state
	static SoXipData *get(SoState *state);

	/// Returns the default pointer
	static SoXipData *getDefault();

protected:
    virtual ~SoXipVolDataElement();

	SoXipData *mData;

};

#endif // SOXIPVOLDATAELEMENT_H
