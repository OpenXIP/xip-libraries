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
#ifndef  SOXIPIMAGETEXTCOLORELEMENT_H
#define  SOXIPIMAGETEXTCOLORELEMENT_H

#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/fields/SoMFColor.h>
#include <xip/inventor/core/SoXipImageTextElement.h>
#include <xip/inventor/overlay/xipivoverlay.h>

class XIPIVOVERLAY_API SoXipImageTextColorElement : public SoAccumulatedElement 
{
	SO_ELEMENT_HEADER( SoXipImageTextColorElement );	

public:
	static void initClass();

	static void	add( SoState* state, SoXipImageTextElement::TextElementPosition position, const SbColor& text );
	static SoXipImageTextColorElement* getInstance( SoState* state );

	virtual void init( SoState* state );
	virtual void push( SoState* state );

	SbColor get( SoXipImageTextElement::TextElementPosition ) const;

protected:
	virtual ~SoXipImageTextColorElement();

	SoMFColor		mColorInfo;

};

#endif // SOXIPIMAGETEXTCOLORELEMENT_H
