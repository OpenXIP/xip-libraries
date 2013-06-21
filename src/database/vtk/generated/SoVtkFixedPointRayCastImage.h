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
 
 
 
# ifndef SO_VTK_FIXEDPOINTRAYCASTIMAGE_H_
# define SO_VTK_FIXEDPOINTRAYCASTIMAGE_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkFixedPointRayCastImage.h"

# include "Inventor/fields/SoSFVec2f.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkFixedPointRayCastImage : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkFixedPointRayCastImage );

public:

	/// Constructor
	SoVtkFixedPointRayCastImage();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ImageInUseSize
	SoSFVec2f ImageInUseSize;
	/// ImageViewportSize
	SoSFVec2f ImageViewportSize;
	/// ImageSampleDistance
	SoSFFloat ImageSampleDistance;
	/// ZBufferSize
	SoSFVec2f ZBufferSize;
	/// UseZBuffer
	SoSFInt32 UseZBuffer;
	/// ImageOrigin
	SoSFVec2f ImageOrigin;
	/// ZBufferOrigin
	SoSFVec2f ZBufferOrigin;
	/// ImageMemorySize
	SoSFVec2f ImageMemorySize;

	
	// Outputs
	/// SoSFVtkObject of type FixedPointRayCastImage
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkFixedPointRayCastImage();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkFixedPointRayCastImage
	SoVtkObject *mOutput;


private:

	vtkFixedPointRayCastImage* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_FIXEDPOINTRAYCASTIMAGE_H_

