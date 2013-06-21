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

#include <xip/inventor/dicom/SoXipSFDataDicom.h>
#include "SoXipDecomposeMFDicom.h"

SO_ENGINE_SOURCE( SoXipDecomposeMFDicom );

SoXipDecomposeMFDicom::SoXipDecomposeMFDicom()
{
	SO_ENGINE_CONSTRUCTOR( SoXipDecomposeMFDicom );

	SO_ENGINE_ADD_INPUT( input, (0) );
	input.setNum(0);
	SO_ENGINE_ADD_INPUT( index, (-1) );

	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataDicom );
}

SoXipDecomposeMFDicom::~SoXipDecomposeMFDicom()
{

}

void
SoXipDecomposeMFDicom::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipDecomposeMFDicom, SoEngine, "Engine" );
}

void
SoXipDecomposeMFDicom::evaluate()
{
	int id = index.getValue();
	if( id < 0 || id >= input.getNum() )
	{
		SO_ENGINE_OUTPUT( output, SoXipSFDataDicom, setValue(0) );
		return ;
	}

	SO_ENGINE_OUTPUT( output, SoXipSFDataDicom, setValue( input[id] ) );
}
