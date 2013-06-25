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

# ifndef SO_VTK_TUBEFILTER_H_
# define SO_VTK_TUBEFILTER_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkTubeFilter.h"

# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFInt32.h"
# include <xip/inventor/core/SoSFVariant.h>
# include "Inventor/fields/SoSFVec3f.h"

class SoVtkTubeFilter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkTubeFilter );

public:

	/// Constructor
	SoVtkTubeFilter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Radius
	SoSFFloat Radius;
	/// RadiusFactor
	SoSFFloat RadiusFactor;
	/// OnRatio
	SoSFInt32 OnRatio;
	/// SidesShareVertices
	SoSFInt32 SidesShareVertices;
	/// VaryRadius
	SoSFInt32 VaryRadius;
	/// TextureLength
	SoSFFloat TextureLength;
	/// NumberOfSides
	SoSFInt32 NumberOfSides;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input data of type vtkDataObject
	SoSFVtkObject Input;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// DefaultNormal
	SoSFVec3f DefaultNormal;
	/// Offset
	SoSFInt32 Offset;
	/// UseDefaultNormal
	SoSFInt32 UseDefaultNormal;
	/// GenerateTCoords
	SoSFInt32 GenerateTCoords;
	/// Capping
	SoSFInt32 Capping;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkTubeFilter();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkPolyData
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

private:

	vtkTubeFilter* mObject;
};

#endif // SO_VTK_TUBEFILTER_H_

