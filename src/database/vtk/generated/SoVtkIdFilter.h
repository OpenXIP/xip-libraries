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
 
 
 
# ifndef SO_VTK_IDFILTER_H_
# define SO_VTK_IDFILTER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkIdFilter.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFString.h"

class SoVtkIdFilter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkIdFilter );

public:

	/// Constructor
	SoVtkIdFilter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// FieldData
	SoSFInt32 FieldData;
	/// CellIds
	SoSFInt32 CellIds;
	/// PointIds
	SoSFInt32 PointIds;
	/// IdsArrayName
	SoMFString IdsArrayName;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput oImageDataOutput;
	/// SoSFVtkObject of type vtkStructuredPoints
	SoEngineOutput oStructuredPointsOutput;
	/// SoSFVtkObject of type vtkStructuredGrid
	SoEngineOutput oStructuredGridOutput;
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput Output;
	/// SoSFVtkObject of type vtkRectilinearGrid
	SoEngineOutput oRectilinearGridOutput;
	/// SoSFVtkObject of type vtkUnstructuredGrid
	SoEngineOutput oUnstructuredGridOutput;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput oPolyDataOutput;

protected:

	/// Destructor
	~SoVtkIdFilter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkImageData
	SoVtkObject *mImageDataOutput;

	/// vtkStructuredPoints
	SoVtkObject *mStructuredPointsOutput;

	/// vtkStructuredGrid
	SoVtkObject *mStructuredGridOutput;

	/// vtkDataSet
	SoVtkObject *mOutput;

	/// vtkRectilinearGrid
	SoVtkObject *mRectilinearGridOutput;

	/// vtkUnstructuredGrid
	SoVtkObject *mUnstructuredGridOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkPolyData
	SoVtkObject *mPolyDataOutput;


private:

	vtkIdFilter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IDFILTER_H_

