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

/* author Sylvain Jaume, Julien Gein */

#include <xip/inventor/itk/SoItkSFDataTransform.h>
#include <xip/inventor/itk/SoItkSFDataArray.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include "SoItkTransform.h"

SO_ENGINE_ABSTRACT_SOURCE( SoItkTransform )

SoItkTransform::SoItkTransform()
{
	SO_ENGINE_CONSTRUCTOR( SoItkTransform );

	SO_ENGINE_ADD_INPUT( Parameters, (0) );
	Parameters.setNum(0);

	SO_ENGINE_ADD_OUTPUT( NumberOfParameters, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( OutputParameters, SoMFFloat );    
	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataTransform );    

    mOutput = 0;
}

SoItkTransform::~SoItkTransform()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
    }
}

void
SoItkTransform::initClass()
{
	SO_ENGINE_INIT_ABSTRACT_CLASS( SoItkTransform, SoEngine, "Engine" );	
}