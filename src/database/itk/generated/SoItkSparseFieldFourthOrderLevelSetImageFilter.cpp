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
#include <itkSparseFieldFourthOrderLevelSetImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkSparseFieldFourthOrderLevelSetImageFilter.h"

SO_ENGINE_ABSTRACT_SOURCE( SoItkSparseFieldFourthOrderLevelSetImageFilter );

SoItkSparseFieldFourthOrderLevelSetImageFilter::SoItkSparseFieldFourthOrderLevelSetImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkSparseFieldFourthOrderLevelSetImageFilter );
	
	// Inputs
	SO_ENGINE_ADD_INPUT( CurvatureBandWidth, (0) );
	SO_ENGINE_ADD_INPUT( NumberOfLayers, (0) );
	SO_ENGINE_ADD_INPUT( NormalProcessUnsharpWeight, (0) );
	SO_ENGINE_ADD_INPUT( NormalProcessConductance, (0) );
	SO_ENGINE_ADD_INPUT( NormalProcessUnsharpFlag, (false) );
	SO_ENGINE_ADD_INPUT( RMSChangeNormalProcessTrigger, (0) );
	SO_ENGINE_ADD_INPUT( MaxNormalIteration, (25) );
	SO_ENGINE_ADD_INPUT( MaxRefitIteration, (100) );
	SO_ENGINE_ADD_INPUT( NormalProcessType, (0) );
}

SoItkSparseFieldFourthOrderLevelSetImageFilter::~SoItkSparseFieldFourthOrderLevelSetImageFilter()
{

}

void
SoItkSparseFieldFourthOrderLevelSetImageFilter::initClass()
{
	SO_ENGINE_INIT_ABSTRACT_CLASS( SoItkSparseFieldFourthOrderLevelSetImageFilter, SoItkSparseFieldLevelSetImageFilter, "SoItkSparseFieldLevelSetImageFilter" );
}

