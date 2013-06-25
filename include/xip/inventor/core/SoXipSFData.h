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
#ifndef SOXIPSFDATA_H
#define SOXIPSFDATA_H

#include <Inventor/fields/SoSubField.h>
#include <xip/inventor/core/xipivcore.h>

class SoXipData;


class XIPIVCORE_API SoXipSFData : public SoSField
{
public:
	SoXipSFData();
	virtual ~SoXipSFData();
    virtual const SoXipData* getDataValue() const;
	virtual void setDataValue( SoXipData* newValue );

	virtual SbBool isSame(const SoField &f) const;
	virtual int operator ==( const SoXipSFData& other ) const;
	virtual int operator !=( const SoXipSFData& other ) const;
	virtual SbBool isReadOnly() const { return FALSE; };

protected:
	virtual SbBool readValue(SoInput *in);
	virtual void   writeValue(SoOutput *out) const;

private:
	virtual void countWriteRefs( SoOutput* out ) const;
	void setVal( SoXipData* newValue );

protected:
	SoXipData *value;
};



#define XIP_SFDATA_HEADER(className, type)							\
	SO_SFIELD_REQUIRED_HEADER(className);							\
	public:															\
	type *	getValue() const { evaluate(); return (type *) value; }	\
	void setValue(type* newValue);									\
	static void initClass();


#define XIP_SFDATA_SOURCE(classname, type)							\
	SO_SFIELD_REQUIRED_SOURCE( classname );							\
																	\
	void classname::setValue( type* newValue )						\
	{																\
		setDataValue( (SoXipData *) newValue );						\
	}																\
																	\
	void classname::initClass()										\
	{																\
		SO_SFIELD_INIT_CLASS( classname, SoSField );				\
	}

#endif	// SOXIPSFDATA_H


