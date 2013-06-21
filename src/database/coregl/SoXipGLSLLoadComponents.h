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

#ifndef SO_XIP_GLSL_LOAD_COMPONENTS_H
#define SO_XIP_GLSL_LOAD_COMPONENTS_H


/**
 *  Component       : XIP
 *  Name            : SoXipGLSLLoadComponents
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


#define MYMF


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

#include <xip/inventor/coregl/ShaderComponentLibrary.h>
#include <xip/inventor/coregl/ShaderEngine.h>
#include <xip/inventor/coregl/ShaderSourceComponent.h>

#include <vector>


class SoGLRenderAction;


/**
 *	SoXipGLSLLoadComponents. An Open Inventor node to load
 *	GLSL shader programs using the ShaderprogramManager.
 */
class SoXipGLSLLoadComponents : public SoNode
{
    SO_NODE_HEADER(SoXipGLSLLoadComponents);

    typedef ShaderEngine::ShaderBatch ShaderBatch;

    enum TouchedFields
    {
        VP_FILENAMES    = 0x01,
        GP_FILENAMES    = 0x02,
        FP_FILENAMES    = 0x04,
        VP_COMPONENTS   = 0x08,
        GP_COMPONENTS   = 0x10,
        FP_COMPONENTS   = 0x20,
        TAG_NAMES       = 0x40
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

    SoXipGLSLLoadComponents();
	static void initClass();

    //SoSFString    vpFilenames;
    //SoSFString    gpFilenames;
    //SoSFString    fpFilenames;
    //SoSFBool      autoNames;
	//SoSFString    vpComponents;
	//SoSFString    gpComponents;
	//SoSFString    fpComponents;

    SoMFString	vpFilenames;
    SoMFString	gpFilenames;
    SoMFString	fpFilenames;
    SoSFBool    autoNames;
	SoMFString	vpComponents;
	SoMFString	gpComponents;
	SoMFString	fpComponents;

    SoSFTrigger update;
    SoSFBool    autoUpdate;
    SoSFBool    testCompilation;

	SoSFEnum    geometryInputType;
	SoSFEnum    geometryOutputType;
	SoSFInt32   maxEmittedVertices;

protected:

    ~SoXipGLSLLoadComponents();

    virtual void GLRender(SoGLRenderAction *action);
    static void updateSensorCB(void *data, SoSensor *sensor);
    static void fieldChangeCB(void *data, SoSensor *sensor);
    static void autoUpdateCB(void *data, SoSensor *sensor);
    static void toggleAutoCB(void *data, SoSensor *sensor);

    void UpdateAction();
	void AutoUpdateAction();

    SoFieldSensor				*mTagSensor;
    SoFieldSensor				*mVpSensor;
	SoFieldSensor				*mGpSensor;
	SoFieldSensor				*mFpSensor;
	SoFieldSensor				*mVpComponentsSensor;
	SoFieldSensor				*mGpComponentsSensor;
	SoFieldSensor				*mFpComponentsSensor;

    SoFieldSensor               *mUpdateFieldSensor;
    SoTimerSensor               *mAutoUpdateTimerSensor;
    SoFieldSensor               *mAutoUpdateCheckboxSensor;

private:

    bool    updateSingleSource(ShaderSourceComponent * comp, const SbString & compName, const SbString & fileName, GLenum shaderType, std::string& errstr);
    bool    updateShaderComponent(ShaderSourceComponent * comp, const SbString & compName, const SbString & fileName, GLenum shaderType, std::string& errstr);
    void    evaluateShaderComponent(ShaderSourceComponent * comp, const SbString & compName, const SbString & fileName, GLenum shaderType);

    void    UpdateComponents(std::vector<ShaderSourceComponent> & compVec, const SoMFString & compMF, const SoMFString & fileMF, GLenum shaderType);

    void    updateLibraryEntry(ShaderSourceComponent * comp);
    void    removeLibraryEntry(ShaderSourceComponent * comp);

    bool    checkTimeStamp(ShaderSourceComponent * comp, const SbString& fileName);
    void    setTimeStamp(ShaderSourceComponent * comp, const SbString& fileName);

    std::vector<ShaderSourceComponent> mVpComponents;
    std::vector<ShaderSourceComponent> mGpComponents;
    std::vector<ShaderSourceComponent> mFpComponents;

    int         mFieldBitmask;
    bool		mTimedUpdate;
    bool        mIsAutoOn;
};

#endif // SO_XIP_GLSL_COMPONENT_PROGRAM_H

