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
 
#ifndef SO_VTK_EXODUSIIWRITER_H_
#define SO_VTK_EXODUSIIWRITER_H_

#include <Inventor/engines/SoSubEngine.h>

#include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
#include "xip/inventor/vtk/SoSFVtkObject.h"

#include "vtkExodusIIWriter.h"

#include "Inventor/fields/SoSFInt32.h"
#include "Inventor/fields/SoMFString.h"

class SoVtkExodusIIWriter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkExodusIIWriter );

public:
	/// Constructor
	SoVtkExodusIIWriter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// GhostLevel
	SoSFInt32 GhostLevel;
	/// StoreDoubles
	SoSFInt32 StoreDoubles;
	/// WriteOutBlockIdArray
	SoSFInt32 WriteOutBlockIdArray;
	/// WriteOutGlobalElementIdArray
	SoSFInt32 WriteOutGlobalElementIdArray;
	/// WriteOutGlobalNodeIdArray
	SoSFInt32 WriteOutGlobalNodeIdArray;
	// CurrentTimeStep
	//SoSFInt32 CurrentTimeStep;
	/// ModelMetadata of type vtkModelMetadata
	SoSFVtkObject ModelMetadata;
	// GlobalNodeIdArrayName
	//SoMFString GlobalNodeIdArrayName;
	// GlobalElementIdArrayName
	//SoMFString GlobalElementIdArrayName;
	/// ErrorStatus
	SoSFInt32 ErrorStatus;
	/// FileName
	SoMFString FileName;
	/// BlockIdArrayName
	SoMFString BlockIdArrayName;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	// Outputs
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkModelMetadata
	SoEngineOutput oOrCreateModelMetadata;
	/// SoSFVtkObject of type ExodusIIWriter
	SoEngineOutput Output;

protected:
	/// Destructor
	~SoVtkExodusIIWriter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkModelMetadata
	SoVtkObject *mOrCreateModelMetadata;

	/// vtkExodusIIWriter
	SoVtkObject *mOutput;

private:
	vtkExodusIIWriter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_EXODUSIIWRITER_H_

