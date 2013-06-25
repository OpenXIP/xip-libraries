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
 * \file SoVtkImageViewer2.cpp
 * \brief Implementation of the SoVtkImageViewer2 node
 * \author Sylvain Jaume, Francois Huguet
 */

#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoFocalDistanceElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoComplexityElement.h>

#include "xip/inventor/vtk/SoVtkAlgorithmOutput.h"
#include "xip/inventor/vtk/SoVtkObject.h"
#include <xip/system/GL/gl.h>

#include "vtkImageData.h"
#include "vtkImageActor.h"
#include "vtkCamera.h"
#include "vtkRenderer.h"

#include "SoVtkImageViewer2.h"

#define pi 3.14159265358979323846

SO_NODE_SOURCE(SoVtkImageViewer2);

SoVtkImageViewer2::SoVtkImageViewer2()
{
  SO_NODE_CONSTRUCTOR(SoVtkImageViewer2);

  // Initializations
  mViewer = vtkImageViewer2::New();
  mViewer->Register(0);

  mRenWin = new myRenderWindow;
  mRenWin->Register(0);
  // We need to give the viewer the render window from Rad to draw in the same context as Rad
  mViewer->SetRenderWindow(mRenWin);

  SO_NODE_ADD_FIELD( InputConnection, (0) );
  SO_NODE_ADD_FIELD( Input, (0) );
  SO_NODE_ADD_FIELD( BitsUsed, (8));
  SO_NODE_ADD_FIELD( Window, (0) );
  SO_NODE_ADD_FIELD( Level, (0) );

  SO_NODE_DEFINE_ENUM_VALUE( SliceOrientationEnum, XY );
  SO_NODE_DEFINE_ENUM_VALUE( SliceOrientationEnum, XZ );
  SO_NODE_DEFINE_ENUM_VALUE( SliceOrientationEnum, YZ );

  SO_NODE_SET_SF_ENUM_TYPE( SliceOrientation, SliceOrientationEnum );
  SO_NODE_ADD_FIELD( SliceOrientation, (XY) );
	
  SO_NODE_ADD_FIELD( SliceIndex , (0) );
  SO_NODE_ADD_FIELD( NextSlice , () );
  SO_NODE_ADD_FIELD( PreviousSlice, () );
	
  mNextSensor = new SoFieldSensor( &onNextCallback, this );
  mNextSensor->attach( &NextSlice );
  mNextSensor->setPriority(0);

  mPreviousSensor = new SoFieldSensor( &onPreviousCallback, this );
  mPreviousSensor->attach( &PreviousSlice );
  mPreviousSensor->setPriority(0);

  mMin = 0;
  mMax = 0;
#ifdef WIN32
  mRC = 0;
#endif // WIN32
}

////////////// CALLBACKS METHODS /////////////

void
SoVtkImageViewer2::onNextCallback( void* user, SoSensor* sensor )
{
	SoVtkImageViewer2 *viewer = (SoVtkImageViewer2*) user;
	if( viewer )
		viewer->nextSlice();
}

void
SoVtkImageViewer2::nextSlice()
{
	if (SliceIndex.getValue() < mMax)
	{
		SliceIndex.setValue(SliceIndex.getValue()+1);
		mViewer->SetSlice(SliceIndex.getValue());
	}
}

void
SoVtkImageViewer2::onPreviousCallback( void* user, SoSensor* sensor )
{
	SoVtkImageViewer2 *viewer = (SoVtkImageViewer2*) user;
	if( viewer )
		viewer->previousSlice();
}

void
SoVtkImageViewer2::previousSlice()
{
	if (SliceIndex.getValue() > mMin)
	{
		SliceIndex.setValue(SliceIndex.getValue()-1);
		mViewer->SetSlice(SliceIndex.getValue());
	}
}

SoVtkImageViewer2::~SoVtkImageViewer2()
{
	if (mViewer)
	{
		mViewer->UnRegister(0);
		mViewer->Delete();
		mViewer = 0;
	}
}

void SoVtkImageViewer2::initClass()
{
  SO_NODE_INIT_CLASS(SoVtkImageViewer2, SoNode, "Node" );
}

