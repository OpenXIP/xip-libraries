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
 
 
# include "SoVtkDataObject.h"
# include "SoVtkUtils.h"

# include "vtkFieldData.h"
# include "vtkExtentTranslator.h"
# include "vtkSource.h"
# include "vtkInformation.h"


SO_ENGINE_SOURCE( SoVtkDataObject )

SoVtkDataObject::SoVtkDataObject()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDataObject);

	mObject = vtkDataObject::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDataObject *aDataObject = vtkDataObject::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(FieldData, (0));

	SO_ENGINE_ADD_INPUT(ExtentTranslator, (0));

	SO_ENGINE_ADD_INPUT(MaximumNumberOfPieces, (0));
	MaximumNumberOfPieces.setValue(aDataObject->GetMaximumNumberOfPieces());

	SO_ENGINE_ADD_INPUT(RequestExactExtent, (0));
	RequestExactExtent.setValue(aDataObject->GetRequestExactExtent());

	SO_ENGINE_ADD_INPUT(UpdatePiece, (0));
	UpdatePiece.setValue(aDataObject->GetUpdatePiece());

	SO_ENGINE_ADD_INPUT(UpdateExtent, ());
	UpdateExtent.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(WholeBoundingBox, ());
	WholeBoundingBox.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(UpdateGhostLevel, (0));
	UpdateGhostLevel.setValue(aDataObject->GetUpdateGhostLevel());

	SO_ENGINE_ADD_INPUT(UpdateNumberOfPieces, (0));
	UpdateNumberOfPieces.setValue(aDataObject->GetUpdateNumberOfPieces());

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(PipelineInformation, (0));

	aDataObject->Delete();

	SO_ENGINE_DEFINE_ENUM_VALUE( FieldAssociations, FIELD_ASSOCIATION_POINTS );
	SO_ENGINE_DEFINE_ENUM_VALUE( FieldAssociations, FIELD_ASSOCIATION_NONE );
	SO_ENGINE_DEFINE_ENUM_VALUE( FieldAssociations, FIELD_ASSOCIATION_CELLS );
	SO_ENGINE_DEFINE_ENUM_VALUE( FieldAssociations, NUMBER_OF_ASSOCIATIONS );
	SO_ENGINE_DEFINE_ENUM_VALUE( FieldAssociations, FIELD_ASSOCIATION_POINTS_THEN_CELLS );
	SO_ENGINE_SET_SF_ENUM_TYPE( FieldAssociationsEnum, FieldAssociations );
	SO_ENGINE_DEFINE_ENUM_VALUE( FieldOperations, FIELD_OPERATION_REMOVED );
	SO_ENGINE_DEFINE_ENUM_VALUE( FieldOperations, FIELD_OPERATION_MODIFIED );
	SO_ENGINE_DEFINE_ENUM_VALUE( FieldOperations, FIELD_OPERATION_REINTERPOLATED );
	SO_ENGINE_DEFINE_ENUM_VALUE( FieldOperations, FIELD_OPERATION_PRESERVED );
	SO_ENGINE_SET_SF_ENUM_TYPE( FieldOperationsEnum, FieldOperations );

	SO_ENGINE_ADD_OUTPUT( oFieldData, SoSFVtkObject );
	mFieldData = 0;
	SO_ENGINE_ADD_OUTPUT( oExtentTranslator, SoSFVtkObject );
	mExtentTranslator = 0;
	SO_ENGINE_ADD_OUTPUT( oSource, SoSFVtkObject );
	mSource = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkDataObject::~SoVtkDataObject()
{
	// Deletion of the objects if they exist
	if ( mFieldData )
	{
	
		mFieldData->unref();
		mFieldData = 0;
	}
	
	if ( mExtentTranslator )
	{
	
		mExtentTranslator->unref();
		mExtentTranslator = 0;
	}
	
	if ( mSource )
	{
	
		mSource->unref();
		mSource = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkDataObject::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDataObject, SoEngine, "Engine" );
}

