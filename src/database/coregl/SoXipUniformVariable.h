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
 *	Node classes for setting uniform variables
 *	in GLSL shader programs
 */


#ifndef _SO_XIP_UNIFORM_VARIABLE_H_
#define _SO_XIP_UNIFORM_VARIABLE_H_

#include <Inventor/errors/SoErrors.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <xip/system/GL/gl.h>

#if !defined(WINDOWS) && !defined(_WIN32)
#include <X11/Xmd.h>
#endif

/**
 *	Node class for setting uniform variables
 *	in GLSL shader programs
 */
class SoXipUniformVariable : public SoNode
{ 
	SO_NODE_HEADER( SoXipUniformVariable );  
public:
	/**
	 *	Field for the name of the variable
	 */
	SoSFString		name;
	/**
	 *	Constructor
	 */
	SoXipUniformVariable(); 
	/**	
	 *	Initializes the class
	 */
	static void initClass();
protected:
	/**	
	 *	GLRender
	 */
	virtual void GLRender(SoGLRenderAction *action);
	/**	
	 *	Get the location of a variable in order to modify its value
	 */
	GLint getLocation();
	/**	
	 *	Set the current value to the variable
	 */	
	void	doAction(SoAction *action);
	/**	
	 *	Shader program handle (Id)
	 */
	GLint programHandle;
	/**
	 *	Destructor
	 */	
	virtual ~SoXipUniformVariable();
	/**
	 *	Cached version of variable name
	 */	
	SbString	mName;
	/**
	 *	Boolean that tells getLocation() if it should display the error
	 */
	BOOL		mDisplayError;
};

/**
 *	Node class for setting float uniform variables
 *	in GLSL shader programs
 */
class  SoXipUniformFloat : public SoXipUniformVariable
{ 
	SO_NODE_HEADER( SoXipUniformFloat );  
public:
	SoMFFloat value;
	/**
	 *	Constructor
	 */
	SoXipUniformFloat(); 
	static void initClass();
protected:
	/**	
	 *	Set the current value to the variable
	 */		
	virtual void doAction(SoAction *action);
private:
};

/**
 *	Node class for setting Vec2f (vector of 2 floats) uniform variables
 *	in GLSL shader programs
 */
class  SoXipUniformVec2f : public SoXipUniformVariable
{ 
	SO_NODE_HEADER( SoXipUniformVec2f );  
public:
	SoSFVec2f value;
	/**
	 *	Constructor
	 */
	SoXipUniformVec2f(); 
	static void initClass();
protected:
	/**	
	 *	Set the current value to the variable
	 */	
	virtual void doAction(SoAction *action);
private:
};

/**
 *	Node class for setting Vec3f (vector of 3 floats) uniform variables
 *	in GLSL shader programs
 */
class  SoXipUniformVec3f : public SoXipUniformVariable
{ 
	SO_NODE_HEADER( SoXipUniformVec3f );  
public:
	SoSFVec3f value;
	/**
	 *	Constructor
	 */
	SoXipUniformVec3f(); 
	static void initClass();
protected:
	/**	
	 *	Set the current value to the variable
	 */		
	virtual void doAction(SoAction *action);
private:
};

/**
 *	Node class for setting Vec4f (vector of 4 floats) uniform variables
 *	in GLSL shader programs
 */
class  SoXipUniformVec4f : public SoXipUniformVariable
{ 
	SO_NODE_HEADER( SoXipUniformVec4f );  
public:
	SoSFVec4f value;
	/**
	 *	Constructor
	 */
	SoXipUniformVec4f(); 
	static void initClass();
protected:
	/**	
	 *	Set the current value to the variable
	 */		
	virtual void doAction(SoAction *action);
private:
};

/**
 *	Node class for setting Integer uniform variables
 *	in GLSL shader programs
 */
class  SoXipUniformInt : public SoXipUniformVariable
{ 
	SO_NODE_HEADER( SoXipUniformInt );  
public:
	SoMFInt32 value;
	/**
	 *	Constructor
	 */
	SoXipUniformInt(); 
	static void initClass();
protected:
	/**	
	 *	Set the current value to the variable
	 */		
	virtual void doAction(SoAction *action);
private:
};

/**
 *	Node class for setting mat4 (matrix 4*4) uniform variables
 *	in GLSL shader programs
 */
class  SoXipUniformMatrix4 : public SoXipUniformVariable
{ 
	SO_NODE_HEADER( SoXipUniformMatrix4 );  
public:
	SoSFMatrix value;
	/**
	 *	Constructor
	 */
	SoXipUniformMatrix4(); 
	static void initClass();
protected:
	/**	
	 *	Set the current value to the variable
	 */		
	virtual void doAction(SoAction *action);
private:
};

/**
 *	Node class for setting mat3 (matrix 3*3) uniform variables
 *	in GLSL shader programs
 */
class  SoXipUniformMatrix3 : public SoXipUniformVariable
{ 
	SO_NODE_HEADER( SoXipUniformMatrix3 );  
public:
	SoMFFloat value;
	/**
	 *	Constructor
	 */
	SoXipUniformMatrix3(); 
	static void initClass();
protected:
	/**	
	 *	Set the current value to the variable
	 */		
	virtual void doAction(SoAction *action);
private:
};

#endif //_SO_XIP_UNIFORM_VARIABLE_H_


