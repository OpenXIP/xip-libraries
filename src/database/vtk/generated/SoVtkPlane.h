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

# ifndef SO_VTK_PLANE_H_
# define SO_VTK_PLANE_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkPlane.h"

# include "Inventor/fields/SoSFVec3f.h"

class SoVtkPlane : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkPlane );

public:

	/// Constructor
	SoVtkPlane();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Transform of type vtkAbstractTransform
	SoSFVtkObject Transform;
	/// Origin
	SoSFVec3f Origin;
	/// Normal
	SoSFVec3f Normal;

	
	// Outputs
	/// SoSFVtkObject of type vtkPlane
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkPlane();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkPlane
	SoVtkObject *mOutput;

private:

	vtkPlane* mObject;
};

#endif // SO_VTK_PLANE_H_

