/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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
				for (int i = 0; i < element->getVM(); i++)
					element->getFloat64(spacing[i], i);
			}
		}

		// patient position
		if ( dataSet->search(DCM_ImagePositionPatient, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (int i = 0; i < element->getVM(); i++)
					element->getFloat64(imagePositionPatient[i], i);
			}
		}

		// patient orientation
		if ( dataSet->search(DCM_ImageOrientationPatient, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (int i = 0; i < element->getVM(); i++)
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
									SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, dicomAttributes.numberOfSlices), SbXipImage::UNSIGNED_SHORT, dicomAttributes.bitsStored, 
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

		for (int i = 1; i < num; i++)
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
				for (int i = 0; i < element->getVM(); i++)
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
				for (int i = 0; i < element->getVM(); i++)
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
				                   SbXipImageDimensions(dicomAttributes.width, dicomAttributes.height, depth), SbXipImage::UNSIGNED_SHORT, dicomAttributes.bitsStored, 
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

			for (int i = 0; i < num; i++)
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