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
#include <itkFastMarchingImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkFastMarchingImageFilter.h"

SO_ENGINE_SOURCE( SoItkFastMarchingImageFilter );

SoItkFastMarchingImageFilter::SoItkFastMarchingImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkFastMarchingImageFilter );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( NormalizationFactor, (1.0) );
	SO_ENGINE_ADD_INPUT( OutputRegion, (0) );
	OutputRegion.setNum(0);
	SO_ENGINE_ADD_INPUT( OutputSpacing, (1.0) );
	SO_ENGINE_ADD_INPUT( OutputOrigin, (0) );
	OutputOrigin.setNum(0);
	SO_ENGINE_ADD_INPUT( CollectPoints, (false) );
	SO_ENGINE_ADD_INPUT( TrialPoints, () );
	SO_ENGINE_ADD_INPUT( AlivePoints, () );
	SO_ENGINE_ADD_INPUT( OverrideOutputInformation, (false) );
	SO_ENGINE_ADD_INPUT( OutputSize, (0) );
	OutputSize.setNum(0);
	SO_ENGINE_ADD_INPUT( StoppingValue, (0) );
	SO_ENGINE_ADD_INPUT( SpeedConstant, (1.0) );
}

SoItkFastMarchingImageFilter::~SoItkFastMarchingImageFilter()
{

}

void
SoItkFastMarchingImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkFastMarchingImageFilter, SoItkImageToImageFilter, "SoItkImageToImageFilter" );
}

bool
SoItkFastMarchingImageFilter::checkInput()
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
SoItkFastMarchingImageFilter::evaluate()
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
						typedef itk::FastMarchingImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, NormalizationFactor );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, OutputRegion, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, OutputSpacing );
						SO_ITK_SET_FIELD_POINT( filter, OutputOrigin, double, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, CollectPoints );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, TrialPoints, float, 2 );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, AlivePoints, float, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, OverrideOutputInformation );
						SO_ITK_SET_FIELD_SIZE( filter, OutputSize, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, StoppingValue );
						SO_ITK_SET_FIELD_VALUE( filter, SpeedConstant );
						
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
						typedef itk::FastMarchingImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, NormalizationFactor );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, OutputRegion, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, OutputSpacing );
						SO_ITK_SET_FIELD_POINT( filter, OutputOrigin, double, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, CollectPoints );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, TrialPoints, float, 3 );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, AlivePoints, float, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, OverrideOutputInformation );
						SO_ITK_SET_FIELD_SIZE( filter, OutputSize, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, StoppingValue );
						SO_ITK_SET_FIELD_VALUE( filter, SpeedConstant );
						
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
						typedef itk::FastMarchingImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, NormalizationFactor );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, OutputRegion, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, OutputSpacing );
						SO_ITK_SET_FIELD_POINT( filter, OutputOrigin, double, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, CollectPoints );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, TrialPoints, unsigned short, 2 );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, AlivePoints, unsigned short, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, OverrideOutputInformation );
						SO_ITK_SET_FIELD_SIZE( filter, OutputSize, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, StoppingValue );
						SO_ITK_SET_FIELD_VALUE( filter, SpeedConstant );
						
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
						typedef itk::FastMarchingImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, NormalizationFactor );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, OutputRegion, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, OutputSpacing );
						SO_ITK_SET_FIELD_POINT( filter, OutputOrigin, double, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, CollectPoints );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, TrialPoints, unsigned short, 3 );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, AlivePoints, unsigned short, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, OverrideOutputInformation );
						SO_ITK_SET_FIELD_SIZE( filter, OutputSize, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, StoppingValue );
						SO_ITK_SET_FIELD_VALUE( filter, SpeedConstant );
						
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
