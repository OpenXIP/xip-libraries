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

#include <xip/system/GL/gl.h>
#include "SoXipGLSLPrograms.h"
#include "ShaderProgramManager.h"

#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/SoXipShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>

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
	mGpSensor = new SoFieldSensor(fieldChangeCB, this);
	mGpSensor->attach(&this->gpFilenames);
	mFpSensor = new SoFieldSensor(fieldChangeCB, this);
	mFpSensor->attach(&this->fpFilenames);
	
	mVpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mVpDefinesSensor->attach(&this->vpDefines);
	mGpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mGpDefinesSensor->attach(&this->gpDefines);
	mFpDefinesSensor = new SoFieldSensor(fieldChangeCB, this);
	mFpDefinesSensor->attach(&this->fpDefines);

  	mTagSensor = new SoFieldSensor(fieldChangeCB, this);
	mTagSensor->attach(&this->prgTags);

  	SO_NODE_ADD_FIELD(updateShaders, ());
	mUpdateFieldSensor = new SoFieldSensor(updateSensorCB, this);
	mUpdateFieldSensor->attach(&this->updateShaders);

	mAutoUpdateTimerSensor = new SoTimerSensor(autoUpdateCB, this);
	mAutoUpdateTimerSensor->setInterval(1.0/3.0);

    SO_NODE_ADD_FIELD(autoUpdate, (false));
  	mAutoUpdateCheckboxSensor = new SoFieldSensor(toggleAutoCB, this);
	mAutoUpdateCheckboxSensor->attach(&this->autoUpdate);

    mShaderList = SbPList();
    mFieldBitmask = 0;
    mHasChanged = true;
    mIsAutoOn = false;

	SO_NODE_ADD_FIELD(geometryInputType, (IN_TRIANGLES));
	SO_NODE_ADD_FIELD(geometryOutputType, (OUT_TRIANGLE_STRIP));
	SO_NODE_ADD_FIELD(maxEmittedVertices, (1));

	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_POINTS);
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_LINES);
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_LINES_ADJACENCY_EXT);
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_TRIANGLES);
	SO_NODE_DEFINE_ENUM_VALUE(InGeometry, IN_TRIANGLES_ADJACENCY_EXT);
	SO_NODE_SET_SF_ENUM_TYPE(geometryInputType, InGeometry);


	SO_NODE_DEFINE_ENUM_VALUE(OutGeometry, OUT_POINTS);
	SO_NODE_DEFINE_ENUM_VALUE(OutGeometry, OUT_LINE_STRIP);
	SO_NODE_DEFINE_ENUM_VALUE(OutGeometry, OUT_TRIANGLE_STRIP);
	SO_NODE_DEFINE_ENUM_VALUE(OutGeometry, OUT_TRIANGLES);
    SO_NODE_SET_SF_ENUM_TYPE(geometryOutputType, OutGeometry);
}

/**
 *	Destructor
 */	
SoXipGLSLPrograms::~SoXipGLSLPrograms()
{
    // Delete ShaderprogramManager entry
    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    ShaderBatch * batch = 0;
    for (int i = 0; i < mShaderList.getLength(); i++)
    {
        batch = reinterpret_cast<ShaderBatch *>(mShaderList[i]);
        manager->removeEntry(batch->tag.getString());
        delete batch;
    }

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
        obj->mFieldBitmask |= TAG_NAMES;

	obj->mHasChanged = true;
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
        if (mFieldBitmask) {
	        evaluateByTags();
            cleanAndSynchronize();
            mFieldBitmask = 0;
            //SoDebugError::postInfo("SoXipGLSLPrograms", "shaders updated");
        }
        else
            evaluateByTimestamps();
    }
    else
    {
        SoDebugError::postWarning(__FUNCTION__, "Number of entries in fields do not match, no action taken\n");
        SoDebugError::postInfo(__FUNCTION__, "vpFn %d gpFn %d fpFn %d vpDf %d gpDf %d fpDf %d",
            vpFilenames.getNum(), gpFilenames.getNum(), fpFilenames.getNum(),
            vpDefines.getNum(), gpDefines.getNum(), fpDefines.getNum());
    }

	mHasChanged = false;
}

