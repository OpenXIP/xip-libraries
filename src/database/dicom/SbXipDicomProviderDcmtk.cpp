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


#include "SbXipDicomProviderDcmtk.h"
#include <Inventor/errors/SoErrors.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcostrmb.h>
#include <dcmtk/dcmdata/dcistrmb.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/fields/SoMFString.h>

#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <io.h>
#endif

#ifdef _WINDOWS
#define DIR_SEP_CHAR	'\\'
#define DIR_SEP_STRING	"\\"
#else
#define DIR_SEP_CHAR	'/'
#define DIR_SEP_STRING	"/"
#endif

// #ifdef linux
#ifndef WIN32

#include <wchar.h>
#include <stdexcept>
#include <errno.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <regex.h>

#endif


void SbXipDicomProviderDcmtk::initClass()
{
	static SbXipDicomProviderDcmtk defaultProvider;

	SoXipDataDicom::setProvider(&defaultProvider);
}

void* SbXipDicomProviderDcmtk::open()
{
	DcmFileFormat *fileFormat = new DcmFileFormat();
	if (!fileFormat)
	{
		SoMemoryError::post("DcmFileFormat");
	}
	
	return fileFormat;
}

void* SbXipDicomProviderDcmtk::open(const char *fileName, const char *options)
{
	DcmFileFormat *fileFormat = new DcmFileFormat();
	if (!fileFormat)
	{
		SoMemoryError::post("DcmFileFormat");
	}
	else
	{
		E_TransferSyntax readXfer = (E_TransferSyntax) parseInt(options, "readXfer", -1);
		E_GrpLenEncoding groupLength = (E_GrpLenEncoding) parseInt(options, "groupLength", 0);
		E_GrpLenEncoding maxReadLength = (E_GrpLenEncoding) parseInt(options, "maxReadLength", 4096);
		E_FileReadMode readMode = (E_FileReadMode) parseInt(options, "readMode", 0);

		if (!fileFormat->loadFile(fileName, readXfer, groupLength, maxReadLength, readMode).good())
		{
			SoError::post("Error loading file '%s'!", fileName);

			delete fileFormat;
			fileFormat = 0;
		}
	}

	return fileFormat;
}


void SbXipDicomProviderDcmtk::close(void *fileHandle)
{
	if (fileHandle)
		delete fileHandle;
}

SbBool SbXipDicomProviderDcmtk::save(void *fileHandle, const char *fileName, const char *options)
{
	if (fileHandle)
	{
		E_TransferSyntax writeXfer = (E_TransferSyntax) parseInt(options, "writeXfer", -1);
		E_EncodingType encodingType = (E_EncodingType) parseInt(options, "encodeType", 1);
		E_GrpLenEncoding groupLength = (E_GrpLenEncoding) parseInt(options, "groupLength", 0);
		E_PaddingEncoding padEncoding = (E_PaddingEncoding) parseInt(options, "padEncode", 0);

		if (((DcmFileFormat*) fileHandle)->saveFile(fileName, writeXfer, encodingType, groupLength, padEncoding).good())
		{
			return TRUE;
		}
	}

	return FALSE;
}

void *SbXipDicomProviderDcmtk::getDataset(void *fileHandle) const
{
	if (fileHandle)
		return ((DcmFileFormat*) fileHandle)->getDataset();

	return 0;
}


void *SbXipDicomProviderDcmtk::getMetaInfo(void *fileHandle) const
{
	if (fileHandle)
		return ((DcmFileFormat*) fileHandle)->getMetaInfo();

	return 0;
}


