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
 
 
# include "SoVtkCleanPolyData.h"
# include "SoVtkUtils.h"

# include "vtkPointLocator.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkCleanPolyData )

SoVtkCleanPolyData::SoVtkCleanPolyData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCleanPolyData);

	mObject = vtkCleanPolyData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCleanPolyData *aCleanPolyData = vtkCleanPolyData::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ToleranceIsAbsolute, (0));
	ToleranceIsAbsolute.setValue(aCleanPolyData->GetToleranceIsAbsolute());

	SO_ENGINE_ADD_INPUT(AbsoluteTolerance, (0));
	AbsoluteTolerance.setValue(aCleanPolyData->GetAbsoluteTolerance());

	SO_ENGINE_ADD_INPUT(ConvertPolysToLines, (0));
	ConvertPolysToLines.setValue(aCleanPolyData->GetConvertPolysToLines());

	SO_ENGINE_ADD_INPUT(ConvertStripsToPolys, (0));
	ConvertStripsToPolys.setValue(aCleanPolyData->GetConvertStripsToPolys());

	SO_ENGINE_ADD_INPUT(PieceInvariant, (0));
	PieceInvariant.setValue(aCleanPolyData->GetPieceInvariant());

	SO_ENGINE_ADD_INPUT(PointMerging, (0));
	PointMerging.setValue(aCleanPolyData->GetPointMerging());

	SO_ENGINE_ADD_INPUT(ConvertLinesToPoints, (0));
	ConvertLinesToPoints.setValue(aCleanPolyData->GetConvertLinesToPoints());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(Tolerance, (0));
	Tolerance.setValue(aCleanPolyData->GetTolerance());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aCleanPolyData->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oLocator, SoSFVtkObject );
	mLocator = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkCleanPolyData::~SoVtkCleanPolyData()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mLocator )
	{
	
		mLocator->unref();
		mLocator = 0;
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

void SoVtkCleanPolyData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCleanPolyData, SoEngine, "Engine" );
}

void SoVtkCleanPolyData::evaluate()
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
		
		if ( mLocator )
		{
		
			mLocator->unref();
			mLocator = 0;
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

		mObject->GetLocator();
		mLocator = new SoVtkObject();
		mLocator->ref();
		mLocator->setPointer( mObject->GetLocator() );

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
	SO_ENGINE_OUTPUT( oLocator, SoSFVtkObject, setValue( mLocator ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkCleanPolyData::inputChanged(SoField * f)
{
	// Get the ToleranceIsAbsolute value
	if ( f == &ToleranceIsAbsolute )
		SO_VTK_SET_FIELD_VALUE( mObject, ToleranceIsAbsolute);

	// Get the AbsoluteTolerance value
	if ( f == &AbsoluteTolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteTolerance);

	// Get the ConvertPolysToLines value
	if ( f == &ConvertPolysToLines )
		SO_VTK_SET_FIELD_VALUE( mObject, ConvertPolysToLines);

	// Get the ConvertStripsToPolys value
	if ( f == &ConvertStripsToPolys )
		SO_VTK_SET_FIELD_VALUE( mObject, ConvertStripsToPolys);

	// Get the PieceInvariant value
	if ( f == &PieceInvariant )
		SO_VTK_SET_FIELD_VALUE( mObject, PieceInvariant);

	// Get the PointMerging value
	if ( f == &PointMerging )
		SO_VTK_SET_FIELD_VALUE( mObject, PointMerging);

	// Get the ConvertLinesToPoints value
	if ( f == &ConvertLinesToPoints )
		SO_VTK_SET_FIELD_VALUE( mObject, ConvertLinesToPoints);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the Tolerance value
	if ( f == &Tolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, Tolerance);

	mObject->Update();
}

void SoVtkCleanPolyData::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCleanPolyData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ToleranceIsAbsolute value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ToleranceIsAbsolute);

	// Get the AbsoluteTolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteTolerance);

	// Get the ConvertPolysToLines value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ConvertPolysToLines);

	// Get the ConvertStripsToPolys value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ConvertStripsToPolys);

	// Get the PieceInvariant value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PieceInvariant);

	// Get the PointMerging value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PointMerging);

	// Get the ConvertLinesToPoints value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ConvertLinesToPoints);

	// Get the Locator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the Tolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Tolerance);

	mObject->Update();
}
