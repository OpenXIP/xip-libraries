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
#include <itkOrImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkOrImageFilter.h"

SO_ENGINE_SOURCE( SoItkOrImageFilter );

SoItkOrImageFilter::SoItkOrImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkOrImageFilter );
}

SoItkOrImageFilter::~SoItkOrImageFilter()
{

}

void
SoItkOrImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkOrImageFilter, SoItkBinaryFunctorImageFilter, "SoItkBinaryFunctorImageFilter" );
}

bool
SoItkOrImageFilter::checkInput()
{
	switch( Input1.getValue()->getNumDimension() )
	{
		case 2:
		{
			switch( Input1.getValue()->getType() )
			{
				case SoItkDataImage::BOOL:
				{
					return true;
				}
				break ;
			}
		}
		break ;
		case 3:
		{
			switch( Input1.getValue()->getType() )
			{
				case SoItkDataImage::BOOL:
				{
					return true;
				}
				break ;
			}
		}
		break ;
	}
	
	return false;
}

void
SoItkOrImageFilter::evaluate()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
		SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( 0 ) );
	}

	if( !Input0.getValue() )
		return ;
	
	if( !Input1.getValue() )
		return ;
	
	if( !checkInput() )
	{
		SoDebugError::post( __FILE__, "Invalid Input Types" );
		return ;
	}

	try
	{
		switch( Input1.getValue()->getNumDimension() )
		{
			case 2:
			{
				switch( Input1.getValue()->getType() )
				{
					case SoItkDataImage::BOOL:
					{
						typedef itk::Image< bool, 2 > BooleanImageType;
						typedef itk::Image< bool, 2 > BooleanImageType;
						typedef itk::Image< bool, 2 > OutputImageType;
						typedef itk::OrImageFilter< BooleanImageType, BooleanImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkBinaryFunctorImageFilter
						typedef itk::Image< bool, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 1, InputImageType );
						
						// Inherited from SoItkInPlaceImageFilter
						SO_ITK_SET_FIELD_VALUE( filter, InPlace );
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< bool, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::BOOL, 2,
							Input0.getValue()->getModelMatrix() );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
				}
			}
			break ;
			case 3:
			{
				switch( Input1.getValue()->getType() )
				{
					case SoItkDataImage::BOOL:
					{
						typedef itk::Image< bool, 3 > BooleanImageType;
						typedef itk::Image< bool, 3 > BooleanImageType;
						typedef itk::Image< bool, 3 > OutputImageType;
						typedef itk::OrImageFilter< BooleanImageType, BooleanImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkBinaryFunctorImageFilter
						typedef itk::Image< bool, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 1, InputImageType );
						
						// Inherited from SoItkInPlaceImageFilter
						SO_ITK_SET_FIELD_VALUE( filter, InPlace );
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< bool, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::BOOL, 3,
							Input0.getValue()->getModelMatrix() );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
				}
			}
			break ;
		}
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), "line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}

	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( mOutput ) );
}
