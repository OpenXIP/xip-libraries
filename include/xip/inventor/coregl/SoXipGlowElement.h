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

#ifndef SO_XIP_GLOW_ELEMENT_H
#define SO_XIP_GLOW_ELEMENT_H

#ifdef linux
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glext.h>
#include <xip/system/GL/glxext.h>
//#include <GL/gl.h>
//#include <GL/glext.h>
#else /* linux */
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glext.h>
#endif /* linux */
#include <Inventor/elements/SoSubElement.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#ifdef linux
  #define glCopyTexSubImage3D glCopyTexSubImage3Dext
  #define glTexImage3D glTexImage3Dext
  #define glTexSubImage3D glTexSubImage3Dext
  #define glActiveTexture glActiveTextureext
#endif

#ifdef WIN32
//#include <windows.h>
#ifdef _CRT_ALLOCATION_DEFINED 
	#include <xip/system/GL/gl.h>
	#include <xip/system/GL/glext.h>
#else //only for VC6 compilation
	#include <GL/gl.h>
	#include <GL/glext.h>
	#define xipGlGetProcAddress(X) wglGetProcAddress(X)
#endif
#endif

extern XIPIVCOREGL_API bool GLOW_init;
extern XIPIVCOREGL_API bool GLOW_GREMEDY_string_marker;
extern XIPIVCOREGL_API bool GLOW_EXT_framebuffer_object;
extern XIPIVCOREGL_API bool GLOW_ARB_pixel_buffer_object;
extern XIPIVCOREGL_API bool GLOW_ARB_shader_objects;
extern XIPIVCOREGL_API bool GLOW_ARB_fragment_shader;
extern XIPIVCOREGL_API bool GLOW_EXT_geometry_shader4;
extern XIPIVCOREGL_API bool GLOW_ARB_shading_language_100;
extern XIPIVCOREGL_API bool GLOW_EXT_depth_bounds_test;
extern XIPIVCOREGL_API bool GLOW_ARB_texture_non_power_of_two;
extern XIPIVCOREGL_API bool GLOW_ARB_draw_buffers;
extern XIPIVCOREGL_API bool GLOW_EXT_timer_query;
extern XIPIVCOREGL_API bool GLOW_ARB_occlusion_query;

#ifndef DARWIN
#ifndef linux
extern XIPIVCOREGL_API PFNGLGETQUERYOBJECTI64VEXTPROC	glGetQueryObjecti64vEXT;
extern XIPIVCOREGL_API PFNGLGETQUERYOBJECTUI64VEXTPROC	glGetQueryObjectui64vEXT;
#endif
extern XIPIVCOREGL_API PFNGLGENQUERIESARBPROC			glGenQueriesARB;
extern XIPIVCOREGL_API PFNGLDELETEQUERIESARBPROC		glDeleteQueriesARB;
extern XIPIVCOREGL_API PFNGLBEGINQUERYARBPROC			glBeginQueryARB;
extern XIPIVCOREGL_API PFNGLENDQUERYARBPROC				glEndQueryARB;
extern XIPIVCOREGL_API PFNGLGETQUERYIVARBPROC			glGetQueryivARB;
extern XIPIVCOREGL_API PFNGLGETQUERYOBJECTIVARBPROC		glGetQueryObjectivARB;
extern XIPIVCOREGL_API PFNGLGETQUERYOBJECTUIVARBPROC	glGetQueryObjectuivARB;

extern XIPIVCOREGL_API PFNGLTEXIMAGE3DEXTPROC glTexImage3D;
extern XIPIVCOREGL_API PFNGLTEXSUBIMAGE3DEXTPROC glTexSubImage3D;
extern XIPIVCOREGL_API PFNGLCOPYTEXSUBIMAGE3DPROC			glCopyTexSubImage3D;

extern XIPIVCOREGL_API PFNGLACTIVETEXTUREPROC				glActiveTexture;

