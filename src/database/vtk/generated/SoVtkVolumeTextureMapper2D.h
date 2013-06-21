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
#ifndef SO_VTK_VOLUMETEXTUREMAPPER2D_H_
#define SO_VTK_VOLUMETEXTUREMAPPER2D_H_

#include <Inventor/engines/SoSubEngine.h>

#include <xip/inventor/vtk/SoSFVtkAlgorithmOutput.h>
#include <xip/inventor/vtk/SoSFVtkObject.h>
#include <xip/inventor/core/SoSFVariant.h>

#include "vtkVolumeTextureMapper2D.h"

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFVec2f.h>

class SoVtkVolumeTextureMapper2D : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkVolumeTextureMapper2D );

public:

	/// Constructor
	SoVtkVolumeTextureMapper2D();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Cropping
	SoSFInt32 Cropping;
	/// CroppingRegionPlanes
	SoMFFloat CroppingRegionPlanes;
	/// MaximumStorageSize
	SoSFInt32 MaximumStorageSize;
	/// ClippingPlanes of type vtkPlanes
	SoSFVtkObject ClippingPlanes;
	/// MaximumNumberOfPlanes
	SoSFInt32 MaximumNumberOfPlanes;
	/// TargetTextureSize
	SoSFVec2f TargetTextureSize;
	/// CroppingRegionFlags
	SoSFInt32 CroppingRegionFlags;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input data of type vtkDataSet
	SoSFVtkObject Input;
	/// BlendMode
	SoSFInt32 BlendMode;
	/// GradientEstimator of type vtkEncodedGradientEstimator
	SoSFVtkObject GradientEstimator;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkVolumeTextureMapper2D
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkVolumeTextureMapper2D();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;
	/// vtkVolumeTextureMapper2D
	SoVtkObject *mOutput;

private:

	vtkVolumeTextureMapper2D* mObject;
};

#endif // SO_VTK_VOLUMETEXTUREMAPPER2D_H_


