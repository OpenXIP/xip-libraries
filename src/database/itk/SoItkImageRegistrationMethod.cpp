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
#include <itkImageRegistrationMethod.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkImageRegistrationMethod.h"

SO_ENGINE_SOURCE( SoItkImageRegistrationMethod );

SoItkImageRegistrationMethod::SoItkImageRegistrationMethod()
{
	SO_ENGINE_CONSTRUCTOR( SoItkImageRegistrationMethod );

	SO_ENGINE_ADD_INPUT( InitialTransformParameters, (0) );
	InitialTransformParameters.setNum(0);
	SO_ENGINE_ADD_INPUT( Transform, (0) );
	SO_ENGINE_ADD_INPUT( FixedImage, (0) );
	SO_ENGINE_ADD_INPUT( MovingImage, (0) );
	SO_ENGINE_ADD_INPUT( Interpolator, (0) );
	SO_ENGINE_ADD_INPUT( Metric, (0) );
	SO_ENGINE_ADD_INPUT( FixedImageRegion, (0) );
	FixedImageRegion.setNum(0);
	SO_ENGINE_ADD_INPUT( Optimizer, (0) );

	SO_ENGINE_ADD_INPUT( Start, () );

	SO_ENGINE_ADD_OUTPUT( OutputOptimizer, SoItkSFDataOptimizer );
	SO_ENGINE_ADD_OUTPUT( LastTransformParameters, SoMFFloat );

	mStartRegistration = false;
	mOptimizer = 0;
}

SoItkImageRegistrationMethod::~SoItkImageRegistrationMethod()
{
	if( mOptimizer )
	{
		mOptimizer->unref();
		mOptimizer = 0;
	}
}

void
SoItkImageRegistrationMethod::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkImageRegistrationMethod, SoItkProcessObject, "SoItkProcessObject" );
}

