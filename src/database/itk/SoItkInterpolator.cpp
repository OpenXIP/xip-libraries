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
#include "SoItkInterpolator.h"

SO_ENGINE_SOURCE( SoItkInterpolator )

SoItkInterpolator::SoItkInterpolator()
{
	SO_ENGINE_CONSTRUCTOR( SoItkInterpolator );

	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataInterpolator );
    
    mOutput = 0;
}

SoItkInterpolator::~SoItkInterpolator()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
    }
}

void
SoItkInterpolator::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkInterpolator, SoEngine, "Engine" );	
}

void
SoItkInterpolator::evaluate()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( Output, SoItkSFDataInterpolator, setValue( 0 ) );
    }
    
    try
    {
        
        
    }
    catch(...)
    {
        SoDebugError::post( __FILE__, "Unknown Exception" );
        return ;
    }
    
	SO_ENGINE_OUTPUT( Output, SoItkSFDataInterpolator, setValue( mOutput ) );
}
