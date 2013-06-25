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
#include <xip/inventor/itk/SoItkSFDataImageMetric.h>
#include "SoItkImageToImageMetric.h"

SO_ENGINE_ABSTRACT_SOURCE( SoItkImageToImageMetric )

SoItkImageToImageMetric::SoItkImageToImageMetric()
{
	SO_ENGINE_CONSTRUCTOR( SoItkImageToImageMetric );

	SO_ENGINE_DEFINE_ENUM_VALUE( PixelTypeEnum, UNSIGNED_SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( PixelTypeEnum, FLOAT );
	SO_ENGINE_SET_SF_ENUM_TYPE( PixelType, PixelTypeEnum );
	SO_ENGINE_ADD_INPUT( PixelType, (FLOAT) );

	SO_ENGINE_ADD_INPUT( Dimension, (2) );
    
//    SO_ENGINE_ADD_INPUT( FixedImage, (0) );
//    SO_ENGINE_ADD_INPUT( MovingImage, (0) );
//    SO_ENGINE_ADD_INPUT( Transform, (0) );
//    SO_ENGINE_ADD_INPUT( Interpolator, (0) );
//    SO_ENGINE_ADD_INPUT( FixedImageRegionOrigin, (0, 0, 0) );
//    SO_ENGINE_ADD_INPUT( FixedImageRegionSize, (0, 0, 0) );
//    SO_ENGINE_ADD_INPUT( TransformParameters, (0) );
//    TransformParameters.setNum(0);
//    SO_ENGINE_ADD_INPUT( ComputeGradient, (FALSE) );
	
//    SO_ENGINE_ADD_OUTPUT( NumberOfPixelsCounted, SoSFFloat );
//    SO_ENGINE_ADD_OUTPUT( NumberOfParameters, SoSFFloat );
//    SO_ENGINE_ADD_OUTPUT( GradientImage, SoItkSFDataImage );

    mGradientImage = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataImageMetric );
    mOutput = 0;
}

SoItkImageToImageMetric::~SoItkImageToImageMetric()
{
    if( mGradientImage )
    {
        mGradientImage->unref();
        mGradientImage = 0;
    }
    
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
    }
}

void
SoItkImageToImageMetric::initClass()
{
	SO_ENGINE_INIT_ABSTRACT_CLASS( SoItkImageToImageMetric, SoEngine, "Engine" );	
}
