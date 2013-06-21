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
 
 
# include "SoVtkImageMandelbrotSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageMandelbrotSource )

SoVtkImageMandelbrotSource::SoVtkImageMandelbrotSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageMandelbrotSource);

	mObject = vtkImageMandelbrotSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageMandelbrotSource *aImageMandelbrotSource = vtkImageMandelbrotSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ConstantSize, (0));
	ConstantSize.setValue(aImageMandelbrotSource->GetConstantSize());

	SO_ENGINE_ADD_INPUT(SizeCX, ());
	SizeCX.setFormat("double double double double");

	SO_ENGINE_ADD_INPUT(ProjectionAxes, ());
	ProjectionAxes.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(SampleCX, (0,0,0,0));

	x = aImageMandelbrotSource->GetSampleCX();
	SampleCX.setValue(x[0],x[1],x[2],x[3]);

	SO_ENGINE_ADD_INPUT(MaximumNumberOfIterations, (0));
	MaximumNumberOfIterations.setValue(aImageMandelbrotSource->GetMaximumNumberOfIterations());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(OriginCX, (0,0,0,0));

	x = aImageMandelbrotSource->GetOriginCX();
	OriginCX.setValue(x[0],x[1],x[2],x[3]);

	aImageMandelbrotSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageMandelbrotSource::~SoVtkImageMandelbrotSource()
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

void SoVtkImageMandelbrotSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageMandelbrotSource, SoEngine, "Engine" );
}

void SoVtkImageMandelbrotSource::evaluate()
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


void SoVtkImageMandelbrotSource::inputChanged(SoField * f)
{
	// Get the ConstantSize value
	if ( f == &ConstantSize )
		SO_VTK_SET_FIELD_VALUE( mObject, ConstantSize);

	// Get the SizeCX value
	if ( f == &SizeCX )
	{
		SbVariant *vSizeCX = (SbVariant *)SizeCX.getValues(0);
		SoInput input;
		int nb_fields = SizeCX.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSizeCX[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->SetSizeCX( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the ProjectionAxes value
	if ( f == &ProjectionAxes )
	{
		SbVariant *vProjectionAxes = (SbVariant *)ProjectionAxes.getValues(0);
		SoInput input;
		int nb_fields = ProjectionAxes.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vProjectionAxes[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetProjectionAxes( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

	// Get the WholeExtent value
	if ( f == &WholeExtent )
	{
		SbVariant *vWholeExtent = (SbVariant *)WholeExtent.getValues(0);
		SoInput input;
		int nb_fields = WholeExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vWholeExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetWholeExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	// Get the SampleCX value
	if ( f == &SampleCX )
		SO_VTK_SET_FIELD_VEC4F( mObject, SampleCX);

	// Get the MaximumNumberOfIterations value
	if ( f == &MaximumNumberOfIterations )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumNumberOfIterations);

	// Get the OriginCX value
	if ( f == &OriginCX )
		SO_VTK_SET_FIELD_VEC4F( mObject, OriginCX);

	mObject->Update();
}

void SoVtkImageMandelbrotSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageMandelbrotSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ConstantSize value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ConstantSize);

	// Get the SizeCX value
	if (addCalled == 1)
	{
		SbVariant *vSizeCX = (SbVariant *)SizeCX.getValues(0);
		SoInput input;
		int nb_fields = SizeCX.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSizeCX[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->SetSizeCX( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the ProjectionAxes value
	if (addCalled == 1)
	{
		SbVariant *vProjectionAxes = (SbVariant *)ProjectionAxes.getValues(0);
		SoInput input;
		int nb_fields = ProjectionAxes.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vProjectionAxes[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetProjectionAxes( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

	// Get the WholeExtent value
	if (addCalled == 1)
	{
		SbVariant *vWholeExtent = (SbVariant *)WholeExtent.getValues(0);
		SoInput input;
		int nb_fields = WholeExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vWholeExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetWholeExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	// Get the SampleCX value
	
		SO_VTK_SET_FIELD_VEC4F( mObject, SampleCX);

	// Get the MaximumNumberOfIterations value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumNumberOfIterations);

	// Get the OriginCX value
	
		SO_VTK_SET_FIELD_VEC4F( mObject, OriginCX);

	mObject->Update();
}
