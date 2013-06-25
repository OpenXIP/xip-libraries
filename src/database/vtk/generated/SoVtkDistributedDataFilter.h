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
 
 
 
# ifndef SO_VTK_DISTRIBUTEDDATAFILTER_H_
# define SO_VTK_DISTRIBUTEDDATAFILTER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkDistributedDataFilter.h"

# include "Inventor/fields/SoSFEnum.h"
# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFString.h"

class SoVtkDistributedDataFilter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkDistributedDataFilter );

public:
	enum BoundaryModes
	{
		ASSIGN_TO_ALL_INTERSECTING_REGIONS,
		SPLIT_BOUNDARY_CELLS,
		ASSIGN_TO_ONE_REGION
	};
	

	/// Constructor
	SoVtkDistributedDataFilter();

	/// Class Initialization
	static void initClass();
	/// Enum BoundaryModesEnum
	SoSFEnum BoundaryModesEnum;
	
	// Inputs
	/// BoundaryMode
	SoSFInt32 BoundaryMode;
	/// IncludeAllIntersectingCells
	SoSFInt32 IncludeAllIntersectingCells;
	/// Timing
	SoSFInt32 Timing;
	/// RetainKdtree
	SoSFInt32 RetainKdtree;
	/// UseMinimalMemory
	SoSFInt32 UseMinimalMemory;
	/// ClipCells
	SoSFInt32 ClipCells;
	/// GlobalNodeIdArrayName
	//SoMFString GlobalNodeIdArrayName;
	/// GlobalElementIdArrayName
	SoMFString GlobalElementIdArrayName;
	/// Controller of type vtkMultiProcessController
	SoSFVtkObject Controller;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkUnstructuredGrid
	SoEngineOutput Output;
	/// SoSFVtkObject of type vtkPKdTree
	SoEngineOutput oKdtree;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkDistributedDataFilter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkUnstructuredGrid
	SoVtkObject *mOutput;

	/// vtkPKdTree
	SoVtkObject *mKdtree;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkDistributedDataFilter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_DISTRIBUTEDDATAFILTER_H_

