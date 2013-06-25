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

# include "SoVtkVolumeTextureMapper2D.h"
# include "SoVtkUtils.h"

# include "vtkPlanes.h"
# include "vtkDataSet.h"
# include "vtkEncodedGradientEstimator.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkVolumeTextureMapper2D )

SoVtkVolumeTextureMapper2D::SoVtkVolumeTextureMapper2D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkVolumeTextureMapper2D);

	mObject = vtkVolumeTextureMapper2D::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkVolumeTextureMapper2D *aVolumeTextureMapper2D = vtkVolumeTextureMapper2D::New();
	int y[2];

	SO_ENGINE_ADD_INPUT(Cropping, (0));
	Cropping.setValue(aVolumeTextureMapper2D->GetCropping());

	SO_ENGINE_ADD_INPUT(CroppingRegionPlanes, (0));

	SO_ENGINE_ADD_INPUT(MaximumStorageSize, (0));
	MaximumStorageSize.setValue(aVolumeTextureMapper2D->GetMaximumStorageSize());

	SO_ENGINE_ADD_INPUT(ClippingPlanes, (0));

	SO_ENGINE_ADD_INPUT(MaximumNumberOfPlanes, (0));
	MaximumNumberOfPlanes.setValue(aVolumeTextureMapper2D->GetMaximumNumberOfPlanes());

	SO_ENGINE_ADD_INPUT(TargetTextureSize, (0,0));

	aVolumeTextureMapper2D->GetTargetTextureSize(y);
	TargetTextureSize.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(CroppingRegionFlags, (0));
	CroppingRegionFlags.setValue(aVolumeTextureMapper2D->GetCroppingRegionFlags());

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(BlendMode, (0));
	BlendMode.setValue(aVolumeTextureMapper2D->GetBlendMode());

	SO_ENGINE_ADD_INPUT(GradientEstimator, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aVolumeTextureMapper2D->Delete();


	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkVolumeTextureMapper2D::~SoVtkVolumeTextureMapper2D()
{
	// Deletion of the objects if they exist
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
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

void SoVtkVolumeTextureMapper2D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkVolumeTextureMapper2D, SoEngine, "Engine" );
}

void SoVtkVolumeTextureMapper2D::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataSet"))
			mObject->SetInput(vtkDataSet::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

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
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkVolumeTextureMapper2D::inputChanged(SoField * f)
{
	// Get the Cropping value
	if ( f == &Cropping )
		SO_VTK_SET_FIELD_VALUE( mObject, Cropping);

	// Get the CroppingRegionPlanes value
	if ( f == &CroppingRegionPlanes )
	{
		if ( CroppingRegionPlanes.getNum() >= 6)
		{
			SO_VTK_SET_FIELD_MFDOUBLE( mObject, CroppingRegionPlanes);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the MaximumStorageSize value
	if ( f == &MaximumStorageSize )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumStorageSize);

	// Get the ClippingPlanes value
	if ( f == &ClippingPlanes )
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlanes);

	// Get the MaximumNumberOfPlanes value
	if ( f == &MaximumNumberOfPlanes )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumNumberOfPlanes);

	// Get the TargetTextureSize value
	if ( f == &TargetTextureSize )
		SO_VTK_SET_FIELD_VEC2F( mObject, TargetTextureSize);

	// Get the CroppingRegionFlags value
	if ( f == &CroppingRegionFlags )
		SO_VTK_SET_FIELD_VALUE( mObject, CroppingRegionFlags);

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
	// Get the BlendMode value
	if ( f == &BlendMode )
		SO_VTK_SET_FIELD_VALUE( mObject, BlendMode);

	// Get the GradientEstimator value
	if ( f == &GradientEstimator )
		SO_VTK_SET_FIELD_DATA( mObject, GradientEstimator, vtkEncodedGradientEstimator);

	//mObject->Update();
	
}

