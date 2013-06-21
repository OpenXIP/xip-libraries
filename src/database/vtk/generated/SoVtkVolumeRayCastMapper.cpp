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

# include "SoVtkVolumeRayCastMapper.h"
# include "SoVtkUtils.h"

# include "vtkPlanes.h"
# include "vtkDataSet.h"
# include "vtkAlgorithmOutput.h"
# include "vtkVolumeRayCastFunction.h"
# include "vtkEncodedGradientEstimator.h"


SO_ENGINE_SOURCE( SoVtkVolumeRayCastMapper )

SoVtkVolumeRayCastMapper::SoVtkVolumeRayCastMapper()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkVolumeRayCastMapper);

	mObject = vtkVolumeRayCastMapper::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkVolumeRayCastMapper *aVolumeRayCastMapper = vtkVolumeRayCastMapper::New();

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aVolumeRayCastMapper->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(AutoAdjustSampleDistances, (0));
	AutoAdjustSampleDistances.setValue(aVolumeRayCastMapper->GetAutoAdjustSampleDistances());

	SO_ENGINE_ADD_INPUT(ClippingPlanes, (0));

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(SampleDistance, (0));
	SampleDistance.setValue(aVolumeRayCastMapper->GetSampleDistance());

	SO_ENGINE_ADD_INPUT(MinimumImageSampleDistance, (0));
	MinimumImageSampleDistance.setValue(aVolumeRayCastMapper->GetMinimumImageSampleDistance());

	SO_ENGINE_ADD_INPUT(Cropping, (0));
	Cropping.setValue(aVolumeRayCastMapper->GetCropping());

	SO_ENGINE_ADD_INPUT(IntermixIntersectingGeometry, (0));
	IntermixIntersectingGeometry.setValue(aVolumeRayCastMapper->GetIntermixIntersectingGeometry());

	SO_ENGINE_ADD_INPUT(CroppingRegionPlanes, (0));

	SO_ENGINE_ADD_INPUT(ImageSampleDistance, (0));
	ImageSampleDistance.setValue(aVolumeRayCastMapper->GetImageSampleDistance());

	SO_ENGINE_ADD_INPUT(CroppingRegionFlags, (0));
	CroppingRegionFlags.setValue(aVolumeRayCastMapper->GetCroppingRegionFlags());

	SO_ENGINE_ADD_INPUT(BlendMode, (0));
	BlendMode.setValue(aVolumeRayCastMapper->GetBlendMode());

	SO_ENGINE_ADD_INPUT(MaximumImageSampleDistance, (0));
	MaximumImageSampleDistance.setValue(aVolumeRayCastMapper->GetMaximumImageSampleDistance());

	SO_ENGINE_ADD_INPUT(VolumeRayCastFunction, (0));

	SO_ENGINE_ADD_INPUT(GradientEstimator, (0));

	aVolumeRayCastMapper->Delete();


	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkVolumeRayCastMapper::~SoVtkVolumeRayCastMapper()
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

void SoVtkVolumeRayCastMapper::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkVolumeRayCastMapper, SoEngine, "Engine" );
}

void SoVtkVolumeRayCastMapper::evaluate()
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


void SoVtkVolumeRayCastMapper::inputChanged(SoField * f)
{
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkDataSet"))
		mObject->SetInput(vtkDataSet::SafeDownCast(inputPtr->getPointer()));

	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the AutoAdjustSampleDistances value
	if ( f == &AutoAdjustSampleDistances )
		SO_VTK_SET_FIELD_VALUE( mObject, AutoAdjustSampleDistances);

	// Get the ClippingPlanes value
	if ( f == &ClippingPlanes )
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlanes);

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
	// Get the SampleDistance value
	if ( f == &SampleDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, SampleDistance);

	// Get the MinimumImageSampleDistance value
	if ( f == &MinimumImageSampleDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumImageSampleDistance);

	// Get the Cropping value
	if ( f == &Cropping )
		SO_VTK_SET_FIELD_VALUE( mObject, Cropping);

	// Get the IntermixIntersectingGeometry value
	if ( f == &IntermixIntersectingGeometry )
		SO_VTK_SET_FIELD_VALUE( mObject, IntermixIntersectingGeometry);

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

	// Get the ImageSampleDistance value
	if ( f == &ImageSampleDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, ImageSampleDistance);

	// Get the CroppingRegionFlags value
	if ( f == &CroppingRegionFlags )
		SO_VTK_SET_FIELD_VALUE( mObject, CroppingRegionFlags);

	// Get the BlendMode value
	if ( f == &BlendMode )
		SO_VTK_SET_FIELD_VALUE( mObject, BlendMode);

	// Get the MaximumImageSampleDistance value
	if ( f == &MaximumImageSampleDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumImageSampleDistance);

	// Get the VolumeRayCastFunction value
	if ( f == &VolumeRayCastFunction )
		SO_VTK_SET_FIELD_DATA( mObject, VolumeRayCastFunction, vtkVolumeRayCastFunction);

	// Get the GradientEstimator value
	if ( f == &GradientEstimator )
		SO_VTK_SET_FIELD_DATA( mObject, GradientEstimator, vtkEncodedGradientEstimator);

	////mObject->Update();
	
}

