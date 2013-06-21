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
#ifndef XIPDICOMSORTUTIL_H
#define XIPDICOMSORTUTIL_H

#include "XipDicomSortImage.h"

class XipDicomSortImageList;
class XipDicomSortVolumeList;


/**	\class XipDicomSortUtil
 *	\brief Dicom sorting utility class.
 *
 *	Utility class to sort dicom images into logical groups that form volumes.
 *
 */
class XipDicomSortUtil
{
public:
	typedef enum
	{
		ACQUISITION_TIME	= 1,
		TRIGGER_TIME		= 2,
		IMAGE_NUMBER		= 4,
		SCAN_OPTIONS		= 8,
		SERIES_NUMBER		= 16,
		SORT_OPTIONS_ALL	= 31
	} sortOption_t;

	/// Default constructor.
	XipDicomSortUtil();

	/// Destructor.
	virtual ~XipDicomSortUtil();

	/// Adds an image to be sorted.
	virtual int addImage(const XipDicomSortImageAttributes *attributes);

	/// Clears the list of images.
	virtual void clear();

	/// Starts the object sorting operation.	
	virtual void sort(unsigned int option = 0);

	/// Gets the number of logical groupings.
	virtual unsigned int getNumVolumes() const;

	/// Returns how many objects belong to a group.
	virtual unsigned int getNumSlicesInVolume(unsigned int volumeIndex) const;
	
	/// Returns a constant pointer to the internal structure describing an object.
	virtual const XipDicomSortImageAttributes * getImageAttributes(unsigned int volumeIndex, unsigned int sliceIndex) const;


protected:
	int getNumDuplicateImagePositions(const XipDicomSortImageList &imageList, unsigned int &sortOption);
	bool canSortByTriggerTime(const XipDicomSortImageList &imageList) const;
	bool canSortBySeriesNumber(const XipDicomSortImageList &imageList) const;
	bool canSortByImageNumber(const XipDicomSortImageList &imageList) const;
	bool canSortByScanOptions(const XipDicomSortImageList &imageList) const;
	bool canSortByAcquisitionTime(const XipDicomSortImageList &imageList) const;

protected:
	/// List of all images.
	XipDicomSortImageList *mSortImageList;

	/// List of volumes.
	XipDicomSortVolumeList *mSortVolumeList;
};



#endif    // XIPDICOMSORTUTIL_H
