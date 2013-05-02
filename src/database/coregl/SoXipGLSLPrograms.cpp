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

#include <xip/inventor/coregl/SoXipShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include <xip/inventor/coregl/ShaderProgramManager.h>

#include "SoXipGLSLPrograms.h"

#include <Inventor/actions/SoGLRenderAction.h>

// Used for insertion of defines in shader source
#include <string>
#include <vector>
#include <fstream>

// Used for timestamp lookup on shader source
#include <sys/stat.h>
#include <time.h>

#define TCALLOC(num, Type) reinterpret_cast<Type *>(calloc(num, sizeof(Type)))

#undef DEBUG
#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif


SO_NODE_SOURCE(SoXipGLSLPrograms);


SoXipGLSLPrograms::SoXipGLSLPrograms()
{
	SO_NODE_CONSTRUCTOR(SoXipGLSLPrograms);
	
    SO_NODE_ADD_FIELD(prgTags, (""));

	SO_NODE_ADD_FIELD(vpFilenames, (""));
    SO_NODE_ADD_FIELD(gpFilenames, (""));
    SO_NODE_ADD_FIELD(fpFilenames, (""));

	SO_NODE_ADD_FIELD(vpDefines, (""));
	SO_NODE_ADD_FIELD(gpDefines, (""));
	SO_NODE_ADD_FIELD(fpDefines, (""));

	mVpSensor = new SoFieldSensor(fieldChangeCB, this);
	mVpSensor->attach(&this->vpFilenames);
    mVpSensor->setPriority(0);
	mGpSensor = new SoFieldSensor(fieldChangeCB, this);
	mGpSensor->attach(&this->gpFilenames);
    mGpSensor->setPriority(0);
	mFpSensor = new SoFieldSensor(fieldChangeCB, this);
	mFpSensor->attach(&this->fpFilenames);
    mFpSensor->setPriority(0);
	
	mVpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mVpDefinesSensor->attach(&this->vpDefines);
    mVpDefinesSensor->setPriority(0);
	mGpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mGpDefinesSensor->attach(&this->gpDefines);
    mGpDefinesSensor->setPriority(0);
	mFpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mFpDefinesSensor->attach(&this->fpDefines);
    mFpDefinesSensor->setPriority(0);

  	mTagSensor = new SoFieldSensor(fieldChangeCB, this);
	mTagSensor->attach(&this->prgTags);
    mTagSensor->setPriority(0);

  	SO_NODE_ADD_FIELD(updateShaders, ());

    mUpdateFieldSensor = new SoFieldSensor(updateSensorCB, this);
	mUpdateFieldSensor->attach(&this->updateShaders);
    mUpdateFieldSensor->setPriority(0);
	mAutoUpdateTimerSensor = new SoTimerSensor(autoUpdateCB, this);
	mAutoUpdateTimerSensor->setInterval(1.0/3.0);

    SO_NODE_ADD_FIELD(autoUpdate, (false));

    mAutoUpdateCheckboxSensor = new SoFieldSensor(toggleAutoCB, this);
	mAutoUpdateCheckboxSensor->attach(&this->autoUpdate);
    mAutoUpdateCheckboxSensor->setPriority(0);

	SO_NODE_ADD_FIELD(geometryInputType, (IN_TRIANGLES));
	SO_NODE_ADD_FIELD(geometryOutputType, (OUT_TRIANGLE_STRIP));
	SO_NODE_ADD_FIELD(maxEmittedVertices, (1));

    SO_NODE_ADD_FIELD(glslVersion, (V120));
    
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_POINTS);
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_LINES);
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_LINES_ADJACENCY_EXT);
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_TRIANGLES);
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_TRIANGLES_ADJACENCY_EXT);
	SO_NODE_SET_SF_ENUM_TYPE(geometryInputType, InGeometry);

    SO_NODE_DEFINE_ENUM_VALUE(GLSLVersion, AUTO_SELECT);
    SO_NODE_DEFINE_ENUM_VALUE(GLSLVersion, V110);
    SO_NODE_DEFINE_ENUM_VALUE(GLSLVersion, V120);
    SO_NODE_DEFINE_ENUM_VALUE(GLSLVersion, V130);
    SO_NODE_DEFINE_ENUM_VALUE(GLSLVersion, V140);
    SO_NODE_DEFINE_ENUM_VALUE(GLSLVersion, V150);
    SO_NODE_SET_SF_ENUM_TYPE(glslVersion, GLSLVersion);

	SO_NODE_DEFINE_ENUM_VALUE(OutGeometry, OUT_POINTS);
	SO_NODE_DEFINE_ENUM_VALUE(OutGeometry, OUT_LINE_STRIP);
	SO_NODE_DEFINE_ENUM_VALUE(OutGeometry, OUT_TRIANGLE_STRIP);
	SO_NODE_DEFINE_ENUM_VALUE(OutGeometry, OUT_TRIANGLES);
    SO_NODE_SET_SF_ENUM_TYPE(geometryOutputType, OutGeometry);

    SO_NODE_ADD_FIELD(nodeUpdated, ());

    mProgramBatchList = SbPList();

    mFieldBitmask = 0;
    mTimedUpdate = false;
    mIsAutoOn = false;
}

