/*
  ------------------------------------------------------------------------

    SoXipDirectRaycaster.cpp

    Direct Raycaster for Volume Rendering

    Copyright (C) 2007 - 2009, Siemens Corporate Research, Inc.

    Authors:
      Patric Ljung, patric.ljung@siemens.com

    This file is part of Open XIP under the caBig license, see end of
    file for details.

  ------------------------------------------------------------------------
*/

/*
  Scope:

  This component is intended for direct raycasting by rendering the
  bounding box of a volume.  It is a possible replacement for the
  volume slicer.
*/

/*
  Implementation Notes:

  1. Scaling and dimensions of the Bounding Box

  After some considering I decided that the volume's Spacial Bounding
  Box should be scaled by explicitely setting the size of it and not
  by using Model Matrix Scale Transform before a normalized cube.  By
  doing so it is intended that Ray Sampling Density (sampling
  distance) can be a scalar and have a uniform meaning in all
  dimensions x, y, and z.  By Scaling the Model Matrix the raycaster
  would otherwise have to consider non-uniform scaling factors.

  A Space to Volume Transform Matrix is derived based on the Scale and
  the Offset (Pivot Point). The center is otherwise (0,0,0) which will
  be the lower-left-front corner of the volume.  Triggering 'Center'
  will compute the pivot point as Scale / 2.


  2. Cropping of the volume

  The Cropping will work by cropping the bounding box as well as being
  provided to the shader as volumeBBox[2][4].  If the volume matrix
  will rotate, swap or invert coordinates the cropping will not
  accurately reflect the min and max coordinates in the texture space.


  3. Self Contained Strategy

  After some discussions and considerations it was decided to make the
  renderer mostly self contained and to internally provide FBOs,
  copying of Depth Buffer, compositing of result onto current Frame
  Buffer, etc.


  4. External Depth Buffer for Depth Clipping

  Current implementation always makes a copy of the existing depth
  buffer in the active Frame Buffer (Object).  This is assumably the
  most common scenario.  In the extension it might be nice to support
  a direct reference to an external depth texture.
*/

#include <xip/inventor/coregl/SoXipGlowElement.h>

#include "SoXipDirectRaycaster.h"

#include <xip/utils/XipBasicOperators.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include <xip/inventor/core/SoXipClipPlaneElement.h>

#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>


#include <stdio.h>
#include <stdlib.h>

#ifndef MAXFLOAT
#  define MAXFLOAT     ((float)3.40282346638528860e+38)
#endif

#ifdef XIP_BASIC_OPS_NAMESPACE
using namespace XipBasicOps;
#endif

static const int indices[24] = {
    0, 2, 3, 1, 4, 5, 7, 6, 0, 1, 5, 4, 2, 6, 7, 3, 0, 4, 6, 2, 1, 3, 7, 5
};

static const float vertices[8][3] = {
    { 0.0, 0.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 1.0, 1.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0 },
    { 0.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0 }
};


static bool checkFramebufferStatus(const char * module, const char * label);

// Output OpenGL Error, if any...
#if defined(_DEBUG)
static inline void CheckGLError(const char * module)
{
    GLenum err = glGetError(); 

    if (err != GL_NO_ERROR)
    { 
        SoDebugError::postInfo(module, (char*)gluErrorString(err));
    }
}
#else
static inline void CheckGLError(const char *) { }
#endif

static inline unsigned int
allocateUnitAndBind(SoState * state, GLenum target, unsigned int texid)
{
    unsigned int unit = SoXipMultiTextureElement::getFreeUnit(state);

    SoXipMultiTextureElement::setUnit(state, unit);
    SoXipMultiTextureElement::bindTexture(state, target, texid);

    return unit;
}

static inline void
freeUnitAndUnbind(SoState * state, GLenum target, unsigned int unit)
{
    SoXipMultiTextureElement::setUnit(state, unit);
    SoXipMultiTextureElement::bindTexture(state, target, 0);
}


static inline void
setUniformSampler(int prog, const char * name, int value)
{
    int loc = glGetUniformLocation(prog, name);

    if (loc >= 0) glUniform1i(loc, value);
}

static inline void
setUniform1f(int prog, const char * name, float value)
{
    int loc = glGetUniformLocation(prog, name);

    if (loc >= 0) glUniform1f(loc, value);
}

static inline void
setUniform4fv(int prog, const char * name, int n, float * value)
{
    int loc = glGetUniformLocation(prog, name);

    if (loc >= 0) glUniform4fv(loc, n, value);
}




SO_NODE_SOURCE(SoXipDirectRaycaster);

