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
 
 
# include "SoVtkImageAnisotropicDiffusion3D.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageAnisotropicDiffusion3D )

SoVtkImageAnisotropicDiffusion3D::SoVtkImageAnisotropicDiffusion3D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageAnisotropicDiffusion3D);

	mObject = vtkImageAnisotropicDiffusion3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageAnisotropicDiffusion3D *aImageAnisotropicDiffusion3D = vtkImageAnisotropicDiffusion3D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(GradientMagnitudeThreshold, (0));
	GradientMagnitudeThreshold.setValue(aImageAnisotropicDiffusion3D->GetGradientMagnitudeThreshold());

	SO_ENGINE_ADD_INPUT(NumberOfIterations, (0));
	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageAnisotropicDiffusion3D->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(Edges, (0));
	Edges.setValue(aImageAnisotropicDiffusion3D->GetEdges());

	SO_ENGINE_ADD_INPUT(DiffusionThreshold, (0));
	DiffusionThreshold.setValue(aImageAnisotropicDiffusion3D->GetDiffusionThreshold());

	SO_ENGINE_ADD_INPUT(DiffusionFactor, (0));
	DiffusionFactor.setValue(aImageAnisotropicDiffusion3D->GetDiffusionFactor());

	SO_ENGINE_ADD_INPUT(Faces, (0));
	Faces.setValue(aImageAnisotropicDiffusion3D->GetFaces());

	SO_ENGINE_ADD_INPUT(Corners, (0));
	Corners.setValue(aImageAnisotropicDiffusion3D->GetCorners());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageAnisotropicDiffusion3D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageAnisotropicDiffusion3D::~SoVtkImageAnisotropicDiffusion3D()
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

void SoVtkImageAnisotropicDiffusion3D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageAnisotropicDiffusion3D, SoEngine, "Engine" );
}

void SoVtkImageAnisotropicDiffusion3D::evaluate()
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


void SoVtkImageAnisotropicDiffusion3D::inputChanged(SoField * f)
{
	// Get the GradientMagnitudeThreshold value
	if ( f == &GradientMagnitudeThreshold )
		SO_VTK_SET_FIELD_VALUE( mObject, GradientMagnitudeThreshold);

	// Get the NumberOfIterations value
	if ( f == &NumberOfIterations )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfIterations);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the Edges value
	if ( f == &Edges )
		SO_VTK_SET_FIELD_VALUE( mObject, Edges);

	// Get the DiffusionThreshold value
	if ( f == &DiffusionThreshold )
		SO_VTK_SET_FIELD_VALUE( mObject, DiffusionThreshold);

	// Get the DiffusionFactor value
	if ( f == &DiffusionFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, DiffusionFactor);

	// Get the Faces value
	if ( f == &Faces )
		SO_VTK_SET_FIELD_VALUE( mObject, Faces);

	// Get the Corners value
	if ( f == &Corners )
		SO_VTK_SET_FIELD_VALUE( mObject, Corners);

	mObject->Update();
}

void SoVtkImageAnisotropicDiffusion3D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageAnisotropicDiffusion3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the GradientMagnitudeThreshold value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GradientMagnitudeThreshold);

	// Get the NumberOfIterations value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfIterations);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the Edges value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Edges);

	// Get the DiffusionThreshold value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DiffusionThreshold);

	// Get the DiffusionFactor value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DiffusionFactor);

	// Get the Faces value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Faces);

	// Get the Corners value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Corners);

	mObject->Update();
}
