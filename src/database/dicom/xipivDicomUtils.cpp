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
#include <Inventor/errors/SoMemoryError.h>
#include <dcmtk/dcmdata/dctk.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>


SbMatrix getModelMatrixFromDICOM(DcmDataset* dataSet)
{
	SbMatrix modelMatrix = SbMatrix::identity();

	if (!dataSet)
		return modelMatrix;

	OFCondition errorFlag;

	try
	{
		unsigned short height, width;
		unsigned short numberOfSlices = 1;
		double zSpacing = 1.0;
		double spacing[2] = { 1.0, 1.0 };
		double imagePositionPatient[3] = {0};
		double imageOrientationPatient[6] = { 1.0, 0.0, 0.0,
			                                  0.0, -1.0, 0.0 };
		double shearYZ = 0, shearXY = 0, shearXZ = 0;

		DcmStack stack;
		DcmElement *element;
		
		// row
		errorFlag = dataSet->findAndGetUint16(DCM_Rows, height);
		if (!errorFlag.good())
			goto error;

		// column
		errorFlag = dataSet->findAndGetUint16(DCM_Columns, width);
		if (!errorFlag.good())
			goto error;

		// number of slices
		if ( dataSet->search(DCM_NumberOfSlices, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_US)
				element->getUint16(numberOfSlices);
		}
		else if ( dataSet->search(DCM_NumberOfFrames, stack) == EC_Normal ) // number of frames
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_IS)
			{
				OFString value;
				element->getOFString(value, 0);
				numberOfSlices = ::atoi(value.c_str());
			}
		}

		// slice thickness
		if ( dataSet->search(DCM_SliceThickness, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
				element->getFloat64(zSpacing);
		}

		// pixel spacing
		if ( dataSet->search(DCM_PixelSpacing, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (unsigned int i = 0; i < element->getVM(); i++)
					element->getFloat64(spacing[i], i);
			}
		}

		// patient position
		if ( dataSet->search(DCM_ImagePositionPatient, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (unsigned int i = 0; i < element->getVM(); i++)
					element->getFloat64(imagePositionPatient[i], i);
			}
		}

		// patient orientation
		if ( dataSet->search(DCM_ImageOrientationPatient, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (unsigned int i = 0; i < element->getVM(); i++)
					element->getFloat64(imageOrientationPatient[i], i);
			}

		}

		// computation of model matrix, must be in sync with the one from SoIvtLoadDicom
		SbVec3f pos(imagePositionPatient[0], imagePositionPatient[1], imagePositionPatient[2]);
		SbVec3f scale(width * spacing[0], height * spacing[1], numberOfSlices * zSpacing);

		SbVec3f row(imageOrientationPatient[0], imageOrientationPatient[1], imageOrientationPatient[2]);
		SbVec3f col(imageOrientationPatient[3], imageOrientationPatient[4], imageOrientationPatient[5]);
		SbVec3f nor = row.cross(col);
		SbMatrix rotMatrix(
			row[0], row[1], row[2], 0,
			col[0], col[1], col[2], 0,
			nor[0], nor[1], nor[2], 0,
			0, 0, 0, 1);

		DcmTag tag(DCM_GantryDetectorTilt);
		DcmVR type = tag.getVR();

		// shearYZ
		if ( dataSet->search(DCM_GantryDetectorTilt, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
				element->getFloat64(shearYZ);

			if (shearYZ != 0)
			{
				// convert from degree to radiant
				shearYZ /= 180.f;
				shearYZ *= acos(-1.f);
			}
		}

		// shearXY and shearXZ are currently unsupported
		SbMatrix shearMatrix(
			1.0,		0.0,		0.0, 0.0,
			shearXY,	1.0,		0.0, 0.0,
			shearXZ,	shearYZ,	1.0, 0.0,
			0.0,		0.0,		0.0, 1.0);

		modelMatrix.setTransform(pos, SbRotation(rotMatrix), scale);
		modelMatrix = shearMatrix * modelMatrix;
	}
	catch(...)
	{
		SoError::post( "Getting model matrix from DICOM Failed!");
	}

	return modelMatrix;

// error handling
error:
	SoError::post("Error : \"%s\"", errorFlag.text());

	return modelMatrix;
}

