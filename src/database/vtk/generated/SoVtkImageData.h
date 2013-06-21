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
 
 
 
# ifndef SO_VTK_IMAGEDATA_H_
# define SO_VTK_IMAGEDATA_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImageData.h"

# include "Inventor/fields/SoSFInt32.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"
# include "Inventor/fields/SoSFVec3f.h"

class SoVtkImageData : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageData );

public:

	/// Constructor
	SoVtkImageData();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ExtentTranslator of type vtkExtentTranslator
	SoSFVtkObject ExtentTranslator;
	/// MaximumNumberOfPieces
	SoSFInt32 MaximumNumberOfPieces;
	/// RequestExactExtent
	SoSFInt32 RequestExactExtent;
	/// UpdatePiece
	SoSFInt32 UpdatePiece;
	/// WholeBoundingBox
	SoMFVariant WholeBoundingBox;
	/// UpdateGhostLevel
	SoSFInt32 UpdateGhostLevel;
	/// UpdateNumberOfPieces
	SoSFInt32 UpdateNumberOfPieces;
	/// Origin
	SoSFVec3f Origin;
	/// Source of type vtkSource
	SoSFVtkObject Source;
	/// Extent
	SoMFVariant Extent;
	/// PipelineInformation of type vtkInformation
	SoSFVtkObject PipelineInformation;
	/// FieldData of type vtkFieldData
	SoSFVtkObject FieldData;
	/// ScalarComponentFromFloat
	SoMFVariant ScalarComponentFromFloat;
	/// Dimensions
	SoMFVariant Dimensions;
	/// UpdateExtent
	SoMFVariant UpdateExtent;
	/// NumberOfScalarComponents
	SoSFInt32 NumberOfScalarComponents;
	/// AxisUpdateExtent
	SoMFVariant AxisUpdateExtent;
	/// WholeExtent
	SoMFVariant WholeExtent;
	/// Spacing
	SoSFVec3f Spacing;
	/// ScalarComponentFromDouble
	SoMFVariant ScalarComponentFromDouble;
	/// ScalarType
	SoSFInt32 ScalarType;

	
	// Outputs
	/// SoSFVtkObject of type vtkFieldData
	SoEngineOutput oFieldData;
	/// SoSFVtkObject of type vtkExtentTranslator
	SoEngineOutput oExtentTranslator;
	/// SoSFVtkObject of type vtkSource
	SoEngineOutput oSource;
	/// SoSFVtkObject of type ImageData
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkImageData();

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

	/// vtkImageData
	SoVtkObject *mOutput;


private:

	vtkImageData* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMAGEDATA_H_