void SoXipDirectRaycaster::initClass()
{
    SO_NODE_INIT_CLASS(SoXipDirectRaycaster, SoShape, "SoShape");

    SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
    SO_ENABLE(SoGLRenderAction, SoXipMultiTextureElement);
    SO_ENABLE(SoGLRenderAction, SoComplexityElement);
    SO_ENABLE(SoGLRenderAction, SoViewportRegionElement);
    SO_ENABLE(SoGLRenderAction, SoXipClipPlaneElement );
    SO_ENABLE(SoGLRenderAction, SoXipGLSLShaderProgramElement);

    SO_ENABLE(SoHandleEventAction, SoXipGLOWElement);
    SO_ENABLE(SoHandleEventAction, SoXipGLSLShaderProgramElement);
    SO_ENABLE(SoHandleEventAction, SoXipClipPlaneElement);

    SO_ENABLE(SoPickAction,     SoXipGLOWElement);
    SO_ENABLE(SoPickAction,     SoXipGLSLShaderProgramElement);
    SO_ENABLE(SoPickAction,     SoXipClipPlaneElement);
    SO_ENABLE(SoRayPickAction,  SoXipClipPlaneElement);
}



SoXipDirectRaycaster::SoXipDirectRaycaster()
{
    SO_NODE_CONSTRUCTOR(SoXipDirectRaycaster);

    SO_NODE_ADD_FIELD(scale, (SbVec3f(1, 1, 1)));
    SO_NODE_ADD_FIELD(pivot, (SbVec3f(0, 0, 0)));
    SO_NODE_ADD_FIELD(cropMin, (SbVec3f(0, 0, 0)));
    SO_NODE_ADD_FIELD(cropMax, (SbVec3f(1, 1, 1)));
    SO_NODE_ADD_FIELD(sampleSpacing, (float(0.01)));
    // SOXIP_NODE_ADD_NAMED_FIELD(mTFSuperSampling, superSampling, (uint32_t(0)));
    SO_NODE_ADD_FIELD(opacityUnitLength, (float(0.01)));
    SO_NODE_ADD_FIELD(opacity, (float(1.0)));
    SO_NODE_ADD_FIELD(ertThreshold, (float(0.98)));
    SO_NODE_ADD_FIELD(useComplexity, (false));

    SO_NODE_ADD_FIELD(fboMode, (FBO_NONE));
    SO_NODE_DEFINE_ENUM_VALUE(FBOMode, FBO_NONE);
    SO_NODE_DEFINE_ENUM_VALUE(FBOMode, FBO_RGBA8);
    SO_NODE_DEFINE_ENUM_VALUE(FBOMode, FBO_RGBA16F);
    SO_NODE_DEFINE_ENUM_VALUE(FBOMode, FBO_RGBA32F);
    SO_NODE_SET_SF_ENUM_TYPE(fboMode, FBOMode);
    SO_NODE_ADD_FIELD(fboDepth, (SbBool(false)));

    SO_NODE_ADD_FIELD(minMaxSize, (SbVec2s(32, 2048))); // Only applies if FBO is used

    SO_NODE_ADD_FIELD(rayOrigin, (FACES_FRONT));
    SO_NODE_DEFINE_ENUM_VALUE(RayOrigin, FACES_FRONT);
    SO_NODE_DEFINE_ENUM_VALUE(RayOrigin, FACES_BACK);
    SO_NODE_DEFINE_ENUM_VALUE(RayOrigin, TEXTURE_FRONT);
    SO_NODE_DEFINE_ENUM_VALUE(RayOrigin, TEXTURE_BACK);
    SO_NODE_DEFINE_ENUM_VALUE(RayOrigin, TEXTURE_FRONT_AND_BACK);
    SO_NODE_DEFINE_ENUM_VALUE(RayOrigin, FISHEYE_POLYGON);
    SO_NODE_SET_SF_ENUM_TYPE(rayOrigin, RayOrigin);

    SO_NODE_ADD_FIELD(depthClipping, (SbBool(false)));
    SO_NODE_ADD_FIELD(compositeProgramTag, (SbString("")));
    SO_NODE_ADD_FIELD(compositeDepthTest, (SbBool(false)));

    mDirtyGeometry = true;

    SoField * fields[] = {
	&scale, &pivot, &cropMin, &cropMax,
        &processMode, &processData
    };

    mInputSensorCount = sizeof(fields) / sizeof(SoField *);
    mInputSensors = new SoFieldSensor *[mInputSensorCount];

    for (int i = 0; i < mInputSensorCount; i++)
    {
        mInputSensors[i] = new SoFieldSensor(&fieldSensorCBFunc, this);
        mInputSensors[i]->attach(fields[i]);
        mInputSensors[i]->setPriority(0);
    }

    // Depth buffer texture
    mDepthTexID = 0;
    mDepthTexUnit = 0;

    // Framebuffer Object
    for (int i = 0; i < cmNumberOfFBOs; i++)
    {
        mFBOIDs[i] = 0;
        mFBOColorBufIDs[i] = 0;
        mFBODepthBufIDs[i] = 0;
    }

    mFrontFBOIdx = 0;
    mBackFBOIdx = 0;
    mFBOSize[0] = mFBOSize[1] = 0;

    mPrevFBO = 0;
    mPrevViewport[0] = 0;
    mPrevViewport[1] = 0;
    mPrevViewport[2] = 0;
    mPrevViewport[3] = 0;
    mPrevDrawBuffer = GL_BACK;
}

SoXipDirectRaycaster::~SoXipDirectRaycaster()
{
    for (int i = 0; i < mInputSensorCount; i++)
    {
        delete mInputSensors[i];
        mInputSensors[i] = 0;
    }

    delete mInputSensors;
    mInputSensors = 0;
    mInputSensorCount = 0;

    // Assertion: invoking process is responsible for providing valid GL Context
    deleteFBO();

    if (mDepthTexID)
    {
        deleteDepthTexture();
    }
}


void SoXipDirectRaycaster::fieldSensorCBFunc(void * user,
                                             SoSensor * sensor)
{
    SoXipDirectRaycaster * raycaster =
        reinterpret_cast<SoXipDirectRaycaster *>(user);
    SoFieldSensor * fieldSensor = static_cast<SoFieldSensor *>(sensor);

    raycaster->inputChanged(fieldSensor->getAttachedField());
}


void SoXipDirectRaycaster::inputChanged(SoField * changedField)
{
    if (changedField == &scale ||
        changedField == &pivot ||
        changedField == &cropMin ||
        changedField == &cropMax)
    {
        mDirtyGeometry = true;
    }
}


/*
  ------------------------------------------------------------------------
    virtual GLRender()

    Render the geometry to trigger the raycasting.
  ------------------------------------------------------------------------
*/

void SoXipDirectRaycaster::GLRender(SoGLRenderAction* action)
{
    /*
      If FBO cache is accurate and any depending content has not changed
      the FBO can be recycled/reused as a cache...

      Still need to sort out how and when it is to be recycled...
    */

    SoState * state = action->getState();

    /*
      This is actually a data update and should not be done in the
      rendering callback.  But OI doesn't have update callbacks...
    */
    if (mDirtyGeometry)
    {
        SbBox3f box;
        SbVec3f center;

        computeBBox(action, box, center);
    };

    float alpha = opacity.getValue();

    GLint prog;
    glGetIntegerv(GL_CURRENT_PROGRAM, &prog);

    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_TEXTURE_BIT);

    /*
      Rip a copy of the Depth Buffer if depth clipping is enabled
    */
    if (depthClipping.getValue())
    {
        setupDepthTexture(state);
    }
    else if (mDepthTexID)
    {
        deleteDepthTexture();
    }

    if (fboMode.getValue() != FBO_NONE) {
        setupFBO(state);
    }

    /* Setup Program Uniforms if there is a program */
    if (prog)
    {
        setupProgramUniforms(state, prog);
    }

    glEnable(GL_BLEND);

    // Only render the backfaces if there is no program...
    // and it makes sense since opacity is less than 1.0
    if (prog == 0)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);
        drawProxyGeometry(alpha);

        glCullFace(GL_BACK);
        drawProxyGeometry(alpha);
    } else {
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        int rayorigsrc = 0;

        switch (rayOrigin.getValue())
        {
        case FACES_FRONT:
        case TEXTURE_FRONT:
        case TEXTURE_FRONT_AND_BACK:
        default:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            break;

        case FACES_BACK:
        case TEXTURE_BACK:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            glDisable(GL_DEPTH_TEST);
            break;

        case FISHEYE_POLYGON:
            glDisable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);
            break;
        }

        drawProxyGeometry(alpha);
    }

    if (fboMode.getValue() != FBO_NONE) {
        releaseFBO(state);
    }

    if (depthClipping.getValue())
    {
        releaseDepthTexture(state);
    }

    if (fboMode.getValue() != FBO_NONE) {
        drawFBO(state);
    }

    // Restore Program used upon entry
    glUseProgram(prog);

    glPopAttrib();
}


void SoXipDirectRaycaster::drawProxyGeometry(float alpha)
{
    glDisable(GL_LIGHTING);

    if (rayOrigin.getValue() != FISHEYE_POLYGON)
    {
        glBegin(GL_QUADS);

        for (int i = 0; i < 24; i++)
        {
            /* Assign the volume domain as color */
            const float * v = vertices[indices[i]];
            glColor4f(v[0], v[1], v[2], alpha);
            glTexCoord3fv(v);
            glVertex3fv(&mVertices[indices[i]][0]);
        }

        glEnd();
    }
    else
    {
        // Expect the vertex shader to take care of proper transformation....
        glBegin(GL_QUADS);
        glColor4f(1.0, 1.0, 1.0, alpha);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-1.0, -1.0);

        glTexCoord2f(0.0, 1.0);
        glVertex2f(-1.0, 1.0);

        glTexCoord2f(1.0, 1.0);
        glVertex2f(1.0, 1.0);

        glTexCoord2f(1.0, 0.0);
        glVertex2f(1.0, -1.0);
        glEnd();
    }
}


void SoXipDirectRaycaster::setupDepthTexture(SoState * state)
{
    if (mDepthTexID == 0)
    {
        glGenTextures(1, &mDepthTexID);
        //SoDebugError::postInfo("", "  Generated texture ID");
    }

    int fbsize[4];

    glGetIntegerv(GL_VIEWPORT, fbsize);

    mDepthTexUnit = allocateUnitAndBind(state, GL_TEXTURE_2D, mDepthTexID);

    /*
      Make a copy of the current frame buffer if requested
      We assume NPOT suppport!!!
      Specific DEPTH COMPONENT not given - see what happens here first...
    */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // This is a must!!!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);

    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                     fbsize[0], fbsize[1], fbsize[2], fbsize[3], 0);

    CheckGLError("SoXipDirectRaycaster::setupDepthTexture");
}


void SoXipDirectRaycaster::releaseDepthTexture(SoState * state)
{
    freeUnitAndUnbind(state, GL_TEXTURE_2D, mDepthTexUnit);
}


void SoXipDirectRaycaster::deleteDepthTexture()
{
    //SoDebugError::postInfo("deleteDepthTexture", "Deleting depth texture");

    glDeleteTextures(1, &mDepthTexID);

    mDepthTexID = 0;
}


static GLenum fboModeFormatMap[SoXipDirectRaycaster::FBO_NUMBER_OF_MODES] =
{
    GL_RGBA,                    // FBO_NONE : Sort of error
    GL_RGBA,                    // FBO_RGBA8
    GL_RGBA_FLOAT16_ATI,        // FBO_RGBA16F
    GL_RGBA_FLOAT32_ATI,        // FBO_RGBA32F
};

static GLenum fboColorAttachment[2] =
{
    GL_COLOR_ATTACHMENT0_EXT,
    GL_COLOR_ATTACHMENT1_EXT,
};

void SoXipDirectRaycaster::setupFBO(SoState * state)
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &mPrevFBO);
    glGetIntegerv(GL_VIEWPORT, mPrevViewport);
    glGetIntegerv(GL_DRAW_BUFFER, &mPrevDrawBuffer);

    bool stereo = false;
    bool attach = false;
    int depth = fboDepth.getValue();

    int nbufs = 1 + int(stereo);        // 1 for mono, 2 for stereo
    int bufidx = 0;                     // 0 for left, 1 for right (if stereo)

    unsigned int * fboIDs = mFBOIDs + mBackFBOIdx;
    unsigned int * colorIDs = mFBOColorBufIDs + mBackFBOIdx;
    unsigned int * depthIDs = mFBODepthBufIDs + mBackFBOIdx;
    unsigned int * fboSize = mFBOSize;

    unsigned int & fboID(fboIDs[bufidx]);
    unsigned int & colorID(colorIDs[bufidx]);
    unsigned int & depthID(depthIDs[bufidx]);

    if (fboIDs[0] <= 0)
    {
        glGenFramebuffersEXT(nbufs, fboIDs);
        glGenTextures(nbufs, colorIDs);
        if (depth) glGenTextures(nbufs, depthIDs);

        attach = true;          // Need to attach textures...
    }

    int target_width = mPrevViewport[2];
    int target_height = mPrevViewport[3];

    // MinMax Rescaling
    float maxscale = min(minMaxSize.getValue()[1] / float(target_width),
                         minMaxSize.getValue()[1] / float(target_height));
    float minscale = max(minMaxSize.getValue()[0] / float(target_width),
                         minMaxSize.getValue()[0] / float(target_height));

    if (maxscale < 1.0)
    {
        // Scale down...
        target_width = target_width * maxscale;
        target_height = target_height * maxscale;
    }
    else if (minscale > 1.0)
    {
        // Scale up...
        target_width = target_width * minscale;
        target_height = target_height * minscale;
    }

    if ((int)fboSize[0] != target_width || (int)fboSize[1] != target_height)
    {
        // We just need to use a unit temporary...
        SoXipMultiTextureElement::setUnit(state, 0);

        GLenum intFormat = fboModeFormatMap[fboMode.getValue()];

        // Resize both textures...
        for (int i = 0; i < nbufs; i++)
        {
            glBindTexture(GL_TEXTURE_2D, colorIDs[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, intFormat, target_width, target_height,
                         0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

            if (fboDepth.getValue())
            {
                glBindTexture(GL_TEXTURE_2D, depthIDs[i]);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
                glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                             target_width, target_height,
                             0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
            }
        }

        fboSize[0] = target_width;
        fboSize[1] = target_height;
        
        SoXipMultiTextureElement::bindTextureCurrUnit(state);

        // Not sure if we need to re-attach if we've changed the size
        // of the textures.
        // attach = true;
    }

    if (attach)
    {
        bool failed = false;

        for (int i = 0; i < nbufs; i++)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboIDs[i]);

            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
                                      GL_COLOR_ATTACHMENT0_EXT,
                                      GL_TEXTURE_2D, colorIDs[i], 0);

            if (depth)
            {
                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
                                          GL_DEPTH_ATTACHMENT_EXT,
                                          GL_TEXTURE_2D, depthIDs[i], 0);
            }

            if (!checkFramebufferStatus("SoXipDirectRaycaster", "Attached Textures"))
            {
                failed = true;
            }
        }

        if (failed)
        {
            releaseFBO(state);
            deleteFBO();
            fboMode.setValue(FBO_NONE);
            SoDebugError::postInfo("SoXipDirectRaycaster",
                                   "FBO Failed - rendering to default framebuffer");

            return;
        }

        CheckGLError("SoXipDirectRaycaster::setupFBO[glFramebufferTexture2DEXT]");
    }

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboIDs[bufidx]);
    glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glViewport(0, 0, target_width, target_height);

    CheckGLError("SoXipDirectRaycaster::setupFBO[glDrawBuffer]");

    glClear(GL_COLOR_BUFFER_BIT | (depth ? GL_DEPTH_BUFFER_BIT : 0));
}


void SoXipDirectRaycaster::releaseFBO(SoState * state)
{
    // Restore previous framebuffer and viewport setting
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mPrevFBO);

    glViewport(mPrevViewport[0], mPrevViewport[1],
               mPrevViewport[2], mPrevViewport[3]);

    glDrawBuffer(mPrevDrawBuffer);

    mPrevFBO = 0;
}


void SoXipDirectRaycaster::deleteFBO()
{
    //SoDebugError::postInfo("deleteFBO", "Deleting FBO");

    for (int i = 0; i < cmNumberOfFBOs; i++)
    {
        if (mFBOIDs[i]) glDeleteFramebuffersEXT(1, &mFBOIDs[i]);
        if (mFBOColorBufIDs[i]) glDeleteTextures(1, &mFBOColorBufIDs[i]);
        if (mFBODepthBufIDs[i]) glDeleteTextures(1, &mFBODepthBufIDs[i]);

        mFBOIDs[i] = 0;
        mFBOColorBufIDs[i] = 0;
        mFBODepthBufIDs[i] = 0;
    }
}


/*
  ------------------------------------------------------------------------
    drawFBO - Redraw the the FBO onto the background framebuffer

    If a depth buffer was attached to the FBO and a shader program is
    provided they will be bound. In addition, if the original depth
    buffer was copied (depthCulling enabled) it will be bound as well.

    Note! We need to go through all the states we modify to make sure
    we are restoring everything. / Patric Ljung - Mar 14, 2008
  ------------------------------------------------------------------------
*/

