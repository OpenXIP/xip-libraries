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
 * \file SoVtkImageViewer2.h
 * \brief XIP wrapping of SoVtkImageViewer2
 * \author Sylvain Jaume (Siemens Corporate Research), Francois Huguet
 */
#ifndef SO_VTK_IMAGEVIEWER2_H
#define SO_VTK_IMAGEVIEWER2_H

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoNode.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFTrigger.h>

#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/misc/SoState.h>

#include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
#include "xip/inventor/vtk/SoSFVtkObject.h"

#include <xip/system/GL/gl.h>
#include <xip/system/GL/glu.h>

#include "vtkImageViewer2.h"

#ifdef WIN32
#include "vtkWin32OpenGLRenderWindow.h"
class myRenderWindow : public vtkWin32OpenGLRenderWindow
#elif linux
#include "vtkXOpenGLRenderWindow.h"
class myRenderWindow : public vtkXOpenGLRenderWindow
#elif DARWIN
#include "vtkCocoaRenderWindow.h" //"vtkCarbonRenderWindow.h"
class myRenderWindow : public vtkCocoaRenderWindow //vtkCarbonRenderWindow
#endif
{
public:
  void Render()
  {
  // notify Inventor instead of rendering...
  //SoDebugError::postInfo("myRenderWindow::Render", "called");
  }

  void GLRender()
  {
  // vtk multiplies to the current modelview matrix, therefore set it to identity
  glLoadIdentity();
  // really does render (called by GLRender method of Inventor node)
  vtkRenderWindow::Render();
  }
};

/*!
 * \brief
 * SoVtkImageViewer2 wraps vtkImageViewer2. Displays a 2D image.
 * 
 * From VTK:
 * vtkImageViewer2 is a convenience class for displaying a 2D image. It
 * packages up the functionality found in vtkRenderWindow, vtkRenderer,
 * vtkImageActor and vtkImageMapToWindowLevelColors into a single easy to use
 * class. The image is placed in the 3D scene at a depth based on the
 * z-coordinate of the particular image slice. Each call to
 * Next/PreviousSlice() changes the image data (slice) displayed AND changes
 * the depth of the displayed slice in the 3D scene.
 * 
 * \see
 * SoVtkWin32OpenGLRenderWindow | SoVtkRenderer | SoVtkImageActor 
 */
class SoVtkImageViewer2 : public SoNode
{
	SO_NODE_HEADER(SoVtkImageViewer2);

  /// Orientation Enum.
  enum SliceOrientationEnum
    {
      XY,
      XZ,
      YZ
    };

public :

	/// Constructor
	SoVtkImageViewer2();

	/// Class Initialization
	static void		initClass();

	/// Input connection
	SoSFVtkAlgorithmOutput InputConnection;
	/// Input data
	SoSFVtkObject Input;
	/// Bits used per pixel
	SoSFInt32  BitsUsed;
	/// Window color
	SoSFFloat Window;
	/// Window level
	SoSFFloat Level;
	/// Slice Orientation enumeration.
	SoSFEnum   SliceOrientation;
	/// Slice index
	SoSFInt32	SliceIndex;
	/// Next Slice
	SoSFTrigger	NextSlice;
	/// Previous Slice
	SoSFTrigger	PreviousSlice;

protected :

	/// Destructor
	virtual ~SoVtkImageViewer2();

	/// GLRender
	virtual void	GLRender(SoGLRenderAction *action);

	/// Handle the next slice
	static void	onNextCallback( void* user, SoSensor* sensor );

	/// Go to the next slice
	virtual void	nextSlice();

	/// Handle the previous slice
	static void	onPreviousCallback( void* user, SoSensor* sensor );

	/// Go to the previous slice
	virtual void	previousSlice();

	/// Get RAD camera information and update the VTK camera.
	void		updateCamera(SoState *state);

	void getBoundingBox(SoGetBoundingBoxAction *action);

private:

	/// Slice min
	int mMin;

	/// Slice max
	int mMax;
#ifdef WIN32
	/// Current context
	HGLRC		mRC;
#endif
	/// OpenGL render Window
	myRenderWindow *mRenWin;

	/// Image Viewer
	vtkImageViewer2	*mViewer;

	SoFieldSensor*	mNextSensor;
	SoFieldSensor*	mPreviousSensor;

};

#endif // SO_VTK_IMAGEVIEWER2_H



