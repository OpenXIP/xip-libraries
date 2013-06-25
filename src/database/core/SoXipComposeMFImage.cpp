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
#include <xip/inventor/core/SoXipMFDataImage.h>
#include "SoXipComposeMFImage.h"

SO_ENGINE_SOURCE( SoXipComposeMFImage );

SoXipComposeMFImage::SoXipComposeMFImage()
{
	SO_ENGINE_CONSTRUCTOR( SoXipComposeMFImage );

	SO_ENGINE_ADD_INPUT( input0, (0) );
	SO_ENGINE_ADD_INPUT( input1, (0) );
	SO_ENGINE_ADD_INPUT( input2, (0) );
	SO_ENGINE_ADD_INPUT( input3, (0) );
	SO_ENGINE_ADD_INPUT( input4, (0) );
	SO_ENGINE_ADD_INPUT( input5, (0) );
	SO_ENGINE_ADD_INPUT( input6, (0) );
	SO_ENGINE_ADD_INPUT( input7, (0) );

	SO_ENGINE_ADD_OUTPUT( output, SoXipMFDataImage );
}

SoXipComposeMFImage::~SoXipComposeMFImage()
{

}

void
SoXipComposeMFImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipComposeMFImage, SoEngine, "Engine" );
}

void
SoXipComposeMFImage::evaluate()
{
    SoXipMFDataImage tmp;
    
    for( int i = 0; i < 8; ++ i )
    {
        char fieldName[256];
        sprintf( fieldName, "input%d", i );
        
        SoXipSFDataImage* field = (SoXipSFDataImage *) getField( fieldName );
        if( field && field->getValue() )
            tmp.set1Value( tmp.getNum(), field->getValue() );
    }
    
    SO_ENGINE_OUTPUT( output, SoXipMFDataImage, copyFrom(tmp) );
}
