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
 
 
# include "SoVtkDataSetMapper.h"
# include "SoVtkUtils.h"

# include "vtkPlaneCollection.h"
# include "vtkDataSet.h"
# include "vtkAlgorithmOutput.h"
# include "vtkScalarsToColors.h"


SO_ENGINE_SOURCE( SoVtkDataSetMapper )

SoVtkDataSetMapper::SoVtkDataSetMapper()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDataSetMapper);

	mObject = vtkDataSetMapper::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDataSetMapper *aDataSetMapper = vtkDataSetMapper::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ScalarRange, (0,0));

	x = aDataSetMapper->GetScalarRange();
	ScalarRange.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(ResolveCoincidentTopology, (0));
	ResolveCoincidentTopology.setValue(aDataSetMapper->GetResolveCoincidentTopology());

	SO_ENGINE_ADD_INPUT(ImmediateModeRendering, (0));
	ImmediateModeRendering.setValue(aDataSetMapper->GetImmediateModeRendering());

	SO_ENGINE_ADD_INPUT(ScalarMode, (0));
	ScalarMode.setValue(aDataSetMapper->GetScalarMode());

	SO_ENGINE_ADD_INPUT(GlobalImmediateModeRendering, (0));
	GlobalImmediateModeRendering.setValue(aDataSetMapper->GetGlobalImmediateModeRendering());

	SO_ENGINE_ADD_INPUT(ClippingPlanes, (0));

	SO_ENGINE_ADD_INPUT(ResolveCoincidentTopologyZShift, (0));
	ResolveCoincidentTopologyZShift.setValue(aDataSetMapper->GetResolveCoincidentTopologyZShift());

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(UseLookupTableScalarRange, (0));
	UseLookupTableScalarRange.setValue(aDataSetMapper->GetUseLookupTableScalarRange());

	SO_ENGINE_ADD_INPUT(ScalarMaterialMode, (0));
	ScalarMaterialMode.setValue(aDataSetMapper->GetScalarMaterialMode());

	SO_ENGINE_ADD_INPUT(LookupTable, (0));

	SO_ENGINE_ADD_INPUT(ScalarVisibility, (0));
	ScalarVisibility.setValue(aDataSetMapper->GetScalarVisibility());

	SO_ENGINE_ADD_INPUT(InterpolateScalarsBeforeMapping, (0));
	InterpolateScalarsBeforeMapping.setValue(aDataSetMapper->GetInterpolateScalarsBeforeMapping());

	SO_ENGINE_ADD_INPUT(Static, (0));
	Static.setValue(aDataSetMapper->GetStatic());

	SO_ENGINE_ADD_INPUT(RenderTime, (0));
	SO_ENGINE_ADD_INPUT(ColorMode, (0));
	ColorMode.setValue(aDataSetMapper->GetColorMode());

	aDataSetMapper->Delete();


	SO_ENGINE_ADD_OUTPUT( oClippingPlanes, SoSFVtkObject );
	mClippingPlanes = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oLookupTable, SoSFVtkObject );
	mLookupTable = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkDataSetMapper::~SoVtkDataSetMapper()
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
	
	if ( mLookupTable )
	{
	
		mLookupTable->unref();
		mLookupTable = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkDataSetMapper::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDataSetMapper, SoEngine, "Engine" );
}

void SoVtkDataSetMapper::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataSet"))
			mObject->SetInput(vtkDataSet::SafeDownCast(inputPtr->getPointer()));

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
		
		if ( mLookupTable )
		{
		
			mLookupTable->unref();
			mLookupTable = 0;
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

		mObject->GetLookupTable();
		mLookupTable = new SoVtkObject();
		mLookupTable->ref();
		mLookupTable->setPointer( mObject->GetLookupTable() );

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
	SO_ENGINE_OUTPUT( oLookupTable, SoSFVtkObject, setValue( mLookupTable ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkDataSetMapper::inputChanged(SoField * f)
{
	// Get the ScalarRange value
	if ( f == &ScalarRange )
		SO_VTK_SET_FIELD_VEC2F( mObject, ScalarRange);

	// Get the ResolveCoincidentTopology value
	if ( f == &ResolveCoincidentTopology )
		SO_VTK_SET_FIELD_VALUE( mObject, ResolveCoincidentTopology);

	// Get the ImmediateModeRendering value
	if ( f == &ImmediateModeRendering )
		SO_VTK_SET_FIELD_VALUE( mObject, ImmediateModeRendering);

	// Get the ScalarMode value
	if ( f == &ScalarMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMode);

	// Get the GlobalImmediateModeRendering value
	if ( f == &GlobalImmediateModeRendering )
		SO_VTK_SET_FIELD_VALUE( mObject, GlobalImmediateModeRendering);

	// Get the ClippingPlanes value
	if ( f == &ClippingPlanes )
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlaneCollection);

	// Get the ResolveCoincidentTopologyZShift value
	if ( f == &ResolveCoincidentTopologyZShift )
		SO_VTK_SET_FIELD_VALUE( mObject, ResolveCoincidentTopologyZShift);

	// Get the UseLookupTableScalarRange value
	if ( f == &UseLookupTableScalarRange )
		SO_VTK_SET_FIELD_VALUE( mObject, UseLookupTableScalarRange);

	// Get the ScalarMaterialMode value
	if ( f == &ScalarMaterialMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMaterialMode);

	// Get the LookupTable value
	if ( f == &LookupTable )
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkScalarsToColors);

	// Get the ScalarVisibility value
	if ( f == &ScalarVisibility )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarVisibility);

	// Get the InterpolateScalarsBeforeMapping value
	if ( f == &InterpolateScalarsBeforeMapping )
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolateScalarsBeforeMapping);

	// Get the Static value
	if ( f == &Static )
		SO_VTK_SET_FIELD_VALUE( mObject, Static);

	// Get the RenderTime value
	if ( f == &RenderTime )
		SO_VTK_SET_FIELD_VALUE( mObject, RenderTime);

	// Get the ColorMode value
	if ( f == &ColorMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorMode);

	mObject->Update();
}

void SoVtkDataSetMapper::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDataSetMapper::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkDataSet"))
		mObject->SetInput(vtkDataSet::SafeDownCast(inputPtr->getPointer()));

	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ScalarRange value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ScalarRange);

	// Get the ResolveCoincidentTopology value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ResolveCoincidentTopology);

	// Get the ImmediateModeRendering value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ImmediateModeRendering);

	// Get the ScalarMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMode);

	// Get the GlobalImmediateModeRendering value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GlobalImmediateModeRendering);

	// Get the ClippingPlanes value
	
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlaneCollection);

	// Get the ResolveCoincidentTopologyZShift value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ResolveCoincidentTopologyZShift);

	// Get the UseLookupTableScalarRange value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UseLookupTableScalarRange);

	// Get the ScalarMaterialMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMaterialMode);

	// Get the LookupTable value
	
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkScalarsToColors);

	// Get the ScalarVisibility value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarVisibility);

	// Get the InterpolateScalarsBeforeMapping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolateScalarsBeforeMapping);

	// Get the Static value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Static);

	// Get the RenderTime value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RenderTime);

	// Get the ColorMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ColorMode);

	mObject->Update();
}
