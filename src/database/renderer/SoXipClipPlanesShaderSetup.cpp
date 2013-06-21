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

/*
  Scope:

  This component is intended to extract the current VR Clip Planes and
  pass them on to a shader program and/or output them to a buffer to
  be stored into a texture.
*/

/*
  Implementation Notes:

*/

#include <xip/inventor/coregl/SoXipGlowElement.h>

#include "SoXipClipPlanesShaderSetup.h"

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/SbLinear.h>

#include <xip/inventor/core/SoXipClipPlaneElement.h>

#include <stdio.h>
#include <stdlib.h>


/*
  Note: #define min and max should be MIN and MAX!!!
*/

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

template <class type_t>
inline type_t min(type_t a, type_t b)
{
    return a < b ? a : b;
}

template <class type_t>
inline type_t max(type_t a, type_t b)
{
    return a > b ? a : b;
}


// Output OpenGL Error, if any...
#if 1
#if 0
inline void CheckGLError()
{
    GLenum err = glGetError(); 

    if (err != GL_NO_ERROR)
	{ 
	SoError::post((char*)gluErrorString(err));
    } 
}
#else
inline void CheckGLError() { }
#endif
#endif


SO_NODE_SOURCE(SoXipClipPlanesShaderSetup);

SoXipClipPlanesShaderSetup::SoXipClipPlanesShaderSetup()
{
    SO_NODE_CONSTRUCTOR(SoXipClipPlanesShaderSetup);

    SO_NODE_ADD_FIELD(mUniformName, (SbString("xipVRClipPlanes")));
    SO_NODE_ADD_FIELD(mUniformNumName, (SbString("xipNumVRClipPlanes")));
    SO_NODE_ADD_FIELD(mUniformMaxName, (SbString("xipMaxVRClipPlanes")));
    SO_NODE_ADD_FIELD(mMaxClipPlanes, (uint32_t(16)));

    mClipPlaneCache = 0;
    mClipPlaneCacheSize = 0;
}

SoXipClipPlanesShaderSetup::~SoXipClipPlanesShaderSetup()
{
    delete mClipPlaneCache;

    mClipPlaneCache = 0;
    mClipPlaneCacheSize = 0;
}


void SoXipClipPlanesShaderSetup::initClass()
{
    SO_NODE_INIT_CLASS(SoXipClipPlanesShaderSetup, SoNode, "Node");
    SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
    SO_ENABLE(SoGLRenderAction, SoXipClipPlaneElement );
}


/*
  ------------------------------------------------------------------------
    virtual GLRender()

    Extract clip planes and setup the Shader Uniforms
  ------------------------------------------------------------------------
*/

void SoXipClipPlanesShaderSetup::GLRender(SoGLRenderAction * action)
{
    SoState * state = action->getState();

    if (!state) return;

    GLint prog = 0;

    glGetIntegerv(GL_CURRENT_PROGRAM, &prog);

    const char * clipsName = mUniformName.getValue().getString();
    const char * clipsNumName = mUniformNumName.getValue().getString();
    const char * clipsMaxName = mUniformMaxName.getValue().getString();

    int clipsLoc = -1;
    int clipsNumLoc = -1;
    int clipsMaxLoc = -1;

    if (clipsName && clipsName[0])
    {
	clipsLoc = glGetUniformLocation(prog, clipsName);
#if 0
	if (clipsLoc < 0)
	{
	     SoDebugError::postInfo("SoXipClipPlanesShaderSetup::GLRender",
				    "Clip Planes Array Uniform not found: %s",
				    clipsName);
	}
#endif
    }

    if (clipsNumName && clipsNumName[0])
    {
	clipsNumLoc = glGetUniformLocation(prog, clipsNumName);
#if 0
	if (clipsNumLoc < 0)
	{
	     SoDebugError::postInfo("SoXipClipPlanesShaderSetup::GLRender",
				    "Clip Planes Num Uniform not found: %s",
				    clipsNumName);
	}
#endif
    }

    if (clipsMaxName && clipsMaxName[0])
    {
	clipsMaxLoc = glGetUniformLocation(prog, clipsMaxName);
#if 0
	if (clipsMaxLoc < 0)
	{
	     SoDebugError::postInfo("SoXipClipPlanesShaderSetup::GLRender",
				    "Clip Planes Max Uniform not found: %s",
				    clipsMaxName);
	}
#endif
    }

    const SoXipClipPlaneElement * clipPlaneElt =
	SoXipClipPlaneElement::getInstance(state);

    int numPlanes = 0;
    int maxPlanes = mMaxClipPlanes.getValue();

    if (clipPlaneElt)
    {
	numPlanes = min(clipPlaneElt->getNum(), maxPlanes);		
    }

    /*
      Increase Clip Plane Cache if needed
    */
    if (numPlanes > mClipPlaneCacheSize)
    {
	delete mClipPlaneCache;
	mClipPlaneCache = new float[4*maxPlanes];
	mClipPlaneCacheSize = maxPlanes;
    }

    /*
      Don't know yet what to do... there are several possibilities.
      In the raycaster the clip planes are preferably defined in the world
      space where the bounding box is defined.
    */
    // SbMatrix modelMat = SoModelMatrixElement::get(state);
    // modelMat = modelMat.inverse();

    /*
      Add clip planes... we could exclude clip planes being outside a bound box...
      We then need the bounding box as input.
    */
    int activePlanes = 0;
    float * planes = mClipPlaneCache;

    for (int i = 0; i < numPlanes; ++i)
    {
	SbPlane clipPlane(clipPlaneElt->get(i, 0));
	// mClipPlanes[i].transform(modelMat);

	if (true)
	{
	    const SbVec3f & normal(clipPlane.getNormal());
	
	    planes[0] = normal[0];
	    planes[1] = normal[1];
	    planes[2] = normal[2];
	    planes[3] = clipPlane.getDistanceFromOrigin();
#if 0
	    SoDebugError::postInfo("VRClipsSetup",
				   " # %d: (%.3f, %.3f, %.3f, %.3f)", activePlanes,
				   planes[0], planes[1], planes[2], planes[3]);
#endif
	    planes += 4;
	    activePlanes++;
	}
    }

    if (clipsLoc >= 0)
    {
	glUniform4fv(clipsLoc, activePlanes, mClipPlaneCache);
    }

    if (clipsNumLoc >= 0)
    {
	glUniform1i(clipsNumLoc, activePlanes);
    }

    if (clipsMaxLoc >= 0)
    {
	glUniform1i(clipsMaxLoc, maxPlanes);
    }
}


/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
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

// local Variables:
//   mode: c++
//   indent-tabs-mode: nil
//   c-indentation-style: stroustrup
//   c-basic-offset: 4
// End