/**
 *  Second out of two main update functions.
 *  Gets triggered by a timer for automatics recompilations.
 *  Can be called both from GLRender or from any other scope.
 */
void SoXipGLSLPrograms::AutoUpdateAction()
{
    if (!mFieldBitmask)
        evaluateByTimestamps();
}

/**	
 *	Local procedure that takes an input string and an input delimiters string
 *	as inputs and fills up a std::vector with the appropriate tokens from
 *	the input string.
 *	Used to create the preprocessor definitions that are to be added ad the
 *	beginning of the shader programs.
 */
void xip_mshaders_tokenize(const std::string& str,
			  std::vector<std::string>& tokens,
              const std::string& delimiters = " ")
#if 1
{
	// Skip delimiters at the beginning
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first non-delimiter character
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Add a token to the vector of tokens
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next non-delimiter character
		pos = str.find_first_of(delimiters, lastPos);
	}
}
#endif

/**
 *	Delete a specific shader program and its attachments.
 * @param programHandle Shader program to delete
 */	
void SoXipGLSLPrograms::deleteProgram(GLuint programHandle)
{
	// If program handle is valid, delete it
	if (glIsProgram(programHandle))
	{
        // Get attached shaders
        int numShaders;
        glGetProgramiv(programHandle, GL_ATTACHED_SHADERS, &numShaders);
        GLuint * shaders = TCALLOC(numShaders, GLuint);
        glGetAttachedShaders(programHandle, NULL, &numShaders, shaders);

	    // Delete program and shaders
	    glDeleteProgram(programHandle);
        for(int i=0; i<numShaders; i++)
            if (glIsShader(shaders[i]))
                glDeleteShader(shaders[i]);
        free(shaders);
	}
}

/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */	
bool SoXipGLSLPrograms::readShadersFile(const char *filename, const char *defines, GLuint handle)
{
	std::ifstream				in;
	std::string					s, line;
	GLchar						*programString;
	std::vector<std::string>	vDefines;

	// Open the shader file
	in.open(filename);
	if (in.fail())
		return false;

	// Create a vector of preprocessor definitions
	xip_mshaders_tokenize(defines, vDefines);
	std::vector<std::string>::iterator it = vDefines.begin();
	
	// Add the #defines to the source file
	while (it != vDefines.end())
		s += "#define " + *it++ + "\n";
	
	// Append the source code
	while (std::getline(in, line))
		s += line + "\n";
	
	programString = (GLchar *)s.c_str();

	// Set the source code of the shader
	glShaderSource(handle, 1, (const GLchar**) &programString, NULL);
	return true;
}

/**
 *	Compile a GLSL shader program
 */	
GLuint SoXipGLSLPrograms::compileShader(const char	*filename, 
									           const char	*defines,
									           GLenum       type)
{
	GLint status = 0;

	// Create the handle for the shader
	GLuint handle = glCreateShader(type);
	// Read and compile the shader program
	if (readShadersFile(filename, defines, handle))
	{
		glCompileShader(handle);
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	}
	else
	{
		SoDebugError::post("SoXipGLSLPrograms::compileShader", "Shader file \"%s\" could not be opened\n", filename);
        if (mIsAutoOn)
            SoDebugError::postWarning("SoXipGLSLPrograms::updateSingleProgram",
                "Autoupdate suspended, trigger manually to reasume");
		glDeleteShader(handle);
        vpFilenames.touch();
        gpFilenames.touch();
        fpFilenames.touch();
		return 0;
	}

    // Check the compilation status
	if (!status)
	{
		SoDebugError::post("SoXipGLSLPrograms::compileShader", "Shader file \"%s\" could not be compiled\n", filename);
        if (mIsAutoOn)
            SoDebugError::postWarning("SoXipGLSLPrograms::updateSingleProgram",
                "Autoupdate suspended, trigger manually to reasume");
		printShaderLog(handle);
		glDeleteShader(handle);
        vpFilenames.touch();
        gpFilenames.touch();
        fpFilenames.touch();
		return 0;
	}

	return handle;
}

