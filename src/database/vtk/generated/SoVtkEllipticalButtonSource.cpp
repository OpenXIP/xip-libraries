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
 
 
# include "SoVtkEllipticalButtonSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkEllipticalButtonSource )

SoVtkEllipticalButtonSource::SoVtkEllipticalButtonSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkEllipticalButtonSource);

	mObject = vtkEllipticalButtonSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkEllipticalButtonSource *aEllipticalButtonSource = vtkEllipticalButtonSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CircumferentialResolution, (0));
	CircumferentialResolution.setValue(aEllipticalButtonSource->GetCircumferentialResolution());

	SO_ENGINE_ADD_INPUT(TextureResolution, (0));
	TextureResolution.setValue(aEllipticalButtonSource->GetTextureResolution());

	SO_ENGINE_ADD_INPUT(Height, (0));
	Height.setValue(aEllipticalButtonSource->GetHeight());

	SO_ENGINE_ADD_INPUT(ShoulderTextureCoordinate, (0,0));

	x = aEllipticalButtonSource->GetShoulderTextureCoordinate();
	ShoulderTextureCoordinate.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(Width, (0));
	Width.setValue(aEllipticalButtonSource->GetWidth());

	SO_ENGINE_ADD_INPUT(Center, (0,0,0));

	x = aEllipticalButtonSource->GetCenter();
	Center.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(TwoSided, (0));
	TwoSided.setValue(aEllipticalButtonSource->GetTwoSided());

	SO_ENGINE_ADD_INPUT(TextureStyle, (0));
	TextureStyle.setValue(aEllipticalButtonSource->GetTextureStyle());

	SO_ENGINE_ADD_INPUT(TextureDimensions, (0,0));

	y = (int *) aEllipticalButtonSource->GetTextureDimensions();
	TextureDimensions.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(RadialRatio, (0));
	RadialRatio.setValue(aEllipticalButtonSource->GetRadialRatio());

	SO_ENGINE_ADD_INPUT(Depth, (0));
	Depth.setValue(aEllipticalButtonSource->GetDepth());

	SO_ENGINE_ADD_INPUT(ShoulderResolution, (0));
	ShoulderResolution.setValue(aEllipticalButtonSource->GetShoulderResolution());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aEllipticalButtonSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkEllipticalButtonSource::~SoVtkEllipticalButtonSource()
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

void SoVtkEllipticalButtonSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkEllipticalButtonSource, SoEngine, "Engine" );
}

void SoVtkEllipticalButtonSource::evaluate()
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


void SoVtkEllipticalButtonSource::inputChanged(SoField * f)
{
	// Get the CircumferentialResolution value
	if ( f == &CircumferentialResolution )
		SO_VTK_SET_FIELD_VALUE( mObject, CircumferentialResolution);

	// Get the TextureResolution value
	if ( f == &TextureResolution )
		SO_VTK_SET_FIELD_VALUE( mObject, TextureResolution);

	// Get the Height value
	if ( f == &Height )
		SO_VTK_SET_FIELD_VALUE( mObject, Height);

	// Get the ShoulderTextureCoordinate value
	if ( f == &ShoulderTextureCoordinate )
		SO_VTK_SET_FIELD_VEC2F( mObject, ShoulderTextureCoordinate);

	// Get the Width value
	if ( f == &Width )
		SO_VTK_SET_FIELD_VALUE( mObject, Width);

	// Get the Center value
	if ( f == &Center )
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the TwoSided value
	if ( f == &TwoSided )
		SO_VTK_SET_FIELD_VALUE( mObject, TwoSided);

	// Get the TextureStyle value
	if ( f == &TextureStyle )
		SO_VTK_SET_FIELD_VALUE( mObject, TextureStyle);

	// Get the TextureDimensions value
	if ( f == &TextureDimensions )
		SO_VTK_SET_FIELD_VEC2F( mObject, TextureDimensions);

	// Get the RadialRatio value
	if ( f == &RadialRatio )
		SO_VTK_SET_FIELD_VALUE( mObject, RadialRatio);

	// Get the Depth value
	if ( f == &Depth )
		SO_VTK_SET_FIELD_VALUE( mObject, Depth);

	// Get the ShoulderResolution value
	if ( f == &ShoulderResolution )
		SO_VTK_SET_FIELD_VALUE( mObject, ShoulderResolution);

	mObject->Update();
}

void SoVtkEllipticalButtonSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkEllipticalButtonSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the CircumferentialResolution value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CircumferentialResolution);

	// Get the TextureResolution value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TextureResolution);

	// Get the Height value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Height);

	// Get the ShoulderTextureCoordinate value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ShoulderTextureCoordinate);

	// Get the Width value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Width);

	// Get the Center value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the TwoSided value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TwoSided);

	// Get the TextureStyle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TextureStyle);

	// Get the TextureDimensions value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, TextureDimensions);

	// Get the RadialRatio value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RadialRatio);

	// Get the Depth value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Depth);

	// Get the ShoulderResolution value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ShoulderResolution);

	mObject->Update();
}
