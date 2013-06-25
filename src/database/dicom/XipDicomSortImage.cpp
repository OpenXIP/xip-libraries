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
#include "XipDicomSortImage.h"
#include <memory.h>
#include <string.h>

#if defined(WIN32) || defined (linux)
#include <malloc.h>
#else //MAC OS
#include <sys/malloc.h>
#endif //WIN32

/**
 *
 *	Initializes all fields in the descriptor to zero.
 *
 */
XipDicomSortImage::XipDicomSortImage()
{
	memset(&mDescriptor, 0, sizeof(mDescriptor));
	mDescriptor.acquisitionTime = XIPDICOMSORT_UNDEFINED;
	mDescriptor.triggerTime = XIPDICOMSORT_UNDEFINED;
	mDescriptor.echoTime = XIPDICOMSORT_UNDEFINED;
	mDescriptor.rescaleSlope = 1.f;

	mNormal[0] = 0;
	mNormal[1] = 0;
	mNormal[2] = 0;
}


/**
 *
 *	Uses the assignment operator to create a copy of a XipDicomSortImage instance.
 *
 *	\param other Reference to instance of XipDicomSortImage, which is copied.
 *
 */
XipDicomSortImage::XipDicomSortImage(const XipDicomSortImage &other)
{
	memset(&mDescriptor, 0, sizeof(mDescriptor));

	try
	{
		// use assignment operator to copy content
		*this = other;
	}
	catch (...)
	{
		// free partially allocated content
		this->reset();
	}
}


/**
 *
 *	Frees previously allocated attributes in the descriptor and resets all values to zero.
 *
 */
void XipDicomSortImage::reset()
{
	if (mDescriptor.identifier) 
	{	
		free((void*) mDescriptor.identifier);
		mDescriptor.identifier = 0;
	}
	
	if (mDescriptor.patientName) 
	{
		free(mDescriptor.patientName);
		mDescriptor.patientName = 0;
	}
	if (mDescriptor.patientID)
	{
		free(mDescriptor.patientID);
		mDescriptor.patientID = 0;
	}
	if (mDescriptor.studyUID) 
	{
		free(mDescriptor.studyUID);
		mDescriptor.studyUID = 0;
	}

	if (mDescriptor.seriesUID)
	{
		free(mDescriptor.seriesUID);
		mDescriptor.seriesUID = 0;
	}

	if (mDescriptor.sopInstanceUID) 
	{
		free(mDescriptor.sopInstanceUID);
		mDescriptor.sopInstanceUID = 0;
	}

	if (mDescriptor.seriesTime) 
	{
		free(mDescriptor.seriesTime);
		mDescriptor.seriesTime = 0;
	}
	if (mDescriptor.modality) 
	{
		free(mDescriptor.modality);
		mDescriptor.modality = 0;
	}

	if (mDescriptor.scanOptions)
	{
		free(mDescriptor.scanOptions);
		mDescriptor.scanOptions = 0;
	}
	if (mDescriptor.imageType)
	{
		free(mDescriptor.imageType);
		mDescriptor.imageType = 0;		
	}
	if (mDescriptor.seriesDescription) 
	{
		free(mDescriptor.seriesDescription);
		mDescriptor.seriesDescription = 0;
	}
	if (mDescriptor.scanningSequence)
	{
		free(mDescriptor.scanningSequence);
		mDescriptor.scanningSequence = 0;
	}
	if (mDescriptor.sequenceVariant) 
	{
		free(mDescriptor.sequenceVariant);
		mDescriptor.sequenceVariant = 0;
	}
	if (mDescriptor.pixelDataFile) 
	{
		free(mDescriptor.pixelDataFile);
		mDescriptor.pixelDataFile = 0;
	}
	if (mDescriptor.pixelDataSharename) 
	{
		free(mDescriptor.pixelDataSharename);
		mDescriptor.pixelDataSharename = 0;
	}

	memset(&mDescriptor, 0, sizeof(mDescriptor));
	mDescriptor.acquisitionTime = XIPDICOMSORT_UNDEFINED;
	mDescriptor.triggerTime = XIPDICOMSORT_UNDEFINED;
	mDescriptor.echoTime = XIPDICOMSORT_UNDEFINED;
	mDescriptor.rescaleSlope = 1.f;

	mNormal[0] = 0;
	mNormal[1] = 0;
	mNormal[2] = 0;
}