SbBool SbXipDicomProviderDcmtk::getPixelData(void *fileHandle, SbXipImage &image, int sliceIndex, const char *options, void* pixelDataItem)
{
	SbBool returnCode = FALSE;

	DcmFileFormat* fileFormat = (DcmFileFormat*) fileHandle;
	if (!fileFormat)
		return FALSE;

	DcmDataset *dataset = fileFormat->getDataset();
	if (!dataset)
		return FALSE;


	OFCondition errorFlag;
	DcmStack stack;
	DcmElement *element;

	// image attributes
	unsigned short width = 0;
	unsigned short height = 0;
	unsigned short bitsStored = 0;
	unsigned short bitsAllocated = 0;
	unsigned short samplesPerPixel = 0;
	unsigned short numberOfSlices = 1;
	unsigned short pixelRepresentation = 0;	// unsigned short
	double zSpacing = 1.0;
	double spacing[2] = { 1.0, 1.0 };
	double imagePositionPatient[3] = {0};
	double imageOrientationPatient[6] = { 1.0, 0.0, 0.0,
		                                  0.0, -1.0, 0.0 };
	double shearYZ = 0, shearXY = 0, shearXZ = 0;


	try
	{
		// row
		errorFlag = dataset->findAndGetUint16(DCM_Rows, height);
		if (!errorFlag.good())
			throw "Rows";

		// column
		errorFlag = dataset->findAndGetUint16(DCM_Columns, width);
		if (!errorFlag.good())
			throw "Columns";

		// bits stored
		errorFlag = dataset->findAndGetUint16(DCM_BitsStored, bitsStored);
		if (!errorFlag.good())
			throw "BitsStored";

		// bits allocated
		errorFlag = dataset->findAndGetUint16(DCM_BitsAllocated, bitsAllocated);
		if (!errorFlag.good())
			throw "BitsAllocated";

		// samples per pixel
		errorFlag = dataset->findAndGetUint16(DCM_SamplesPerPixel, samplesPerPixel);
		if (!errorFlag.good())
			throw "SamplesPerPixel";

		// pixel representation
		errorFlag = dataset->findAndGetUint16(DCM_PixelRepresentation, pixelRepresentation);
		if (!errorFlag.good())
			throw "PixelRepresentation";

		// number of slices
		if ( dataset->search(DCM_NumberOfSlices, stack) == EC_Normal)
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_US)
				element->getUint16(numberOfSlices);
		}
		else if ( dataset->search(DCM_NumberOfFrames, stack) == EC_Normal )	// number of frames
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
		if ( dataset->search(DCM_SliceThickness, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
				element->getFloat64(zSpacing);
		}

		// pixel spacing
		if ( dataset->search(DCM_PixelSpacing, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (unsigned int i = 0; i < element->getVM(); i++)
					element->getFloat64(spacing[i], i);
			}
		}

		// patient position
		if ( dataset->search(DCM_ImagePositionPatient, stack) == EC_Normal )
		{
			element = OFstatic_cast(DcmElement *, stack.top());

			if (element->ident() == EVR_DS)
			{
				for (unsigned int i = 0; i < element->getVM(); i++)
					element->getFloat64(imagePositionPatient[i], i);
			}
		}

		// patient orientation
		if ( dataset->search(DCM_ImageOrientationPatient, stack) == EC_Normal )
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

		// shearYZ
		if ( dataset->search(DCM_GantryDetectorTilt, stack) == EC_Normal )
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

		SbMatrix modelMatrix;
		modelMatrix.setTransform(pos, SbRotation(rotMatrix), scale);
		modelMatrix = shearMatrix * modelMatrix;

		// single slice extraction?
		unsigned int pixelOffset = 0;
		if (sliceIndex >= 0)
		{
			if (sliceIndex > numberOfSlices)
				throw "invalid slice number";

			modelMatrix[2][0] /= numberOfSlices;
			modelMatrix[2][1] /= numberOfSlices;
			modelMatrix[2][2] /= numberOfSlices;

			modelMatrix[3][0] += sliceIndex * modelMatrix[2][0];
			modelMatrix[3][1] += sliceIndex * modelMatrix[2][1];
			modelMatrix[3][2] += sliceIndex * modelMatrix[2][2];

			numberOfSlices = 1;
			pixelOffset = sliceIndex * (width * height * samplesPerPixel);
		}

		// get the DICOM pixel data pointer
		unsigned long pixelBufferSize = 0;
		DcmPixelData *pixelData;

		if ( dataset->search(DCM_PixelData, stack, ESM_fromHere, OFFalse) == EC_Normal )
		{
			if (stack.top()->ident() == EVR_PixelData)
			{
				pixelData = (DcmPixelData *)stack.top();
				pixelBufferSize = pixelData->getLength();

				SbXipImage::ComponentType compType = SbXipImage::SEPARATE;
				SbXipImage::ComponentLayoutType compLayoutType = SbXipImage::LUMINANCE;

				// color image?
				if (samplesPerPixel == 3)
				{
					compType = SbXipImage::INTERLEAVED;
					compLayoutType = SbXipImage::RGB;
				}

				switch (pixelData->getVR())
				{
				case EVR_OW:
					{
						Uint16 *pixelBuffer = 0;
						pixelData->getUint16Array(pixelBuffer);
						image.init(
							SbXipImageDimensions(width, height, numberOfSlices),
							(pixelRepresentation == 1) ? SbXipImage::SHORT : SbXipImage::UNSIGNED_SHORT, 
							bitsStored,
							pixelBuffer + pixelOffset,
							samplesPerPixel,
							compType,
							compLayoutType, 
							modelMatrix);
						returnCode = TRUE;
					} break;

				case EVR_OB:
					{
						Uint8 *pixelBuffer = 0;
						pixelData->getUint8Array(pixelBuffer);

						image.init(
							SbXipImageDimensions(width, height, numberOfSlices),
							SbXipImage::UNSIGNED_BYTE, 
							bitsStored,
							pixelBuffer + pixelOffset,
							samplesPerPixel, 
							compType,
							compLayoutType, 
							modelMatrix);
						returnCode = TRUE;
					} break;
				default:
					SoError::post("Unsupported value representation of pixel format.");
				}
			}
		}
	}
	catch(...)
	{
		SoError::post("Unsupported dataset for pixel data access.");
	}

	return returnCode;
}


