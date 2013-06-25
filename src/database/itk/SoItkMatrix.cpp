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
#include <itkMatrix.h>
#include <xip/inventor/itk/SoItkSFDataMatrix.h>
#include "SoItkMatrix.h"

SO_ENGINE_SOURCE( SoItkMatrix )

SoItkMatrix::SoItkMatrix()
{
	SO_ENGINE_CONSTRUCTOR( SoItkMatrix );

	// Enumerations
	SO_ENGINE_DEFINE_ENUM_VALUE( ValueTypeEnum, UNSIGNED_SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( ValueTypeEnum, FLOAT );
	SO_ENGINE_DEFINE_ENUM_VALUE( ValueTypeEnum, DOUBLE );
    
    SO_ENGINE_DEFINE_ENUM_VALUE( MatrixTypeEnum, _2x2 );
	SO_ENGINE_DEFINE_ENUM_VALUE( MatrixTypeEnum, _3x3 );
	SO_ENGINE_DEFINE_ENUM_VALUE( MatrixTypeEnum, _4x4 );

	// Define input fields and their default values
	SO_ENGINE_SET_SF_ENUM_TYPE( ValueType, ValueTypeEnum );
	SO_ENGINE_ADD_INPUT( ValueType, (FLOAT) );
	SO_ENGINE_SET_SF_ENUM_TYPE( MatrixType, MatrixTypeEnum );
	SO_ENGINE_ADD_INPUT( MatrixType, (_2x2) );
	SO_ENGINE_ADD_INPUT( Values, (0) );

	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataMatrix );
	mOutput = 0;
}

SoItkMatrix::~SoItkMatrix()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
    }	
}

void
SoItkMatrix::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkMatrix, SoEngine, "Engine" );	
}

void
SoItkMatrix::inputChanged( SoField* field )
{
	if( field == &MatrixType )
	{
		unsigned int oldSize = Values.getNum();
        unsigned int newSize = 0;
        
        switch( MatrixType.getValue() )
        {
            case _2x2: newSize =  4; break ;
            case _3x3: newSize =  9; break ;
            case _4x4: newSize = 16; break ;
        }

        Values.setNum( newSize );
        for( unsigned int i = oldSize; i < newSize; ++ i )
            Values.set1Value( i, 0 );
    }
}

void
SoItkMatrix::evaluate()
{
	if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( Output, SoItkSFDataMatrix, setValue( 0 ) );
    }
    
    try
    {
        // FIXME : check size
        
		switch( ValueType.getValue() )
		{
		    case UNSIGNED_SHORT:
			{
                switch( MatrixType.getValue() )
                {
                    case _2x2: 
                    {
                        typedef itk::Matrix< unsigned short, 2, 2 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 2; ++ i )
                        for( unsigned int j = 0; j < 2; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*2 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_2X2 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
                    
                    case _3x3: 
                    {
                        typedef itk::Matrix< unsigned short, 3, 3 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 3; ++ i )
                        for( unsigned int j = 0; j < 3; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*3 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_3X3 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
                    
                    case _4x4: 
                    {
                        typedef itk::Matrix< unsigned short, 4, 4 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 4; ++ i )
                        for( unsigned int j = 0; j < 4; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*4 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_4X4 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
				}
            }
			break ;

            case FLOAT:
			{
                switch( MatrixType.getValue() )
                {
                    case _2x2: 
                    {
                        typedef itk::Matrix< float, 2, 2 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 2; ++ i )
                        for( unsigned int j = 0; j < 2; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*2 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_2X2 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
                    
                    case _3x3: 
                    {
                        typedef itk::Matrix< float, 3, 3 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 3; ++ i )
                        for( unsigned int j = 0; j < 3; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*3 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_3X3 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
                    
                    case _4x4: 
                    {
                        typedef itk::Matrix< float, 4, 4 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 4; ++ i )
                        for( unsigned int j = 0; j < 4; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*4 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_4X4 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
				}
            }
			break ;

		    case DOUBLE:
			{
                switch( MatrixType.getValue() )
                {
                    case _2x2: 
                    {
                        typedef itk::Matrix< double, 2, 2 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 2; ++ i )
                        for( unsigned int j = 0; j < 2; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*2 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_2X2 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
                    
                    case _3x3: 
                    {
                        typedef itk::Matrix< double, 3, 3 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 3; ++ i )
                        for( unsigned int j = 0; j < 3; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*3 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_3X3 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
                    
                    case _4x4: 
                    {
                        typedef itk::Matrix< double, 4, 4 > MatrixType;
                        
                        MatrixType* array = new MatrixType();
                        
                        for( unsigned int i = 0; i < 4; ++ i )
                        for( unsigned int j = 0; j < 4; ++ j )
                        {
                            array->operator() ( i, j ) = Values[ i*4 + j ];
                        }
            
                        mOutput = new SoItkDataMatrix( 
							SoItkDataMatrix::UNSIGNED_SHORT, SoItkDataMatrix::MATRIX_4X4 );
                        mOutput->ref();
                        mOutput->setPointer( array );
                    }
                    break ;
				}
            }
			break ; 
		}
    }
    catch(...)
    {
        SoDebugError::post( __FILE__, "Unknown Exception" );
        return ;
    }
    
	SO_ENGINE_OUTPUT( Output, SoItkSFDataMatrix, setValue( mOutput ) );
}
