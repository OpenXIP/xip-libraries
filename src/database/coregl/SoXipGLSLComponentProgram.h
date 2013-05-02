/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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

