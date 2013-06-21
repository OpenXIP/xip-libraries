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
#include <itkMinimumMaximumImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkMinimumMaximumImageFilter.h"

SO_ENGINE_SOURCE( SoItkMinimumMaximumImageFilter );

SoItkMinimumMaximumImageFilter::SoItkMinimumMaximumImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkMinimumMaximumImageFilter );
	
	// Outputs
	SO_ENGINE_ADD_OUTPUT( Maximum, SoSFFloat );
	mMaximumOutput = 0;
	SO_ENGINE_ADD_OUTPUT( MaximumOutput, SoItkSFDataDecorator );
	mMinimumOutput = 0;
	SO_ENGINE_ADD_OUTPUT( MinimumOutput, SoItkSFDataDecorator );
	SO_ENGINE_ADD_OUTPUT( Minimum, SoSFFloat );
}

SoItkMinimumMaximumImageFilter::~SoItkMinimumMaximumImageFilter()
{
	if( mMaximumOutput )
		mMaximumOutput->unref();
	mMaximumOutput = 0;
	if( mMinimumOutput )
		mMinimumOutput->unref();
	mMinimumOutput = 0;
}

void
SoItkMinimumMaximumImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkMinimumMaximumImageFilter, SoItkImageToImageFilter, "SoItkImageToImageFilter" );
}

bool
SoItkMinimumMaximumImageFilter::checkInput()
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
SoItkMinimumMaximumImageFilter::evaluate()
{
	if( mMaximumOutput )
	{
		mMaximumOutput->unref();
		mMaximumOutput = 0;
		SO_ENGINE_OUTPUT( MaximumOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mMinimumOutput )
	{
		mMinimumOutput->unref();
		mMinimumOutput = 0;
		SO_ENGINE_OUTPUT( MinimumOutput, SoItkSFDataDecorator, setValue( 0 ) );
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
						typedef itk::MinimumMaximumImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< float, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
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
						typedef itk::MinimumMaximumImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< float, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
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
						typedef itk::MinimumMaximumImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< unsigned short, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
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
						typedef itk::MinimumMaximumImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< unsigned short, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
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
	SO_ENGINE_OUTPUT( MinimumOutput, SoItkSFDataDecorator, setValue( mMinimumOutput ) );
	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( mOutput ) );
}