extern XIPIVCOREGL_API PFNGLDRAWBUFFERSPROC                 glDrawBuffers;
extern XIPIVCOREGL_API PFNGLBINDBUFFERPROC					glBindBuffer;
extern XIPIVCOREGL_API PFNGLDELETEBUFFERSPROC				glDeleteBuffers;
extern XIPIVCOREGL_API PFNGLGENBUFFERSPROC					glGenBuffers;
extern XIPIVCOREGL_API PFNGLISBUFFERPROC					glIsBuffer;
extern XIPIVCOREGL_API PFNGLBUFFERDATAPROC					glBufferData;
extern XIPIVCOREGL_API PFNGLBUFFERSUBDATAPROC				glBufferSubData;
extern XIPIVCOREGL_API PFNGLGETBUFFERSUBDATAPROC			glGetBufferSubData;
extern XIPIVCOREGL_API PFNGLMAPBUFFERPROC					glMapBuffer;
extern XIPIVCOREGL_API PFNGLUNMAPBUFFERPROC				    glUnmapBuffer;
extern XIPIVCOREGL_API PFNGLGETBUFFERPARAMETERIVPROC		glGetBufferParamateriv;
extern XIPIVCOREGL_API PFNGLGETBUFFERPOINTERVPROC			glGetBufferPointerv;

