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

# ifndef SO_VTK_VOLUMEPROPERTY_H_
# define SO_VTK_VOLUMEPROPERTY_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkVolumeProperty.h"

# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkVolumeProperty : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkVolumeProperty );

public:

	/// Constructor
	SoVtkVolumeProperty();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Ambient
	SoSFFloat Ambient;
	/// Shade
	SoSFInt32 Shade;
	/// InterpolationType
	SoSFInt32 InterpolationType;
	/// ScalarOpacity of type vtkPiecewiseFunction
	SoSFVtkObject ScalarOpacity;
	/// Diffuse
	SoSFFloat Diffuse;
	/// Specular
	SoSFFloat Specular;
	/// GradientOpacity of type vtkPiecewiseFunction
	SoSFVtkObject GradientOpacity;
	/// IndependentComponents
	SoSFInt32 IndependentComponents;
	/// Color of type vtkColorTransferFunction
	SoSFVtkObject Color;
	/// SpecularPower
	SoSFFloat SpecularPower;
	/// ScalarOpacityUnitDistance
	SoSFFloat ScalarOpacityUnitDistance;
	/// DisableGradientOpacity
	SoSFInt32 DisableGradientOpacity;

	
	// Outputs
	/// SoSFVtkObject of type vtkVolumeProperty
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkVolumeProperty();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkVolumeProperty
	SoVtkObject *mOutput;

private:

	vtkVolumeProperty* mObject;
};

#endif // SO_VTK_VOLUMEPROPERTY_H_

