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

# include "SoVtkProperty.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkProperty )

SoVtkProperty::SoVtkProperty()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkProperty);

	mObject = vtkProperty::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkProperty *aProperty = vtkProperty::New();
	double *x;

	SO_ENGINE_ADD_INPUT(Representation, (0));
	Representation.setValue(aProperty->GetRepresentation());

	SO_ENGINE_ADD_INPUT(Diffuse, (0));
	Diffuse.setValue(aProperty->GetDiffuse());

	SO_ENGINE_ADD_INPUT(AmbientColor, (0,0,0));

	x= aProperty->GetAmbientColor();
	AmbientColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Color, ());
	Color.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(FrontfaceCulling, (0));
	FrontfaceCulling.setValue(aProperty->GetFrontfaceCulling());

	SO_ENGINE_ADD_INPUT(BackfaceCulling, (0));
	BackfaceCulling.setValue(aProperty->GetBackfaceCulling());

	SO_ENGINE_ADD_INPUT(EdgeVisibility, (0));
	EdgeVisibility.setValue(aProperty->GetEdgeVisibility());

	SO_ENGINE_ADD_INPUT(Opacity, (0));
	Opacity.setValue(aProperty->GetOpacity());

	SO_ENGINE_ADD_INPUT(DiffuseColor, (0,0,0));

	x= aProperty->GetDiffuseColor();
	DiffuseColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Interpolation, (0));
	Interpolation.setValue(aProperty->GetInterpolation());

	SO_ENGINE_ADD_INPUT(Ambient, (0));
	Ambient.setValue(aProperty->GetAmbient());

	SO_ENGINE_ADD_INPUT(LineWidth, (0));
	LineWidth.setValue(aProperty->GetLineWidth());

	SO_ENGINE_ADD_INPUT(LineStipplePattern, (0));
	LineStipplePattern.setValue(aProperty->GetLineStipplePattern());

	SO_ENGINE_ADD_INPUT(Specular, (0));
	Specular.setValue(aProperty->GetSpecular());

	SO_ENGINE_ADD_INPUT(SpecularColor, (0,0,0));

	x= aProperty->GetSpecularColor();
	SpecularColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(LineStippleRepeatFactor, (0));
	LineStippleRepeatFactor.setValue(aProperty->GetLineStippleRepeatFactor());

	SO_ENGINE_ADD_INPUT(SpecularPower, (0));
	SpecularPower.setValue(aProperty->GetSpecularPower());

	SO_ENGINE_ADD_INPUT(EdgeColor, (0,0,0));

	x= aProperty->GetEdgeColor();
	EdgeColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(PointSize, (0));
	PointSize.setValue(aProperty->GetPointSize());

	aProperty->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkProperty::~SoVtkProperty()
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

void SoVtkProperty::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkProperty, SoEngine, "Engine" );
}

void SoVtkProperty::evaluate()
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


void SoVtkProperty::inputChanged(SoField * f)
{
	// Get the Representation value
	if ( f == &Representation )
		SO_VTK_SET_FIELD_VALUE( mObject, Representation);

	// Get the Diffuse value
	if ( f == &Diffuse )
		SO_VTK_SET_FIELD_VALUE( mObject, Diffuse);

	// Get the AmbientColor value
	if ( f == &AmbientColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, AmbientColor);

	// Get the Color value
	if ( f == &Color )
	{
		SbVariant vColor = (SbVariant)Color.getValue();
		SoInput input;
		double val0;
		double val1;
		double val2;
	
		input.setBuffer((void *)vColor.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		mObject->SetColor( 
			(double) val0,
			(double) val1,
			(double) val2
		);
	}
	// Get the FrontfaceCulling value
	if ( f == &FrontfaceCulling )
		SO_VTK_SET_FIELD_VALUE( mObject, FrontfaceCulling);

	// Get the BackfaceCulling value
	if ( f == &BackfaceCulling )
		SO_VTK_SET_FIELD_VALUE( mObject, BackfaceCulling);

	// Get the EdgeVisibility value
	if ( f == &EdgeVisibility )
		SO_VTK_SET_FIELD_VALUE( mObject, EdgeVisibility);

	// Get the Opacity value
	if ( f == &Opacity )
		SO_VTK_SET_FIELD_VALUE( mObject, Opacity);

	// Get the DiffuseColor value
	if ( f == &DiffuseColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, DiffuseColor);

	// Get the Interpolation value
	if ( f == &Interpolation )
		SO_VTK_SET_FIELD_VALUE( mObject, Interpolation);

	// Get the Ambient value
	if ( f == &Ambient )
		SO_VTK_SET_FIELD_VALUE( mObject, Ambient);

	// Get the LineWidth value
	if ( f == &LineWidth )
		SO_VTK_SET_FIELD_VALUE( mObject, LineWidth);

	// Get the LineStipplePattern value
	if ( f == &LineStipplePattern )
		SO_VTK_SET_FIELD_VALUE( mObject, LineStipplePattern);

	// Get the Specular value
	if ( f == &Specular )
		SO_VTK_SET_FIELD_VALUE( mObject, Specular);

	// Get the SpecularColor value
	if ( f == &SpecularColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, SpecularColor);

	// Get the LineStippleRepeatFactor value
	if ( f == &LineStippleRepeatFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, LineStippleRepeatFactor);

	// Get the SpecularPower value
	if ( f == &SpecularPower )
		SO_VTK_SET_FIELD_VALUE( mObject, SpecularPower);

	// Get the EdgeColor value
	if ( f == &EdgeColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, EdgeColor);

	// Get the PointSize value
	if ( f == &PointSize )
		SO_VTK_SET_FIELD_VALUE( mObject, PointSize);

	
}

