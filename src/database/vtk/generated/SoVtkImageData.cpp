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
 
 
# include "SoVtkImageData.h"
# include "SoVtkUtils.h"

# include "vtkExtentTranslator.h"
# include "vtkSource.h"
# include "vtkInformation.h"
# include "vtkFieldData.h"


SO_ENGINE_SOURCE( SoVtkImageData )

SoVtkImageData::SoVtkImageData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageData);

	mObject = vtkImageData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageData *aImageData = vtkImageData::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ExtentTranslator, (0));

	SO_ENGINE_ADD_INPUT(MaximumNumberOfPieces, (0));
	MaximumNumberOfPieces.setValue(aImageData->GetMaximumNumberOfPieces());

	SO_ENGINE_ADD_INPUT(RequestExactExtent, (0));
	RequestExactExtent.setValue(aImageData->GetRequestExactExtent());

	SO_ENGINE_ADD_INPUT(UpdatePiece, (0));
	UpdatePiece.setValue(aImageData->GetUpdatePiece());

	SO_ENGINE_ADD_INPUT(WholeBoundingBox, ());
	WholeBoundingBox.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(UpdateGhostLevel, (0));
	UpdateGhostLevel.setValue(aImageData->GetUpdateGhostLevel());

	SO_ENGINE_ADD_INPUT(UpdateNumberOfPieces, (0));
	UpdateNumberOfPieces.setValue(aImageData->GetUpdateNumberOfPieces());

	SO_ENGINE_ADD_INPUT(Origin, (0,0,0));

	x = aImageData->GetOrigin();
	Origin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(Extent, ());
	Extent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(PipelineInformation, (0));

	SO_ENGINE_ADD_INPUT(FieldData, (0));

	SO_ENGINE_ADD_INPUT(ScalarComponentFromFloat, ());
	ScalarComponentFromFloat.setFormat("int int int int float");

	SO_ENGINE_ADD_INPUT(Dimensions, ());
	Dimensions.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(UpdateExtent, ());
	UpdateExtent.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(NumberOfScalarComponents, (0));
	NumberOfScalarComponents.setValue(aImageData->GetNumberOfScalarComponents());

	SO_ENGINE_ADD_INPUT(AxisUpdateExtent, ());
	AxisUpdateExtent.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(Spacing, (0,0,0));

	x = aImageData->GetSpacing();
	Spacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(ScalarComponentFromDouble, ());
	ScalarComponentFromDouble.setFormat("int int int int double");

	SO_ENGINE_ADD_INPUT(ScalarType, (0));
	ScalarType.setValue(aImageData->GetScalarType());

	aImageData->Delete();


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

SoVtkImageData::~SoVtkImageData()
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

void SoVtkImageData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageData, SoEngine, "Engine" );
}

void SoVtkImageData::evaluate()
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


void SoVtkImageData::inputChanged(SoField * f)
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

	// Get the Origin value
	if ( f == &Origin )
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkSource);

	// Get the Extent value
	if ( f == &Extent )
	{
		SbVariant *vExtent = (SbVariant *)Extent.getValues(0);
		SoInput input;
		int nb_fields = Extent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	// Get the PipelineInformation value
	if ( f == &PipelineInformation )
		SO_VTK_SET_FIELD_DATA( mObject, PipelineInformation, vtkInformation);

	// Get the FieldData value
	if ( f == &FieldData )
		SO_VTK_SET_FIELD_DATA( mObject, FieldData, vtkFieldData);

	// Get the ScalarComponentFromFloat value
	if ( f == &ScalarComponentFromFloat )
	{
		SbVariant *vScalarComponentFromFloat = (SbVariant *)ScalarComponentFromFloat.getValues(0);
		SoInput input;
		int nb_fields = ScalarComponentFromFloat.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		float val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vScalarComponentFromFloat[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetScalarComponentFromFloat( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(float) val4
			);
		}
	}

	// Get the Dimensions value
	if ( f == &Dimensions )
	{
		SbVariant *vDimensions = (SbVariant *)Dimensions.getValues(0);
		SoInput input;
		int nb_fields = Dimensions.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vDimensions[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetDimensions( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

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

	// Get the NumberOfScalarComponents value
	if ( f == &NumberOfScalarComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the AxisUpdateExtent value
	if ( f == &AxisUpdateExtent )
	{
		SbVariant *vAxisUpdateExtent = (SbVariant *)AxisUpdateExtent.getValues(0);
		SoInput input;
		int nb_fields = AxisUpdateExtent.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vAxisUpdateExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetAxisUpdateExtent( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

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

	// Get the Spacing value
	if ( f == &Spacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, Spacing);

	// Get the ScalarComponentFromDouble value
	if ( f == &ScalarComponentFromDouble )
	{
		SbVariant *vScalarComponentFromDouble = (SbVariant *)ScalarComponentFromDouble.getValues(0);
		SoInput input;
		int nb_fields = ScalarComponentFromDouble.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		double val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vScalarComponentFromDouble[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetScalarComponentFromDouble( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(double) val4
			);
		}
	}

	// Get the ScalarType value
	if ( f == &ScalarType )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarType);

	mObject->Update();
}

void SoVtkImageData::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the ExtentTranslator value
	
		SO_VTK_SET_FIELD_DATA( mObject, ExtentTranslator, vtkExtentTranslator);

	// Get the MaximumNumberOfPieces value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumNumberOfPieces);

	// Get the RequestExactExtent value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RequestExactExtent);

	// Get the UpdatePiece value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UpdatePiece);

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

	// Get the Origin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the Source value
	
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkSource);

	// Get the Extent value
	if (addCalled == 1)
	{
		SbVariant *vExtent = (SbVariant *)Extent.getValues(0);
		SoInput input;
		int nb_fields = Extent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	// Get the PipelineInformation value
	
		SO_VTK_SET_FIELD_DATA( mObject, PipelineInformation, vtkInformation);

	// Get the FieldData value
	
		SO_VTK_SET_FIELD_DATA( mObject, FieldData, vtkFieldData);

	// Get the ScalarComponentFromFloat value
	if (addCalled == 1)
	{
		SbVariant *vScalarComponentFromFloat = (SbVariant *)ScalarComponentFromFloat.getValues(0);
		SoInput input;
		int nb_fields = ScalarComponentFromFloat.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		float val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vScalarComponentFromFloat[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetScalarComponentFromFloat( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(float) val4
			);
		}
	}

	// Get the Dimensions value
	if (addCalled == 1)
	{
		SbVariant *vDimensions = (SbVariant *)Dimensions.getValues(0);
		SoInput input;
		int nb_fields = Dimensions.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vDimensions[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetDimensions( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

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

	// Get the NumberOfScalarComponents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the AxisUpdateExtent value
	if (addCalled == 1)
	{
		SbVariant *vAxisUpdateExtent = (SbVariant *)AxisUpdateExtent.getValues(0);
		SoInput input;
		int nb_fields = AxisUpdateExtent.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vAxisUpdateExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetAxisUpdateExtent( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

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

	// Get the Spacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Spacing);

	// Get the ScalarComponentFromDouble value
	if (addCalled == 1)
	{
		SbVariant *vScalarComponentFromDouble = (SbVariant *)ScalarComponentFromDouble.getValues(0);
		SoInput input;
		int nb_fields = ScalarComponentFromDouble.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		double val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vScalarComponentFromDouble[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetScalarComponentFromDouble( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(double) val4
			);
		}
	}

	// Get the ScalarType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarType);

	mObject->Update();
}
