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
#ifndef XIPDICOMSORTIMAGE_H
#define XIPDICOMSORTIMAGE_H

#include <xip/system/standard.h>

const float XIPDICOMSORT_UNDEFINED = -1.f;


/**	\struct XipDicomSortImageAttributes
 *	\brief Structure holding image attributes needed for sorting.
 * 
 *  This structure is used by XipDicomSortImage to store all needed attributes of an image
 *  that may be needed for the sorting operation.
 * 
 */
struct XipDicomSortImageAttributes
{	
public:
	/// Object name (loid or file name).
	const char* identifier;

	/// Patient ID.
	char* patientID;

	/// Patient's name.
	char* patientName;

	/// Study instance UID.
	char* studyUID;

	/// Series instance UID.
	char* seriesUID;

	/// SOP instance UID
	char* sopInstanceUID;

	/// Series time.
	char* seriesTime;

	/// Series description.
	char* seriesDescription;

	/// Modality (CT, MR ...).
	char* modality;

	/// Scan options.
	char* scanOptions;

	/// Image type (fields separated by '\').
	char* imageType;

	/// Image number.
	unsigned int imageNumber;

	/// Series number
	unsigned int seriesNumber;

	/// Image rows.
	unsigned short rows;

	/// Image columns.
	unsigned short columns;

	/// Image acquisition time.
	float acquisitionTime;

	/// Image trigger time.
	float triggerTime;

	/// Image trigger time.
	float echoTime;

	/// Image postion vector.
	double imagePosition[3];

	/// Image orientation (row and column vector).
	double imageOrientation[6];

	/// Z-position in object coordinates.
	double objectPositionZ;

	/// Pixel spacing (x, y).
	double pixelSpacing[2];

	/// Bits allocated.
	unsigned short bitsAllocated;

	/// Bits stored.
	unsigned short bitsStored;

	/// High bit.
	unsigned short highBit;

	/// MR scanning sequence.
	char* scanningSequence;

	/// MR image sequence variant
	char* sequenceVariant;

	/// Flag containing information about the pixel data encoding.
	unsigned int pixelDataEncoding;

	/// File containing the pixel data (0 if direct file-mapping is not supported).
	char* pixelDataFile;

	/// Pixel data offset.
	#ifdef WIN32
	unsigned __int64 pixelDataOffset;
	#else
	// #ifdef linux
	uint64_t pixelDataOffset;
	// #endif
	#endif

	/// Suggested sharename for the pixel data (0 if not supported).
	char* pixelDataSharename;

	/// pixel representation
	unsigned short pixelRepresentation;

	/// rescale
	float rescaleSlope;
	float rescaleIntercept;
};


/**	\class XipDicomSortImage
 *	\brief Utility class representing a single image in the sorting operation.
 *
 *	This encapsulates XipDicomSortImageAttributes and implements the assignemnet operator and
 *  copy constructor.
 *
 */
class XipDicomSortImage  
{
public:
	/// Default constructor.
	XipDicomSortImage();

	/// Copy constructor.
	XipDicomSortImage(const XipDicomSortImage &other);

	/// Assignment operator.
    XipDicomSortImage& operator =(const XipDicomSortImage& other);

	/// Destructor.
	virtual ~XipDicomSortImage();

	/// Resets image descriptor.
	virtual void reset();

	/// Returns a pointer to the image descriptor.
	virtual const XipDicomSortImageAttributes *getAttributes() const;
	virtual int setAttributes(const XipDicomSortImageAttributes *attr);

protected:
	/// Computes the position along the z-axis in object coordinates.
	double computePositionZ(double imageOrientation[6], double imagePosition[3]);
	void computeNormal(double imageOrientation[6]);

protected:
	/// Image descriptor containing queried information.
	XipDicomSortImageAttributes mDescriptor;	

	/// computed image orientation normal
	double mNormal[3];
};


#endif	// XIPDICOMSORTIMAGE_H

