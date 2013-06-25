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
/**
 *	Element class for shaders
 * This class is supposed to be the base class for shader elements, for example for a possible 
 * support of CG shaders or assembly shaders
 */

#ifndef SO_XIP_SHADER_PROGRAM_ELEMENT_H
#define  SO_XIP_SHADER_PROGRAM_ELEMENT_H

#include <Inventor/elements/SoInt32Element.h>

#include <xip/inventor/coregl/xipivcoregl.h>
/**
 *	SoXipShaderProgramElement. An Open Inventor element to handle
 *	shader program ids.
 */
class XIPIVCOREGL_API SoXipShaderProgramElement : public SoInt32Element {

	typedef SoInt32Element parent;
	SO_ELEMENT_HEADER(SoXipShaderProgramElement);

public:
	/**
	 *	Initializes the element class
	 */
	static void    initClass();
	
	/**
	 *	Initializes the element
	 */
	virtual void	init(SoState *state);
	static  void	set(SoState * const state, SoNode * const node, const int tmp );
	static void		set(SoState * const state, const int tmp);
	static int		get(SoState *state);
	static int		getDefault()         { return 0; }

protected:
	/**
	 *	Destructor
	 */	
	virtual ~SoXipShaderProgramElement();
};
#endif
