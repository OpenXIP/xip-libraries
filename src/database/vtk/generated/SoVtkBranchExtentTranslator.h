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
 
 
 
# ifndef SO_VTK_BRANCHEXTENTTRANSLATOR_H_
# define SO_VTK_BRANCHEXTENTTRANSLATOR_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkBranchExtentTranslator.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFInt32.h"

class SoVtkBranchExtentTranslator : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkBranchExtentTranslator );

public:

	/// Constructor
	SoVtkBranchExtentTranslator();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// GhostLevel
	SoSFInt32 GhostLevel;
	/// AssignedPiece
	SoSFInt32 AssignedPiece;
	/// OriginalSource of type vtkImageData
	SoSFVtkObject OriginalSource;
	/// NumberOfPieces
	SoSFInt32 NumberOfPieces;
	/// Piece
	SoSFInt32 Piece;
	/// WholeExtent
	SoMFInt32 WholeExtent;
	/// AssignedNumberOfPieces
	SoSFInt32 AssignedNumberOfPieces;
	/// Extent
	SoMFInt32 Extent;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput oOriginalSource;
	/// SoSFVtkObject of type BranchExtentTranslator
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkBranchExtentTranslator();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkImageData
	SoVtkObject *mOriginalSource;

	/// vtkBranchExtentTranslator
	SoVtkObject *mOutput;


private:

	vtkBranchExtentTranslator* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_BRANCHEXTENTTRANSLATOR_H_

