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
 
 
 
# ifndef SO_VTK_DATASETMAPPER_H_
# define SO_VTK_DATASETMAPPER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkDataSetMapper.h"

# include "Inventor/fields/SoSFVec2f.h"
# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"

class SoVtkDataSetMapper : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkDataSetMapper );

public:

	/// Constructor
	SoVtkDataSetMapper();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ScalarRange
	SoSFVec2f ScalarRange;
	/// ResolveCoincidentTopology
	SoSFInt32 ResolveCoincidentTopology;
	/// ImmediateModeRendering
	SoSFInt32 ImmediateModeRendering;
	/// ScalarMode
	SoSFInt32 ScalarMode;
	/// GlobalImmediateModeRendering
	SoSFInt32 GlobalImmediateModeRendering;
	/// ClippingPlanes of type vtkPlaneCollection
	SoSFVtkObject ClippingPlanes;
	/// ResolveCoincidentTopologyZShift
	SoSFFloat ResolveCoincidentTopologyZShift;
	/// Input data of type vtkDataSet
	SoSFVtkObject Input;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// UseLookupTableScalarRange
	SoSFInt32 UseLookupTableScalarRange;
	/// ScalarMaterialMode
	SoSFInt32 ScalarMaterialMode;
	/// LookupTable of type vtkScalarsToColors
	SoSFVtkObject LookupTable;
	/// ScalarVisibility
	SoSFInt32 ScalarVisibility;
	/// InterpolateScalarsBeforeMapping
	SoSFInt32 InterpolateScalarsBeforeMapping;
	/// Static
	SoSFInt32 Static;
	/// RenderTime
	SoSFFloat RenderTime;
	/// ColorMode
	SoSFInt32 ColorMode;

	
	// Outputs
	/// SoSFVtkObject of type vtkPlaneCollection
	SoEngineOutput oClippingPlanes;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkScalarsToColors
	SoEngineOutput oLookupTable;
	/// SoSFVtkObject of type DataSetMapper
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkDataSetMapper();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkPlaneCollection
	SoVtkObject *mClippingPlanes;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkScalarsToColors
	SoVtkObject *mLookupTable;

	/// vtkDataSetMapper
	SoVtkObject *mOutput;


private:

	vtkDataSetMapper* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_DATASETMAPPER_H_

