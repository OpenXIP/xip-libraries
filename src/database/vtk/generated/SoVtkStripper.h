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

# ifndef SO_VTK_STRIPPER_H_
# define SO_VTK_STRIPPER_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkStripper.h"

# include "Inventor/fields/SoSFInt32.h"
# include <xip/inventor/core/SoSFVariant.h>

class SoVtkStripper : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkStripper );

public:

	/// Constructor
	SoVtkStripper();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// MaximumLength
	SoSFInt32 MaximumLength;
	/// Input data of type vtkDataObject
	SoSFVtkObject Input;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// PassCellDataAsFieldData
	SoSFInt32 PassCellDataAsFieldData;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkStripper();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkPolyData
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

private:

	vtkStripper* mObject;
};

#endif // SO_VTK_STRIPPER_H_

