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
/*
 * \author Sylvain Jaume, Francois Huguet
 */
#ifndef SO_VTK_COLORTRANSFERFUNCTION_H_
#define SO_VTK_COLORTRANSFERFUNCTION_H_

#include <Inventor/engines/SoSubEngine.h>

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>

#include <xip/inventor/vtk/SoSFVtkAlgorithmOutput.h>
#include <xip/inventor/vtk/SoSFVtkObject.h>
#include <xip/inventor/core/SoMFVariant.h>

#include "vtkColorTransferFunction.h"

class SoVtkColorTransferFunction : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkColorTransferFunction );

public:

	/// Constructor
	SoVtkColorTransferFunction();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// RGBSegment
	SoMFVariant RGBSegment;
	/// HSVWrap
	SoSFInt32 HSVWrap;
	/// VectorComponent
	SoSFInt32 VectorComponent;
	/// ColorSpace
	SoSFInt32 ColorSpace;
	/// Clamping
	SoSFInt32 Clamping;
	/// HSVSegment
	SoMFVariant HSVSegment;
	/// RGBPoint
	SoMFVariant RGBPoint;
	/// HSVPoint
	SoMFVariant HSVPoint;
	/// VectorMode
	SoSFInt32 VectorMode;
	/// Alpha
	SoSFFloat Alpha;

	
	// Outputs
	/// SoSFVtkObject of type vtkColorTransferFunction
	SoEngineOutput Output;

protected:

	/// Destructor
	~SoVtkColorTransferFunction();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkColorTransferFunction
	SoVtkObject *mOutput;

private:

	vtkColorTransferFunction* mObject;
};

#endif // SO_VTK_COLORTRANSFERFUNCTION_H_


