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
 
 
 
# ifndef SO_VTK_DATAREADER_H_
# define SO_VTK_DATAREADER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkDataReader.h"

# include "Inventor/fields/SoMFString.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkDataReader : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkDataReader );

public:

	/// Constructor
	SoVtkDataReader();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// FieldDataName
	SoMFString FieldDataName;
	/// ReadFromInputString
	SoSFInt32 ReadFromInputString;
	/// TCoordsName
	SoMFString TCoordsName;
	/// ReadAllNormals
	SoSFInt32 ReadAllNormals;
	/// VectorsName
	SoMFString VectorsName;
	/// ReadAllTCoords
	SoSFInt32 ReadAllTCoords;
	/// ReadAllColorScalars
	SoSFInt32 ReadAllColorScalars;
	/// ReadAllTensors
	SoSFInt32 ReadAllTensors;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// InputArray of type vtkCharArray
	SoSFVtkObject InputArray;
	/// LookupTableName
	SoMFString LookupTableName;
	/// ScalarsName
	SoMFString ScalarsName;
	/// NormalsName
	SoMFString NormalsName;
	/// ReadAllScalars
	SoSFInt32 ReadAllScalars;
	/// ReadAllVectors
	SoSFInt32 ReadAllVectors;
	/// TensorsName
	SoMFString TensorsName;
	/// FileName
	SoMFString FileName;
	/// InputString
	SoMFString InputString;
	/// ReadAllFields
	SoSFInt32 ReadAllFields;

	
	// Outputs
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type DataReader
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkDataReader();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkDataReader
	SoVtkObject *mOutput;


private:

	vtkDataReader* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_DATAREADER_H_

