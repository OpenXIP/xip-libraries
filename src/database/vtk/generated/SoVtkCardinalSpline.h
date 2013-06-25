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
 
 
 
# ifndef SO_VTK_CARDINALSPLINE_H_
# define SO_VTK_CARDINALSPLINE_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkCardinalSpline.h"

# include "Inventor/fields/SoSFInt32.h"
# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"
# include "Inventor/fields/SoSFFloat.h"

class SoVtkCardinalSpline : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkCardinalSpline );

public:

	/// Constructor
	SoVtkCardinalSpline();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// RightConstraint
	SoSFInt32 RightConstraint;
	/// ParametricRange
	SoMFVariant ParametricRange;
	/// RightValue
	SoSFFloat RightValue;
	/// LeftValue
	SoSFFloat LeftValue;
	/// ClampValue
	SoSFInt32 ClampValue;
	/// Closed
	SoSFInt32 Closed;
	/// LeftConstraint
	SoSFInt32 LeftConstraint;
	/// Point
	SoMFVariant Point;

	
	// Outputs
	/// SoSFVtkObject of type CardinalSpline
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkCardinalSpline();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkCardinalSpline
	SoVtkObject *mOutput;


private:

	vtkCardinalSpline* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_CARDINALSPLINE_H_

