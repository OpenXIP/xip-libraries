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
 *      Element class for GLSL shaders
 */
#include <xip/system/standard.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

#include <xip/inventor/coregl/ShaderProgramManager.h>


SO_ELEMENT_SOURCE(SoXipGLSLShaderProgramElement);

/**
 *      Initializes the element class
 */
void SoXipGLSLShaderProgramElement::initClass()
{
    SO_ELEMENT_INIT_CLASS(SoXipGLSLShaderProgramElement, SoXipShaderProgramElement);
}

/*
 *      Destructor
 */
SoXipGLSLShaderProgramElement::~SoXipGLSLShaderProgramElement()
{
}

/* 
 *      Initializes the first instance used in an action's state.
 */
void SoXipGLSLShaderProgramElement::init(SoState * state )
{
    parent::init(state);
    this->data = getDefault();
}

/**
 *      Method to update the program object id
 */
void SoXipGLSLShaderProgramElement::updateGl(void)
{
    if (glIsProgram(this->data))
        glUseProgram(this->data);
    else
        glUseProgram(0);
}

/**
 *      Update the element and calls to update GL to update the state
 */
void SoXipGLSLShaderProgramElement::setElt(int temp)
{
    if (data != temp)
    {
        data = temp;
        updateGl();
    }
}

void SoXipGLSLShaderProgramElement::push(SoState * state)
{
    SoXipGLSLShaderProgramElement * prev =
        (SoXipGLSLShaderProgramElement*)this->getNextInStack();

    /** copy data to avoid unnecessary GL calls */
    this->data = prev->data;

    /** capture previous element since we might or might not change the
        GL state in set/pop */
    prev->capture(state);
}


void SoXipGLSLShaderProgramElement::pop(SoState * state,
                                        const SoElement * prevTopElement)
{
    SoXipGLSLShaderProgramElement * prev = (SoXipGLSLShaderProgramElement*) prevTopElement;
    if (this->data != prev->data) this->updateGl();
}



int SoXipGLSLShaderProgramElement::get(SoState *state)
{
    /** Use the corresponding method on SoInt32Element to get the
        value from the top instance in the state */
    return SoInt32Element::get(classStackIndex, state);
}

void SoXipGLSLShaderProgramElement::set(SoState * const state, SoNode * const node, const int tmp )
{
    SoInt32Element::set(classStackIndex, state, node, tmp);
}

void SoXipGLSLShaderProgramElement::set(SoState * const state, const int idProgramObject)
{
    SoInt32Element::set(classStackIndex, state, idProgramObject);
}

int SoXipGLSLShaderProgramElement::set(SoState * const state,
                                       const SbString & prgTag)
{
    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    int prgHandle = manager->getProgramHandle(prgTag.getString());

    SoInt32Element::set(classStackIndex, state, prgHandle);

    return prgHandle;
}

int SoXipGLSLShaderProgramElement::set(SoState * const state,
                                       const char * prgTag)
{
    if (!prgTag) return 0;

    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    int prgHandle = manager->getProgramHandle(prgTag);

    SoInt32Element::set(classStackIndex, state, prgHandle);

    return prgHandle;
}

int SoXipGLSLShaderProgramElement::getProgramID(SoState * const state,
                                                const SbString & prgTag)
{
    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    int prgHandle = manager->getProgramHandle(prgTag.getString());

    return prgHandle;
}

int SoXipGLSLShaderProgramElement::getProgramID(SoState * const state,
                                                const char * prgTag)
{
    if (!prgTag) return 0;

    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    int prgHandle = manager->getProgramHandle(prgTag);

    return prgHandle;
}

__uint64 SoXipGLSLShaderProgramElement::getTimeStamp(SoState * const state,
                                                const SbString & prgTag)
{
    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    __uint64 time = manager->getTimeStamp(prgTag.getString());

    return time;
}

__uint64 SoXipGLSLShaderProgramElement::getTimeStamp(SoState * const state,
                                                const char * prgTag)
{
    if (!prgTag) return 0;

    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    __uint64 time = manager->getTimeStamp(prgTag);

    return time;
}


// local Variables:
//   mode: c++
//   indent-tabs-mode: nil
//   c-basic-offset: 4
//   c-indentation-style: k&r
// End:


