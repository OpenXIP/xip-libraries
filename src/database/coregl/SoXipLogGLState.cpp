#include <xip/system/standard.h>
#include "SoXipLogGLState.h"

#include <Inventor/actions/SoGLRenderAction.h>
#ifndef linux
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glext.h>
#endif
#include <xip/inventor/coregl/SoXipGlowElement.h>

#if defined(WINDOWS) || defined(_MSC_VER)
# pragma warning(disable:4996)
#endif 

SO_NODE_SOURCE(SoXipLogGLState);



//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipLogGLState::initClass()
{
	SO_NODE_INIT_CLASS(SoXipLogGLState, SoNode, "Node");	

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
}

//////////////////////////////////////////////////////////////////////////////////////////
///
SoXipLogGLState::SoXipLogGLState() :
mCount(0)
{
	SO_NODE_CONSTRUCTOR(SoXipLogGLState);

	SO_NODE_ADD_FIELD(log, (TRUE));
	SO_NODE_ADD_FIELD(filename, (""));
}

//////////////////////////////////////////////////////////////////////////////////////////
///
SoXipLogGLState::~SoXipLogGLState()
{
}

#define LOG_BOOL_FIELD(name)				\
  ip[0] = glIsEnabled(name);			\
  fprintf(out, "%-*s%d\n", space, #name ":", ip[0])

#define LOG_INT1_FIELD(name)					\
  glGetIntegerv(name, ip);					\
  fprintf(out, "%-*s%d\n", space, #name ":", ip[0])

#define LOG_FLOAT1_FIELD(name)					\
  glGetFloatv(name, fp);					\
  fprintf(out, "%-*s%f\n", space, #name ":", fp[0])

#define LOG_INT4_FIELD(name)					\
  glGetIntegerv(name, ip);					\
  fprintf(out, "%-*s%d, %d, %d, %d\n", space, #name ":",	\
	  ip[0], ip[1], ip[2], ip[3])

#define LOG_BOOL4_FIELD(name)					\
  glGetBooleanv(name, bp);					\
  fprintf(out, "%-*s%d, %d, %d, %d\n", space, #name ":",	\
	  bp[0], bp[1], bp[2], bp[3])

#define LOG_FLOAT2_FIELD(name)					\
  glGetFloatv(name, fp);					\
  fprintf(out, "%-*s%f, %f\n", space, #name ":", fp[0], fp[1])

#define LOG_FLOAT4_FIELD(name)					\
  glGetFloatv(name, fp);					\
  fprintf(out, "%-*s%f, %f, %f, %f\n", space, #name ":",	\
	  fp[0], fp[1], fp[2], fp[3])

#define LOG_FLOAT4x4_FIELD(name)						\
  glGetFloatv(name, fp);						\
  fprintf(out, "%-*s%f, %f, %f, %f, %f, %f, %f, %f, "			\
	  "%f, %f, %f, %f, %f, %f, %f, %f\n", space, #name ":",		\
	  fp[0], fp[1], fp[2], fp[3], fp[4], fp[5], fp[6], fp[7],	\
	  fp[8], fp[9], fp[10], fp[11], fp[12], fp[13], fp[14], fp[15])

#define LOG_CLIP_FIELD(name)					\
  glGetClipPlane(name, dp);					\
  fprintf(out, "%-*s%d: %f, %f, %f, %f\n", space, #name ":",	\
	  glIsEnabled(name), dp[0], dp[1], dp[2], dp[3])

#define LOG_TEXTURE(i) {						\
    glActiveTexture(GL_TEXTURE0 + i);					\
    glGetIntegerv(GL_TEXTURE_BINDING_1D, ip);				\
    int tex1d = ip[0];						\
    glGetIntegerv(GL_TEXTURE_BINDING_2D, ip);				\
    int tex2d = ip[0];						\
    glGetIntegerv(GL_TEXTURE_BINDING_3D, ip);				\
    int tex3d = ip[0];						\
    int on1d = glIsEnabled(GL_TEXTURE_1D);				\
    int on2d = glIsEnabled(GL_TEXTURE_2D);				\
    int on3d = glIsEnabled(GL_TEXTURE_3D);				\
    fprintf(out, "GL_TEXTURE%-2d:%-*s1D %3s (%d), 2D %3s (%d), "	\
	    "3D %3s (%d)\n", i, space - 13, "",				\
	    (on1d ? "on" : "off"), tex1d,				\
	    (on2d ? "on" : "off"), tex2d,				\
	    (on3d ? "on" : "off"), tex3d);				\
  }

//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipLogGLState::GLRender(SoGLRenderAction * action)
{
	SoState *state = action->getState();
	const char * basename = filename.getValue().getString();
	int baselen = filename.getValue().getLength();

	if (log.getValue() == TRUE && basename && basename[0])
	{
 	        // Mark we've already logged
		log.setValue(FALSE);

		// create log file
	        int maxlen = baselen + 32;
	        char * ssFilename = new char[maxlen];
		snprintf(ssFilename, maxlen, "%s_%d.log", basename, mCount);

		FILE * out = fopen(ssFilename, "w");

		if (!out)
		{
		        delete ssFilename;
			return;
		}

		/** OpenGL **/
		GLint ip[16] = { 0 };
		GLboolean bp[16] = { 0 };
		GLfloat fp[16] = { 0.0 };
		GLdouble dp[16] = { 0.0 };

		const int space = 24;

		// Transforms
		LOG_FLOAT4x4_FIELD(GL_COLOR_MATRIX);
		LOG_FLOAT4x4_FIELD(GL_MODELVIEW_MATRIX);
		LOG_FLOAT4x4_FIELD(GL_PROJECTION_MATRIX);
		LOG_FLOAT4x4_FIELD(GL_TEXTURE_MATRIX);
		LOG_INT4_FIELD(GL_VIEWPORT);
		LOG_FLOAT2_FIELD(GL_DEPTH_RANGE);
		LOG_CLIP_FIELD(GL_CLIP_PLANE0);
		LOG_CLIP_FIELD(GL_CLIP_PLANE1);
		LOG_CLIP_FIELD(GL_CLIP_PLANE2);
		LOG_CLIP_FIELD(GL_CLIP_PLANE3);
		LOG_CLIP_FIELD(GL_CLIP_PLANE4);
		LOG_CLIP_FIELD(GL_CLIP_PLANE5);

		// Coloring
		LOG_BOOL_FIELD(GL_FOG);
		LOG_INT1_FIELD(GL_SHADE_MODEL);
		LOG_FLOAT4_FIELD(GL_CURRENT_COLOR);

		// Lighting
		LOG_BOOL_FIELD(GL_LIGHTING);
		LOG_BOOL_FIELD(GL_COLOR_MATERIAL);
		LOG_BOOL_FIELD(GL_LIGHT0);
		LOG_BOOL_FIELD(GL_LIGHT1);
		LOG_BOOL_FIELD(GL_LIGHT2);
		LOG_BOOL_FIELD(GL_LIGHT3);
		LOG_BOOL_FIELD(GL_LIGHT4);
		LOG_BOOL_FIELD(GL_LIGHT5);
		LOG_BOOL_FIELD(GL_LIGHT6);
		LOG_BOOL_FIELD(GL_LIGHT7);

		// Rasterization
		LOG_BOOL_FIELD(GL_POINT_SMOOTH);
		LOG_FLOAT1_FIELD(GL_POINT_SIZE);
		LOG_FLOAT1_FIELD(GL_POINT_SIZE_MIN);
		LOG_FLOAT1_FIELD(GL_POINT_SIZE_MAX);
		LOG_BOOL_FIELD(GL_LINE_SMOOTH);
		LOG_FLOAT1_FIELD(GL_LINE_WIDTH);
		LOG_BOOL_FIELD(GL_LINE_STIPPLE);
		LOG_BOOL_FIELD(GL_POLYGON_SMOOTH);
		LOG_BOOL_FIELD(GL_CULL_FACE);
		LOG_INT1_FIELD(GL_CULL_FACE_MODE);
		LOG_INT1_FIELD(GL_FRONT_FACE);
		LOG_INT1_FIELD(GL_POLYGON_MODE);

		// Texturing
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, ip);
		int maxunits = ip[0];

		for (int i = 0; i < maxunits; i++)
		{
		        LOG_TEXTURE(i);
		}

		// Pixel Operations
		LOG_BOOL_FIELD(GL_SCISSOR_TEST);
		LOG_BOOL_FIELD(GL_ALPHA_TEST);
		LOG_INT1_FIELD(GL_ALPHA_TEST_FUNC);
		LOG_BOOL_FIELD(GL_STENCIL_TEST);
		LOG_INT1_FIELD(GL_STENCIL_FUNC);
		LOG_BOOL_FIELD(GL_DEPTH_TEST);
		LOG_INT1_FIELD(GL_DEPTH_FUNC);
		LOG_BOOL_FIELD(GL_BLEND);

		LOG_INT1_FIELD(GL_BLEND_SRC_RGB);
		LOG_INT1_FIELD(GL_BLEND_SRC_ALPHA);
		LOG_INT1_FIELD(GL_BLEND_DST_RGB);
		LOG_INT1_FIELD(GL_BLEND_DST_ALPHA);
		LOG_INT1_FIELD(GL_BLEND_EQUATION);
		LOG_FLOAT4_FIELD(GL_BLEND_COLOR);

		LOG_INT1_FIELD(GL_DRAW_BUFFER);
		LOG_BOOL4_FIELD(GL_COLOR_WRITEMASK);
		LOG_INT1_FIELD(GL_DEPTH_WRITEMASK);

		// Shader Programs
		LOG_INT1_FIELD(GL_CURRENT_PROGRAM);

		fclose(out);

		
		/** Inventor **/
		snprintf(ssFilename, maxlen, "%s_IV_%d.log", basename, mCount);

		out = fopen(ssFilename, "w");

		if (!out)
		{
		        delete ssFilename;
			return;
		}

		state->print(out);
		fclose(out);

		mCount++;
	}
}


