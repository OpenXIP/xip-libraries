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

/*! \mainpage eXtensible Imaging Platform (Xip) Documentation
 *
 * \image html xip_logo.png
 *
 * \section intro_sec Introduction
 *
 * The eXtensible Imaging Platform is a C++ toolkit to build Medical
 * Imaging and Visualization applications.
 * Xip was created with NCI funding and is part of the caBIG initiative.
 * Siemens Corporate Research contributes to and maintains the source
 * code of Xip.
 *
 * \section download_sec Download
 * 
 * You can download the source code and the binaries at this location:
 * https://collab01a.scr.siemens.com/gf/project/xip/
 *
 * \section tutorials_sec Tutorials
 * 
 * Tutorials to install, use and program with Xip are available on
 * the Xip Wiki:
 * https://collab01a.scr.siemens.com/xipwiki
 *
 * \section modules_sec Modules
 * Xip is organized around a number of libraries also called modules:
 *  \li core: base module built around Open Inventor
 *  \li coregl: module built on OpenGL
 *  \li dicom: module that wraps DCMTK
 *  \li itk: module that wraps the Insight Toolkit
 *  \li overlay: module for 2D annotation
 *  \li remote: module for client-server functionalities
 *  \li renderer: module for volume rendering
 *  \li vtk: module that wraps the Visualization Toolkit
 *
 *  \sa README.txt and LICENSE.txt in the source directory.
 */

#include <xip/system/GL/gl.h>

#include <Inventor/SoInteraction.h>

#include <xip/inventor/core/SoXipData.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipDataImageElement.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipMFDataImage.h>
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/SoXipExaminer.h>
#include <xip/inventor/core/SoXipKit.h>
#include <xip/inventor/core/SoXipRenderModeElement.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/core/SbVariant.h>
#include <xip/inventor/core/SoMFVariant.h>
#include <xip/inventor/core/SoSFVariant.h>
#include <xip/inventor/core/SoXipMprPlaneElement.h>
#include <xip/inventor/core/SoXipMprActiveElement.h>
#include <xip/inventor/core/SoXipTransparentGeometryGroupElement.h>
#include <xip/inventor/core/SoXipMprLockElement.h>
#include <xip/inventor/core/SoXipVolGroupElement.h>
#include <xip/inventor/core/SoXipVolDataElement.h>
#include <xip/inventor/core/SoXipClipPlaneElement.h>
#include <xip/inventor/core/SbXipDirtyFieldList.h>
#include <xip/inventor/core/SoXipPickRadiusElement.h>
#include <xip/inventor/core/SoXipImageTextElement.h>
#include <xip/inventor/core/SoXipWindowLevelElement.h>
#include <xip/inventor/core/SoXipConvertToTrigger.h>

#include <xip/inventor/core/SoXipSlopeInterceptConvert.h>
#include <xip/inventor/core/SoXipValueConvertElement.h>

#include "SoXipAutoScale.h"
#include "SoXipBackground.h"
#include "SoXipTexture.h"
#include "SoXipDisableTexturing.h"
#include "SoXipSFDataImageToSFImage.h"
#include "SoXipImage.h"
#include "SoXipGetImage.h"
#include "SoXipLoadRaw.h"
#include "SoXipSaveRaw.h"
#include "SoXipViewportBorder.h"
#include "SoXipIncrement.h"
#include "SoXipIntersectionPlane.h"
#include "SoXipViewportGroup.h"
#include "SoXipImageAttributes.h"
#include "SoXipRenderMode.h"
#include "SoXipWindowLevelManip.h"
#include "SoXipPlaneManipBase.h"
#include "SoXipMprPlane.h"
#include "SoXipMprIntersectionManip.h"
#include "SoXipMprIntersectionLine.h"
#include "SoXipMprExaminer.h"
#include "SoXipMprIntersectionPlanes.h"
#include "SoXipMprAlign.h"
#include "SoXipTransparentGeometryGroup.h"
#include "SoXipMprActive.h"
#include "SoXipMprLock.h"
#include "SoXipVolGroup.h"
#include "SoXipPickAction.h"
#include "SoXipBoundingBox.h"
#include "SoXipTrackballToMouse.h"
#include "SoXipTimerFunction.h"
#include "SoXipWindowSize.h"
#include "SoXipMouseToggle.h"
#include "SoXipDogEar.h"
#include "SoXipQuad.h"
#include "SoXipDrawQuad.h"
#include "SoXipOrientationCube.h"
#include "SoXipClipPlane.h"
#include "SoXipLut.h"
#include "SoXipApplyLutToImage.h"
#include "SoXipPerformance.h"
#include "SoXipPerformanceCounter.h"
#include "SoXipProxy.h"
#include "SoXipConvertMatrixToPlane.h"
#include "SoXipConvertToEnum.h"
#include "SoXipAnchor.h"
#include "SoXipImageExaminer.h"
#include "SoXipComposeMFImage.h"
#include "SoXipDecomposeMFImage.h"
#include "SoXipExtractSlice.h"
#include "SoXipInvertMatrix.h"
#include "SoXipLazyGroup.h"
#include "SoXipImageText.h"
#include "SoXipComposeVec6.h"
#include "SoXipDecomposeVec6.h"
#include "SoXipStringConcatenate.h"
#include "SoXipConvertMFImageToSFImage.h"
#include "SoXipConvertSFImageToMFImage.h"
#include "SoXipImageOperation.h"
#include "SoXipSwitchMFDataImage.h"
#include "SoXipCheckGLStacks.h"
#include <xip/inventor/core/SoXipRegistrationElement.h>
#include "SoXipRegistrationTransform.h"

