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
#include <itkImage.h>
#include <itkLinearInterpolateImageFunction.h>
#include <xip/inventor/itk/SoItkSFDataInterpolator.h>
#include "SoItkLinearInterpolateImageFunction.h"

SO_ENGINE_SOURCE( SoItkLinearInterpolateImageFunction )

SoItkLinearInterpolateImageFunction::SoItkLinearInterpolateImageFunction()
{
	SO_ENGINE_CONSTRUCTOR( SoItkLinearInterpolateImageFunction );


}

SoItkLinearInterpolateImageFunction::~SoItkLinearInterpolateImageFunction()
{

}

void
SoItkLinearInterpolateImageFunction::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkLinearInterpolateImageFunction, 
        SoItkInterpolateImageFunction, "SoItkInterpolateImageFunction" );
}

void
SoItkLinearInterpolateImageFunction::evaluate()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( Output, SoItkSFDataInterpolator, setValue( 0 ) );
    }
    
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
						typedef itk::Image< float, 2 > ImageType;
						typedef itk::LinearInterpolateImageFunction< ImageType, double > InterpolatorType;
						
						InterpolatorType::Pointer interpolator = InterpolatorType::New();
						interpolator->Register();

						mOutput = new SoItkDataInterpolator( SoItkDataInterpolator::FLOAT, 2 );
						mOutput->ref();
						mOutput->setPointer( interpolator );        
					}
					break ;

					case 3:
					{
						typedef itk::Image< float, 3 > ImageType;
						typedef itk::LinearInterpolateImageFunction< ImageType, double > InterpolatorType;
						
						InterpolatorType::Pointer interpolator = InterpolatorType::New();
						interpolator->Register();

						mOutput = new SoItkDataInterpolator( SoItkDataInterpolator::FLOAT, 3 );
						mOutput->ref();
						mOutput->setPointer( interpolator );        
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
						typedef itk::Image< unsigned short, 2 > ImageType;
						typedef itk::LinearInterpolateImageFunction< ImageType, double > InterpolatorType;
						
						InterpolatorType::Pointer interpolator = InterpolatorType::New();
						interpolator->Register();

						mOutput = new SoItkDataInterpolator( SoItkDataInterpolator::UNSIGNED_SHORT, 2 );
						mOutput->ref();
						mOutput->setPointer( interpolator );        
					}
					break ;

					case 3:
					{
						typedef itk::Image< unsigned short, 3 > ImageType;
						typedef itk::LinearInterpolateImageFunction< ImageType, double > InterpolatorType;
						
						InterpolatorType::Pointer interpolator = InterpolatorType::New();
						interpolator->Register();

						mOutput = new SoItkDataInterpolator( SoItkDataInterpolator::UNSIGNED_SHORT, 3 );
						mOutput->ref();
						mOutput->setPointer( interpolator );        
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
    
	SO_ENGINE_OUTPUT( Output, SoItkSFDataInterpolator, setValue( mOutput ) );
}
