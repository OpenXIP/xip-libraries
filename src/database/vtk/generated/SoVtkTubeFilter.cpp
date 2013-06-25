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

# include "SoVtkTubeFilter.h"
# include "SoVtkUtils.h"

# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkTubeFilter )

SoVtkTubeFilter::SoVtkTubeFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkTubeFilter);

	mObject = vtkTubeFilter::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkTubeFilter *aTubeFilter = vtkTubeFilter::New();
	double *x;

	SO_ENGINE_ADD_INPUT(Radius, (0));
	Radius.setValue(aTubeFilter->GetRadius());

	SO_ENGINE_ADD_INPUT(RadiusFactor, (0));
	RadiusFactor.setValue(aTubeFilter->GetRadiusFactor());

	SO_ENGINE_ADD_INPUT(OnRatio, (0));
	OnRatio.setValue(aTubeFilter->GetOnRatio());

	SO_ENGINE_ADD_INPUT(SidesShareVertices, (0));
	SidesShareVertices.setValue(aTubeFilter->GetSidesShareVertices());

	SO_ENGINE_ADD_INPUT(VaryRadius, (0));
	VaryRadius.setValue(aTubeFilter->GetVaryRadius());

	SO_ENGINE_ADD_INPUT(TextureLength, (0));
	TextureLength.setValue(aTubeFilter->GetTextureLength());

	SO_ENGINE_ADD_INPUT(NumberOfSides, (0));
	NumberOfSides.setValue(aTubeFilter->GetNumberOfSides());

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(DefaultNormal, (0,0,0));

	x= aTubeFilter->GetDefaultNormal();
	DefaultNormal.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Offset, (0));
	Offset.setValue(aTubeFilter->GetOffset());

	SO_ENGINE_ADD_INPUT(UseDefaultNormal, (0));
	UseDefaultNormal.setValue(aTubeFilter->GetUseDefaultNormal());

	SO_ENGINE_ADD_INPUT(GenerateTCoords, (0));
	GenerateTCoords.setValue(aTubeFilter->GetGenerateTCoords());

	SO_ENGINE_ADD_INPUT(Capping, (0));
	Capping.setValue(aTubeFilter->GetCapping());

	aTubeFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

}

SoVtkTubeFilter::~SoVtkTubeFilter()
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

void SoVtkTubeFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkTubeFilter, SoEngine, "Engine" );
}

void SoVtkTubeFilter::evaluate()
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
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataObject"))
			mObject->SetInput(vtkDataObject::SafeDownCast(inputPtr->getPointer()));

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


void SoVtkTubeFilter::inputChanged(SoField * f)
{
	// Get the Radius value
	if ( f == &Radius )
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

	// Get the RadiusFactor value
	if ( f == &RadiusFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, RadiusFactor);

	// Get the OnRatio value
	if ( f == &OnRatio )
		SO_VTK_SET_FIELD_VALUE( mObject, OnRatio);

	// Get the SidesShareVertices value
	if ( f == &SidesShareVertices )
		SO_VTK_SET_FIELD_VALUE( mObject, SidesShareVertices);

	// Get the VaryRadius value
	if ( f == &VaryRadius )
		SO_VTK_SET_FIELD_VALUE( mObject, VaryRadius);

	// Get the TextureLength value
	if ( f == &TextureLength )
		SO_VTK_SET_FIELD_VALUE( mObject, TextureLength);

	// Get the NumberOfSides value
	if ( f == &NumberOfSides )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfSides);

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
	// Get the DefaultNormal value
	if ( f == &DefaultNormal )
		SO_VTK_SET_FIELD_VEC3F( mObject, DefaultNormal);

	// Get the Offset value
	if ( f == &Offset )
		SO_VTK_SET_FIELD_VALUE( mObject, Offset);

	// Get the UseDefaultNormal value
	if ( f == &UseDefaultNormal )
		SO_VTK_SET_FIELD_VALUE( mObject, UseDefaultNormal);

	// Get the GenerateTCoords value
	if ( f == &GenerateTCoords )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateTCoords);

	// Get the Capping value
	if ( f == &Capping )
		SO_VTK_SET_FIELD_VALUE( mObject, Capping);

	//mObject->Update();
	
}

