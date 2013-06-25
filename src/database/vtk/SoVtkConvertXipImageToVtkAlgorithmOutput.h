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
/*!
 * \file SoVtkConvertXipImageToVtkAlgorithmOutput.h
 *
 * \brief SoVtkConvertXipImageToVtkAlgorithmOutput class description.
 *
 */

#ifndef SO_VTK_CONVERTXIPIMAGETOVTKALGORITHMOUTPUT_H_
#define SO_VTK_CONVERTXIPIMAGETOVTKALGORITHMOUTPUT_H_

#include <Inventor/engines/SoFieldConverter.h>
#include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>

#include "vtkImageFlip.h"


/*!
 * \brief
 * Convert xipImage to vtkAlgorithmOutput data.
 *
 * This engine gets a xipImage and produces an ImageData embedded in a
 * vtkAlgorithmOutput. It gets the dimensions, the number of
 * components and the scalar type of the incoming image to produce the
 * output.
 *
 */
class SoVtkConvertXipImageToVtkAlgorithmOutput : public SoFieldConverter
{
	SO_ENGINE_HEADER( SoVtkConvertXipImageToVtkAlgorithmOutput );

public:

	/// Constructor
	SoVtkConvertXipImageToVtkAlgorithmOutput();

	/// Open Inventor class initialization
	static void initClass();

	/// Input Image
	SoXipSFDataImage Input;

	/// Output Algo
	SoEngineOutput OutputPort;

private:

	/// Destructor
	~SoVtkConvertXipImageToVtkAlgorithmOutput();

	/// Evaluation method
	virtual void evaluate();

	/// Return the input defined by the given type
	virtual SoField* getInput( SoType type );

	/// Return the output defined by the given type
	virtual SoEngineOutput* getOutput( SoType type );

protected:

	/// Instance of the vtkImageFlip to return the image.
	vtkImageFlip			*mFlip;

	/// Data wrapper for the AlgorithmOutput output object.
	SoVtkAlgorithmOutput		*mAlgorithmOutput;
};

#endif /// SO_VTK_CONVERTXIPIMAGETOVTKALGORITHMOUTPUT_H_
