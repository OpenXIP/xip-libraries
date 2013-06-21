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
#include "SoXipVolumeDicom.h"

#include <Inventor/errors/SoMemoryError.h>

#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>
#include <dcmtk/dcmdata/dctk.h>

SO_ENGINE_SOURCE(SoXipVolumeDicom);

void SoXipVolumeDicom::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipVolumeDicom, SoEngine, "Engine" );
}

SoXipVolumeDicom::SoXipVolumeDicom()
{
	SO_ENGINE_CONSTRUCTOR( SoXipVolumeDicom );

	// Define input field and its default value
	SO_ENGINE_ADD_INPUT( input, (0) );
	input.setNum(0);

	// Define the output, specifying its type
	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage );

	mOutputImage = 0;
}

SoXipVolumeDicom::~SoXipVolumeDicom()
{
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}
}

// This is the evaluation routine.
void SoXipVolumeDicom::evaluate()
{
	// set output to NULL
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(0));

	// clear existing data
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}

	int numSlices = input.getNum();

	// if input size is zero, return
	if (numSlices == 0)
	{
		return;
	}

	DcmDataset **datasets = 0; 

	try
	{
		datasets = new DcmDataset*[numSlices];

		if (!datasets)
		{
			SoMemoryError::post( "Error allocating datasets" );
		}

		for (int i = 0; i < numSlices; i++)
		{
			SoXipDataDicom *out = (SoXipDataDicom*) *(input.getValues(i));

			if (!out)
			{
				SoError::post("Dicom data is NULL");
				goto error;
			}

			//DCMTBD
			datasets[i] = (DcmDataset *) out->getDataset().getItem("DcmItem");
		}

		// create instance of SoXipDataImage
		mOutputImage = new SoXipDataImage();
		mOutputImage->ref();

		// convert dicom data to xip image
		mOutputImage->set(createImage(datasets, numSlices));

		// update output
		SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(mOutputImage));
	}
	catch(...)
	{
		SoError::post("Dicom Data to Xip Image conversion failed in SoXipVolumeDicom");
		goto error;
	}

// error handling
error:
	if (datasets)
	{
		delete [] datasets;
		datasets = 0;
	}

}
