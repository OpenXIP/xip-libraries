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
 
 
 
# ifndef SO_VTK_IMAGEMAPPER_H_
# define SO_VTK_IMAGEMAPPER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImageMapper.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"

class SoVtkImageMapper : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageMapper );

public:

	/// Constructor
	SoVtkImageMapper();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ZSlice
	SoSFInt32 ZSlice;
	/// RenderToRectangle
	SoSFInt32 RenderToRectangle;
	/// UseCustomExtents
	SoSFInt32 UseCustomExtents;
	/// ClippingPlanes of type vtkPlaneCollection
	SoSFVtkObject ClippingPlanes;
	/// ColorWindow
	SoSFFloat ColorWindow;
	/// ColorLevel
	SoSFFloat ColorLevel;
	/// CustomDisplayExtents
	SoSFInt32 CustomDisplayExtents;
	/// Input data of type vtkImageData
	SoSFVtkObject Input;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPlaneCollection
	SoEngineOutput oClippingPlanes;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type ImageMapper
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkImageMapper();

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

	/// vtkImageMapper
	SoVtkObject *mOutput;


private:

	vtkImageMapper* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMAGEMAPPER_H_

