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
#include <xip/system/GL/gl.h>

#include <Inventor/actions/SoGLRenderAction.h>

#include "SoXipGpuProcessTexture.h"


static inline void CheckGLError(const char * module)
{
    GLenum err = glGetError(); 

    if (err != GL_NO_ERROR)
    { 
        SoDebugError::post(module, (char*)gluErrorString(err));
    }
}


SO_NODE_SOURCE(SoXipGpuProcessTexture);


SoXipGpuProcessTexture::SoXipGpuProcessTexture()
{
    SO_NODE_CONSTRUCTOR(SoXipGpuProcessTexture);

    // Set up enumerations for texture model
    SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_2D);
    SO_NODE_DEFINE_ENUM_VALUE(TextureDimension, TEXTURE_3D); 
    SO_NODE_SET_SF_ENUM_TYPE(textureDimension, TextureDimension);
	
    // fields
    SO_NODE_ADD_FIELD(textureDimension,	(TEXTURE_3D));
    SO_NODE_ADD_FIELD(useGeomShader,	(FALSE);)
    SO_NODE_ADD_FIELD(reload,	());

    mfboSet = 0;
    mNodeId = 0;
    mOutputSize[0] = 0;
    mOutputSize[1] = 0;
    mOutputSize[2] = 0;
    mInformGeom = false;
    mTextureDimension = 0;

#ifdef GPU_VBO

	 _vertexVBO = 0;
	_textureVBO = 0;
#endif
}


SoXipGpuProcessTexture::~SoXipGpuProcessTexture()
{

#ifdef GPU_VBO
	if(_vertexVBO)
		glDeleteBuffers(1, &_vertexVBO);
	if(_textureVBO)	
		glDeleteBuffers(1, &_textureVBO);
#endif

}


void SoXipGpuProcessTexture::initClass()
{
    SO_NODE_INIT_CLASS( SoXipGpuProcessTexture, SoNode, "Node" );

    SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
    SO_ENABLE(SoGLRenderAction, SoXipFboElement);
}


void
SoXipGpuProcessTexture::GLRender(SoGLRenderAction *action)
{
    SoState  *state = action->getState();
    renderTo3D(state);	
    //checkFramebufferStatus();
}


void SoXipGpuProcessTexture::renderTo3D(SoState  *state)
{	

    glPushAttrib(GL_ENABLE_BIT );
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
	
    setup(state);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    if (useGeomShader.getValue())
        renderTo3DMaxPerformance(state);
    else
        renderTo3DMaxCompatibility(state);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}


void SoXipGpuProcessTexture::setup(SoState  *state)
{	
    mfboSet = SoXipFboElement::getActive(state, this);

	// check FBO
	if (!mfboSet)
	{
		SoDebugError::postInfo(__FUNCTION__, " No Framebuffer Object is Active \n");
		return;
	}

	// check Shader Support	
	if (!(GL_ARB_vertex_shader && GL_ARB_fragment_shader && GL_EXT_geometry_shader4))
	{
		SoDebugError::postInfo(__FUNCTION__, "Not totally ready for GLSL :( \n");
		return;
	}

	// Oliver Kutter
	// gen VBOs for vert/tex coordinates 
#ifdef GPU_VBO
	if(!_vertexVBO)
		glGenBuffers(1, &_vertexVBO);
	if(!_textureVBO)	
		glGenBuffers(1, &_textureVBO);
#endif


    if (textureDimension.getValue()== TEXTURE_3D)
    {
        mTextureDimension = 3;
		// Oliver Kutter, do we realy want this? Only works with slicewise rendering anyways!
        glEnable(GL_TEXTURE_3D); // if there is a 3D input texture and no shader
    }
    else
        mTextureDimension = 2;

	// copy fbo width/height for output size
	mOutputSize[0] = mfboSet->width;
	mOutputSize[1] = mfboSet->height;

	// check for a possible change of the number of slices 
	// forces recomputation of the vert/tex coordinates
    bool zTexDimHasChanged = false;

	if(mOutputSize[2] != mfboSet->depth)
	{
		const int numSlices = mOutputSize[2] = mfboSet->depth;

		GLfloat  triVertexCoords[12] =
		{
			// triangle 1
			-1,  -1,
			1,  -1,
			1,  1,
			// triangle 2
			1, 1,
			-1,  1,
			-1,  -1
		};

		GLfloat triTextureCoords[24] =
		{
			// triangle 1
			0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 0.0f,
			// triangle 2
			1.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 0.0f, 0.0f, 0.0f, 
		};

		

#ifndef GPU_VBO
		_vertexCoords.resize (numSlices	 * 12);
		_textureCoords.resize(numSlices  * 24);

		float * vertexBuffMem = &_vertexCoords[0];
		float * textureBuffMem = &_textureCoords[0];
#else
		// check for currently bound GL_ARRAY BUFFER
		GLint prevArrayBuffer = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prevArrayBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, numSlices * 12 * sizeof(float), 0, GL_STATIC_DRAW);
		float * vertexBuffMem = (float* ) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		glBindBuffer(GL_ARRAY_BUFFER, _textureVBO);
		glBufferData(GL_ARRAY_BUFFER, numSlices * 24 * sizeof(float), 0, GL_STATIC_DRAW);
		float * textureBuffMem =(float* ) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#endif
		float dInc = 1.0f / (float) numSlices;
		float d = 0.5 * dInc;

		// update Texture Coordinates
		for (int z = 0; z < numSlices; z++)
		{		
			// set 3D texture z coordinate for looking up bound 3D texture in shader
			triTextureCoords[2] =
				triTextureCoords[6] =
				triTextureCoords[10] =
				triTextureCoords[14] =
				triTextureCoords[18] =
				triTextureCoords[22] = (float)d;

			// set layer coordinate for geometry shader 
			triTextureCoords[3] =
				triTextureCoords[7] =
				triTextureCoords[11] =
				triTextureCoords[15] =
				triTextureCoords[19] =
				triTextureCoords[23] = (float)z;

			// copy current slices vert/tex coordinates to VAO/VBO
			::memcpy(vertexBuffMem, triVertexCoords, sizeof(GLfloat) * 12);
			::memcpy(textureBuffMem, triTextureCoords, sizeof(GLfloat) * 24);

			vertexBuffMem  += 12;
			textureBuffMem += 24;

			d += dInc;
		}

#ifdef GPU_VBO
		glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glBindBuffer(GL_ARRAY_BUFFER, _textureVBO);
		glUnmapBuffer(GL_ARRAY_BUFFER);

		// disable vbo, replace with currently bound vbo in cleaned up version
		glBindBuffer(GL_ARRAY_BUFFER, prevArrayBuffer);
#endif
		// 2 triangles per quad -> 6 vertices
		mNumTrianglePoints = 6 * numSlices;
	}

	// setup viewport for rendering to FBO
    glViewport(0, 0, mOutputSize[0], mOutputSize[1]);
}


