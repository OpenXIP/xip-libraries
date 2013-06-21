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
 
 
 
# ifndef SO_VTK_IMAGETOPOLYDATAFILTER_H_
# define SO_VTK_IMAGETOPOLYDATAFILTER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkImageToPolyDataFilter.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"

class SoVtkImageToPolyDataFilter : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageToPolyDataFilter );

public:

	/// Constructor
	SoVtkImageToPolyDataFilter();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// Decimation
	SoSFInt32 Decimation;
	/// LookupTable of type vtkScalarsToColors
	SoSFVtkObject LookupTable;
	/// SubImageSize
	SoSFInt32 SubImageSize;
	/// Error
	SoSFInt32 Error;
	/// OutputStyle
	SoSFInt32 OutputStyle;
	/// NumberOfSmoothingIterations
	SoSFInt32 NumberOfSmoothingIterations;
	/// DecimationError
	SoSFFloat DecimationError;
	/// ColorMode
	SoSFInt32 ColorMode;
	/// Smoothing
	SoSFInt32 Smoothing;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkScalarsToColors
	SoEngineOutput oLookupTable;

protected:

	/// Destructor
	~SoVtkImageToPolyDataFilter();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkPolyData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkScalarsToColors
	SoVtkObject *mLookupTable;


private:

	vtkImageToPolyDataFilter* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_IMAGETOPOLYDATAFILTER_H_

