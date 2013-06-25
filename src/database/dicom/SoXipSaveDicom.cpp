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
#include "SoXipSaveDicom.h"

#include <Inventor/errors/SoErrors.h>

#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/core/XipStringUtils.h>

#include <dcmtk/dcmdata/dctk.h>

SO_ENGINE_SOURCE(SoXipSaveDicom);


void SoXipSaveDicom::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipSaveDicom, SoEngine, "Engine");
}


SoXipSaveDicom::SoXipSaveDicom()
{
	SO_ENGINE_CONSTRUCTOR(SoXipSaveDicom);

	SO_ENGINE_ADD_INPUT(image, (0));
	SO_ENGINE_ADD_INPUT(referenceImage,	(0));
	SO_ENGINE_ADD_INPUT(storage, (""));
	SO_ENGINE_ADD_INPUT(seriesNumber, (0));
	SO_ENGINE_ADD_INPUT(imageNumber, (0));
	SO_ENGINE_ADD_INPUT(apply, ());

	SO_ENGINE_ADD_OUTPUT(id, SoSFString);

}


SoXipSaveDicom::~SoXipSaveDicom()
{
}

void SoXipSaveDicom::inputChanged(SoField *whichField)
{
	if (whichField == &apply)
	{
		try
		{
			// get the input image
			SoXipDataImage* imageData = image.getValue();
			if (!imageData)
				return;

			SoXipDataDicom* dicomData = referenceImage.getValue();
			if (!dicomData)
			{
				SoError::post("Null pointer");
				return;
			}

			SoXipDataDicom *outputDicomData = new SoXipDataDicom();
			if (!outputDicomData)
			{
				SoMemoryError::post("Failed to create SoXipDataDicom object");
				return;
			}

			outputDicomData->ref();

			if (!outputDicomData->createCompatible(dicomData))
			{
				SoError::post("Failed to copy dicom object");
				return;
			}

			SbXipImage* imageIn = imageData->get();

			SbXipImage::DataType type = imageIn->getType();

			SbXipImageDimensions imgDimension = imageIn->getDimAllocated();
			unsigned short bitsStored = imageIn->getBitsStored();
			unsigned short bitsAllocated = 0;

			switch (type)
			{
			case SbXipImage::UNSIGNED_BYTE:
			case SbXipImage::BYTE:				bitsAllocated = 8; break;
			case SbXipImage::UNSIGNED_SHORT:
			case SbXipImage::SHORT:				bitsAllocated = 16; break;
			case SbXipImage::UNSIGNED_INT:
			case SbXipImage::INT:
			case SbXipImage::FLOAT:				bitsAllocated = 32; break;
			case SbXipImage::DOUBLE:			bitsAllocated = 64; break;
			}

			SbMatrix modelMatrix = imageIn->getModelMatrix();

			SbVec3f pos, scale;
			SbRotation rot, scaleOrient;
			modelMatrix.getTransform(pos, rot, scale, scaleOrient);

			// find rotation matrix
			SbMatrix rotMatrix;
			rot.getValue(rotMatrix);


			// image orientation
			double imageOrientation[] = { rotMatrix[0][0],
										  rotMatrix[0][1],
										  rotMatrix[0][2],
										  rotMatrix[1][0],
										  rotMatrix[1][1],
										  rotMatrix[1][2] };

			SbXipDicomItemHandle itemHandle = outputDicomData->getDataset();

			if (itemHandle.isNull())
			{
				SoError::post("Null pointer");
				return;
			}

			DcmDataset *dataset = (DcmDataset *)itemHandle.getItem();

			char uid[100];
			// SOP class UID (Secondary capture Image Storage)
			dataset->putAndInsertString(DCM_SOPClassUID, UID_SecondaryCaptureImageStorage);

			// SOP class instance UID
			dataset->putAndInsertString(DCM_SOPInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));

			// series number
			char seriesNum[16];
			sprintf(seriesNum, "%d", seriesNumber.getValue());
			dataset->putAndInsertString(DCM_SeriesNumber, seriesNum);

			// image number
			char imgNum[16];
			sprintf(imgNum, "%d", imageNumber.getValue());
			dataset->putAndInsertString(DCM_InstanceNumber, imgNum);

			// number of columns
			dataset->putAndInsertUint16(DCM_Columns, imgDimension[0]);

			// number of rows
			dataset->putAndInsertUint16(DCM_Rows, imgDimension[1]);

			// bits allocated
			dataset->putAndInsertUint16(DCM_BitsAllocated, bitsAllocated);

			// bits stored
			dataset->putAndInsertUint16(DCM_BitsStored, bitsStored);

			// high bit
			dataset->putAndInsertUint16(DCM_HighBit, bitsStored - 1);

			// samples per pixel
			dataset->putAndInsertUint16(DCM_SamplesPerPixel, imageIn->getComponents());

			// photometric representation
			dataset->putAndInsertString(DCM_PhotometricInterpretation, imageIn->getComponents() == 1 ? "MONOCHROME2" : "RGB");

			// pixel representation
			unsigned short pixelRepresentation = 0;		// unsigned
			if ((type == SbXipImage::BYTE) || (type == SbXipImage::SHORT) || (type == SbXipImage::INT))
			{
				pixelRepresentation = 1;
			}
			dataset->putAndInsertUint16(DCM_PixelRepresentation, pixelRepresentation);

			if (imageIn->getComponents() > 1)
			{
				// The planar configuration tag is required when "Samples per Pixel" has a value greater than 1.
				// The Configuration values 0 (color by pixel) are supported now.

				// set Planar Configuration
				dataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);

				if (dataset->tagExists(DCM_RescaleIntercept))
				{
					// Rescale
					dataset->putAndInsertString(DCM_RescaleIntercept, "0");

					// Slope
					dataset->putAndInsertString(DCM_RescaleSlope, "1");
				}
			}

			// image type
			char imageType[] = "DERIVED\\SECONDARY\\OTHER\\XIP\\NOT FOR CLINICAL USE";
			dataset->putAndInsertString(DCM_ImageType, imageType);

			// set pixel data
			unsigned long bufferSize = imgDimension[0] * imgDimension[1] * imgDimension[2] * imageIn->getComponents();
			void* bufferPtr = 0;
			
			switch (type)
			{
				case SbXipImage::BYTE:
					{
						bufferPtr = (char *)imageIn->refBufferPtr();
						bufferSize *= sizeof(char);
					} break;
				case SbXipImage::UNSIGNED_BYTE:
					{
						bufferPtr = (unsigned char *)imageIn->refBufferPtr();
						bufferSize *= sizeof(unsigned char);
					} break;
				case SbXipImage::UNSIGNED_SHORT:
					{
						bufferPtr = (unsigned short *)imageIn->refBufferPtr();
						bufferSize *= sizeof(unsigned short);
					} break;
				case SbXipImage::SHORT:
					{
						bufferPtr = (short *)imageIn->refBufferPtr();
						bufferSize *= sizeof(short);
					} break;
				case SbXipImage::UNSIGNED_INT:
					{
						bufferPtr = (unsigned int *)imageIn->refBufferPtr();
						bufferSize *= sizeof(unsigned int);
					} break;
				case SbXipImage::INT:
					{
						bufferPtr = (int *)imageIn->refBufferPtr();
						bufferSize *= sizeof(int);
					} break;
			}
            
			dataset->putAndInsertUint8Array(DCM_PixelData, (unsigned char *)bufferPtr, bufferSize);
			
            imageIn->unrefBufferPtr();

			// save in the file
#ifdef WIN32
            //assuming everything is done using the bad backslashes... so we convert all forward slashes to those
            const char * storageLocal = XipReplaceChar(storage.getValue().getString(), '/', '\\').getString();
#else //UNIX
            //assuming the other way around since we need forward slashes now...
            const char * storageLocal = XipReplaceChar(storage.getValue().getString(), '\\', '/').getString();
#endif //WIN32
			if (!outputDicomData->save(storageLocal, "writeXfer=EXS_LittleEndianExplicit"))
			{
				SoError::post("Failed to save dicom object into file");
				return;
			}

			// delete the object
			if (outputDicomData)
			{
				outputDicomData->unref();
				outputDicomData = 0;
			}

			SO_ENGINE_OUTPUT(id, SoSFString, setValue(""));
		}
		catch (...)
		{
			SoDebugError::post( __FILE__, "Unexpected error in evaluate()" );
		}
	}
}

void SoXipSaveDicom::evaluate()
{
}