int SbXipDicomProviderDcmtk::getNumSlices(void *fileHandle, const char *options, void* pixelDataItem)
{
	DcmFileFormat* fileFormat = (DcmFileFormat*) fileHandle;
	if (!fileFormat)
		return 0;

	DcmDataset *dataset = fileFormat->getDataset();
	if (!dataset)
		return 0;

	// number of slices
	OFCondition errorFlag;
	DcmStack stack;
	DcmElement *element;
	unsigned short numberOfSlices = 1;

	if ( dataset->search(DCM_NumberOfSlices, stack) == EC_Normal)
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_US)
			element->getUint16(numberOfSlices);
	}
	else if ( dataset->search(DCM_NumberOfFrames, stack) == EC_Normal )	// number of frames
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_IS)
		{
			OFString value;
			element->getOFString(value, 0);
			numberOfSlices = ::atoi(value.c_str());
		}
	}

	return numberOfSlices;
}


SbBool  SbXipDicomProviderDcmtk::isOfType(void *item, const char *type) const
{
	if (item && type)
	{
		return (strcmp(type, "DcmItem") == 0);
	}

	return FALSE;
}

void* SbXipDicomProviderDcmtk::createCompatible(void *metaInfoHandle, void *datasetHandle)
{
	if (!(metaInfoHandle && datasetHandle))
		return NULL;

	DcmFileFormat *fileFormat = new DcmFileFormat();
	if (!fileFormat)
	{
		SoMemoryError::post("DcmFileFormat");
	}
	
	try
	{
		// get dicom meta info header
		DcmMetaInfo *metaInfo = (DcmMetaInfo *)(((SbXipDicomItemHandle *)metaInfoHandle)->getItem());
		if (!metaInfo)
		{
			SoMemoryError::post("DcmMetaInfo");
		}

		// get dicom dataset
		DcmDataset *dataset = (DcmDataset *)(((SbXipDicomItemHandle *)metaInfoHandle)->getItem());
		if (!dataset)
		{
			SoMemoryError::post("DcmDataset");
		}

		E_TransferSyntax opt_oxfer = EXS_LittleEndianExplicit;
		
		Uint32 elementLength = metaInfo->calcElementLength(opt_oxfer, EET_UndefinedLength) + 
			                   dataset->calcElementLength(opt_oxfer, EET_UndefinedLength);

		// create buffer
		unsigned char *buffer = new unsigned char[elementLength];
		if (!buffer)
		{
			SoMemoryError::post("Failed to create memory");
		}

		DcmOutputBufferStream outStream(buffer, elementLength);

		// transfer meta info header
		metaInfo->transferInit();

		if (metaInfo->write(outStream, opt_oxfer, EET_UndefinedLength) != EC_Normal)
		{
			SoError::post("Error writting meta info header into output buffer stream");
		}

		metaInfo->transferEnd();

		// transfer dataset
		dataset->transferInit();

		if (dataset->write(outStream, opt_oxfer, EET_UndefinedLength) != EC_Normal)
		{
			SoError::post("Error writting data object element into output buffer stream");
		}

		dataset->transferEnd();

		DcmInputBufferStream inputStream;
		inputStream.setBuffer(buffer, elementLength);

		fileFormat->transferInit();

		fileFormat->read(inputStream);

		if ((fileFormat->error() != EC_Normal) && (fileFormat->error() != EC_StreamNotifyClient))
		{
			SoError::post("Error reading from input buffer stream");
		}

		fileFormat->transferEnd();

	}
	catch(...)
	{
		if (fileFormat)
		{
			delete fileFormat;
			fileFormat = 0;
		}

		SoError::post("Failed to create compatible DICOM object");
	}

	return fileFormat;
}

