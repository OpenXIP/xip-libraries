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
#include <itkStatisticsImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkStatisticsImageFilter.h"

SO_ENGINE_SOURCE( SoItkStatisticsImageFilter );

SoItkStatisticsImageFilter::SoItkStatisticsImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkStatisticsImageFilter );
	
	// Outputs
	SO_ENGINE_ADD_OUTPUT( Sum, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( Maximum, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( Mean, SoSFFloat );
	mMaximumOutput = 0;
	SO_ENGINE_ADD_OUTPUT( MaximumOutput, SoItkSFDataDecorator );
	mSumOutput = 0;
	SO_ENGINE_ADD_OUTPUT( SumOutput, SoItkSFDataDecorator );
	SO_ENGINE_ADD_OUTPUT( Variance, SoSFFloat );
	mMeanOutput = 0;
	SO_ENGINE_ADD_OUTPUT( MeanOutput, SoItkSFDataDecorator );
	mVarianceOutput = 0;
	SO_ENGINE_ADD_OUTPUT( VarianceOutput, SoItkSFDataDecorator );
	mMinimumOutput = 0;
	SO_ENGINE_ADD_OUTPUT( MinimumOutput, SoItkSFDataDecorator );
	mSigmaOutput = 0;
	SO_ENGINE_ADD_OUTPUT( SigmaOutput, SoItkSFDataDecorator );
	SO_ENGINE_ADD_OUTPUT( Sigma, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( Minimum, SoSFFloat );
}

SoItkStatisticsImageFilter::~SoItkStatisticsImageFilter()
{
	if( mMaximumOutput )
		mMaximumOutput->unref();
	mMaximumOutput = 0;
	if( mSumOutput )
		mSumOutput->unref();
	mSumOutput = 0;
	if( mMeanOutput )
		mMeanOutput->unref();
	mMeanOutput = 0;
	if( mVarianceOutput )
		mVarianceOutput->unref();
	mVarianceOutput = 0;
	if( mMinimumOutput )
		mMinimumOutput->unref();
	mMinimumOutput = 0;
	if( mSigmaOutput )
		mSigmaOutput->unref();
	mSigmaOutput = 0;
}

void
SoItkStatisticsImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkStatisticsImageFilter, SoItkImageToImageFilter, "SoItkImageToImageFilter" );
}

