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

#ifndef SO_XIP_GLSL_PROGRAMS_H
#define SO_XIP_GLSL_PROGRAMS_H


/**
 *  Component       : XIP
 *  Name            : SoXipGLSLPrograms
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
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
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
#include <xip/inventor/coregl/ShaderSourceComponent.h>

class SoGLRenderAction;


/**
 *	SoXipGLSLPrograms. An Open Inventor node to load
 *	GLSL shader programs using the ShaderprogramManager.
 */
class SoXipGLSLPrograms : public SoNode
{
    SO_NODE_HEADER(SoXipGLSLPrograms);

    typedef ShaderEngine::ProgramBatch ProgramBatch;
    typedef ShaderEngine::ShaderBatch  ShaderBatch;

    enum TouchedFields
    {
        VP_FILENAMES = 0x01,
        GP_FILENAMES = 0x02,
        FP_FILENAMES = 0x04,
        VP_DEFINES    = 0x08,
        GP_DEFINES    = 0x10,
        FP_DEFINES    = 0x20,
        TAG_NAME      = 0x40
    };

    enum GLSLVersion
    {
        AUTO_SELECT,
        V110,
        V120,
        V130,
        V140,
        V150
    };

    enum InGeometry
    {
      IN_POINTS=GL_POINTS,
	  IN_LINES=GL_LINES,
      IN_LINES_ADJACENCY_EXT=GL_LINES_ADJACENCY_EXT,
	  IN_TRIANGLES=GL_TRIANGLES,
	  IN_TRIANGLES_ADJACENCY_EXT=GL_TRIANGLES_ADJACENCY_EXT
	};
	 
	enum OutGeometry
    {
	    OUT_POINTS=GL_POINTS,
	    OUT_LINE_STRIP=GL_LINE_STRIP,
	    OUT_TRIANGLE_STRIP=GL_TRIANGLE_STRIP,
	    OUT_TRIANGLES=GL_TRIANGLES
	};

public:

    SoXipGLSLPrograms();
	static void initClass();

    SoMFString	prgTags;
    SoMFString	vpFilenames;
    SoMFString	gpFilenames;
	SoMFString	fpFilenames;
	SoMFString	vpDefines;
	SoMFString	gpDefines;
	SoMFString	fpDefines;
    SoSFTrigger updateShaders;
    SoSFTrigger nodeUpdated;
    SoSFBool    autoUpdate;

	SoSFEnum    geometryInputType;
	SoSFEnum    geometryOutputType;
	SoSFInt32   maxEmittedVertices;
    /**
    *   Field to force the shader(s) to a specific version.
    */
    SoSFEnum    glslVersion;

protected:

    ~SoXipGLSLPrograms();

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

    SoFieldSensor               *mUpdateFieldSensor;
    SoTimerSensor               *mAutoUpdateTimerSensor;
    SoFieldSensor               *mAutoUpdateCheckboxSensor;

private:

    bool    updateSingleShader(ShaderBatch * batch, const SbString& filename, const SbString& defines, std::string& errstr);
    bool    updateShaderBatch(ShaderBatch * batch, const SbString& filename, const SbString& defines, std::string& errstr);
    bool    updateSingleProgram(ProgramBatch * batch, std::string& errstr);
    void    evaluateSingleProgramBatch(ProgramBatch * batch, int slot);
    void    evaluateProgramBatches();

    void    updateManagerEntry(ProgramBatch * batch);
    void    removeManagerEntry(ProgramBatch * batch);

    bool    checkTimeStamps(ShaderBatch * batch, const SbString& filename);
    void    setTimeStamps(ShaderBatch * batch, const SbString& filename);

    bool    evaluateFieldBitmaskChange(const SoMFString& field, SoMFString& m_field, int slot);

    SbPList     mProgramBatchList;

    SoMFString	m_prgTags;
    SoMFString	m_vpFilenames;
    SoMFString	m_gpFilenames;
	SoMFString	m_fpFilenames;
	SoMFString	m_vpDefines;
	SoMFString	m_gpDefines;
	SoMFString	m_fpDefines;

    int         mFieldBitmask;
    bool		mTimedUpdate;
    bool        mIsAutoOn;
};

#endif // SO_XIP_GLSL_COMPONENT_PROGRAM_H

