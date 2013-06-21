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
#include <itkThresholdSegmentationLevelSetImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkThresholdSegmentationLevelSetImageFilter.h"

SO_ENGINE_SOURCE( SoItkThresholdSegmentationLevelSetImageFilter );

SoItkThresholdSegmentationLevelSetImageFilter::SoItkThresholdSegmentationLevelSetImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkThresholdSegmentationLevelSetImageFilter );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( SmoothingConductance, (0) );
	SO_ENGINE_ADD_INPUT( LowerThreshold, (0) );
	SO_ENGINE_ADD_INPUT( UpperThreshold, (0) );
	SO_ENGINE_ADD_INPUT( EdgeWeight, (0) );
	SO_ENGINE_ADD_INPUT( SmoothingIterations, (0) );
	SO_ENGINE_ADD_INPUT( SmoothingTimeStep, (0) );
}

SoItkThresholdSegmentationLevelSetImageFilter::~SoItkThresholdSegmentationLevelSetImageFilter()
{

}

void
SoItkThresholdSegmentationLevelSetImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkThresholdSegmentationLevelSetImageFilter, SoItkSegmentationLevelSetImageFilter, "SoItkSegmentationLevelSetImageFilter" );
}

bool
SoItkThresholdSegmentationLevelSetImageFilter::checkInput()
{
	switch( FeatureImage.getValue()->getNumDimension() )
	{
		case 2:
		{
			switch( FeatureImage.getValue()->getType() )
			{
				case SoItkDataImage::FLOAT:
				{
					return true;
				}
				break ;
			}
		}
		break ;
		case 3:
		{
			switch( FeatureImage.getValue()->getType() )
			{
				case SoItkDataImage::FLOAT:
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
SoItkThresholdSegmentationLevelSetImageFilter::evaluate()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
		SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( 0 ) );
	}

	if( !FeatureImage.getValue() )
		return ;
	
	if( !Input0.getValue() )
		return ;
	
	if( !checkInput() )
	{
		SoDebugError::post( __FILE__, "Invalid Input Types" );
		return ;
	}

	try
	{
		switch( FeatureImage.getValue()->getNumDimension() )
		{
			case 2:
			{
				switch( FeatureImage.getValue()->getType() )
				{
					case SoItkDataImage::FLOAT:
					{
						typedef itk::Image< float, 2 > InputImageType;
						typedef itk::Image< float, 2 > OutputImageType;
						typedef itk::ThresholdSegmentationLevelSetImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, SmoothingConductance );
						SO_ITK_SET_FIELD_VALUE( filter, LowerThreshold );
						SO_ITK_SET_FIELD_VALUE( filter, UpperThreshold );
						SO_ITK_SET_FIELD_VALUE( filter, EdgeWeight );
						SO_ITK_SET_FIELD_VALUE( filter, SmoothingIterations );
						SO_ITK_SET_FIELD_VALUE( filter, SmoothingTimeStep );
						
						// Inherited from SoItkSegmentationLevelSetImageFilter
						SO_ITK_SET_FIELD_VALUE( filter, FeatureScaling );
						SO_ITK_SET_FIELD_VALUE( filter, AdvectionScaling );
						SO_ITK_SET_FIELD_VALUE( filter, CurvatureScaling );
						typedef itk::Image< float, 2 > InputImageType;
						SO_ITK_SET_FIELD_DATA( filter, FeatureImage, InputImageType );
						SO_ITK_SET_FIELD_VALUE( filter, MaximumPropagationTimeStep );
						SO_ITK_SET_FIELD_VALUE( filter, UseMinimalCurvature );
						SO_ITK_SET_FIELD_VALUE( filter, ReverseExpansionDirection );
						SO_ITK_SET_FIELD_VALUE( filter, PropagationScaling );
						SO_ITK_SET_FIELD_VALUE( filter, MaximumCurvatureTimeStep );
						
						// Inherited from SoItkSparseFieldLevelSetImageFilter
						SO_ITK_SET_FIELD_VALUE( filter, NumberOfLayers );
						SO_ITK_SET_FIELD_VALUE( filter, IsoSurfaceValue );
						SO_ITK_SET_FIELD_VALUE( filter, InterpolateSurfaceLocation );
						
						// Inherited from SoItkFiniteDifferenceImageFilter
						SO_ITK_SET_FIELD_VALUE( filter, UseImageSpacing );
						SO_ITK_SET_FIELD_VALUE( filter, NumberOfIterations );
						SO_ITK_SET_FIELD_VALUE( filter, RMSChange );
						SO_ITK_SET_FIELD_VALUE( filter, ManualReinitialization );
						SO_ITK_SET_FIELD_VALUE( filter, MaximumRMSError );
						
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
				}
			}
			break ;
			case 3:
			{
				switch( FeatureImage.getValue()->getType() )
				{
					case SoItkDataImage::FLOAT:
					{
						typedef itk::Image< float, 3 > InputImageType;
						typedef itk::Image< float, 3 > OutputImageType;
						typedef itk::ThresholdSegmentationLevelSetImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, SmoothingConductance );
						SO_ITK_SET_FIELD_VALUE( filter, LowerThreshold );
						SO_ITK_SET_FIELD_VALUE( filter, UpperThreshold );
						SO_ITK_SET_FIELD_VALUE( filter, EdgeWeight );
						SO_ITK_SET_FIELD_VALUE( filter, SmoothingIterations );
						SO_ITK_SET_FIELD_VALUE( filter, SmoothingTimeStep );
						
						// Inherited from SoItkSegmentationLevelSetImageFilter
						SO_ITK_SET_FIELD_VALUE( filter, FeatureScaling );
						SO_ITK_SET_FIELD_VALUE( filter, AdvectionScaling );
						SO_ITK_SET_FIELD_VALUE( filter, CurvatureScaling );
						typedef itk::Image< float, 3 > InputImageType;
						SO_ITK_SET_FIELD_DATA( filter, FeatureImage, InputImageType );
						SO_ITK_SET_FIELD_VALUE( filter, MaximumPropagationTimeStep );
						SO_ITK_SET_FIELD_VALUE( filter, UseMinimalCurvature );
						SO_ITK_SET_FIELD_VALUE( filter, ReverseExpansionDirection );
						SO_ITK_SET_FIELD_VALUE( filter, PropagationScaling );
						SO_ITK_SET_FIELD_VALUE( filter, MaximumCurvatureTimeStep );
						
						// Inherited from SoItkSparseFieldLevelSetImageFilter
						SO_ITK_SET_FIELD_VALUE( filter, NumberOfLayers );
						SO_ITK_SET_FIELD_VALUE( filter, IsoSurfaceValue );
						SO_ITK_SET_FIELD_VALUE( filter, InterpolateSurfaceLocation );
						
						// Inherited from SoItkFiniteDifferenceImageFilter
						SO_ITK_SET_FIELD_VALUE( filter, UseImageSpacing );
						SO_ITK_SET_FIELD_VALUE( filter, NumberOfIterations );
						SO_ITK_SET_FIELD_VALUE( filter, RMSChange );
						SO_ITK_SET_FIELD_VALUE( filter, ManualReinitialization );
						SO_ITK_SET_FIELD_VALUE( filter, MaximumRMSError );
						
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
