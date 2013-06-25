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
 
 
 
# ifndef SO_VTK_EXTENTTRANSLATOR_H_
# define SO_VTK_EXTENTTRANSLATOR_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkExtentTranslator.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFInt32.h"

class SoVtkExtentTranslator : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkExtentTranslator );

public:

	/// Constructor
	SoVtkExtentTranslator();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// GhostLevel
	SoSFInt32 GhostLevel;
	/// NumberOfPieces
	SoSFInt32 NumberOfPieces;
	/// Piece
	SoSFInt32 Piece;
	/// Extent
	SoMFInt32 Extent;
	/// WholeExtent
	SoMFInt32 WholeExtent;

	
	// Outputs
	/// SoSFVtkObject of type ExtentTranslator
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkExtentTranslator();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkExtentTranslator
	SoVtkObject *mOutput;


private:

	vtkExtentTranslator* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_EXTENTTRANSLATOR_H_

