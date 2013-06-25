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
 * \file SoVtkImageActor.h
 *
 * \brief SoVtkImageActor class description.
 *
 */

#ifndef SO_VTK_IMAGE_ACTOR_H_
# define SO_VTK_IMAGE_ACTOR_H_

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include "xip/inventor/vtk/SoSFVtkObject.h"
#include "vtkImageActor.h"


/*!
 * \brief
 * SoVtkImageActor class description.
 *
 * vtkImageActor is used to render an image (data & properties) in a
 * rendered 3D scene.
 *
 *
 * \see SoVtkRenderer
 * \see SoVtkActor2D
 * \see SoVtkAssembly
 * \see SoVtkActor
 *
 */
class SoVtkImageActor : public SoNode
{
	SO_NODE_HEADER(SoVtkImageActor);

public :

	/// Constructor.
	SoVtkImageActor();

	/// Class initialization.
	static void initClass();

	/// Get the current imageActor.
	vtkImageActor *getVtkImageActor() const;

	/// Image Input
	SoSFVtkObject Input;

	/// Get actor input
	vtkImageActor * getImageActor() const;


protected :

	/// Destructor
	virtual ~SoVtkImageActor();

	/// GLRender
	virtual void GLRender(SoGLRenderAction *action);

	/// Get Bounding box
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);


private :

	vtkImageActor		*mActor;
};

#endif // SO_VTK_IMAGE_ACTOR_H_


