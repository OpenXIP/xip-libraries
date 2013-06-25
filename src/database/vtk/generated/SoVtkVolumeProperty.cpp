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

# include "SoVtkVolumeProperty.h"
# include "SoVtkUtils.h"

# include "vtkPiecewiseFunction.h"
# include "vtkColorTransferFunction.h"


SO_ENGINE_SOURCE( SoVtkVolumeProperty )

SoVtkVolumeProperty::SoVtkVolumeProperty()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkVolumeProperty);

	mObject = vtkVolumeProperty::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkVolumeProperty *aVolumeProperty = vtkVolumeProperty::New();

	SO_ENGINE_ADD_INPUT(Ambient, (0));
	Ambient.setValue(aVolumeProperty->GetAmbient());

	SO_ENGINE_ADD_INPUT(Shade, (0));
	Shade.setValue(aVolumeProperty->GetShade());

	SO_ENGINE_ADD_INPUT(InterpolationType, (0));
	InterpolationType.setValue(aVolumeProperty->GetInterpolationType());

	SO_ENGINE_ADD_INPUT(ScalarOpacity, (0));

	SO_ENGINE_ADD_INPUT(Diffuse, (0));
	Diffuse.setValue(aVolumeProperty->GetDiffuse());

	SO_ENGINE_ADD_INPUT(Specular, (0));
	Specular.setValue(aVolumeProperty->GetSpecular());

	SO_ENGINE_ADD_INPUT(GradientOpacity, (0));

	SO_ENGINE_ADD_INPUT(IndependentComponents, (0));
	IndependentComponents.setValue(aVolumeProperty->GetIndependentComponents());

	SO_ENGINE_ADD_INPUT(Color, (0));

	SO_ENGINE_ADD_INPUT(SpecularPower, (0));
	SpecularPower.setValue(aVolumeProperty->GetSpecularPower());

	SO_ENGINE_ADD_INPUT(ScalarOpacityUnitDistance, (0));
	ScalarOpacityUnitDistance.setValue(aVolumeProperty->GetScalarOpacityUnitDistance());

	SO_ENGINE_ADD_INPUT(DisableGradientOpacity, (0));
	DisableGradientOpacity.setValue(aVolumeProperty->GetDisableGradientOpacity());

	aVolumeProperty->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkVolumeProperty::~SoVtkVolumeProperty()
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

void SoVtkVolumeProperty::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkVolumeProperty, SoEngine, "Engine" );
}

void SoVtkVolumeProperty::evaluate()
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


void SoVtkVolumeProperty::inputChanged(SoField * f)
{
	// Get the Ambient value
	if ( f == &Ambient )
		SO_VTK_SET_FIELD_VALUE( mObject, Ambient);

	// Get the Shade value
	if ( f == &Shade )
		SO_VTK_SET_FIELD_VALUE( mObject, Shade);

	// Get the InterpolationType value
	if ( f == &InterpolationType )
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolationType);

	// Get the ScalarOpacity value
	if ( f == &ScalarOpacity )
		SO_VTK_SET_FIELD_DATA( mObject, ScalarOpacity, vtkPiecewiseFunction);

	// Get the Diffuse value
	if ( f == &Diffuse )
		SO_VTK_SET_FIELD_VALUE( mObject, Diffuse);

	// Get the Specular value
	if ( f == &Specular )
		SO_VTK_SET_FIELD_VALUE( mObject, Specular);

	// Get the GradientOpacity value
	if ( f == &GradientOpacity )
		SO_VTK_SET_FIELD_DATA( mObject, GradientOpacity, vtkPiecewiseFunction);

	// Get the IndependentComponents value
	if ( f == &IndependentComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, IndependentComponents);

	// Get the Color value
	if ( f == &Color )
		SO_VTK_SET_FIELD_DATA( mObject, Color, vtkColorTransferFunction);

	// Get the SpecularPower value
	if ( f == &SpecularPower )
		SO_VTK_SET_FIELD_VALUE( mObject, SpecularPower);

	// Get the ScalarOpacityUnitDistance value
	if ( f == &ScalarOpacityUnitDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarOpacityUnitDistance);

	// Get the DisableGradientOpacity value
	if ( f == &DisableGradientOpacity )
		SO_VTK_SET_FIELD_VALUE( mObject, DisableGradientOpacity);

	
}