/**
 *	Destructor
 */	
SoXipGLSLPrograms::~SoXipGLSLPrograms()
{
    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    ProgramBatch * batch = 0;
    if (manager)
        for (int i = 0; i < mProgramBatchList.getLength(); i++)
            if (batch = reinterpret_cast<ProgramBatch *>(mProgramBatchList[i]))
                if (batch->tag != "")
                    manager->removeEntry(batch->tag.getString());

    // Delete self
    delete mVpSensor;
	delete mFpSensor;
	delete mGpSensor;
	delete mGpDefinesSensor;
	delete mVpDefinesSensor;
	delete mFpDefinesSensor;
	delete mTagSensor;

	delete mUpdateFieldSensor;
	delete mAutoUpdateTimerSensor;
	delete mAutoUpdateCheckboxSensor;
}

void SoXipGLSLPrograms::fieldChangeCB(void * data, SoSensor * sensor)
{
    // Accumulate bitmask of manipulated fields
    SoXipGLSLPrograms * obj = reinterpret_cast<SoXipGLSLPrograms *>(data);
    if      (sensor == obj->mVpSensor)
        obj->mFieldBitmask |= VP_FILENAMES;
    else if (sensor == obj->mGpSensor)
        obj->mFieldBitmask |= GP_FILENAMES;
    else if (sensor == obj->mFpSensor)
        obj->mFieldBitmask |= FP_FILENAMES;
    else if (sensor == obj->mVpDefinesSensor)
        obj->mFieldBitmask |= VP_DEFINES;
    else if (sensor == obj->mGpDefinesSensor)
        obj->mFieldBitmask |= GP_DEFINES;
    else if (sensor == obj->mFpDefinesSensor)
        obj->mFieldBitmask |= FP_DEFINES;
    else if (sensor == obj->mTagSensor)
        obj->mFieldBitmask |= TAG_NAME;
}

/**	
 *	Initializes the class
 */
void SoXipGLSLPrograms::initClass()
{
	SO_NODE_INIT_CLASS(SoXipGLSLPrograms, SoNode, "SoNode");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipShaderProgramElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLSLShaderProgramElement);
}

/**
 *  One of two main update functions.
 *  Gets triggered by user interaction.
 *  Can be called both from GLRender or from any other scope.
 */
void SoXipGLSLPrograms::UpdateAction()
{
    if (prgTags.getNum() == vpFilenames.getNum() &&
        prgTags.getNum() == fpFilenames.getNum() &&
        prgTags.getNum() == gpFilenames.getNum() &&
        prgTags.getNum() == vpDefines.getNum() &&
        prgTags.getNum() == fpDefines.getNum() &&
        prgTags.getNum() == gpDefines.getNum())
    {
        evaluateProgramBatches();
    }
    else
    {
        SoDebugError::postWarning(__FUNCTION__, "Number of entries in fields do not match, no action taken\n");
        SoDebugError::postInfo(__FUNCTION__, "vpFn %d gpFn %d fpFn %d vpDf %d gpDf %d fpDf %d",
            vpFilenames.getNum(), gpFilenames.getNum(), fpFilenames.getNum(),
            vpDefines.getNum(), gpDefines.getNum(), fpDefines.getNum());
    }

    mFieldBitmask = 0;
    mTimedUpdate = false;
    nodeUpdated.touch();
}

