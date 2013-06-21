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

#ifndef SHADER_PROGRAM_MANAGER_H
#define SHADER_PROGRAM_MANAGER_H

#include <xip/inventor/coregl/xipivcoregl.h>

#include <xip/system/standard.h>

/**
 *  Component       : XIP
 *  Name            : ShaderProgramManager
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     : Class Declaration/Definition.
 *                    Singleton class providing support
 *                    for a shader manager that handles
 *                    all compiled and linked shaders.
 *
 *  Copyright � Siemens AG 2006-2007. All Rights Reserved.
 */


class XIPIVCOREGL_API ShaderProgramManager
{
    struct ShaderEntry {
    public:
        char *              tag;               /**< shader frontend identifier */
        unsigned int        programHandle;     /**< program ID (not shader IDs) */
        __uint64    timeStamp;         /**< latest compilation */
#if 0
        // friend class ShaderProgramManager;

    private:
        ShaderEntry * prev;             /**< link in list */
        ShaderEntry * next;             /**< link in list */
#endif
    };

public:
    static void initClass();
    static ShaderProgramManager * getInstance();
    /** Manager entry insertion */
    unsigned int    insertEntry(const char * newTag, unsigned int newID, __uint64 newTimeStamp);
    /** Manager entry removal */
    unsigned int    removeEntry(const char * iSearchTag);
    /** Extraction of handle */
    unsigned int    getProgramHandle(const char * iSearchTag);
    /** Extraction of timestamp */
    __uint64 getTimeStamp(const char * iSearchTag);

    /** Use only if insertEntry/getprogramHandle/getTimeStamp not sufficient !! */
    ShaderEntry *   getEntry(const char * iSearchTag);

    /** Use for debug purposes ONLY */
    char *          getAllTagsAsOneString();
    void            deleteAllEntries();

protected:
    ShaderProgramManager();
    ~ShaderProgramManager();
    /** Internal search func */
    ShaderEntry * findEntry(const char * iSearchTag);

    static ShaderProgramManager * mInstance;    /**< Singleton object */
#if 0
    ShaderEntry * mEntryListAnchor;             /**< Beginning of list */
#else
    class EntryMap;

    EntryMap * mEntryMap;
#endif
};

#endif // SHADER_PROGRAM_MANAGER_H