/**
 *	Links GLSL shader programs
 */	
GLuint SoXipGLSLPrograms::linkShaders(GLuint &vpHandle, GLuint &gpHandle, GLuint &fpHandle)
{
	GLint isLinked = 0;

	// Create a GLSL program
	GLuint handle = glCreateProgram();
	// Attach the vertex and fragment shaders to the GLSL program
	if (vpHandle != 0)
		glAttachShader(handle, vpHandle);
	if (fpHandle != 0)
		glAttachShader(handle, fpHandle);
	if (gpHandle != 0){
		glAttachShader(handle, gpHandle);

        //max number of emitted vertices is
		glProgramParameteriEXT(handle,GL_GEOMETRY_VERTICES_OUT_EXT,maxEmittedVertices.getValue());
	     //input geometry type
		glProgramParameteriEXT(handle,GL_GEOMETRY_INPUT_TYPE_EXT,geometryInputType.getValue());
	    //output geometry type
	    glProgramParameteriEXT(handle,GL_GEOMETRY_OUTPUT_TYPE_EXT,geometryOutputType.getValue());
	}

	// Link the shaders
	glLinkProgram(handle);

	// Check the link status
	glGetProgramiv(handle, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		SoDebugError::post("SoXipGLSLPrograms::linkShaders", "Program could not be linked\n");
		printProgramLog(handle);
		deleteProgram(handle);
        handle = 0;
        vpHandle = 0;
        gpHandle = 0;
        fpHandle = 0;
        vpFilenames.touch();
        gpFilenames.touch();
        fpFilenames.touch();
        if (mIsAutoOn)
            SoDebugError::postWarning("SoXipGLSLPrograms::updateSingleProgram",
                "Autoupdate suspended, trigger manually to reasume");
	}
	return handle;
}

/**
 *	Print a log when compiling a shader fails 
 */	
void SoXipGLSLPrograms::printShaderLog(GLuint shader)
{
	GLint length = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		GLchar *info = new GLchar[length + 1];
		glGetShaderInfoLog(shader, length, NULL, info);
		info[length] = 0;
		SoError::post(info);
		delete[] info;
	}
}

/**
 *	Print a log when linking shaders fails 
 */	
void SoXipGLSLPrograms::printProgramLog(GLuint program)
{
	GLint length = 0;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		GLchar *info = new GLchar[length + 1];
		glGetProgramInfoLog(program, length, NULL, info);
		info[length] = 0;
		SoError::post(info);
		delete[] info;
	}
}

/**
 *	Update single shader.
 */
