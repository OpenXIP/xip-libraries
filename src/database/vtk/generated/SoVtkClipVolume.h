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
 
 
 
# ifndef SO_VTK_CLIPVOLUME_H_
# define SO_VTK_CLIPVOLUME_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkClipVolume.h"

# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkClipVolume : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkClipVolume );

public:

	/// Constructor
	SoVtkClipVolume();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Value
	SoSFFloat Value;
	/// InsideOut
	SoSFInt32 InsideOut;
	/// Mixed3DCellGeneration
	SoSFInt32 Mixed3DCellGeneration;
	/// GenerateClippedOutput
	SoSFInt32 GenerateClippedOutput;
	/// Locator of type vtkPointLocator
	SoSFVtkObject Locator;
	/// GenerateClipScalars
	SoSFInt32 GenerateClipScalars;
	/// ClipFunction of type vtkImplicitFunction
	SoSFVtkObject ClipFunction;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// MergeTolerance
	SoSFFloat MergeTolerance;

	
	// Outputs
	/// SoSFVtkObject of type vtkUnstructuredGrid
	SoEngineOutput Output;
	/// SoSFVtkObject of type vtkPointLocator
	SoEngineOutput oLocator;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkImplicitFunction
	SoEngineOutput oClipFunction;
	/// SoSFVtkObject of type vtkUnstructuredGrid
	SoEngineOutput oClippedOutput;

protected:

	/// Destructor
	~SoVtkClipVolume();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkUnstructuredGrid
	SoVtkObject *mOutput;

	/// vtkPointLocator
	SoVtkObject *mLocator;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkImplicitFunction
	SoVtkObject *mClipFunction;

	/// vtkUnstructuredGrid
	SoVtkObject *mClippedOutput;


private:

	vtkClipVolume* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_CLIPVOLUME_H_

