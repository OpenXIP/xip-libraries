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
 
 
 
# ifndef SO_VTK_CELLLOCATOR_H_
# define SO_VTK_CELLLOCATOR_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkCellLocator.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"

class SoVtkCellLocator : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkCellLocator );

public:

	/// Constructor
	SoVtkCellLocator();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// DataSet of type vtkDataSet
	SoSFVtkObject DataSet;
	/// RetainCellLists
	SoSFInt32 RetainCellLists;
	/// CacheCellBounds
	SoSFInt32 CacheCellBounds;
	/// NumberOfCellsPerBucket
	SoSFInt32 NumberOfCellsPerBucket;
	/// Automatic
	SoSFInt32 Automatic;
	/// MaxLevel
	SoSFInt32 MaxLevel;
	/// Tolerance
	SoSFFloat Tolerance;

	
	// Outputs
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput oDataSet;
	/// SoSFVtkObject of type CellLocator
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkCellLocator();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkDataSet
	SoVtkObject *mDataSet;

	/// vtkCellLocator
	SoVtkObject *mOutput;


private:

	vtkCellLocator* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_CELLLOCATOR_H_