void SoXipGLSLPrograms::updateSingleShader(ShaderBatch * batch, GLenum shaderType)
{
    if (shaderType == GL_VERTEX_SHADER)
    {
        if (glIsShader(batch->vpHandle))
            glDeleteShader(batch->vpHandle);
        if (batch->vpFilename != "") {
            batch->vpHandle = compileShader(batch->vpFilename.getString(), batch->vpDefines.getString(), GL_VERTEX_SHADER);
            struct stat filestat = { 0 };
            int returncode = (batch->vpHandle) ? stat(batch->vpFilename.getString(), &filestat) : -1;
            batch->vpTimestamp = (returncode == 0) ? filestat.st_mtime : 0;
            //SoDebugError::postInfo("SoXipGLSLPrograms::updateSingleShader", "vp %d (%d) return %d", batch->vpHandle, batch->vpTimestamp, returncode);
        }
    }
    else if (shaderType == GL_GEOMETRY_SHADER_EXT)
    {
        if (glIsShader(batch->gpHandle))
            glDeleteShader(batch->gpHandle);
        if (batch->gpFilename != "") {
            batch->gpHandle = compileShader(batch->gpFilename.getString(), batch->gpDefines.getString(), GL_GEOMETRY_SHADER_EXT);
            struct stat filestat = { 0 };
            int returncode = (batch->gpHandle) ? stat(batch->gpFilename.getString(), &filestat) : -1;
            batch->gpTimestamp = (returncode == 0) ? filestat.st_mtime : 0;
            //SoDebugError::postInfo("SoXipGLSLPrograms::updateSingleShader", "gp %d (%d) return %d", batch->gpHandle, batch->gpTimestamp, returncode);
        }
    }
    else if (shaderType == GL_FRAGMENT_SHADER)
    {
        if (glIsShader(batch->fpHandle))
            glDeleteShader(batch->fpHandle);
        if (batch->fpFilename != "") {
            batch->fpHandle = compileShader(batch->fpFilename.getString(), batch->fpDefines.getString(), GL_FRAGMENT_SHADER);
            struct stat filestat = { 0 };
            int returncode = (batch->fpHandle) ? stat(batch->fpFilename.getString(), &filestat) : -1;
            batch->fpTimestamp = (returncode == 0) ? filestat.st_mtime : 0;
            //SoDebugError::postInfo("SoXipGLSLPrograms::updateSingleShader", "fp %d (%d) return %d", batch->fpHandle, batch->fpTimestamp, returncode);
        }
    }
    else
        SoDebugError::post("SoXipGLSLPrograms::updateSingleShader", "Unknown shader type\n");
}

/**
 *	Update single shader.
 */
void SoXipGLSLPrograms::updateSingleProgram(ShaderBatch * batch)
{
    // If handle exists then release the program
    GLuint oldP = batch->prgHandle;
    if (glIsProgram(batch->prgHandle))
        glDeleteProgram(batch->prgHandle);
    // Set flags
    batch->prgHandle    = linkShaders(batch->vpHandle, batch->gpHandle, batch->fpHandle);
    batch->prgTimestamp = (batch->prgHandle) ? time(NULL) : 0;
#if 0
/////
// This functionality has been changed so that "confirmedActive" is true even if compilation went wrong
// That way the internal list will reflect the field values in a more optimiced way. The cost beeing an
// entry in the manager with program 0.
/////

    batch->confirmedActive = (batch->prgHandle) ? true : false;
#endif
    if (!batch->prgHandle)
    {
        // Touch handle to avoid multiple error in auto mode
        SoDebugError::postWarning("SoXipGLSLPrograms::updateSingleProgram",
            "Updating program \"%s\" failed, handle set to 0\n", batch->tag.getString());
    }
}

/**
 *	Update existing shader batch by per field comparison.
 */
void SoXipGLSLPrograms::updateShaderBatchByFields(ShaderBatch * batch, int field)
{
    bool vDirty    = false;
    bool gDirty    = false;
    bool fDirty    = false;

    // Only compare manipulated fields and update if changed
    if ((mFieldBitmask & VP_FILENAMES) || (mFieldBitmask & VP_DEFINES)) {
        if (batch->vpFilename != vpFilenames[field] ||
            batch->vpDefines  != vpDefines[field]   ||
            (batch->vpHandle == 0 && batch->vpFilename != ""))
        {
            batch->vpFilename = vpFilenames[field];
            batch->vpDefines  = vpDefines[field];
            updateSingleShader(batch, GL_VERTEX_SHADER);
            vDirty = true;
        }
    }
    if ((mFieldBitmask & GP_FILENAMES) || (mFieldBitmask & GP_DEFINES)) {
        if (batch->gpFilename != gpFilenames[field] ||
            batch->gpDefines  != gpDefines[field]   ||
            (batch->gpHandle == 0 && batch->gpFilename != ""))
        {
            batch->gpFilename = gpFilenames[field];
            batch->gpDefines  = gpDefines[field];
            updateSingleShader(batch, GL_GEOMETRY_SHADER_EXT);
            gDirty = true;
        }
    }
    if ((mFieldBitmask & FP_FILENAMES) || (mFieldBitmask & FP_DEFINES)) {
        if (batch->fpFilename != fpFilenames[field] ||
            batch->fpDefines  != fpDefines[field]   ||
            (batch->fpHandle == 0 && batch->fpFilename != ""))
        {
            batch->fpFilename = fpFilenames[field];
            batch->fpDefines  = fpDefines[field];
            updateSingleShader(batch, GL_FRAGMENT_SHADER);
            fDirty = true;
        }
    }

    // Have we changed anything in this batch?
    if (vDirty || gDirty || fDirty) {
        updateSingleProgram(batch);
        batch->isDirty = true;
    }
}

