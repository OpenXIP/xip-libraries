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
/*
 * \brief
 * \author Sylvain Jaume, Francois Huguet
 */

# include "SoVtkPolyDataMapper.h"
# include "SoVtkUtils.h"

# include "vtkPlanes.h"
# include "vtkPolyData.h"
# include "vtkAlgorithmOutput.h"
# include "vtkScalarsToColors.h"


SO_ENGINE_SOURCE( SoVtkPolyDataMapper )

SoVtkPolyDataMapper::SoVtkPolyDataMapper()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkPolyDataMapper);

	mObject = vtkPolyDataMapper::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	mObject->GlobalWarningDisplayOff();

	vtkPolyDataMapper *aPolyDataMapper = vtkPolyDataMapper::New();
	double *x;

	SO_ENGINE_ADD_INPUT(ScalarRange, (0,0));

	x= aPolyDataMapper->GetScalarRange();
	ScalarRange.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(ResolveCoincidentTopology, (0));
	ResolveCoincidentTopology.setValue(aPolyDataMapper->GetResolveCoincidentTopology());

	SO_ENGINE_ADD_INPUT(ImmediateModeRendering, (0));
	ImmediateModeRendering.setValue(aPolyDataMapper->GetImmediateModeRendering());

	SO_ENGINE_ADD_INPUT(ScalarMode, (0));
	ScalarMode.setValue(aPolyDataMapper->GetScalarMode());

	SO_ENGINE_ADD_INPUT(GlobalImmediateModeRendering, (0));
	GlobalImmediateModeRendering.setValue(aPolyDataMapper->GetGlobalImmediateModeRendering());

	SO_ENGINE_ADD_INPUT(ClippingPlanes, (0));

	SO_ENGINE_ADD_INPUT(ResolveCoincidentTopologyZShift, (0));
	ResolveCoincidentTopologyZShift.setValue(aPolyDataMapper->GetResolveCoincidentTopologyZShift());

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(NumberOfSubPieces, (0));
	NumberOfSubPieces.setValue(aPolyDataMapper->GetNumberOfSubPieces());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(GhostLevel, (0));
	GhostLevel.setValue(aPolyDataMapper->GetGhostLevel());

	SO_ENGINE_ADD_INPUT(UseLookupTableScalarRange, (0));
	UseLookupTableScalarRange.setValue(aPolyDataMapper->GetUseLookupTableScalarRange());

	SO_ENGINE_ADD_INPUT(ScalarMaterialMode, (0));
	ScalarMaterialMode.setValue(aPolyDataMapper->GetScalarMaterialMode());

	SO_ENGINE_ADD_INPUT(NumberOfPieces, (0));
	NumberOfPieces.setValue(aPolyDataMapper->GetNumberOfPieces());

	SO_ENGINE_ADD_INPUT(Piece, (0));
	Piece.setValue(aPolyDataMapper->GetPiece());

	SO_ENGINE_ADD_INPUT(LookupTable, (0));

	SO_ENGINE_ADD_INPUT(ScalarVisibility, (0));
	ScalarVisibility.setValue(aPolyDataMapper->GetScalarVisibility());

	SO_ENGINE_ADD_INPUT(InterpolateScalarsBeforeMapping, (0));
	InterpolateScalarsBeforeMapping.setValue(aPolyDataMapper->GetInterpolateScalarsBeforeMapping());

	SO_ENGINE_ADD_INPUT(Static, (0));
	Static.setValue(aPolyDataMapper->GetStatic());

	SO_ENGINE_ADD_INPUT(RenderTime, (0));
	RenderTime.setValue(aPolyDataMapper->GetRenderTime());

	SO_ENGINE_ADD_INPUT(ColorMode, (0));
	ColorMode.setValue(aPolyDataMapper->GetColorMode());

	aPolyDataMapper->Delete();


	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkPolyDataMapper::~SoVtkPolyDataMapper()
{
	// Deletion of the objects if they exist
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
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

void SoVtkPolyDataMapper::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkPolyDataMapper, SoEngine, "Engine" );
}

void SoVtkPolyDataMapper::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkPolyData"))
			mObject->SetInput(vtkPolyData::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

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
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkPolyDataMapper::inputChanged(SoField * f)
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
		SO_VTK_SET_FIELD_DATA( mObject, ClippingPlanes, vtkPlanes);

	// Get the ResolveCoincidentTopologyZShift value
	if ( f == &ResolveCoincidentTopologyZShift )
		SO_VTK_SET_FIELD_VALUE( mObject, ResolveCoincidentTopologyZShift);

	// Get the InputArrayToProcess value
	if ( f == &InputArrayToProcess )
	{
		SbVariant vInputArrayToProcess = (SbVariant)InputArrayToProcess.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		SbString val4;
	
		input.setBuffer((void *)vInputArrayToProcess.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		mObject->SetInputArrayToProcess( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			val4.getString()
		);
	}
	// Get the NumberOfSubPieces value
	if ( f == &NumberOfSubPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfSubPieces);

	// Get the GhostLevel value
	if ( f == &GhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the UseLookupTableScalarRange value
	if ( f == &UseLookupTableScalarRange )
		SO_VTK_SET_FIELD_VALUE( mObject, UseLookupTableScalarRange);

	// Get the ScalarMaterialMode value
	if ( f == &ScalarMaterialMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMaterialMode);

	// Get the NumberOfPieces value
	if ( f == &NumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfPieces);

	// Get the Piece value
	if ( f == &Piece )
		SO_VTK_SET_FIELD_VALUE( mObject, Piece);

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

	//mObject->Update();
	
}

