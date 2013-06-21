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
#include <itkNaryFunctorImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkNaryFunctorImageFilter.h"

SO_ENGINE_ABSTRACT_SOURCE( SoItkNaryFunctorImageFilter );

SoItkNaryFunctorImageFilter::SoItkNaryFunctorImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkNaryFunctorImageFilter );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( Input1, (0) );
}

SoItkNaryFunctorImageFilter::~SoItkNaryFunctorImageFilter()
{

}

void
SoItkNaryFunctorImageFilter::initClass()
{
	SO_ENGINE_INIT_ABSTRACT_CLASS( SoItkNaryFunctorImageFilter, SoItkInPlaceImageFilter, "SoItkInPlaceImageFilter" );
}

