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

#include <Inventor/sensors/SoDelayQueueSensor.h>
#include <xip/inventor/core/SoXipMFData.h>
#include <xip/inventor/core/SbXipDirtyFieldList.h>


SoXipMFData::~SoXipMFData()
{
	SbXipDirtyFieldList::remove(this);
}


const SoXipData** SoXipMFData::getDataValues(int start) const
{
	evaluate();
	return (const SoXipData**) (values + start);
}


void SoXipMFData::setDataValues(int start, int num, const SoXipData** newValues)
{
	int	newNum = start + num;

	if( newNum > getNum() )
		makeRoom( newNum );

	for( int i = 0; i < num; ++ i )
		set1Value_( start + i, newValues[i] );

	valueChanged();
}


void SoXipMFData::set1DataValue( int index, SoXipData* newValue )
{
	if( index >= getNum() )
		makeRoom( index + 1 );
	set1Value_( index, newValue );
	valueChanged();
}


void SoXipMFData::setDataValue( SoXipData* newValue )
{
	makeRoom(1);
	set1Value_( 0, newValue );
	valueChanged();
}


void SoXipMFData::set1Value_( int index, const SoXipData* constNewValue )
{
	SoXipData* newValue = const_cast< SoXipData* >( constNewValue );
	if( newValue == values[ index ] )
		return ;

	if( newValue != NULL )
		newValue->ref();

	if( values[ index ] != NULL )
	{
		values[ index ]->removeAuditor( this, SoNotRec::FIELD );
		values[ index ]->unref();
	}

	values[ index ] = newValue;

	if( values[ index ] != NULL )
	{
		values[ index ]->ref();
		values[ index ]->addAuditor( this, SoNotRec::FIELD );
	}

	if( newValue != NULL )
		newValue->unref();
}


int SoXipMFData::find( SoXipData* targetValue, SbBool addIfNotFound )
{
	int	num = getNum();

	for( int i = 0; i < num; ++ i )
	if( values[i] == targetValue )
		return i;

	if( addIfNotFound )
		set1DataValue( num, targetValue );

	return -1;
}


int SoXipMFData::operator ==( const SoXipMFData& other ) const
{
	int num = getNum();
	if( num != other.getNum() )
		return false;

	const SoXipData** lhs = getDataValues(0);
	const SoXipData** rhs = other.getDataValues(0);

	for( int i = 0; i < num; ++ i )
	{
		if( lhs[i] != rhs[i] )
			return false;
	}

	return true;
}


int SoXipMFData::operator !=( const SoXipMFData& other ) const
{
	return !(*this == other);
}


void SoXipMFData::allocValues( int newNum )
{
	if( values == NULL )
	{
		if( newNum > 0 )
		{
			values = new SoXipData*[ newNum ];
			memset( values, 0, newNum * sizeof( SoXipData* ) );
		}
	}
	else
	{
		int pNum = getNum();
		SoXipData** pValues = values;

		if( newNum > 0 )
		{
			values = new SoXipData*[ newNum ];

			for( int i = 0; i < newNum; ++ i )
			{
				values[i] = ( i < pNum ) ? pValues[i] : NULL;
			}
		}
		else
		{
			values = NULL;
		}

		for( int i = newNum; i < pNum; i ++ )
		{
			if( pValues[i] != NULL )
			{
				pValues[i]->removeAuditor( this, SoNotRec::FIELD );
				pValues[i]->unref();
			}
		}

		delete [] pValues;
	}

	num = maxNum = newNum;
}


void SoXipMFData::deleteAllValues()
{
	allocValues(0);
}


void SoXipMFData::copyValue( int to, int from )
{
	set1Value_( to, values[ from ] );
}


SbBool SoXipMFData::read1Value( SoInput* in, int index )
{
	SbName name;
	if( in->read( name ) )
	{
		if( name == "NULL" || name == "DATA" || name == "\"NULL\"" || name == "\"DATA\"" )
		{
			set1DataValue( index, NULL );
			SbXipDirtyFieldList::append(this);
			return TRUE;
		}
		else in->putBack( name.getString() );
	}

	SoBase* base;
	if(! SoBase::read( in, base, SoXipData::getClassTypeId() ) )
	{
		set1DataValue( index, NULL );
		return FALSE;
	}

	set1DataValue( index, NULL );
	SbXipDirtyFieldList::append(this);
	return TRUE;
}


void SoXipMFData::write1Value( SoOutput* out, int index ) const
{
	if( values[ index ] != NULL )
		out->write( "\"DATA\"" );
	else
		out->write( "\"NULL\"" );
}


void SoXipMFData::countWriteRefs( SoOutput* out ) const
{
	SoField::countWriteRefs( out );

	int num = getNum();
	for( int i = 0; i < num; ++ i )
	{
		if( values[i] != NULL )
			values[i]->addWriteReference( out );
	}
}

