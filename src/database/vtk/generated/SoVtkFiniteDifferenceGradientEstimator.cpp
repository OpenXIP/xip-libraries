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
 
 
# include "SoVtkFiniteDifferenceGradientEstimator.h"
# include "SoVtkUtils.h"

# include "vtkDirectionEncoder.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkFiniteDifferenceGradientEstimator )

SoVtkFiniteDifferenceGradientEstimator::SoVtkFiniteDifferenceGradientEstimator()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkFiniteDifferenceGradientEstimator);

	mObject = vtkFiniteDifferenceGradientEstimator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkFiniteDifferenceGradientEstimator *aFiniteDifferenceGradientEstimator = vtkFiniteDifferenceGradientEstimator::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CylinderClip, (0));
	CylinderClip.setValue(aFiniteDifferenceGradientEstimator->GetCylinderClip());

	SO_ENGINE_ADD_INPUT(BoundsClip, (0));
	BoundsClip.setValue(aFiniteDifferenceGradientEstimator->GetBoundsClip());

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aFiniteDifferenceGradientEstimator->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(SampleSpacingInVoxels, (0));
	SampleSpacingInVoxels.setValue(aFiniteDifferenceGradientEstimator->GetSampleSpacingInVoxels());

	SO_ENGINE_ADD_INPUT(ZeroNormalThreshold, (0));
	SO_ENGINE_ADD_INPUT(Bounds, (0));

	SO_ENGINE_ADD_INPUT(GradientMagnitudeBias, (0));
	GradientMagnitudeBias.setValue(aFiniteDifferenceGradientEstimator->GetGradientMagnitudeBias());

	SO_ENGINE_ADD_INPUT(ComputeGradientMagnitudes, (0));
	ComputeGradientMagnitudes.setValue(aFiniteDifferenceGradientEstimator->GetComputeGradientMagnitudes());

	SO_ENGINE_ADD_INPUT(DirectionEncoder, (0));

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(GradientMagnitudeScale, (0));
	GradientMagnitudeScale.setValue(aFiniteDifferenceGradientEstimator->GetGradientMagnitudeScale());

	SO_ENGINE_ADD_INPUT(ZeroPad, (0));
	ZeroPad.setValue(aFiniteDifferenceGradientEstimator->GetZeroPad());

	aFiniteDifferenceGradientEstimator->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkFiniteDifferenceGradientEstimator::~SoVtkFiniteDifferenceGradientEstimator()
{
	// Deletion of the objects if they exist
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

void SoVtkFiniteDifferenceGradientEstimator::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkFiniteDifferenceGradientEstimator, SoEngine, "Engine" );
}

void SoVtkFiniteDifferenceGradientEstimator::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
			mObject->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
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
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkFiniteDifferenceGradientEstimator::inputChanged(SoField * f)
{
	// Get the CylinderClip value
	if ( f == &CylinderClip )
		SO_VTK_SET_FIELD_VALUE( mObject, CylinderClip);

	// Get the BoundsClip value
	if ( f == &BoundsClip )
		SO_VTK_SET_FIELD_VALUE( mObject, BoundsClip);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the SampleSpacingInVoxels value
	if ( f == &SampleSpacingInVoxels )
		SO_VTK_SET_FIELD_VALUE( mObject, SampleSpacingInVoxels);

	// Get the ZeroNormalThreshold value
	if ( f == &ZeroNormalThreshold )
		SO_VTK_SET_FIELD_VALUE( mObject, ZeroNormalThreshold);

	// Get the Bounds value
	if ( f == &Bounds )
	{
		if ( Bounds.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, Bounds);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the GradientMagnitudeBias value
	if ( f == &GradientMagnitudeBias )
		SO_VTK_SET_FIELD_VALUE( mObject, GradientMagnitudeBias);

	// Get the ComputeGradientMagnitudes value
	if ( f == &ComputeGradientMagnitudes )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeGradientMagnitudes);

	// Get the DirectionEncoder value
	if ( f == &DirectionEncoder )
		SO_VTK_SET_FIELD_DATA( mObject, DirectionEncoder, vtkDirectionEncoder);

	// Get the GradientMagnitudeScale value
	if ( f == &GradientMagnitudeScale )
		SO_VTK_SET_FIELD_VALUE( mObject, GradientMagnitudeScale);

	// Get the ZeroPad value
	if ( f == &ZeroPad )
		SO_VTK_SET_FIELD_VALUE( mObject, ZeroPad);

}

void SoVtkFiniteDifferenceGradientEstimator::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkFiniteDifferenceGradientEstimator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
		mObject->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

	// Get the CylinderClip value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CylinderClip);

	// Get the BoundsClip value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BoundsClip);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the SampleSpacingInVoxels value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SampleSpacingInVoxels);

	// Get the ZeroNormalThreshold value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ZeroNormalThreshold);

	// Get the Bounds value
	
	{
		if ( Bounds.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, Bounds);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the GradientMagnitudeBias value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GradientMagnitudeBias);

	// Get the ComputeGradientMagnitudes value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeGradientMagnitudes);

	// Get the DirectionEncoder value
	
		SO_VTK_SET_FIELD_DATA( mObject, DirectionEncoder, vtkDirectionEncoder);

	// Get the GradientMagnitudeScale value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GradientMagnitudeScale);

	// Get the ZeroPad value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ZeroPad);

}
