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
#include <itkCheckerBoardImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkCheckerBoardImageFilter.h"

SO_ENGINE_SOURCE( SoItkCheckerBoardImageFilter );

SoItkCheckerBoardImageFilter::SoItkCheckerBoardImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkCheckerBoardImageFilter );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( Input1, (0) );
	SO_ENGINE_ADD_INPUT( CheckerPattern, (0) );
	CheckerPattern.setNum(0);
}

SoItkCheckerBoardImageFilter::~SoItkCheckerBoardImageFilter()
{

}

void
SoItkCheckerBoardImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkCheckerBoardImageFilter, SoItkImageToImageFilter, "SoItkImageToImageFilter" );
}

bool
SoItkCheckerBoardImageFilter::checkInput()
{
	switch( Input1.getValue()->getNumDimension() )
	{
		case 2:
		{
			switch( Input1.getValue()->getType() )
			{
				case SoItkDataImage::FLOAT:
				{
					return true;
				}
				break ;
				case SoItkDataImage::UNSIGNED_SHORT:
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
				case SoItkDataImage::FLOAT:
				{
					return true;
				}
				break ;
				case SoItkDataImage::UNSIGNED_SHORT:
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
SoItkCheckerBoardImageFilter::evaluate()
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
					case SoItkDataImage::FLOAT:
					{
						typedef itk::Image< float, 2 > OutputImageType;
						typedef itk::CheckerBoardImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						typedef itk::Image< float, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 1, InputImageType );
						SO_ITK_SET_FIELD_FIXEDARRAY( filter, CheckerPattern, unsigned int, 2 );
						
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
					case SoItkDataImage::UNSIGNED_SHORT:
					{
						typedef itk::Image< unsigned short, 2 > OutputImageType;
						typedef itk::CheckerBoardImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						typedef itk::Image< unsigned short, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 1, InputImageType );
						SO_ITK_SET_FIELD_FIXEDARRAY( filter, CheckerPattern, unsigned int, 2 );
						
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
				}
			}
			break ;
			case 3:
			{
				switch( Input1.getValue()->getType() )
				{
					case SoItkDataImage::FLOAT:
					{
						typedef itk::Image< float, 3 > OutputImageType;
						typedef itk::CheckerBoardImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						typedef itk::Image< float, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 1, InputImageType );
						SO_ITK_SET_FIELD_FIXEDARRAY( filter, CheckerPattern, unsigned int, 3 );
						
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
					case SoItkDataImage::UNSIGNED_SHORT:
					{
						typedef itk::Image< unsigned short, 3 > OutputImageType;
						typedef itk::CheckerBoardImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						typedef itk::Image< unsigned short, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 1, InputImageType );
						SO_ITK_SET_FIELD_FIXEDARRAY( filter, CheckerPattern, unsigned int, 3 );
						
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
