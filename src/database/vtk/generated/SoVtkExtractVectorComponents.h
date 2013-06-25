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
 
 
 
# ifndef SO_VTK_EXTRACTVECTORCOMPONENTS_H_
# define SO_VTK_EXTRACTVECTORCOMPONENTS_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkExtractVectorComponents.h"

# include "Inventor/fields/SoSFInt32.h"

class SoVtkExtractVectorComponents : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkExtractVectorComponents );

public:

	/// Constructor
	SoVtkExtractVectorComponents();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ExtractToFieldData
	SoSFInt32 ExtractToFieldData;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput oVzComponent;
	/// SoSFVtkObject of type vtkStructuredPoints
	SoEngineOutput oStructuredPointsOutput;
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput oVxComponent;
	/// SoSFVtkObject of type vtkStructuredGrid
	SoEngineOutput oStructuredGridOutput;
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput oPolyDataOutput;
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput oImageDataOutput;
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkUnstructuredGrid
	SoEngineOutput oUnstructuredGridOutput;
	/// SoSFVtkObject of type vtkRectilinearGrid
	SoEngineOutput oRectilinearGridOutput;
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput oVyComponent;

protected:

	/// Destructor
	~SoVtkExtractVectorComponents();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkDataSet
	SoVtkObject *mVzComponent;

	/// vtkStructuredPoints
	SoVtkObject *mStructuredPointsOutput;

	/// vtkDataSet
	SoVtkObject *mVxComponent;

	/// vtkStructuredGrid
	SoVtkObject *mStructuredGridOutput;

	/// vtkPolyData
	SoVtkObject *mPolyDataOutput;

	/// vtkImageData
	SoVtkObject *mImageDataOutput;

	/// vtkDataSet
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkUnstructuredGrid
	SoVtkObject *mUnstructuredGridOutput;

	/// vtkRectilinearGrid
	SoVtkObject *mRectilinearGridOutput;

	/// vtkDataSet
	SoVtkObject *mVyComponent;


private:

	vtkExtractVectorComponents* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_EXTRACTVECTORCOMPONENTS_H_

