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
*	@file    SoXipFontTypeElement.h
*	@brief   Declaration of the SoXipFontTypeElement element class
*	@author  Julien Gein
**/

#ifndef SOXIPFONTTYPEELEMENT_H
#define SOXIPFONTTYPEELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>

class SoXipFontTypeElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER( SoXipFontTypeElement );

public:
	enum FontType
	{
		BITMAP,
		PIXMAP,
		TEXTURE
	};
    
	static void initClass();

	virtual void init( SoState* state );

	static void set( SoState* state, SoNode* node, FontType type );

	virtual SoElement* copyMatchInfo() const;

	virtual SbBool matches( const SoElement* elt ) const;
    
    static FontType get( SoState* state );

protected:
	virtual ~SoXipFontTypeElement();

    FontType    mFontType;

};

#endif // SOXIPFONTTYPEELEMENT_H

