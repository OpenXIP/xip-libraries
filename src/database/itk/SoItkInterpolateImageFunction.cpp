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
#include <xip/inventor/itk/SoItkSFDataInterpolator.h>
#include "SoItkInterpolateImageFunction.h"

SO_ENGINE_ABSTRACT_SOURCE( SoItkInterpolateImageFunction )

SoItkInterpolateImageFunction::SoItkInterpolateImageFunction()
{
	SO_ENGINE_CONSTRUCTOR( SoItkInterpolateImageFunction );

	SO_ENGINE_DEFINE_ENUM_VALUE( PixelTypeEnum, UNSIGNED_SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( PixelTypeEnum, FLOAT );
	SO_ENGINE_SET_SF_ENUM_TYPE( PixelType, PixelTypeEnum );
	SO_ENGINE_ADD_INPUT( PixelType, (FLOAT) );

	SO_ENGINE_ADD_INPUT( Dimension, (2) );
}

SoItkInterpolateImageFunction::~SoItkInterpolateImageFunction()
{
    
}

void
SoItkInterpolateImageFunction::initClass()
{
	SO_ENGINE_INIT_ABSTRACT_CLASS( SoItkInterpolateImageFunction, 
        SoItkImageFunction, "SoItkImageFunction" );	
}
