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
 
 
 
# ifndef SO_VTK_FEATUREEDGES_H_
# define SO_VTK_FEATUREEDGES_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkFeatureEdges.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"

class SoVtkFeatureEdges : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkFeatureEdges );

public:

	/// Constructor
	SoVtkFeatureEdges();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// NonManifoldEdges
	SoSFInt32 NonManifoldEdges;
	/// FeatureEdges
	SoSFInt32 FeatureEdges;
	/// BoundaryEdges
	SoSFInt32 BoundaryEdges;
	/// Locator of type vtkPointLocator
	SoSFVtkObject Locator;
	/// ManifoldEdges
	SoSFInt32 ManifoldEdges;
	/// FeatureAngle
	SoSFFloat FeatureAngle;
	/// Coloring
	SoSFInt32 Coloring;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkObject of type vtkPointLocator
	SoEngineOutput oLocator;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkFeatureEdges();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkPolyData
	SoVtkObject *mOutput;

	/// vtkPointLocator
	SoVtkObject *mLocator;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkFeatureEdges* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_FEATUREEDGES_H_

