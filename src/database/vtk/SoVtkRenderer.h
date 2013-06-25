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
 * \file SoVtkRenderer.h
 *
 * \brief SoVtkRenderer class description.
 * \author Sylvain Jaume, Francois Huguet
 */

#ifndef SO_VTKRENDERER_H
#define SO_VTKRENDERER_H

#include <vector>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/misc/SoState.h>

#include <Inventor/actions/SoGLRenderAction.h>

#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>

#include "xip/inventor/vtk/SoSFVtkObject.h"

#include "vtkOpenGLRenderer.h"
#include "vtkRenderWindow.h"

#include <xip/system/GL/gl.h>	// Header File For The OpenGL32 Library
#include <xip/system/GL/glu.h>	// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library

/*!
 * \brief
 * SoVtkRenderer class description.
 *
 *  This node allows the user to instanciate a vtkRenderer so as to add
 *  some volumes or actors to it. The renderer has to be plugged to
 *  a VTK render window to work. The viewport and the window center of this
 *  class define the position of the renderer in the render window.
 *
 * \see SoVtkActor
 * \see SoVtkImageActor
 * \see SoVtkActor2D
 * \see SoVtkVolume
 */
class SoVtkRenderer : public SoGroup
{
  SO_NODE_HEADER( SoVtkRenderer );

public:
  /// Constructor.
  SoVtkRenderer();

  /// Class initialization.
  static void initClass();

  /// Get XIP camera information and update the VTK camera.
  void	updateCamera(SoState *state);

  /// Get directly all the children of the renderer.
  void updateChildren();

  enum StereoModeEnum
  {
	Anaglyph,
	CrystalEyes,
	Dresden,
	Interlaced,
	Left,
	RedBlue,
	Right
  };

  SoSFEnum	StereoMode;
  SoSFBool	StereoRender;
  SoSFVec3f	Background;

  void normalize(SbVec3f& );

  vtkOpenGLRenderer * getRenderer() const;
  vtkRenderWindow * getRenderWindow() const;
  virtual void	GLRender( SoGLRenderAction* action );

protected:
  /// Destructor.
  ~SoVtkRenderer();

  vtkOpenGLRenderer  *mRen;
  vtkRenderWindow    *mRenWin;

  /// Update the stereo render mode.
  void		updateStereoMode();
  /// Update the window size of the vtk window.
  void		updateRenderWindowSize(SoState *state);
#ifdef WIN32
  HGLRC		mRC;
#endif // WIN32
  int lastStereo;
  int mNodeId;
};

#endif //  SO_VTKRENDERER_H



