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
 
 
 
# ifndef SO_VTK_EXODUSREADER_H_
# define SO_VTK_EXODUSREADER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkExodusReader.h"

# include "Inventor/fields/SoSFEnum.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"
# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFString.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFVec2f.h"

class SoVtkExodusReader : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkExodusReader );

public:
	enum ArrayType
	{
		BLOCK,
		POINT,
		CELL,
		NUM_ARRAY_TYPES,
		HIERARCHY,
		ASSEMBLY,
		PART,
		UNKNOWN_TYPE,
		MATERIAL
	};
	

	/// Constructor
	SoVtkExodusReader();

	/// Class Initialization
	static void initClass();
	/// Enum ArrayTypeEnum
	SoSFEnum ArrayTypeEnum;
	
	// Inputs
	/// NodeSetArrayStatus
	SoMFVariant NodeSetArrayStatus;
	/// ApplyDisplacements
	SoSFInt32 ApplyDisplacements;
	/// CellArrayStatus
	SoMFVariant CellArrayStatus;
	/// FilterOutputVar
	SoMFString FilterOutputVar;
	/// GenerateGlobalNodeIdArray
	SoSFInt32 GenerateGlobalNodeIdArray;
	/// AllPartArrayStatus
	SoSFInt32 AllPartArrayStatus;
	/// XMLFileName
	SoMFString XMLFileName;
	/// PartArrayStatus
	SoMFVariant PartArrayStatus;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// FilterDenominatorWeight
	SoSFFloat FilterDenominatorWeight;
	/// AllAssemblyArrayStatus
	SoSFInt32 AllAssemblyArrayStatus;
	/// MaterialArrayStatus
	SoMFVariant MaterialArrayStatus;
	/// ExodusModelMetadata
	SoSFInt32 ExodusModelMetadata;
	/// AssemblyArrayStatus
	SoMFVariant AssemblyArrayStatus;
	/// PointArrayStatus
	SoMFVariant PointArrayStatus;
	/// FileName
	SoMFString FileName;
	/// HierarchyArrayStatus
	SoMFVariant HierarchyArrayStatus;
	/// SideSetArrayStatus
	SoMFVariant SideSetArrayStatus;
	/// FilterInputVar
	SoMFString FilterInputVar;
	/// DisplacementMagnitude
	SoSFFloat DisplacementMagnitude;
	/// AllPointArrayStatus
	SoSFInt32 AllPointArrayStatus;
	/// BlockArrayStatus
	SoMFVariant BlockArrayStatus;
	/// PackExodusModelOntoOutput
	SoSFInt32 PackExodusModelOntoOutput;
	/// AllBlockArrayStatus
	SoSFInt32 AllBlockArrayStatus;
	/// AllCellArrayStatus
	SoSFInt32 AllCellArrayStatus;
	/// DisplayType
	SoSFInt32 DisplayType;
	/// TimeStep
	SoSFInt32 TimeStep;
	/// FilterNumeratorWeight
	SoSFFloat FilterNumeratorWeight;
	/// GenerateGlobalElementIdArray
	SoSFInt32 GenerateGlobalElementIdArray;
	/// TimeStepRange
	SoSFVec2f TimeStepRange;
	/// GenerateBlockIdCellArray
	SoSFInt32 GenerateBlockIdCellArray;
	/// AllHierarchyArrayStatus
	SoSFInt32 AllHierarchyArrayStatus;
	/// FilterForwardNumeratorWeight
	SoSFFloat FilterForwardNumeratorWeight;
	/// AllMaterialArrayStatus
	SoSFInt32 AllMaterialArrayStatus;

	
	// Outputs
	/// SoSFVtkObject of type vtkUnstructuredGrid
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkExodusReader();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkUnstructuredGrid
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkExodusReader* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_EXODUSREADER_H_