/**
 *	Update existing shader batch by per field comparison.
 */
void SoXipGLSLPrograms::updateShaderBatchByTimestamp(ShaderBatch * batch)
{
  struct stat filestat = { 0 };
    int returncode;

    // Get time on disk, setting the code to 0 if no existing program means we down have to bother about validity
    returncode = (batch->vpHandle) ? stat(batch->vpFilename.getString(), &filestat) : 0;
    int vTimeOnDrive = (returncode == 0) ? filestat.st_mtime : 0;
    returncode = (batch->gpHandle) ? stat(batch->gpFilename.getString(), &filestat) : 0;
    int gTimeOnDrive = (returncode == 0) ? filestat.st_mtime : 0;
    returncode = (batch->fpHandle) ? stat(batch->fpFilename.getString(), &filestat) : 0;
    int fTimeOnDrive = (returncode == 0) ? filestat.st_mtime : 0;

    bool vDirty = false;
    bool gDirty = false;
    bool fDirty = false;

    // Only compare manipulated fields (manipulation of tag field causes full evaluation)
    if (batch->vpTimestamp < vTimeOnDrive && batch->vpTimestamp != 0) {
        //SoDebugError::postInfo("Update by stamp", "Timestamp %d OnDrive %d\n", batch->vpTimestamp, vTimeOnDrive);
        updateSingleShader(batch, GL_VERTEX_SHADER);
        vDirty = true;
    }
    if (batch->gpTimestamp < gTimeOnDrive && batch->gpTimestamp != 0) {
        //SoDebugError::postInfo("Update by stamp", "Timestamp %d OnDrive %d\n", batch->gpTimestamp, gTimeOnDrive);
        updateSingleShader(batch, GL_GEOMETRY_SHADER_EXT);
        gDirty = true;
    }
    if (batch->fpTimestamp < fTimeOnDrive && batch->fpTimestamp != 0) {
        //SoDebugError::postInfo("Update by stamp", "Timestamp %d OnDrive %d\n", batch->fpTimestamp, fTimeOnDrive);
        updateSingleShader(batch, GL_FRAGMENT_SHADER);
        fDirty = true;
    }

#if 0
/////
// For debugging timestamp issues
/////

    SoDebugError::postInfo("SoXipGLSLPrograms", "vp %d (%d %d) gp %d (%d %d) fp %d (%d %d)",
        batch->vpHandle, batch->vpTimestamp, vTimeOnDrive,
        batch->gpHandle, batch->gpTimestamp, gTimeOnDrive,
        batch->fpHandle, batch->fpTimestamp, fTimeOnDrive);
#endif

    // Have we changed anything in this batch?
    if (vDirty || gDirty || fDirty) {
        updateSingleProgram(batch);
        batch->isDirty = true;
    }
}

/**
 * Update batch entry in ShaderProgramManager singleton.
 * @param batch The shader batch we want to update.
 * @see removeManagerEntry()
 */
