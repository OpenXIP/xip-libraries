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
#include <itkFiniteDifferenceImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkFiniteDifferenceImageFilter.h"

SO_ENGINE_ABSTRACT_SOURCE( SoItkFiniteDifferenceImageFilter );

SoItkFiniteDifferenceImageFilter::SoItkFiniteDifferenceImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkFiniteDifferenceImageFilter );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( UseImageSpacing, (false) );
	SO_ENGINE_ADD_INPUT( NumberOfIterations, (10) );
	SO_ENGINE_ADD_INPUT( RMSChange, (0.0) );
	SO_ENGINE_ADD_INPUT( ManualReinitialization, (false) );
	SO_ENGINE_ADD_INPUT( MaximumRMSError, (0.0) );
}

SoItkFiniteDifferenceImageFilter::~SoItkFiniteDifferenceImageFilter()
{

}

void
SoItkFiniteDifferenceImageFilter::initClass()
{
	SO_ENGINE_INIT_ABSTRACT_CLASS( SoItkFiniteDifferenceImageFilter, SoItkInPlaceImageFilter, "SoItkInPlaceImageFilter" );
}

