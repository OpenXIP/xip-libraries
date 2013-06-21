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

#ifndef FRAMEBUFFER_OBJECT_H
#define FRAMEBUFFER_OBJECT_H


/**
 *  Component       : XIP
 *  Name            : SoXipFBO
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Standalone (no GL, no Inventor) struct used
 *                      for framebuffer objact information. Used in
 *                      interface between elements and nodes.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


struct FboSetup
{
    unsigned int    fboHandle;
    unsigned int    width;
    unsigned int    height;
    unsigned int    depth;

    unsigned int    numColorAttachments;
    unsigned int    numDepthAttachments;
    unsigned int    numStencilAttachments;

    unsigned int    colorHandles[16];
    unsigned int    depthHandle;
    unsigned int    stencilHandle;

    int             colorStorage;
    int             depthStorage;
    int             stencilStorage;

    int             internalColorFormat;
    int             internalDepthFormat;
    int             internalStencilFormat;

    int             colorFormat;
    int             colorWrap;
    int             colorFilter;

    int             depthFormat;
    int             depthWrap;
    int             depthFilter;

    bool            isComplete;
    bool            isDirty;
    bool            isOpen;

    bool            hasModColors;
    bool            hasModDepth;
    bool            hasModStencil;

    FboSetup() {
        this->clear();
    }
    
    FboSetup(const FboSetup &other) {
        (*this) = other;
    }

    void clear() {
        fboHandle               = 0;
        width                   = 0;
        height                  = 0;
		depth                   = 0;

        numColorAttachments     = 0;
        numDepthAttachments     = 0;
        numStencilAttachments   = 0;

        for (int i = 0; i < 16; i++)
            colorHandles[i]     = 0;
        depthHandle             = 0;
        stencilHandle           = 0;

        colorStorage            = 0;
        depthStorage            = 0;
        stencilStorage          = 0;

        internalColorFormat     = 0;
        internalDepthFormat     = 0;
        internalStencilFormat   = 0;

        colorFormat             = 0;
        colorWrap               = 0;
        colorFilter             = 0;

        depthFormat             = 0;
        depthWrap               = 0;
        depthFilter             = 0;

        isComplete              = false;
        isDirty                 = false;
        isOpen                  = false;

        hasModColors            = false;
        hasModDepth             = false;
        hasModStencil           = false;
    }

    FboSetup& operator= (const FboSetup &other) {
        fboHandle               = other.fboHandle;
        width                   = other.width;
        height                  = other.height;
        depth                   = other.depth;

        numColorAttachments     = other.numColorAttachments;
        numDepthAttachments     = other.numDepthAttachments;
        numStencilAttachments   = other.numStencilAttachments;

        for (int i = 0; i < 16; i++)
            colorHandles[i]     = other.colorHandles[i];
        depthHandle             = other.depthHandle;
        stencilHandle           = other.stencilHandle;

        colorStorage            = other.colorStorage;
        depthStorage            = other.depthStorage;
        stencilStorage          = other.stencilStorage;

        internalColorFormat     = other.internalColorFormat;
        internalDepthFormat     = other.internalDepthFormat;
        internalStencilFormat   = other.internalStencilFormat;

        colorFormat             = other.colorFormat;
        colorWrap               = other.colorWrap;
        colorFilter             = other.colorFilter;

        depthFormat             = other.depthFormat;
        depthWrap               = other.depthWrap;
        depthFilter             = other.depthFilter;

        isComplete              = other.isComplete;
        isDirty                 = other.isDirty;
        isOpen                  = other.isOpen;

        hasModColors            = other.hasModColors;
        hasModDepth             = other.hasModDepth;
        hasModStencil           = other.hasModStencil;

        return *this;
    }

    bool operator== (const FboSetup &other) {
        bool col = true;
        for (int i = 0; i < 16; i++)
            if (colorHandles[i] != other.colorHandles[i])
                col = false;

        return (fboHandle               == other.fboHandle              &&
                width                   == other.width                  &&
                height                  == other.height                 &&
                depth                   == other.depth                  &&

                numColorAttachments     == other.numColorAttachments    &&
                numDepthAttachments     == other.numDepthAttachments    &&
                numStencilAttachments   == other.numStencilAttachments  &&

                /*col                                                     &&*/
                /*(for (int i = 0; i < 16; i++)
                    colorHandles[i]     == other.colorHandles[i])       &&*/
                depthHandle             == other.depthHandle            &&
                stencilHandle           == other.stencilHandle          &&

                colorStorage            == other.colorStorage           &&
                depthStorage            == other.depthStorage           &&
                stencilStorage          == other.stencilStorage         &&

                internalColorFormat     == other.internalColorFormat    &&
                internalDepthFormat     == other.internalDepthFormat    &&
                internalStencilFormat   == other.internalStencilFormat  &&
                
                colorFormat             == other.colorFormat            &&
                colorWrap               == other.colorWrap              &&
                colorFilter             == other.colorFilter            &&

                depthFormat             == other.depthFormat            &&
                depthWrap               == other.depthWrap              &&
                depthFilter             == other.depthFilter            &&

                isComplete              == other.isComplete             &&
                isDirty                 == other.isDirty                &&
                isOpen                  == other.isOpen                 &&

                hasModColors            == other.hasModColors           &&
                hasModDepth             == other.hasModDepth            &&
                hasModStencil           == other.hasModStencil)

                ? true : false;
    }

    bool operator!= (const FboSetup &other) {
        return (*this == other) ? false : true;
    }
};

#endif 
