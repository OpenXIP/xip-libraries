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

# include "SoVtkLookupTable.h"
# include "SoVtkUtils.h"

# include "vtkUnsignedCharArray.h"


SO_ENGINE_SOURCE( SoVtkLookupTable )

SoVtkLookupTable::SoVtkLookupTable()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkLookupTable);

	mObject = vtkLookupTable::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkLookupTable *aLookupTable = vtkLookupTable::New();
	double *x;

	SO_ENGINE_ADD_INPUT(VectorComponent, (0));
	VectorComponent.setValue(aLookupTable->GetVectorComponent());

	SO_ENGINE_ADD_INPUT(TableRange, ());
	TableRange.setFormat("double double");

	SO_ENGINE_ADD_INPUT(ValueRange, (0,0));

	x= aLookupTable->GetValueRange();
	ValueRange.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(SaturationRange, (0,0));

	x= aLookupTable->GetSaturationRange();
	SaturationRange.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(Ramp, (0));
	Ramp.setValue(aLookupTable->GetRamp());

	SO_ENGINE_ADD_INPUT(Scale, (0));
	Scale.setValue(aLookupTable->GetScale());

	SO_ENGINE_ADD_INPUT(AlphaRange, (0,0));

	x= aLookupTable->GetAlphaRange();
	AlphaRange.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(Table, (0));

	SO_ENGINE_ADD_INPUT(HueRange, (0,0));

	x= aLookupTable->GetHueRange();
	HueRange.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(VectorMode, (0));
	VectorMode.setValue(aLookupTable->GetVectorMode());

	SO_ENGINE_ADD_INPUT(Alpha, (0));
	Alpha.setValue(aLookupTable->GetAlpha());

	aLookupTable->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkLookupTable::~SoVtkLookupTable()
{
	// Deletion of the objects if they exist
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

void SoVtkLookupTable::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkLookupTable, SoEngine, "Engine" );
}

void SoVtkLookupTable::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		// Get the input type(s)
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkLookupTable::inputChanged(SoField * f)
{
	// Get the VectorComponent value
	if ( f == &VectorComponent )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorComponent);

	// Get the TableRange value
	if ( f == &TableRange )
	{
		SbVariant vTableRange = (SbVariant)TableRange.getValue();
		SoInput input;
		double val0;
		double val1;
	
		input.setBuffer((void *)vTableRange.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		mObject->SetTableRange( 
			(double) val0,
			(double) val1
		);
	}
	// Get the ValueRange value
	if ( f == &ValueRange )
		SO_VTK_SET_FIELD_VEC2F( mObject, ValueRange);

	// Get the SaturationRange value
	if ( f == &SaturationRange )
		SO_VTK_SET_FIELD_VEC2F( mObject, SaturationRange);

	// Get the Ramp value
	if ( f == &Ramp )
		SO_VTK_SET_FIELD_VALUE( mObject, Ramp);

	// Get the Scale value
	if ( f == &Scale )
		SO_VTK_SET_FIELD_VALUE( mObject, Scale);

	// Get the AlphaRange value
	if ( f == &AlphaRange )
		SO_VTK_SET_FIELD_VEC2F( mObject, AlphaRange);

	// Get the Table value
	if ( f == &Table )
		SO_VTK_SET_FIELD_DATA( mObject, Table, vtkUnsignedCharArray);

	// Get the HueRange value
	if ( f == &HueRange )
		SO_VTK_SET_FIELD_VEC2F( mObject, HueRange);

	// Get the VectorMode value
	if ( f == &VectorMode )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorMode);

	// Get the Alpha value
	if ( f == &Alpha )
		SO_VTK_SET_FIELD_VALUE( mObject, Alpha);

	
}

