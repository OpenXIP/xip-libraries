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

#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>

#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SoXipData.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipMFDataImage.h>
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/SoXipKit.h>
#include <xip/inventor/coregl/SoXipShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipBlendFuncElement.h>
#include <xip/inventor/coregl/SoXipFrameRate.h>
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/coregl/SoXipSetTransform.h>
#include <xip/inventor/coregl/SoXipBufferMaskElement.h>
#include <xip/inventor/coregl/SoXipCaptureImage.h>
#include <xip/inventor/coregl/SoXipDepthTestElement.h>
#include <xip/inventor/coregl/SoXipDrawImage.h>
#include <xip/inventor/coregl/SoXipFramebufferFlip.h>
#include <xip/inventor/coregl/SoXipGetTransform.h>
#include <xip/inventor/coregl/SoXipMultiplyMatrices.h>
#include <xip/inventor/coregl/SoXipOffscreenRenderer.h>

#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>

#include "SoXipClipPlaneKit.h"
#include "SoXipBlendFunc.h"
#include "SoXipBufferMask.h"
#include "SoXipUniformVariable.h"
#include "SoXipLoadShaders.h"
#include "SoXipLogGLState.h"
#include "SoXipDepthTest.h"
#include "SoXipDrawClipPlane.h"
#include "SoXipClearBuffer.h"
#include "SoXipFramebufferGroup.h"
#include "SoXipTextureUnit.h"
#include "SoXipLutTexture.h"
#include "SoXipOpenGLError.h"
#include "SoXipGLStringMarker.h"

#include "SoXipCube.h"
#include "SoXipDecomposeMFInt32.h"
#include "SoXipDecomposeMFMatrix.h"
#include "SoXipBindTextures.h"
#include "SoXipGetCameraProperties.h"

#include "SoXipClearFbo.h"
#include "SoXipFbo.h"
#include "SoXipFboAttachColor.h"
#include "SoXipFboAttachColor3D.h"
#include "SoXipFboAttachDepth.h"
#include "SoXipFboAttachDepth3D.h"
#include "SoXipPingPongFlip.h"
#include "SoXipPingPong.h"

#include "SoXipGLSLComponentProgram.h"
#include "SoXipGLSLLoadComponents.h"
#include "SoXipGLSLPrograms.h"
#include "SoXipGLSLUniformGroup.h"
#include "SoXipGLSLUseProgram.h"

#include  "SoXipTransparentGeometryRenderer.h"

int XIPIVCOREGL_API xipivcoregl_init()
{
	static bool isInit = false;
	if(isInit)
		return 1;
	isInit = true;

	xipivcore_init();

	//initialize elements first
    SoXipGLOWElement::initClass();
	SoXipShaderProgramElement::initClass();
	SoXipGLSLShaderProgramElement::initClass();
    SoXipFramebufferElement::initClass();
    SoXipBlendFuncElement::initClass();
    SoXipBufferMaskElement::initClass();
    SoXipDepthTestElement::initClass();
   	SoXipDrawBuffersElement::initClass();
   	SoXipFboElement::initClass();

	//then initialize rest
	SoXipTextureUnit::initClass();
	
	SoXipUniformVariable::initClass();
	SoXipUniformMatrix3::initClass();
	SoXipUniformMatrix4 ::initClass();
	SoXipUniformInt::initClass();
	SoXipUniformVec4f::initClass();
	SoXipUniformVec3f::initClass();
	SoXipUniformVec2f ::initClass();
	SoXipUniformFloat::initClass();

	SoXipClipPlaneKit::initClass();
	SoXipDrawClipPlane::initClass();
	SoXipFrameRate::initClass();
	
	SoXipFramebufferGroup::initClass();
	SoXipSetTransform::initClass();
	
    SoXipBlendFunc::initClass();
	SoXipBufferMask::initClass();
	SoXipCaptureImage::initClass();
	SoXipClearBuffer::initClass();
	
	SoXipDepthTest::initClass();
	SoXipDrawImage::initClass();
	SoXipFramebufferFlip::initClass();
	SoXipGetTransform::initClass();
    SoXipGetCameraProperties::initClass();
	SoXipMultiplyMatrices::initClass();
	SoXipOffscreenRenderer::initClass();
	SoXipTransparentGeometryRenderer::initClass();
    SoXipLoadShaders::initClass();
    SoXipLogGLState::initClass();
	SoXipLutTexture::initClass();
	SoXipOpenGLError::initClass();
	SoXipGLStringMarker::initClass();

    SoXipCube::initClass();
    SoXipDecomposeMFInt32::initClass();
    SoXipDecomposeMFMatrix::initClass();
    SoXipBindTextures::initClass();

    SoXipClearFbo::initClass();
    SoXipFbo::initClass();
    SoXipFboAttachColor::initClass();
    SoXipFboAttachColor3D::initClass();
    SoXipFboAttachDepth::initClass();
    SoXipFboAttachDepth3D::initClass();
    SoXipPingPong::initClass();
    SoXipPingPongFlip::initClass();

    SoXipGLSLComponentProgram::initClass();
    SoXipGLSLLoadComponents::initClass();
    SoXipGLSLPrograms::initClass();
    SoXipGLSLUseProgram::initClass();
    SoXipGLSLUniformGroup::initClass();

	return 1;
}

#ifdef WIN32

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
		xipivcoregl_init();

	return TRUE;
}

#else /* not WIN32 */

static int initted = FALSE;    // a little protection--probably unnecessary
void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{
	int err;

	xipivcoregl_init();

	initted = TRUE;
	//return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
	//printf ("fini print.\n");
}

//forcing initialization through static member (as workaround)
static const bool initMe = xipivcoregl_init();

#endif /* WIN32 */


