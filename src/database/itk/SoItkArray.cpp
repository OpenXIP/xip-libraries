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
#include <itkArray.h>
#include <xip/inventor/itk/SoItkSFDataArray.h>
#include "SoItkArray.h"

SO_ENGINE_SOURCE( SoItkArray )

SoItkArray::SoItkArray()
{
	SO_ENGINE_CONSTRUCTOR( SoItkArray );

	// Enumerations
	SO_ENGINE_DEFINE_ENUM_VALUE( ValueTypeEnum, UNSIGNED_SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( ValueTypeEnum, FLOAT );
	SO_ENGINE_DEFINE_ENUM_VALUE( ValueTypeEnum, DOUBLE );

	// Define input fields and their default values
	SO_ENGINE_SET_SF_ENUM_TYPE( ValueType, ValueTypeEnum );
	SO_ENGINE_ADD_INPUT( ValueType, (FLOAT) );
	SO_ENGINE_ADD_INPUT( Rows, (0) );
	SO_ENGINE_ADD_INPUT( Columns, (0) );
	SO_ENGINE_ADD_INPUT( Values, (0) );

	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataArray );
	mOutput = 0;
}

SoItkArray::~SoItkArray()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
    }	
}

void
SoItkArray::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkArray, SoEngine, "Engine" );	
}

void
SoItkArray::inputChanged( SoField* field )
{
	if( field == &Rows ||
		field == &Columns )
	{
		unsigned int oldSize = Values.getNum();
		unsigned int newSize = Rows.getValue() * Columns.getValue();
		Values.setNum( newSize );
		for( unsigned int i = oldSize; i < newSize; ++ i )
			Values.set1Value( i, 0 );
	}
}

void
SoItkArray::evaluate()
{
	if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( Output, SoItkSFDataArray, setValue( 0 ) );
    }
    
    try
    {
		unsigned short n_rows = Rows.getValue();
		unsigned short n_columns = Columns.getValue();

		if( Values.getNum() != (n_rows * n_columns) )
		{
			SoDebugError::post( __FILE__, 
				"The number of element of the array does not match the given dimensions" );
			return ;
		}

		switch( ValueType.getValue() )
		{
		case UNSIGNED_SHORT:
			{
				typedef itk::Array< unsigned short > ArrayType;

				ArrayType* array = new ArrayType( 
					(unsigned short *) Values.getValues(0), Values.getNum(), false );

				mOutput = new SoItkDataArray( SoItkDataArray::UNSIGNED_SHORT, Values.getNum() );
				mOutput->ref();
				mOutput->setPointer( array );
			}
			break ;

		case FLOAT:
			{
				typedef itk::Array< float > ArrayType;

				ArrayType* array = new ArrayType( 
					(float *) Values.getValues(0), Values.getNum(), false );

				mOutput = new SoItkDataArray( SoItkDataArray::FLOAT, Values.getNum() );
				mOutput->ref();
				mOutput->setPointer( array );
			}
			break ;

		case DOUBLE:
			{
				typedef itk::Array< double > ArrayType;

				ArrayType* array = new ArrayType( 
					(double *) Values.getValues(0), Values.getNum(), false );

				mOutput = new SoItkDataArray( SoItkDataArray::DOUBLE, Values.getNum() );
				mOutput->ref();
				mOutput->setPointer( array );
			}
			break ;
		}
    }
    catch(...)
    {
        SoDebugError::post( __FILE__, "Unknown Exception" );
        return ;
    }
    
	SO_ENGINE_OUTPUT( Output, SoItkSFDataArray, setValue( mOutput ) );
}
