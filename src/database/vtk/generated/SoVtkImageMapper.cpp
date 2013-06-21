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
 
 
# include "SoVtkImageMapper.h"
# include "SoVtkUtils.h"

# include "vtkPlaneCollection.h"
# include "vtkImageData.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkImageMapper )

SoVtkImageMapper::SoVtkImageMapper()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageMapper);

	mObject = vtkImageMapper::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageMapper *aImageMapper = vtkImageMapper::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ZSlice, (0));
	ZSlice.setValue(aImageMapper->GetZSlice());

	SO_ENGINE_ADD_INPUT(RenderToRectangle, (0));
	RenderToRectangle.setValue(aImageMapper->GetRenderToRectangle());

	SO_ENGINE_ADD_INPUT(UseCustomExtents, (0));
	UseCustomExtents.setValue(aImageMapper->GetUseCustomExtents());

	SO_ENGINE_ADD_INPUT(ClippingPlanes, (0));

	SO_ENGINE_ADD_INPUT(ColorWindow, (0));
	ColorWindow.setValue(aImageMapper->GetColorWindow());

	SO_ENGINE_ADD_INPUT(ColorLevel, (0));
	ColorLevel.setValue(aImageMapper->GetColorLevel());

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageMapper->Delete();


	SO_ENGINE_ADD_OUTPUT( oClippingPlanes, SoSFVtkObject );
	mClippingPlanes = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkImageMapper::~SoVtkImageMapper()
{
	// Deletion of the objects if they exist
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

void SoVtkImageMapper::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageMapper, SoEngine, "Engine" );
}

void SoVtkImageMapper::evaluate()
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
	SO_ENGINE_OUTPUT( oClippingPlanes, SoSFVtkObject, setValue( mClippingPlanes ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkImageMapper::inputChanged(SoField * f)
{
	// Get the ZSlice value
	if ( f == &ZSlice )
		SO_VTK_SET_FIELD_VALUE( mObject, ZSlice);

	// Get the RenderToRectangle value
	if ( f == &RenderToRectangle )
		SO_VTK_SET_FIELD_VALUE( mObject, RenderToRectangle);

	// Get the UseCustomExtents value
	if ( f == &UseCustomExtents )
		SO_VTK_SET_FIELD_VALUE( mObject, UseCustomExtents);

	// Get the ClippingPlanes value
	if ( f == &ClippingPlanes )
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlaneCollection);

	// Get the ColorWindow value
	if ( f == &ColorWindow )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorWindow);

	// Get the ColorLevel value
	if ( f == &ColorLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorLevel);

	mObject->Update();
}

void SoVtkImageMapper::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageMapper::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
		mObject->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ZSlice value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ZSlice);

	// Get the RenderToRectangle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RenderToRectangle);

	// Get the UseCustomExtents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UseCustomExtents);

	// Get the ClippingPlanes value
	
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlaneCollection);

	// Get the ColorWindow value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ColorWindow);

	// Get the ColorLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ColorLevel);

	mObject->Update();
}
