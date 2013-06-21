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
 
 
 
# ifndef SO_VTK_DEPTHSORTPOLYDATA_H_
# define SO_VTK_DEPTHSORTPOLYDATA_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkDepthSortPolyData.h"

# include "Inventor/fields/SoSFVec3f.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkDepthSortPolyData : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkDepthSortPolyData );

public:

	/// Constructor
	SoVtkDepthSortPolyData();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Camera of type vtkCamera
	SoSFVtkObject Camera;
	/// Vector
	SoSFVec3f Vector;
	/// Direction
	SoSFInt32 Direction;
	/// DepthSortMode
	SoSFInt32 DepthSortMode;
	/// Origin
	SoSFVec3f Origin;
	/// Prop3D of type vtkProp3D
	SoSFVtkObject Prop3D;
	/// SortScalars
	SoSFInt32 SortScalars;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkCamera
	SoEngineOutput oCamera;
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkProp3D
	SoEngineOutput oProp3D;

protected:

	/// Destructor
	~SoVtkDepthSortPolyData();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkCamera
	SoVtkObject *mCamera;

	/// vtkPolyData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkProp3D
	SoVtkObject *mProp3D;


private:

	vtkDepthSortPolyData* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_DEPTHSORTPOLYDATA_H_

