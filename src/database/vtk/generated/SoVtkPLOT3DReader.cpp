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

# include "SoVtkPLOT3DReader.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkStructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkPLOT3DReader )

SoVtkPLOT3DReader::SoVtkPLOT3DReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkPLOT3DReader);

	mObject = vtkPLOT3DReader::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkPLOT3DReader *aPLOT3DReader = vtkPLOT3DReader::New();

	SO_ENGINE_ADD_INPUT(HasByteCount, (0));
	HasByteCount.setValue(aPLOT3DReader->GetHasByteCount());

	SO_ENGINE_ADD_INPUT(ByteOrder, (0));
	ByteOrder.setValue(aPLOT3DReader->GetByteOrder());

	SO_ENGINE_ADD_INPUT(QFileName, (""));

	SO_ENGINE_ADD_INPUT(Uvinf, (0));
	Uvinf.setValue(aPLOT3DReader->GetUvinf());

	SO_ENGINE_ADD_INPUT(Function, ());
	Function.setFormat("int");

	SO_ENGINE_ADD_INPUT(ScalarFunctionNumber, (0));
	ScalarFunctionNumber.setValue(aPLOT3DReader->GetScalarFunctionNumber());

	SO_ENGINE_ADD_INPUT(DoNotReduceNumberOfOutputs, (0));
	DoNotReduceNumberOfOutputs.setValue(aPLOT3DReader->GetDoNotReduceNumberOfOutputs());

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Vvinf, (0));
	Vvinf.setValue(aPLOT3DReader->GetVvinf());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(BinaryFile, (0));
	BinaryFile.setValue(aPLOT3DReader->GetBinaryFile());

	SO_ENGINE_ADD_INPUT(IBlanking, (0));
	IBlanking.setValue(aPLOT3DReader->GetIBlanking());

	SO_ENGINE_ADD_INPUT(TwoDimensionalGeometry, (0));
	TwoDimensionalGeometry.setValue(aPLOT3DReader->GetTwoDimensionalGeometry());

	SO_ENGINE_ADD_INPUT(Wvinf, (0));
	Wvinf.setValue(aPLOT3DReader->GetWvinf());

	SO_ENGINE_ADD_INPUT(NumberOfInputConnections, ());
	NumberOfInputConnections.setFormat("int int");

	SO_ENGINE_ADD_INPUT(Gamma, (0));
	Gamma.setValue(aPLOT3DReader->GetGamma());

	SO_ENGINE_ADD_INPUT(VectorFunctionNumber, (0));
	VectorFunctionNumber.setValue(aPLOT3DReader->GetVectorFunctionNumber());

	SO_ENGINE_ADD_INPUT(ForceRead, (0));
	ForceRead.setValue(aPLOT3DReader->GetForceRead());

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(R, (0));
	R.setValue(aPLOT3DReader->GetR());

	SO_ENGINE_ADD_INPUT(MultiGrid, (0));
	MultiGrid.setValue(aPLOT3DReader->GetMultiGrid());

	SO_ENGINE_ADD_INPUT(XYZFileName, (""));

	aPLOT3DReader->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

}

SoVtkPLOT3DReader::~SoVtkPLOT3DReader()
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

void SoVtkPLOT3DReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkPLOT3DReader, SoEngine, "Engine" );
}

void SoVtkPLOT3DReader::evaluate()
{
	try
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
		
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

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


void SoVtkPLOT3DReader::inputChanged(SoField * f)
{
	// Get the HasByteCount value
	if ( f == &HasByteCount )
		SO_VTK_SET_FIELD_VALUE( mObject, HasByteCount);

	// Get the ByteOrder value
	if ( f == &ByteOrder )
		SO_VTK_SET_FIELD_VALUE( mObject, ByteOrder);

	// Get the QFileName value
	if ( f == &QFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, QFileName);

	// Get the Uvinf value
	if ( f == &Uvinf )
		SO_VTK_SET_FIELD_VALUE( mObject, Uvinf);

	// Get the Function value
	if ( f == &Function )
	{
		SbVariant *vFunction = (SbVariant *)Function.getValues(0);
		SoInput input;
		int nb_fields = Function.getNum();

		int val0;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vFunction[i].getField().getString(),256);
			input.read(val0);
			mObject->AddFunction( 
				(int) val0
			);
		}
	}

	// Get the ScalarFunctionNumber value
	if ( f == &ScalarFunctionNumber )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarFunctionNumber);

	// Get the DoNotReduceNumberOfOutputs value
	if ( f == &DoNotReduceNumberOfOutputs )
		SO_VTK_SET_FIELD_VALUE( mObject, DoNotReduceNumberOfOutputs);

	// Get the InputArrayToProcess value
	if ( f == &InputArrayToProcess )
	{
		SbVariant vInputArrayToProcess = (SbVariant)InputArrayToProcess.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		SbString val4;
	
		input.setBuffer((void *)vInputArrayToProcess.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		mObject->SetInputArrayToProcess( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			val4.getString()
		);
	}
	// Get the Vvinf value
	if ( f == &Vvinf )
		SO_VTK_SET_FIELD_VALUE( mObject, Vvinf);

	// Get the BinaryFile value
	if ( f == &BinaryFile )
		SO_VTK_SET_FIELD_VALUE( mObject, BinaryFile);

	// Get the IBlanking value
	if ( f == &IBlanking )
		SO_VTK_SET_FIELD_VALUE( mObject, IBlanking);

	// Get the TwoDimensionalGeometry value
	if ( f == &TwoDimensionalGeometry )
		SO_VTK_SET_FIELD_VALUE( mObject, TwoDimensionalGeometry);

	// Get the Wvinf value
	if ( f == &Wvinf )
		SO_VTK_SET_FIELD_VALUE( mObject, Wvinf);

	// Get the NumberOfInputConnections value
	if ( f == &NumberOfInputConnections )
	{
		SbVariant vNumberOfInputConnections = (SbVariant)NumberOfInputConnections.getValue();
		SoInput input;
		int val0;
		int val1;
	
		input.setBuffer((void *)vNumberOfInputConnections.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		mObject->SetNumberOfInputConnections( 
			(int) val0,
			(int) val1
		);
	}
	// Get the Gamma value
	if ( f == &Gamma )
		SO_VTK_SET_FIELD_VALUE( mObject, Gamma);

	// Get the VectorFunctionNumber value
	if ( f == &VectorFunctionNumber )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorFunctionNumber);

	// Get the ForceRead value
	if ( f == &ForceRead )
		SO_VTK_SET_FIELD_VALUE( mObject, ForceRead);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the R value
	if ( f == &R )
		SO_VTK_SET_FIELD_VALUE( mObject, R);

	// Get the MultiGrid value
	if ( f == &MultiGrid )
		SO_VTK_SET_FIELD_VALUE( mObject, MultiGrid);

	// Get the XYZFileName value
	if ( f == &XYZFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, XYZFileName);

	//mObject->Update();
	
}

