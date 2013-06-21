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

# ifndef SO_VTK_PIECEWISEFUNCTION_H_
# define SO_VTK_PIECEWISEFUNCTION_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkPiecewiseFunction.h"

# include <xip/inventor/core/SoMFVariant.h>
# include "Inventor/fields/SoSFInt32.h"
# include <xip/inventor/core/SoSFVariant.h>

class SoVtkPiecewiseFunction : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkPiecewiseFunction );

public:

	/// Constructor
	SoVtkPiecewiseFunction();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ExtentTranslator of type vtkExtentTranslator
	SoSFVtkObject ExtentTranslator;
	/// FieldData of type vtkFieldData
	SoSFVtkObject FieldData;
	/// Segment
	SoMFVariant Segment;
	/// MaximumNumberOfPieces
	SoSFInt32 MaximumNumberOfPieces;
	/// RequestExactExtent
	SoSFInt32 RequestExactExtent;
	/// UpdatePiece
	SoSFInt32 UpdatePiece;
	/// WholeBoundingBox
	SoSFVariant WholeBoundingBox;
	/// UpdateExtent
	SoSFVariant UpdateExtent;
	/// UpdateGhostLevel
	SoSFInt32 UpdateGhostLevel;
	/// UpdateNumberOfPieces
	SoSFInt32 UpdateNumberOfPieces;
	/// Clamping
	SoSFInt32 Clamping;
	/// WholeExtent
	SoSFVariant WholeExtent;
	/// Source of type vtkSource
	SoSFVtkObject Source;
	/// PipelineInformation of type vtkInformation
	SoSFVtkObject PipelineInformation;
	/// Point
	SoMFVariant Point;

	
	// Outputs
	/// SoSFVtkObject of type vtkPiecewiseFunction
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkPiecewiseFunction();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkPiecewiseFunction
	SoVtkObject *mOutput;

private:

	vtkPiecewiseFunction* mObject;
};

#endif // SO_VTK_PIECEWISEFUNCTION_H_