int XIPIVCORE_API xipivcore_init()
{
  static bool isInit = false;
  if(isInit)
    return 1;
  isInit = true;

  SoInteraction::init();

    //initialize elements first
    SoXipLutElement::initClass();
    //SoXipListActionElement::initClass();
    //SoXipListActionEnableElement::initClass();
    SoXipActiveViewportElement::initClass();
    SoXipDataImageElement::initClass();
    SoXipMultiTextureElement::initClass();
    SoXipRenderModeElement::initClass();
    SoXipMprPlaneElement::initClass();
    SoXipMprActiveElement::initClass();		
    SoXipTransparentGeometryGroupElement::initClass();
    SoXipMprLockElement::initClass();
    SoXipVolDataElement::initClass();		
    SoXipVolGroupElement::initClass();		
    SoXipClipPlaneElement::initClass();
    SoXipPickRadiusElement::initClass();
    SoXipImageTextElement::initClass();
    SoXipWindowLevelElement::initClass();

	SoXipValueConvertElement::initClass();

    //initialize rest then
    SbXipDirtyFieldList::initClass();
    SoXipData::initClass();
    SoXipDataImage::initClass();
    SoXipSFDataImage::initClass();
    SoXipMFDataImage::initClass();
    SoXipSFDataImageToSFImage::initClass();
    SoXipComposeVec6::initClass();
    SoXipCursor::initClass();
    SoXipDecomposeVec6::initClass();
    SoXipKit::initClass();
    //SoXipList::initClass();
    //SoXipListAction::initClass();
    //SoXipListActionEnable::initClass();
    SoXipImage::initClass();
    SoXipImageAttributes::initClass();
    SoXipLoadRaw::initClass();
	SoXipSaveRaw::initClass();
    SoXipDogEar::initClass();
    SoXipQuad::initClass();
    SoXipDrawQuad::initClass();
    SoXipViewportBorder::initClass();
    SoXipOrientationCube::initClass();	
    SoXipViewportGroup::initClass();
    SoXipLut::initClass();
    SoXipApplyLutToImage::initClass();
    SoXipTexture::initClass();
    SoXipDisableTexturing::initClass();
    SoXipTimerFunction::initClass();
    SoXipRenderMode::initClass();
    SoXipExaminer::initClass();
    SoSFVariant::initClass();
    SoMFVariant::initClass();
    SoXipPlaneManipBase::initClass();
    SoXipIntersectionPlane::initClass();
    SoXipWindowLevelManip::initClass();
    SoXipMprPlane::initClass();
    SoXipMprIntersectionLine::initClass();
    SoXipMprIntersectionManip::initClass();
    SoXipMprExaminer::initClass();
    SoXipMprAlign::initClass();
    SoXipTransparentGeometryGroup::initClass();
    SoXipMprLock::initClass();
    SoXipMprActive::initClass();
    SoXipVolGroup::initClass();
    SoXipPickAction::initClass();

  SoXipInvertMatrix::initClass();
    SoXipLazyGroup::initClass();

    SoXipBoundingBox::initClass();
    SoXipTrackballToMouse::initClass();
    SoXipWindowSize::initClass();
    SoXipMouseToggle::initClass();
    SoXipClipPlane::initClass();
    SoXipPerformance::initClass();
    SoXipPerformanceCounter::initClass();
	SoXipProxy::initClass();
    SoXipConvertMatrixToPlane::initClass();
    SoXipConvertToEnum::initClass();
    SoXipAutoScale::initClass();
    SoXipBackground::initClass();
    SoXipAnchor::initClass();
    SoXipGetImage::initClass();
    SoXipImageExaminerBase::initClass();
    SoXipImageExaminer::initClass();    
    SoXipComposeMFImage::initClass();
    SoXipDecomposeMFImage::initClass();
    SoXipExtractSlice::initClass();
    SoXipImageText::initClass();
    SoXipIncrement::initClass();
    SoXipStringConcatenate::initClass();
    SoXipConvertMFImageToSFImage::initClass();
    SoXipConvertSFImageToMFImage::initClass();
    SoXipImageOperation::initClass();
    SoXipSwitchMFDataImage::initClass();

	SoXipRegistrationElement::initClass();
	SoXipRegistrationTransform::initClass();

	SoXipSlopeInterceptConvert::initClass();
    SoXipConvertToTrigger::initClass();
    SoXipCheckGLStacks::initClass();

    // Register converters to trigger for all data types
    SoType triggerType = SoType::fromName( "SoSFTrigger" );
    SoType convType = SoType::fromName( "SoXipConvertToTrigger" );

    SoDB::addConverter( SoXipSFDataImage::getClassTypeId(), triggerType, convType );
    SoDB::addConverter( SoXipMFDataImage::getClassTypeId(), triggerType, convType );



	
  return 1;
}

#ifndef WIN32

static int initted = FALSE;    // a little protection--probably unnecessary
void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{

	int err;



	xipivcore_init();


	initted = TRUE;
	//return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
   //printf ("fini print.\n");
}

//forcing initialization through static member (as workaround)
static const bool initMe = xipivcore_init();

#endif
#ifdef WIN32
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)

        if (!SoDB::isInitialized())
        {
            SoDB::init();
//            SoInteraction::init();
        }

        xipivcore_init();

    return TRUE;
}
#endif


