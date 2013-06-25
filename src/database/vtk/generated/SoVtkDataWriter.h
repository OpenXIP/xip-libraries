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
 
 
 
# ifndef SO_VTK_DATAWRITER_H_
# define SO_VTK_DATAWRITER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkDataWriter.h"

# include "Inventor/fields/SoMFString.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkDataWriter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkDataWriter );

public:

	/// Constructor
	SoVtkDataWriter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// FieldDataName
	SoMFString FieldDataName;
	/// FileType
	SoSFInt32 FileType;
	/// LookupTableName
	SoMFString LookupTableName;
	/// TCoordsName
	SoMFString TCoordsName;
	/// ScalarsName
	SoMFString ScalarsName;
	/// NormalsName
	SoMFString NormalsName;
	/// VectorsName
	SoMFString VectorsName;
	/// WriteToOutputString
	SoSFInt32 WriteToOutputString;
	/// TensorsName
	SoMFString TensorsName;
	/// FileName
	SoMFString FileName;
	/// Header
	SoMFString Header;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type DataWriter
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkDataWriter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkDataWriter
	SoVtkObject *mOutput;


private:

	vtkDataWriter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_DATAWRITER_H_

