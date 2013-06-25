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
#ifndef XIPIVDICOMUTILS_H
#define XIPIVDICOMUTILS_H

#include <xip/inventor/dicom/xipivdicom.h>
#include <Inventor/SbLinear.h>

/**
 *  Structure to hold dicom attributes.
 *
 */
struct XipDicomAttributes
{
	XipDicomAttributes()
	{
		width = 0;
		height = 0;
		bitsStored = 0;
		bitsAllocated = 0;
		samplesPerPixel = 0;
		numberOfSlices = 1;
	}

	unsigned short	width;
	unsigned short	height;
	unsigned short	bitsStored;
	unsigned short	bitsAllocated;
	unsigned short	samplesPerPixel;
	unsigned short	numberOfSlices;
	unsigned short  pixelRepresentation;
};

/**
 *  Extracts the model matrix out of a Dicom image.
 *
 */
XIPIVDICOM_API SbMatrix getModelMatrixFromDICOM( class DcmDataset* dataSet );

/**
 *  Extracts the dicom attributes from Dicom image.
 *
 */
XIPIVDICOM_API XipDicomAttributes getAttributesFromDicom( class DcmDataset* dataset );

/**
 *  Creates SbXipImage from dicom dataset.
 *
 */
XIPIVDICOM_API class SbXipImage* createImage( class DcmDataset* dataSet );

/**
 *  Creates SbXipImage from dicom datasets.
 *
 */
XIPIVDICOM_API class SbXipImage* createImage( class DcmDataset** dataSet, unsigned int num );

#endif	// XIPIVDICOMUTILS_H