bool
SoItkStatisticsImageFilter::checkInput()
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
SoItkStatisticsImageFilter::evaluate()
{
	if( mMaximumOutput )
	{
		mMaximumOutput->unref();
		mMaximumOutput = 0;
		SO_ENGINE_OUTPUT( MaximumOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mSumOutput )
	{
		mSumOutput->unref();
		mSumOutput = 0;
		SO_ENGINE_OUTPUT( SumOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mMeanOutput )
	{
		mMeanOutput->unref();
		mMeanOutput = 0;
		SO_ENGINE_OUTPUT( MeanOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mVarianceOutput )
	{
		mVarianceOutput->unref();
		mVarianceOutput = 0;
		SO_ENGINE_OUTPUT( VarianceOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mMinimumOutput )
	{
		mMinimumOutput->unref();
		mMinimumOutput = 0;
		SO_ENGINE_OUTPUT( MinimumOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mSigmaOutput )
	{
		mSigmaOutput->unref();
		mSigmaOutput = 0;
		SO_ENGINE_OUTPUT( SigmaOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
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
						typedef itk::Image< float, 2 > OutputImageType;
						typedef itk::StatisticsImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< float, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Sum, SoSFFloat, setValue( filter->GetSum() ) ); 
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						SO_ENGINE_OUTPUT( Mean, SoSFFloat, setValue( filter->GetMean() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetSumOutput()->Register();
						mSumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mSumOutput->ref();
						mSumOutput->setPointer( filter->GetSumOutput() );
						SO_ENGINE_OUTPUT( Variance, SoSFFloat, setValue( filter->GetVariance() ) ); 
						filter->GetMeanOutput()->Register();
						mMeanOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMeanOutput->ref();
						mMeanOutput->setPointer( filter->GetMeanOutput() );
						filter->GetVarianceOutput()->Register();
						mVarianceOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mVarianceOutput->ref();
						mVarianceOutput->setPointer( filter->GetVarianceOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
						filter->GetSigmaOutput()->Register();
						mSigmaOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mSigmaOutput->ref();
						mSigmaOutput->setPointer( filter->GetSigmaOutput() );
						SO_ENGINE_OUTPUT( Sigma, SoSFFloat, setValue( filter->GetSigma() ) ); 
						SO_ENGINE_OUTPUT( Minimum, SoSFFloat, setValue( filter->GetMinimum() ) ); 
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 2,
							Input0.getValue()->getModelMatrix() );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
					case 3:
					{
						typedef itk::Image< float, 3 > OutputImageType;
						typedef itk::StatisticsImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< float, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Sum, SoSFFloat, setValue( filter->GetSum() ) ); 
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						SO_ENGINE_OUTPUT( Mean, SoSFFloat, setValue( filter->GetMean() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetSumOutput()->Register();
						mSumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mSumOutput->ref();
						mSumOutput->setPointer( filter->GetSumOutput() );
						SO_ENGINE_OUTPUT( Variance, SoSFFloat, setValue( filter->GetVariance() ) ); 
						filter->GetMeanOutput()->Register();
						mMeanOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMeanOutput->ref();
						mMeanOutput->setPointer( filter->GetMeanOutput() );
						filter->GetVarianceOutput()->Register();
						mVarianceOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mVarianceOutput->ref();
						mVarianceOutput->setPointer( filter->GetVarianceOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
						filter->GetSigmaOutput()->Register();
						mSigmaOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mSigmaOutput->ref();
						mSigmaOutput->setPointer( filter->GetSigmaOutput() );
						SO_ENGINE_OUTPUT( Sigma, SoSFFloat, setValue( filter->GetSigma() ) ); 
						SO_ENGINE_OUTPUT( Minimum, SoSFFloat, setValue( filter->GetMinimum() ) ); 
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
						typedef itk::Image< unsigned short, 2 > OutputImageType;
						typedef itk::StatisticsImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< unsigned short, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Sum, SoSFFloat, setValue( filter->GetSum() ) ); 
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						SO_ENGINE_OUTPUT( Mean, SoSFFloat, setValue( filter->GetMean() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetSumOutput()->Register();
						mSumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mSumOutput->ref();
						mSumOutput->setPointer( filter->GetSumOutput() );
						SO_ENGINE_OUTPUT( Variance, SoSFFloat, setValue( filter->GetVariance() ) ); 
						filter->GetMeanOutput()->Register();
						mMeanOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMeanOutput->ref();
						mMeanOutput->setPointer( filter->GetMeanOutput() );
						filter->GetVarianceOutput()->Register();
						mVarianceOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mVarianceOutput->ref();
						mVarianceOutput->setPointer( filter->GetVarianceOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
						filter->GetSigmaOutput()->Register();
						mSigmaOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mSigmaOutput->ref();
						mSigmaOutput->setPointer( filter->GetSigmaOutput() );
						SO_ENGINE_OUTPUT( Sigma, SoSFFloat, setValue( filter->GetSigma() ) ); 
						SO_ENGINE_OUTPUT( Minimum, SoSFFloat, setValue( filter->GetMinimum() ) ); 
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 2,
							Input0.getValue()->getModelMatrix() );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
					case 3:
					{
						typedef itk::Image< unsigned short, 3 > OutputImageType;
						typedef itk::StatisticsImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< unsigned short, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Sum, SoSFFloat, setValue( filter->GetSum() ) ); 
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						SO_ENGINE_OUTPUT( Mean, SoSFFloat, setValue( filter->GetMean() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetSumOutput()->Register();
						mSumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mSumOutput->ref();
						mSumOutput->setPointer( filter->GetSumOutput() );
						SO_ENGINE_OUTPUT( Variance, SoSFFloat, setValue( filter->GetVariance() ) ); 
						filter->GetMeanOutput()->Register();
						mMeanOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMeanOutput->ref();
						mMeanOutput->setPointer( filter->GetMeanOutput() );
						filter->GetVarianceOutput()->Register();
						mVarianceOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mVarianceOutput->ref();
						mVarianceOutput->setPointer( filter->GetVarianceOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
						filter->GetSigmaOutput()->Register();
						mSigmaOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mSigmaOutput->ref();
						mSigmaOutput->setPointer( filter->GetSigmaOutput() );
						SO_ENGINE_OUTPUT( Sigma, SoSFFloat, setValue( filter->GetSigma() ) ); 
						SO_ENGINE_OUTPUT( Minimum, SoSFFloat, setValue( filter->GetMinimum() ) ); 
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

	SO_ENGINE_OUTPUT( MaximumOutput, SoItkSFDataDecorator, setValue( mMaximumOutput ) );
	SO_ENGINE_OUTPUT( SumOutput, SoItkSFDataDecorator, setValue( mSumOutput ) );
	SO_ENGINE_OUTPUT( MeanOutput, SoItkSFDataDecorator, setValue( mMeanOutput ) );
	SO_ENGINE_OUTPUT( VarianceOutput, SoItkSFDataDecorator, setValue( mVarianceOutput ) );
	SO_ENGINE_OUTPUT( MinimumOutput, SoItkSFDataDecorator, setValue( mMinimumOutput ) );
	SO_ENGINE_OUTPUT( SigmaOutput, SoItkSFDataDecorator, setValue( mSigmaOutput ) );
	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( mOutput ) );
}
