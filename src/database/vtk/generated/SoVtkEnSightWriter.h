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
 
 
 
# ifndef SO_VTK_ENSIGHTWRITER_H_
# define SO_VTK_ENSIGHTWRITER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkEnSightWriter.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFInt32.h"
# include "Inventor/fields/SoMFString.h"
# include "Inventor/fields/SoSFBool.h"

class SoVtkEnSightWriter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkEnSightWriter );

public:

	/// Constructor
	SoVtkEnSightWriter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// GhostLevel
	SoSFInt32 GhostLevel;
	/// ProcessNumber
	SoSFInt32 ProcessNumber;
	/// BlockIDs
	SoMFInt32 BlockIDs;
	/// ModelMetadata of type vtkModelMetadata
	SoSFVtkObject ModelMetadata;
	/// FileName
	SoMFString FileName;
	/// Path
	SoMFString Path;
	/// TransientGeometry
	SoSFBool TransientGeometry;
	/// TimeStep
	SoSFInt32 TimeStep;
	/// BaseName
	SoMFString BaseName;
	/// NumberOfBlocks
	SoSFInt32 NumberOfBlocks;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type EnSightWriter
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkEnSightWriter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkEnSightWriter
	SoVtkObject *mOutput;


private:

	vtkEnSightWriter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_ENSIGHTWRITER_H_

