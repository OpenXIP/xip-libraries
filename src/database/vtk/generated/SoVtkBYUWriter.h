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
 
 
 
# ifndef SO_VTK_BYUWRITER_H_
# define SO_VTK_BYUWRITER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkBYUWriter.h"

# include "Inventor/fields/SoMFString.h"
# include "Inventor/fields/SoSFInt32.h"

class SoVtkBYUWriter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkBYUWriter );

public:

	/// Constructor
	SoVtkBYUWriter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// FieldDataName
	SoMFString FieldDataName;
	/// TCoordsName
	SoMFString TCoordsName;
	/// VectorsName
	SoMFString VectorsName;
	/// WriteDisplacement
	SoSFInt32 WriteDisplacement;
	/// DisplacementFileName
	SoMFString DisplacementFileName;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// LookupTableName
	SoMFString LookupTableName;
	/// FileType
	SoSFInt32 FileType;
	/// ScalarsName
	SoMFString ScalarsName;
	/// ScalarFileName
	SoMFString ScalarFileName;
	/// NormalsName
	SoMFString NormalsName;
	/// TextureFileName
	SoMFString TextureFileName;
	/// WriteToOutputString
	SoSFInt32 WriteToOutputString;
	/// GeometryFileName
	SoMFString GeometryFileName;
	/// WriteScalar
	SoSFInt32 WriteScalar;
	/// TensorsName
	SoMFString TensorsName;
	/// FileName
	SoMFString FileName;
	/// WriteTexture
	SoSFInt32 WriteTexture;
	/// Header
	SoMFString Header;

	
	// Outputs
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type BYUWriter
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkBYUWriter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkBYUWriter
	SoVtkObject *mOutput;


private:

	vtkBYUWriter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_BYUWRITER_H_

