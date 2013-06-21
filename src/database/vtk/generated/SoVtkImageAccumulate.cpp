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
 
 
# include "SoVtkImageAccumulate.h"
# include "SoVtkUtils.h"

# include "vtkImageStencilData.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageAccumulate )

SoVtkImageAccumulate::SoVtkImageAccumulate()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageAccumulate);

	mObject = vtkImageAccumulate::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageAccumulate *aImageAccumulate = vtkImageAccumulate::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ReverseStencil, (0));
	ReverseStencil.setValue(aImageAccumulate->GetReverseStencil());

	SO_ENGINE_ADD_INPUT(ComponentExtent, ());
	ComponentExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(Stencil, (0));

	SO_ENGINE_ADD_INPUT(ComponentSpacing, (0,0,0));

	x = aImageAccumulate->GetComponentSpacing();
	ComponentSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(ComponentOrigin, (0,0,0));

	x = aImageAccumulate->GetComponentOrigin();
	ComponentOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageAccumulate->Delete();


	SO_ENGINE_ADD_OUTPUT( oStencil, SoSFVtkObject );
	mStencil = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageAccumulate::~SoVtkImageAccumulate()
{
	// Deletion of the objects if they exist
	if ( mStencil )
	{
	
		mStencil->unref();
		mStencil = 0;
	}
	
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkImageAccumulate::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageAccumulate, SoEngine, "Engine" );
}

void SoVtkImageAccumulate::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mStencil )
		{
		
			mStencil->unref();
			mStencil = 0;
		}
		
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetStencil();
		mStencil = new SoVtkObject();
		mStencil->ref();
		mStencil->setPointer( mObject->GetStencil() );

		mObject->GetOutput()->Register(0);
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject->GetOutput() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oStencil, SoSFVtkObject, setValue( mStencil ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageAccumulate::inputChanged(SoField * f)
{
	// Get the ReverseStencil value
	if ( f == &ReverseStencil )
		SO_VTK_SET_FIELD_VALUE( mObject, ReverseStencil);

	// Get the ComponentExtent value
	if ( f == &ComponentExtent )
	{
		SbVariant *vComponentExtent = (SbVariant *)ComponentExtent.getValues(0);
		SoInput input;
		int nb_fields = ComponentExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponentExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetComponentExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	// Get the Stencil value
	if ( f == &Stencil )
		SO_VTK_SET_FIELD_DATA( mObject, Stencil, vtkImageStencilData);

	// Get the ComponentSpacing value
	if ( f == &ComponentSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, ComponentSpacing);

	// Get the ComponentOrigin value
	if ( f == &ComponentOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, ComponentOrigin);

	mObject->Update();
}

void SoVtkImageAccumulate::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageAccumulate::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ReverseStencil value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReverseStencil);

	// Get the ComponentExtent value
	if (addCalled == 1)
	{
		SbVariant *vComponentExtent = (SbVariant *)ComponentExtent.getValues(0);
		SoInput input;
		int nb_fields = ComponentExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponentExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetComponentExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	// Get the Stencil value
	
		SO_VTK_SET_FIELD_DATA( mObject, Stencil, vtkImageStencilData);

	// Get the ComponentSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, ComponentSpacing);

	// Get the ComponentOrigin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, ComponentOrigin);

	mObject->Update();
}
