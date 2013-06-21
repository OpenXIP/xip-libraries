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
 
#include "SoVtkBranchExtentTranslator.h"
#include "SoVtkUtils.h"

#include "vtkImageData.h"

SO_ENGINE_SOURCE( SoVtkBranchExtentTranslator )

SoVtkBranchExtentTranslator::SoVtkBranchExtentTranslator()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBranchExtentTranslator);

	mObject = vtkBranchExtentTranslator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBranchExtentTranslator *aBranchExtentTranslator =
				 vtkBranchExtentTranslator::New();

	SO_ENGINE_ADD_INPUT(GhostLevel, (0));
	GhostLevel.setValue(aBranchExtentTranslator->GetGhostLevel());

	SO_ENGINE_ADD_INPUT(AssignedPiece, (0));
	AssignedPiece.setValue(aBranchExtentTranslator->GetAssignedPiece());

	SO_ENGINE_ADD_INPUT(OriginalSource, (0));

	SO_ENGINE_ADD_INPUT(NumberOfPieces, (0));
	NumberOfPieces.setValue(aBranchExtentTranslator->GetNumberOfPieces());

	SO_ENGINE_ADD_INPUT(Piece, (0));
	Piece.setValue(aBranchExtentTranslator->GetPiece());

	SO_ENGINE_ADD_INPUT(WholeExtent, (0));

	SO_ENGINE_ADD_INPUT(AssignedNumberOfPieces, (0));
	AssignedNumberOfPieces.setValue(aBranchExtentTranslator->
									GetAssignedNumberOfPieces());

	SO_ENGINE_ADD_INPUT(Extent, (0));
	aBranchExtentTranslator->Delete();

	SO_ENGINE_ADD_OUTPUT( oOriginalSource, SoSFVtkObject );
	mOriginalSource = 0;

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	addCalled = 0;
}

SoVtkBranchExtentTranslator::~SoVtkBranchExtentTranslator()
{
	// Deletion of the objects if they exist
	if ( mOriginalSource )
	{
	
		mOriginalSource->unref();
		mOriginalSource = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkBranchExtentTranslator::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBranchExtentTranslator, SoEngine, "Engine" );
}

void SoVtkBranchExtentTranslator::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mOriginalSource )
		{
		
			mOriginalSource->unref();
			mOriginalSource = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetOriginalSource();
		mOriginalSource = new SoVtkObject();
		mOriginalSource->ref();
		mOriginalSource->setPointer( mObject->GetOriginalSource() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oOriginalSource, SoSFVtkObject, setValue( mOriginalSource ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkBranchExtentTranslator::inputChanged(SoField * f)
{
	// Get the GhostLevel value
	if ( f == &GhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the AssignedPiece value
	if ( f == &AssignedPiece )
		SO_VTK_SET_FIELD_VALUE( mObject, AssignedPiece);

	// Get the OriginalSource value
	if ( f == &OriginalSource )
		SO_VTK_SET_FIELD_DATA( mObject, OriginalSource, vtkImageData);

	// Get the NumberOfPieces value
	if ( f == &NumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfPieces);

	// Get the Piece value
	if ( f == &Piece )
		SO_VTK_SET_FIELD_VALUE( mObject, Piece);

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

	// Get the AssignedNumberOfPieces value
	if ( f == &AssignedNumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, AssignedNumberOfPieces);

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

}

void SoVtkBranchExtentTranslator::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBranchExtentTranslator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the GhostLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the AssignedPiece value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AssignedPiece);

	// Get the OriginalSource value
	
		SO_VTK_SET_FIELD_DATA( mObject, OriginalSource, vtkImageData);

	// Get the NumberOfPieces value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfPieces);

	// Get the Piece value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Piece);

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

	// Get the AssignedNumberOfPieces value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AssignedNumberOfPieces);

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

}

