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
 
 
 
# ifndef SO_VTK_FIELDDATATOATTRIBUTEDATAFILTER_H_
# define SO_VTK_FIELDDATATOATTRIBUTEDATAFILTER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkFieldDataToAttributeDataFilter.h"

# include "Inventor/fields/SoSFInt32.h"

class SoVtkFieldDataToAttributeDataFilter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkFieldDataToAttributeDataFilter );

public:

	/// Constructor
	SoVtkFieldDataToAttributeDataFilter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// DefaultNormalize
	SoSFInt32 DefaultNormalize;
	/// OutputAttributeData
	SoSFInt32 OutputAttributeData;
	/// InputField
	SoSFInt32 InputField;
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
	~SoVtkFieldDataToAttributeDataFilter();

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

	vtkFieldDataToAttributeDataFilter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_FIELDDATATOATTRIBUTEDATAFILTER_H_