bool
SoItkImageRegistrationMethod::checkInput()
{
	switch( FixedImage.getValue()->getType() )
	{
		case SoItkDataImage::FLOAT:
		{
			switch( FixedImage.getValue()->getNumDimension() )
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
			switch( MovingImage.getValue()->getNumDimension() )
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
SoItkImageRegistrationMethod::evaluate()
{
	if( !mStartRegistration )
		return ;

	if( mOptimizer )
	{
		mOptimizer->unref();
		mOptimizer = 0;
		SO_ENGINE_OUTPUT( OutputOptimizer, SoItkSFDataOptimizer, setValue( 0 ) );
	}

	SO_ENGINE_OUTPUT( LastTransformParameters, SoMFFloat, setNum( 0 ) );

	if( !checkInput() )
	{
		SoDebugError::post( __FILE__, "Invalid Input Types" );
		return ;
	}

	try
	{
		switch( FixedImage.getValue()->getType() )
		{
			case SoItkDataImage::FLOAT:
			{
				switch( MovingImage.getValue()->getNumDimension() )
				{
					case 2:
					{
						typedef itk::Image< float, 2 > InputImageType;
						typedef itk::Image< float, 2 > OutputImageType;
						typedef itk::Image< float, 2 > InputImageType;
						typedef itk::Image< float, 2 > OutputImageType;
						typedef itk::Array< double > ArrayType;
						typedef itk::ImageToImageMetric< InputImageType, OutputImageType > MetricType;
						typedef itk::SingleValuedNonLinearOptimizer OptimizerType;
						typedef double CoordinateRepresentationType;
						typedef itk::Transform< CoordinateRepresentationType, 2, 2 > TransformType;
						typedef itk::Image< float, 2 > InputImageType;
						typedef double CoordinateRepresentationType;
						typedef itk::InterpolateImageFunction< InputImageType, CoordinateRepresentationType > InterpolatorType;
						typedef itk::ImageRegistrationMethod< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						SO_ITK_SET_FIELD_ARRAY( filter, InitialTransformParameters, double );
						SO_ITK_SET_FIELD_DATA( filter, FixedImage, InputImageType );
						SO_ITK_SET_FIELD_DATA( filter, MovingImage, InputImageType );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, FixedImageRegion, 2 );
						SO_ITK_SET_FIELD_DATA( filter, Interpolator, InterpolatorType );
						SO_ITK_SET_FIELD_DATA( filter, Metric, MetricType );
						SO_ITK_SET_FIELD_DATA( filter, Transform, TransformType );
						SO_ITK_SET_FIELD_DATA( filter, Optimizer, OptimizerType );

						// Start processing the ouputs
						filter->StartRegistration();
						
						// Retrieve the filter's outputs
						ArrayType lastParameters = filter->GetLastTransformParameters();
						unsigned int numberOfParameters = lastParameters.size();						
						float* parameters = new float[ numberOfParameters ];
						for( unsigned int i = 0; i < numberOfParameters; ++ i )
							parameters[i] = lastParameters( i );

                        SO_ENGINE_OUTPUT( LastTransformParameters, SoMFFloat, setValues( 0, numberOfParameters, parameters ) );
						delete [] parameters;

						filter->GetOptimizer()->Register();

						mOptimizer = new SoItkDataOptimizer();
						mOptimizer->ref();
						mOptimizer->setPointer( filter->GetOptimizer() );

						SO_ENGINE_OUTPUT( OutputOptimizer, SoItkSFDataOptimizer, setValue( mOptimizer ) );

						SoDebugError::post( __FILE__, "Registration Done (FLOAT 2)" );
					}
					break ;
					case 3:
					{
						typedef itk::Image< float, 3 > InputImageType;
						typedef itk::Image< float, 3 > OutputImageType;
						typedef itk::Image< float, 3 > InputImageType;
						typedef itk::Image< float, 3 > OutputImageType;
						typedef itk::Array< double > ArrayType;
						typedef itk::ImageToImageMetric< InputImageType, OutputImageType > MetricType;
						typedef itk::SingleValuedNonLinearOptimizer OptimizerType;
						typedef double CoordinateRepresentationType;
						typedef itk::Transform< CoordinateRepresentationType, 3, 3 > TransformType;
						typedef itk::Image< float, 3 > InputImageType;
						typedef double CoordinateRepresentationType;
						typedef itk::InterpolateImageFunction< InputImageType, CoordinateRepresentationType > InterpolatorType;
						typedef itk::ImageRegistrationMethod< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						SO_ITK_SET_FIELD_ARRAY( filter, InitialTransformParameters, double );
						SO_ITK_SET_FIELD_DATA( filter, FixedImage, InputImageType );
						SO_ITK_SET_FIELD_DATA( filter, MovingImage, InputImageType );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, FixedImageRegion, 3 );
						SO_ITK_SET_FIELD_DATA( filter, Interpolator, InterpolatorType );
						SO_ITK_SET_FIELD_DATA( filter, Metric, MetricType );
						SO_ITK_SET_FIELD_DATA( filter, Transform, TransformType );
						SO_ITK_SET_FIELD_DATA( filter, Optimizer, OptimizerType );
						// Start processing the ouputs
						filter->StartRegistration();
						
						// Retrieve the filter's outputs
						ArrayType lastParameters = filter->GetLastTransformParameters();
						unsigned int numberOfParameters = lastParameters.size();						
						float* parameters = new float[ numberOfParameters ];
						for( unsigned int i = 0; i < numberOfParameters; ++ i )
							parameters[i] = lastParameters( i );

                        SO_ENGINE_OUTPUT( LastTransformParameters, SoMFFloat, setValues( 0, numberOfParameters, parameters ) );
						delete [] parameters;

						filter->GetOptimizer()->Register();

						mOptimizer = new SoItkDataOptimizer();
						mOptimizer->ref();
						mOptimizer->setPointer( filter->GetOptimizer() );

						SO_ENGINE_OUTPUT( OutputOptimizer, SoItkSFDataOptimizer, setValue( mOptimizer ) );

						SoDebugError::post( __FILE__, "Registration Done (FLOAT 3)" );
					}
					break ;
				}
			}
			break ;
			case SoItkDataImage::UNSIGNED_SHORT:
			{
				switch( MovingImage.getValue()->getNumDimension() )
				{
					case 2:
					{
						typedef itk::Image< unsigned short, 2 > InputImageType;
						typedef itk::Image< unsigned short, 2 > OutputImageType;
						typedef itk::Image< unsigned short, 2 > InputImageType;
						typedef itk::Image< unsigned short, 2 > OutputImageType;
						typedef itk::Array< double > ArrayType;
						typedef itk::ImageToImageMetric< InputImageType, OutputImageType > MetricType;
						typedef itk::SingleValuedNonLinearOptimizer OptimizerType;
						typedef double CoordinateRepresentationType;
						typedef itk::Transform< CoordinateRepresentationType, 2, 2 > TransformType;
						typedef itk::Image< unsigned short, 2 > InputImageType;
						typedef double CoordinateRepresentationType;
						typedef itk::InterpolateImageFunction< InputImageType, CoordinateRepresentationType > InterpolatorType;
						typedef itk::ImageRegistrationMethod< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						SO_ITK_SET_FIELD_ARRAY( filter, InitialTransformParameters, double );
						SO_ITK_SET_FIELD_DATA( filter, FixedImage, InputImageType );
						SO_ITK_SET_FIELD_DATA( filter, MovingImage, InputImageType );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, FixedImageRegion, 2 );
						SO_ITK_SET_FIELD_DATA( filter, Interpolator, InterpolatorType );
						SO_ITK_SET_FIELD_DATA( filter, Metric, MetricType );
						SO_ITK_SET_FIELD_DATA( filter, Transform, TransformType );
						SO_ITK_SET_FIELD_DATA( filter, Optimizer, OptimizerType );

						// Start processing the ouputs
						filter->StartRegistration();
						
						// Retrieve the filter's outputs
						ArrayType lastParameters = filter->GetLastTransformParameters();
						unsigned int numberOfParameters = lastParameters.size();						
						float* parameters = new float[ numberOfParameters ];
						for( unsigned int i = 0; i < numberOfParameters; ++ i )
							parameters[i] = lastParameters( i );

                        SO_ENGINE_OUTPUT( LastTransformParameters, SoMFFloat, setValues( 0, numberOfParameters, parameters ) );
						delete [] parameters;

						filter->GetOptimizer()->Register();

						mOptimizer = new SoItkDataOptimizer();
						mOptimizer->ref();
						mOptimizer->setPointer( filter->GetOptimizer() );

						SO_ENGINE_OUTPUT( OutputOptimizer, SoItkSFDataOptimizer, setValue( mOptimizer ) );

						SoDebugError::post( __FILE__, "Registration Done (US 2)" );
					}
					break ;
					case 3:
					{
						typedef itk::Image< unsigned short, 3 > InputImageType;
						typedef itk::Image< unsigned short, 3 > OutputImageType;
						typedef itk::Image< unsigned short, 3 > InputImageType;
						typedef itk::Image< unsigned short, 3 > OutputImageType;
						typedef itk::Array< double > ArrayType;
						typedef itk::ImageToImageMetric< InputImageType, OutputImageType > MetricType;
						typedef itk::SingleValuedNonLinearOptimizer OptimizerType;
						typedef double CoordinateRepresentationType;
						typedef itk::Transform< CoordinateRepresentationType, 3, 3 > TransformType;
						typedef itk::Image< unsigned short, 3 > InputImageType;
						typedef double CoordinateRepresentationType;
						typedef itk::InterpolateImageFunction< InputImageType, CoordinateRepresentationType > InterpolatorType;
						typedef itk::ImageRegistrationMethod< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						SO_ITK_SET_FIELD_ARRAY( filter, InitialTransformParameters, double );
						SO_ITK_SET_FIELD_DATA( filter, FixedImage, InputImageType );
						SO_ITK_SET_FIELD_DATA( filter, MovingImage, InputImageType );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, FixedImageRegion, 3 );
						SO_ITK_SET_FIELD_DATA( filter, Interpolator, InterpolatorType );
						SO_ITK_SET_FIELD_DATA( filter, Metric, MetricType );
						SO_ITK_SET_FIELD_DATA( filter, Transform, TransformType );
						SO_ITK_SET_FIELD_DATA( filter, Optimizer, OptimizerType );

						// Start processing the ouputs
						filter->StartRegistration();
						
						// Retrieve the filter's outputs
						ArrayType lastParameters = filter->GetLastTransformParameters();
						unsigned int numberOfParameters = lastParameters.size();						
						float* parameters = new float[ numberOfParameters ];
						for( unsigned int i = 0; i < numberOfParameters; ++ i )
							parameters[i] = lastParameters( i );

                        SO_ENGINE_OUTPUT( LastTransformParameters, SoMFFloat, setValues( 0, numberOfParameters, parameters ) );
						delete [] parameters;

						filter->GetOptimizer()->Register();

						mOptimizer = new SoItkDataOptimizer();
						mOptimizer->ref();
						mOptimizer->setPointer( filter->GetOptimizer() );

						SO_ENGINE_OUTPUT( OutputOptimizer, SoItkSFDataOptimizer, setValue( mOptimizer ) );

						SoDebugError::post( __FILE__, "Registration Done (US 3)" );
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
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
	}	

	mStartRegistration = false;
}

void 
SoItkImageRegistrationMethod::inputChanged( SoField* whichInput )
{
	if( whichInput == &Start )
	{
		mStartRegistration = true;
	}
}