void SoVtkImageViewer2::getBoundingBox(SoGetBoundingBoxAction *action)
{
	SbBox3f	bbox;
	SbVec3f	center;

	if (mViewer->GetImageActor())
	{
		const double *bounds = mViewer->GetImageActor()->GetBounds();
		SbBox3f bbox(bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5]);
		action->extendBy(bbox);
		action->setCenter(bbox.getCenter(), FALSE);
	}
}

             ///////////////// GLRENDER /////////////////

void SoVtkImageViewer2::GLRender(SoGLRenderAction *action)
{
  try
    {
    // Get the 2 inputs
    SoVtkObject *inputPtr = Input.getValue();

    if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
      {
      mViewer->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));
      }

    SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();

    if (inputPortPtr)
      {
      mViewer->SetInputConnection(inputPortPtr->getPointer());
      }
#ifdef WIN32
    // Update graphics/rendering context
    HGLRC currentContext = ::wglGetCurrentContext();

    if (mRC != currentContext)
    {
	mRC = currentContext;
	if (mViewer->GetRenderWindow())
	{
		mRenWin->SetDeviceContext(::wglGetCurrentDC());
		mRenWin->SetContextId(currentContext);
		mRenWin->SetSwapBuffers(0);
	}
	mRenWin->OpenGLInit();
    }
#endif // WIN32
    // Get the slice range
    mMin = mViewer->GetSliceMin();
    mMax = mViewer->GetSliceMax();

    // Update the slice orientation
    switch( SliceOrientation.getValue() )
    {
	case XY:
	{
	mViewer->SetSliceOrientationToXY();
	}
	break ;
	case XZ:
	{
	mViewer->SetSliceOrientationToXZ();
	}
	break ;
	case YZ:
	{
	mViewer->SetSliceOrientationToYZ();
	}
	break ;
    }

    // Set the slice index
    mViewer->SetSlice(SliceIndex.getValue());

    // Update the vtk camera according to the inventor state
    updateCamera(action->getState());

    // Render
    mRenWin->GLRender();
    }
    catch(...)
    {
    SoDebugError::post( __FILE__, "Unknown Exception" );
    return ;
    }
}

////////////// UPDATE METHODS ////////////

void SoVtkImageViewer2::updateCamera(SoState *state)
{

	// Get the viewport information about the scene.
	SbViewportRegion viewportRegion = SoViewportRegionElement::get(state);

	float X = viewportRegion.getWindowSize()[0];
	float Y = viewportRegion.getWindowSize()[1];

	float X_beg = viewportRegion.getViewportOrigin()[0];
	float Y_beg = viewportRegion.getViewportOrigin()[1];

	float view_X = viewportRegion.getViewportSize()[0];
	float view_Y = viewportRegion.getViewportSize()[1];

	float ratio = viewportRegion.getViewportAspectRatio();

	// Reset Renderer camera
	mViewer->GetRenderer()->ResetCamera();

	// Adjust camera depending if we do a stretch horizontally or vertically
	if (ratio < 1.0)
		mViewer->GetRenderer()->GetActiveCamera()->SetUseHorizontalViewAngle(1);
	else
		mViewer->GetRenderer()->GetActiveCamera()->SetUseHorizontalViewAngle(0);

	// Update the render window level and color
	int value = Window.getValue();
	if (value < 1)
	{
		double Bits = pow(2,(double) BitsUsed.getValue());
		mViewer->SetColorLevel(Level.getValue() * Bits );
		mViewer->SetColorWindow(Window.getValue() * Bits );
	}
	else
	{
		mViewer->SetColorLevel(Level.getValue());
		mViewer->SetColorWindow(Window.getValue());
	}
	
	// Set the viewport of the renderer
	mViewer->GetRenderer()->SetViewport(X_beg,Y_beg,X_beg+view_X,Y_beg+view_Y);

	// Set the size of the vtkRenderWindow.
	int x = floor(X + 0.5f);
	int y = floor(Y + 0.5f);
	mViewer->GetRenderWindow()->SetSize(x, y);  
}



