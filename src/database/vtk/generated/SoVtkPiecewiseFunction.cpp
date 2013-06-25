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
 * \author Sylvain Jaume, Francois Huguet
 */

# include "SoVtkPiecewiseFunction.h"
# include "SoVtkUtils.h"

# include "vtkExtentTranslator.h"
# include "vtkFieldData.h"
# include "vtkSource.h"
# include "vtkInformation.h"


SO_ENGINE_SOURCE( SoVtkPiecewiseFunction )

SoVtkPiecewiseFunction::SoVtkPiecewiseFunction()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkPiecewiseFunction);

	mObject = vtkPiecewiseFunction::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkPiecewiseFunction *aPiecewiseFunction = vtkPiecewiseFunction::New();

	SO_ENGINE_ADD_INPUT(ExtentTranslator, (0));

	SO_ENGINE_ADD_INPUT(FieldData, (0));

	SO_ENGINE_ADD_INPUT(Segment, ());
	Segment.setFormat("double double double double");

	SO_ENGINE_ADD_INPUT(MaximumNumberOfPieces, (0));
	MaximumNumberOfPieces.setValue(aPiecewiseFunction->GetMaximumNumberOfPieces());

	SO_ENGINE_ADD_INPUT(RequestExactExtent, (0));
	RequestExactExtent.setValue(aPiecewiseFunction->GetRequestExactExtent());

	SO_ENGINE_ADD_INPUT(UpdatePiece, (0));
	UpdatePiece.setValue(aPiecewiseFunction->GetUpdatePiece());

	SO_ENGINE_ADD_INPUT(WholeBoundingBox, ());
	WholeBoundingBox.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(UpdateExtent, ());
	UpdateExtent.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(UpdateGhostLevel, (0));
	UpdateGhostLevel.setValue(aPiecewiseFunction->GetUpdateGhostLevel());

	SO_ENGINE_ADD_INPUT(UpdateNumberOfPieces, (0));
	UpdateNumberOfPieces.setValue(aPiecewiseFunction->GetUpdateNumberOfPieces());

	SO_ENGINE_ADD_INPUT(Clamping, (0));
	Clamping.setValue(aPiecewiseFunction->GetClamping());

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(PipelineInformation, (0));

	SO_ENGINE_ADD_INPUT(Point, ());
	Point.setFormat("double double");

	aPiecewiseFunction->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkPiecewiseFunction::~SoVtkPiecewiseFunction()
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

void SoVtkPiecewiseFunction::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkPiecewiseFunction, SoEngine, "Engine" );
}

void SoVtkPiecewiseFunction::evaluate()
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


void SoVtkPiecewiseFunction::inputChanged(SoField * f)
{
	// Get the ExtentTranslator value
	if ( f == &ExtentTranslator )
		SO_VTK_SET_FIELD_DATA( mObject, ExtentTranslator, vtkExtentTranslator);

	// Get the FieldData value
	if ( f == &FieldData )
		SO_VTK_SET_FIELD_DATA( mObject, FieldData, vtkFieldData);

	// Get the Segment value
	if ( f == &Segment )
	{
		SbVariant *vSegment = (SbVariant *)Segment.getValues(0);
		SoInput input;
		int nb_fields = Segment.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSegment[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->AddSegment( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

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
	// Get the UpdateGhostLevel value
	if ( f == &UpdateGhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateGhostLevel);

	// Get the UpdateNumberOfPieces value
	if ( f == &UpdateNumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateNumberOfPieces);

	// Get the Clamping value
	if ( f == &Clamping )
		SO_VTK_SET_FIELD_VALUE( mObject, Clamping);

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
	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkSource);

	// Get the PipelineInformation value
	if ( f == &PipelineInformation )
		SO_VTK_SET_FIELD_DATA( mObject, PipelineInformation, vtkInformation);

	// Get the Point value
	if ( f == &Point )
	{
		SbVariant *vPoint = (SbVariant *)Point.getValues(0);
		SoInput input;
		int nb_fields = Point.getNum();

		double val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->AddPoint( 
				(double) val0,
				(double) val1
			);
		}
	}

	//mObject->Update();
	
}