void SoVtkDataObject::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mFieldData )
		{
		
			mFieldData->unref();
			mFieldData = 0;
		}
		
		if ( mExtentTranslator )
		{
		
			mExtentTranslator->unref();
			mExtentTranslator = 0;
		}
		
		if ( mSource )
		{
		
			mSource->unref();
			mSource = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetFieldData();
		mFieldData = new SoVtkObject();
		mFieldData->ref();
		mFieldData->setPointer( mObject->GetFieldData() );

		mObject->GetExtentTranslator();
		mExtentTranslator = new SoVtkObject();
		mExtentTranslator->ref();
		mExtentTranslator->setPointer( mObject->GetExtentTranslator() );

		mObject->GetSource();
		mSource = new SoVtkObject();
		mSource->ref();
		mSource->setPointer( mObject->GetSource() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oFieldData, SoSFVtkObject, setValue( mFieldData ) );
	SO_ENGINE_OUTPUT( oExtentTranslator, SoSFVtkObject, setValue( mExtentTranslator ) );
	SO_ENGINE_OUTPUT( oSource, SoSFVtkObject, setValue( mSource ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkDataObject::inputChanged(SoField * f)
{
	// Get the FieldData value
	if ( f == &FieldData )
		SO_VTK_SET_FIELD_DATA( mObject, FieldData, vtkFieldData);

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

	// Get the UpdateExtent value
	if ( f == &UpdateExtent )
	{
		SbVariant *vUpdateExtent = (SbVariant *)UpdateExtent.getValues(0);
		SoInput input;
		int nb_fields = UpdateExtent.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vUpdateExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetUpdateExtent( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

	// Get the WholeBoundingBox value
	if ( f == &WholeBoundingBox )
	{
		SbVariant *vWholeBoundingBox = (SbVariant *)WholeBoundingBox.getValues(0);
		SoInput input;
		int nb_fields = WholeBoundingBox.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vWholeBoundingBox[i].getField().getString(),256);
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
	}

	// Get the UpdateGhostLevel value
	if ( f == &UpdateGhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateGhostLevel);

	// Get the UpdateNumberOfPieces value
	if ( f == &UpdateNumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateNumberOfPieces);

	// Get the WholeExtent value
	if ( f == &WholeExtent )
	{
		SbVariant *vWholeExtent = (SbVariant *)WholeExtent.getValues(0);
		SoInput input;
		int nb_fields = WholeExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vWholeExtent[i].getField().getString(),256);
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
	}

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkSource);

	// Get the PipelineInformation value
	if ( f == &PipelineInformation )
		SO_VTK_SET_FIELD_DATA( mObject, PipelineInformation, vtkInformation);

	mObject->Update();
}

void SoVtkDataObject::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDataObject::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the FieldData value
	
		SO_VTK_SET_FIELD_DATA( mObject, FieldData, vtkFieldData);

	// Get the ExtentTranslator value
	
		SO_VTK_SET_FIELD_DATA( mObject, ExtentTranslator, vtkExtentTranslator);

	// Get the MaximumNumberOfPieces value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumNumberOfPieces);

	// Get the RequestExactExtent value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RequestExactExtent);

	// Get the UpdatePiece value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UpdatePiece);

	// Get the UpdateExtent value
	if (addCalled == 1)
	{
		SbVariant *vUpdateExtent = (SbVariant *)UpdateExtent.getValues(0);
		SoInput input;
		int nb_fields = UpdateExtent.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vUpdateExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetUpdateExtent( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

	// Get the WholeBoundingBox value
	if (addCalled == 1)
	{
		SbVariant *vWholeBoundingBox = (SbVariant *)WholeBoundingBox.getValues(0);
		SoInput input;
		int nb_fields = WholeBoundingBox.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vWholeBoundingBox[i].getField().getString(),256);
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
	}

	// Get the UpdateGhostLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateGhostLevel);

	// Get the UpdateNumberOfPieces value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateNumberOfPieces);

	// Get the WholeExtent value
	if (addCalled == 1)
	{
		SbVariant *vWholeExtent = (SbVariant *)WholeExtent.getValues(0);
		SoInput input;
		int nb_fields = WholeExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vWholeExtent[i].getField().getString(),256);
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
	}

	// Get the Source value
	
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkSource);

	// Get the PipelineInformation value
	
		SO_VTK_SET_FIELD_DATA( mObject, PipelineInformation, vtkInformation);

	mObject->Update();
}
