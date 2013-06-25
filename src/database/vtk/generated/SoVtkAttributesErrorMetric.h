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
 
 
 
# ifndef SO_VTK_ATTRIBUTESERRORMETRIC_H_
# define SO_VTK_ATTRIBUTESERRORMETRIC_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkAttributesErrorMetric.h"

# include "Inventor/fields/SoSFFloat.h"

class SoVtkAttributesErrorMetric : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkAttributesErrorMetric );

public:

	/// Constructor
	SoVtkAttributesErrorMetric();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// GenericCell of type vtkGenericAdaptorCell
	SoSFVtkObject GenericCell;
	/// DataSet of type vtkGenericDataSet
	SoSFVtkObject DataSet;
	/// AttributeTolerance
	SoSFFloat AttributeTolerance;
	/// AbsoluteAttributeTolerance
	SoSFFloat AbsoluteAttributeTolerance;

	
	// Outputs
	/// SoSFVtkObject of type vtkGenericAdaptorCell
	SoEngineOutput oGenericCell;
	/// SoSFVtkObject of type vtkGenericDataSet
	SoEngineOutput oDataSet;

protected:

	/// Destructor
	~SoVtkAttributesErrorMetric();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkGenericAdaptorCell
	SoVtkObject *mGenericCell;

	/// vtkGenericDataSet
	SoVtkObject *mDataSet;


private:

	vtkAttributesErrorMetric* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_ATTRIBUTESERRORMETRIC_H_

