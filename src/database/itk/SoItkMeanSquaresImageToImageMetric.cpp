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
#include <itkMeanSquaresImageToImageMetric.h>
#include <xip/inventor/itk/SoItkSFDataImageMetric.h>
#include "SoItkMeanSquaresImageToImageMetric.h"

SO_ENGINE_SOURCE( SoItkMeanSquaresImageToImageMetric )

SoItkMeanSquaresImageToImageMetric::SoItkMeanSquaresImageToImageMetric()
{
	SO_ENGINE_CONSTRUCTOR( SoItkMeanSquaresImageToImageMetric );
}

SoItkMeanSquaresImageToImageMetric::~SoItkMeanSquaresImageToImageMetric()
{

}

void
SoItkMeanSquaresImageToImageMetric::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkMeanSquaresImageToImageMetric, 
        SoItkImageToImageMetric, "SoItkImageToImageMetric" );	
}

void
SoItkMeanSquaresImageToImageMetric::evaluate()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( Output, SoItkSFDataImageMetric, setValue( 0 ) );
    }
    
	/*
    if( mGradientImage )
    {
        mGradientImage->unref();
        mGradientImage = 0;
        SO_ENGINE_OUTPUT( GradientImage, SoItkSFDataImage, setValue( 0 ) );
    }
    */

    try
    {
        switch( PixelType.getValue() )
		{
			case FLOAT:
			{
				switch( Dimension.getValue() )
				{
					case 2:
					{
                        typedef itk::Image< float, 2 > InputImageType;
						typedef itk::Image< float, 2 > OutputImageType;
                        typedef itk::MeanSquaresImageToImageMetric< InputImageType, OutputImageType > MetricType;
                        typedef itk::Transform< double, 2, 2 > TransformType;
						typedef itk::InterpolateImageFunction< InputImageType, double > InterpolatorType;
                        
                        MetricType::Pointer metric = MetricType::New();
                        metric->Register();
                        
                        // Fixed Image

						/*
                        SoItkDataImage* FixedImage_ = FixedImage.getValue();
						InputImageType* itkFixedImage =
							static_cast< InputImageType* >( FixedImage_->getPointer() );
						if( !itkFixedImage )
							return ;
						metric->SetFixedImage( itkFixedImage );
                        
                        // Moving Image
                        SoItkDataImage* MovingImage_ = MovingImage.getValue();
						InputImageType* itkMovingImage =
							static_cast< InputImageType* >( MovingImage_->getPointer() );
						if( !itkMovingImage )
							return ;
						metric->SetMovingImage( itkMovingImage );
                        
                        // Transform
                        SoItkDataTransform* Transform_ = Transform.getValue();
						TransformType* itkTransform =
							static_cast< TransformType* >( Transform_->getPointer() );
						if( !itkTransform )
							return ;
						metric->SetTransform( itkTransform );
                        
                        // Interpolator
                        SoItkDataInterpolator* Interpolator_ = Interpolator.getValue();
						InterpolatorType* itkInterpolator =
							static_cast< InterpolatorType* >( Interpolator_->getPointer() );
						if( !itkInterpolator )
							return ;
						metric->SetInterpolator( itkInterpolator );
                        
                        // Fixed Image Region
                        typedef itk::ImageRegion< 2 > ImageRegionType;
                        typedef itk::Index< 2 > ImageRegionIndexType;
                        typedef itk::Size< 2 > ImageRegionSizeType;
                        
                        ImageRegionIndexType fixedImageRegionIndex;
                        fixedImageRegionIndex[0] = FixedImageRegionOrigin.getValue()[0];
                        fixedImageRegionIndex[1] = FixedImageRegionOrigin.getValue()[1];
                        
                        ImageRegionSizeType fixedImageRegionSize;
                        fixedImageRegionSize[0] = FixedImageRegionSize.getValue()[0];
                        fixedImageRegionSize[1] = FixedImageRegionSize.getValue()[1];
                        
                        ImageRegionType fixedImageRegion;
                        fixedImageRegion.SetIndex( fixedImageRegionIndex );
                        fixedImageRegion.SetSize( fixedImageRegionSize );
                        
                        metric->SetFixedImageRegion( fixedImageRegion );
                        
                        // Transform Parameters
                        typedef itk::Array< double > ArrayType;
                        ArrayType transformParameters( (double *) TransformParameters.getValues(0), TransformParameters.getNum(), false );
                        metric->SetTransformParameters( transformParameters );
                        
                        metric->SetComputeGradient( ComputeGradient.getValue() );
        
                        if( ComputeGradient.getValue() == TRUE )
                        {
                            metric->GetGradientImage()->Register();
                            
                            mGradientImage = new SoItkDataImage( SoItkDataImage::FLOAT, 2, 
                                FixedImage.getValue()->getModelMatrix() );
                            mGradientImage->ref();
                            mGradientImage->setPointer( metric->GetGradientImage() );
                        }
						*/
                        
						mOutput = new SoItkDataImageMetric( SoItkDataImageMetric::FLOAT, 2 );
                        mOutput->ref();
                        mOutput->setPointer( metric );
					}
					break ;
                    
					case 3:
					{
						typedef itk::Image< float, 3 > InputImageType;
						typedef itk::Image< float, 3 > OutputImageType;
                        typedef itk::MeanSquaresImageToImageMetric< InputImageType, OutputImageType > MetricType;
                        typedef itk::Transform< double, 3, 3 > TransformType;
						typedef itk::InterpolateImageFunction< InputImageType, double > InterpolatorType;
                        
                        MetricType::Pointer metric = MetricType::New();
                        metric->Register();
                        
						/*

                        // Fixed Image
                        SoItkDataImage* FixedImage_ = FixedImage.getValue();
						InputImageType* itkFixedImage =
							static_cast< InputImageType* >( FixedImage_->getPointer() );
						if( !itkFixedImage )
							return ;
						metric->SetFixedImage( itkFixedImage );
                        
                        // Moving Image
                        SoItkDataImage* MovingImage_ = MovingImage.getValue();
						InputImageType* itkMovingImage =
							static_cast< InputImageType* >( MovingImage_->getPointer() );
						if( !itkMovingImage )
							return ;
						metric->SetMovingImage( itkMovingImage );
                        
                        // Transform
                        SoItkDataTransform* Transform_ = Transform.getValue();
						TransformType* itkTransform =
							static_cast< TransformType* >( Transform_->getPointer() );
						if( !itkTransform )
							return ;
						metric->SetTransform( itkTransform );
                        
                        // Interpolator
                        SoItkDataInterpolator* Interpolator_ = Interpolator.getValue();
						InterpolatorType* itkInterpolator =
							static_cast< InterpolatorType* >( Interpolator_->getPointer() );
						if( !itkInterpolator )
							return ;
						metric->SetInterpolator( itkInterpolator );
                        
                        // Fixed Image Region
                        typedef itk::ImageRegion< 3 > ImageRegionType;
                        typedef itk::Index< 3 > ImageRegionIndexType;
                        typedef itk::Size< 3 > ImageRegionSizeType;
                        
                        ImageRegionIndexType fixedImageRegionIndex;
                        fixedImageRegionIndex[0] = FixedImageRegionOrigin.getValue()[0];
                        fixedImageRegionIndex[1] = FixedImageRegionOrigin.getValue()[1];
                        fixedImageRegionIndex[2] = FixedImageRegionOrigin.getValue()[2];
                        
                        ImageRegionSizeType fixedImageRegionSize;
                        fixedImageRegionSize[0] = FixedImageRegionSize.getValue()[0];
                        fixedImageRegionSize[1] = FixedImageRegionSize.getValue()[1];
                        fixedImageRegionSize[2] = FixedImageRegionSize.getValue()[2];
                        
                        ImageRegionType fixedImageRegion;
                        fixedImageRegion.SetIndex( fixedImageRegionIndex );
                        fixedImageRegion.SetSize( fixedImageRegionSize );
                        
                        metric->SetFixedImageRegion( fixedImageRegion );
                        
                        // Transform Parameters
                        typedef itk::Array< double > ArrayType;
                        ArrayType transformParameters( (double *) TransformParameters.getValues(0), TransformParameters.getNum(), false );
                        metric->SetTransformParameters( transformParameters );
                        
                        metric->SetComputeGradient( ComputeGradient.getValue() );
        
                        if( ComputeGradient.getValue() == TRUE )
                        {
                            metric->GetGradientImage()->Register();
                            
                            mGradientImage = new SoItkDataImage( SoItkDataImage::FLOAT, 3, 
                                FixedImage.getValue()->getModelMatrix() );
                            mGradientImage->ref();
                            mGradientImage->setPointer( metric->GetGradientImage() );
                        }
						*/
                        
						mOutput = new SoItkDataImageMetric( SoItkDataImageMetric::FLOAT, 3 );
                        mOutput->ref();
                        mOutput->setPointer( metric );
					}
					break ;
				}
			}
			break ;

			case UNSIGNED_SHORT:
			{
				switch( Dimension.getValue() )
				{
					case 2:
					{
                        typedef itk::Image< unsigned short, 2 > InputImageType;
						typedef itk::Image< unsigned short, 2 > OutputImageType;
                        typedef itk::MeanSquaresImageToImageMetric< InputImageType, OutputImageType > MetricType;
                        typedef itk::Transform< double, 2, 2 > TransformType;
						typedef itk::InterpolateImageFunction< InputImageType, double > InterpolatorType;
                        
                        MetricType::Pointer metric = MetricType::New();
                        metric->Register();

                        /*

                        // Fixed Image
                        SoItkDataImage* FixedImage_ = FixedImage.getValue();
						InputImageType* itkFixedImage =
							static_cast< InputImageType* >( FixedImage_->getPointer() );
						if( !itkFixedImage )
							return ;
						metric->SetFixedImage( itkFixedImage );
                        
                        // Moving Image
                        SoItkDataImage* MovingImage_ = MovingImage.getValue();
						InputImageType* itkMovingImage =
							static_cast< InputImageType* >( MovingImage_->getPointer() );
						if( !itkMovingImage )
							return ;
						metric->SetMovingImage( itkMovingImage );
                        
                        // Transform
                        SoItkDataTransform* Transform_ = Transform.getValue();
						TransformType* itkTransform =
							static_cast< TransformType* >( Transform_->getPointer() );
						if( !itkTransform )
							return ;
						metric->SetTransform( itkTransform );
                        
                        // Interpolator
                        SoItkDataInterpolator* Interpolator_ = Interpolator.getValue();
						InterpolatorType* itkInterpolator =
							static_cast< InterpolatorType* >( Interpolator_->getPointer() );
						if( !itkInterpolator )
							return ;
						metric->SetInterpolator( itkInterpolator );
                        
                        // Fixed Image Region
                        typedef itk::ImageRegion< 2 > ImageRegionType;
                        typedef itk::Index< 2 > ImageRegionIndexType;
                        typedef itk::Size< 2 > ImageRegionSizeType;
                        
                        ImageRegionIndexType fixedImageRegionIndex;
                        fixedImageRegionIndex[0] = FixedImageRegionOrigin.getValue()[0];
                        fixedImageRegionIndex[1] = FixedImageRegionOrigin.getValue()[1];
                        
                        ImageRegionSizeType fixedImageRegionSize;
                        fixedImageRegionSize[0] = FixedImageRegionSize.getValue()[0];
                        fixedImageRegionSize[1] = FixedImageRegionSize.getValue()[1];
                        
                        ImageRegionType fixedImageRegion;
                        fixedImageRegion.SetIndex( fixedImageRegionIndex );
                        fixedImageRegion.SetSize( fixedImageRegionSize );
                        
                        metric->SetFixedImageRegion( fixedImageRegion );
                        
                        // Transform Parameters
                        typedef itk::Array< double > ArrayType;
                        ArrayType transformParameters( (double *) TransformParameters.getValues(0), TransformParameters.getNum(), false );
                        metric->SetTransformParameters( transformParameters );
                        
                        metric->SetComputeGradient( ComputeGradient.getValue() );
        
                        if( ComputeGradient.getValue() == TRUE )
                        {
                            metric->GetGradientImage()->Register();
                            
                            mGradientImage = new SoItkDataImage( SoItkDataImage::FLOAT, 2, 
                                FixedImage.getValue()->getModelMatrix() );
                            mGradientImage->ref();
                            mGradientImage->setPointer( metric->GetGradientImage() );
                        }
                        */

						mOutput = new SoItkDataImageMetric( SoItkDataImageMetric::UNSIGNED_SHORT, 2 );
                        mOutput->ref();
                        mOutput->setPointer( metric );
					}
					break ;
                    
					case 3:
					{
						typedef itk::Image< unsigned short, 3 > InputImageType;
						typedef itk::Image< unsigned short, 3 > OutputImageType;
                        typedef itk::MeanSquaresImageToImageMetric< InputImageType, OutputImageType > MetricType;
                        typedef itk::Transform< double, 3, 3 > TransformType;
						typedef itk::InterpolateImageFunction< InputImageType, double > InterpolatorType;
                        
                        MetricType::Pointer metric = MetricType::New();
                        metric->Register();
                        
						/*

                        // Fixed Image
                        SoItkDataImage* FixedImage_ = FixedImage.getValue();
						InputImageType* itkFixedImage =
							static_cast< InputImageType* >( FixedImage_->getPointer() );
						if( !itkFixedImage )
							return ;
						metric->SetFixedImage( itkFixedImage );
                        
                        // Moving Image
                        SoItkDataImage* MovingImage_ = MovingImage.getValue();
						InputImageType* itkMovingImage =
							static_cast< InputImageType* >( MovingImage_->getPointer() );
						if( !itkMovingImage )
							return ;
						metric->SetMovingImage( itkMovingImage );
                        
                        // Transform
                        SoItkDataTransform* Transform_ = Transform.getValue();
						TransformType* itkTransform =
							static_cast< TransformType* >( Transform_->getPointer() );
						if( !itkTransform )
							return ;
						metric->SetTransform( itkTransform );
                        
                        // Interpolator
                        SoItkDataInterpolator* Interpolator_ = Interpolator.getValue();
						InterpolatorType* itkInterpolator =
							static_cast< InterpolatorType* >( Interpolator_->getPointer() );
						if( !itkInterpolator )
							return ;
						metric->SetInterpolator( itkInterpolator );
                        
                        // Fixed Image Region
                        typedef itk::ImageRegion< 3 > ImageRegionType;
                        typedef itk::Index< 3 > ImageRegionIndexType;
                        typedef itk::Size< 3 > ImageRegionSizeType;
                        
                        ImageRegionIndexType fixedImageRegionIndex;
                        fixedImageRegionIndex[0] = FixedImageRegionOrigin.getValue()[0];
                        fixedImageRegionIndex[1] = FixedImageRegionOrigin.getValue()[1];
                        fixedImageRegionIndex[2] = FixedImageRegionOrigin.getValue()[2];
                        
                        ImageRegionSizeType fixedImageRegionSize;
                        fixedImageRegionSize[0] = FixedImageRegionSize.getValue()[0];
                        fixedImageRegionSize[1] = FixedImageRegionSize.getValue()[1];
                        fixedImageRegionSize[2] = FixedImageRegionSize.getValue()[2];
                        
                        ImageRegionType fixedImageRegion;
                        fixedImageRegion.SetIndex( fixedImageRegionIndex );
                        fixedImageRegion.SetSize( fixedImageRegionSize );
                        
                        metric->SetFixedImageRegion( fixedImageRegion );
                        
                        // Transform Parameters
                        typedef itk::Array< double > ArrayType;
                        ArrayType transformParameters( (double *) TransformParameters.getValues(0), TransformParameters.getNum(), false );
                        metric->SetTransformParameters( transformParameters );
                        
                        metric->SetComputeGradient( ComputeGradient.getValue() );
        
                        if( ComputeGradient.getValue() == TRUE )
                        {
                            metric->GetGradientImage()->Register();
                            
                            mGradientImage = new SoItkDataImage( SoItkDataImage::FLOAT, 3, 
                                FixedImage.getValue()->getModelMatrix() );
                            mGradientImage->ref();
                            mGradientImage->setPointer( metric->GetGradientImage() );
                        }
						*/
                        
                        mOutput = new SoItkDataImageMetric( SoItkDataImageMetric::UNSIGNED_SHORT, 3 );
                        mOutput->ref();
                        mOutput->setPointer( metric );
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
    
	SO_ENGINE_OUTPUT( Output, SoItkSFDataImageMetric, setValue( mOutput ) );
//	SO_ENGINE_OUTPUT( GradientImage, SoItkSFDataImage, setValue( mGradientImage ) );
}
