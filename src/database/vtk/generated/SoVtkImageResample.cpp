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
 
 
# include "SoVtkImageResample.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"
# include "vtkMatrix4x4.h"
# include "vtkAlgorithmOutput.h"
# include "vtkAbstractTransform.h"


SO_ENGINE_SOURCE( SoVtkImageResample )

SoVtkImageResample::SoVtkImageResample()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageResample);

	mObject = vtkImageResample::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageResample *aImageResample = vtkImageResample::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(BackgroundColor, (0,0,0,0));

	x = aImageResample->GetBackgroundColor();
	BackgroundColor.setValue(x[0],x[1],x[2],x[3]);

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageResample->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(BackgroundLevel, (0));
	BackgroundLevel.setValue(aImageResample->GetBackgroundLevel());

	SO_ENGINE_ADD_INPUT(OutputOrigin, (0,0,0));

	x = aImageResample->GetOutputOrigin();
	OutputOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InformationInput, (0));

	SO_ENGINE_ADD_INPUT(ResliceAxesDirectionCosines, ());
	ResliceAxesDirectionCosines.setFormat("double double double double double double double double double");

	SO_ENGINE_ADD_INPUT(ResliceAxes, (0));

	SO_ENGINE_ADD_INPUT(Wrap, (0));
	Wrap.setValue(aImageResample->GetWrap());

	SO_ENGINE_ADD_INPUT(ResliceAxesOrigin, ());
	ResliceAxesOrigin.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(Mirror, (0));
	Mirror.setValue(aImageResample->GetMirror());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(Optimization, (0));
	Optimization.setValue(aImageResample->GetOptimization());

	SO_ENGINE_ADD_INPUT(ResliceTransform, (0));

	SO_ENGINE_ADD_INPUT(AxisOutputSpacing, ());
	AxisOutputSpacing.setFormat("int double");

	SO_ENGINE_ADD_INPUT(AxisMagnificationFactor, ());
	AxisMagnificationFactor.setFormat("int double");

	SO_ENGINE_ADD_INPUT(OutputDimensionality, (0));
	OutputDimensionality.setValue(aImageResample->GetOutputDimensionality());

	SO_ENGINE_ADD_INPUT(OutputSpacing, (0,0,0));

	x = aImageResample->GetOutputSpacing();
	OutputSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InterpolationMode, (0));
	InterpolationMode.setValue(aImageResample->GetInterpolationMode());

	SO_ENGINE_ADD_INPUT(Dimensionality, (0));
	Dimensionality.setValue(aImageResample->GetDimensionality());

	SO_ENGINE_ADD_INPUT(OutputExtent, (0));

	SO_ENGINE_ADD_INPUT(Border, (0));
	Border.setValue(aImageResample->GetBorder());

	SO_ENGINE_ADD_INPUT(AutoCropOutput, (0));
	AutoCropOutput.setValue(aImageResample->GetAutoCropOutput());

	SO_ENGINE_ADD_INPUT(Interpolate, (0));
	SO_ENGINE_ADD_INPUT(TransformInputSampling, (0));
	TransformInputSampling.setValue(aImageResample->GetTransformInputSampling());

	aImageResample->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageResample::~SoVtkImageResample()
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

void SoVtkImageResample::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageResample, SoEngine, "Engine" );
}

void SoVtkImageResample::evaluate()
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


