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
*/#pragma once

#include <xip/inventor/core/xipivcore.h>

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

class XIPIVCORE_API SoXipRegistrationElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER(SoXipRegistrationElement);

public:
	// Initializes element
	virtual void init(SoState *state);

	// Sets the view matrix to the given matrix
	static void	set(SoState *state, SoNode *node, const SbMatrix &matrix);

	// Returns current matrix from the state
	static const SbMatrix &	get(SoState *state);

	// Prints element (for debugging)
	virtual void print(FILE *fp) const;

	static void initClass();

protected:
	SbMatrix mMatrix;

	// Sets the matrix in an instance
	virtual void setElt(const SbMatrix &matrix);

	virtual ~SoXipRegistrationElement();
};