void SoXipDirectRaycaster::drawFBO(SoState * state)
{
    CheckGLError("SoXipDirectRaycaster::drawFBO - entry");

    // Draw polygon over original FB
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    int bufidx = mFrontFBOIdx + 0; // Left or Right?
    int depthComposite = false;

    int prog =
        SoXipGLSLShaderProgramElement::getProgramID(state,
                                                    compositeProgramTag.getValue());

    if (compositeProgramTag.getValue() != "" && prog == 0)
    {
        SoDebugError::postInfo("SoXipDirectRaycaster::drawFBO",
                               "Failed to retrieve Compositing Shader Program: %s",
                               compositeProgramTag.getValue().getString());
    }

    if (mFBODepthBufIDs[bufidx] > 0 && prog)
    {
        depthComposite = true;
        glUseProgram(prog);

        setUniformSampler(prog, "colorTex", 0);
        setUniformSampler(prog, "depthTex", 1);
        setUniformSampler(prog, "bgDepthTex", 2);
    }
    else
    {
        glUseProgram(0);
    }

    SoXipMultiTextureElement::setUnit(state, 0);
    glBindTexture(GL_TEXTURE_2D, mFBOColorBufIDs[bufidx]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    if (depthComposite)
    {
        glDisable(GL_TEXTURE_2D);

        SoXipMultiTextureElement::setUnit(state, 1);
        glBindTexture(GL_TEXTURE_2D, mFBODepthBufIDs[bufidx]);

        if (mDepthTexID)
        {
            SoXipMultiTextureElement::setUnit(state, 2);
            glBindTexture(GL_TEXTURE_2D, mDepthTexID);
        }
    }

    CheckGLError("SoXipDirectRaycaster::drawFBO - set uniforms");

    if (compositeDepthTest.getValue())
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    CheckGLError("SoXipDirectRaycaster::drawFBO - GL_DEPTH_TEST");

#if 0
    SbViewportRegion vpRegion = SoViewportRegionElement::get(state);
    SbVec2s vpSize = vpRegion.getViewportSizePixels();
    SbVec2s vpOrigin = vpRegion.getViewportOriginPixels();
    glViewport(vpOrigin[0], vpOrigin[1], vpSize[0], vpSize[1]);
#else
    glViewport(mPrevViewport[0], mPrevViewport[1], mPrevViewport[2], mPrevViewport[3]);
#endif

    CheckGLError("SoXipDirectRaycaster::drawFBO - glViewport");

    glColor4f(1.0f, 0.8f, 0.5f, 0.5f);
    glDisable(GL_LIGHTING);
    CheckGLError("SoXipDirectRaycaster::drawFBO - GL_LIGHTING");

    glDisable(GL_CULL_FACE);
    CheckGLError("SoXipDirectRaycaster::drawFBO - GL_CULL_FACE");

    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2d(1.0, 0);
    glVertex2f(1.0f, -1.0f);
    glTexCoord2d(1.0, 1.0);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2d(0, 1.0);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    CheckGLError("SoXipDirectRaycaster::drawFBO - GL_QUADS");

    // Restore the textures bound to current texture unit
    if (depthComposite)
    {
        if (mDepthTexID)
        {
            SoXipMultiTextureElement::setUnit(state, 2);
            SoXipMultiTextureElement::bindTextureCurrUnit(state);

            CheckGLError("SoXipDirectRaycaster::drawFBO - Restore Unit 2");
        }

        SoXipMultiTextureElement::setUnit(state, 1);
        SoXipMultiTextureElement::bindTextureCurrUnit(state);

        CheckGLError("SoXipDirectRaycaster::drawFBO - Restore Unit 1");
    }

    SoXipMultiTextureElement::setUnit(state, 0);
    SoXipMultiTextureElement::bindTextureCurrUnit(state);

    CheckGLError("SoXipDirectRaycaster::drawFBO - Restore Unit 0");

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    CheckGLError("SoXipDirectRaycaster::drawFBO - Pop Projection");

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    CheckGLError("SoXipDirectRaycaster::drawFBO - end");
}

void SoXipDirectRaycaster::setupProgramUniforms(SoState * state, int prog)
{
    /* Setup the geometry bounding box, array of vec4 */
    int geobboxloc = glGetUniformLocation(prog, "geometryBBox");

    if (geobboxloc >= 0)
    {
        const SbVec3f & minv(mGeometryBBox.getMin());
        const SbVec3f & maxv(mGeometryBBox.getMax());

        float bbox[8] = {
            minv[0], minv[1], minv[2], 1.0,
            maxv[0], maxv[1], maxv[2], 1.0
        };

        glUniform4fv(geobboxloc, 2, bbox);
    }

    /* Setup the volume (texture space) bounding box, array of vec4 */
    int volbboxloc = glGetUniformLocation(prog, "volumeBBox");

    if (volbboxloc >= 0)
    {
        const SbVec3f & minv(cropMin.getValue());
        const SbVec3f & maxv(cropMax.getValue());

        float bbox[8] = {
            minv[0], minv[1], minv[2], 1.0,
            maxv[0], maxv[1], maxv[2], 1.0
        };

        glUniform4fv(volbboxloc, 2, bbox);
    }

    /*
      A normalized texture coordinate is computes as:
      texcoord = coord * volScale + volOffset;
    */
    const SbVec3f & sc(scale.getValue());
    const SbVec3f & pv(pivot.getValue());

    int volscaleloc = glGetUniformLocation(prog, "volScale");

    if (volscaleloc >= 0)
    {
        float volscale[3] = {
            1.0 / sc[0], 1.0 / sc[1], 1.0 / sc[2]
        };

        glUniform3fv(volscaleloc, 1, volscale);
    }

    int voloffsetloc = glGetUniformLocation(prog, "volOffset");

    if (voloffsetloc >= 0)
    {
        float voloffset[3] = {
            pv[0] / sc[0], pv[1] / sc[1], pv[2] / sc[2]
        };

        glUniform3fv(voloffsetloc, 1, voloffset);
    }

    /*
      Setup Raycaster Viewport size (might be different from parents)
    */
    int viewportloc = glGetUniformLocation(prog, "viewport");

    if (viewportloc >= 0)
    {
        int viewport[4];

        glGetIntegerv(GL_VIEWPORT, viewport);

        glUniform4iv(viewportloc, 1, viewport);
    }

    /* Setup type of ray origin, from face attributes or texture, front or back */
    int rayorigsrcloc = glGetUniformLocation(prog, "rayOriginSource");
    int rayorigtexloc = glGetUniformLocation(prog, "rayOriginTexture");

    if (rayorigsrcloc >= 0 || rayorigtexloc >= 0)
    {
        int tex = 0;
        int src = 0;

        switch (rayOrigin.getValue())
        {
        case FACES_FRONT:
            tex = 0;
            src = 0;
            break;

        case FACES_BACK:
            tex = 0;
            src = 1;
            break;

        case TEXTURE_FRONT:
            tex = 1;
            src = 0;
            break;

        case TEXTURE_BACK:
            tex = 1;
            src = 1;
            break;

        case TEXTURE_FRONT_AND_BACK:
            tex = 1;
            src = 2;
            break;

        case FISHEYE_POLYGON:
            tex = 0;
            src = 3;
            break;

        default: // Default is Faces Front
            tex = 0;
            src = 0;
            break;
        }

        if (rayorigsrcloc >= 0)
        {
            glUniform1i(rayorigsrcloc, src);
        }

        if (rayorigtexloc >= 0)
        {
            glUniform1i(rayorigtexloc, tex);
        }
    }

    /*
      TF Super Sampling, support for additional samples of TF between
      volume samples
    */
#if 0
    int supersmplloc = glGetUniformLocation(prog, "superSampling");
    int oneoversuperloc = glGetUniformLocation(prog, "oneOverSuperSampling");

    int tfsupersampling = 0; // No additional TF sampling

    if (supersmplloc >= 0)
    {
        tfsupersampling = mTFSuperSampling.getValue();

        glUniform1i(supersmplloc, tfsupersampling);

        if (oneoversuperloc >= 0)
        {
            glUniform1f(oneoversuperloc, 1.0 / float(1 + tfsupersampling));
        }
    }
#endif

    /* Sample Spacing, in world space units [mm?] */
    int smplSpacingLoc = glGetUniformLocation(prog, "sampleSpacing");
    float smplSpacing = sampleSpacing.getValue(); /*  / float(1 + tfsupersampling); */

    if (smplSpacingLoc >= 0)
    {
        glUniform1f(smplSpacingLoc, smplSpacing);
    }

    /*
      TF Opacity Unit Length, in world space units [mm?]
      If different from sample density
    */
    int tfOpacityAdjLoc = glGetUniformLocation(prog, "tfOpacityAdj");

    if (tfOpacityAdjLoc >= 0)
    {
        float tfunitlen = opacityUnitLength.getValue();

        float opacityAdj = smplSpacing / (tfunitlen /* * float(1 + tfsupersampling) */);

        glUniform1f(tfOpacityAdjLoc, opacityAdj);
    }

    /*
      Early Ray Termination Threshold
    */
    int ertThresholdLoc = glGetUniformLocation(prog, "ertThreshold");

    if (ertThresholdLoc >= 0)
    {
        float threshold = ertThreshold.getValue();

        glUniform1f(ertThresholdLoc, threshold);
    }

    /*
      Rendering Complexity
    */
    int complexLoc = glGetUniformLocation(prog, "renderingComplexity");

    if (complexLoc >= 0)
    {
        float complexity = 1.0;

        if (useComplexity.getValue()) {
            // Inventor complexity usually ranges from 0.1 -> 0.5, remap to 0.2 -> 1.0
            complexity = 2.0 * SoComplexityElement::get(state);
        }

        glUniform1f(complexLoc, complexity);
    }

    /* Setup use of depth texture */
    int depthClipLoc = glGetUniformLocation(prog, "depthClippingEnabled");
    int depthTexLoc = glGetUniformLocation(prog, "depthTexture");
    int depthClipEnabled = static_cast<int>(depthClipping.getValue());

    if (depthClipLoc >= 0)
    {
        glUniform1i(depthClipLoc, depthClipEnabled);
    }

    if (depthTexLoc >= 0 && depthClipEnabled)
    {
#if 0
        char buffer[256] = "";
        _snprintf(buffer, 256, "Setting sampler uniform: depthTexture = %d",
                  static_cast<int>(mDepthTexUnit.getValue()));
        SoDebugError::postInfo("setupProgramUniforms", buffer);
#endif
        glUniform1i(depthTexLoc, mDepthTexUnit);
    }

    /* Fisheye Mode? */
    int fisheyeLoc = glGetUniformLocation(prog, "fisheyeMode");

    if (fisheyeLoc >= 0)
    {
        int fisheyeMode = rayOrigin.getValue() == FISHEYE_POLYGON;

        glUniform1i(fisheyeLoc, fisheyeMode);
    }
}

/*
  ------------------------------------------------------------------------
    virtual generatePrimitives()

    Generate the primitives... update vertices
  ------------------------------------------------------------------------
*/

void SoXipDirectRaycaster::generatePrimitives(SoAction * action)
{
    //SoDebugError::postInfo("", "SoXipDirectRaycaster::generatePrimitives:");

    const SbVec3f & sc = scale.getValue();
    const SbVec3f & pv = pivot.getValue();
    const SbVec3f & minv = cropMin.getValue();
    const SbVec3f & maxv = cropMax.getValue();

    for (int i = 0; i < 8; i++)
    {
        mVertices[i][0] = clamp(vertices[i][0], minv[0], maxv[0]) *
            sc[0] - pv[0];
        mVertices[i][1] = clamp(vertices[i][1], minv[1], maxv[1]) *
            sc[1] - pv[1];
        mVertices[i][2] = clamp(vertices[i][2], minv[2], maxv[2]) *
            sc[2] - pv[2];
    }

    mDirtyGeometry = false;
}

/*
  ------------------------------------------------------------------------
    virtual computeBBox()

    Compute the bounding box for scaled and translated proxy geometry.
  ------------------------------------------------------------------------
*/

/*
  Should actually use the largest positive and negative numbers...
*/

void SoXipDirectRaycaster::computeBBox(SoAction * action,
                                       SbBox3f & box, SbVec3f & center)
{
    //SoDebugError::postInfo("", "SoXipDirectRaycaster::computeBBox:");

    if (mDirtyGeometry) generatePrimitives(action);

    SbVec3f & minv(box.getMin());
    SbVec3f & maxv(box.getMax());

    minv[0] = MAXFLOAT;
    minv[1] = MAXFLOAT;
    minv[2] = MAXFLOAT;

    maxv[0] = -MAXFLOAT;
    maxv[1] = -MAXFLOAT;
    maxv[2] = -MAXFLOAT;

    for (int i = 0; i < 8; i++)
    {
        center[0] += mVertices[i][0];
        center[1] += mVertices[i][1];
        center[2] += mVertices[i][2];

        minv[0] = min(minv[0], mVertices[i][0]);
        minv[1] = min(minv[1], mVertices[i][1]);
        minv[2] = min(minv[2], mVertices[i][2]);

        maxv[0] = max(maxv[0], mVertices[i][0]);
        maxv[1] = max(maxv[1], mVertices[i][1]);
        maxv[2] = max(maxv[2], mVertices[i][2]);
    }

    center[0] /= 8.0;
    center[1] /= 8.0;
    center[2] /= 8.0;

    // Save the bounding box
    mGeometryBBox = box;
}


bool checkFramebufferStatus(const char * module, const char * label)
{
    bool isOk = false;
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE_EXT:
        isOk = true;
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
        SoDebugError::postInfo(module, "%s: "
                               "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT", label);
        break;

    case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
        SoDebugError::postInfo(module, "%s: "
                               "GL_FRAMEBUFFER_UNSUPPORTED_EXT", label);
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
        SoDebugError::postInfo(module, "%s: "
                               "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT", label);
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        SoDebugError::postInfo(module, "%s: "
                               "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT", label);
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
        SoDebugError::postInfo(module, "%s: "
                               "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT", label);
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
        SoDebugError::postInfo(module, "%s: "
                               "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT", label);
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
        SoDebugError::postInfo(module, "%s: "
                               "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT", label);
        break;

    default:
        SoDebugError::postInfo(module, "%s: "
                               "Unknwon Frambuffer Object fault: 0x%04x", label, status);
        break;
    }

    return isOk;
} 

#ifdef UNDEFINE_M_INF
#  undef M_INF
#  undef UNDEFINE_M_INF
#endif


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
//   c-basic-offset: 4
//   c-indentation-style: stroustrup
// End:
