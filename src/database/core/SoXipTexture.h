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

/**
 *	Node class for texture handling
 */

#ifndef SO_XIP_TEXTURE_H
#define SO_XIP_TEXTURE_H

#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>

#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glext.h>

#ifndef DARWIN
# include <GL/glu.h>
#endif /* DARWIN */

#ifndef TGS_VERSION
class SoGLDisplayList;
#endif

/**
 *	SoXipTexture. An Open Inventor node to create and upload
 *	any texture in video memory
 */
class XIPIVCORE_API SoXipTexture : public SoShape
{
	SO_NODE_HEADER(SoXipTexture);

public:
	/**
	 *	Constructor
	 */
	SoXipTexture();
	/**
	 *	Destructor
	 */
	virtual ~SoXipTexture();
	/**	
	 *	Enum for internal texture dimension
	 */
	enum TextureDimension {
		TEXTURE_1D = GL_TEXTURE_1D,
		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_3D = GL_TEXTURE_3D,
		AUTO,
	};
	/**	
	 *	Enum for internal format of the texture
	 */
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
	/**	
	 *	Enum for the texture model
	 */
	enum Model
	{
		REPLACE = GL_REPLACE,
		MODULATE = GL_MODULATE,
		DECAL = GL_DECAL,
		BLEND = GL_BLEND,
		ADD = GL_ADD
	};
	/**	
	 *	Enum for the texture wrap type
	 */
	enum Wrap
	{
		REPEAT = GL_REPEAT,
		CLAMP = GL_CLAMP,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT
	};
	/**	
	 *	Enum for the texture filtering method
	 */
	enum Filter
	{
		NEAREST	= GL_NEAREST,
		LINEAR = GL_LINEAR
	};

    virtual void generatePrimitives(SoAction *action) {};
	/**	
	 *	Compute the bounding box for the texture
	 */
	virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);	
	virtual void doAction(SoAction *action);
	virtual void GLRender(SoGLRenderAction *action);
	/**	
	 *	Initializes the class
	 */
	static void initClass();
	/**	
	 *	Test if non-power of two textures are supported
	 */
	virtual SbBool hasNonPowerOfTwoExtensions() const;
	/**	
	 *	Input image
	 */
	SoXipSFDataImage image;
	/**	
	 *	Bind the texture ?
	 */
	SoSFBool on;
	/**	
	 *	Sets the texture matrix to model matrix of connected image
	 */
	SoSFBool textureMatrix;

	/**	
	 *	Wrap type
	 */
	SoSFEnum wrapS;
	SoSFEnum wrapT;
	SoSFEnum wrapR;
	/**	
	 *	Color for the border of the texture
	 */
	SoSFVec4f borderColor;
	/**	
	 *	Filtering method
	 */
	SoSFEnum filter;
	/**	
	 *	Model for the texture
	 */
	SoSFEnum model;
	/**	
	 *	Texture Dimension
	 */
	SoSFEnum textureDimension;
	/**	
	 *	Blend color if the model is BLEND
	 */
	SoSFVec4f blendColor;
	/**	
	 *	Need to override the default data type ?
	 */
	SoSFBool overrideDefault;
	/**	
	 *	Internal format
	 */
	SoSFEnum internalFormat;
	/**	
	 *	Pad the dimensions of the texture to have
	 *	power-of-two dimensions
	 */
	SoSFBool padDimensions;
	/**
	 * Certain video cards (ATI) support the NPOT extension but do not export the string.
	 * If this flag is true then we don't check the extension and NPOT support is assumed.
	 */
	SoSFBool forceNPOT;
	/**	
	 *	Outputs the texture size
	 */
	SoSFVec3f textureSize;

	SoSFBool	usePBO;

private:
	/**	
	 *	Checks if the input image is valid
	 */
	bool validateImage();
#ifdef TGS_VERSION
	/**	
	 *	Delete the texture
	 */
	void deleteTexture();
	/**	
	 *	Allocate memory for the texture
	 */
	void allocTexture();
#else
	void deleteTexture(SoGLRenderAction *action);
	void allocTexture(SoGLRenderAction *action);
#endif
	/**	
	 *	Compare the input image with the current image
	 */
	bool compareImage();
	/**	
	 *	Create the texture
	 */
	void createTexture();
	/**	
	 *	Set the parameters for the texture
	 */
	void setTexParams();
	/**	
	 *	Set the environment for the texture
	 */
	void setTexEnv();
	/**	
	 *	Update the current texture
	 */
    void updateTexture();
	/**	
	 *	Update the image
	 */
	void updateImage();
	/**	
	 *	Bind the texture
	 */
	void bindTexture(SoState *state);
	/**	
	 *	Enable texturing
	 */
	void enableTexture(SoState *state);
	/**	
	 *	Get the next power-of-two
	 */	
	unsigned int powerOfTwo(unsigned int x);
	
	/**	
	 *	Utility functions to handle the texture dimensions
	 */
	SbXipImageDimensions calcTextureSize(const SbXipImageDimensions &dim);
	GLenum getTextureDimension(const SbXipImageDimensions &dim);
	/**	
	 *	callback functions to update the texture
	 */
	static void paramHasChangedCB(void *data, SoSensor* s);
	static void textureInvalidCB(void *data, SoSensor* s);

	/**	
	 *	Sensors for the input image
	 */
	int mNumFields;
	SoFieldSensor **mSensors;
	int mNumCriticalFields;
	SoFieldSensor **mCriticalSensors;

	/**	
	 *	Current image
	 */
	SoXipDataImage *mImageData;
	/**	
	 *	New image
	 */
	SoXipDataImage *mNewImageData;
    bool mImageHasChanged;
	bool mParamHasChanged;
	uint32_t mImageId;

	/**	
	 *	Texture Id
	 */
#ifdef TGS_VERSION
	GLuint mGLTexture;
#else
	SoGLDisplayList *mGLTexture;
#endif
	/**	
	 *	Texture sizes for current and new images
	 */
	SbXipImageDimensions mTextureSize;
	SbXipImageDimensions mNewTextureSize;
	
	/**	
	 *	Texture dimensions (1D/2D/3D) for current and new images
	 */
	GLenum mTextureDimension;
	GLenum mNewTextureDimension;
	/**	
	 *	Data types for current and new images
	 */
	unsigned int mTextureDataType;
	unsigned int mNewTextureDataType;
	/**	
	 *	Internal formats for current and new images
	 */	
	GLenum mTextureInternalFormat;
	GLenum mNewTextureInternalFormat;

	enum ScaleOption {
		NONE,
		BITSUSED,
		BITSUSED_SIGNED
	};
	/**	
	 *	Information of the currently used data type
	 */
	struct DataTypeInfo {
		GLenum type;
		int bits;
		ScaleOption scaleOption;
		GLenum defaultFormat[4];
	};

	static GLint maxTextureSize;
	static GLenum baseFormats[4];
	static DataTypeInfo dataTypeInfo[8];

	bool	mHasPBOs;
	unsigned int mPBOId;
	unsigned int	mPBOBufSize;

	bool	mQueryExtensions;
};

#endif // SO_XIP_TEXTURE_H