extern XIPIVCOREGL_API PFNGLATTACHSHADERPROC				glAttachShader;
extern XIPIVCOREGL_API PFNGLBINDATTRIBLOCATIONPROC			glBindAttribLocation;
extern XIPIVCOREGL_API PFNGLCOMPILESHADERPROC				glCompileShader;
extern XIPIVCOREGL_API PFNGLCREATEPROGRAMPROC				glCreateProgram;
extern XIPIVCOREGL_API PFNGLCREATESHADERPROC				glCreateShader;
extern XIPIVCOREGL_API PFNGLDELETEPROGRAMPROC				glDeleteProgram;
extern XIPIVCOREGL_API PFNGLDELETESHADERPROC				glDeleteShader;
extern XIPIVCOREGL_API PFNGLDETACHSHADERPROC				glDetachShader;
extern XIPIVCOREGL_API PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray;
extern XIPIVCOREGL_API PFNGLENABLEVERTEXATTRIBARRAYPROC		glEnableVertexAttribArray;
extern XIPIVCOREGL_API PFNGLGETACTIVEATTRIBPROC				glGetActiveAttrib;
extern XIPIVCOREGL_API PFNGLGETACTIVEUNIFORMPROC			glGetActiveUniform;
extern XIPIVCOREGL_API PFNGLGETATTACHEDSHADERSPROC			glGetAttachedShaders;
extern XIPIVCOREGL_API PFNGLGETATTRIBLOCATIONPROC			glGetAttribLocation;
extern XIPIVCOREGL_API PFNGLGETPROGRAMIVPROC				glGetProgramiv;
extern XIPIVCOREGL_API PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog;
extern XIPIVCOREGL_API PFNGLGETSHADERIVPROC					glGetShaderiv;
extern XIPIVCOREGL_API PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog;
extern XIPIVCOREGL_API PFNGLGETSHADERSOURCEPROC				glGetShaderSource;
extern XIPIVCOREGL_API PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation;
extern XIPIVCOREGL_API PFNGLGETUNIFORMFVPROC				glGetUniformfv;
extern XIPIVCOREGL_API PFNGLGETUNIFORMIVPROC				glGetUniformiv;
extern XIPIVCOREGL_API PFNGLGETVERTEXATTRIBDVPROC			glGetVertexAttribdv;
extern XIPIVCOREGL_API PFNGLGETVERTEXATTRIBFVPROC			glGetVertexAttribfv;
extern XIPIVCOREGL_API PFNGLGETVERTEXATTRIBIVPROC			glGetVertexAttribiv;
extern XIPIVCOREGL_API PFNGLGETVERTEXATTRIBPOINTERVPROC		glGetVertexAttribPointerv;
extern XIPIVCOREGL_API PFNGLISPROGRAMPROC					glIsProgram;
extern XIPIVCOREGL_API PFNGLISSHADERPROC					glIsShader;
extern XIPIVCOREGL_API PFNGLLINKPROGRAMPROC					glLinkProgram;
extern XIPIVCOREGL_API PFNGLSHADERSOURCEPROC				glShaderSource;
extern XIPIVCOREGL_API PFNGLUSEPROGRAMPROC					glUseProgram;
extern XIPIVCOREGL_API PFNGLUNIFORM1FPROC					glUniform1f;
extern XIPIVCOREGL_API PFNGLUNIFORM2FPROC					glUniform2f;
extern XIPIVCOREGL_API PFNGLUNIFORM3FPROC					glUniform3f;
extern XIPIVCOREGL_API PFNGLUNIFORM4FPROC					glUniform4f;
extern XIPIVCOREGL_API PFNGLUNIFORM1IPROC					glUniform1i;
extern XIPIVCOREGL_API PFNGLUNIFORM2IPROC					glUniform2i;
extern XIPIVCOREGL_API PFNGLUNIFORM3IPROC					glUniform3i;
extern XIPIVCOREGL_API PFNGLUNIFORM4IPROC					glUniform4i;
extern XIPIVCOREGL_API PFNGLUNIFORM1FVPROC					glUniform1fv;
extern XIPIVCOREGL_API PFNGLUNIFORM2FVPROC					glUniform2fv;
extern XIPIVCOREGL_API PFNGLUNIFORM3FVPROC					glUniform3fv;
extern XIPIVCOREGL_API PFNGLUNIFORM4FVPROC					glUniform4fv;
extern XIPIVCOREGL_API PFNGLUNIFORM1IVPROC					glUniform1iv;
extern XIPIVCOREGL_API PFNGLUNIFORM2IVPROC					glUniform2iv;
extern XIPIVCOREGL_API PFNGLUNIFORM3IVPROC					glUniform3iv;
extern XIPIVCOREGL_API PFNGLUNIFORM4IVPROC					glUniform4iv;
extern XIPIVCOREGL_API PFNGLUNIFORMMATRIX2FVPROC			glUniformMatrix2fv;	
extern XIPIVCOREGL_API PFNGLUNIFORMMATRIX3FVPROC			glUniformMatrix3fv;	
extern XIPIVCOREGL_API PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv;
extern XIPIVCOREGL_API PFNGLVALIDATEPROGRAMPROC				glValidateProgram;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB1DPROC				glVertexAttrib1d ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB1DVPROC				glVertexAttrib1dv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB1FPROC				glVertexAttrib1f ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB1FVPROC				glVertexAttrib1fv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB1SPROC				glVertexAttrib1s ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB1SVPROC				glVertexAttrib1sv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB2DPROC				glVertexAttrib2d ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB2DVPROC				glVertexAttrib2dv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB2FPROC				glVertexAttrib2f ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB2FVPROC				glVertexAttrib2fv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB2SPROC				glVertexAttrib2s ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB2SVPROC				glVertexAttrib2sv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB3DPROC				glVertexAttrib3d ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB3DVPROC				glVertexAttrib3dv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB3FPROC				glVertexAttrib3f ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB3FVPROC				glVertexAttrib3fv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB3SPROC				glVertexAttrib3s ;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB3SVPROC				glVertexAttrib3sv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4NBVPROC			glVertexAttrib4Nbv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4NIVPROC			glVertexAttrib4Niv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4NSVPROC			glVertexAttrib4Nsv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4NUBPROC			glVertexAttrib4Nub;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4NUBVPROC			glVertexAttrib4Nubv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4NUIVPROC			glVertexAttrib4Nuiv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4NUSVPROC			glVertexAttrib4Nusv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4BVPROC				glVertexAttrib4bv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4DPROC				glVertexAttrib4d;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4DVPROC				glVertexAttrib4dv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4FPROC				glVertexAttrib4f;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4FVPROC				glVertexAttrib4fv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4IVPROC				glVertexAttrib4iv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4SPROC				glVertexAttrib4s; 
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4SVPROC				glVertexAttrib4sv; 
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4UBVPROC			glVertexAttrib4ubv; 
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4UIVPROC			glVertexAttrib4uiv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIB4USVPROC			glVertexAttrib4usv;
extern XIPIVCOREGL_API PFNGLVERTEXATTRIBPOINTERPROC			glVertexAttribPointer;

