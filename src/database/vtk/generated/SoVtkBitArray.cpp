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
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */

#include "SoVtkBitArray.h"
#include "SoVtkUtils.h"

#include "vtkLookupTable.h"

SO_ENGINE_SOURCE( SoVtkBitArray )

SoVtkBitArray::SoVtkBitArray()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBitArray);

	mObject = vtkBitArray::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBitArray *aBitArray = vtkBitArray::New();

	SO_ENGINE_ADD_INPUT(Value, ());
	Value.setFormat("vtkIdType int");

	SO_ENGINE_ADD_INPUT(Tuple1, ());
	Tuple1.setFormat("vtkIdType double");

	SO_ENGINE_ADD_INPUT(NumberOfComponents, (0));
	NumberOfComponents.setValue(aBitArray->GetNumberOfComponents());

	SO_ENGINE_ADD_INPUT(Tuple9, ());
	Tuple9.setFormat(
	"vtkIdType double double double double double double double double double");

	SO_ENGINE_ADD_INPUT(LookupTable, (0));

	SO_ENGINE_ADD_INPUT(Component, ());
	Component.setFormat("vtkIdType int double");

	SO_ENGINE_ADD_INPUT(Tuple3, ());
	Tuple3.setFormat("vtkIdType double double double");

	SO_ENGINE_ADD_INPUT(Tuple2, ());
	Tuple2.setFormat("vtkIdType double double");

	SO_ENGINE_ADD_INPUT(Name, (""));

	SO_ENGINE_ADD_INPUT(Tuple4, ());
	Tuple4.setFormat("vtkIdType double double double double");

	aBitArray->Delete();

	SO_ENGINE_ADD_OUTPUT( oLookupTable, SoSFVtkObject );
	mLookupTable = 0;

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	addCalled = 0;
}

SoVtkBitArray::~SoVtkBitArray()
{
	// Deletion of the objects if they exist
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

void SoVtkBitArray::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBitArray, SoEngine, "Engine" );
}

void SoVtkBitArray::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
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

	SO_ENGINE_OUTPUT( oLookupTable, SoSFVtkObject, setValue( mLookupTable ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkBitArray::inputChanged(SoField * f)
{
	// Get the Value value
	if ( f == &Value )
	{
		SbVariant *vValue = (SbVariant *)Value.getValues(0);
		SoInput input;
		int nb_fields = Value.getNum();

		vtkIdType val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vValue[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetValue( 
				(vtkIdType) val0,
				(int) val1
			);
		}
	}

	// Get the Tuple1 value
	if ( f == &Tuple1 )
	{
		SbVariant *vTuple1 = (SbVariant *)Tuple1.getValues(0);
		SoInput input;
		int nb_fields = Tuple1.getNum();

		vtkIdType val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple1[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetTuple1( 
				(vtkIdType) val0,
				(double) val1
			);
		}
	}

	// Get the NumberOfComponents value
	if ( f == &NumberOfComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfComponents);

	// Get the Tuple9 value
	if ( f == &Tuple9 )
	{
		SbVariant *vTuple9 = (SbVariant *)Tuple9.getValues(0);
		SoInput input;
		int nb_fields = Tuple9.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		double val8;
		double val9;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple9[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			input.read(val8);
			input.read(val9);
			mObject->SetTuple9( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7,
				(double) val8,
				(double) val9
			);
		}
	}

	// Get the LookupTable value
	if ( f == &LookupTable )
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkLookupTable);

	// Get the Component value
	if ( f == &Component )
	{
		SbVariant *vComponent = (SbVariant *)Component.getValues(0);
		SoInput input;
		int nb_fields = Component.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetComponent( 
				(vtkIdType) val0,
				(int) val1,
				(double) val2
			);
		}
	}

	// Get the Tuple3 value
	if ( f == &Tuple3 )
	{
		SbVariant *vTuple3 = (SbVariant *)Tuple3.getValues(0);
		SoInput input;
		int nb_fields = Tuple3.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple3[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->SetTuple3( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the Tuple2 value
	if ( f == &Tuple2 )
	{
		SbVariant *vTuple2 = (SbVariant *)Tuple2.getValues(0);
		SoInput input;
		int nb_fields = Tuple2.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple2[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetTuple2( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Name value
	if ( f == &Name )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Name);

	// Get the Tuple4 value
	if ( f == &Tuple4 )
	{
		SbVariant *vTuple4 = (SbVariant *)Tuple4.getValues(0);
		SoInput input;
		int nb_fields = Tuple4.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		double val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple4[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetTuple4( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4
			);
		}
	}

}

void SoVtkBitArray::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBitArray::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the Value value
	if (addCalled == 1)
	{
		SbVariant *vValue = (SbVariant *)Value.getValues(0);
		SoInput input;
		int nb_fields = Value.getNum();

		vtkIdType val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vValue[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetValue( 
				(vtkIdType) val0,
				(int) val1
			);
		}
	}

	// Get the Tuple1 value
	if (addCalled == 1)
	{
		SbVariant *vTuple1 = (SbVariant *)Tuple1.getValues(0);
		SoInput input;
		int nb_fields = Tuple1.getNum();

		vtkIdType val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple1[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetTuple1( 
				(vtkIdType) val0,
				(double) val1
			);
		}
	}

	// Get the NumberOfComponents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfComponents);

	// Get the Tuple9 value
	if (addCalled == 1)
	{
		SbVariant *vTuple9 = (SbVariant *)Tuple9.getValues(0);
		SoInput input;
		int nb_fields = Tuple9.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		double val8;
		double val9;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple9[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			input.read(val8);
			input.read(val9);
			mObject->SetTuple9( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7,
				(double) val8,
				(double) val9
			);
		}
	}

	// Get the LookupTable value
	
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkLookupTable);

	// Get the Component value
	if (addCalled == 1)
	{
		SbVariant *vComponent = (SbVariant *)Component.getValues(0);
		SoInput input;
		int nb_fields = Component.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetComponent( 
				(vtkIdType) val0,
				(int) val1,
				(double) val2
			);
		}
	}

	// Get the Tuple3 value
	if (addCalled == 1)
	{
		SbVariant *vTuple3 = (SbVariant *)Tuple3.getValues(0);
		SoInput input;
		int nb_fields = Tuple3.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple3[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->SetTuple3( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the Tuple2 value
	if (addCalled == 1)
	{
		SbVariant *vTuple2 = (SbVariant *)Tuple2.getValues(0);
		SoInput input;
		int nb_fields = Tuple2.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple2[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetTuple2( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Name value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Name);

	// Get the Tuple4 value
	if (addCalled == 1)
	{
		SbVariant *vTuple4 = (SbVariant *)Tuple4.getValues(0);
		SoInput input;
		int nb_fields = Tuple4.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		double val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple4[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetTuple4( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4
			);
		}
	}

}