void SoXipGpuProcessTexture:: renderTo3DMaxCompatibility(SoState  *state)
{
    GLfloat	vertexCoordsQuad[8] =
    {
        -1,-1,
         1,-1,
         1, 1,
        -1, 1
    };

    // when using gl_DrawArrays
    GLfloat texCoordsQuad[12] =
    {
        0.0f, 0.0f, 0.0f, 
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // point to Vertex and Tex Coords when using gl_DrawArrays
    glVertexPointer(2, GL_FLOAT, 0, vertexCoordsQuad);
    glTexCoordPointer(3, GL_FLOAT, 0, texCoordsQuad);

    // offset in z direction when reading from input texture
    // z coordinate when reading from input texture
    int numSlices = mOutputSize[2];
    float dInc = 1.0f / (float) numSlices;
    float d = 0.5 * dInc;

    for(int z = 0; z < numSlices; z++)
    {
        // Attach 3D Texture as target to FBO (glFramebufferTexture3DEXT)
        if (textureDimension.getValue() == TEXTURE_3D || mTextureDimension == 3)
        {
            SoXipFboElement::renderToSlice(state, this, z);
        }

#if 0 /*CODE REVIEW Stefan Lindholm*/
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
#endif

        texCoordsQuad[2] =
            texCoordsQuad[5] =
            texCoordsQuad[8] =
            texCoordsQuad[11] = d;
		
        // render into the quad for each slice
        glDrawArrays(GL_QUADS, 0, 4);
        d += dInc;
    }
}


void SoXipGpuProcessTexture:: renderTo3DMaxPerformance(SoState  *state)
{
	// inform about a necessary geometry shader
	if (mInformGeom == false)
	{
		SoDebugError::postInfo(__FUNCTION__, "This mode requires a geometry shader\n");
		mInformGeom = true;
	}

	if (textureDimension.getValue() == TEXTURE_3D || mTextureDimension == 3)
	{
		SoXipFboElement::reattachAs3D(state, this);
	}

#ifndef GPU_VBO
	glVertexPointer(  2, GL_FLOAT, 0, &_vertexCoords[0]);
	glTexCoordPointer(4, GL_FLOAT, 0, &_textureCoords[0]);
#else
	GLint prevArrayBuffer = 0;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prevArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVBO);
	glVertexPointer(  2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, _textureVBO);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
#endif

	glDrawArrays(GL_TRIANGLES, 0, mNumTrianglePoints);

#ifdef GPU_VBO
	glBindBuffer(GL_ARRAY_BUFFER, prevArrayBuffer);
#endif
}


void SoXipGpuProcessTexture:: checkFramebufferStatus()
{
    GLenum status;
    status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
    case GL_FRAMEBUFFER_COMPLETE_EXT:
        //SoDebugError::postInfo(__FUNCTION__, "Framebuffer seems to work\n");
        break;		 
    case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
        SoDebugError::postInfo(__FUNCTION__,
                               "Unsupported framebuffer format\n");
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
        SoDebugError::postInfo(__FUNCTION__, "Framebuffer incomplete, "
                               "attached images must have same dimensions\n");
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
        SoDebugError::postInfo(__FUNCTION__, "Framebuffer incomplete, "
                               "missing attachment\n");
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        SoDebugError::postInfo(__FUNCTION__, "Framebuffer incomplete, "
                               "attached images must have same dimensions\n");
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
        SoDebugError::postInfo(__FUNCTION__, "Framebuffer incomplete, "
                               "attached images must have same format\n");
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
        SoDebugError::postInfo(__FUNCTION__, "Framebuffer incomplete, "
                               "missing draw buffer\n");
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
        SoDebugError::postInfo(__FUNCTION__, "Framebuffer incomplete, "
                               "missing read buffer\n");
        break;
    default:
        SoDebugError::postInfo(__FUNCTION__, "Framebuffer incomplete, "
                               "missing read buffer\n");
        break;
    }
}


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
