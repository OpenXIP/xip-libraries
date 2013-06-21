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
* \author Sylvain Jaume (Siemens Corporate Research), Francois Huguet
*/

# include "SoVtkPolyData.h"
# include "SoVtkUtils.h"

# include "vtkExtentTranslator.h"
# include "vtkCellArray.h"
# include "vtkSource.h"
# include "vtkInformation.h"
# include "vtkFieldData.h"
# include "vtkPoints.h"


SO_ENGINE_SOURCE( SoVtkPolyData )

SoVtkPolyData::SoVtkPolyData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkPolyData);

	mObject = vtkPolyData::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkPolyData *aPolyData = vtkPolyData::New();

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(ExtentTranslator, (0));

	SO_ENGINE_ADD_INPUT(MaximumNumberOfPieces, (0));
	MaximumNumberOfPieces.setValue(aPolyData->GetMaximumNumberOfPieces());

	SO_ENGINE_ADD_INPUT(RequestExactExtent, (0));
	RequestExactExtent.setValue(aPolyData->GetRequestExactExtent());

	SO_ENGINE_ADD_INPUT(UpdatePiece, (0));
	UpdatePiece.setValue(aPolyData->GetUpdatePiece());

	SO_ENGINE_ADD_INPUT(WholeBoundingBox, ());
	WholeBoundingBox.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(UpdateGhostLevel, (0));
	UpdateGhostLevel.setValue(aPolyData->GetUpdateGhostLevel());

	SO_ENGINE_ADD_INPUT(UpdateNumberOfPieces, (0));
	UpdateNumberOfPieces.setValue(aPolyData->GetUpdateNumberOfPieces());

	SO_ENGINE_ADD_INPUT(Lines, (0));

	SO_ENGINE_ADD_INPUT(Strips, (0));

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(PipelineInformation, (0));

	SO_ENGINE_ADD_INPUT(FieldData, (0));

	SO_ENGINE_ADD_INPUT(Polys, (0));

	SO_ENGINE_ADD_INPUT(UpdateExtent, ());
	UpdateExtent.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(Points, (0));

	SO_ENGINE_ADD_INPUT(Verts, (0));

	aPolyData->Delete();

	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;
}

SoVtkPolyData::~SoVtkPolyData()
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

void SoVtkPolyData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkPolyData, SoEngine, "Engine" );
}

void SoVtkPolyData::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkPolyData"))
			mObject->SetPoints((vtkPolyData::SafeDownCast(inputPtr->getPointer()))->GetPoints());

		if (inputPtr && inputPtr->getPointer()->IsA("vtkPolyData"))
			mObject->SetPolys((vtkPolyData::SafeDownCast(inputPtr->getPointer()))->GetLines());

		// Get the input type(s)
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


void SoVtkPolyData::inputChanged(SoField * f)
{
	// Get the ExtentTranslator value
	if ( f == &ExtentTranslator )
		SO_VTK_SET_FIELD_DATA( mObject, ExtentTranslator, vtkExtentTranslator);

	// Get the MaximumNumberOfPieces value
	if ( f == &MaximumNumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumNumberOfPieces);

	// Get the RequestExactExtent value
	if ( f == &RequestExactExtent )
		SO_VTK_SET_FIELD_VALUE( mObject, RequestExactExtent);

	// Get the UpdatePiece value
	if ( f == &UpdatePiece )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdatePiece);

	// Get the WholeBoundingBox value
	if ( f == &WholeBoundingBox )
	{
		SbVariant vWholeBoundingBox = (SbVariant)WholeBoundingBox.getValue();
		SoInput input;
		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
	
		input.setBuffer((void *)vWholeBoundingBox.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		input.read(val5);
		mObject->SetWholeBoundingBox( 
			(double) val0,
			(double) val1,
			(double) val2,
			(double) val3,
			(double) val4,
			(double) val5
		);
	}
	// Get the UpdateGhostLevel value
	if ( f == &UpdateGhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateGhostLevel);

	// Get the UpdateNumberOfPieces value
	if ( f == &UpdateNumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateNumberOfPieces);

	// Get the Lines value
	if ( f == &Lines )
		SO_VTK_SET_FIELD_DATA( mObject, Lines, vtkCellArray);

	// Get the Strips value
	if ( f == &Strips )
		SO_VTK_SET_FIELD_DATA( mObject, Strips, vtkCellArray);

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkSource);

	// Get the PipelineInformation value
	if ( f == &PipelineInformation )
		SO_VTK_SET_FIELD_DATA( mObject, PipelineInformation, vtkInformation);

	// Get the FieldData value
	if ( f == &FieldData )
		SO_VTK_SET_FIELD_DATA( mObject, FieldData, vtkFieldData);

	//// Get the Polys value
	//if ( f == &Polys )
	//	SO_VTK_SET_FIELD_DATA( mObject, Polys, vtkCellArray);

	// Get the UpdateExtent value
	if ( f == &UpdateExtent )
	{
		SbVariant vUpdateExtent = (SbVariant)UpdateExtent.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
	
		input.setBuffer((void *)vUpdateExtent.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		mObject->SetUpdateExtent( 
			(int) val0,
			(int) val1,
			(int) val2
		);
	}

	// Get the WholeExtent value
	if ( f == &WholeExtent )
	{
		SbVariant vWholeExtent = (SbVariant)WholeExtent.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
	
		input.setBuffer((void *)vWholeExtent.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		input.read(val5);
		mObject->SetWholeExtent( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			(int) val4,
			(int) val5
		);
	}
	//// Get the Points value
	//if ( f == &Points )
	//	SO_VTK_SET_FIELD_DATA( mObject, Points, vtkPoints);

	// Get the Verts value
	if ( f == &Verts )
		SO_VTK_SET_FIELD_DATA( mObject, Verts, vtkCellArray);

	//mObject->Update();
	
}