void SoVtkImageResample::inputChanged(SoField * f)
{
	// Get the BackgroundColor value
	if ( f == &BackgroundColor )
		SO_VTK_SET_FIELD_VEC4F( mObject, BackgroundColor);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the BackgroundLevel value
	if ( f == &BackgroundLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, BackgroundLevel);

	// Get the OutputOrigin value
	if ( f == &OutputOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputOrigin);

	// Get the InformationInput value
	if ( f == &InformationInput )
		SO_VTK_SET_FIELD_DATA( mObject, InformationInput, vtkImageData);

	// Get the ResliceAxesDirectionCosines value
	if ( f == &ResliceAxesDirectionCosines )
	{
		SbVariant *vResliceAxesDirectionCosines = (SbVariant *)ResliceAxesDirectionCosines.getValues(0);
		SoInput input;
		int nb_fields = ResliceAxesDirectionCosines.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		double val8;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vResliceAxesDirectionCosines[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			input.read(val8);
			mObject->SetResliceAxesDirectionCosines( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7,
				(double) val8
			);
		}
	}

	// Get the ResliceAxes value
	if ( f == &ResliceAxes )
		SO_VTK_SET_FIELD_DATA( mObject, ResliceAxes, vtkMatrix4x4);

	// Get the Wrap value
	if ( f == &Wrap )
		SO_VTK_SET_FIELD_VALUE( mObject, Wrap);

	// Get the ResliceAxesOrigin value
	if ( f == &ResliceAxesOrigin )
	{
		SbVariant *vResliceAxesOrigin = (SbVariant *)ResliceAxesOrigin.getValues(0);
		SoInput input;
		int nb_fields = ResliceAxesOrigin.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vResliceAxesOrigin[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetResliceAxesOrigin( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Mirror value
	if ( f == &Mirror )
		SO_VTK_SET_FIELD_VALUE( mObject, Mirror);

	// Get the Optimization value
	if ( f == &Optimization )
		SO_VTK_SET_FIELD_VALUE( mObject, Optimization);

	// Get the ResliceTransform value
	if ( f == &ResliceTransform )
		SO_VTK_SET_FIELD_DATA( mObject, ResliceTransform, vtkAbstractTransform);

	// Get the AxisOutputSpacing value
	if ( f == &AxisOutputSpacing )
	{
		SbVariant *vAxisOutputSpacing = (SbVariant *)AxisOutputSpacing.getValues(0);
		SoInput input;
		int nb_fields = AxisOutputSpacing.getNum();

		int val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vAxisOutputSpacing[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetAxisOutputSpacing( 
				(int) val0,
				(double) val1
			);
		}
	}

	// Get the AxisMagnificationFactor value
	if ( f == &AxisMagnificationFactor )
	{
		SbVariant *vAxisMagnificationFactor = (SbVariant *)AxisMagnificationFactor.getValues(0);
		SoInput input;
		int nb_fields = AxisMagnificationFactor.getNum();

		int val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vAxisMagnificationFactor[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetAxisMagnificationFactor( 
				(int) val0,
				(double) val1
			);
		}
	}

	// Get the OutputDimensionality value
	if ( f == &OutputDimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputDimensionality);

	// Get the OutputSpacing value
	if ( f == &OutputSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputSpacing);

	// Get the InterpolationMode value
	if ( f == &InterpolationMode )
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolationMode);

	// Get the Dimensionality value
	if ( f == &Dimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, Dimensionality);

	// Get the OutputExtent value
	if ( f == &OutputExtent )
	{
		if ( OutputExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, OutputExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the Border value
	if ( f == &Border )
		SO_VTK_SET_FIELD_VALUE( mObject, Border);

	// Get the AutoCropOutput value
	if ( f == &AutoCropOutput )
		SO_VTK_SET_FIELD_VALUE( mObject, AutoCropOutput);

	// Get the Interpolate value
	if ( f == &Interpolate )
		SO_VTK_SET_FIELD_VALUE( mObject, Interpolate);

	// Get the TransformInputSampling value
	if ( f == &TransformInputSampling )
		SO_VTK_SET_FIELD_VALUE( mObject, TransformInputSampling);

	mObject->Update();
}

void SoVtkImageResample::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageResample::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the BackgroundColor value
	
		SO_VTK_SET_FIELD_VEC4F( mObject, BackgroundColor);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the BackgroundLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BackgroundLevel);

	// Get the OutputOrigin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputOrigin);

	// Get the InformationInput value
	
		SO_VTK_SET_FIELD_DATA( mObject, InformationInput, vtkImageData);

	// Get the ResliceAxesDirectionCosines value
	if (addCalled == 1)
	{
		SbVariant *vResliceAxesDirectionCosines = (SbVariant *)ResliceAxesDirectionCosines.getValues(0);
		SoInput input;
		int nb_fields = ResliceAxesDirectionCosines.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		double val8;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vResliceAxesDirectionCosines[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			input.read(val8);
			mObject->SetResliceAxesDirectionCosines( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7,
				(double) val8
			);
		}
	}

	// Get the ResliceAxes value
	
		SO_VTK_SET_FIELD_DATA( mObject, ResliceAxes, vtkMatrix4x4);

	// Get the Wrap value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Wrap);

	// Get the ResliceAxesOrigin value
	if (addCalled == 1)
	{
		SbVariant *vResliceAxesOrigin = (SbVariant *)ResliceAxesOrigin.getValues(0);
		SoInput input;
		int nb_fields = ResliceAxesOrigin.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vResliceAxesOrigin[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetResliceAxesOrigin( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Mirror value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Mirror);

	// Get the Optimization value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Optimization);

	// Get the ResliceTransform value
	
		SO_VTK_SET_FIELD_DATA( mObject, ResliceTransform, vtkAbstractTransform);

	// Get the AxisOutputSpacing value
	if (addCalled == 1)
	{
		SbVariant *vAxisOutputSpacing = (SbVariant *)AxisOutputSpacing.getValues(0);
		SoInput input;
		int nb_fields = AxisOutputSpacing.getNum();

		int val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vAxisOutputSpacing[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetAxisOutputSpacing( 
				(int) val0,
				(double) val1
			);
		}
	}

	// Get the AxisMagnificationFactor value
	if (addCalled == 1)
	{
		SbVariant *vAxisMagnificationFactor = (SbVariant *)AxisMagnificationFactor.getValues(0);
		SoInput input;
		int nb_fields = AxisMagnificationFactor.getNum();

		int val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vAxisMagnificationFactor[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetAxisMagnificationFactor( 
				(int) val0,
				(double) val1
			);
		}
	}

	// Get the OutputDimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputDimensionality);

	// Get the OutputSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputSpacing);

	// Get the InterpolationMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolationMode);

	// Get the Dimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Dimensionality);

	// Get the OutputExtent value
	
	{
		if ( OutputExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, OutputExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the Border value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Border);

	// Get the AutoCropOutput value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AutoCropOutput);

	// Get the Interpolate value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Interpolate);

	// Get the TransformInputSampling value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TransformInputSampling);

	mObject->Update();
}
