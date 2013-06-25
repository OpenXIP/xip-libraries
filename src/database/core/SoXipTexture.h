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
*	Node class for texture handling
*/

#ifndef SO_XIP_TEXTURE_H
#define SO_XIP_TEXTURE_H

#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/nodes/SoSubNode.h>
//#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>

#include <xip/system/standard.h> 
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glu.h>

#ifndef TGS_VERSION
class SoGLDisplayList;
#endif

/**
*	SoXipTexture. An Open Inventor node to create and upload
*	any texture in video memory
*/
class XIPIVCORE_API SoXipTexture : public SoNode//SoShape
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

#if 0 //SoXipTexture IS NO LONGER A SHAPE (Stefan Lindholm - 2009.8.19)
    virtual void generatePrimitives(SoAction *action) {};
    /**	
    *	Compute the bounding box for the texture
    */
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);	
#endif

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
    /**	
    *	Outputs the texture model matrix
    */
    SoSFMatrix modelMatrix;

    SoSFBool	usePBO;
    /*
    * Automatically scale the range of pixels (using pixel_scale and _bias),
    * based on bitsUsed of the input image.
    */
    SoSFBool	autoScaleRange;

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
    *	Texture model matrix for current and new images
    */
    SbMatrix mTextureModelMatrix;
    SbMatrix mNewTextureModelMatrix;

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
