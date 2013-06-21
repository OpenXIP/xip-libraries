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
#include <Inventor/SoDB.h>

#include <xip/inventor/core/xipivcore.h>

#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/dicom/SoXipPState.h>
#include <xip/inventor/dicom/SoXipSFDataDicom.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>
#include <xip/inventor/dicom/SoXipSFPState.h>
#include <xip/inventor/dicom/SoXipDataDicomElement.h>

#include "SoXipLoadDicom.h"
#include "SoXipLoadPState.h"
#include "SoXipSortDicom.h"
#include "SoXipGetDicom.h"
#include "SoXipSaveDicom.h"
#include "SoXipGetDicomReference.h"
#include "SoXipConvertDicom.h"
#include "SoXipConvertDicomToXipImage.h"
#include "SoXipGetDicomString.h"
#include "SoXipDicomExaminer.h"
#include "SoXipDicomExtractSlice.h"
#include "SoXipVolumeDicom.h"
#include "SbXipDicomProviderDcmtk.h"
#include "SoXipDicomSort3D.h"
#include "SoXipDicomWindowLevel.h"
#include "SoXipComposeMFDicom.h"
#include "SoXipDecomposeMFDicom.h"
#include "SoXipSwitchMFDataDicom.h"

int XIPIVDICOM_API xipivdicom_init()
{
	static bool isInit = false;
	if(isInit)
		return 1;
	isInit = true;

	xipivcore_init();

  SoXipDataDicom::initClass();
  SoXipPState::initClass();
  SoXipDataDicomElement::initClass();
  SoXipSFDataDicom::initClass();
  SoXipMFDataDicom::initClass();
  SoXipSFPState::initClass();
  SoXipLoadDicom::initClass();
  SoXipLoadPState::initClass();
  SoXipSortDicom::initClass();
  SoXipGetDicom::initClass();
  SoXipSaveDicom::initClass();
  SoXipGetDicomReference::initClass();
  SoXipGetDicomString::initClass();
  SoXipDicomExaminer::initClass();
  SoXipDicomExtractSlice::initClass();
  SoXipVolumeDicom::initClass();
  SoXipDicomSort3D::initClass();
  SoXipDicomWindowLevel::initClass();
  SoXipComposeMFDicom::initClass();
  SoXipDecomposeMFDicom::initClass();
  SoXipSwitchMFDataDicom::initClass();

  // converters
  SoXipConvertMFDicomToSFDicom::initClass();
  SoXipConvertSFDicomToMFDicom::initClass();
  SoXipConvertMFDicomToMFImage::initClass();
  SoXipConvertMFDicomToSFImage::initClass();
  SoXipConvertSFDicomToSFImage::initClass();

  // data providers
  SbXipDicomProviderDcmtk::initClass();

  return 1;
}

#ifdef WIN32

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
		xipivdicom_init();

	return TRUE;
}

#else //UNIX

static int initted = FALSE;    // a little protection--probably unnecessary
void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{
    
	int err;
    
    
    
	//xipivdicom_init();
    
    
	//initted = TRUE;
	//return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
    //printf ("fini print.\n");
}

//forcing initialization through static member (as workaround)
//static const bool initMe = xipivdicom_init();

#endif //WIN32