/**
 *
 *	Clones all values of a XipDicomSortImage instance.
 *
 *	\param other Reference to instance of XipDicomSortImage, which is copied.
 *
 */
XipDicomSortImage& XipDicomSortImage::operator =(const XipDicomSortImage& other)
{
    // prevent self-assignment
    if(&other == this)
    {
        return *this;
    }

	setAttributes(other.getAttributes());

    return(*this);
}


/**
 *
 *	Calls XipDicomSortImage::reset to free all descriptor attributes.
 *
 */
XipDicomSortImage::~XipDicomSortImage()
{
	this->reset();
}


/**
 * 
 *  \return Constant pointer to internal image descriptor structure. The pointer is valid as long
 *			this instance is alive.
 * 
 */
const XipDicomSortImageAttributes *XipDicomSortImage::getAttributes() const
{
	return ((const XipDicomSortImageAttributes*) &mDescriptor);
}


/**
 * 
 *  Sets the attributes for this image.
 * 
 *  \return Returns 0 when successful, otherwise -1 (out of memory).
 * 
 */
int XipDicomSortImage::setAttributes(const XipDicomSortImageAttributes *attr)
{
	int rc = 0;

	// free allocated memory
	reset();

	// copy entire descriptor
	mDescriptor = *attr;

	// make new copy of all strings...
	if (attr->patientName)
	{
		mDescriptor.patientName = strdup(attr->patientName);
		if (!mDescriptor.patientName) rc = -1;
	}

	if (attr->patientID)
	{
		mDescriptor.patientID = strdup(attr->patientID);
		if (!mDescriptor.patientID) rc = -1;
	}

	if (attr->identifier)
	{
		mDescriptor.identifier = strdup(attr->identifier);
		if (!mDescriptor.identifier) rc = -1;
	}

	if (attr->studyUID)
	{
		mDescriptor.studyUID = strdup(attr->studyUID);
		if (!mDescriptor.studyUID) rc = -1;
	}

	if (attr->seriesUID)
	{
		mDescriptor.seriesUID = strdup(attr->seriesUID);
		if (!mDescriptor.seriesUID) rc = -1;
	}

	if (attr->sopInstanceUID)
	{
		mDescriptor.sopInstanceUID = strdup(attr->sopInstanceUID);
		if (!mDescriptor.sopInstanceUID) rc = -1;
	}

	if (attr->seriesTime)
	{
		mDescriptor.seriesTime = strdup(attr->seriesTime);
		if (!mDescriptor.seriesTime) rc = -1;
	}

	if (attr->modality)
	{
		mDescriptor.modality = strdup(attr->modality);
		if (!mDescriptor.modality) rc = -1;
	}

	if (attr->scanOptions)
	{
		mDescriptor.scanOptions = strdup(attr->scanOptions);
		if (!mDescriptor.scanOptions) rc = -1;
	}

	if (attr->imageType)
	{
		mDescriptor.imageType = strdup(attr->imageType);
		if (!mDescriptor.imageType) rc = -1;
	}

	if (attr->seriesDescription)
	{
		mDescriptor.seriesDescription = strdup(attr->seriesDescription);
		if (!mDescriptor.seriesDescription) rc = -1;
	}

	if (attr->scanningSequence)
	{
		mDescriptor.scanningSequence = strdup(attr->scanningSequence);
		if (!mDescriptor.scanningSequence) rc = -1;
	}

	if (attr->sequenceVariant)
	{
		mDescriptor.sequenceVariant = strdup(attr->sequenceVariant);
		if (!mDescriptor.sequenceVariant) rc = -1;
	}

	if (attr->pixelDataFile)
	{
		mDescriptor.pixelDataFile = strdup(attr->pixelDataFile);
		if (!mDescriptor.pixelDataFile) rc = -1;
	}

	if (attr->pixelDataSharename)
	{
		mDescriptor.pixelDataSharename = strdup(attr->pixelDataSharename);
		if (!mDescriptor.pixelDataSharename) rc = -1;
	}


	// update computed values
	mDescriptor.objectPositionZ = computePositionZ(mDescriptor.imageOrientation, mDescriptor.imagePosition);


	return rc;
}


