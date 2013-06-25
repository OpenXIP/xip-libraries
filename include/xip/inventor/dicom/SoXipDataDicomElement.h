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
#ifndef SOXIPDATADICOMELEMENT_H
#define SOXIPDATADICOMELEMENT_H

#include <Inventor/elements/SoSubElement.h>
#include <xip/inventor/dicom/xipivdicom.h>

class SoXipDataDicom;

class XIPIVDICOM_API SoXipDataDicomElement : public SoElement
{
	SO_ELEMENT_HEADER( SoXipDataDicomElement );

public:
	static void initClass();

	// Initializes element
	virtual void init(SoState* state);

	// Sets the current active slice index 
	static void set(SoState* state, SoXipDataDicom* dataObject, int sliceIndex = 0);
	static SoXipDataDicom* get(SoState* state);
	static int getSliceIndex(SoState* state);

    // Returns TRUE if the viewports match
    virtual SbBool	matches(const SoElement *elt) const;

    // Create and return a copy of this element
    virtual SoElement	*copyMatchInfo() const;

protected:
	virtual ~SoXipDataDicomElement();

	// Dicom slice index
	SoXipDataDicom *mDicomObject;
	int				mSliceIndex;
};

#endif	// SOXIPDATADICOMELEMENT_H
