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

#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>

#include <xip/inventor/coregl/SoXipShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include <xip/inventor/coregl/ShaderComponentLibrary.h>
#include <xip/inventor/coregl/ShaderProgramManager.h>
#include <xip/inventor/coregl/ShaderSourceComponent.h>

#include "SoXipGLSLComponentProgram.h"

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







SO_NODE_SOURCE(SoXipGLSLComponentProgram);


SoXipGLSLComponentProgram::SoXipGLSLComponentProgram()
{
	SO_NODE_CONSTRUCTOR(SoXipGLSLComponentProgram);
	
    SO_NODE_ADD_FIELD(prgTag, (""));

	SO_NODE_ADD_FIELD(vpComponents, (""));
    SO_NODE_ADD_FIELD(gpComponents, (""));
    SO_NODE_ADD_FIELD(fpComponents, (""));

	SO_NODE_ADD_FIELD(vpDefines, (""));
	SO_NODE_ADD_FIELD(gpDefines, (""));
	SO_NODE_ADD_FIELD(fpDefines, (""));

    vpComponents.deleteValues(0);
    gpComponents.deleteValues(0);
    fpComponents.deleteValues(0);

    vpDefines.deleteValues(0);
    gpDefines.deleteValues(0);
    fpDefines.deleteValues(0);

	mVpSensor = new SoFieldSensor(fieldChangeCB, this);
	mVpSensor->attach(&this->vpComponents);
	mGpSensor = new SoFieldSensor(fieldChangeCB, this);
	mGpSensor->attach(&this->gpComponents);
	mFpSensor = new SoFieldSensor(fieldChangeCB, this);
	mFpSensor->attach(&this->fpComponents);
	
	mVpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mVpDefinesSensor->attach(&this->vpDefines);
	mGpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mGpDefinesSensor->attach(&this->gpDefines);
	mFpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mFpDefinesSensor->attach(&this->fpDefines);

  	mTagSensor = new SoFieldSensor(fieldChangeCB, this);
	mTagSensor->attach(&this->prgTag);

  	SO_NODE_ADD_FIELD(updateShaders, ());

    mUpdateFieldSensor = new SoFieldSensor(updateSensorCB, this);
	mUpdateFieldSensor->attach(&this->updateShaders);
	mAutoUpdateTimerSensor = new SoTimerSensor(autoUpdateCB, this);
	mAutoUpdateTimerSensor->setInterval(1.0/3.0);

    SO_NODE_ADD_FIELD(autoUpdate, (false));

    mAutoUpdateCheckboxSensor = new SoFieldSensor(toggleAutoCB, this);
	mAutoUpdateCheckboxSensor->attach(&this->autoUpdate);

    SO_NODE_ADD_FIELD(shadersUpdated, ());
  	SO_NODE_ADD_FIELD(printToFile, ());
  	SO_NODE_ADD_FIELD(filename,    (""));

  	mFileSensor = new SoFieldSensor(fieldChangeCB, this);
	mFileSensor->attach(&this->printToFile);


    mVsTimeStamps.clear();
    mGsTimeStamps.clear();
    mFsTimeStamps.clear();

    mBatch.clear();
    mBatch.vertShader.source.setType(GL_VERTEX_SHADER);
    mBatch.geomShader.source.setType(GL_GEOMETRY_SHADER_EXT);
    mBatch.fragShader.source.setType(GL_FRAGMENT_SHADER);

    mLines.clear();
    mSLines.clear();
    mHLines.clear();
    mGLines.clear();
    mDefLines.clear();
    mFuncLines.clear();

    mFieldBitmask = 0;
    mNodeId = 0;
    mTimedUpdate = false;
    mIsAutoOn = false;
}

/**
 *	Destructor
 */	
SoXipGLSLComponentProgram::~SoXipGLSLComponentProgram()
{
    ShaderProgramManager * manager = 0;
    if (mBatch.tag != "")
        if (manager = ShaderProgramManager::getInstance())
            manager->removeEntry(mBatch.tag.getString());

    // Delete self
    delete mVpSensor;
	delete mFpSensor;
	delete mGpSensor;
	delete mGpDefinesSensor;
	delete mVpDefinesSensor;
	delete mFpDefinesSensor;
	delete mTagSensor;
	delete mFileSensor;

	delete mUpdateFieldSensor;
	delete mAutoUpdateTimerSensor;
	delete mAutoUpdateCheckboxSensor;
}