/**
 *  Second out of two main update functions.
 *  Gets triggered by a timer for automatics recompilations.
 *  Can be called both from GLRender or from any other scope.
 */
void SoXipGLSLPrograms::AutoUpdateAction()
{
    bool dirty = false;
    ProgramBatch * batch = 0;

    for (int i = 0; i < mProgramBatchList.getLength(); i++)
    {
        batch = reinterpret_cast<ProgramBatch *>(mProgramBatchList[i]);
        dirty |= checkTimeStamps(&batch->vertShader, vpFilenames[i]);
        dirty |= checkTimeStamps(&batch->geomShader, gpFilenames[i]);
        dirty |= checkTimeStamps(&batch->fragShader, fpFilenames[i]);
    }

    if (dirty)
    {
        mTimedUpdate = true;
        startNotify();
    }
}

/**
 *  Second out of two main update functions.
 *  Gets triggered by a timer for automatics recompilations.
 *  Can be called both from GLRender or from any other scope.
 */
void SoXipGLSLPrograms::GLValidityCheck()
{
    bool dirty = false;
    GLint prog = 0;
    ProgramBatch * batch = 0;
    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    
    if (!manager)
    {
        dirty = true;
    }
    else
    {
        for (int i = 0; i < mProgramBatchList.getLength(); i++)
        {
            batch = reinterpret_cast<ProgramBatch *>(mProgramBatchList[i]);
            prog = manager->getProgramHandle(batch->tag.getString());
            if (!glIsProgram(prog))
                dirty = true;
        }
    }

    if (dirty)
    {
        mTimedUpdate = true;
        startNotify();
    }
}

bool SoXipGLSLPrograms::checkTimeStamps(ShaderBatch * batch, const SbString& filename)
{
    if (!batch)
        return false;

    bool dirty = false; 

    int tod = ShaderEngine::getSourceFileTimeStamp(filename.getString());
    int sts = batch->source.getSourceTimeStamp();
    if (tod > sts)
        dirty = true;

    batch->dirtyTimestamp = dirty;
    return dirty;
}


void SoXipGLSLPrograms::setTimeStamps(ShaderBatch * batch, const SbString& filename)
{
    if (!batch)
        return;

    int tod = ShaderEngine::getSourceFileTimeStamp(filename.getString());
    batch->source.setSourceTimeStamp(tod);

    batch->dirtyTimestamp = false;
}


/**
 *	Concatenates all componets into batch->vSource/gSource/fSource.
 */	
bool SoXipGLSLPrograms::updateSingleShader(ShaderBatch * batch, const SbString& filename, const SbString& defines, std::string& errstr)
{
    if (!batch)
        return false;

    std::string funcs = "";
    int shaderType = batch->source.getType();

    // Add the version string to the source file
    std::string s;
    switch(glslVersion.getValue())
    {
    default:
    case AUTO_SELECT:
        break;
    case V110:
        s += "#version 110 \n\n";
        break;
    case V120:
        s += "#version 120 \n\n";
        break;
    case V130:
        s += "#version 130 \n\n";
        break;
    case V140:
        s += "#version 140 \n\n";
        break;
    case V150:
        s += "#version 150 \n\n";
        break;
    }
    batch->source.addToSuppHeader(s.c_str());

    std::string defstr(defines.getString());
    std::string tmp, defVal;
    int p0 = 0;
    int p1 = 0;
    int d = defstr.find_first_not_of(",");
    while (d != defstr.npos)
    {
        p1 = defstr.find_first_of(",", p0);
        defVal = defstr.substr(p0,p1-p0);
        if (!defVal.empty() && defVal.find_first_not_of(" ") != defVal.npos)
        {
            tmp = std::string("#define ") + defVal;
            batch->source.addToSuppHeader(tmp.c_str());
        }
        p0 = p1+1;
        d  = p1;
    }

    batch->source.addToSuppHeader(ShaderEngine::readShaderSourceFile(filename.getString()).c_str());
    batch->handle = ShaderEngine::compileShader(batch->source.getFullComponent(), shaderType, errstr);
    //batch->timestamp = (batch->handle) ? time(NULL) : 0;
#ifdef WIN32
    batch->timestamp = (batch->handle) ? QueryPerformanceCounter((LARGE_INTEGER*)&batch->timestamp) : 0;
#else //UNIX
    if (!(batch->handle))
    {
        batch->timestamp = 0;
    }
    else
    {
        struct timeval curTime;
        gettimeofday(&curTime, NULL);
        //batch->timestamp = ((int64_t)curTime.tv_sec * (1000*1000) + (int64_t)curTime.tv_usec);
        batch->timestamp = (int64_t)curTime.tv_sec;
    }
#endif //WIN32
    if (!errstr.empty())
        return false;

    return true;
}


