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
 
 
 
# ifndef SO_VTK_ENSIGHTGOLDBINARYREADER_H_
# define SO_VTK_ENSIGHTGOLDBINARYREADER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkEnSightGoldBinaryReader.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoMFString.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"

class SoVtkEnSightGoldBinaryReader : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkEnSightGoldBinaryReader );

public:

	/// Constructor
	SoVtkEnSightGoldBinaryReader();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ByteOrder
	SoSFInt32 ByteOrder;
	/// TimeValue
	SoSFFloat TimeValue;
	/// FilePath
	SoMFString FilePath;
	/// NumberOfInputConnections
	SoMFVariant NumberOfInputConnections;
	/// CaseFileName
	SoMFString CaseFileName;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// ReadAllVariables
	SoSFInt32 ReadAllVariables;

	
	// Outputs
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkEnSightGoldBinaryReader();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkDataSet
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkEnSightGoldBinaryReader* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_ENSIGHTGOLDBINARYREADER_H_