SbBool  SbXipDicomProviderDcmtk::tagExists(void *item, const SbXipDicomTagKey &key, SbBool searchIntoSub)
{
	if (item)
	{
		return ((DcmItem*) item)->tagExists(DcmTagKey(key.getGroup(), key.getElement()), searchIntoSub ? OFTrue : OFFalse);
	}

	return FALSE;
}


SbBool  SbXipDicomProviderDcmtk::tagExistsWithValue(void *item, const SbXipDicomTagKey &key, SbBool searchIntoSub)
{
	if (item)
	{
		return ((DcmItem*) item)->tagExistsWithValue(DcmTagKey(key.getGroup(), key.getElement()), searchIntoSub ? OFTrue : OFFalse);
	}

	return FALSE;
}


SbBool  SbXipDicomProviderDcmtk::findAndGet(const void *item, const SbXipDicomTagKey &key, SbString &value, SbBool searchIntoSub)
{
	if (item)
	{
		OFString str;
		if (((DcmItem*) item)->findAndGetOFStringArray(DcmTagKey(key.getGroup(), key.getElement()), str, searchIntoSub ? OFTrue : OFFalse).good())
		{
			value = SbString(str.c_str());
			return TRUE;
		}
	}

	return FALSE;
}


void    SbXipDicomProviderDcmtk::remove(void *item, const SbXipDicomTagKey &key)
{
	if (item)
	{
		((DcmItem*) item)->remove(DcmTagKey(key.getGroup(), key.getElement()));
	}
}


SbPList SbXipDicomProviderDcmtk::search(void *item, const SbXipDicomTagKey &key, int searchMode, SbBool searchIntoSub)
{
	SbPList list;

	if (item)
	{
		DcmStack resultStack;
		DcmTagKey searchKey;

		if (((DcmItem*) item)->search(DcmTagKey(key.getGroup(), key.getElement()), resultStack, (E_SearchMode) searchMode, searchIntoSub ? OFTrue : OFFalse).good())
		{
			for (unsigned int i = 0; i < resultStack.card(); i++)
			{
				list.append(resultStack.elem(i));
			}
		}
	}

	return list;
}