/**
 *	Update single shader.
 */
bool SoXipGLSLPrograms::updateSingleProgram(ProgramBatch * batch, std::string& errstr)
{
    if (!batch)
        return false;

    ShaderBatch & geomShader = batch->geomShader;
	ShaderEngine::deleteProgram(batch->handle);

    if (geomShader.handle)
    {
        batch->handle = ShaderEngine::linkShaders(batch->vertShader.handle,
                                              batch->geomShader.handle,
                                              batch->fragShader.handle,
                                              maxEmittedVertices.getValue(),
											  geometryInputType.getValue(),
											  geometryOutputType.getValue(),
                                              errstr);
    }
	else
	{
		batch->handle = ShaderEngine::linkShaders(batch->vertShader.handle,
                                              batch->geomShader.handle,
                                              batch->fragShader.handle,
                                              errstr);
    }

//TODO: need better fix !
#ifdef WIN32
    int isValid = 0;
    glGetProgramiv(batch->handle, GL_VALIDATE_STATUS, &isValid);

    if (!isValid || !errstr.empty())
#else //for some reason the validation always fails under mac & linux ... may be something with the file format?
    if (!errstr.empty())
#endif //WIN32
    {
        if (glIsProgram(batch->handle))
            glDeleteProgram(batch->handle);
        batch->handle = 0;
    }
    
#ifdef WIN32
    //batch->timestamp = (batch->handle) ? time(NULL) : 0;
    batch->timestamp = (batch->handle) ? QueryPerformanceCounter((LARGE_INTEGER*)&batch->timestamp) : 0;
#else //UNIX
    if (!(batch->handle))
    {
        batch->timestamp = 0;
    }
    else
    {
        struct timeval curTime;
        gettimeofday(&curTime, NULL);
        //batch->timestamp = ((int64_t)curTime.tv_sec * (1000*1000) + (int64_t)curTime.tv_usec);
        batch->timestamp = (int64_t)curTime.tv_sec;
    }
#endif //WIN32
    
    if (!errstr.empty())
    {
        SoDebugError::post("GLSLPrograms", "\"%s\": %s", batch->tag.getString(), errstr.c_str());
        return false;
    }

    return true;
}




/**
 *	Update existing shader batch by per field comparison.
 */
bool SoXipGLSLPrograms::updateShaderBatch(ShaderBatch * batch, const SbString& filename, const SbString& defines, std::string& errstr)
{
    if (!batch)
        return false;

    bool dirty = false;
    int shaderType = batch->source.getType();

    dirty |= batch->dirtyTimestamp; 
    dirty |= batch->dirtySource;

    if (dirty)
    {
        this->setTimeStamps(batch, filename);
        ShaderEngine::deleteShader(batch->handle);
        batch->source.clearContent();
        batch->timestamp = 0;
        batch->dirtySource = false;
        if (filename != "")
        {
            this->updateSingleShader(batch, filename, defines, errstr);
        }
    }

    if (!errstr.empty())
    {
        SoDebugError::post("GLSLPrograms", "\"%s\": %s", batch->source.getName(), errstr.c_str());
    }

    return dirty;
}





/**
 * Update batch entry in ShaderProgramManager singleton.
 * @param batch The shader batch we want to update.
 * @see removeManagerEntry()
 */
