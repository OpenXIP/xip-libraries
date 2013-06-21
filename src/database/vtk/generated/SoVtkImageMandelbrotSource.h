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
 
 
 
# ifndef SO_VTK_IMAGEMANDELBROTSOURCE_H_
# define SO_VTK_IMAGEMANDELBROTSOURCE_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImageMandelbrotSource.h"

# include "Inventor/fields/SoSFInt32.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"
# include "Inventor/fields/SoSFVec4f.h"
# include "Inventor/fields/SoSFUShort.h"

class SoVtkImageMandelbrotSource : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageMandelbrotSource );

public:

	/// Constructor
	SoVtkImageMandelbrotSource();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ConstantSize
	SoSFInt32 ConstantSize;
	/// SizeCX
	SoMFVariant SizeCX;
	/// ProjectionAxes
	SoMFVariant ProjectionAxes;
	/// WholeExtent
	SoMFVariant WholeExtent;
	/// SampleCX
	SoSFVec4f SampleCX;
	/// MaximumNumberOfIterations
	SoSFUShort MaximumNumberOfIterations;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// OriginCX
	SoSFVec4f OriginCX;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkImageMandelbrotSource();

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

	vtkImageMandelbrotSource* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMAGEMANDELBROTSOURCE_H_

