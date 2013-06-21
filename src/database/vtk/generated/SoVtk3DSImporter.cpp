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
 
 
 
# include "SoVtk3DSImporter.h"
# include "SoVtkUtils.h"

# include "vtkRenderWindow.h"
# include "vtkRenderer.h"


SO_ENGINE_SOURCE( SoVtk3DSImporter )

SoVtk3DSImporter::SoVtk3DSImporter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtk3DSImporter);

	mObject = vtk3DSImporter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtk3DSImporter *a3DSImporter = vtk3DSImporter::New();

	SO_ENGINE_ADD_INPUT(RenderWindow, (0));

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(ComputeNormals, (0));
	ComputeNormals.setValue(a3DSImporter->GetComputeNormals());

	a3DSImporter->Delete();

	SO_ENGINE_ADD_OUTPUT( oRenderWindow, SoSFVtkObject );
	mRenderWindow = 0;

	SO_ENGINE_ADD_OUTPUT( oRenderer, SoSFVtkObject );
	mRenderer = 0;

	addCalled = 0;
}

SoVtk3DSImporter::~SoVtk3DSImporter()
{
	// Deletion of the objects if they exist
	if ( mRenderWindow )
	{
	
		mRenderWindow->unref();
		mRenderWindow = 0;
	}
	
	if ( mRenderer )
	{
	
		mRenderer->unref();
		mRenderer = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtk3DSImporter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtk3DSImporter, SoEngine, "Engine" );
}

void SoVtk3DSImporter::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mRenderWindow )
		{
		
			mRenderWindow->unref();
			mRenderWindow = 0;
		}
		
		if ( mRenderer )
		{
		
			mRenderer->unref();
			mRenderer = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetRenderWindow();
		mRenderWindow = new SoVtkObject();
		mRenderWindow->ref();
		mRenderWindow->setPointer( mObject->GetRenderWindow() );

		mObject->GetRenderer();
		mRenderer = new SoVtkObject();
		mRenderer->ref();
		mRenderer->setPointer( mObject->GetRenderer() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oRenderWindow, SoSFVtkObject, setValue( mRenderWindow ) );
	SO_ENGINE_OUTPUT( oRenderer, SoSFVtkObject, setValue( mRenderer ) );
}


void SoVtk3DSImporter::inputChanged(SoField * f)
{
	// Get the RenderWindow value
	if ( f == &RenderWindow )
		SO_VTK_SET_FIELD_DATA( mObject, RenderWindow, vtkRenderWindow);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the ComputeNormals value
	if ( f == &ComputeNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

}

void SoVtk3DSImporter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtk3DSImporter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the RenderWindow value
	
		SO_VTK_SET_FIELD_DATA( mObject, RenderWindow, vtkRenderWindow);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the ComputeNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

}

