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
#ifndef  SOXIPDATA_H
#define  SOXIPDATA_H

#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/SbPList.h>
#include <xip/inventor/core/SoXipSubData.h>
#include <xip/inventor/core/xipivcore.h>

class SbXipDataPropertyMap;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXipData
//
//  Base SoXipData class (abstract).
//
//////////////////////////////////////////////////////////////////////////////

class XIPIVCORE_API SoXipData : public SoFieldContainer
{
	XIP_DATA_HEADER(SoXipData);

public:
	SoXipData();

	static void initClass();

    // Initiates notification from an instance.
    virtual void startNotify();

	uint32_t getDataId() const;
	static uint32_t getNextDataId();

	virtual void addRef( SoBase* refData );
	virtual SoBase* getRef(int index) const;
	virtual SoBase* getRefByType(SoType type) const;
	virtual int getNumRef() const;

	virtual void setProperty(const SbString &key, const SbString &value);
	virtual SbString getProperty(const SbString key) const;
	virtual void copyProperties(SoXipData *from);

	// debugging
	static void enableInstanceTracing(SbBool enable);
	static uint32_t getNumInstances();

protected:
	~SoXipData();

	SbPList mExtSources;
	SbXipDataPropertyMap *mProperties;
	uint32_t uniqueId;
	static uint32_t nextUniqueId;
	static uint32_t instanceCount;
	static SbBool instanceTracingEnabled;
};

#endif /* SOXIPDATA_H */