extern XIPIVCOREGL_API PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT;
extern XIPIVCOREGL_API PFNGLBINDRENDERBUFFEREXTPROC						glBindRenderbufferEXT;
extern XIPIVCOREGL_API PFNGLDELETERENDERBUFFERSEXTPROC					glDeleteRenderbuffersEXT;
extern XIPIVCOREGL_API PFNGLGENRENDERBUFFERSEXTPROC						glGenRenderbuffersEXT;
extern XIPIVCOREGL_API PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT;
extern XIPIVCOREGL_API PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT;
extern XIPIVCOREGL_API PFNGLISFRAMEBUFFEREXTPROC						glIsFramebufferEXT;
extern XIPIVCOREGL_API PFNGLBINDFRAMEBUFFEREXTPROC						glBindFramebufferEXT;
extern XIPIVCOREGL_API PFNGLDELETEFRAMEBUFFERSEXTPROC					glDeleteFramebuffersEXT;
extern XIPIVCOREGL_API PFNGLGENFRAMEBUFFERSEXTPROC						glGenFramebuffersEXT;
extern XIPIVCOREGL_API PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT;
extern XIPIVCOREGL_API PFNGLFRAMEBUFFERTEXTURE1DEXTPROC					glFramebufferTexture1DEXT;
extern XIPIVCOREGL_API PFNGLFRAMEBUFFERTEXTURE2DEXTPROC					glFramebufferTexture2DEXT;
extern XIPIVCOREGL_API PFNGLFRAMEBUFFERTEXTURE3DEXTPROC					glFramebufferTexture3DEXT;
extern XIPIVCOREGL_API PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT;
extern XIPIVCOREGL_API PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT;
extern XIPIVCOREGL_API PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT;
extern XIPIVCOREGL_API PFNGLPROGRAMPARAMETERIEXTPROC					glProgramParameteriEXT;
extern XIPIVCOREGL_API PFNGLFRAMEBUFFERTEXTUREEXTPROC					glFramebufferTextureEXT;
extern XIPIVCOREGL_API PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC				glFramebufferTextureLayerEXT; 
extern XIPIVCOREGL_API PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC				glFramebufferTextureFaceEXT; 

extern XIPIVCOREGL_API PFNGLBLENDEQUATIONEXTPROC						glBlendEquationEXT;

extern XIPIVCOREGL_API PFNGLGETHANDLEARBPROC							glGetHandleARB;

extern XIPIVCOREGL_API PFNGLSTRINGMARKERGREMEDYPROC						glStringMarkerGREMEDY;

extern XIPIVCOREGL_API PFNGLDEPTHBOUNDSEXTPROC							glDepthBoundsEXT;
#endif // DARWIN

class XIPIVCOREGL_API SoXipGLOWElement : public SoElement {
	SO_ELEMENT_HEADER(SoXipGLOWElement);

public:
	static void initClass();

	void init(SoState *state);
	
	inline SbBool matches(const SoElement *elt) const { return true; }
	inline SoElement *copyMatchInfo() const { return (SoXipGLOWElement*)getTypeId().createInstance(); }

private:
	
};
class XIPIVCOREGL_API SoXipGLOW
{
public:
	static void init();
};

int	XIPIVCOREGL_API getPackAlignment(int width);

#endif // SO_XIP_GLOW_ELEMENT_H

