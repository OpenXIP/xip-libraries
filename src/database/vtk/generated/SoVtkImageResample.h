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
 
 
 
# ifndef SO_VTK_IMAGERESAMPLE_H_
# define SO_VTK_IMAGERESAMPLE_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImageResample.h"

# include "Inventor/fields/SoSFVec4f.h"
# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFVec3f.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"
# include "Inventor/fields/SoMFInt32.h"

class SoVtkImageResample : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageResample );

public:

	/// Constructor
	SoVtkImageResample();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// BackgroundColor
	SoSFVec4f BackgroundColor;
	/// NumberOfThreads
	SoSFInt32 NumberOfThreads;
	/// BackgroundLevel
	SoSFFloat BackgroundLevel;
	/// OutputOrigin
	SoSFVec3f OutputOrigin;
	/// InformationInput of type vtkImageData
	SoSFVtkObject InformationInput;
	/// ResliceAxesDirectionCosines
	SoMFVariant ResliceAxesDirectionCosines;
	/// ResliceAxes of type vtkMatrix4x4
	SoSFVtkObject ResliceAxes;
	/// Wrap
	SoSFInt32 Wrap;
	/// ResliceAxesOrigin
	SoMFVariant ResliceAxesOrigin;
	/// Mirror
	SoSFInt32 Mirror;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// Optimization
	SoSFInt32 Optimization;
	/// ResliceTransform of type vtkAbstractTransform
	SoSFVtkObject ResliceTransform;
	/// AxisOutputSpacing
	SoMFVariant AxisOutputSpacing;
	/// AxisMagnificationFactor
	SoMFVariant AxisMagnificationFactor;
	/// OutputDimensionality
	SoSFInt32 OutputDimensionality;
	/// OutputSpacing
	SoSFVec3f OutputSpacing;
	/// InterpolationMode
	SoSFInt32 InterpolationMode;
	/// Dimensionality
	SoSFInt32 Dimensionality;
	/// OutputExtent
	SoMFInt32 OutputExtent;
	/// Border
	SoSFInt32 Border;
	/// AutoCropOutput
	SoSFInt32 AutoCropOutput;
	/// Interpolate
	SoSFInt32 Interpolate;
	/// TransformInputSampling
	SoSFInt32 TransformInputSampling;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkImageResample();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkImageData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkImageResample* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMAGERESAMPLE_H_

