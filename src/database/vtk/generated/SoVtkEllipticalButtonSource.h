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
 
 
 
# ifndef SO_VTK_ELLIPTICALBUTTONSOURCE_H_
# define SO_VTK_ELLIPTICALBUTTONSOURCE_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkEllipticalButtonSource.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFVec2f.h"
# include "Inventor/fields/SoSFVec3f.h"

class SoVtkEllipticalButtonSource : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkEllipticalButtonSource );

public:

	/// Constructor
	SoVtkEllipticalButtonSource();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// CircumferentialResolution
	SoSFInt32 CircumferentialResolution;
	/// TextureResolution
	SoSFInt32 TextureResolution;
	/// Height
	SoSFFloat Height;
	/// ShoulderTextureCoordinate
	SoSFVec2f ShoulderTextureCoordinate;
	/// Width
	SoSFFloat Width;
	/// Center
	SoSFVec3f Center;
	/// TwoSided
	SoSFInt32 TwoSided;
	/// TextureStyle
	SoSFInt32 TextureStyle;
	/// TextureDimensions
	SoSFVec2f TextureDimensions;
	/// RadialRatio
	SoSFFloat RadialRatio;
	/// Depth
	SoSFFloat Depth;
	/// ShoulderResolution
	SoSFInt32 ShoulderResolution;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkEllipticalButtonSource();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkPolyData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkEllipticalButtonSource* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_ELLIPTICALBUTTONSOURCE_H_

