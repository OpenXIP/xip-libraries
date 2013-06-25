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
 
 
 
# ifndef SO_VTK_CGMWRITER_H_
# define SO_VTK_CGMWRITER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkCGMWriter.h"

# include "Inventor/fields/SoMFString.h"
# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFVec3f.h"

class SoVtkCGMWriter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkCGMWriter );

public:

	/// Constructor
	SoVtkCGMWriter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// FieldDataName
	SoMFString FieldDataName;
	/// Viewport of type vtkViewport
	SoSFVtkObject Viewport;
	/// TCoordsName
	SoMFString TCoordsName;
	/// Sort
	SoSFInt32 Sort;
	/// VectorsName
	SoMFString VectorsName;
	/// SpecifiedColor
	SoSFVec3f SpecifiedColor;
	/// Resolution
	SoSFInt32 Resolution;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// LookupTableName
	SoMFString LookupTableName;
	/// FileType
	SoSFInt32 FileType;
	/// ScalarsName
	SoMFString ScalarsName;
	/// NormalsName
	SoMFString NormalsName;
	/// WriteToOutputString
	SoSFInt32 WriteToOutputString;
	/// TensorsName
	SoMFString TensorsName;
	/// FileName
	SoMFString FileName;
	/// ColorMode
	SoSFInt32 ColorMode;
	/// Header
	SoMFString Header;

	
	// Outputs
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type CGMWriter
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkCGMWriter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkCGMWriter
	SoVtkObject *mOutput;


private:

	vtkCGMWriter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_CGMWRITER_H_

