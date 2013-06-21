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
 
 
# include "SoVtkCellData.h"
# include "SoVtkUtils.h"

# include "vtkDataArray.h"


SO_ENGINE_SOURCE( SoVtkCellData )

SoVtkCellData::SoVtkCellData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCellData);

	mObject = vtkCellData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCellData *aCellData = vtkCellData::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CopyVectors, (0));
	CopyVectors.setValue(aCellData->GetCopyVectors());

	SO_ENGINE_ADD_INPUT(CopyScalars, (0));
	CopyScalars.setValue(aCellData->GetCopyScalars());

	SO_ENGINE_ADD_INPUT(CopyAttribute, ());
	CopyAttribute.setFormat("int int");

	SO_ENGINE_ADD_INPUT(CopyNormals, (0));
	CopyNormals.setValue(aCellData->GetCopyNormals());

	SO_ENGINE_ADD_INPUT(Component, ());
	Component.setFormat("const vtkIdType const int const double");

	SO_ENGINE_ADD_INPUT(CopyTensors, (0));
	CopyTensors.setValue(aCellData->GetCopyTensors());

	SO_ENGINE_ADD_INPUT(CopyTCoords, (0));
	CopyTCoords.setValue(aCellData->GetCopyTCoords());

	aCellData->Delete();


	SO_ENGINE_ADD_OUTPUT( oTensors, SoSFVtkObject );
	mTensors = 0;
	SO_ENGINE_ADD_OUTPUT( oScalars, SoSFVtkObject );
	mScalars = 0;
	SO_ENGINE_ADD_OUTPUT( oTCoords, SoSFVtkObject );
	mTCoords = 0;
	SO_ENGINE_ADD_OUTPUT( oNormals, SoSFVtkObject );
	mNormals = 0;
	SO_ENGINE_ADD_OUTPUT( oVectors, SoSFVtkObject );
	mVectors = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkCellData::~SoVtkCellData()
{
	// Deletion of the objects if they exist
	if ( mTensors )
	{
	
		mTensors->unref();
		mTensors = 0;
	}
	
	if ( mScalars )
	{
	
		mScalars->unref();
		mScalars = 0;
	}
	
	if ( mTCoords )
	{
	
		mTCoords->unref();
		mTCoords = 0;
	}
	
	if ( mNormals )
	{
	
		mNormals->unref();
		mNormals = 0;
	}
	
	if ( mVectors )
	{
	
		mVectors->unref();
		mVectors = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkCellData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCellData, SoEngine, "Engine" );
}

void SoVtkCellData::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mTensors )
		{
		
			mTensors->unref();
			mTensors = 0;
		}
		
		if ( mScalars )
		{
		
			mScalars->unref();
			mScalars = 0;
		}
		
		if ( mTCoords )
		{
		
			mTCoords->unref();
			mTCoords = 0;
		}
		
		if ( mNormals )
		{
		
			mNormals->unref();
			mNormals = 0;
		}
		
		if ( mVectors )
		{
		
			mVectors->unref();
			mVectors = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetTensors();
		mTensors = new SoVtkObject();
		mTensors->ref();
		mTensors->setPointer( mObject->GetTensors() );

		mObject->GetScalars();
		mScalars = new SoVtkObject();
		mScalars->ref();
		mScalars->setPointer( mObject->GetScalars() );

		mObject->GetTCoords();
		mTCoords = new SoVtkObject();
		mTCoords->ref();
		mTCoords->setPointer( mObject->GetTCoords() );

		mObject->GetNormals();
		mNormals = new SoVtkObject();
		mNormals->ref();
		mNormals->setPointer( mObject->GetNormals() );

		mObject->GetVectors();
		mVectors = new SoVtkObject();
		mVectors->ref();
		mVectors->setPointer( mObject->GetVectors() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oTensors, SoSFVtkObject, setValue( mTensors ) );
	SO_ENGINE_OUTPUT( oScalars, SoSFVtkObject, setValue( mScalars ) );
	SO_ENGINE_OUTPUT( oTCoords, SoSFVtkObject, setValue( mTCoords ) );
	SO_ENGINE_OUTPUT( oNormals, SoSFVtkObject, setValue( mNormals ) );
	SO_ENGINE_OUTPUT( oVectors, SoSFVtkObject, setValue( mVectors ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkCellData::inputChanged(SoField * f)
{
	// Get the CopyVectors value
	if ( f == &CopyVectors )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyVectors);

	// Get the CopyScalars value
	if ( f == &CopyScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyScalars);

	// Get the CopyAttribute value
	if ( f == &CopyAttribute )
	{
		SbVariant *vCopyAttribute = (SbVariant *)CopyAttribute.getValues(0);
		SoInput input;
		int nb_fields = CopyAttribute.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vCopyAttribute[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetCopyAttribute( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the CopyNormals value
	if ( f == &CopyNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyNormals);

	// Get the Component value
	if ( f == &Component )
	{
		SbVariant *vComponent = (SbVariant *)Component.getValues(0);
		SoInput input;
		int nb_fields = Component.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetComponent( 
				(const vtkIdType) val0,
				(const int) val1,
				(const double) val2
			);
		}
	}

	// Get the CopyTensors value
	if ( f == &CopyTensors )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyTensors);

	// Get the CopyTCoords value
	if ( f == &CopyTCoords )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyTCoords);

}

void SoVtkCellData::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCellData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the CopyVectors value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyVectors);

	// Get the CopyScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyScalars);

	// Get the CopyAttribute value
	if (addCalled == 1)
	{
		SbVariant *vCopyAttribute = (SbVariant *)CopyAttribute.getValues(0);
		SoInput input;
		int nb_fields = CopyAttribute.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vCopyAttribute[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetCopyAttribute( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the CopyNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyNormals);

	// Get the Component value
	if (addCalled == 1)
	{
		SbVariant *vComponent = (SbVariant *)Component.getValues(0);
		SoInput input;
		int nb_fields = Component.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetComponent( 
				(const vtkIdType) val0,
				(const int) val1,
				(const double) val2
			);
		}
	}

	// Get the CopyTensors value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyTensors);

	// Get the CopyTCoords value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyTCoords);

}
