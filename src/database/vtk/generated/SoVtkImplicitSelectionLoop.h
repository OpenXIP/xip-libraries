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
 
 
 
# ifndef SO_VTK_IMPLICITSELECTIONLOOP_H_
# define SO_VTK_IMPLICITSELECTIONLOOP_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImplicitSelectionLoop.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFVec3f.h"

class SoVtkImplicitSelectionLoop : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImplicitSelectionLoop );

public:

	/// Constructor
	SoVtkImplicitSelectionLoop();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// AutomaticNormalGeneration
	SoSFInt32 AutomaticNormalGeneration;
	/// Loop of type vtkPoints
	SoSFVtkObject Loop;
	/// Normal
	SoSFVec3f Normal;

	
	// Outputs
	/// SoSFVtkObject of type vtkPoints
	SoEngineOutput oLoop;
	/// SoSFVtkObject of type ImplicitSelectionLoop
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkImplicitSelectionLoop();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkPoints
	SoVtkObject *mLoop;

	/// vtkImplicitSelectionLoop
	SoVtkObject *mOutput;


private:

	vtkImplicitSelectionLoop* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMPLICITSELECTIONLOOP_H_

