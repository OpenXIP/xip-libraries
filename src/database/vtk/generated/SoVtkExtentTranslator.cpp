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
 
 
# include "SoVtkExtentTranslator.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkExtentTranslator )

SoVtkExtentTranslator::SoVtkExtentTranslator()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExtentTranslator);

	mObject = vtkExtentTranslator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkExtentTranslator *aExtentTranslator = vtkExtentTranslator::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(GhostLevel, (0));
	GhostLevel.setValue(aExtentTranslator->GetGhostLevel());

	SO_ENGINE_ADD_INPUT(NumberOfPieces, (0));
	NumberOfPieces.setValue(aExtentTranslator->GetNumberOfPieces());

	SO_ENGINE_ADD_INPUT(Piece, (0));
	Piece.setValue(aExtentTranslator->GetPiece());

	SO_ENGINE_ADD_INPUT(Extent, (0));

	SO_ENGINE_ADD_INPUT(WholeExtent, (0));

	aExtentTranslator->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkExtentTranslator::~SoVtkExtentTranslator()
{
	// Deletion of the objects if they exist
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkExtentTranslator::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExtentTranslator, SoEngine, "Engine" );
}

void SoVtkExtentTranslator::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
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


void SoVtkExtentTranslator::inputChanged(SoField * f)
{
	// Get the GhostLevel value
	if ( f == &GhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the NumberOfPieces value
	if ( f == &NumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfPieces);

	// Get the Piece value
	if ( f == &Piece )
		SO_VTK_SET_FIELD_VALUE( mObject, Piece);

	// Get the Extent value
	if ( f == &Extent )
	{
		if ( Extent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, Extent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the WholeExtent value
	if ( f == &WholeExtent )
	{
		if ( WholeExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, WholeExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

}

void SoVtkExtentTranslator::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkExtentTranslator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the GhostLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the NumberOfPieces value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfPieces);

	// Get the Piece value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Piece);

	// Get the Extent value
	
	{
		if ( Extent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, Extent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the WholeExtent value
	
	{
		if ( WholeExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, WholeExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

}
