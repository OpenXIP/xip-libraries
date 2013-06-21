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
#include <itkBilateralImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkBilateralImageFilter.h"

SO_ENGINE_SOURCE( SoItkBilateralImageFilter );

SoItkBilateralImageFilter::SoItkBilateralImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkBilateralImageFilter );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( DomainSigma, (4.0) );
	SO_ENGINE_ADD_INPUT( Radius, (1) );
	SO_ENGINE_ADD_INPUT( RangeSigma, (50.0) );
	SO_ENGINE_ADD_INPUT( FilterDimensionality, (2) );
	SO_ENGINE_ADD_INPUT( AutomaticKernelSize, (true) );
	SO_ENGINE_ADD_INPUT( NumberOfRangeGaussianSamples, (100) );
}

SoItkBilateralImageFilter::~SoItkBilateralImageFilter()
{

}

void
SoItkBilateralImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkBilateralImageFilter, SoItkImageToImageFilter, "SoItkImageToImageFilter" );
}

bool
SoItkBilateralImageFilter::checkInput()
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
	
	return false;
}

void
SoItkBilateralImageFilter::evaluate()
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
						typedef itk::BilateralImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, DomainSigma );
						SO_ITK_SET_FIELD_VALUE( filter, Radius );
						SO_ITK_SET_FIELD_VALUE( filter, RangeSigma );
						SO_ITK_SET_FIELD_VALUE( filter, FilterDimensionality );
						SO_ITK_SET_FIELD_VALUE( filter, AutomaticKernelSize );
						SO_ITK_SET_FIELD_VALUE( filter, NumberOfRangeGaussianSamples );
						
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
						typedef itk::BilateralImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, DomainSigma );
						SO_ITK_SET_FIELD_VALUE( filter, Radius );
						SO_ITK_SET_FIELD_VALUE( filter, RangeSigma );
						SO_ITK_SET_FIELD_VALUE( filter, FilterDimensionality );
						SO_ITK_SET_FIELD_VALUE( filter, AutomaticKernelSize );
						SO_ITK_SET_FIELD_VALUE( filter, NumberOfRangeGaussianSamples );
						
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
						typedef itk::Image< unsigned short, 2 > OutputImageType;
						typedef itk::BilateralImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, DomainSigma );
						SO_ITK_SET_FIELD_VALUE( filter, Radius );
						SO_ITK_SET_FIELD_VALUE( filter, RangeSigma );
						SO_ITK_SET_FIELD_VALUE( filter, FilterDimensionality );
						SO_ITK_SET_FIELD_VALUE( filter, AutomaticKernelSize );
						SO_ITK_SET_FIELD_VALUE( filter, NumberOfRangeGaussianSamples );
						
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
						typedef itk::BilateralImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, DomainSigma );
						SO_ITK_SET_FIELD_VALUE( filter, Radius );
						SO_ITK_SET_FIELD_VALUE( filter, RangeSigma );
						SO_ITK_SET_FIELD_VALUE( filter, FilterDimensionality );
						SO_ITK_SET_FIELD_VALUE( filter, AutomaticKernelSize );
						SO_ITK_SET_FIELD_VALUE( filter, NumberOfRangeGaussianSamples );
						
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
