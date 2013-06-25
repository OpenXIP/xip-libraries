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
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include "SoXipGetDicomReference.h"


SO_ENGINE_SOURCE( SoXipGetDicomReference );


SoXipGetDicomReference::SoXipGetDicomReference()
{
	SO_ENGINE_CONSTRUCTOR( SoXipGetDicomReference );

	SO_ENGINE_ADD_INPUT( image, (0) );
	image.setNum(0);

	SO_ENGINE_ADD_OUTPUT( dicom, SoXipMFDataDicom );
}

SoXipGetDicomReference::~SoXipGetDicomReference()
{

}

void 
SoXipGetDicomReference::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipGetDicomReference, SoEngine, "Engine" );
}

void 
SoXipGetDicomReference::evaluate()
{
	// Reset output
	SO_ENGINE_OUTPUT( dicom, SoXipMFDataDicom, setNum(0) );

	SoXipMFDataDicom tmp;

	for( int i = 0; i < image.getNum(); ++ i )
	{
		SoXipDataImage* imageData = image[i];
		if( !imageData )
		{
			SoDebugError::post( __FILE__, "Found null image data" );
			return ;
		}

		// Get reference image
		SoXipDataDicom* ref = (SoXipDataDicom *) imageData->getRefByType( SoXipDataDicom::getClassTypeId() );
		if( !ref )
		{
			// See if image has itself SoXipDataImage references
			// Get reference image
			SoXipDataImage* refData = 0;
			
			while( (refData = (SoXipDataImage *) imageData->getRefByType( SoXipDataImage::getClassTypeId() )) )
				imageData = refData;

			ref = (SoXipDataDicom *) imageData->getRefByType( SoXipDataDicom::getClassTypeId() );
			if( !ref )
			{
				SoDebugError::post( __FILE__, "No Dicom references found in input image" );
				return ;
			}
		}

		tmp.set1Value( tmp.getNum(), ref );
	}

	SO_ENGINE_OUTPUT( dicom, SoXipMFDataDicom, copyFrom(tmp) );
}
