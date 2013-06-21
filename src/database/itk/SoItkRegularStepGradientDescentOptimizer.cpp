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
#include <itkRegularStepGradientDescentOptimizer.h>
#include <xip/inventor/itk/SoItkSFDataOptimizer.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkRegularStepGradientDescentOptimizer.h"

SO_ENGINE_SOURCE( SoItkRegularStepGradientDescentOptimizer )

SoItkRegularStepGradientDescentOptimizer::SoItkRegularStepGradientDescentOptimizer()
{
	SO_ENGINE_CONSTRUCTOR( SoItkRegularStepGradientDescentOptimizer );
}

SoItkRegularStepGradientDescentOptimizer::~SoItkRegularStepGradientDescentOptimizer()
{

}

void
SoItkRegularStepGradientDescentOptimizer::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkRegularStepGradientDescentOptimizer, 
        SoItkRegularStepGradientDescentBaseOptimizer,
        "SoItkRegularStepGradientDescentBaseOptimizer" );
}

void
SoItkRegularStepGradientDescentOptimizer::evaluate()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( Output, SoItkSFDataOptimizer, setValue( 0 ) );
    }
    
    try
    {      
        typedef itk::RegularStepGradientDescentOptimizer OptimizerType;
        OptimizerType::Pointer optimizer = OptimizerType::New();
	        
        // From SoItkOptimizer
		SO_ITK_SET_FIELD_ARRAY( optimizer, Scales, double );
		SO_ITK_SET_FIELD_ARRAY( optimizer, InitialPosition, double );
        
        // From SoItkRegularStepGradientDescentBaseOptimizer
        optimizer->SetMinimize( Minimize.getValue() );
        optimizer->SetMinimumStepLength( MinimumStepLength.getValue() );
        optimizer->SetMaximumStepLength( MaximumStepLength.getValue() );
        optimizer->SetRelaxationFactor( RelaxationFactor.getValue() );
        optimizer->SetNumberOfIterations( NumberOfIterations.getValue() );
        optimizer->SetGradientMagnitudeTolerance( GradientMagnitudeTolerance.getValue() );
        
        optimizer->Register();
        
        mOutput = new SoItkDataOptimizer();
        mOutput->ref();
        mOutput->setPointer( optimizer );
    }
    catch(...)
    {
        SoDebugError::post( __FILE__, "Unknown Exception" );
        return ;
    }
    
	SO_ENGINE_OUTPUT( Output, SoItkSFDataOptimizer, setValue( mOutput ) );
}
