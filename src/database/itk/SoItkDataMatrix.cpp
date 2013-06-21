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
#include <xip/inventor/itk/SoItkDataMatrix.h>

XIP_DATA_SOURCE( SoItkDataMatrix );

SoItkDataMatrix::SoItkDataMatrix()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataMatrix );

	mItkMatrix = 0;
	mValueType = UNSIGNED_SHORT;
    mMatrixType = MATRIX_2X2;
}

SoItkDataMatrix::SoItkDataMatrix( ValueType valueType, MatrixType matrixType )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataMatrix );

	mItkMatrix = 0;
	mValueType = valueType;
    mMatrixType = matrixType;
}

SoItkDataMatrix::SoItkDataMatrix( const SoItkDataMatrix& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataMatrix );

	mItkMatrix = other.mItkMatrix;
	mValueType = other.mValueType;
	mMatrixType = other.mMatrixType;
}

SoItkDataMatrix::~SoItkDataMatrix()
{
	if( mItkMatrix )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
		switch( mValueType )
		{
		case UNSIGNED_SHORT:
			{
                switch( mMatrixType )
                {
                    case MATRIX_2X2:
                    {
                        typedef itk::Matrix< unsigned short, 2, 2 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                    
                    case MATRIX_3X3:
                    {
                        typedef itk::Matrix< unsigned short, 3, 3 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                    
                    case MATRIX_4X4:
                    {
                        typedef itk::Matrix< unsigned short, 4, 4 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                }
			}
			break ;

		case FLOAT:
			{
                switch( mMatrixType )
                {
                    case MATRIX_2X2:
                    {
                        typedef itk::Matrix< float, 2, 2 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                    
                    case MATRIX_3X3:
                    {
                        typedef itk::Matrix< float, 3, 3 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                    
                    case MATRIX_4X4:
                    {
                        typedef itk::Matrix< float, 4, 4 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                }
			}
			break ;

		case DOUBLE:
			{
                switch( mMatrixType )
                {
                    case MATRIX_2X2:
                    {
                        typedef itk::Matrix< double, 2, 2 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                    
                    case MATRIX_3X3:
                    {
                        typedef itk::Matrix< double, 3, 3 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                    
                    case MATRIX_4X4:
                    {
                        typedef itk::Matrix< double, 4, 4 > ArrayType;
                        ArrayType* array = static_cast< ArrayType* >( mItkMatrix );
                        delete array;                        
                    }
                    break ;
                }
			}
			break ;
		}
		mItkMatrix = 0;
	}
}

void 
SoItkDataMatrix::initClass()
{	
	XIP_DATA_INIT_CLASS( SoItkDataMatrix, SoXipData, "SoXipData" );	
}

void 
SoItkDataMatrix::setPointer( void* itkArray )
{
	mItkMatrix = itkArray;
}

void*
SoItkDataMatrix::getPointer() const
{
	return mItkMatrix;
}

SoItkDataMatrix::ValueType
SoItkDataMatrix::getValueType() const
{
	return mValueType;
}

SoItkDataMatrix::MatrixType
SoItkDataMatrix::getMatrixType() const
{
	return mMatrixType;
}

unsigned int
SoItkDataMatrix::getRows() const
{
    switch( mMatrixType )
    {
        case MATRIX_2X2: return 2;
        case MATRIX_3X3: return 3;
        case MATRIX_4X4: return 4;
    }
	return -1;
}

unsigned int
SoItkDataMatrix::getCols() const
{
    switch( mMatrixType )
    {
        case MATRIX_2X2: return 2;
        case MATRIX_3X3: return 3;
        case MATRIX_4X4: return 4;
    }
	return -1;
}