void SoXipGLSLComponentProgram::fieldChangeCB(void * data, SoSensor * sensor)
{
    // Accumulate bitmask of manipulated fields
    SoXipGLSLComponentProgram * obj = reinterpret_cast<SoXipGLSLComponentProgram *>(data);
    if      (sensor == obj->mVpSensor)
        obj->mFieldBitmask |= VP_COMPONENTS;
    else if (sensor == obj->mGpSensor)
        obj->mFieldBitmask |= GP_COMPONENTS;
    else if (sensor == obj->mFpSensor)
        obj->mFieldBitmask |= FP_COMPONENTS;
    else if (sensor == obj->mVpDefinesSensor)
        obj->mFieldBitmask |= VP_DEFINES;
    else if (sensor == obj->mGpDefinesSensor)
        obj->mFieldBitmask |= GP_DEFINES;
    else if (sensor == obj->mFpDefinesSensor)
        obj->mFieldBitmask |= FP_DEFINES;
    else if (sensor == obj->mTagSensor)
        obj->mFieldBitmask |= TAG_NAME;
    else if (sensor == obj->mFileSensor)
        obj->mFieldBitmask |= PRINT_TO_FILE;
}

/**	
 *	Initializes the class
 */
void SoXipGLSLComponentProgram::initClass()
{
	SO_NODE_INIT_CLASS(SoXipGLSLComponentProgram, SoNode, "SoNode");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipShaderProgramElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLSLShaderProgramElement);
}

/**
 *  One of two main update functions.
 *  Gets triggered by user interaction.
 *  Can be called both from GLRender or from any other scope.
 */
void SoXipGLSLComponentProgram::UpdateAction()
{
    evaluateProgramBatch(&mBatch);
    mFieldBitmask = 0;
	mTimedUpdate = false;
}

/**
 *  Second out of two main update functions.
 *  Gets triggered by a timer for automatics recompilations.
 *  Can be called both from GLRender or from any other scope.
 */
