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
 
 
 
# ifndef SO_VTK_IMAGEIMPORT_H_
# define SO_VTK_IMAGEIMPORT_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImageImport.h"

# include "Inventor/fields/SoSFVec3f.h"
# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFInt32.h"

class SoVtkImageImport : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageImport );

public:

	/// Constructor
	SoVtkImageImport();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// DataSpacing
	SoSFVec3f DataSpacing;
	/// NumberOfScalarComponents
	SoSFInt32 NumberOfScalarComponents;
	/// WholeExtent
	SoMFInt32 WholeExtent;
	/// DataOrigin
	SoSFVec3f DataOrigin;
	/// DataScalarType
	SoSFInt32 DataScalarType;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// DataExtent
	SoMFInt32 DataExtent;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkImageImport();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkImageData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkImageImport* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMAGEIMPORT_H_