static int findFilesInFolder(const char *dir, SoMFString &out)
{
#ifdef WIN32 
	struct _finddata_t c_file;
	long hFile;

	if ((hFile = _findfirst(dir, &c_file)) == -1L)
	{
		// not a valid file or directory
		return -1;
	}
	else
	{
		// something matches, remove patten/file name
		SbString folder;
		const char *s = strrchr(dir, DIR_SEP_CHAR);
		if (s)
			folder = SbString(dir).getSubString(0, s - dir);

		do 
		{
			// find all files in directories
			if (c_file.attrib & _A_SUBDIR)
			{
				if ( (strcmp(c_file.name, ".") == 0) || (strcmp(c_file.name, "..") == 0))
					continue;

				SbString search(folder);
				search += SbString(c_file.name);
				search += SbString(DIR_SEP_STRING "*.*");

				findFilesInFolder(search.getString(), out);
			}
			else
			{
				SbString fullPath(folder);
				fullPath += SbString(c_file.name);
				out.set1Value(out.getNum(), fullPath);
			}
		} while (_findnext(hFile, &c_file) == 0);

		_findclose( hFile );
	}

#else 
// #ifdef linux

	// something matches, remove patten/file name
	SbString folder;
	SbString remain;
	regex_t reg;
	const char *s = strrchr(dir, DIR_SEP_CHAR);
	if (s)
	{
		folder = SbString(dir).getSubString(0, s - dir);
		remain= SbString(dir).getSubString(s - dir+1);
	}
	string path=folder.getString();
	string pattern=remain.getString();

	if (regcomp(&reg, pattern.c_str(), REG_EXTENDED | REG_NOSUB))
        return -1;

    DIR* d = opendir( path.c_str());
    static struct dirent* dirp;
  
    if (! d)
    {
        cerr << "Unable to open directory " << path.c_str() << endl;
        cerr << "Error is " << strerror(errno) << "(" << errno << ")" << endl;
        return -1;
    } 
   
	while ( (dirp = readdir(d)) != NULL )
    {
		if (!regexec(&reg, dirp->d_name, 0, NULL, 0))
		{
	        if ( 0 == strcmp( ".", dirp->d_name ) || 0 == strcmp( "..",dirp->d_name ) ) continue; // skip . and ..
			string candidate( path + dirp->d_name );
	        try {
				//Find the mode of File or directory
				struct stat _stat;
				if ( 0 > lstat(candidate.c_str(), &_stat) )
				{
		    		throw invalid_argument("Unable to stat file");
				}
		    	if ( S_ISREG(_stat.st_mode)) //check whether given Path is File
		    	{
								
					SbString fullPath(folder);
					fullPath += SbString(dirp->d_name);
					out.set1Value(out.getNum(), fullPath);	

		    	}
		    	else if ( S_ISDIR(_stat.st_mode)) //check whether given Path is Directory
		    	{
				SbString search(folder);
				search += SbString(dirp->d_name);
				search += SbString(DIR_SEP_STRING "*.*");
				findFilesInFolder(search.getString(), out);
		  
		    	}
			}
        	catch ( const invalid_argument& ia )
        	{
            		cerr << "Caught exception on path " << candidate << ":  " << ia.what() << endl;
			}
		}
    }
    closedir(d);
// #endif //linux
#endif /* WIN32 */

	return 0;
}


SbBool SbXipDicomProviderDcmtk::interpret(const SoMFString &in, SoMFString &out)
{
	for (int i = 0; i < in.getNum(); i++)
	{
		SbString fileName = in[i];

		if (fileName.getSubString(fileName.getLength() - 8) == SbString("DICOMDIR"))
		{
			// DICOM directory
			DcmFileFormat dcmDirectory;
			if (dcmDirectory.loadFile(fileName.getString()) == EC_Normal)
			{
				// truncate to path only (minus "DICOMDIR")
				fileName.deleteSubString(fileName.getLength() - 8);

				DcmObject* dobj = 0;
				DcmStack stack;

				while (dcmDirectory.search(DCM_ReferencedFileID, stack, ESM_afterStackTop, OFTrue) == EC_Normal)
				{
					dobj =	stack.top();
					if (!dobj || dobj->ident() != EVR_CS)
						continue; // search at least next element

					char * str = NULL;
					((DcmByteString*) dobj)->getString(str);

					SbString fullPath = fileName;
					fullPath += SbString(str);
					out.set1Value(out.getNum(), fullPath);
				}
			}
		}
		else
		{
			findFilesInFolder(fileName.getString(), out);
		}
	}

	return TRUE;
}

