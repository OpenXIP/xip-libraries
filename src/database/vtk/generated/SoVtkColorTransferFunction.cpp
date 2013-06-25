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

# include "SoVtkColorTransferFunction.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkColorTransferFunction )

SoVtkColorTransferFunction::SoVtkColorTransferFunction()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkColorTransferFunction);

	mObject = vtkColorTransferFunction::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkColorTransferFunction *aColorTransferFunction = vtkColorTransferFunction::New();

	SO_ENGINE_ADD_INPUT(RGBSegment, ());
	RGBSegment.setFormat("double double double double double double double double");

	SO_ENGINE_ADD_INPUT(HSVWrap, (0));
	HSVWrap.setValue(aColorTransferFunction->GetHSVWrap());

	SO_ENGINE_ADD_INPUT(VectorComponent, (0));
	VectorComponent.setValue(aColorTransferFunction->GetVectorComponent());

	SO_ENGINE_ADD_INPUT(ColorSpace, (0));
	ColorSpace.setValue(aColorTransferFunction->GetColorSpace());

	SO_ENGINE_ADD_INPUT(Clamping, (0));
	Clamping.setValue(aColorTransferFunction->GetClamping());

	SO_ENGINE_ADD_INPUT(HSVSegment, ());
	HSVSegment.setFormat("double double double double double double double double");

	SO_ENGINE_ADD_INPUT(RGBPoint, ());
	RGBPoint.setFormat("double double double double");

	SO_ENGINE_ADD_INPUT(HSVPoint, ());
	HSVPoint.setFormat("double double double double");

	SO_ENGINE_ADD_INPUT(VectorMode, (0));
	VectorMode.setValue(aColorTransferFunction->GetVectorMode());

	SO_ENGINE_ADD_INPUT(Alpha, (0));
	Alpha.setValue(aColorTransferFunction->GetAlpha());

	aColorTransferFunction->Delete();

	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;
}

SoVtkColorTransferFunction::~SoVtkColorTransferFunction()
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

void SoVtkColorTransferFunction::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkColorTransferFunction, SoEngine, "Engine" );
}

void SoVtkColorTransferFunction::evaluate()
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


void SoVtkColorTransferFunction::inputChanged(SoField * f)
{
	// Get the RGBSegment value
	if ( f == &RGBSegment )
	{
		SbVariant *vRGBSegment = (SbVariant *)RGBSegment.getValues(0);
		SoInput input;
		int nb_fields = RGBSegment.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vRGBSegment[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			mObject->AddRGBSegment( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7
			);
		}
	}

	// Get the HSVWrap value
	if ( f == &HSVWrap )
		SO_VTK_SET_FIELD_VALUE( mObject, HSVWrap);

	// Get the VectorComponent value
	if ( f == &VectorComponent )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorComponent);

	// Get the ColorSpace value
	if ( f == &ColorSpace )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorSpace);

	// Get the Clamping value
	if ( f == &Clamping )
		SO_VTK_SET_FIELD_VALUE( mObject, Clamping);

	// Get the HSVSegment value
	if ( f == &HSVSegment )
	{
		SbVariant *vHSVSegment = (SbVariant *)HSVSegment.getValues(0);
		SoInput input;
		int nb_fields = HSVSegment.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vHSVSegment[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			mObject->AddHSVSegment( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7
			);
		}
	}

	// Get the RGBPoint value
	if ( f == &RGBPoint )
	{
		SbVariant *vRGBPoint = (SbVariant *)RGBPoint.getValues(0);
		SoInput input;
		int nb_fields = RGBPoint.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vRGBPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->AddRGBPoint( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the HSVPoint value
	if ( f == &HSVPoint )
	{
		SbVariant *vHSVPoint = (SbVariant *)HSVPoint.getValues(0);
		SoInput input;
		int nb_fields = HSVPoint.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vHSVPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->AddHSVPoint( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the VectorMode value
	if ( f == &VectorMode )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorMode);

	// Get the Alpha value
	if ( f == &Alpha )
		SO_VTK_SET_FIELD_VALUE( mObject, Alpha);

	
}

