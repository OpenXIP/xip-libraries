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
#ifndef SOXIPDATADICOM_H
#define SOXIPDATADICOM_H

#include <xip/inventor/core/SoXipData.h>
#include <xip/inventor/core/SoXipSubData.h>
#include <xip/inventor/dicom/xipivdicom.h>


class SbXipDicomProviderBase;
class SbXipDicomItem;
class SbXipImage;
class SoMFString;



// helper class representing a dicom tag key (DcmTagKey)
class XIPIVDICOM_API SbXipDicomTagKey
{
public:
	SbXipDicomTagKey(unsigned int group = 0, unsigned int element = 0);
	unsigned int getGroup() const;
	unsigned int getElement() const;

protected:
	unsigned int mGroup;
	unsigned int mElement;
};


// abstract interface for data providers
class XIPIVDICOM_API SbXipDicomProviderBase
{
public:
	// object
	virtual void* open() = 0;
	virtual void* open(const char *fileName, const char *options) = 0;
	virtual void close(void *fileHandle) = 0;
	virtual SbBool save(void *fileHandle, const char *fileName, const char *options) = 0;
	virtual void *getDataset(void *fileHandle) const = 0;
	virtual void *getMetaInfo(void *fileHandle) const = 0;
	virtual SbBool getPixelData(void *fileHandle, SbXipImage &image, int sliceIndex, const char *options, void* pixelDataItem) = 0;
	virtual int getNumSlices(void *fileHandle, const char *options, void* pixelDataItem) = 0;
	virtual void* createCompatible(void *metaInfoHandle, void *datasetHandle) = 0;

	// item
	virtual SbBool  isOfType(void *item, const char *type) const = 0;
	virtual SbBool  tagExists(void *item, const SbXipDicomTagKey &key, SbBool searchIntoSub = FALSE) = 0;
	virtual SbBool  tagExistsWithValue(void *item, const SbXipDicomTagKey &key, SbBool searchIntoSub = FALSE) = 0;
	virtual SbBool  findAndGet(const void *item, const SbXipDicomTagKey &key, SbString &value, SbBool searchIntoSub = FALSE) = 0;

	virtual void    remove(void *item, const SbXipDicomTagKey &key) = 0;
	virtual SbPList search(void *item, const SbXipDicomTagKey &key, int searchMode = 0, SbBool searchIntoSub = TRUE) = 0;

	virtual SbBool interpret(const SoMFString &in, SoMFString &out) = 0;

protected:
	virtual int parseInt(const char *str, const char *option, int defaultValue);
};


// helper class representing a handle to a dicom item
class XIPIVDICOM_API SbXipDicomItemHandle
{
public:
	SbXipDicomItemHandle(void *item = 0, SbXipDicomProviderBase *provider = 0);
	SbXipDicomItemHandle(const SbXipDicomItemHandle& other);
	SbXipDicomItemHandle& operator=(const SbXipDicomItemHandle& other);
	void* getItem(const char *type = 0) const;
	SbXipDicomProviderBase* getProvider() const;
	SbBool isNull() const;
	SbBool isOfType(const char *type) const;

protected:
	void *mItem;
	SbXipDicomProviderBase *mProvider;
};


// list for storing handles
// this class only stores only one instance of a provider object,
// the [] operator constructs SbXipDicomItemHandle on the fly
class XIPIVDICOM_API SbXipDicomItemList : public SbPList 
{
public:
	SbXipDicomItemList(SbXipDicomProviderBase *provider);

	SbXipDicomItemHandle operator [](int i) const;
	SbXipDicomItemList& operator=(const SbXipDicomItemList& other);
	SbXipDicomItemList& operator=(const SbPList& other);

protected:
	SbXipDicomProviderBase *mProvider;
};


// helper class representing a dicom item (DcmItem)
// It is used as simple API wrapper around DcmItem to avoid having to link
// against DCMTK wherever a DICOM element needs to be queried.
class XIPIVDICOM_API SbXipDicomItem
{
public:
	SbXipDicomItem(const SbXipDicomItemHandle &itemHandle);

	SbBool isOfType(const char *type) const;
	SbBool tagExists(const SbXipDicomTagKey &key, SbBool searchIntoSub = FALSE);
	SbBool tagExistsWithValue(const SbXipDicomTagKey &key, SbBool searchIntoSub = FALSE);
	SbBool findAndGet(const SbXipDicomTagKey &key, SbString &value, SbBool searchIntoSub = FALSE);

	void remove(const SbXipDicomTagKey &key);
	SbXipDicomItemList search(const SbXipDicomTagKey &key, int searchMode = 0, SbBool searchIntoSub = TRUE);

protected:
	SbXipDicomItemHandle mItemHandle;
};



// dicom wrapper data class
class XIPIVDICOM_API SoXipDataDicom : public SoXipData
{
	XIP_DATA_HEADER(SoXipDataDicom);

public:
	SoXipDataDicom();
	static void initClass();

	//DcmFileFormat*	getFileFormat() const;
	SbXipDicomItemHandle getDataset() const;
	SbXipDicomItemHandle getMetaInfo() const;
	SbBool getPixelData(SbXipImage &image, int sliceIndex = -1, const char *options = 0, SbXipDicomItemHandle pixelDataItem = SbXipDicomItemHandle()) const;
	int getNumSlices(const char *options = 0, SbXipDicomItemHandle pixelDataItem = SbXipDicomItemHandle()) const;
	SbBool createCompatible(const SoXipDataDicom *dataDicomObj);

	SbBool open();
	SbBool open(const char *fileName, const char *options = 0);
	SbBool save(const char *fileName, const char *options = 0);
	void close();

	static SbBool interpret(const SoMFString &in, SoMFString &out);

	static void setProvider(SbXipDicomProviderBase *provider);

protected:
	virtual ~SoXipDataDicom();

	void *mFile;
	static SbXipDicomProviderBase *mProvider;
};


#endif // SOXIPDATADICOM_H
