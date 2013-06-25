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
/*!
 * \file SoVtkAlgorithmOutput.cpp
 *
 * \brief SoVtkAlgorithmOutput class implementation.
 *
 * \see SoVtkObject
 *
 */

#include "xip/inventor/vtk/SoVtkAlgorithmOutput.h"

XIP_DATA_SOURCE( SoVtkAlgorithmOutput );

SoVtkAlgorithmOutput::SoVtkAlgorithmOutput()
{
	XIP_DATA_CONSTRUCTOR( SoVtkAlgorithmOutput );
	this->mVtkAlgorithmOutput = 0;
}

SoVtkAlgorithmOutput::~SoVtkAlgorithmOutput()
{
	if( mVtkAlgorithmOutput )
	{
		vtkObject *tmp = static_cast<vtkObject *> (this->mVtkAlgorithmOutput);
        tmp->Delete();
		mVtkAlgorithmOutput = 0;
	}
}

void
SoVtkAlgorithmOutput::initClass()
{
	XIP_DATA_INIT_CLASS( SoVtkAlgorithmOutput, SoXipData, "SoXipData" );
}

void
SoVtkAlgorithmOutput::setPointer(vtkAlgorithmOutput* data )
{
	mVtkAlgorithmOutput = data;
}


vtkAlgorithmOutput*
SoVtkAlgorithmOutput::getPointer() const
{
	return mVtkAlgorithmOutput;
}


