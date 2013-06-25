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
/* 
 * \author Sylvain Jaume, Francois Huguet
 */
#ifndef SO_VTK_CONNECTIVITYFILTER_H_
#define SO_VTK_CONNECTIVITYFILTER_H_

#include <Inventor/engines/SoSubEngine.h>

#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFVec3f.h>

#include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
#include "xip/inventor/vtk/SoSFVtkObject.h"

#include "vtkConnectivityFilter.h"
#include "vtkType.h"

class SoVtkConnectivityFilter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkConnectivityFilter );

public:

	/// Constructor
	SoVtkConnectivityFilter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ScalarRange
	SoSFVec2f ScalarRange;
	/// ColorRegions
	SoSFInt32 ColorRegions;
	/// ExtractionMode
	SoSFInt32 ExtractionMode;
	/// ClosestPoint
	SoSFVec3f ClosestPoint;
	/// SpecifiedRegion
	SoSFInt32 SpecifiedRegion;
	/// Seed of type vtkIdType
	SoSFVtkObject Seed;
	/// ScalarConnectivity
	SoSFInt32 ScalarConnectivity;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkUnstructuredGrid
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkConnectivityFilter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkUnstructuredGrid
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkConnectivityFilter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_CONNECTIVITYFILTER_H_


