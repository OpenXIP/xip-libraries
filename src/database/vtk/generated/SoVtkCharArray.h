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
 
 
 
# ifndef SO_VTK_CHARARRAY_H_
# define SO_VTK_CHARARRAY_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkCharArray.h"

# include "xip/inventor/core/SbVariant.h"
# include "xip/inventor/core/SoMFVariant.h"
# include "Inventor/fields/SoSFInt32.h"
# include "vtkType.h"
# include "Inventor/fields/SoMFString.h"

class SoVtkCharArray : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkCharArray );

public:

	/// Constructor
	SoVtkCharArray();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Value
	SoMFVariant Value;
	/// Tuple1
	SoMFVariant Tuple1;
	/// NumberOfComponents
	SoSFInt32 NumberOfComponents;
	/// Tuple9
	SoMFVariant Tuple9;
	/// LookupTable of type vtkLookupTable
	SoSFVtkObject LookupTable;
	/// Component
	SoMFVariant Component;
	/// Tuple3
	SoMFVariant Tuple3;
	/// NumberOfTuples of type vtkIdType
	SoSFVtkObject NumberOfTuples;
	/// Tuple2
	SoMFVariant Tuple2;
	/// NumberOfValues of type vtkIdType
	SoSFVtkObject NumberOfValues;
	/// Name
	SoMFString Name;
	/// Tuple4
	SoMFVariant Tuple4;

	
	// Outputs
	/// SoSFVtkObject of type vtkLookupTable
	SoEngineOutput oLookupTable;
	/// SoSFVtkObject of type CharArray
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkCharArray();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkLookupTable
	SoVtkObject *mLookupTable;

	/// vtkCharArray
	SoVtkObject *mOutput;


private:

	vtkCharArray* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_CHARARRAY_H_

