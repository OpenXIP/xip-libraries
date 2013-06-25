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
/*
 * \brief
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */

#include "SoVtkBSPCuts.h"
#include "SoVtkUtils.h"

SO_ENGINE_SOURCE( SoVtkBSPCuts )

SoVtkBSPCuts::SoVtkBSPCuts()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBSPCuts);

	mObject = vtkBSPCuts::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBSPCuts *aBSPCuts = vtkBSPCuts::New();
	aBSPCuts->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	addCalled = 0;
}

SoVtkBSPCuts::~SoVtkBSPCuts()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
}

void SoVtkBSPCuts::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBSPCuts, SoEngine, "Engine" );
}

void SoVtkBSPCuts::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutput )
		{
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkBSPCuts::inputChanged(SoField * f)
{
}

void SoVtkBSPCuts::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBSPCuts::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
}

