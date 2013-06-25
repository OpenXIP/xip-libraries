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

# ifndef SO_VTK_PROPERTY_H_
# define SO_VTK_PROPERTY_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkProperty.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFVec3f.h"
# include <xip/inventor/core/SoSFVariant.h>

class SoVtkProperty : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkProperty );

public:

	/// Constructor
	SoVtkProperty();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Representation
	SoSFInt32 Representation;
	/// Diffuse
	SoSFFloat Diffuse;
	/// AmbientColor
	SoSFVec3f AmbientColor;
	/// Color
	SoSFVariant Color;
	/// FrontfaceCulling
	SoSFInt32 FrontfaceCulling;
	/// BackfaceCulling
	SoSFInt32 BackfaceCulling;
	/// EdgeVisibility
	SoSFInt32 EdgeVisibility;
	/// Opacity
	SoSFFloat Opacity;
	/// DiffuseColor
	SoSFVec3f DiffuseColor;
	/// Interpolation
	SoSFInt32 Interpolation;
	/// Ambient
	SoSFFloat Ambient;
	/// LineWidth
	SoSFFloat LineWidth;
	/// LineStipplePattern
	SoSFInt32 LineStipplePattern;
	/// Specular
	SoSFFloat Specular;
	/// SpecularColor
	SoSFVec3f SpecularColor;
	/// LineStippleRepeatFactor
	SoSFInt32 LineStippleRepeatFactor;
	/// SpecularPower
	SoSFFloat SpecularPower;
	/// EdgeColor
	SoSFVec3f EdgeColor;
	/// PointSize
	SoSFFloat PointSize;

	
	// Outputs
	/// SoSFVtkObject of type vtkProperty
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkProperty();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkProperty
	SoVtkObject *mOutput;

private:

	vtkProperty* mObject;
};

#endif // SO_VTK_PROPERTY_H_

