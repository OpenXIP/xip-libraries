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
#ifndef _SO_XIP_MULTI_TEXTURE_ELEMENT_H_
#define _SO_XIP_MULTI_TEXTURE_ELEMENT_H_

#include <Inventor/elements/SoSubElement.h>
#include <xip/inventor/core/xipivcore.h>

//
//! SoXipMultiTextureElement.
//! 
//! element that manages the multitexturing
//! -> contains a static list to know which texture units are used
//! -> contains the last active texture unit
//
class XIPIVCORE_API SoXipMultiTextureElement : public SoElement
{
	SO_ELEMENT_HEADER(SoXipMultiTextureElement);

public:
	static void initClass();

	virtual SbBool matches(const SoElement *element) const;
	virtual SoElement* copyMatchInfo(void) const;

	void init(SoState *state);
	void push(SoState *state);
	void pop(SoState *state, const SoElement *prevTopElement);

	static void         setUnit(SoState *state, unsigned int unit);
	static void         bindTexture(SoState *state, unsigned int target, unsigned int id);
	static unsigned int getFreeUnit(SoState *state);
    static unsigned int getFreeUnits(SoState *state, unsigned int num, unsigned int *units);
	static unsigned int getCurrentUnit(SoState *state);
    static void         bindTextureCurrUnit(SoState *state);

protected:
	void                setUnitElt(unsigned int unit);
	void                bindTextureElt(unsigned int target, unsigned int id);
	unsigned int        getFreeUnitElt() const;
    unsigned int        getFreeUnitsElt(unsigned int num, unsigned int *units) const;
	unsigned int        getCurrentUnitElt() const;

private:
	virtual ~SoXipMultiTextureElement();

	class textureInfo {
	public:
		textureInfo(unsigned int _target, unsigned int _id) : target(_target), id(_id) { }
		textureInfo() : target(0), id(0) { }
		unsigned int target;
		unsigned int id;
	};

	void setUnitGL(unsigned int unit);
	void bindTextureGL(unsigned int unit);
	void unbindTextureGL(unsigned int unit);

	static int      mMaxUnits;
	textureInfo     mTextures[32];
	unsigned int    mCurrentUnit;
	unsigned int    mUnitsChanged;
};

#endif

