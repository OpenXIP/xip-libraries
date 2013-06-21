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
 * \file SoVtkMatrix4x4.cpp
 * \brief Implementation of the SoVtkMatrix4x4 engine
 * 
 */


#include "SoVtkMatrix4x4.h"

SO_ENGINE_SOURCE( SoVtkMatrix4x4 )

SoVtkMatrix4x4::SoVtkMatrix4x4()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkMatrix4x4);
		
	mMat = vtkMatrix4x4::New();
	mMat->Register(0);

	SO_ENGINE_ADD_INPUT(Matrix  , (1,0,0,0,
						0,1,0,0,
						0,0,1,0,
						0,0,0,1));
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );

	mOutput = 0;
}

SoVtkMatrix4x4::~SoVtkMatrix4x4()
{
    if( mOutput )
    {
		mOutput->unref();
		mOutput = 0;
    }

	if( mMat )
	{
		mMat->UnRegister(0);
		mMat->Delete();
		mMat = 0;
	}
}

void
SoVtkMatrix4x4::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkMatrix4x4, SoEngine, "Engine" );
}

void
SoVtkMatrix4x4::evaluate()
{
   
    try
    {
		if( mOutput )
		{
			mOutput->unref();
			mOutput = 0;
		}

		SbMatrix inputPtr = Matrix.getValue();


		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				mMat->SetElement(i,j,inputPtr[i][j]);
		
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mMat );

    }
	catch(...)
    {
        SoDebugError::post( __FILE__, "Unknown Exception" );
        return ;
    }
    
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}
