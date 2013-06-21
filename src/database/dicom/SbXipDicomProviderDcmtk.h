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

#ifndef SBXIPDICOMPROVIDERDCMTK_H
#define SBXIPDICOMPROVIDERDCMTK_H

#include <xip/inventor/dicom/SoXipDataDicom.h>


class SbXipDicomProviderDcmtk : public SbXipDicomProviderBase
{
public:
	static void initClass();

	virtual void* open();
	virtual void* open(const char *fileName, const char *options);
	virtual void close(void *handle);
	virtual SbBool save(void *fileHandle, const char *fileName, const char *options);
	virtual void *getDataset(void *fileHandle) const;
	virtual void *getMetaInfo(void *fileHandle) const;
	virtual SbBool getPixelData(void *fileHandle, SbXipImage &image, int sliceIndex, const char *options, void* pixelDataItem);
	virtual int getNumSlices(void *fileHandle, const char *options, void* pixelDataItem);
	virtual void* createCompatible(void *metaInfoHandle, void *datasetHandle);

	virtual SbBool  isOfType(void *item, const char *type) const;
	virtual SbBool  tagExists(void *item, const SbXipDicomTagKey &key, SbBool searchIntoSub = FALSE);
	virtual SbBool  tagExistsWithValue(void *item, const SbXipDicomTagKey &key, SbBool searchIntoSub = FALSE);
	virtual SbBool  findAndGet(const void *item, const SbXipDicomTagKey &key, SbString &value, SbBool searchIntoSub = FALSE);

	virtual void    remove(void *item, const SbXipDicomTagKey &key);
	virtual SbPList search(void *item, const SbXipDicomTagKey &key, int searchMode = 0, SbBool searchIntoSub = TRUE);

	virtual SbBool interpret(const SoMFString &in, SoMFString &out);

protected:
	// Destructor
	virtual ~SbXipDicomProviderDcmtk();
};


#endif // SBXIPDICOMPROVIDERDCMTK_H
