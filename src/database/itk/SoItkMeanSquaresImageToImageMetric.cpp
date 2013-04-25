/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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