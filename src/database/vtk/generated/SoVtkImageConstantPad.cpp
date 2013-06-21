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
 
 
# include "SoVtkImageConstantPad.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageConstantPad )

SoVtkImageConstantPad::SoVtkImageConstantPad()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageConstantPad);

	mObject = vtkImageConstantPad::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageConstantPad *aImageConstantPad = vtkImageConstantPad::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Constant, (0));
	Constant.setValue(aImageConstantPad->GetConstant());

	SO_ENGINE_ADD_INPUT(OutputNumberOfScalarComponents, (0));
	OutputNumberOfScalarComponents.setValue(aImageConstantPad->GetOutputNumberOfScalarComponents());

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageConstantPad->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(OutputWholeExtent, ());
	OutputWholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageConstantPad->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageConstantPad::~SoVtkImageConstantPad()
{
	// Deletion of the objects if they exist
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

void SoVtkImageConstantPad::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageConstantPad, SoEngine, "Engine" );
}

void SoVtkImageConstantPad::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
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
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageConstantPad::inputChanged(SoField * f)
{
	// Get the Constant value
	if ( f == &Constant )
		SO_VTK_SET_FIELD_VALUE( mObject, Constant);

	// Get the OutputNumberOfScalarComponents value
	if ( f == &OutputNumberOfScalarComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputNumberOfScalarComponents);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the OutputWholeExtent value
	if ( f == &OutputWholeExtent )
	{
		SbVariant *vOutputWholeExtent = (SbVariant *)OutputWholeExtent.getValues(0);
		SoInput input;
		int nb_fields = OutputWholeExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vOutputWholeExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetOutputWholeExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	mObject->Update();
}

void SoVtkImageConstantPad::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageConstantPad::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Constant value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Constant);

	// Get the OutputNumberOfScalarComponents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputNumberOfScalarComponents);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the OutputWholeExtent value
	if (addCalled == 1)
	{
		SbVariant *vOutputWholeExtent = (SbVariant *)OutputWholeExtent.getValues(0);
		SoInput input;
		int nb_fields = OutputWholeExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vOutputWholeExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetOutputWholeExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	mObject->Update();
}