/**
 * 
 *  Internal method to compute position of a slice along the z-axis in object space.
 *
 *	\param	imageOrientation	Orientation of the image (row and column vector as stored in DICOM).
 *	\param  imagePosition		Image position vector.
 *  \return Position along the z-axis in object coordinates.
 * 
 */
double XipDicomSortImage::computePositionZ(double imageOrientation[6], double imagePosition[3])
{
	// compute normal and z-Order
	computeNormal(imageOrientation);

	// position.dot(normal)
	return (imagePosition[0] * mNormal[0] + imagePosition[1] * mNormal[1] + imagePosition[2] * mNormal[2]);
}


/**
 * 
 *  Internal method to compute image normal given the row and column vectors.
 *
 *	\param	imageOrientation	Orientation of the image (row and column vector as stored in DICOM).
 *	\param  normal_out			Receives the normal vector.
 * 
 */
void XipDicomSortImage::computeNormal(double imageOrientation[6])
{
	// compute depth order
	double *row = imageOrientation;
	double *col = imageOrientation + 3;
	double nor[3];
	const double *matrix[3] = { row, col, nor };

	mNormal[0] = row[1] * col[2] - row[2] * col[1];
	mNormal[1] = -(row[0] * col[2] - row[2] * col[0]);
	mNormal[2] = row[0] * col[1] - row[1] * col[0];
}



