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

#include <Inventor/SoLists.h>
#include <Inventor/misc/SoBase.h>
#include <Inventor/errors/SoErrors.h>
#include <xip/inventor/core/SoXipSFData.h>
#include <xip/inventor/core/SoXipData.h>
#include <xip/inventor/core/SbXipDirtyFieldList.h>


SoXipSFData::SoXipSFData()
{
	value = NULL;
}


SoXipSFData::~SoXipSFData()
{
	if( value != NULL )
	{
		value->removeAuditor( this, SoNotRec::FIELD );
		value->unref();
	}

	SbXipDirtyFieldList::remove(this);
}


const SoXipData* SoXipSFData::getDataValue() const
{
	evaluate();
	return value;
}


void SoXipSFData::setDataValue( SoXipData* newValue )
{
	setVal(newValue);
	valueChanged();
}


SbBool SoXipSFData::isSame(const SoField &f) const
{
    return (getTypeId() == f.getTypeId() &&
	    (*this) == (const SoXipSFData &) f);
}


int SoXipSFData::operator ==( const SoXipSFData& other ) const
{
	return isSame(other);
}


int SoXipSFData::operator !=( const SoXipSFData& other ) const
{
	return !isSame(other);
}


SbBool SoXipSFData::readValue(SoInput *in)
{
	SbName name;
	if( in->read( name ) )
	{
		if( name == "NULL" || name == "DATA" || name == "\"NULL\"" || name == "\"DATA\"" )
		{
			setVal( NULL );
			SbXipDirtyFieldList::append(this);
			return TRUE;
		}
		else
			in->putBack( name.getString() );
	}

	SoBase* base;
	if( !SoBase::read( in, base, SoXipData::getClassTypeId() ) )
	{
		setVal( NULL );
		return FALSE;
	}

	setVal( NULL );
	SbXipDirtyFieldList::append(this);
	return TRUE;
}


void SoXipSFData::writeValue(SoOutput *out) const
{
	if( value != NULL )
		out->write( "\"DATA\"" );
	else
		out->write( "\"NULL\"" );
}


void SoXipSFData::setVal( SoXipData* newValue )
{
	if( newValue != NULL )
		newValue->ref();

	if( value != NULL )
	{
		value->removeAuditor( this, SoNotRec::FIELD );
		value->unref();
	}

	value = newValue;

	if( value != NULL )
	{
		value->ref();
		value->addAuditor( this, SoNotRec::FIELD );
	}

	if( newValue != NULL )
		newValue->unref();
}


void SoXipSFData::countWriteRefs( SoOutput* out ) const
{
	SoField::countWriteRefs( out );
	if( value != NULL )
		value->addWriteReference( out );
}
