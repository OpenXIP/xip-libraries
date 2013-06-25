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
 
 
 
# ifndef SO_VTK_GENERICGEOMETRYFILTER_H_
# define SO_VTK_GENERICGEOMETRYFILTER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkGenericGeometryFilter.h"

# include "vtkType.h"
# include "Inventor/fields/SoSFInt32.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"

class SoVtkGenericGeometryFilter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkGenericGeometryFilter );

public:

	/// Constructor
	SoVtkGenericGeometryFilter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// CellMaximum of type vtkIdType
	SoSFVtkObject CellMaximum;
	/// CellMinimum of type vtkIdType
	SoSFVtkObject CellMinimum;
	/// PointMaximum of type vtkIdType
	SoSFVtkObject PointMaximum;
	/// CellClipping
	SoSFInt32 CellClipping;
	/// Locator of type vtkPointLocator
	SoSFVtkObject Locator;
	/// PointClipping
	SoSFInt32 PointClipping;
	/// ExtentClipping
	SoSFInt32 ExtentClipping;
	/// Merging
	SoSFInt32 Merging;
	/// Extent
	SoMFVariant Extent;
	/// PointMinimum of type vtkIdType
	SoSFVtkObject PointMinimum;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkObject of type vtkPointLocator
	SoEngineOutput oLocator;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkGenericGeometryFilter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkPolyData
	SoVtkObject *mOutput;

	/// vtkPointLocator
	SoVtkObject *mLocator;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkGenericGeometryFilter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_GENERICGEOMETRYFILTER_H_

