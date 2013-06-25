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
 
 
 
# ifndef SO_VTK_IMAGEMARCHINGCUBES_H_
# define SO_VTK_IMAGEMARCHINGCUBES_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImageMarchingCubes.h"

# include "Inventor/fields/SoSFInt32.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"

class SoVtkImageMarchingCubes : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageMarchingCubes );

public:

	/// Constructor
	SoVtkImageMarchingCubes();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// NumberOfContours
	SoSFInt32 NumberOfContours;
	/// Value
	SoMFVariant Value;
	/// LocatorPoint
	SoMFVariant LocatorPoint;
	/// ComputeScalars
	SoSFInt32 ComputeScalars;
	/// ComputeGradients
	SoSFInt32 ComputeGradients;
	/// ComputeNormals
	SoSFInt32 ComputeNormals;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// InputMemoryLimit
	SoSFInt32 InputMemoryLimit;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkImageMarchingCubes();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkPolyData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkImageMarchingCubes* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMAGEMARCHINGCUBES_H_

