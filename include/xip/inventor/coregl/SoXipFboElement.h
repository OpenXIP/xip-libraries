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
#ifndef SO_XIP_FBO_ELEMENT_H
#define SO_XIP_FBO_ELEMENT_H


/**
 *  Component       : XIP
 *  Name            : SoXipFboElement
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Replaced element managing fbo and buffer
 *                      activity. It also provides information
 *                      on current fbo setup if requested.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbViewportRegion.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#include <xip/inventor/coregl/FramebufferObject.h>


class XIPIVCOREGL_API SoXipFboElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER(SoXipFboElement);

public:

    static void initClass();

	virtual void init(SoState *state);
    virtual void push(SoState *state);
    virtual void pop(SoState *state, const SoElement *prevTopElement);

#if 0
	virtual SbBool      matches(const SoElement *elt) const;
    virtual SoElement*  copyMatchInfo() const;
#endif

	static unsigned int* getUnits(SoState * state, SoNode *node);
	unsigned int*		getUnitsElt();

    static void         set(SoState *state, SoNode *node, FboSetup &primaryFB);
	void                setElt(SoState *state, FboSetup &primaryFB);

	static void         setPingPong(SoState *state, SoNode *node, FboSetup &secondaryFB, unsigned int * units);
	void                setPingPongElt(SoState *state, FboSetup &secondaryFB, unsigned int * units);

	static void         bind(SoState *state, SoNode *node);
	void                bindElt(SoState *state);

    static void         flip(SoState *state, SoNode *node);
	void                flipElt(SoState * state);

	static FboSetup*    getActive(SoState *state, SoNode *node);
	FboSetup*           getActiveElt();

	static FboSetup*    getPassive(SoState *state, SoNode *node);
	FboSetup*           getPassiveElt();

  	static bool         isPingPong(SoState *state, SoNode *node);
	bool                isPingPongElt();

	static void			renderToSlice(SoState *state, SoNode *node, int z);
	void				renderToSliceElt(int z);

	static void			reattachAs3D(SoState *state, SoNode *node);
	void				reattachAs3DElt();

private:
	~SoXipFboElement();

	void                bindActiveFB();
	void                bindDefaultFB();
	void                bindPassiveTextures(SoState * state);

    FboSetup            mActiveFB;
    FboSetup            mPassiveFB;

    SbVec2s             mPrevVp;
    unsigned int        mPingPongUnits[16];
    bool                mIsPingPong;
};

#endif 
