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

# ifndef SO_VTK_LOOKUPTABLE_H_
# define SO_VTK_LOOKUPTABLE_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkLookupTable.h"

# include "Inventor/fields/SoSFInt32.h"
# include <xip/inventor/core/SoSFVariant.h>
# include "Inventor/fields/SoSFVec2f.h"
# include "Inventor/fields/SoSFFloat.h"

class SoVtkLookupTable : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkLookupTable );

public:

	/// Constructor
	SoVtkLookupTable();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// VectorComponent
	SoSFInt32 VectorComponent;
	/// TableRange
	SoSFVariant TableRange;
	/// ValueRange
	SoSFVec2f ValueRange;
	/// SaturationRange
	SoSFVec2f SaturationRange;
	/// Ramp
	SoSFInt32 Ramp;
	/// Scale
	SoSFInt32 Scale;
	/// AlphaRange
	SoSFVec2f AlphaRange;
	/// Table of type vtkUnsignedCharArray
	SoSFVtkObject Table;
	/// HueRange
	SoSFVec2f HueRange;
	/// VectorMode
	SoSFInt32 VectorMode;
	/// Alpha
	SoSFFloat Alpha;

	
	// Outputs
	/// SoSFVtkObject of type vtkLookupTable
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkLookupTable();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkLookupTable
	SoVtkObject *mOutput;

private:

	vtkLookupTable* mObject;
};

#endif // SO_VTK_LOOKUPTABLE_H_

