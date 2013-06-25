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
#include <xip/inventor/itk/SoItkSFDataOptimizer.h>
#include "SoItkRegularStepGradientDescentBaseOptimizer.h"

SO_ENGINE_ABSTRACT_SOURCE( SoItkRegularStepGradientDescentBaseOptimizer )

SoItkRegularStepGradientDescentBaseOptimizer::SoItkRegularStepGradientDescentBaseOptimizer()
{
	SO_ENGINE_CONSTRUCTOR( SoItkRegularStepGradientDescentBaseOptimizer );
    
    SO_ENGINE_ADD_INPUT( Minimize, (TRUE) );
    SO_ENGINE_ADD_INPUT( MinimumStepLength, (1e-3) );
    SO_ENGINE_ADD_INPUT( MaximumStepLength, (1.f) );
    SO_ENGINE_ADD_INPUT( RelaxationFactor, (0.5f) );
    SO_ENGINE_ADD_INPUT( NumberOfIterations, (100) );
    SO_ENGINE_ADD_INPUT( GradientMagnitudeTolerance, (1e-4) );
    
//    SO_ENGINE_ADD_OUTPUT( Value, SoSFFloat );
//    SO_ENGINE_ADD_OUTPUT( CurrentIteration, SoSFFloat );
//    SO_ENGINE_ADD_OUTPUT( CurrentStepLength, SoSFFloat );
}

SoItkRegularStepGradientDescentBaseOptimizer::~SoItkRegularStepGradientDescentBaseOptimizer()
{

}

void
SoItkRegularStepGradientDescentBaseOptimizer::initClass()
{
	SO_ENGINE_INIT_ABSTRACT_CLASS( SoItkRegularStepGradientDescentBaseOptimizer,
        SoItkSingleValuedNonLinearOptimizer, "SoItkSingleValuedNonLinearOptimizer" );	
}
