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
 
 
 
# ifndef SO_VTK_GENERALTRANSFORM_H_
# define SO_VTK_GENERALTRANSFORM_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkGeneralTransform.h"


class SoVtkGeneralTransform : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkGeneralTransform );

public:

	/// Constructor
	SoVtkGeneralTransform();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Inverse of type vtkAbstractTransform
	SoSFVtkObject Inverse;

	
	// Outputs
	/// SoSFVtkObject of type vtkAbstractTransform
	SoEngineOutput oInverse;
	/// SoSFVtkObject of type GeneralTransform
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkGeneralTransform();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkAbstractTransform
	SoVtkObject *mInverse;

	/// vtkGeneralTransform
	SoVtkObject *mOutput;


private:

	vtkGeneralTransform* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_GENERALTRANSFORM_H_

