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
 
 
# include "SoVtkGenericGlyph3DFilter.h"
# include "SoVtkUtils.h"

# include "vtkPolyData.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkGenericGlyph3DFilter )

SoVtkGenericGlyph3DFilter::SoVtkGenericGlyph3DFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGenericGlyph3DFilter);

	mObject = vtkGenericGlyph3DFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGenericGlyph3DFilter *aGenericGlyph3DFilter = vtkGenericGlyph3DFilter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(GeneratePointIds, (0));
	GeneratePointIds.setValue(aGenericGlyph3DFilter->GetGeneratePointIds());

	SO_ENGINE_ADD_INPUT(PointIdsName, (""));

	SO_ENGINE_ADD_INPUT(Scaling, (0));
	Scaling.setValue(aGenericGlyph3DFilter->GetScaling());

	SO_ENGINE_ADD_INPUT(Clamping, (0));
	Clamping.setValue(aGenericGlyph3DFilter->GetClamping());

	SO_ENGINE_ADD_INPUT(IndexMode, (0));
	IndexMode.setValue(aGenericGlyph3DFilter->GetIndexMode());

	SO_ENGINE_ADD_INPUT(ScaleMode, (0));
	ScaleMode.setValue(aGenericGlyph3DFilter->GetScaleMode());

	SO_ENGINE_ADD_INPUT(Orient, (0));
	Orient.setValue(aGenericGlyph3DFilter->GetOrient());

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(ColorMode, (0));
	ColorMode.setValue(aGenericGlyph3DFilter->GetColorMode());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(VectorMode, (0));
	VectorMode.setValue(aGenericGlyph3DFilter->GetVectorMode());

	SO_ENGINE_ADD_INPUT(ScaleFactor, (0));
	ScaleFactor.setValue(aGenericGlyph3DFilter->GetScaleFactor());

	aGenericGlyph3DFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkGenericGlyph3DFilter::~SoVtkGenericGlyph3DFilter()
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

void SoVtkGenericGlyph3DFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGenericGlyph3DFilter, SoEngine, "Engine" );
}

void SoVtkGenericGlyph3DFilter::evaluate()
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


void SoVtkGenericGlyph3DFilter::inputChanged(SoField * f)
{
	// Get the GeneratePointIds value
	if ( f == &GeneratePointIds )
		SO_VTK_SET_FIELD_VALUE( mObject, GeneratePointIds);

	// Get the PointIdsName value
	if ( f == &PointIdsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, PointIdsName);

	// Get the Scaling value
	if ( f == &Scaling )
		SO_VTK_SET_FIELD_VALUE( mObject, Scaling);

	// Get the Clamping value
	if ( f == &Clamping )
		SO_VTK_SET_FIELD_VALUE( mObject, Clamping);

	// Get the IndexMode value
	if ( f == &IndexMode )
		SO_VTK_SET_FIELD_VALUE( mObject, IndexMode);

	// Get the ScaleMode value
	if ( f == &ScaleMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleMode);

	// Get the Orient value
	if ( f == &Orient )
		SO_VTK_SET_FIELD_VALUE( mObject, Orient);

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkPolyData);

	// Get the ColorMode value
	if ( f == &ColorMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorMode);

	// Get the VectorMode value
	if ( f == &VectorMode )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorMode);

	// Get the ScaleFactor value
	if ( f == &ScaleFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleFactor);

	mObject->Update();
}

void SoVtkGenericGlyph3DFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGenericGlyph3DFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the GeneratePointIds value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GeneratePointIds);

	// Get the PointIdsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, PointIdsName);

	// Get the Scaling value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Scaling);

	// Get the Clamping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Clamping);

	// Get the IndexMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IndexMode);

	// Get the ScaleMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleMode);

	// Get the Orient value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Orient);

	// Get the Source value
	
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkPolyData);

	// Get the ColorMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ColorMode);

	// Get the VectorMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, VectorMode);

	// Get the ScaleFactor value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleFactor);

	mObject->Update();
}