/**
 * 
 *  Opens a data object referenced by identifier using the dataObject interface and queries
 *	all necessary information for sorting (stored in RadImageDescriptor structure). The
 *	caller can access this information later using XipDicomSortImage::getDescriptor.
 *
 *	\param	objectName	Specifies the object Name 
 *	\param	dataObject	Pointer to RadDataObjectBase object
 * 
 */
 /*
void XipDicomSortImage::initialize(const wchar_t* objectName, RadDataObjectBase* dataObject)
{
	if(!objectName || !dataObject)
	{
		throw RadException(__LINE__, __FILE__, RadException::INVALID_PARAM_ERROR, L"objectName / dataObject is NULL");
	}
		
	int val= 0;
	double pos[3] = { 0.0,0.0,0.0};
	double doubleVal=0.0;
	wchar_t tmp[MAX_PATH + 1];
	unsigned int dimension = 0;


	this->reset();
	memset(tmp, 0, sizeof(tmp));				

	//
	//	DICOM Type 1 elements are not checked for availablity. All other elements are
	//	checked for availability. Additionally, some elements are checked for dimension also, because, 
	//	it may be possible that the elements may be present in the DICOM element list contained in the 
	//	dataObject, but the value is NULL 
    //

	try
	{
		mDescriptor.objectName = _wcsdup(objectName);
		if (!mDescriptor.objectName)
		{
			throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
		}

		// open the data object and query for the necessary objects
		dataObject->open(mDescriptor.objectName);

		// Patient Name
		if (dataObject->getElement(RAD_PATIENTSNAME_DICOMGROUP, RAD_PATIENTSNAME_DICOMELEMENT,
								  RadDataObjectBase::STRING, 1, sizeof(tmp), tmp) )
		{							
			mDescriptor.patientName = _wcsdup(tmp);
			if (!mDescriptor.patientName)
			{
				throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
			}
		}

		// Patient ID if available
		if( dataObject->getElementProperty( RAD_PATIENTID_DICOMGROUP, RAD_PATIENTID_DICOMELEMENT, RAD_DATA_PROP_EXISTS ) ) 
		{
			dimension = dataObject->getElementProperty(RAD_PATIENTID_DICOMGROUP, RAD_PATIENTID_DICOMELEMENT, RAD_DATA_PROP_DIMENSION);
			if(dimension)
			{
				if (dataObject->getElement(RAD_PATIENTID_DICOMGROUP, RAD_PATIENTID_DICOMELEMENT,
										  RadDataObjectBase::STRING, 1, sizeof(tmp), tmp) )
				{							
					mDescriptor.patientID = _wcsdup(tmp);
					if (!mDescriptor.patientID)
					{
						throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
					}
				}
			}
		}
		// Study Instance UID
		if (dataObject->getElement(RAD_STUDY_INSTANCE_UID_DICOMGROUP, RAD_STUDY_INSTANCE_UID_DICOMELEMENT,
								  RadDataObjectBase::STRING, 1,  sizeof(tmp), tmp) )
		{							
			mDescriptor.studyUID = _wcsdup(tmp);		
			if (!mDescriptor.studyUID)
			{
				throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
			}
		}								

		// Series Instance UID
		if (dataObject->getElement(RAD_SERIES_INSTANCE_UID_DICOMGROUP, RAD_SERIES_INSTANCE_UID_DICOMELEMENT,
								  RadDataObjectBase::STRING, 1,  sizeof(tmp), tmp))
		{			
			mDescriptor.seriesUID = _wcsdup(tmp);		
			if (!mDescriptor.seriesUID)
			{
				throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
			}
		}								

		// SOPInstance UID
		if (dataObject->getElement(RAD_IMAGE_INSTANCE_UID_DICOMGROUP, RAD_IMAGE_INSTANCE_UID_DICOMELEMENT,
								  RadDataObjectBase::STRING, 1,  sizeof(tmp), tmp))
		{			
			mDescriptor.sopInstanceUID = _wcsdup(tmp);		
			if (!mDescriptor.sopInstanceUID)
			{
				throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
			}
		}								

		//Series Time if available
		if( dataObject->getElementProperty( RAD_SERIES_TIME_DICOMGROUP, 
											RAD_SERIES_TIME_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {		
			dimension = dataObject->getElementProperty(RAD_SERIES_TIME_DICOMGROUP,
				                                       RAD_SERIES_TIME_DICOMELEMENT , 
													   RAD_DATA_PROP_DIMENSION ) ;
			if ( dimension )
			{
				dataObject->getElement(RAD_SERIES_TIME_DICOMGROUP, RAD_SERIES_TIME_DICOMELEMENT,
									  RadDataObjectBase::STRING, dimension,  sizeof(tmp), tmp) ;				
				mDescriptor.seriesTime = _wcsdup(tmp);
				if (!mDescriptor.seriesTime)
				{
					throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
				}
			}
		}

		//Modality
		if (dataObject->getElement(RAD_MODALITY_DICOMGROUP, RAD_MODALITY_DICOMELEMENT,
								  RadDataObjectBase::STRING, 1,  sizeof(tmp), tmp))
		{							
			mDescriptor.modality = _wcsdup(tmp);			
			if (!mDescriptor.modality)
			{
				throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
			}
		}	

		//Series description if available
		if( dataObject->getElementProperty( RAD_SERIES_DESCRIPTION_DICOMGROUP, 
											RAD_SERIES_DESCRIPTION_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS) ) 
        {		
			dataObject->getElement(RAD_SERIES_DESCRIPTION_DICOMGROUP, RAD_SERIES_DESCRIPTION_DICOMELEMENT, 
									  RadDataObjectBase::STRING, 1, sizeof(tmp), tmp) ;

			mDescriptor.seriesDescription = _wcsdup(tmp);
			if (!mDescriptor.seriesDescription)
			{
				throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
			}
		}

		//Scan Options if available
		if( dataObject->getElementProperty( RAD_SCANOPTIONS_DICOMGROUP, 
											RAD_SCANOPTIONS_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {		
			dataObject->getElement(RAD_SCANOPTIONS_DICOMGROUP, RAD_SCANOPTIONS_DICOMELEMENT, 
									  RadDataObjectBase::STRING, 1, sizeof(tmp), tmp) ;

			mDescriptor.scanOptions = _wcsdup(tmp);
			if (!mDescriptor.scanOptions)
			{
				throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
			}
		}

		// image type
		if (dataObject->getElementProperty(RAD_IMAGE_TYPE_DICOMGROUP, RAD_IMAGE_TYPE_DICOMELEMENT, RAD_DATA_PROP_EXISTS))
		{			
			dimension = dataObject->getElementProperty(RAD_IMAGE_TYPE_DICOMGROUP, RAD_IMAGE_TYPE_DICOMELEMENT, RAD_DATA_PROP_DIMENSION);
			if(dimension)
			{
				int len = dataObject->getElement(RAD_IMAGE_TYPE_DICOMGROUP, RAD_IMAGE_TYPE_DICOMELEMENT,
					  RadDataObjectBase::STRING, dimension, sizeof(tmp), tmp);

				// replace field null-terminators by '\'
				for (int c = 0; c < (len - 1); c++) if (!tmp[c]) tmp[c] = '\\';

				mDescriptor.imageType = _wcsdup(tmp);
				if (!mDescriptor.imageType)
				{
					throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
				}
			}
		}

		//Image Number if available
		if( dataObject->getElementProperty( RAD_IMAGE_NUMBER_DICOMGROUP, 
											RAD_IMAGE_NUMBER_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {		
			dataObject->getElement(RAD_IMAGE_NUMBER_DICOMGROUP, RAD_IMAGE_NUMBER_DICOMELEMENT, 
									  RadDataObjectBase::STRING, 1, sizeof(tmp), tmp) ;

			mDescriptor.imageNumber = _wtoi(tmp); //if present , must be 1
		}

		//Series Number if available
		if( dataObject->getElementProperty( RAD_SERIES_NUMBER_DICOMGROUP, 
											RAD_SERIES_NUMBER_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {		
			dataObject->getElement(RAD_SERIES_NUMBER_DICOMGROUP, RAD_SERIES_NUMBER_DICOMELEMENT, 
									  RadDataObjectBase::STRING, 1, sizeof(tmp), tmp) ;

			mDescriptor.seriesNumber = _wtoi(tmp); //if present , must be 1
		}

		//Image position patient
		if (!dataObject->getElement(RAD_IMAGE_POSITIONPATIENT_DICOMGROUP, RAD_IMAGE_POSITIONPATIENT_DICOMELEMENT,
								  RadDataObjectBase::FLT64, 3, sizeof(double)*3, &(mDescriptor.imagePosition) ))
		{
			throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"image position patient unknown");
		}


		//Image Acquisition time if available
		if( dataObject->getElementProperty( RAD_IMAGE_ACQUITISIONTIME_DICOMGROUP, 
											RAD_IMAGE_ACQUITISIONTIME_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
		{
			dimension = dataObject->getElementProperty( RAD_IMAGE_ACQUITISIONTIME_DICOMGROUP,
				                                        RAD_IMAGE_ACQUITISIONTIME_DICOMELEMENT , 
														RAD_DATA_PROP_DIMENSION ) ;
			if(dimension)
			{
				dataObject->getElement(RAD_IMAGE_ACQUITISIONTIME_DICOMGROUP, RAD_IMAGE_ACQUITISIONTIME_DICOMELEMENT, 
										  RadDataObjectBase::STRING, dimension, sizeof(tmp), tmp) ;
				
				swscanf(tmp, L"%f", &mDescriptor.acquisitionTime);			
			}
		}

		//Image Trigger time if available
		if( dataObject->getElementProperty( RAD_IMAGE_TRIGGER_TIME_DICOMGROUP, 
											RAD_IMAGE_TRIGGER_TIME_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
		{
			dimension = dataObject->getElementProperty( RAD_IMAGE_TRIGGER_TIME_DICOMGROUP,
				                                        RAD_IMAGE_TRIGGER_TIME_DICOMELEMENT, 
														RAD_DATA_PROP_DIMENSION ) ;
			if(dimension)
			{
				dataObject->getElement(RAD_IMAGE_TRIGGER_TIME_DICOMGROUP, RAD_IMAGE_TRIGGER_TIME_DICOMELEMENT, 
									   RadDataObjectBase::STRING, dimension, sizeof(tmp), tmp) ;

				swscanf(tmp, L"%f", &mDescriptor.triggerTime);
			}
		}
		else
		{
			// for CT trigger time is store in scanOptions
			if ((wcsncmp(mDescriptor.modality, L"CT", 2) == 0) && mDescriptor.scanOptions)
			{
				wchar_t *timePos = wcsstr(mDescriptor.scanOptions, L"TP");
				if (timePos)
				{
					float time = XIPDICOMSORT_UNDEFINED;
					if (swscanf(timePos, L"TP%f", &time) == 1)
					{
						// succesfull
						mDescriptor.triggerTime = time;
					}
				}
			}
		}

		// echo time if available
		if( dataObject->getElementProperty( RAD_ECHOTIME_DICOMGROUP, 
											RAD_ECHOTIME_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS)) 
		{
			dimension = dataObject->getElementProperty( RAD_ECHOTIME_DICOMGROUP,
				                                        RAD_ECHOTIME_DICOMELEMENT, 
														RAD_DATA_PROP_DIMENSION) ;
			if(dimension)
			{
				dataObject->getElement(RAD_ECHOTIME_DICOMGROUP, RAD_ECHOTIME_DICOMELEMENT, 
									   RadDataObjectBase::STRING, dimension, sizeof(tmp), tmp) ;

				swscanf(tmp, L"%f", &mDescriptor.echoTime);
			}
		}

		//MR Scanning Sequence if available
		if( dataObject->getElementProperty( RAD_MRIMAGE_SCANNING_SEQUENCE_DICOMGROUP, 
											RAD_MRIMAGE_SCANNING_SEQUENCE_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {			
			dimension = dataObject->getElementProperty( RAD_MRIMAGE_SCANNING_SEQUENCE_DICOMGROUP,
														RAD_MRIMAGE_SCANNING_SEQUENCE_DICOMELEMENT, 
														RAD_DATA_PROP_DIMENSION ) ;
			if(dimension)
			{
				dataObject->getElement(RAD_MRIMAGE_SCANNING_SEQUENCE_DICOMGROUP, RAD_MRIMAGE_SCANNING_SEQUENCE_DICOMELEMENT,
										  RadDataObjectBase::STRING, dimension, sizeof(tmp), tmp) ;
				mDescriptor.scanningSequence = _wcsdup(tmp);
				if (!mDescriptor.scanningSequence)
				{
					throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
				}
			}
		}

		//get MR sequenceVariant if available
		if( dataObject->getElementProperty( RAD_MRIMAGE_SEQUENCE_VARIANT_DICOMGROUP, 
											RAD_MRIMAGE_SEQUENCE_VARIANT_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {			
			dimension = dataObject->getElementProperty( RAD_MRIMAGE_SEQUENCE_VARIANT_DICOMGROUP,
														RAD_MRIMAGE_SEQUENCE_VARIANT_DICOMELEMENT, 
														RAD_DATA_PROP_DIMENSION ) ;
			if(dimension)
			{
				dataObject->getElement(RAD_MRIMAGE_SEQUENCE_VARIANT_DICOMGROUP, RAD_MRIMAGE_SEQUENCE_VARIANT_DICOMELEMENT,
										  RadDataObjectBase::STRING, dimension, sizeof(tmp), tmp) ;

				mDescriptor.sequenceVariant = _wcsdup(tmp);
				if (!mDescriptor.sequenceVariant)
				{
					throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
				}
			}
		}

		//get pixelRepresentation if available
		if( dataObject->getElementProperty( RAD_IMAGE_PIXELREPRESENTATION_DICOMGROUP, 
											RAD_IMAGE_PIXELREPRESENTATION_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {
			dataObject->getElement(RAD_IMAGE_PIXELREPRESENTATION_DICOMGROUP, RAD_IMAGE_PIXELREPRESENTATION_DICOMELEMENT,
								   RadDataObjectBase::UINT16, 1, sizeof(unsigned short), &(mDescriptor.pixelRepresentation));
		}

		//get rescale intercept and slope
		if( dataObject->getElementProperty( RAD_IMAGE_RESCALE_INTERCEPT_DICOMGROUP, 
											RAD_IMAGE_RESCALE_INTERCEPT_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {
			dimension = dataObject->getElementProperty( RAD_IMAGE_RESCALE_INTERCEPT_DICOMGROUP,
				                                        RAD_IMAGE_RESCALE_INTERCEPT_DICOMELEMENT, 
														RAD_DATA_PROP_DIMENSION ) ;
			if(dimension)
			{
				dataObject->getElement(RAD_IMAGE_RESCALE_INTERCEPT_DICOMGROUP, RAD_IMAGE_RESCALE_INTERCEPT_DICOMELEMENT, 
									   RadDataObjectBase::STRING, dimension, sizeof(tmp), tmp) ;

				swscanf(tmp, L"%f", &mDescriptor.rescaleIntercept);
			}
		}

		if( dataObject->getElementProperty( RAD_IMAGE_RESCALE_SLOPE_DICOMGROUP, 
											RAD_IMAGE_RESCALE_SLOPE_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {
			dimension = dataObject->getElementProperty( RAD_IMAGE_RESCALE_SLOPE_DICOMGROUP,
				                                        RAD_IMAGE_RESCALE_SLOPE_DICOMELEMENT, 
														RAD_DATA_PROP_DIMENSION ) ;
			if(dimension)
			{
				dataObject->getElement(RAD_IMAGE_RESCALE_SLOPE_DICOMGROUP, RAD_IMAGE_RESCALE_SLOPE_DICOMELEMENT, 
									   RadDataObjectBase::STRING, dimension, sizeof(tmp), tmp) ;

				swscanf(tmp, L"%f", &mDescriptor.rescaleSlope);
			}
		}

		if (!dataObject->getElement(RAD_IMAGE_BITSALLOCATED_DICOMGROUP, RAD_IMAGE_BITSALLOCATED_DICOMELEMENT,
								   RadDataObjectBase::UINT16, 1, sizeof(unsigned short), &mDescriptor.bitsAllocated))
		{
			throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"unable to get element");		
		}

		if (!dataObject->getElement(RAD_IMAGE_BITSSTORED_DICOMGROUP, RAD_IMAGE_BITSSTORED_DICOMELEMENT,
								  RadDataObjectBase::UINT16, 1, sizeof(unsigned short), &mDescriptor.bitsStored))
		{
			throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"unable to get element");		
		}

		if (!dataObject->getElement(RAD_IMAGE_HIGHBITS_DICOMGROUP, RAD_IMAGE_HIGHBITS_DICOMELEMENT,
								  RadDataObjectBase::UINT16, 1, sizeof(unsigned short), &mDescriptor.highBit))
		{
			throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"unable to get element");		
		}

		if (!dataObject->getElement(RAD_IMAGE_ROWS_DICOMGROUP, RAD_IMAGE_ROWS_DICOMELEMENT,
								   RadDataObjectBase::UINT16, 1, sizeof(unsigned short), &(mDescriptor.rows) ) )
		{
			throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"unable to get element");		
		}

		if (!dataObject->getElement(RAD_IMAGE_COLUMNS_DICOMGROUP, RAD_IMAGE_COLUMNS_DICOMELEMENT,
								   RadDataObjectBase::UINT16, 1, sizeof(unsigned short), &(mDescriptor.columns) ) )
		{
			throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"unable to get element");		
		}

		//get Image Orientation if available
		if( dataObject->getElementProperty( RAD_IMAGE_ORIENTATIONPATIENT_DICOMGROUP, 
											RAD_IMAGE_ORIENTATIONPATIENT_DICOMELEMENT,
			                                RAD_DATA_PROP_EXISTS  )  ) 
        {		
			if (!dataObject->getElement(RAD_IMAGE_ORIENTATIONPATIENT_DICOMGROUP, RAD_IMAGE_ORIENTATIONPATIENT_DICOMELEMENT,
									   RadDataObjectBase::FLT64, 6, 6 * sizeof(double), mDescriptor.imageOrientation))
			{	
				throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"image orientation unknown");
			}

			//compute the positionZ based on orientation and position vectors
			mDescriptor.objectPositionZ = this->computePositionZ(mDescriptor.imageOrientation, mDescriptor.imagePosition);
		}

		//pixelspacing
		if (!dataObject->getElement(RAD_IMAGE_PIXELSPACING_DICOMGROUP, RAD_IMAGE_PIXELSPACING_DICOMELEMENT,
								   RadDataObjectBase::FLT64, 2, sizeof(double)*2, &(mDescriptor.pixelSpacing) ) )
		{
			//TBD:- Not set for RF images
			throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"pixel data not set");
		}


		//check if pixel data can be mapped
		if( dataObject->getElementProperty( RAD_IMAGE_PIXEL_DATA_DICOMGROUP, 
											RAD_IMAGE_PIXEL_DATA_DICOMELEMENT,
			                                RAD_DATA_PROP_SUPPORTS_FILE_MAPPING  )  ) 
        {	
			//mapping of pixel data is supported
			try
			{
				//get pixel data filename	
				if (!dataObject->getElementEx(RAD_DATA_EX_PIXEL_PATH, RadDataObjectBase::STRING, 1, sizeof(tmp), tmp))
				{	
					throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"pixel path unknown");
				}

				mDescriptor.pixelDataFile = _wcsdup(tmp);
				if (!mDescriptor.pixelDataFile)
				{
					throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR, L"XipDicomSortImage::initialize");
				}			

				//get pixel data offset
				if (!dataObject->getElementEx(RAD_DATA_EX_PIXEL_OFFSET, RadDataObjectBase::UINT64, 1, sizeof(unsigned __int64), &(mDescriptor.pixelDataOffset)))
				{	
					throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"offset unknown");
				}
			}
			catch(...)
			{
				// no pixel mapping possible
				if (mDescriptor.pixelDataFile)
				{
					free(mDescriptor.pixelDataFile);
					mDescriptor.pixelDataFile = 0;
				}
				mDescriptor.pixelDataOffset = 0;
			}
		}

		//get pixel data sharename (optional)	
		if (dataObject->getElementEx(RAD_DATA_EX_PIXEL_SHARENAME, RadDataObjectBase::STRING, 1, sizeof(tmp), tmp) > 0)
		{
			if (tmp[0])
			{
				mDescriptor.pixelDataSharename = _wcsdup(tmp);
			}
		}

		dataObject->close();
	}
	catch(RadException &e)
	{
		RAD_LOG("radsortgeneric: Error reading object \"%S\" (%d%s).\n", objectName,
			e.type, e.type == RadException::INVALID_PARAM_ERROR ? " / missing element" : "");

		this->reset();
		dataObject->close();

		throw;
	}
	catch(...)
	{
		RAD_LOG("radsortgeneric: Error reading object \"%S\" (reason unknown).\n", objectName);

		this->reset();
		dataObject->close();

		throw;
	}
}
*/
