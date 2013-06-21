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
 
 
 
# ifndef SO_VTK_IMAGERECTILINEARWIPE_H_
# define SO_VTK_IMAGERECTILINEARWIPE_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImageRectilinearWipe.h"

# include "Inventor/fields/SoSFVec2f.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkImageRectilinearWipe : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageRectilinearWipe );

public:

	/// Constructor
	SoVtkImageRectilinearWipe();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Input2 of type vtkDataObject
	SoSFVtkObject Input2;
	/// Position
	SoSFVec2f Position;
	/// Wipe
	SoSFInt32 Wipe;
	/// NumberOfThreads
	SoSFInt32 NumberOfThreads;
	/// Input1 of type vtkDataObject
	SoSFVtkObject Input1;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkImageRectilinearWipe();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkImageData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkImageRectilinearWipe* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMAGERECTILINEARWIPE_H_

