/*
  ------------------------------------------------------------------------

    SoXipGpuProcessTexture.cpp

    This node provides image processing for texture to texture
    processing on the GPU, supporting both 2D and 3D textures.
    Requires the use of GLSL Shader Program

    Copyright (C) 2008 - 2009, Siemens Corporate Research, Inc.

    Authors:
      Fabian Klebe, fabian.klebe.ext@siemens.com
      Stefan Lindholm, stefan.lindholm.ext@siemens.com
      Patric Ljung, patric.ljung@siemens.com

    This file is part of Open XIP under the caBig license, see end of
    file for details.

  ------------------------------------------------------------------------
*/


#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/system/GL/glu.h>

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
    mHasChanged = true;
    mInformGeom = false;
    mTextureDimension = 0;
}


SoXipGpuProcessTexture::~SoXipGpuProcessTexture()
{
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

    if (useGeomShader.getValue())
        renderTo3DMaxPerformance();
    else
        renderTo3DMaxCompatibility(state);

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

    if (textureDimension.getValue()== TEXTURE_3D)
    {
        mTextureDimension = 3;
        glEnable(GL_TEXTURE_3D); // if there is a 3D input texture and no shader
    }
    else
        mTextureDimension = 2;

    mOutputSize[0] = mfboSet->width;
    mOutputSize[1] = mfboSet->height;
    mOutputSize[2] = mfboSet->depth;

    glViewport(0, 0, mOutputSize[0], mOutputSize[1]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}


void SoXipGpuProcessTexture:: renderTo3DMaxCompatibility(SoState  *state)
{
    GLfloat	vertexCoordsQuad[8] =
    {
        1, 1,
        -1, 1,
        -1,-1,
        1,-1
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
    int depth = mOutputSize[2];
    float dInc = 1.0f / (float) depth;
    float d = 0.5 * dInc;

    for(int z = 0; z < depth; z++)
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


void SoXipGpuProcessTexture:: renderTo3DMaxPerformance()
{
    // inform about a necessary geometry shader
    if (mInformGeom == false)
    {
        SoDebugError::postInfo(__FUNCTION__, "This mode requires a geometry shader\n");
        mInformGeom = true;
    }

    const int vertCoordNum = 12;
    const int textCoordNum = 24;

    GLfloat	vertexCoordsMaxPerform[12] =
    {
        // triangle 1
        1,  1,
        -1,  1,
        -1, -1,
        // triangle 2
        -1, -1,
        1, -1,
        1,  1
    };

    float textureCoords[textCoordNum] =
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

    std::vector<float> _vertexCoords;
    std::vector<float> _textureCoords;
	
    const int depth = mOutputSize[2];
    //float _vertexCoords[(const int)depth	 * vertCoordNum];
    _vertexCoords.resize (depth	 * vertCoordNum);
    _textureCoords.resize(depth  * textCoordNum);

    float dInc = 1.0f / (float) depth;
    float d = 0.5 * dInc;

    // update Texture Coordinates
    for (int z = 0; z < depth; z++)
    {		
        textureCoords[2] =
            textureCoords[6] =
            textureCoords[10] =
            textureCoords[14] =
            textureCoords[18] =
            textureCoords[22] = (float)d;

        textureCoords[3] =
            textureCoords[7] =
            textureCoords[11] =
            textureCoords[15] =
            textureCoords[19] =
            textureCoords[23] = (float)z;

        ::memcpy(&_vertexCoords [z * vertCoordNum],
                 vertexCoordsMaxPerform, sizeof(GLfloat) *vertCoordNum);
        ::memcpy(&_textureCoords[z * textCoordNum],
                 textureCoords, sizeof(GLfloat) *textCoordNum);
		
        d += dInc;
    }

    glVertexPointer(  2, GL_FLOAT, 0, &_vertexCoords[0]);
    glTexCoordPointer(4, GL_FLOAT, 0, &_textureCoords[0]);
	
    glDrawArrays(GL_TRIANGLES, 0, 6 * depth);
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
