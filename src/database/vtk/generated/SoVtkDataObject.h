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
 
 
 
# ifndef SO_VTK_DATAOBJECT_H_
# define SO_VTK_DATAOBJECT_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkDataObject.h"

# include "Inventor/fields/SoSFEnum.h"
# include "Inventor/fields/SoSFInt32.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"

class SoVtkDataObject : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkDataObject );

public:
	enum FieldAssociations
	{
		FIELD_ASSOCIATION_POINTS,
		FIELD_ASSOCIATION_NONE,
		FIELD_ASSOCIATION_CELLS,
		NUMBER_OF_ASSOCIATIONS,
		FIELD_ASSOCIATION_POINTS_THEN_CELLS
	};
	
	enum FieldOperations
	{
		FIELD_OPERATION_REMOVED,
		FIELD_OPERATION_MODIFIED,
		FIELD_OPERATION_REINTERPOLATED,
		FIELD_OPERATION_PRESERVED
	};
	

	/// Constructor
	SoVtkDataObject();

	/// Class Initialization
	static void initClass();
	/// Enum FieldAssociationsEnum
	SoSFEnum FieldAssociationsEnum;
	/// Enum FieldOperationsEnum
	SoSFEnum FieldOperationsEnum;
	
	// Inputs
	/// FieldData of type vtkFieldData
	SoSFVtkObject FieldData;
	/// ExtentTranslator of type vtkExtentTranslator
	SoSFVtkObject ExtentTranslator;
	/// MaximumNumberOfPieces
	SoSFInt32 MaximumNumberOfPieces;
	/// RequestExactExtent
	SoSFInt32 RequestExactExtent;
	/// UpdatePiece
	SoSFInt32 UpdatePiece;
	/// UpdateExtent
	SoMFVariant UpdateExtent;
	/// WholeBoundingBox
	SoMFVariant WholeBoundingBox;
	/// UpdateGhostLevel
	SoSFInt32 UpdateGhostLevel;
	/// UpdateNumberOfPieces
	SoSFInt32 UpdateNumberOfPieces;
	/// WholeExtent
	SoMFVariant WholeExtent;
	/// Source of type vtkSource
	SoSFVtkObject Source;
	/// PipelineInformation of type vtkInformation
	SoSFVtkObject PipelineInformation;

	
	// Outputs
	/// SoSFVtkObject of type vtkFieldData
	SoEngineOutput oFieldData;
	/// SoSFVtkObject of type vtkExtentTranslator
	SoEngineOutput oExtentTranslator;
	/// SoSFVtkObject of type vtkSource
	SoEngineOutput oSource;
	/// SoSFVtkObject of type DataObject
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkDataObject();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkFieldData
	SoVtkObject *mFieldData;

	/// vtkExtentTranslator
	SoVtkObject *mExtentTranslator;

	/// vtkSource
	SoVtkObject *mSource;

	/// vtkDataObject
	SoVtkObject *mOutput;


private:

	vtkDataObject* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_DATAOBJECT_H_

