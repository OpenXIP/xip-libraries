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

/* author Sylvain Jaume, Julien Gein */

#include <itkMatrixOffsetTransformBase.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include <xip/inventor/itk/SoItkSFDataTransform.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include "SoItkMatrixOffsetTransformBase.h"

SO_ENGINE_SOURCE( SoItkMatrixOffsetTransformBase )

SoItkMatrixOffsetTransformBase::SoItkMatrixOffsetTransformBase()
{
	SO_ENGINE_CONSTRUCTOR( SoItkMatrixOffsetTransformBase );

	SO_ENGINE_ADD_INPUT( Center, (0) );
	Center.setNum(0);
	SO_ENGINE_ADD_INPUT( Translation, (0) );
	Translation.setNum(0);
	SO_ENGINE_ADD_INPUT( UseMatrix, (FALSE) );
	SO_ENGINE_ADD_INPUT( Matrix, (1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
	SO_ENGINE_ADD_INPUT( Offset, (0) );
	Offset.setNum(0);
}

SoItkMatrixOffsetTransformBase::~SoItkMatrixOffsetTransformBase()
{

}

void
SoItkMatrixOffsetTransformBase::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkMatrixOffsetTransformBase, 
		SoItkTransform, "SoItkTransform" );
}

void
SoItkMatrixOffsetTransformBase::evaluate()
{
	if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( Output, SoItkSFDataTransform, setValue( 0 ) );
    }
    
    try
    {
		typedef itk::MatrixOffsetTransformBase< double, 2, 2 > TransformType;
		TransformType::Pointer transform = TransformType::New();

		if( Parameters.getNum() )
		{
			SO_ITK_SET_FIELD_ARRAY( transform, Parameters, double );
		}
		else
		{
			if( UseMatrix.getValue() )
			{
				SO_ITK_SET_FIELD_MATRIX( transform, Matrix, double, 2, 2 );
				SO_ITK_SET_FIELD_VECTOR( transform, Offset, double, 2 );
			}
			else
			{
				SO_ITK_SET_FIELD_POINT( transform, Center, double, 2 );
				SO_ITK_SET_FIELD_VECTOR( transform, Translation, double, 2 );
			}
		}

		transform->Register();

		mOutput = new SoItkDataTransform();
		mOutput->ref();
		mOutput->setPointer( transform );
		
		unsigned short numberOfParameters = transform->GetNumberOfParameters();
		SO_ENGINE_OUTPUT( NumberOfParameters, SoSFFloat, setValue( numberOfParameters ) );

		float* parameters = new float[ numberOfParameters ];
		for( unsigned int i = 0; i < numberOfParameters; ++ i )
			transform->GetParameters().GetElement( i );
		SO_ENGINE_OUTPUT( OutputParameters, SoMFFloat, setValues( 0, numberOfParameters, parameters ) );
		delete [] parameters;
    }
    catch(...)
    {
        SoDebugError::post( __FILE__, "Unknown Exception" );
        return ;
    }
    
	SO_ENGINE_OUTPUT( Output, SoItkSFDataTransform, setValue( mOutput ) );
}