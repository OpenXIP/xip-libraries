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
 
 
# include "SoVtkCursor3D.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkCursor3D )

SoVtkCursor3D::SoVtkCursor3D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCursor3D);

	mObject = vtkCursor3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCursor3D *aCursor3D = vtkCursor3D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(FocalPoint, ());
	FocalPoint.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(TranslationMode, (0));
	TranslationMode.setValue(aCursor3D->GetTranslationMode());

	SO_ENGINE_ADD_INPUT(ModelBounds, ());
	ModelBounds.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(Axes, (0));
	Axes.setValue(aCursor3D->GetAxes());

	SO_ENGINE_ADD_INPUT(Outline, (0));
	Outline.setValue(aCursor3D->GetOutline());

	SO_ENGINE_ADD_INPUT(ZShadows, (0));
	ZShadows.setValue(aCursor3D->GetZShadows());

	SO_ENGINE_ADD_INPUT(Wrap, (0));
	Wrap.setValue(aCursor3D->GetWrap());

	SO_ENGINE_ADD_INPUT(XShadows, (0));
	XShadows.setValue(aCursor3D->GetXShadows());

	SO_ENGINE_ADD_INPUT(YShadows, (0));
	YShadows.setValue(aCursor3D->GetYShadows());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aCursor3D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkCursor3D::~SoVtkCursor3D()
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

void SoVtkCursor3D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCursor3D, SoEngine, "Engine" );
}

void SoVtkCursor3D::evaluate()
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


void SoVtkCursor3D::inputChanged(SoField * f)
{
	// Get the FocalPoint value
	if ( f == &FocalPoint )
	{
		SbVariant *vFocalPoint = (SbVariant *)FocalPoint.getValues(0);
		SoInput input;
		int nb_fields = FocalPoint.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vFocalPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetFocalPoint( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the TranslationMode value
	if ( f == &TranslationMode )
		SO_VTK_SET_FIELD_VALUE( mObject, TranslationMode);

	// Get the ModelBounds value
	if ( f == &ModelBounds )
	{
		SbVariant *vModelBounds = (SbVariant *)ModelBounds.getValues(0);
		SoInput input;
		int nb_fields = ModelBounds.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vModelBounds[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetModelBounds( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	// Get the Axes value
	if ( f == &Axes )
		SO_VTK_SET_FIELD_VALUE( mObject, Axes);

	// Get the Outline value
	if ( f == &Outline )
		SO_VTK_SET_FIELD_VALUE( mObject, Outline);

	// Get the ZShadows value
	if ( f == &ZShadows )
		SO_VTK_SET_FIELD_VALUE( mObject, ZShadows);

	// Get the Wrap value
	if ( f == &Wrap )
		SO_VTK_SET_FIELD_VALUE( mObject, Wrap);

	// Get the XShadows value
	if ( f == &XShadows )
		SO_VTK_SET_FIELD_VALUE( mObject, XShadows);

	// Get the YShadows value
	if ( f == &YShadows )
		SO_VTK_SET_FIELD_VALUE( mObject, YShadows);

	mObject->Update();
}

void SoVtkCursor3D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCursor3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the FocalPoint value
	if (addCalled == 1)
	{
		SbVariant *vFocalPoint = (SbVariant *)FocalPoint.getValues(0);
		SoInput input;
		int nb_fields = FocalPoint.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vFocalPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetFocalPoint( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the TranslationMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TranslationMode);

	// Get the ModelBounds value
	if (addCalled == 1)
	{
		SbVariant *vModelBounds = (SbVariant *)ModelBounds.getValues(0);
		SoInput input;
		int nb_fields = ModelBounds.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vModelBounds[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetModelBounds( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	// Get the Axes value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Axes);

	// Get the Outline value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Outline);

	// Get the ZShadows value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ZShadows);

	// Get the Wrap value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Wrap);

	// Get the XShadows value
	
		SO_VTK_SET_FIELD_VALUE( mObject, XShadows);

	// Get the YShadows value
	
		SO_VTK_SET_FIELD_VALUE( mObject, YShadows);

	mObject->Update();
}