void SoXipGLSLPrograms::updateManagerEntry(ProgramBatch * batch)
{
    if (!batch)
        return;

    // Insert entry
    if (batch->tag != "")
    {
        ShaderProgramManager * manager = ShaderProgramManager::getInstance();

        const char * tag = batch->tag.getString();

        if (manager && tag && *tag)
        {
            unsigned int returnedHandle =
                manager->insertEntry(tag, batch->handle, batch->timestamp);

            // Decipher return code
            if (returnedHandle == 0)
            {
                SoDebugError::postWarning("GLSLPrograms",
                    "Manager returned 0 for entry \"%s\", possibly due to invalid program\n", tag);
            }
            else if (returnedHandle != batch->handle)
                SoDebugError::postInfo("Shader Manager", "Shader entry \"%s\" updated (replaced)", tag);
            else
                SoDebugError::postInfo("Shader Manager",
                                       "Shader entry \"%s\" updated", tag);
        }
    }
}

/**
 *  Remove entry in ShaderProgramManager singleton.
 *  @param batch The shader batch we want to update.
 *  @see updateManagerEntry()
 */
void SoXipGLSLPrograms::removeManagerEntry(ProgramBatch * batch)
{
    if (!batch)
        return;

    if (batch->tag.getString() != "")
    {
        ShaderProgramManager * manager = ShaderProgramManager::getInstance();
        if (manager)
            manager->removeEntry(batch->tag.getString());
    }
}

bool SoXipGLSLPrograms::evaluateFieldBitmaskChange(const SoMFString& field, SoMFString& m_field, int slot)
{
    if (m_field.getNum() != field.getNum())
    {
        m_field.setNum( field.getNum() );
    }

    if (m_field[slot] != field[slot])
    {
        m_field.set1Value(slot, field[slot]);
        return true;
    }

    return false;
    //{
    //    switch (shaderType)
    //    {
    //    case GL_VERTEX_SHADER :
    //        dirty |= (mFieldBitmask & (VP_FILENAMES | VP_DEFINES)) ? true : false;
    //        break;
    //    case GL_GEOMETRY_SHADER_EXT :
    //        dirty |= (mFieldBitmask & (GP_FILENAMES | GP_DEFINES)) ? true : false;
    //        break;
    //    case GL_FRAGMENT_SHADER :
    //        dirty |= (mFieldBitmask & (FP_FILENAMES | FP_DEFINES)) ? true : false;
    //        break;
    //    default:
    //        errstr.append("Unknown shader type");
    //        return false;
    //    }
    //}
}

/**
 *	Compare timestamps in internal list and update if necessary.
 *  Function only executes if no fields have been touched, this way we
 *  avoid costly validation of filenames. No cleaning and synchronizing
 *  need to be done since fields and values are intact.
 */
void SoXipGLSLPrograms::evaluateSingleProgramBatch(ProgramBatch * batch, int slot)
{
    if (!batch)
        return;

    if (mFieldBitmask & TAG_NAME)
    {
        if (batch->tag != prgTags[slot])
        {
            if (batch->tag != "")
                removeManagerEntry(batch);
            batch->tag = prgTags[slot];
        }
    }

    if (mFieldBitmask & VP_FILENAMES)
        batch->vertShader.dirtySource |= evaluateFieldBitmaskChange(vpFilenames, m_vpFilenames, slot);
    if (mFieldBitmask & GP_FILENAMES)
        batch->geomShader.dirtySource |= evaluateFieldBitmaskChange(gpFilenames, m_gpFilenames, slot);
    if (mFieldBitmask & FP_FILENAMES)
        batch->fragShader.dirtySource |= evaluateFieldBitmaskChange(fpFilenames, m_fpFilenames, slot);
    if (mFieldBitmask & VP_DEFINES)
        batch->vertShader.dirtySource |= evaluateFieldBitmaskChange(vpDefines, m_vpDefines, slot);
    if (mFieldBitmask & GP_DEFINES)
        batch->geomShader.dirtySource |= evaluateFieldBitmaskChange(gpDefines, m_gpDefines, slot);
    if (mFieldBitmask & FP_DEFINES)
        batch->fragShader.dirtySource |= evaluateFieldBitmaskChange(fpDefines, m_fpDefines, slot);

    std::string errstr = "";
    std::string errone = "";
    bool dirty = false;

    dirty |= this->updateShaderBatch(&batch->vertShader, vpFilenames[slot], vpDefines[slot], errone);
    errstr += errone;
    errone = "";

    dirty |= this->updateShaderBatch(&batch->geomShader, gpFilenames[slot], gpDefines[slot], errone);
    errstr += errone;
    errone = "";

    dirty |= this->updateShaderBatch(&batch->fragShader, fpFilenames[slot], fpDefines[slot], errone);
    errstr += errone;
    errone = "";

    if (dirty)
    {
        this->updateSingleProgram(batch, errone);
        errstr += errone;
    }

    if (!errstr.empty())
    {
        if (batch->tag != "")
            removeManagerEntry(batch);
    }
    else if (dirty)
    {
	    this->updateManagerEntry(batch);
    }
}