XipDicomAttributes getAttributesFromDicom( DcmDataset* dataset )
{
	XipDicomAttributes dicomAttributes;

	if (!dataset)
		return dicomAttributes;

	OFCondition errorFlag;
	DcmStack stack;
	DcmElement *element;

	try
	{
		// row
		errorFlag = dataset->findAndGetUint16(DCM_Rows, dicomAttributes.height);
		if (!errorFlag.good())
			goto error;

		// column
		errorFlag = dataset->findAndGetUint16(DCM_Columns, dicomAttributes.width);
		if (!errorFlag.good())
			goto error;

		// bits stored
		errorFlag = dataset->findAndGetUint16(DCM_BitsStored, dicomAttributes.bitsStored);
		if (!errorFlag.good())
			goto error;

		// bits allocated
		errorFlag = dataset->findAndGetUint16(DCM_BitsAllocated, dicomAttributes.bitsAllocated);
		if (!errorFlag.good())
			goto error;

		// samples per pixel
		errorFlag = dataset->findAndGetUint16(DCM_SamplesPerPixel, dicomAttributes.samplesPerPixel);
		if (!errorFlag.good())
			goto error;

		// pixel representation
		errorFlag = dataset->findAndGetUint16(DCM_PixelRepresentation, dicomAttributes.pixelRepresentation);
		if (!errorFlag.good())
			goto error;

		// number of slices
		if ( dataset->search(DCM_NumberOfSlices, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_US)
				element->getUint16(dicomAttributes.numberOfSlices);
		}
		else if ( dataset->search(DCM_NumberOfFrames, stack) == EC_Normal )	// number of frames
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_IS)
			{
				OFString value;
				element->getOFString(value, 0);
				dicomAttributes.numberOfSlices = ::atoi(value.c_str());
			}
		}
	}
	catch(...)
	{
		SoError::post( "Extracting dicom attributes from dicom dataset Failed!");
	}

	return dicomAttributes;

// error handling
error:
	SoError::post("Error : \"%s\"", errorFlag.text());

	return dicomAttributes;
}

SbXipImage* createImage(DcmDataset* dataSet)
{
	SbXipImage *image = 0;

	if (!dataSet)
		return image;

	OFCondition errorFlag;
	DcmStack stack;

	try
	{
		// get Dicom attributes like width, heigh, bits stored, bits allocated .....
		XipDicomAttributes dicomAttributes = getAttributesFromDicom(dataSet);

		// compute model matrix
		SbMatrix modelMatrix = getModelMatrixFromDICOM(dataSet);

		// get the DICOM pixel data pointer
		void *pixelBuffer = 0;
		unsigned long pixelBufferSize = 0;
		DcmPixelData *pixelData;

		if ( dataSet->search(DCM_PixelData, stack, ESM_fromHere, OFFalse) == EC_Normal )
		{
			if (stack.top()->ident() == EVR_PixelData)
			{
				pixelData = (DcmPixelData *)stack.top();

				DcmEVR evr = pixelData->getVR();

		        if ( evr == EVR_OW )
					pixelData->getUint16Array( (Uint16 *&)pixelBuffer );
	            else // evr == EVR_OB
					pixelData->getUint8Array( (Uint8 *&)pixelBuffer );

				pixelBufferSize = pixelData->getLength();
			}
		}

		if (dicomAttributes.bitsAllocated > 8)
		{
			// 16 bit
			image = new SbXipImage(SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, dicomAttributes.numberOfSlices), 
									SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, dicomAttributes.numberOfSlices), 
									(dicomAttributes.pixelRepresentation == 1) ? SbXipImage::SHORT : SbXipImage::UNSIGNED_SHORT, 
									dicomAttributes.bitsStored, 
									1, SbXipImage::SEPARATE, SbXipImage::LUMINANCE, modelMatrix);

		}
		else
		{
			// 8 bit
			SbXipImage::ComponentType compType = SbXipImage::SEPARATE;
			SbXipImage::ComponentLayoutType compLayoutType = SbXipImage::LUMINANCE;

  			// color image
			if(dicomAttributes.samplesPerPixel == 3)
			{
				compType = SbXipImage::INTERLEAVED;
				compLayoutType = SbXipImage::RGB;
			}

			image = new SbXipImage(SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, dicomAttributes.numberOfSlices), 
				                    SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, dicomAttributes.numberOfSlices), SbXipImage::UNSIGNED_BYTE, dicomAttributes.bitsStored, 
				                    dicomAttributes.samplesPerPixel, compType, compLayoutType, modelMatrix);

		}

		if (image && pixelBuffer && pixelBufferSize > 0)
		{
			// copy pixel data
			void *ptr = image->refBufferPtr();
			memcpy(ptr, pixelBuffer, pixelBufferSize);
			image->unrefBufferPtr();
		}
	}
	catch(...)
	{
		SoError::post( "Creating xip image from dicom dataset Failed!");
	}

	return image;
}

