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
#ifndef SO_XIP_FRAMEBUFFER_ELEMENT_H
#define SO_XIP_FRAMEBUFFER_ELEMENT_H

//#include <xip/system/GL/gl.h>
//#include <xip/system/GL/glext.h>

#include <Inventor/elements/SoSubElement.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

class XIPIVCOREGL_API SoXipFramebufferElement : public SoElement {
	SO_ELEMENT_HEADER(SoXipFramebufferElement);

public:
	static void initClass();

	virtual void init(SoState *state);

    virtual void push(SoState *state);
    virtual void pop(SoState *state, const SoElement *prevTopElement);

	virtual SbBool matches(const SoElement *elt) const;
    virtual SoElement *copyMatchInfo() const;

	static void set(SoState *state, GLuint primaryFB, GLuint secondaryFB, GLuint primaryTex, GLuint secondaryTex);
	void setElt(SoState *state, GLuint primaryFB, GLuint secondaryFB, GLuint primaryTex, GLuint secondaryTex);

	static void flip(SoState *state);
	void flipElt(SoState *state);

	static int getCurrent(SoState *state);
	int getCurrentElt() const;

private:
	~SoXipFramebufferElement();

	void bindFB();
	void bindTex(SoState *state);

	GLuint mFrameBuffer[2];
	GLuint mColorBufferTex[2];
	GLuint mCurrentFramebuffer;
	GLuint mTextureUnit;
	bool hasDualBuffers;
};

#endif 




