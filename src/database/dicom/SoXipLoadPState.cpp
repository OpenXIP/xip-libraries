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
#include "SoXipLoadPState.h"
#include <Inventor/errors/SoError.h> 
#include <xip/inventor/dicom/SoXipSFPState.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/dicom/SoXipPState.h>
//#include <xip/inventor/core/SbXipDirtyFieldList.h>


SO_ENGINE_SOURCE(SoXipLoadPState);


void SoXipLoadPState::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipLoadPState, SoEngine, "Engine");
}


SoXipLoadPState::SoXipLoadPState()
{
	SO_ENGINE_CONSTRUCTOR(SoXipLoadPState);

	SO_ENGINE_ADD_INPUT( image, (0) );
	SO_ENGINE_ADD_INPUT(pstateFile, (""));
	SO_ENGINE_ADD_OUTPUT(presentationstate, SoXipSFPState);

	mPState		 = 0;
}


SoXipLoadPState::~SoXipLoadPState()
{
	#if defined(COIN_DLL) || defined (COIN_NO_DLL)
	// SGI automatically triggers evaluate after loading but COIN doesn't
	SbXipDirtyFieldList::remove(&pstateFile);
	#endif

	unloadAll();
}

void SoXipLoadPState::unloadAll()
{
	if (mPState)
	{
		mPState->unref();
		mPState = 0;
	}
}

void SoXipLoadPState::evaluate()
{
	unloadAll();

	SO_ENGINE_OUTPUT(presentationstate, SoXipSFPState, setValue(0));

	SoXipDataDicom* dicomData = image.getValue();
	if (!dicomData)
		return;

	//DCMTBD
	DcmDataset *dataset = (DcmDataset *) dicomData->getDataset().getItem("DcmItem");
	if (!dataset)
	{
		SoError::post("Unsupported data type for DICOM presentation state!");
		return;
	}

	const SbString strName = pstateFile.getValue();
	if (strName.getLength() == 0)	// empty string
		return;

	try
	{
		// create instance of SoXipPState and set dobject
		mPState = new SoXipPState(dataset);
		mPState->ref();
		mPState->read(strName.getString());
	}
	catch ( ... )
	{
		SoError::post("Object creation failed in SoXipLoadPState.");
	}

	SO_ENGINE_OUTPUT(presentationstate, SoXipSFPState, setValue(mPState));
}


SbBool SoXipLoadPState::readInstance(SoInput * in, unsigned short flags)
{
	#if defined(COIN_DLL) || defined (COIN_NO_DLL)
	// SGI automatically triggers evaluate after loading but COIN doesn't
	SbXipDirtyFieldList::append(&pstateFile);
	#endif

	return SoEngine::readInstance(in, flags);
}
