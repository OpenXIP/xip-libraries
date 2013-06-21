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
#ifndef SOXIPMFDATA_H
#define SOXIPMFDATA_H

#include <Inventor/fields/SoSubField.h>
#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SoXipData.h>


// base class for multiple value fields containing non-serializable pointers
class XIPIVCORE_API SoXipMFData : public SoMField
{
public:
	SbBool isReadOnly() const { return FALSE; };

    const SoXipData** getDataValues(int start) const;
	void setDataValues(int start, int num, const SoXipData** newValues);
	void setDataValue( SoXipData* newValue );
	void set1DataValue( int index, SoXipData* newValue );

	int operator ==( const SoXipMFData& other ) const;
	int operator !=( const SoXipMFData& other ) const;

protected:
	virtual ~SoXipMFData();

	// inventor internal
	int find( SoXipData* targetValue, SbBool addIfNotFound );
	virtual void allocValues( int newNum );
	virtual void deleteAllValues();
	virtual void copyValue( int to, int from );
	virtual SbBool read1Value( SoInput* in, int index );
	virtual void write1Value( SoOutput* out, int index ) const;
	virtual void countWriteRefs( SoOutput* out ) const;
	void set1Value_( int index, const SoXipData* constNewValue );

    SoXipData **values;
};


#if !defined(COIN_DLL) && !defined(COIN_NO_DLL)

// SGI Inventor:

// Unfortunately with SGI Inventor we cannot use SO_MFDATA_VALUE_HEADER()
// and SO_MFDATA_VALUE_SOURCE() due to the use of const attributes in
// some headers. Therefore we need to provide our own implementation (we
// implement only the necessary ones).
#define XIP_MFDATA_VALUE_HEADER(classname, type, notUsed)					\
	public:																	\
	type operator [](int i) const;											\
	const type *getValues(int start) const;									\
	void setValues(int start, int num, const type *newValues);				\
	void set1Value(int index, type newValue);								\
	void setValue(type newValue);											\
	type operator =(type newValue);											\
	type *startEditing();													\
	void finishEditing();


#define XIP_MFDATA_VALUE_SOURCE(classname, type, notUsed)					\
	type classname::operator [](int i) const								\
	{ evaluate(); return (type) values[i]; }								\
																			\
    const type * classname::getValues(int start) const						\
	{ return (const type *) getDataValues(start); }							\
																			\
	void classname::setValues(int start, int num, const type* newValues)	\
	{ setDataValues(start, num, (const SoXipData**) newValues); }			\
																			\
	void classname::set1Value( int index, type newValue )					\
	{ set1DataValue(index, newValue); }										\
																			\
	void classname::setValue( type newValue )								\
	{ setDataValue(newValue); }												\
																			\
	type *classname::startEditing()											\
	{ evaluate(); return (type *) values; }									\
																			\
	void classname::finishEditing()											\
	{ valueChanged(); }



#define XIP_MFDATA_HEADER(classname, type)									\
	SO_MFIELD_REQUIRED_HEADER( classname );									\
	SO_MFIELD_CONSTRUCTOR_HEADER( classname );								\
	XIP_MFDATA_VALUE_HEADER( classname, type*, type* );						\
																			\
	public:																	\
	static void initClass();

#define XIP_MFDATA_SOURCE(classname, type)									\
	SO_MFIELD_REQUIRED_SOURCE( classname )									\
	SO_MFIELD_CONSTRUCTOR_SOURCE( classname )								\
	XIP_MFDATA_VALUE_SOURCE( classname , type*, type* )						\
																			\
	void classname::initClass()												\
	{ SO_SFIELD_INIT_CLASS( classname, SoMField ); }


#else 

// COIN:

#define XIP_MFDATA_HEADER(classname, type)									\
    SO_SFIELD_REQUIRED_HEADER( classname );									\
    SO_SFIELD_CONSTRUCTOR_HEADER( classname );								\
	SO_MFIELD_VALUE_HEADER(classname, type*, type*);						\
																			\
	public:																	\
	static void initClass();

#define XIP_MFDATA_SOURCE(classname, type)									\
	SO_MFIELD_REQUIRED_SOURCE(classname);									\
	SO_MFIELD_CONSTRUCTOR_SOURCE(classname);								\
	SO_MFIELD_VALUE_SOURCE(classname, type*, type*);						\
	SO_MFIELD_MALLOC_SOURCE(classname, type*);								\
																			\
	SbBool classname::read1Value(SoInput * in, int idx)						\
	{ return SoXipMFData::read1Value(in, idx); };							\
																			\
	void classname::write1Value(SoOutput * out, int idx) const				\
	{ SoXipMFData::write1Value(out, idx); };								\
																			\
	void classname::initClass()												\
	{ SO_SFIELD_INIT_CLASS( classname, SoMField ); }

#endif


#endif	// SOXIPMFDATA_H


