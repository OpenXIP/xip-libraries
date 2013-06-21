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
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <dcmtk/dcmdata/dctk.h>
#include <Inventor/SbPList.h>
#include <Inventor/fields/SoMFString.h>


SbXipDicomProviderBase *SoXipDataDicom::mProvider = 0;


XIP_DATA_SOURCE(SoXipDataDicom);


void SoXipDataDicom::initClass()
{
	XIP_DATA_INIT_CLASS(SoXipDataDicom, SoXipData, "SoXipData");
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoXipDataDicom::SoXipDataDicom()
{
	XIP_DATA_CONSTRUCTOR(SoXipDataDicom);

	mFile = 0;
}


SoXipDataDicom::~SoXipDataDicom()
{
	close();
}


SbXipDicomItemHandle SoXipDataDicom::getDataset() const
{
	SbXipDicomItemHandle handle;

	if (mProvider && mFile)
	{
		handle = SbXipDicomItemHandle(mProvider->getDataset(mFile), mProvider);
	}

	return handle;
}


SbXipDicomItemHandle SoXipDataDicom::getMetaInfo() const
{
	SbXipDicomItemHandle handle;

	if (mProvider && mFile)
	{
		handle = SbXipDicomItemHandle(mProvider->getMetaInfo(mFile), mProvider);
	}

	return handle;
}


SbBool SoXipDataDicom::getPixelData(SbXipImage &image, int sliceIndex, const char *options, SbXipDicomItemHandle pixelDataItem) const
{
	if (mProvider && mFile)
	{
		return mProvider->getPixelData(mFile, image, sliceIndex, options, (pixelDataItem.getProvider() == mProvider) ? pixelDataItem.getItem() : 0);
	}

	return FALSE;
}


int SoXipDataDicom::getNumSlices(const char *options, SbXipDicomItemHandle pixelDataItem) const
{
	if (mProvider && mFile)
	{
		return mProvider->getNumSlices(mFile, options, (pixelDataItem.getProvider() == mProvider) ? pixelDataItem.getItem() : 0);
	}

	return 0;
}

SbBool SoXipDataDicom::createCompatible(const SoXipDataDicom *dataDicomObj)
{
	if (!dataDicomObj)
		return FALSE;

	close();

	if (mProvider)
	{
		mFile = mProvider->createCompatible(&dataDicomObj->getMetaInfo(), &dataDicomObj->getDataset());
	}

	return (mFile ? TRUE : FALSE);
}

SbBool SoXipDataDicom::open()
{
	close();

	if (mProvider)
	{
		mFile = mProvider->open();
	}

	return (mFile ? TRUE : FALSE);
}

SbBool SoXipDataDicom::open(const char *fileName, const char *options)
{
	close();

	if (mProvider)
	{
		mFile = mProvider->open(fileName, options);
	}

	return (mFile ? TRUE : FALSE);
}


void SoXipDataDicom::close()
{
	if (mProvider && mFile)
	{
		mProvider->close(mFile);
		mFile = 0;
	}
}

SbBool SoXipDataDicom::save(const char *fileName, const char *options)
{
	if (mProvider && mFile)
	{
		return mProvider->save(mFile, fileName, options);
	}

	return FALSE;
}


SbBool SoXipDataDicom::interpret(const SoMFString &in, SoMFString &out)
{
	if (mProvider)
	{
		return mProvider->interpret(in, out);
	}

	return FALSE;
}


void SoXipDataDicom::setProvider(SbXipDicomProviderBase *provider)
{
	mProvider = provider;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


SbXipDicomItem::SbXipDicomItem(const SbXipDicomItemHandle &itemHandle)
{
	mItemHandle = itemHandle;
}


SbXipDicomItemList SbXipDicomItem::search(const SbXipDicomTagKey &key, int searchMode, SbBool searchIntoSub)
{
	SbXipDicomItemList results(mItemHandle.getProvider());

	if (!mItemHandle.isNull())
	{
		results = mItemHandle.getProvider()->search(mItemHandle.getItem(), key, searchMode, searchIntoSub);
	}

	return results;
}


void SbXipDicomItem::remove(const SbXipDicomTagKey &key)
{
	if (!mItemHandle.isNull())
	{
		mItemHandle.getProvider()->remove(mItemHandle.getItem(), key);
	}
}


SbBool SbXipDicomItem::isOfType(const char *type) const
{
	if (!mItemHandle.isNull())
	{
		return mItemHandle.getProvider()->isOfType(mItemHandle.getItem(), type);
	}

	return FALSE;
}


SbBool SbXipDicomItem::tagExists(const SbXipDicomTagKey &key, SbBool searchIntoSub)
{
	if (!mItemHandle.isNull())
	{
		return mItemHandle.getProvider()->tagExists(mItemHandle.getItem(), key, searchIntoSub);
	}

	return FALSE;
}


SbBool SbXipDicomItem::tagExistsWithValue(const SbXipDicomTagKey &key, SbBool searchIntoSub)
{
	if (!mItemHandle.isNull())
	{
		return mItemHandle.getProvider()->tagExistsWithValue(mItemHandle.getItem(), key, searchIntoSub);
	}

	return FALSE;
}


SbBool SbXipDicomItem::findAndGet(const SbXipDicomTagKey &key, SbString &value, SbBool searchIntoSub)
{
	if (!mItemHandle.isNull())
	{
		return mItemHandle.getProvider()->findAndGet(mItemHandle.getItem(), key, value, searchIntoSub);
	}

	return FALSE;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int SbXipDicomProviderBase::parseInt(const char *str, const char *option, int defaultValue)
{
	if (str && option)
	{
		char tmp[100];
		sprintf(tmp, "%s=", option);

		const char *f = strstr(str, tmp);
		if (f)
		{
			return atoi(f + strlen(option) + 1);
		}
	}

	return defaultValue;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



SbXipDicomItemList::SbXipDicomItemList(SbXipDicomProviderBase *provider)
{
	mProvider = provider;
}


SbXipDicomItemHandle SbXipDicomItemList::operator [](int i) const
{ 
	return SbXipDicomItemHandle(get(i), mProvider);
}


SbXipDicomItemList& SbXipDicomItemList::operator=(const SbXipDicomItemList& other)
{
	mProvider = other.mProvider;
	copy(other);

	return (*this);
}


SbXipDicomItemList& SbXipDicomItemList::operator=(const SbPList& other)
{
	// leave provider as is, just copy items
	copy(other);

	return (*this);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



SbXipDicomTagKey::SbXipDicomTagKey(unsigned int group, unsigned int element)
{
	mGroup = group;
	mElement = element;
}


unsigned int SbXipDicomTagKey::getGroup() const
{
	return mGroup;
}


unsigned int SbXipDicomTagKey::getElement() const
{
	return mElement;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



SbXipDicomItemHandle::SbXipDicomItemHandle(void *item, SbXipDicomProviderBase *provider)
{
	mItem = item;
	mProvider = provider;
}


SbXipDicomItemHandle::SbXipDicomItemHandle(const SbXipDicomItemHandle& other)
{
	*this = other;
}


SbXipDicomItemHandle& SbXipDicomItemHandle::operator=(const SbXipDicomItemHandle& other)
{
	mItem = other.mItem;
	mProvider = other.mProvider;

	return (*this);
}


void* SbXipDicomItemHandle::getItem(const char *type) const
{
	if (type && !isOfType(type))
		return 0;

	return mItem;
}


SbXipDicomProviderBase* SbXipDicomItemHandle::getProvider() const
{
	return mProvider;
}


SbBool SbXipDicomItemHandle::isNull() const
{
	return !(mItem && mProvider);
}


SbBool SbXipDicomItemHandle::isOfType(const char *type) const
{
	if (mProvider && mItem)
	{
		return mProvider->isOfType(mItem, type);
	}

	return FALSE;
}

