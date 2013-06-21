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
 
 
 
# ifndef SO_VTK_IMPLICITWINDOWFUNCTION_H_
# define SO_VTK_IMPLICITWINDOWFUNCTION_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImplicitWindowFunction.h"

# include "Inventor/fields/SoSFVec2f.h"

class SoVtkImplicitWindowFunction : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImplicitWindowFunction );

public:

	/// Constructor
	SoVtkImplicitWindowFunction();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ImplicitFunction of type vtkImplicitFunction
	SoSFVtkObject ImplicitFunction;
	/// WindowRange
	SoSFVec2f WindowRange;
	/// WindowValues
	SoSFVec2f WindowValues;

	
	// Outputs
	/// SoSFVtkObject of type vtkImplicitFunction
	SoEngineOutput oImplicitFunction;
	/// SoSFVtkObject of type ImplicitWindowFunction
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkImplicitWindowFunction();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkImplicitFunction
	SoVtkObject *mImplicitFunction;

	/// vtkImplicitWindowFunction
	SoVtkObject *mOutput;


private:

	vtkImplicitWindowFunction* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMPLICITWINDOWFUNCTION_H_

