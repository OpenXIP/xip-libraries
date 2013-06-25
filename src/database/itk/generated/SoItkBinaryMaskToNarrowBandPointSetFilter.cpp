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
#include <itkMesh.h>
#include <itkBinaryMaskToNarrowBandPointSetFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkBinaryMaskToNarrowBandPointSetFilter.h"

SO_ENGINE_SOURCE( SoItkBinaryMaskToNarrowBandPointSetFilter );

SoItkBinaryMaskToNarrowBandPointSetFilter::SoItkBinaryMaskToNarrowBandPointSetFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkBinaryMaskToNarrowBandPointSetFilter );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( BandWidth, (5) );
}

SoItkBinaryMaskToNarrowBandPointSetFilter::~SoItkBinaryMaskToNarrowBandPointSetFilter()
{

}

void
SoItkBinaryMaskToNarrowBandPointSetFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkBinaryMaskToNarrowBandPointSetFilter, SoItkImageToMeshFilter, "SoItkImageToMeshFilter" );
}

bool
SoItkBinaryMaskToNarrowBandPointSetFilter::checkInput()
{
	switch( Input.getValue()->getType() )
	{
		case SoItkDataImage::FLOAT:
		{
			switch( Input.getValue()->getNumDimension() )
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
SoItkBinaryMaskToNarrowBandPointSetFilter::evaluate()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
		SO_ENGINE_OUTPUT( Output, SoItkSFDataPointSet, setValue( 0 ) );
	}

	if( !Input.getValue() )
		return ;
	
	if( !checkInput() )
	{
		SoDebugError::post( __FILE__, "Invalid Input Types" );
		return ;
	}

	try
	{
		switch( Input.getValue()->getType() )
		{
			case SoItkDataImage::FLOAT:
			{
				switch( Input.getValue()->getNumDimension() )
				{
					case 2:
					{
						typedef itk::Image< float, 2 > InputImageType;
						typedef itk::Mesh< float, 2 > OutputMeshType;
						typedef itk::BinaryMaskToNarrowBandPointSetFilter< InputImageType, OutputMeshType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, BandWidth );
						
						// Inherited from SoItkImageToMeshFilter
						typedef itk::Image< float, 2 > InputImageType;
						SO_ITK_SET_FIELD_DATA( filter, Input, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						filter->GetOutput()->Register();
						mOutput = new SoItkDataPointSet( SoItkDataPointSet::FLOAT, 2 );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
					case 3:
					{
						typedef itk::Image< float, 3 > InputImageType;
						typedef itk::Mesh< float, 3 > OutputMeshType;
						typedef itk::BinaryMaskToNarrowBandPointSetFilter< InputImageType, OutputMeshType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, BandWidth );
						
						// Inherited from SoItkImageToMeshFilter
						typedef itk::Image< float, 3 > InputImageType;
						SO_ITK_SET_FIELD_DATA( filter, Input, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						filter->GetOutput()->Register();
						mOutput = new SoItkDataPointSet( SoItkDataPointSet::FLOAT, 3 );
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

}