SbXipImage* createImage( DcmDataset** dataset, unsigned int num )
{
	SbXipImage *image = 0;

	if (!dataset || num == 0)
		return image;

	OFCondition errorFlag;
	DcmStack stack;
	DcmElement *element;

	try
	{
		// take first dataset as a reference
		DcmDataset* refDataset = dataset[0];

		if (!refDataset)
			return image;

		double zSpacing = 1.0;

		// get Dicom attributes like width, heigh, bits stored, bits allocated .....
		XipDicomAttributes dicomAttributes = getAttributesFromDicom(refDataset);

		// slice thickness
		if ( refDataset->search(DCM_SliceThickness, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
				element->getFloat64(zSpacing);
		}

		// find the total number of slices
		int depth = dicomAttributes.numberOfSlices;

		for (unsigned int i = 1; i < num; i++)
		{
			if (!dataset[i])
			{
				SoError::post( "Creating xip image from dicom datasets Failed!");
				return image;
			}

			XipDicomAttributes attributes = getAttributesFromDicom(dataset[i]);

			if ( (attributes.width != dicomAttributes.width) || (attributes.height != dicomAttributes.height) ||
				(attributes.bitsAllocated != dicomAttributes.bitsAllocated) || (attributes.bitsStored != dicomAttributes.bitsStored) ||
				(attributes.samplesPerPixel != dicomAttributes.samplesPerPixel) )
			{
				SoError::post( "Creating xip image from dicom datasets Failed!");
				return image;
			}

			depth += dicomAttributes.numberOfSlices;
		}

		// get the first slice position
		double imagePositionPatientFirst[3] = {0};

		// patient position
		if ( refDataset->search(DCM_ImagePositionPatient, stack, ESM_fromHere, OFFalse) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (unsigned int i = 0; i < element->getVM(); i++)
					element->getFloat64(imagePositionPatientFirst[i], i);
			}
		}

		// get the last slice position
		double imagePositionPatientLast[3] = {0};

		DcmDataset* lastDataset = dataset[num-1];

		if (!lastDataset)
			return image;

		// patient position
		if ( lastDataset->search(DCM_ImagePositionPatient, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (unsigned int i = 0; i < element->getVM(); i++)
					element->getFloat64(imagePositionPatientLast[i], i);
			}
		}

		// compute model matrix
		SbMatrix modelMatrix = getModelMatrixFromDICOM(refDataset);

		SbVec3f row(modelMatrix[0][0], modelMatrix[0][1], modelMatrix[0][2]);
		SbVec3f col(modelMatrix[1][0], modelMatrix[1][1], modelMatrix[1][2]);
		SbVec3f nor = row.cross(col);
		nor.normalize();

		SbVec3f firstSlicePos(imagePositionPatientFirst[0] * nor[0], imagePositionPatientFirst[1] * nor[1], imagePositionPatientFirst[2] * nor[2]);
		SbVec3f lastSlicePos(imagePositionPatientLast[0] * nor[0], imagePositionPatientLast[1] * nor[1], imagePositionPatientLast[2] * nor[2]);
		SbVec3f diffPos = lastSlicePos - firstSlicePos;

        // the scale of the model matrix goes from the edge to edge, not center to center, 
        // so we need to get the slice spacing first, then multiply by depth
        if (depth > 1)
        {
            diffPos /= (depth-1);
            diffPos *= depth;
        }
		// The above model matrix is for only the first slice
		// update it to consider all the slices
		SbVec3f t, s;
		SbRotation r, so;
		modelMatrix.getTransform(t, r, s, so);

		s[2] = (num > 1) ? diffPos.length() : depth * zSpacing; 

		modelMatrix.setTransform(t, r, s, so);

		if (dicomAttributes.bitsAllocated > 8)
		{
			// 16 bit
			image = new SbXipImage(SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, depth), 
				                   SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, depth), 
								   (dicomAttributes.pixelRepresentation == 1) ? SbXipImage::SHORT : SbXipImage::UNSIGNED_SHORT, 
								   dicomAttributes.bitsStored, 
				                   1, SbXipImage::SEPARATE, SbXipImage::LUMINANCE, modelMatrix);

		}
		else
		{
			// 8 bit
			SbXipImage::ComponentType compType = SbXipImage::SEPARATE;
			SbXipImage::ComponentLayoutType compLayoutType = SbXipImage::LUMINANCE;

  			// color image
			if(dicomAttributes.samplesPerPixel == 3)
			{
				compType = SbXipImage::INTERLEAVED;
				compLayoutType = SbXipImage::RGB;
			}

			image = new SbXipImage(SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, depth), 
				                   SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, depth), SbXipImage::UNSIGNED_BYTE, dicomAttributes.bitsStored, 
				                   dicomAttributes.samplesPerPixel, compType, compLayoutType, modelMatrix);

		}

		if (image)
		{
			// copy pixel data
			Uint8 *ptr = (Uint8 *)image->refBufferPtr();

			// get the DICOM pixel data pointer
			void *pixelBuffer = 0;
			unsigned long pixelBufferSize = 0;
			DcmPixelData *pixelData;

			for (unsigned int i = 0; i < num; i++)
			{
				pixelBuffer = 0;
				pixelBufferSize = 0;

				if ( dataset[i]->search(DCM_PixelData, stack) == EC_Normal )
				{
					if (stack.top()->ident() == EVR_PixelData)
					{
						pixelData = (DcmPixelData *)stack.top();

						DcmEVR evr = pixelData->getVR();

						if ( evr == EVR_OW )
							pixelData->getUint16Array( (Uint16 *&)pixelBuffer );
						else // evr == EVR_OB
							pixelData->getUint8Array( (Uint8 *&)pixelBuffer );

						pixelBufferSize = pixelData->getLength();
					}
				}

				if (pixelBuffer && pixelBufferSize > 0)
				{
					memcpy(ptr, pixelBuffer, pixelBufferSize);
					ptr += pixelBufferSize;
				}
			}
			
			image->unrefBufferPtr();
		}
	}
	catch(...)
	{
		SoError::post( "Creating xip image from dicom dataset Failed!");
	}

	return image;
}
