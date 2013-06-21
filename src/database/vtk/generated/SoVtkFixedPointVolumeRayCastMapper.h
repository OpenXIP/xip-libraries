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
 
 
 
# ifndef SO_VTK_FIXEDPOINTVOLUMERAYCASTMAPPER_H_
# define SO_VTK_FIXEDPOINTVOLUMERAYCASTMAPPER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkFixedPointVolumeRayCastMapper.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoMFFloat.h"

class SoVtkFixedPointVolumeRayCastMapper : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkFixedPointVolumeRayCastMapper );

public:

	/// Constructor
	SoVtkFixedPointVolumeRayCastMapper();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// NumberOfThreads
	SoSFInt32 NumberOfThreads;
	/// AutoAdjustSampleDistances
	SoSFInt32 AutoAdjustSampleDistances;
	/// ClippingPlanes of type vtkPlaneCollection
	SoSFVtkObject ClippingPlanes;
	/// Input data of type vtkImageData
	SoSFVtkObject Input;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// SampleDistance
	SoSFFloat SampleDistance;
	/// MinimumImageSampleDistance
	SoSFFloat MinimumImageSampleDistance;
	/// Cropping
	SoSFInt32 Cropping;
	/// IntermixIntersectingGeometry
	SoSFInt32 IntermixIntersectingGeometry;
	/// RayCastImage of type vtkFixedPointRayCastImage
	SoSFVtkObject RayCastImage;
	/// CroppingRegionPlanes
	SoMFFloat CroppingRegionPlanes;
	/// InteractiveSampleDistance
	SoSFFloat InteractiveSampleDistance;
	/// ImageSampleDistance
	SoSFFloat ImageSampleDistance;
	/// CroppingRegionFlags
	SoSFInt32 CroppingRegionFlags;
	/// BlendMode
	SoSFInt32 BlendMode;
	/// MaximumImageSampleDistance
	SoSFFloat MaximumImageSampleDistance;

	
	// Outputs
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput oDataSetInput;
	/// SoSFVtkObject of type vtkPlaneCollection
	SoEngineOutput oClippingPlanes;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type FixedPointVolumeRayCastMapper
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkFixedPointVolumeRayCastMapper();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkDataSet
	SoVtkObject *mDataSetInput;

	/// vtkPlaneCollection
	SoVtkObject *mClippingPlanes;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkFixedPointVolumeRayCastMapper
	SoVtkObject *mOutput;


private:

	vtkFixedPointVolumeRayCastMapper* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_FIXEDPOINTVOLUMERAYCASTMAPPER_H_