void SoXipGLSLPrograms::updateManagerEntry(ShaderBatch * batch)
{
    // Insert entry
    if (batch->tag != "")
    {
        // Get manager instance
        ShaderProgramManager * manager = ShaderProgramManager::getInstance();
        unsigned int returnedHandle = manager->insertEntry(batch->tag.getString(), batch->prgHandle, 0);

        // Decipher return code
        if (returnedHandle == 0) {
            SoDebugError::postWarning("SoXipGLSLPrograms::updateManagerEntry",
                "Returned value 0, possibly due to issue with tag\n");
        }
        else if (returnedHandle != batch->prgHandle) {
            SoDebugError::postInfo("Shader Manager", "Shader entry updated (replaced)");
            //SoDebugError::postInfo("Shader Manager", "\"%s\" entry updated (replaced %d with %d)",
            //    batch->tag.getString(), returnedHandle, batch->prgHandle);
#if 0
/////
// This should already have been taken care of (when cleaning the internal list) and there is
// actually a chance that we would try to delete a shader that has already been deleted.
// The double deletion could be prevented by a validity check by what if the freed handle has
// been used anew with a totaly diffenrent shader? Then we would probably end up deleting a
// shader we do not want to delete!
// Is there any automatic way to prevent this without introducing member variables to hold old handles?
//
// See DevDoc for updated discussion!
/////

            glDeleteProgram(returnedHandle);
#endif
        }
    }
    mIsManagerUpdated = true;
}

/**
 *  Remove entry in ShaderProgramManager singleton.
 *  @param batch The shader batch we want to update.
 *  @see updateManagerEntry()
 */
void SoXipGLSLPrograms::removeManagerEntry(ShaderBatch * batch)
{
    if (batch)
    {
        // Get manager instance
        ShaderProgramManager * manager = ShaderProgramManager::getInstance();
#if 0
/////
// Need more checks here?
// What if program already released?
// What if shader handles attached to program have been released
// and then used anew by different program?
// It seems we have to restrict the deletion to the node that creates
// entry (we do not know this if using the returned handle)
//
// See DevDoc for updated discussion!
/////

        GLuint handle = manager->getProgramHandle(batch->tag.getString());
        if (handle)
            glDeleteProgram(handle);
#endif
        manager->removeEntry(batch->tag.getString());
    }
    mIsManagerUpdated = true;
}

/**
 *	Compare tags in field and internal list, process divergence.
 *  When stepping through tag field we have several cases:
 *      1: Tag exists and is equal to internal list.
 *          Perform update (since at least one field has been manipulated)
 *      2: Tag exists but do not match internal list.
 *          Remove previous tag from manager.
 *          Update tag in existing batch.
 *          Perform update
 *      3: Internal list is to short.
 *          Append new batch
 *          Set tag according to field
 *          Perform update
 *  Case 1 and 2 are only checked if tag fields has been touched,
 *  if not then a regular update is performed.
 *  All encountered entries are marked active as to not be deleted
 *  by the clear function.
 */
void SoXipGLSLPrograms::evaluateByTags()
{
    ShaderBatch * batch = 0;

    // Force internal list to reflect fields if tag field has changed
    for (int i = 0; i < prgTags.getNum(); i++)
    {
        bool extending = false;
        if (mShaderList.getLength() <= i) {
            mShaderList.append(new ShaderBatch);
            extending = true;
        }
        batch = reinterpret_cast<ShaderBatch *>(mShaderList[i]);
        if (batch) {
            if (mFieldBitmask & TAG_NAMES || extending) {
                if (batch->tag != prgTags[i]) {
                    removeManagerEntry(batch);
                    batch->tag = prgTags[i];
                    batch->isDirty = true;
                }
            }
            batch->confirmedActive = true;
            updateShaderBatchByFields(batch, i);
        }
        else
            SoDebugError::post("SoXipGLSLPrograms::compareByTags", "Empty slot found, this should not happen!\n");
    }
}

/**
 *	Compare timestamps in internal list and update if necessary.
 *  Function only executes if no fields have been touched, this way we
 *  avoid costly validation of filenames. No cleaning and synchronizing
 *  need to be done since fields and values are intact.
 */
