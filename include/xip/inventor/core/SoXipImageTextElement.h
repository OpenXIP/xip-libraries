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
#ifndef  SOXIPIMAGETEXTELEMENT_H
#define  SOXIPIMAGETEXTELEMENT_H

#include <vector>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <xip/inventor/core/xipivcore.h>

class XIPIVCORE_API SoXipImageTextElement : public SoAccumulatedElement 
{
	SO_ELEMENT_HEADER( SoXipImageTextElement );	

public:
	enum TextElementPosition
	{
		TP_UPPER_LEFT,
		TP_UPPER_CENTER,
		TP_UPPER_RIGHT,
		TP_CENTER_LEFT,
		TP_CENTER_RIGHT,
		TP_LOWER_LEFT,
		TP_LOWER_CENTER,
		TP_LOWER_RIGHT
	};

	struct CustomImageText
	{
		TextElementPosition		position;
		SbString				text;
	};

	typedef std::vector< CustomImageText > CustomImageTextVector;

	static void initClass();

	static void	add( SoState* state, TextElementPosition position, const SbString& text );
	static SoXipImageTextElement* getInstance( SoState* state );

	virtual void init( SoState* state );
	virtual void push( SoState* state );

	int getNum() const;
	TextElementPosition getPosition( int index ) const;
	const SbString& getText( int index ) const;

protected:
	virtual ~SoXipImageTextElement();

	CustomImageTextVector		mTextInfo;

};

#endif // SOXIPIMAGETEXTELEMENT_H