void SoXipGLSLComponentProgram::AutoUpdateAction()
{
    bool dirty = false;

    dirty |= checkTimeStamps(&mBatch.vertShader, vpComponents, mVsTimeStamps);
    dirty |= checkTimeStamps(&mBatch.geomShader, gpComponents, mGsTimeStamps);
    dirty |= checkTimeStamps(&mBatch.fragShader, fpComponents, mFsTimeStamps);

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
void SoXipGLSLComponentProgram::GLValidityCheck()
{
    bool dirty = false;
    GLint prog = 0;
    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    
    if (!manager)
    {
        dirty = true;
    }
    else
    {
        prog = manager->getProgramHandle(mBatch.tag.getString());
        if (!glIsProgram(prog))
            dirty = true;
    }

    if (dirty)
    {
        mTimedUpdate = true;
        startNotify();
    }
}

bool SoXipGLSLComponentProgram::checkTimeStamps(ShaderBatch * batch, SoMFString& components, std::vector<int>& timevec)
{
    bool dirty = false; 
    int numC = components.getNum();
    int numT = timevec.size();
    const ShaderSourceComponent * entry = 0;
    ShaderComponentLibrary * lib = ShaderComponentLibrary::getInstance();
   
    if (!batch || !lib)
        return false;

    if (numT != numC)
    {
        timevec.clear();
        timevec.reserve(numC);
        timevec.insert(timevec.begin(), numC, 0);
        dirty = true;
    }
    else
    {
        for (int i = 0; i < numC; i++)
        {
            if (entry = lib->getEntry( components[i].getString() ))
            {
                int ts = entry->getTimeStamp();
                int tv = timevec[i];
                if (ts > tv /*&& tv*/)
                {
                    timevec[i] = ts;
                    dirty = true;
                }
            }
        }
    }
    batch->dirtyTimestamp = dirty;
    return dirty;
}


void SoXipGLSLComponentProgram::setTimeStamps(ShaderBatch * batch, SoMFString& components, std::vector<int>& timevec)
{
    int numC = components.getNum();
    int numT = timevec.size();
    const ShaderSourceComponent * entry = 0;
    ShaderComponentLibrary * lib = ShaderComponentLibrary::getInstance();

    if (!batch || !lib)
        return;

    if (numT != numC)
    {
        timevec.clear();
        timevec.reserve(numC);
        timevec.insert(timevec.begin(), numC, 0);
    }

    for (int i = 0; i < numC; i++)
    {
        if (entry = lib->getEntry( components[i].getString() ))
        {
            int ts = entry->getTimeStamp();
            timevec[i] = ts;
        }
    }
    batch->dirtyTimestamp = false;
}


void SoXipGLSLComponentProgram::addDefineLineEntry(const std::string &key, const ShaderSourceComponent::LineEntry &entry)
{
    bool replaced = false;
    DefineLineVec_t::iterator it;
    for (it = mDefLines.begin(); it != mDefLines.end(); it++)
    {
        if (it->first == key)
        {
            it->second = entry;
            replaced = true;
            break;
        }
    }
    if (!replaced)
        mDefLines.push_back(DefineLinePair_t(key, entry));
}


/**
 *	Concatenates all componets into batch->vSource/gSource/fSource.
 */	
bool SoXipGLSLComponentProgram::updateSingleShader(ShaderBatch * batch, SoMFString& components, SoMFString& defines, std::string& errstr)
{
    ShaderComponentLibrary * lib = ShaderComponentLibrary::getInstance();
    const ShaderSourceComponent * entry = 0;

    if (!lib)
        return false;

    int         numRepFuncs = 0;
    std::string strRepFuncs = "";

    int shaderType = batch->source.getType();
    int numD = defines.getNum();

    mSLines.clear();
    mHLines.clear();
    mGLines.clear();
    mFuncLines.clear();

    mDefLines.clear();

    int         numRepDefs = 0;
    std::string strRepDefs = "";

    for (int i = 0; i < components.getNum(); i++)
    {
        // character # is used to temporarily comment out components
        if (components[i].getSubString(0,0) != "#")
        {
            entry = lib->getEntry( components[i].getString() );
            if (entry)
            {
                numRepFuncs = 0;
                strRepFuncs = "";

                numRepDefs = 0;
                strRepDefs = "";


                for (int k = 0; k < entry->getNumDefines(); k++)
                {
                    int r = batch->source.setDefine(entry->getDefineKey(k), entry->getDefineValue(k));
                    if (r)
                    {
                        numRepDefs++;
                        strRepDefs += std::string(entry->getDefineKey(k)) + "|";
                    }

                    std::string errdef = std::string("#define ") + std::string(entry->getDefineKey(k)) + std::string(" ") + std::string(entry->getDefineValue(k));
                    addDefineLineEntry(std::string(entry->getDefineKey(k)),
                                       LineEntry(entry->getNumLinesInDefine(k),
                                                 entry->getLineOffsetInDefine(k),
                                                 entry->getName(), errdef.c_str(),
                                                 entry->getOrigin()));
                }
                if (entry->getNumLinesInSuppHeader())
                {
                    batch->source.addToSuppHeader(entry->getSuppHeader());
                    mSLines.push_back(LineEntry(entry->getNumLinesInSuppHeader(),
                                                entry->getLineOffsetInSuppHeader(),
                                                entry->getName(), "supplementary header",
                                                entry->getOrigin()));
                }
                if (entry->getNumLinesInHeader())
                {
                    batch->source.addToHeader(entry->getHeader());
                    mHLines.push_back(LineEntry(entry->getNumLinesInHeader(),
                                                entry->getLineOffsetInHeader(),
                                                entry->getName(), "header",
                                                entry->getOrigin()));
                }
                if (entry->getNumLinesInGlobal())
                {
                    batch->source.addToGlobal(entry->getGlobal());
                    mGLines.push_back(LineEntry(entry->getNumLinesInGlobal(),
                                                entry->getLineOffsetInGlobal(),
                                                entry->getName(), "global",
                                                entry->getOrigin()));
                }

                for (int k = 0; k < entry->getNumFunctions(); k++)
                {
                    int r = batch->source.setFunction(entry->getFunctionSignature(k), entry->getFunctionBody(k));
                    if (r)
                    {
                        numRepFuncs++;
                        strRepFuncs += std::string(entry->getFunctionSignature(k)) + "|";
                    }
                    mFuncLines[entry->getFunctionSignature(k)] = LineEntry(entry->getNumLinesInFunction(k),
                                                                           entry->getLineOffsetInFunction(k),
                                                                           entry->getName(),
                                                                           entry->getFunctionSignature(k),
                                                                           entry->getOrigin() );
                }

                if (numRepFuncs)
                    SoDebugError::postInfo("GLSL Component Program",
                        "Shader \"%s\" component \"%s\" replaced (%d) functions \"%s\"",
                            batch->source.getName(), components[i].getString(), numRepFuncs, strRepFuncs.c_str());
                if (numRepDefs)
                    SoDebugError::postInfo("GLSL Component Program",
                        "Shader \"%s\" component \"%s\" replaced (%d) defines \"%s\"",
                            batch->source.getName(), components[i].getString(), numRepDefs, strRepDefs.c_str());

				// copy parameters 
                int key, value;
                for(int i = 0; i < entry->numParameters(); ++i)
                {
                    entry->getParameter(i, key, value);
                    batch->source.setParameter(key, value);
                }
            }
            else
            {
                if (mNodeId == 0)
                    SoDebugError::postInfo("GLSL Component Program",
                        "Shader \"%s\" component \"%s\" not found in library on first try",
                            batch->source.getName(), components[i].getString());
                else
                    SoDebugError::postWarning("GLSL Component Program",
                        "Shader \"%s\" component \"%s\" not found in library",
                            batch->source.getName(), components[i].getString());
            }
        }
    }

    if (numD && !(numD == 1 && defines[0] == ""))
    {
        for (int i = 0; i < defines.getNum(); i++)
        {
            std::string line = defines[i].getString();

            int s=0,t=0;
            if (line.compare(0,7,"#define") == 0)
                s = 7;

            s = line.find_first_not_of(" ",s);

            if (s != std::string::npos)
            {
                t = line.find_first_of(" ", s+1);
                std::string key = (t == std::string::npos) ? line.substr(s) : line.substr(s,t-s);
                std::string val = (t == std::string::npos) ? ""             : line.substr(t+1);
                batch->source.setDefine(key.c_str(), val.c_str());
                addDefineLineEntry(key, LineEntry(1,0,"External Defines", line.c_str(),"SoSFString"));
            }
        }
    }

    mGLines.push_back(LineEntry(batch->source.getNumFunctions()+1, 0, "", "Function Prototypes", "C++" ));

	const std::string fullShaderSrcString(batch->source.getFullComponent());

	if(fullShaderSrcString.empty())
		SoDebugError::postWarning(__FUNCTION__, "Src string for shader %s is empty! Make sure to use component tags in src file(s)!", batch->source.getName());

    batch->handle = ShaderEngine::compileShader(fullShaderSrcString, shaderType, errstr);
    batch->timestamp = (batch->handle) ? time(NULL) : 0;

    if (!errstr.empty())
        return false;

    return true;
}


/**
 *	Update single shader.
 */
bool SoXipGLSLComponentProgram::updateSingleProgram(ProgramBatch * batch, std::string& errstr)
{
    if (!batch)
        return false;

    ShaderBatch & geomShader = batch->geomShader;

    ShaderEngine::deleteProgram(batch->handle);


	if(batch->geomShader.handle)
    {
		bool error = false;
		error |= !(batch->geomShader.source.getParamter(GL_GEOMETRY_VERTICES_OUT_EXT, batch->gsNumVertOut ));
		error |= !(batch->geomShader.source.getParamter(GL_GEOMETRY_INPUT_TYPE_EXT, batch->gsPrimTypeIn  ));
		error |= !(batch->geomShader.source.getParamter(GL_GEOMETRY_OUTPUT_TYPE_EXT, batch->gsPrimTypeOut ));

		if(error)
		    SoDebugError::postWarning(__FUNCTION__, "Using Geometry Shader without setting stream in/out options!");
	}
		batch->handle = ShaderEngine::linkShaders(batch->vertShader.handle,
												  batch->fragShader.handle,
												  batch->geomShader.handle,
	  											  batch->gsNumVertOut, 
												  batch->gsPrimTypeIn, 
												  batch->gsPrimTypeOut,
												  errstr);

    int isValid = 0;
    if (glIsProgram(batch->handle))
        glGetProgramiv(batch->handle, GL_VALIDATE_STATUS, &isValid);

    if (!isValid || !errstr.empty())
    {
        if (glIsProgram(batch->handle))
            glDeleteProgram(batch->handle);
        batch->handle = 0;
    }

    batch->timestamp = (batch->handle) ? time(NULL) : 0;

    if (!errstr.empty())
    {
        SoDebugError::post("GLSL Component Program", "\"%s\": %s", batch->tag.getString(), errstr.c_str());
        return false;
    }

    return true;
}




/**
 *	Update existing shader batch by per field comparison.
 */
bool SoXipGLSLComponentProgram::updateShaderBatch(ShaderBatch * batch, SoMFString& components, SoMFString& defines, std::vector<int>& timevec, std::string& errstr)
{
    ShaderComponentLibrary * lib = ShaderComponentLibrary::getInstance();

    if (!batch || !lib)
        return false;

    const ShaderSourceComponent * entry = 0;
    bool dirty = false;
    int shaderType = batch->source.getType();
    int numC = components.getNum();

    dirty |= batch->dirtyTimestamp;

    if (mFieldBitmask)
    {
        switch (shaderType)
        {
        case GL_VERTEX_SHADER :
            dirty |= (mFieldBitmask & (VP_COMPONENTS | VP_DEFINES)) ? true : false;
            break;
        case GL_GEOMETRY_SHADER_EXT :
            dirty |= (mFieldBitmask & (GP_COMPONENTS | GP_DEFINES)) ? true : false;
            break;
        case GL_FRAGMENT_SHADER :
            dirty |= (mFieldBitmask & (FP_COMPONENTS | FP_DEFINES)) ? true : false;
            break;
        default:
            errstr.append("Unknown shader type");
            return false;
        }
    }

    if (dirty)
    {
        ShaderEngine::deleteShader(batch->handle);
        batch->source.clearContent();
        batch->timestamp = 0;
        if (numC && !(numC == 1 && components[0] == ""))
        {
            this->updateSingleShader(batch, components, defines, errstr);
        }
    }

    batch->dirtyTimestamp = false;
    //this->setTimeStamps(batch, components, timevec);

    if (!errstr.empty())
    {
        const char * name = batch->source.getName();
        int posa = errstr.find("(", 0);
        int posb = errstr.find(")", 0);
        //std::string numstr = errstr.substr(posa+1, posb-2);
        std::string numstr = errstr.substr(posa+1, (posb) - (posa+1));
        if (!numstr.empty())
        {
            char bad[] = "n/a";
            char * origin = bad;
            char * component = bad;
            char * part = bad;
            int lineOffset = 0;

            int eline = atoi(numstr.c_str());
            int last = 0;
            int line = 0;

            if (line < eline)
            {
                DefineLineVec_t::const_iterator dit;
                for (dit = mDefLines.begin(); dit != mDefLines.end(); dit++)
                {
                    line += dit->second.len; //+1 for space between funcs
                    if (line >= eline)
                    {
                        component = const_cast<char*>( dit->second.comp.c_str() );
                        part = const_cast<char*>( dit->second.part.c_str() );
                        origin = const_cast<char*>( dit->second.orig.c_str() );
                        lineOffset = dit->second.off-1;
                        break;
                    }
                    last = line;
                }
            }
            if (line < eline)
            {
                std::string fullcomp = batch->source.getFullComponent();
                mLines.clear();
                mLines.reserve(mSLines.size()+mHLines.size()+mGLines.size());
                for (unsigned int i = 0; i < mSLines.size(); i++)
                    mLines.push_back(mSLines[i]);
                for (unsigned int i = 0; i < mHLines.size(); i++)
                    mLines.push_back(mHLines[i]);
                for (unsigned int i = 0; i < mGLines.size(); i++)
                    mLines.push_back(mGLines[i]);
                std::vector<LineEntry>::const_iterator lit;
                for (lit = mLines.begin(); lit != mLines.end(); lit++)
                {
                    line += lit->len;
                    if (line >= eline)
                    {
                        component = const_cast<char*>( lit->comp.c_str() );
                        part = const_cast<char*>( lit->part.c_str() );
                        origin = const_cast<char*>( lit->orig.c_str() );
                        lineOffset = lit->off;
                        break;
                    }
                    last = line;
                }
            }
            if (line < eline)
            {
                FuncLineMap_t::const_iterator fit;
                for (fit = mFuncLines.begin(); fit != mFuncLines.end(); fit++)
                {
                    line += fit->second.len + 1; //+1 for space between funcs
                    if (line >= eline)
                    {
                        component = const_cast<char*>( fit->second.comp.c_str() );
                        part = const_cast<char*>( fit->second.part.c_str() );
                        origin = const_cast<char*>( fit->second.orig.c_str() );
                        lineOffset = fit->second.off-1;
                        break;
                    }
                    last = line;
                }
            }
            if (line >= eline)
            {
                SoDebugError::post("GLSL Component Program", "Error: line %d in \"%s\" (line %d in \"%s\" component \"%s\")",
                    eline-last + lineOffset,
                    origin,
                    eline-last,
                    part,
                    component );
            }
        }

        SoDebugError::post("GLSL Component Program", "\"%s\" : %s", name, errstr.c_str());
    }

    return dirty;
}





/**
 * Update batch entry in ShaderProgramManager singleton.
 * @param batch The shader batch we want to update.
 * @see removeManagerEntry()
 */
void SoXipGLSLComponentProgram::updateManagerEntry(ProgramBatch * batch)
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
            unsigned int returnedHandle = manager->insertEntry(tag, batch->handle, batch->timestamp);

            // Decipher return code
            if (returnedHandle == 0)
            {
                SoDebugError::postWarning("GLSL Component Program",
                    "Manager returned 0 for entry \"%s\", possibly due to invalid program\n", tag);
            }
            else if (returnedHandle != batch->handle)
                SoDebugError::postInfo("Shader Manager", "Shader entry \"%s\" updated (replaced)", tag);
            else
                SoDebugError::postInfo("Shader Manager", "Shader entry \"%s\" updated", tag);
        }
    }
}