void SoXipGLSLPrograms::evaluateProgramBatches()
{
    ProgramBatch * batch = 0;

    // Force internal list to reflect fields if tag field has changed
    for (int i = 0; i < prgTags.getNum(); i++)
    {
        if (mProgramBatchList.getLength() <= i)
        {
            ProgramBatch * newBatch = new ProgramBatch();

            newBatch->vertShader.source.setName(std::string(prgTags[0].getString() + std::string(" vertex Shader")).c_str());
            newBatch->geomShader.source.setName(std::string(prgTags[0].getString() + std::string(" geometry Shader")).c_str());
            newBatch->fragShader.source.setName(std::string(prgTags[0].getString() + std::string(" fragment Shader")).c_str());

            newBatch->vertShader.source.setType(GL_VERTEX_SHADER);
            newBatch->geomShader.source.setType(GL_GEOMETRY_SHADER_EXT);
            newBatch->fragShader.source.setType(GL_FRAGMENT_SHADER);

            mProgramBatchList.append(newBatch);
        }

        batch = reinterpret_cast<ProgramBatch *>(mProgramBatchList[i]);

        if (batch)
        {
            evaluateSingleProgramBatch(batch, i);
        }
        else
        {
            SoDebugError::post("SoXipGLSLPrograms::compareByTags", "Empty slot found, this should not happen!\n");
        }
    }
}




/**
 *	GLRender.
 *  Binds program 0 after update since we have no idea which shader
 *  the user wants anyway.
 */
void SoXipGLSLPrograms::GLRender(SoGLRenderAction *action)
{
    this->GLValidityCheck();

	if (mTimedUpdate || mFieldBitmask)
	{
        int prevShader = SoXipGLSLShaderProgramElement::get(action->getState());
        this->UpdateAction();
        SoXipGLSLShaderProgramElement::set(action->getState(), prevShader);
	}
}


void SoXipGLSLPrograms::updateSensorCB(void *data, SoSensor *sensor)
{
	// cast editor object
	SoXipGLSLPrograms *thisObj = (SoXipGLSLPrograms*)data;

    if (sensor == thisObj->mUpdateFieldSensor)
    {
        ProgramBatch * batch = 0;
        for (int i = 0; i < thisObj->mProgramBatchList.getLength();  i++)
        {
            if (batch = reinterpret_cast<ProgramBatch *>(thisObj->mProgramBatchList[i]))
            {
                batch->vertShader.dirtyTimestamp = true;
                batch->geomShader.dirtyTimestamp = true;
                batch->fragShader.dirtyTimestamp = true;
            }
        }
    }

    thisObj->mTimedUpdate = true;
    thisObj->startNotify();
}

void SoXipGLSLPrograms::autoUpdateCB(void *data, SoSensor *sensor)
{
	// cast editor object
	SoXipGLSLPrograms *thisObj = (SoXipGLSLPrograms*)data;
    thisObj->AutoUpdateAction();
}

void SoXipGLSLPrograms::toggleAutoCB(void *data, SoSensor *sensor)
{
	// cast editor object
	SoXipGLSLPrograms *thisObj = (SoXipGLSLPrograms*)data;

    if ((thisObj->mIsAutoOn && !thisObj->autoUpdate.getValue()) ||
        (!thisObj->mIsAutoOn && thisObj->autoUpdate.getValue()))
    {
        thisObj->mIsAutoOn = (thisObj->autoUpdate.getValue()) ? true : false;
        (thisObj->mIsAutoOn) ? thisObj->mAutoUpdateTimerSensor->schedule()
                             : thisObj->mAutoUpdateTimerSensor->unschedule();
    }
}


