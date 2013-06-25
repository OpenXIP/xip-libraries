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
 
 
 
# ifndef SO_VTK_CURSOR3D_H_
# define SO_VTK_CURSOR3D_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkCursor3D.h"

# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkCursor3D : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkCursor3D );

public:

	/// Constructor
	SoVtkCursor3D();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// FocalPoint
	SoMFVariant FocalPoint;
	/// TranslationMode
	SoSFInt32 TranslationMode;
	/// ModelBounds
	SoMFVariant ModelBounds;
	/// Axes
	SoSFInt32 Axes;
	/// Outline
	SoSFInt32 Outline;
	/// ZShadows
	SoSFInt32 ZShadows;
	/// Wrap
	SoSFInt32 Wrap;
	/// XShadows
	SoSFInt32 XShadows;
	/// YShadows
	SoSFInt32 YShadows;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkCursor3D();

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

	vtkCursor3D* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_CURSOR3D_H_

