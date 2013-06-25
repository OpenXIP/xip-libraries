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
 
 
 
# ifndef SO_VTK_FINITEDIFFERENCEGRADIENTESTIMATOR_H_
# define SO_VTK_FINITEDIFFERENCEGRADIENTESTIMATOR_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkFiniteDifferenceGradientEstimator.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoMFInt32.h"

class SoVtkFiniteDifferenceGradientEstimator : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkFiniteDifferenceGradientEstimator );

public:

	/// Constructor
	SoVtkFiniteDifferenceGradientEstimator();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// CylinderClip
	SoSFInt32 CylinderClip;
	/// BoundsClip
	SoSFInt32 BoundsClip;
	/// NumberOfThreads
	SoSFInt32 NumberOfThreads;
	/// SampleSpacingInVoxels
	SoSFInt32 SampleSpacingInVoxels;
	/// ZeroNormalThreshold
	SoSFFloat ZeroNormalThreshold;
	/// Bounds
	SoMFInt32 Bounds;
	/// GradientMagnitudeBias
	SoSFFloat GradientMagnitudeBias;
	/// ComputeGradientMagnitudes
	SoSFInt32 ComputeGradientMagnitudes;
	/// DirectionEncoder of type vtkDirectionEncoder
	SoSFVtkObject DirectionEncoder;
	/// Input data of type vtkImageData
	SoSFVtkObject Input;
	/// GradientMagnitudeScale
	SoSFFloat GradientMagnitudeScale;
	/// ZeroPad
	SoSFInt32 ZeroPad;

	
	// Outputs
	/// SoSFVtkObject of type FiniteDifferenceGradientEstimator
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkFiniteDifferenceGradientEstimator();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkFiniteDifferenceGradientEstimator
	SoVtkObject *mOutput;


private:

	vtkFiniteDifferenceGradientEstimator* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_FINITEDIFFERENCEGRADIENTESTIMATOR_H_

