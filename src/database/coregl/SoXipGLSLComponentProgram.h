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

#ifndef SO_XIP_GLSL_COMPONENT_PROGRAM_H
#define SO_XIP_GLSL_COMPONENT_PROGRAM_H


#define TEST_DEF


/**
 *  Component       : XIP
 *  Name            : SoXipGLSLComponentProgram
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Reimplementation of SoXipLoadShader.
 *                      Purpose is to provide ability to load
 *                      multiple shaders from a single node and
 *                      to use 'conditioned recompilation'.
 *                      "compile only what must be compiled"
 *                      TODO! See non-member function xip_mshaders_tokensize(...)
 *
 *  Copyright � Siemens AG 2006-2007. All Rights Reserved.
 */


#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/SbPList.h>

#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/fields/SoSFTrigger.h>

#include <xip/inventor/coregl/ShaderEngine.h>
#include <xip/inventor/coregl/ShaderComponentLibrary.h>
#include <xip/inventor/coregl/ShaderSourceComponent.h>

#include <list>

class SoGLRenderAction;


/**
 *	SoXipGLSLComponentProgram. An Open Inventor node to load
 *	GLSL shader programs using the ShaderprogramManager.
 */
class SoXipGLSLComponentProgram : public SoNode
{
    SO_NODE_HEADER(SoXipGLSLComponentProgram);

    typedef ShaderEngine::ProgramBatch          ProgramBatch;
    typedef ShaderEngine::ShaderBatch           ShaderBatch;
    typedef ShaderSourceComponent::LineEntry    LineEntry;

    typedef ShaderSourceComponent::DefineLinePair_t DefineLinePair_t;
    typedef ShaderSourceComponent::DefineLineVec_t  DefineLineVec_t;
    typedef ShaderSourceComponent::FuncLineMap_t    FuncLineMap_t;

    enum TouchedFields
    {
        VP_COMPONENTS = 0x01,
        GP_COMPONENTS = 0x02,
        FP_COMPONENTS = 0x04,
        VP_DEFINES    = 0x08,
        GP_DEFINES    = 0x10,
        FP_DEFINES    = 0x20,
        TAG_NAME      = 0x40,
        PRINT_TO_FILE = 0x80
    };
/*    
    enum InGeometry {
      IN_POINTS=GL_POINTS,
	  IN_LINES=GL_LINES,
      IN_LINES_ADJACENCY_EXT=GL_LINES_ADJACENCY_EXT,
	  IN_TRIANGLES=GL_TRIANGLES,
	  IN_TRIANGLES_ADJACENCY_EXT=GL_TRIANGLES_ADJACENCY_EXT
	};
	 
	enum OutGeometry { 
	    OUT_POINTS=GL_POINTS,
	    OUT_LINE_STRIP=GL_LINE_STRIP,
	    OUT_TRIANGLE_STRIP=GL_TRIANGLE_STRIP,
	    OUT_TRIANGLES=GL_TRIANGLES
	};
*/
public:

    SoXipGLSLComponentProgram();
	static void initClass();

    SoSFString	prgTag;
    SoMFString	vpComponents;
    SoMFString	gpComponents;
	SoMFString	fpComponents;
	SoMFString	vpDefines;
	SoMFString	gpDefines;
	SoMFString	fpDefines;
    SoSFTrigger updateShaders;
    SoSFBool    autoUpdate;
    SoSFTrigger shadersUpdated;
    SoSFTrigger printToFile;
    SoSFString	filename;
/*
	SoSFEnum    geometryInputType;
	SoSFEnum    geometryOutputType;
	SoSFInt32   maxEmittedVertices;
*/
protected:

    ~SoXipGLSLComponentProgram();

    virtual void GLRender(SoGLRenderAction *action);
    static void updateSensorCB(void *data, SoSensor *sensor);
    static void fieldChangeCB(void *data, SoSensor *sensor);
    static void autoUpdateCB(void *data, SoSensor *sensor);
    static void toggleAutoCB(void *data, SoSensor *sensor);

    void UpdateAction();
	void AutoUpdateAction();
	void GLValidityCheck();

    SoFieldSensor				*mTagSensor;
    SoFieldSensor				*mVpSensor;
	SoFieldSensor				*mGpSensor;
	SoFieldSensor				*mFpSensor;
	SoFieldSensor				*mVpDefinesSensor;
	SoFieldSensor				*mGpDefinesSensor;
	SoFieldSensor				*mFpDefinesSensor;
    SoFieldSensor				*mFileSensor;

    SoFieldSensor               *mUpdateFieldSensor;
    SoTimerSensor               *mAutoUpdateTimerSensor;
    SoFieldSensor               *mAutoUpdateCheckboxSensor;

private:

    void    addDefineLineEntry(const std::string &key, const ShaderSourceComponent::LineEntry &entry);

    void    updateLibraryUniforms(SoGLRenderAction *action);

    bool    updateSingleShader(ShaderBatch * batch, SoMFString& components, SoMFString& defines, std::string& errstr);
    bool    updateShaderBatch(ShaderBatch * batch, SoMFString& components, SoMFString& defines, std::vector<int>& timevec, std::string& errstr);
    bool    updateSingleProgram(ProgramBatch * batch, std::string& errstr);
    void    evaluateProgramBatch(ProgramBatch * batch);

    void    updateManagerEntry(ProgramBatch * batch);
    void    removeManagerEntry(ProgramBatch * batch);

    bool    checkTimeStamps(ShaderBatch * batch, SoMFString& components, std::vector<int>& timevec);
    void    setTimeStamps(ShaderBatch * batch, SoMFString& components, std::vector<int>& timevec);

    void    printCurrentSourceToFile();

    ProgramBatch             mBatch;

    std::vector<int>         mVsTimeStamps;
    std::vector<int>         mGsTimeStamps;
    std::vector<int>         mFsTimeStamps;

    std::vector<LineEntry>           mSLines;
    std::vector<LineEntry>           mHLines;
    std::vector<LineEntry>           mGLines;
    std::vector<LineEntry>           mLines;
    DefineLineVec_t             mDefLines;
    //std::map<std::string, LineEntry> mFuncLines;
    FuncLineMap_t               mFuncLines;

    int         mFieldBitmask;
    int         mNodeId;
    bool		mTimedUpdate;
    bool        mIsAutoOn;
};

#define NFO(str) SoDebugError::postInfo(__FUNCTION__, str)
#define NFO1(str, a1) SoDebugError::postInfo(__FUNCTION__, str, a1)
#define NFO2(str, a1, a2) SoDebugError::postInfo(__FUNCTION__, str, a1, a2)

#endif // SO_XIP_GLSL_COMPONENT_PROGRAM_H

