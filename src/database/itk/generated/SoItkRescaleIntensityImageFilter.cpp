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
#include <itkRescaleIntensityImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkRescaleIntensityImageFilter.h"

SO_ENGINE_SOURCE( SoItkRescaleIntensityImageFilter );

SoItkRescaleIntensityImageFilter::SoItkRescaleIntensityImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkRescaleIntensityImageFilter );
	
	// Enumerations
	SO_ENGINE_DEFINE_ENUM_VALUE( OutputPixelTypeEnum, FLOAT );
	SO_ENGINE_DEFINE_ENUM_VALUE( OutputPixelTypeEnum, UNSIGNED_SHORT );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( OutputMaximum, (65535) );
	SO_ENGINE_ADD_INPUT( OutputMinimum, (0) );
	SO_ENGINE_SET_SF_ENUM_TYPE( OutputPixelType, OutputPixelTypeEnum );
	SO_ENGINE_ADD_INPUT( OutputPixelType, (FLOAT) );
}

SoItkRescaleIntensityImageFilter::~SoItkRescaleIntensityImageFilter()
{

}

void
SoItkRescaleIntensityImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkRescaleIntensityImageFilter, SoItkUnaryFunctorImageFilter, "SoItkUnaryFunctorImageFilter" );
}

bool
SoItkRescaleIntensityImageFilter::checkInput()
{
	switch( OutputPixelType.getValue() )
	{
		case FLOAT:
		{
			switch( Input0.getValue()->getType() )
			{
				case SoItkDataImage::FLOAT:
				{
					switch( Input0.getValue()->getNumDimension() )
					{
						case 2:
						{
							return true;
						}
						break ;
						case 3:
						{
							return true;
						}
						break ;
					}
				}
				break ;
				case SoItkDataImage::UNSIGNED_SHORT:
				{
					switch( Input0.getValue()->getNumDimension() )
					{
						case 2:
						{
							return true;
						}
						break ;
						case 3:
						{
							return true;
						}
						break ;
					}
				}
				break ;
			}
		}
		break ;
		case UNSIGNED_SHORT:
		{
			switch( Input0.getValue()->getType() )
			{
				case SoItkDataImage::FLOAT:
				{
					switch( Input0.getValue()->getNumDimension() )
					{
						case 2:
						{
							return true;
						}
						break ;
						case 3:
						{
							return true;
						}
						break ;
					}
				}
				break ;
				case SoItkDataImage::UNSIGNED_SHORT:
				{
					switch( Input0.getValue()->getNumDimension() )
					{
						case 2:
						{
							return true;
						}
						break ;
						case 3:
						{
							return true;
						}
						break ;
					}
				}
				break ;
			}
		}
		break ;
	}
	
	return false;
}

