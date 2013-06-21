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
#ifndef SO_ITK_DATA_MATRIX_H_
# define SO_ITK_DATA_MATRIX_H_

# include <xip/inventor/core/SoXipData.h>
# include <xip/inventor/core/SoXipSubData.h>
# include <xip/inventor/itk/xipivitk.h>

class XIPIVITK_API SoItkDataMatrix : public SoXipData
{
	XIP_DATA_HEADER( SoItkDataMatrix );

public:
	enum ValueType
	{
		UNSIGNED_SHORT,
		FLOAT,
		DOUBLE
	};
    
    enum MatrixType
    {
        MATRIX_2X2,
        MATRIX_3X3,
        MATRIX_4X4
    };

	SoItkDataMatrix();
	SoItkDataMatrix( ValueType valueType, MatrixType matrixType );
	SoItkDataMatrix( const SoItkDataMatrix& other );

	void setPointer( void* array );

	static void initClass();

public:
	void* getPointer() const;
	ValueType getValueType() const;
	MatrixType getMatrixType() const;
	unsigned int getRows() const;
	unsigned int getCols() const;

protected:
	~SoItkDataMatrix();

protected:
	void* mItkMatrix;
	ValueType mValueType;
	MatrixType mMatrixType;

};

#endif // SO_ITK_DATA_MATRIX_H_
