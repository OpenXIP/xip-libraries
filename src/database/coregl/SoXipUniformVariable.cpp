/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
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

#include "SoXipUniformVariable.h"
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include <xip/system/GL/glext.h>


SO_NODE_SOURCE(SoXipUniformVariable);

/**
 *	 Implementation of base class SoXipUniformVariable
 */
void SoXipUniformVariable::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformVariable,SoNode,"Node");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement );
	SO_ENABLE( SoGLRenderAction, SoXipGLSLShaderProgramElement );
}

void SoXipUniformVariable::GLRender(SoGLRenderAction* action)
{
	if (mName != name.getValue())
	{
		mDisplayError = TRUE;
		mName = name.getValue();
	}
	doAction(action);
}

/**
 *	Constructor
 */
SoXipUniformVariable::SoXipUniformVariable()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformVariable);
	SO_NODE_ADD_FIELD(name,(""));
	programHandle = 0;
	mDisplayError = TRUE;
	mName = SbString("");
}

SoXipUniformVariable::~SoXipUniformVariable()
{

}

/**
 *	getLocation : return the location of a uniform variable
 *	in a shader program so that its value can be modified
 */
GLint SoXipUniformVariable::getLocation()
{
	GLhandleARB	programObject = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
#ifdef DARWIN
	GLint		loc	= glGetUniformLocationARB(programObject,  name.getValue().getString());
#else
	GLint		loc	= glGetUniformLocation(programObject,  name.getValue().getString());
#endif /* DARWIN */
	
	if (loc == -1 && mDisplayError)
	{
		SoDebugError::postInfo("SoXipUniformVariable::getLocation", "Unknown uniform variable: %s", name.getValue().getString());
		mDisplayError = FALSE;
	}
	return loc;
}

void SoXipUniformVariable::doAction(SoAction *action)
{

}

/**
 *	 Implementation of derived class SoXipUniformFloat
 */
SO_NODE_SOURCE(SoXipUniformFloat);

void SoXipUniformFloat::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformFloat,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformFloat::SoXipUniformFloat()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformFloat);
	SO_NODE_ADD_FIELD(value,(0.0));
}

void SoXipUniformFloat::doAction(SoAction *action)
{
//	programHandle = SoXipGLSLShaderProgramElement::get(action->getState());
	glUniform1fv(getLocation(), value.getNum(), value.getValues(0));
}

/**
 *	 Implementation of derived class SoXipUniformVec2f
 */
SO_NODE_SOURCE(SoXipUniformVec2f);

void SoXipUniformVec2f::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformVec2f,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformVec2f::SoXipUniformVec2f()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformVec2f);
	SO_NODE_ADD_FIELD(value,(0.0,0.0));
}

void SoXipUniformVec2f::doAction(SoAction *action)
{
	float x,y;
	value.getValue().getValue(x,y);
	glUniform2f(getLocation(), x,y);
}

/**
 *	 Implementation of derived class SoXipUniformVec3f
 */
SO_NODE_SOURCE(SoXipUniformVec3f);

void SoXipUniformVec3f::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformVec3f,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformVec3f::SoXipUniformVec3f()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformVec3f);
	SO_NODE_ADD_FIELD(value,(0.0,0.0,0.0));
}

void SoXipUniformVec3f::doAction(SoAction *action)
{
	float x,y,z;
	value.getValue().getValue(x,y,z);
	glUniform3f(getLocation(), x,y,z);
}

/**
 *	 Implementation of derived class SoXipUniformVec4f
 */
SO_NODE_SOURCE(SoXipUniformVec4f);

void SoXipUniformVec4f::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformVec4f,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformVec4f::SoXipUniformVec4f()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformVec4f);
	SO_NODE_ADD_FIELD(value,(0.0,0.0,0.0,0.0));
}

void SoXipUniformVec4f::doAction(SoAction *action)
{
	float x,y,z,w;
	value.getValue().getValue(x,y,z,w);
	glUniform4f(getLocation(), x,y,z,w);
}

/**
 *	 Implementation of derived class SoXipUniformInt
 */
SO_NODE_SOURCE(SoXipUniformInt);

void SoXipUniformInt::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformInt,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformInt::SoXipUniformInt()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformInt);
	SO_NODE_ADD_FIELD(value,(0));
}

void SoXipUniformInt::doAction(SoAction *action)
{
	glUniform1iv(getLocation(), value.getNum(), value.getValues(0));
}

/**
 *	 Implementation of derived class SoXipUniformMatrix4
 */
SO_NODE_SOURCE(SoXipUniformMatrix4);

void SoXipUniformMatrix4::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformMatrix4,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformMatrix4::SoXipUniformMatrix4()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformMatrix4);
	SO_NODE_ADD_FIELD(value,(SbMatrix::identity()));
}

void SoXipUniformMatrix4::doAction(SoAction *action)
{
	SbMatrix m = value.getValue();
    glUniformMatrix4fv(getLocation(),1, false, (float*)m);
}

/**
 *	 Implementation of derived class SoXipUniformMatrix3
 */
SO_NODE_SOURCE(SoXipUniformMatrix3);

void SoXipUniformMatrix3::initClass()
{
	SO_NODE_INIT_CLASS(SoXipUniformMatrix3, SoXipUniformVariable, "SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformMatrix3::SoXipUniformMatrix3()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformMatrix3);
	SO_NODE_ADD_FIELD(value, (0));
}

void SoXipUniformMatrix3::doAction(SoAction *action)
{
	int num = value.getNum();
	if (num == 9) {
		glUniformMatrix3fv(getLocation(), 1 ,false, value.getValues(0));
	}
	else {
		SoDebugError::postInfo(__FUNCTION__, "Requires 9 floats");
	}
}
