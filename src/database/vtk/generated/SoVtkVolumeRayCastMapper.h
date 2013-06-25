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
# ifndef SO_VTK_VOLUMERAYCASTMAPPER_H_
# define SO_VTK_VOLUMERAYCASTMAPPER_H_

# include <Inventor/engines/SoSubEngine.h>

# include <Inventor/fields/SoSFInt32.h>
# include <Inventor/fields/SoSFFloat.h>
# include <Inventor/fields/SoMFFloat.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkVolumeRayCastMapper.h"
# include <xip/inventor/core/SoSFVariant.h>

class SoVtkVolumeRayCastMapper : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkVolumeRayCastMapper );

public:

	/// Constructor
	SoVtkVolumeRayCastMapper();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// NumberOfThreads
	SoSFInt32 NumberOfThreads;
	/// AutoAdjustSampleDistances
	SoSFInt32 AutoAdjustSampleDistances;
	/// ClippingPlanes of type vtkPlanes
	SoSFVtkObject ClippingPlanes;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input data of type vtkDataSet
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
	/// CroppingRegionPlanes
	SoMFFloat CroppingRegionPlanes;
	/// ImageSampleDistance
	SoSFFloat ImageSampleDistance;
	/// CroppingRegionFlags
	SoSFInt32 CroppingRegionFlags;
	/// BlendMode
	SoSFInt32 BlendMode;
	/// MaximumImageSampleDistance
	SoSFFloat MaximumImageSampleDistance;
	/// VolumeRayCastFunction of type vtkVolumeRayCastFunction
	SoSFVtkObject VolumeRayCastFunction;
	/// GradientEstimator of type vtkEncodedGradientEstimator
	SoSFVtkObject GradientEstimator;

	
	// Outputs
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkVolumeRayCastMapper
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkVolumeRayCastMapper();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;
	/// vtkVolumeRayCastMapper
	SoVtkObject *mOutput;

private:
	vtkVolumeRayCastMapper* mObject;
};

#endif // SO_VTK_VOLUMERAYCASTMAPPER_H_


