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

#pragma warning (disable:4786)

#include <Inventor/errors/SoErrors.h>
#include <xip/inventor/core/SoXipData.h>
#include <map>

struct SbStringLessFunctor : public std::binary_function< SbString, SbString, bool >
{
	bool operator()( const SbString& s1, const SbString& s2 ) const
	{
		return strcmp( s1.getString(), s2.getString() ) < 0;
	}
};

// let's avoid declaring anything using STL in the header due to export/import issues
// we simply allocate the property list dynamically
class SbXipDataPropertyMap : public std::map<SbString, SbString, SbStringLessFunctor>
{
};


XIP_DATA_SOURCE(SoXipData)

uint32_t SoXipData::nextUniqueId = 0;
uint32_t SoXipData::instanceCount = 0;
SbBool   SoXipData::instanceTracingEnabled = FALSE;


void SoXipData::initClass()
{
	XIP_DATA_INIT_CLASS(SoXipData, SoFieldContainer, "FieldContainer");
}


uint32_t SoXipData::getDataId() const
{
	return uniqueId;
}


uint32_t SoXipData::getNextDataId()
{
	return nextUniqueId;
}


void SoXipData::enableInstanceTracing(SbBool enable)
{
	instanceTracingEnabled = enable;
}


uint32_t SoXipData::getNumInstances()
{
	return instanceCount;
}


SoXipData::SoXipData()
{
	mProperties = 0;

    uniqueId = ++nextUniqueId;

	instanceCount++;
	if (instanceTracingEnabled)
	{
		SoDebugError::postInfo("SoXipData::SoXipData", "Total of %d SoXipData objects allocated (this=0x%p).", instanceCount, this);
	}
}


SoXipData::~SoXipData()
{
	if (mProperties)
	{
		delete mProperties;
		mProperties = 0;
	}

	int i;
	for (i = 0; i < mExtSources.getLength(); i++)
	{
		((SoBase*) mExtSources.get(i))->unref();
	}

	instanceCount--;
	if (instanceTracingEnabled)
	{
		SoDebugError::postInfo("SoXipData::~SoXipData", "Total of %d SoXipData objects allocated (this=0x%p).", instanceCount, this);
	}
}


void SoXipData::startNotify()
{
    // Update our unique id to indicate that we are a different node.
    uniqueId = nextUniqueId++;

    // Let base class pass notification on to auditors...
    SoFieldContainer::startNotify();
}


void SoXipData::addRef( SoBase* refData )
{
	if (refData)
	{
		// Reference the data object
		refData->ref();

		// Push it in the list of referenced sources
		mExtSources.append( refData );
	}
}


SoBase* SoXipData::getRef(int index) const
{
	return (SoBase*) mExtSources.get(index);
}


int SoXipData::getNumRef() const
{
	return mExtSources.getLength();
}


SoBase* SoXipData::getRefByType(SoType type) const
{
	for (int i = 0; i < getNumRef(); i++)
	{
		if (getRef(i)->isOfType(type))
			return getRef(i);
	}

	return 0;
}


void SoXipData::setProperty(const SbString &key, const SbString &value)
{
	if (key.getLength() == 0)
	{
		SoDebugError::postWarning("SoXipData::setProperty", "Key is empty! The value cannot be stored.");
		return;
	}

	if (!mProperties)
	{
		mProperties = new SbXipDataPropertyMap;
		if (!mProperties)
		{
			SoMemoryError::post("SbXipDataPropertyMap");
			return;
		}
	}

	(*mProperties)[key] = value;
}


SbString SoXipData::getProperty(const SbString key) const
{
	if (mProperties)
	{
		SbXipDataPropertyMap::const_iterator it;
		it = mProperties->find(key);
		if (it != mProperties->end())
			return it->second;
	}

	return SbString("");
}


void SoXipData::copyProperties(SoXipData *from)
{
	if (from && from->mProperties)
	{
		SbXipDataPropertyMap::const_iterator it;

		for (it = from->mProperties->begin(); it != from->mProperties->end(); it++)
		{
			setProperty(it->first, it->second);
		}
	}
}



