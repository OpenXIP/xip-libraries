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
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */

#include "SoVtkAttributesErrorMetric.h"
#include "SoVtkUtils.h"

#include "vtkGenericAdaptorCell.h"
#include "vtkGenericDataSet.h"

SO_ENGINE_SOURCE( SoVtkAttributesErrorMetric )

SoVtkAttributesErrorMetric::SoVtkAttributesErrorMetric()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkAttributesErrorMetric);

	mObject = vtkAttributesErrorMetric::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkAttributesErrorMetric *aAttributesErrorMetric =
				 vtkAttributesErrorMetric::New();

	SO_ENGINE_ADD_INPUT(GenericCell, (0));

	SO_ENGINE_ADD_INPUT(DataSet, (0));

	SO_ENGINE_ADD_INPUT(AttributeTolerance, (0));
	SO_ENGINE_ADD_INPUT(AbsoluteAttributeTolerance, (0));
	aAttributesErrorMetric->Delete();

	SO_ENGINE_ADD_OUTPUT( oGenericCell, SoSFVtkObject );
	mGenericCell = 0;

	SO_ENGINE_ADD_OUTPUT( oDataSet, SoSFVtkObject );
	mDataSet = 0;

	addCalled = 0;
}

SoVtkAttributesErrorMetric::~SoVtkAttributesErrorMetric()
{
	// Deletion of the objects if they exist
	if ( mGenericCell )
	{
		mGenericCell->unref();
		mGenericCell = 0;
	}
	
	if ( mDataSet )
	{
		mDataSet->unref();
		mDataSet = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
}

void SoVtkAttributesErrorMetric::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkAttributesErrorMetric, SoEngine, "Engine" );
}

void SoVtkAttributesErrorMetric::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mGenericCell )
		{
			mGenericCell->unref();
			mGenericCell = 0;
		}
		
		if ( mDataSet )
		{
			mDataSet->unref();
			mDataSet = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetGenericCell();
		mGenericCell = new SoVtkObject();
		mGenericCell->ref();
		mGenericCell->setPointer( mObject->GetGenericCell() );

		mObject->GetDataSet();
		mDataSet = new SoVtkObject();
		mDataSet->ref();
		mDataSet->setPointer( mObject->GetDataSet() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oGenericCell, SoSFVtkObject, setValue( mGenericCell ) );
	SO_ENGINE_OUTPUT( oDataSet, SoSFVtkObject, setValue( mDataSet ) );
}


void SoVtkAttributesErrorMetric::inputChanged(SoField * f)
{
	// Get the GenericCell value
	if ( f == &GenericCell )
		SO_VTK_SET_FIELD_DATA( mObject, GenericCell, vtkGenericAdaptorCell);

	// Get the DataSet value
	if ( f == &DataSet )
		SO_VTK_SET_FIELD_DATA( mObject, DataSet, vtkGenericDataSet);

	// Get the AttributeTolerance value
	if ( f == &AttributeTolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, AttributeTolerance);

	// Get the AbsoluteAttributeTolerance value
	if ( f == &AbsoluteAttributeTolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteAttributeTolerance);

}

void SoVtkAttributesErrorMetric::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkAttributesErrorMetric::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the GenericCell value
	
		SO_VTK_SET_FIELD_DATA( mObject, GenericCell, vtkGenericAdaptorCell);

	// Get the DataSet value
	
		SO_VTK_SET_FIELD_DATA( mObject, DataSet, vtkGenericDataSet);

	// Get the AttributeTolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AttributeTolerance);

	// Get the AbsoluteAttributeTolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteAttributeTolerance);

}