/**
 *  Remove entry in ShaderProgramManager singleton.
 *  @param batch The shader batch we want to update.
 *  @see updateManagerEntry()
 */
void SoXipGLSLComponentProgram::removeManagerEntry(ProgramBatch * batch)
{
    if (!batch)
        return;

    const char * tag = batch->tag.getString();

    if (tag && *tag)
    {
        ShaderProgramManager * manager = ShaderProgramManager::getInstance();
        if (manager)
            manager->removeEntry(tag);
    }
}


/**
 *	Compare timestamps in internal list and update if necessary.
 *  Function only executes if no fields have been touched, this way we
 *  avoid costly validation of filenames. No cleaning and synchronizing
 *  need to be done since fields and values are intact.
 */
void SoXipGLSLComponentProgram::evaluateProgramBatch(ProgramBatch * batch)
{
    if (!batch)
        return;

    if (mFieldBitmask & TAG_NAME)
    {
        if (batch->tag != prgTag.getValue())
        {
            if (batch->tag != "")
                removeManagerEntry(batch);
            batch->tag = prgTag.getValue();
            //batch->vertShader.source.setName(std::string(prgTag.getValue().getString())+std::string(" vertex Shader"));
            //batch->geomShader.source.setName(std::string(prgTag.getValue().getString())+std::string(" geometry Shader"));
            //batch->fragShader.source.setName(std::string(prgTag.getValue().getString())+std::string(" fragment Shader"));
            batch->vertShader.source.setName(std::string(prgTag.getValue().getString() + std::string(" vertex Shader")).c_str());
            batch->geomShader.source.setName(std::string(prgTag.getValue().getString() + std::string(" geometry Shader")).c_str());
            batch->fragShader.source.setName(std::string(prgTag.getValue().getString() + std::string(" fragment Shader")).c_str());
        }
    }

    std::string errstr = "";
    std::string errone = "";
    bool dirty = false;   

    dirty |= this->updateShaderBatch(&batch->vertShader, vpComponents, vpDefines, mVsTimeStamps, errone);
    errstr += errone;
    errone = "";

    dirty |= this->updateShaderBatch(&batch->geomShader, gpComponents, gpDefines, mGsTimeStamps, errone);
    errstr += errone;
    errone = "";

    dirty |= this->updateShaderBatch(&batch->fragShader, fpComponents, fpDefines, mFsTimeStamps, errone);
    errstr += errone;
    errone = "";

    if (dirty)
    {
        this->updateSingleProgram(batch, errone);
        if (this->shadersUpdated.isConnected())
            this->shadersUpdated.touch();
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

/**
 *	GLRender.
 *  Binds program 0 after update since we have no idea which shader
 *  the user wants anyway.
 */
void SoXipGLSLComponentProgram::GLRender(SoGLRenderAction *action)
{
    int prevShader = SoXipGLSLShaderProgramElement::get(action->getState());

    if (mFieldBitmask & PRINT_TO_FILE && filename.getValue() != "")
    {
        this->printCurrentSourceToFile();
        mFieldBitmask &= ~PRINT_TO_FILE;
    }

    GLValidityCheck();
    AutoUpdateAction();

    if (mTimedUpdate || mFieldBitmask)
    {
        UpdateAction();
    }

    this->updateLibraryUniforms(action);

    SoXipGLSLShaderProgramElement::set(action->getState(), prevShader);

    mNodeId = getNodeId();
}


void SoXipGLSLComponentProgram::updateSensorCB(void *data, SoSensor *sensor)
{
	// cast editor object
	SoXipGLSLComponentProgram *thisObj = (SoXipGLSLComponentProgram*)data;

    if (sensor == thisObj->mUpdateFieldSensor)
    {
        thisObj->vpComponents.touch();
        thisObj->gpComponents.touch();
        thisObj->fpComponents.touch();
    }
}

void SoXipGLSLComponentProgram::autoUpdateCB(void *data, SoSensor *sensor)
{
	// cast editor object
	SoXipGLSLComponentProgram *thisObj = (SoXipGLSLComponentProgram*)data;
    thisObj->AutoUpdateAction();
}

void SoXipGLSLComponentProgram::toggleAutoCB(void *data, SoSensor *sensor)
{
	// cast editor object
	SoXipGLSLComponentProgram *thisObj = (SoXipGLSLComponentProgram*)data;

    if ((thisObj->mIsAutoOn && !thisObj->autoUpdate.getValue()) ||
        (!thisObj->mIsAutoOn && thisObj->autoUpdate.getValue()))
    {
        thisObj->mIsAutoOn = (thisObj->autoUpdate.getValue()) ? true : false;
        (thisObj->mIsAutoOn) ? thisObj->mAutoUpdateTimerSensor->schedule()
                             : thisObj->mAutoUpdateTimerSensor->unschedule();
    }
}

void SoXipGLSLComponentProgram::printCurrentSourceToFile()
{
    std::ofstream out;
    const char * fname = filename.getValue().getString();

	// Open the shader file
    out.open(fname);
	if (out.fail())
    {
        SoDebugError::postWarning(__FUNCTION__, "Failed to open \"%s\"", fname);
		return;
    }

    out << mBatch.fragShader.source.getFullComponent();
    out.close(); 

    SoDebugError::postInfo("GLSL Component Program",
        "Wrote \"%s\" to \"%s\"", mBatch.fragShader.source.getName(), fname);
}

void SoXipGLSLComponentProgram::updateLibraryUniforms(SoGLRenderAction *action)
{
    ShaderComponentLibrary * lib = ShaderComponentLibrary::getInstance();
    if (!lib)
        return;

    SoMFString * compMF = 0;
    int numC = 0;
    int numU = 0;
    const char * comp;
    const GLSLUniform * uni;
   	GLint loc = -1;

    int prog = SoXipGLSLShaderProgramElement::getProgramID(action->getState(), prgTag.getValue());
    SoXipGLSLShaderProgramElement::set(action->getState(), prog);

    for (int p = 0; p < 3; p ++)
    {
        if (p == 0)
            compMF = &vpComponents;
        else if (p == 1)
            compMF = &gpComponents;
        else if (p == 2)
            compMF = &fpComponents;

        numC = compMF->getNum();
        for (int i = 0; i < numC; i++)
        {
            comp = (*compMF)[i].getString();
            numU = lib->getNumUniforms(comp);
            for (int k = 0; k < numU; k++)
            {
                uni = lib->getUniform(comp, k);
                if (uni && uni->getNumVals())
                {
                    loc = glGetUniformLocation(prog, uni->getName());
                    if (loc > -1)
                    {
                        if (uni->getType() == GLSLUniform::UNIFORM_MAT3)
                            glUniformMatrix3fv(loc, 1, false, uni->getFloatVals());
                        else if (uni->getType() == GLSLUniform::UNIFORM_MAT4)
                            glUniformMatrix4fv(loc, 1, false, uni->getFloatVals());
                        else if (uni->isFloat())
                            glUniform1fv(loc, uni->getNumVals(), uni->getFloatVals());
                        else
                            glUniform1iv(loc, uni->getNumVals(), uni->getIntVals());
                    }
                }
            }
        }
    }
}
