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
#include "SoXipDicomExtractSlice.h"

#include <Inventor/errors/SoErrors.h>
#include <dcmtk/dcmdata/dctk.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>

SO_ENGINE_SOURCE( SoXipDicomExtractSlice );


SoXipDicomExtractSlice::SoXipDicomExtractSlice()
{
	SO_ENGINE_CONSTRUCTOR( SoXipDicomExtractSlice );

	SO_ENGINE_ADD_INPUT(image, (0));
	SO_ENGINE_ADD_INPUT(sliceIndex, (-1));

	SO_ENGINE_ADD_OUTPUT(output, SoXipSFDataImage);
	SO_ENGINE_ADD_OUTPUT(numSlices, SoSFShort);

	mOutput		= 0;
}


SoXipDicomExtractSlice::~SoXipDicomExtractSlice()
{
	if (mOutput)
	{
		mOutput->unref();
		mOutput = 0;
	}
}


void SoXipDicomExtractSlice::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipDicomExtractSlice, SoEngine, "Engine" );
}


void SoXipDicomExtractSlice::evaluate()
{
	if (mOutput)
	{
		mOutput->unref();
		mOutput = 0;
	}

	int nSlices = 0;

	if (image.getValue())
	{
		nSlices = image.getValue()->getNumSlices();

		if ((sliceIndex.getValue() < nSlices) && (sliceIndex.getValue() >= 0))
		{
			// convert dicom data to xip image
			SbXipImage *img = new SbXipImage();
			if (!img)
			{
				SoMemoryError::post("SbXipImage");
			}
			else if (image.getValue()->getPixelData(*img, sliceIndex.getValue()))
			{
				// create instance of SoXipDataImage
				mOutput = new SoXipDataImage();
				mOutput->ref();
				mOutput->set(img);
			}
		}
	}

	SO_ENGINE_OUTPUT(numSlices, SoSFShort, setValue(nSlices));
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(mOutput));	
}