void SoXipGLSLPrograms::evaluateByTimestamps()
{
    ShaderBatch * batch = 0;

    // Evaluate internal list
    for (int i = 0; i < mShaderList.getLength(); i++)
    {
        batch = reinterpret_cast<ShaderBatch *>(mShaderList[i]);
        if (batch) {
            // Recompile shaders if timestamp is old
            updateShaderBatchByTimestamp(batch);

			if (batch->isDirty)
			{
				// Since program id might have changed we need to update the manager as well
				updateManagerEntry(batch);
				batch->isDirty = false;
			}
        }
    }

    // If manager has been updated we post a redisplay event to force Useprogram nodes into action
    if (mIsManagerUpdated) {
        startNotify();
        mIsManagerUpdated = false;
    }
}

/**
 *  Clean internal list and sync with ShaderProgramManager.
 *  The confirmedActive flag is used to determine what entries in our
 *  internal list that have gone obsolete (this might happen if we change
 *  a tag or remove field entries)
 */
 void SoXipGLSLPrograms::cleanAndSynchronize()
{
    ShaderBatch * batch = 0;

    // Clean internal list and sync with manager
    for (int i = 0; i < mShaderList.getLength(); i++)
    {
        batch = reinterpret_cast<ShaderBatch *>(mShaderList[i]);
        // Update if dirty
        if (batch->isDirty)
        {
            updateManagerEntry(batch);
            batch->isDirty = false;
        }
        if (! batch->confirmedActive) {
#if 1
/////
// We can probably do this in a safe way here as the entry and batch
// both have been valid up to here but now are discarded.
//
// See DevDoc for updated discussion!
/////
            
            deleteProgram(batch->prgHandle);
            batch->prgHandle = 0;
            batch->vpHandle = 0;
            batch->gpHandle = 0;
            batch->fpHandle = 0;
#endif
            removeManagerEntry(batch);
#if 1
/////
// We can remove the obsolete entry since even those entries that
// did not compile still counts as valid (even though they have
// their program handle set to 0)
//
// See DevDoc for updated discussion!
/////

            delete batch;
            mShaderList.remove(i);
#endif
        }
        else
            batch->confirmedActive = false;
    }

    // If manager has been updated we post a redisplay event
    if (mIsManagerUpdated) {
        startNotify();
        mIsManagerUpdated = false;
    }

#if 0
/////
// DEBUG ONLY
// The implementation of manager->getAllTagsAsOneString() can resault in
// memory corruption if called from a seperate .dll
// USE FOR SPECIFIC DEBUG ONLY
// Anyone have a better idea how to get the names as a string?
/////

    // Get manager instance
    ShaderProgramManager * manager = ShaderProgramManager::getInstance();
    // Print list of avaliable tags
    char * taglist = manager->getAllTagsAsOneString();
    SoDebugError::postInfo("Taglist", taglist);
    free(taglist);
    taglist = 0;
#endif
#if 0
/////
// DEBUG ONLY
// Nice to have if we want to compare the internal list with the one from
// the manager.
/////

    // Print internal list
    printInternalTagsAsOneString();
#endif
}

/**
 *	Debug function printing a copy of the internal list including handles.
 */
void SoXipGLSLPrograms::printInternalTagsAsOneString()
{
    ShaderBatch * batch = 0;
    for (int i = 0; i < mShaderList.getLength(); i++)
    {
        batch = reinterpret_cast<ShaderBatch *>(mShaderList[i]);
        if (batch)
            SoDebugError::postInfo("", "Internal shader %d %s   (id %d, vp %d, gp %d, fp %d)", i, batch->tag.getString(), batch->prgHandle,
            batch->vpHandle, batch->gpHandle, batch->fpHandle);
    }
}

/**
 *	GLRender.
 *  Binds program 0 after update since we have no idea which shader
 *  the user wants anyway.
 */
void SoXipGLSLPrograms::GLRender(SoGLRenderAction *action)
{
	if (mHasChanged)
	{
        UpdateAction();
        SoXipGLSLShaderProgramElement::set(action->getState(), 0);
	}
}


void SoXipGLSLPrograms::updateSensorCB(void *data, SoSensor *sensor)
{
	// cast editor object
	SoXipGLSLPrograms *thisObj = (SoXipGLSLPrograms*)data;
	//thisObj->UpdateAction();
    thisObj->mHasChanged = true;
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
