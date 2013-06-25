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

# ifndef SO_VTK_POLYDATANORMALS_H_
# define SO_VTK_POLYDATANORMALS_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkPolyDataNormals.h"

# include "Inventor/fields/SoSFInt32.h"
# include <xip/inventor/core/SoSFVariant.h>
# include "Inventor/fields/SoSFFloat.h"

class SoVtkPolyDataNormals : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkPolyDataNormals );

public:

	/// Constructor
	SoVtkPolyDataNormals();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Splitting
	SoSFInt32 Splitting;
	/// ComputePointNormals
	SoSFInt32 ComputePointNormals;
	/// NonManifoldTraversal
	SoSFInt32 NonManifoldTraversal;
	/// ComputeCellNormals
	SoSFInt32 ComputeCellNormals;
	/// FlipNormals
	SoSFInt32 FlipNormals;
	/// Consistency
	SoSFInt32 Consistency;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input data of type vtkDataObject
	SoSFVtkObject Input;
	/// FeatureAngle
	SoSFFloat FeatureAngle;
	/// AutoOrientNormals
	SoSFInt32 AutoOrientNormals;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkPolyDataNormals();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkPolyData
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

private:

	vtkPolyDataNormals* mObject;
};

#endif // SO_VTK_POLYDATANORMALS_H_

