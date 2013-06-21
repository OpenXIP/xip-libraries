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
 
 
 
# ifndef SO_VTK_COORDINATE_H_
# define SO_VTK_COORDINATE_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkCoordinate.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFVec3f.h"

class SoVtkCoordinate : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkCoordinate );

public:

	/// Constructor
	SoVtkCoordinate();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// CoordinateSystem
	SoSFInt32 CoordinateSystem;
	/// Value
	SoSFVec3f Value;
	/// Viewport of type vtkViewport
	SoSFVtkObject Viewport;
	/// ReferenceCoordinate of type vtkCoordinate
	SoSFVtkObject ReferenceCoordinate;

	
	// Outputs
	/// SoSFVtkObject of type vtkViewport
	SoEngineOutput oViewport;
	/// SoSFVtkObject of type vtkCoordinate
	SoEngineOutput oReferenceCoordinate;
	/// SoSFVtkObject of type Coordinate
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkCoordinate();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkViewport
	SoVtkObject *mViewport;

	/// vtkCoordinate
	SoVtkObject *mReferenceCoordinate;

	/// vtkCoordinate
	SoVtkObject *mOutput;


private:

	vtkCoordinate* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_COORDINATE_H_

