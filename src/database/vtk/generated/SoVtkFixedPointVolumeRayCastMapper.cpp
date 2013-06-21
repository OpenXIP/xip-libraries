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
 
 
# include "SoVtkFixedPointVolumeRayCastMapper.h"
# include "SoVtkUtils.h"

# include "vtkPlaneCollection.h"
# include "vtkImageData.h"
# include "vtkAlgorithmOutput.h"
# include "vtkFixedPointRayCastImage.h"
# include "vtkDataSet.h"


SO_ENGINE_SOURCE( SoVtkFixedPointVolumeRayCastMapper )

SoVtkFixedPointVolumeRayCastMapper::SoVtkFixedPointVolumeRayCastMapper()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkFixedPointVolumeRayCastMapper);

	mObject = vtkFixedPointVolumeRayCastMapper::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkFixedPointVolumeRayCastMapper *aFixedPointVolumeRayCastMapper = vtkFixedPointVolumeRayCastMapper::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aFixedPointVolumeRayCastMapper->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(AutoAdjustSampleDistances, (0));
	AutoAdjustSampleDistances.setValue(aFixedPointVolumeRayCastMapper->GetAutoAdjustSampleDistances());

	SO_ENGINE_ADD_INPUT(ClippingPlanes, (0));

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(SampleDistance, (0));
	SampleDistance.setValue(aFixedPointVolumeRayCastMapper->GetSampleDistance());

	SO_ENGINE_ADD_INPUT(MinimumImageSampleDistance, (0));
	MinimumImageSampleDistance.setValue(aFixedPointVolumeRayCastMapper->GetMinimumImageSampleDistance());

	SO_ENGINE_ADD_INPUT(Cropping, (0));
	Cropping.setValue(aFixedPointVolumeRayCastMapper->GetCropping());

	SO_ENGINE_ADD_INPUT(IntermixIntersectingGeometry, (0));
	IntermixIntersectingGeometry.setValue(aFixedPointVolumeRayCastMapper->GetIntermixIntersectingGeometry());

	SO_ENGINE_ADD_INPUT(RayCastImage, (0));

	SO_ENGINE_ADD_INPUT(CroppingRegionPlanes, (0));

	SO_ENGINE_ADD_INPUT(InteractiveSampleDistance, (0));
	InteractiveSampleDistance.setValue(aFixedPointVolumeRayCastMapper->GetInteractiveSampleDistance());

	SO_ENGINE_ADD_INPUT(ImageSampleDistance, (0));
	ImageSampleDistance.setValue(aFixedPointVolumeRayCastMapper->GetImageSampleDistance());

	SO_ENGINE_ADD_INPUT(CroppingRegionFlags, (0));
	CroppingRegionFlags.setValue(aFixedPointVolumeRayCastMapper->GetCroppingRegionFlags());

	SO_ENGINE_ADD_INPUT(BlendMode, (0));
	BlendMode.setValue(aFixedPointVolumeRayCastMapper->GetBlendMode());

	SO_ENGINE_ADD_INPUT(MaximumImageSampleDistance, (0));
	MaximumImageSampleDistance.setValue(aFixedPointVolumeRayCastMapper->GetMaximumImageSampleDistance());

	aFixedPointVolumeRayCastMapper->Delete();


	SO_ENGINE_ADD_OUTPUT( oDataSetInput, SoSFVtkObject );
	mDataSetInput = 0;
	SO_ENGINE_ADD_OUTPUT( oClippingPlanes, SoSFVtkObject );
	mClippingPlanes = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkFixedPointVolumeRayCastMapper::~SoVtkFixedPointVolumeRayCastMapper()
{
	// Deletion of the objects if they exist
	if ( mDataSetInput )
	{
	
		mDataSetInput->unref();
		mDataSetInput = 0;
	}
	
	if ( mClippingPlanes )
	{
	
		mClippingPlanes->unref();
		mClippingPlanes = 0;
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

void SoVtkFixedPointVolumeRayCastMapper::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkFixedPointVolumeRayCastMapper, SoEngine, "Engine" );
}

void SoVtkFixedPointVolumeRayCastMapper::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
			mObject->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mDataSetInput )
		{
		
			mDataSetInput->unref();
			mDataSetInput = 0;
		}
		
		if ( mClippingPlanes )
		{
		
			mClippingPlanes->unref();
			mClippingPlanes = 0;
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

		mObject->GetDataSetInput();
		mDataSetInput = new SoVtkObject();
		mDataSetInput->ref();
		mDataSetInput->setPointer( mObject->GetDataSetInput() );

		mObject->GetClippingPlanes();
		mClippingPlanes = new SoVtkObject();
		mClippingPlanes->ref();
		mClippingPlanes->setPointer( mObject->GetClippingPlanes() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oDataSetInput, SoSFVtkObject, setValue( mDataSetInput ) );
	SO_ENGINE_OUTPUT( oClippingPlanes, SoSFVtkObject, setValue( mClippingPlanes ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkFixedPointVolumeRayCastMapper::inputChanged(SoField * f)
{
	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the AutoAdjustSampleDistances value
	if ( f == &AutoAdjustSampleDistances )
		SO_VTK_SET_FIELD_VALUE( mObject, AutoAdjustSampleDistances);

	// Get the ClippingPlanes value
	if ( f == &ClippingPlanes )
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlaneCollection);

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

	// Get the RayCastImage value
	if ( f == &RayCastImage )
		SO_VTK_SET_FIELD_DATA( mObject, RayCastImage, vtkFixedPointRayCastImage);

	// Get the CroppingRegionPlanes value
	if ( f == &CroppingRegionPlanes )
	{
		if ( CroppingRegionPlanes.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFDOUBLE( mObject, CroppingRegionPlanes);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the InteractiveSampleDistance value
	if ( f == &InteractiveSampleDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, InteractiveSampleDistance);

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

	mObject->Update();
}

void SoVtkFixedPointVolumeRayCastMapper::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkFixedPointVolumeRayCastMapper::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
		mObject->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the AutoAdjustSampleDistances value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AutoAdjustSampleDistances);

	// Get the ClippingPlanes value
	
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlaneCollection);

	// Get the SampleDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SampleDistance);

	// Get the MinimumImageSampleDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumImageSampleDistance);

	// Get the Cropping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Cropping);

	// Get the IntermixIntersectingGeometry value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntermixIntersectingGeometry);

	// Get the RayCastImage value
	
		SO_VTK_SET_FIELD_DATA( mObject, RayCastImage, vtkFixedPointRayCastImage);

	// Get the CroppingRegionPlanes value
	
	{
		if ( CroppingRegionPlanes.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFDOUBLE( mObject, CroppingRegionPlanes);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the InteractiveSampleDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InteractiveSampleDistance);

	// Get the ImageSampleDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ImageSampleDistance);

	// Get the CroppingRegionFlags value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CroppingRegionFlags);

	// Get the BlendMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BlendMode);

	// Get the MaximumImageSampleDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumImageSampleDistance);

	mObject->Update();
}
