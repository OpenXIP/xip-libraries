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

#ifndef SO_XIP_FRAMEBUFFER_GROUP_H
#define SO_XIP_FRAMEBUFFER_GROUP_H

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

class SoXipFramebufferGroup : public SoGroup {
	SO_NODE_HEADER(SoXipFramebufferGroup);

public:
	enum Format {
		NONE = 0,
		ALPHA = GL_ALPHA,
		LUMINANCE = GL_LUMINANCE,
		LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA,
		INTENSITY = GL_INTENSITY,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
	};

	enum InternalFormat {
		ALPHA4 = GL_ALPHA4,
		ALPHA8 = GL_ALPHA8,
		ALPHA12 = GL_ALPHA12,
		ALPHA16 = GL_ALPHA16,
		ALPHA16F_ARB = GL_ALPHA16F_ARB,
		ALPHA32F_ARB = GL_ALPHA32F_ARB,
		LUMINANCE4 = GL_LUMINANCE4,
		LUMINANCE8 = GL_LUMINANCE8,
		LUMINANCE12 = GL_LUMINANCE12,
		LUMINANCE16 = GL_LUMINANCE16,
		LUMINANCE16F_ARB = GL_LUMINANCE16F_ARB,
		LUMINANCE32F_ARB = GL_LUMINANCE32F_ARB,
		LUMINANCE4_ALPHA4 = GL_LUMINANCE4_ALPHA4,
		LUMINANCE6_ALPHA2 = GL_LUMINANCE6_ALPHA2,
		LUMINANCE8_ALPHA8 = GL_LUMINANCE8_ALPHA8,
		LUMINANCE12_ALPHA4 = GL_LUMINANCE12_ALPHA4,
		LUMINANCE12_ALPHA12 = GL_LUMINANCE12_ALPHA12,
		LUMINANCE16_ALPHA16 = GL_LUMINANCE16_ALPHA16,
		LUMINANCE_ALPHA16F_ARB = GL_LUMINANCE_ALPHA16F_ARB,
		LUMINANCE_ALPHA32F_ARB = GL_LUMINANCE_ALPHA32F_ARB,
		INTENSITY4 = GL_INTENSITY4,
		INTENSITY8 = GL_INTENSITY8,
		INTENSITY12 = GL_INTENSITY12,
		INTENSITY16 = GL_INTENSITY16,
		INTENSITY16F_ARB = GL_INTENSITY16F_ARB,
		INTENSITY32F_ARB = GL_INTENSITY32F_ARB,
		R3_G3_B2 = GL_R3_G3_B2,
		RGB4 = GL_RGB4,
		RGB5 = GL_RGB5,
		RGB8 = GL_RGB8,
		RGB10 = GL_RGB10,
		RGB12 = GL_RGB12,
		RGB16 = GL_RGB16,
		RGB16F_ARB = GL_RGB16F_ARB,
		RGB32F_ARB = GL_RGB32F_ARB,
		RGBA2 = GL_RGBA2,
		RGBA4 = GL_RGBA4,
		RGB5_A1 = GL_RGB5_A1,
		RGBA8 = GL_RGBA8,
		RGB10_A2 = GL_RGB10_A2,
		RGBA12 = GL_RGBA12,
		RGBA16 = GL_RGBA16,
		RGBA16F_ARB = GL_RGBA16F_ARB,
		RGBA32F_ARB = GL_RGBA32F_ARB,
	};

	enum DepthInternalFormat {
		DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
		DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
		DEPTH_COMPONENT32 = GL_DEPTH_COMPONENT32,
	};

	enum Wrap			// Texture wrap type
	{
		REPEAT			= GL_REPEAT,
		CLAMP			= GL_CLAMP,
		CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER	= GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT	= GL_MIRRORED_REPEAT
	};

	enum Filter
	{
		NEAREST	= GL_NEAREST,
		LINEAR = GL_LINEAR
	};

	SoXipFramebufferGroup();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

protected:
	SoFieldSensor **mSensors;
	int mNumFields;

private:
	~SoXipFramebufferGroup();

	static void sensorCB(void *usr, SoSensor *sensor);

	void allocate();
	void deallocate();

	SoSFInt32 width;
	SoSFInt32 height;
	SoSFBool autoSize;
	SoSFEnum format;
	SoSFEnum internalFormat;
	SoSFEnum depthInternalFormat;
	SoSFEnum wrapS;
	SoSFEnum wrapT;
	SoSFEnum filter;
	SoSFVec4f borderColor;
	//SoSFInt32 numBuffers;
	SoSFBool needPingPong;
	SoSFBool sharedDepth;
	SoSFBool bindAllTextures;

	bool mNeedsUpdate;
	bool mIsAllocated;

	GLuint mFrameBuffer[2];
	GLuint mColorBufferTex[2];
	GLuint mDepthBuffer[2];
	int mNumFrameBuffers;
	int mNumDepthBuffers;

	int mWidth;
	int mHeight;
};


#endif // SO_XIP_FRAMEBUFFER_GROUP_H
