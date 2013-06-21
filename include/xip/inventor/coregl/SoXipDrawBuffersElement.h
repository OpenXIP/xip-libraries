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
#ifndef SO_XIP_DRAW_BUFFERS_ELEMENT_H
#define SO_XIP_DRAW_BUFFERS_ELEMENT_H

/**
 *  Component       : XIP
 *  Name            : SoXipDrawBuffersElement
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Replaced element keeping track of which
 *                      color targets we are currently rendering.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


#include <Inventor/elements/SoReplacedElement.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include "FramebufferObject.h"


class XIPIVCOREGL_API SoXipDrawBuffersElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER(SoXipDrawBuffersElement);

public:

    static void initClass();

	virtual void init(SoState *state);
    virtual void push(SoState *state);
    virtual void pop(SoState *state, const SoElement *prevTopElement);

#if 0
	virtual SbBool      matches(const SoElement *elt) const;
    virtual SoElement*  copyMatchInfo() const;
#endif

	static void     set(SoState *state, SoNode *node, int numBuffers);
	void            setElt(int numBuffers);
	static void     setBuffer(SoState *state, SoNode *node, int buffer);
	void            setBufferElt(int buffer);

	static int      getNum(SoState *state, SoNode *node);
	int             getNumElt();
	static void     getSubBuffers(SoState *state, SoNode *node, int num, GLenum * iBuffers);
	void            getSubBuffersElt(int num, GLenum * iBuffers);

private:
	~SoXipDrawBuffersElement();

	void    drawBuffersGL();

    int     mMaxBuffers;
    int     mNumBuffers;
    GLenum  mSubBuffers[16];
};

#endif 