void
SoItkRescaleIntensityImageFilter::evaluate()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
		SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( 0 ) );
	}

	if( !Input0.getValue() )
		return ;
	
	if( !checkInput() )
	{
		SoDebugError::post( __FILE__, "Invalid Input Types" );
		return ;
	}

	try
	{
		switch( OutputPixelType.getValue() )
		{
			case FLOAT:
			{
				switch( Input0.getValue()->getType() )
				{
					case SoItkDataImage::FLOAT:
					{
						switch( Input0.getValue()->getNumDimension() )
						{
							case 2:
							{
								typedef itk::Image< float, 2 > InputImageType;
								typedef itk::Image< float, 2 > OutputImageType;
								typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > FilterType;
								
								FilterType::Pointer filter = FilterType::New();
								
								// Set the filter's inputs
								SO_ITK_SET_FIELD_VALUE( filter, OutputMaximum );
								SO_ITK_SET_FIELD_VALUE( filter, OutputMinimum );
								
								
								
								// Inherited from SoItkInPlaceImageFilter
								SO_ITK_SET_FIELD_VALUE( filter, InPlace );
								
								// Inherited from SoItkImageToImageFilter
								typedef itk::Image< float, 2 > InputImageType;
								SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
								
								
								
								// Start processing the ouputs
								filter->Update();
								
								// Retrieve the filter's outputs
								filter->GetOutput()->Register();
								mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 2,
									Input0.getValue()->getModelMatrix() );
								mOutput->ref();
								mOutput->setPointer( filter->GetOutput() );
							}
							break ;
							case 3:
							{
								typedef itk::Image< float, 3 > InputImageType;
								typedef itk::Image< float, 3 > OutputImageType;
								typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > FilterType;
								
								FilterType::Pointer filter = FilterType::New();
								
								// Set the filter's inputs
								SO_ITK_SET_FIELD_VALUE( filter, OutputMaximum );
								SO_ITK_SET_FIELD_VALUE( filter, OutputMinimum );
								
								
								
								// Inherited from SoItkInPlaceImageFilter
								SO_ITK_SET_FIELD_VALUE( filter, InPlace );
								
								// Inherited from SoItkImageToImageFilter
								typedef itk::Image< float, 3 > InputImageType;
								SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
								
								
								
								// Start processing the ouputs
								filter->Update();
								
								// Retrieve the filter's outputs
								filter->GetOutput()->Register();
								mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 3,
									Input0.getValue()->getModelMatrix() );
								mOutput->ref();
								mOutput->setPointer( filter->GetOutput() );
							}
							break ;
						}
					}
					break ;
					case SoItkDataImage::UNSIGNED_SHORT:
					{
						switch( Input0.getValue()->getNumDimension() )
						{
							case 2:
							{
								typedef itk::Image< unsigned short, 2 > InputImageType;
								typedef itk::Image< float, 2 > OutputImageType;
								typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > FilterType;
								
								FilterType::Pointer filter = FilterType::New();
								
								// Set the filter's inputs
								SO_ITK_SET_FIELD_VALUE( filter, OutputMaximum );
								SO_ITK_SET_FIELD_VALUE( filter, OutputMinimum );
								
								
								
								// Inherited from SoItkInPlaceImageFilter
								SO_ITK_SET_FIELD_VALUE( filter, InPlace );
								
								// Inherited from SoItkImageToImageFilter
								typedef itk::Image< unsigned short, 2 > InputImageType;
								SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
								
								
								
								// Start processing the ouputs
								filter->Update();
								
								// Retrieve the filter's outputs
								filter->GetOutput()->Register();
								mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 2,
									Input0.getValue()->getModelMatrix() );
								mOutput->ref();
								mOutput->setPointer( filter->GetOutput() );
							}
							break ;
							case 3:
							{
								typedef itk::Image< unsigned short, 3 > InputImageType;
								typedef itk::Image< float, 3 > OutputImageType;
								typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > FilterType;
								
								FilterType::Pointer filter = FilterType::New();
								
								// Set the filter's inputs
								SO_ITK_SET_FIELD_VALUE( filter, OutputMaximum );
								SO_ITK_SET_FIELD_VALUE( filter, OutputMinimum );
								
								
								
								// Inherited from SoItkInPlaceImageFilter
								SO_ITK_SET_FIELD_VALUE( filter, InPlace );
								
								// Inherited from SoItkImageToImageFilter
								typedef itk::Image< unsigned short, 3 > InputImageType;
								SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
								
								
								
								// Start processing the ouputs
								filter->Update();
								
								// Retrieve the filter's outputs
								filter->GetOutput()->Register();
								mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 3,
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
			break ;
			case UNSIGNED_SHORT:
			{
				switch( Input0.getValue()->getType() )
				{
					case SoItkDataImage::FLOAT:
					{
						switch( Input0.getValue()->getNumDimension() )
						{
							case 2:
							{
								typedef itk::Image< float, 2 > InputImageType;
								typedef itk::Image< unsigned short, 2 > OutputImageType;
								typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > FilterType;
								
								FilterType::Pointer filter = FilterType::New();
								
								// Set the filter's inputs
								SO_ITK_SET_FIELD_VALUE( filter, OutputMaximum );
								SO_ITK_SET_FIELD_VALUE( filter, OutputMinimum );
								
								
								
								// Inherited from SoItkInPlaceImageFilter
								SO_ITK_SET_FIELD_VALUE( filter, InPlace );
								
								// Inherited from SoItkImageToImageFilter
								typedef itk::Image< float, 2 > InputImageType;
								SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
								
								
								
								// Start processing the ouputs
								filter->Update();
								
								// Retrieve the filter's outputs
								filter->GetOutput()->Register();
								mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 2,
									Input0.getValue()->getModelMatrix() );
								mOutput->ref();
								mOutput->setPointer( filter->GetOutput() );
							}
							break ;
							case 3:
							{
								typedef itk::Image< float, 3 > InputImageType;
								typedef itk::Image< unsigned short, 3 > OutputImageType;
								typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > FilterType;
								
								FilterType::Pointer filter = FilterType::New();
								
								// Set the filter's inputs
								SO_ITK_SET_FIELD_VALUE( filter, OutputMaximum );
								SO_ITK_SET_FIELD_VALUE( filter, OutputMinimum );
								
								
								
								// Inherited from SoItkInPlaceImageFilter
								SO_ITK_SET_FIELD_VALUE( filter, InPlace );
								
								// Inherited from SoItkImageToImageFilter
								typedef itk::Image< float, 3 > InputImageType;
								SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
								
								
								
								// Start processing the ouputs
								filter->Update();
								
								// Retrieve the filter's outputs
								filter->GetOutput()->Register();
								mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 3,
									Input0.getValue()->getModelMatrix() );
								mOutput->ref();
								mOutput->setPointer( filter->GetOutput() );
							}
							break ;
						}
					}
					break ;
					case SoItkDataImage::UNSIGNED_SHORT:
					{
						switch( Input0.getValue()->getNumDimension() )
						{
							case 2:
							{
								typedef itk::Image< unsigned short, 2 > InputImageType;
								typedef itk::Image< unsigned short, 2 > OutputImageType;
								typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > FilterType;
								
								FilterType::Pointer filter = FilterType::New();
								
								// Set the filter's inputs
								SO_ITK_SET_FIELD_VALUE( filter, OutputMaximum );
								SO_ITK_SET_FIELD_VALUE( filter, OutputMinimum );
								
								
								
								// Inherited from SoItkInPlaceImageFilter
								SO_ITK_SET_FIELD_VALUE( filter, InPlace );
								
								// Inherited from SoItkImageToImageFilter
								typedef itk::Image< unsigned short, 2 > InputImageType;
								SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
								
								
								
								// Start processing the ouputs
								filter->Update();
								
								// Retrieve the filter's outputs
								filter->GetOutput()->Register();
								mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 2,
									Input0.getValue()->getModelMatrix() );
								mOutput->ref();
								mOutput->setPointer( filter->GetOutput() );
							}
							break ;
							case 3:
							{
								typedef itk::Image< unsigned short, 3 > InputImageType;
								typedef itk::Image< unsigned short, 3 > OutputImageType;
								typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > FilterType;
								
								FilterType::Pointer filter = FilterType::New();
								
								// Set the filter's inputs
								SO_ITK_SET_FIELD_VALUE( filter, OutputMaximum );
								SO_ITK_SET_FIELD_VALUE( filter, OutputMinimum );
								
								
								
								// Inherited from SoItkInPlaceImageFilter
								SO_ITK_SET_FIELD_VALUE( filter, InPlace );
								
								// Inherited from SoItkImageToImageFilter
								typedef itk::Image< unsigned short, 3 > InputImageType;
								SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
								
								
								
								// Start processing the ouputs
								filter->Update();
								
								// Retrieve the filter's outputs
								filter->GetOutput()->Register();
								mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 3,
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
