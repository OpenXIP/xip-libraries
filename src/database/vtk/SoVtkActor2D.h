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
 * \file SoVtkActor2D.h
 * \brief Wrapping of vtkActor2D
 * \author Sylvain Jaume (Siemens Corporate Research), Francois Huguet
 * A vtkActor2D has a mapper as input.
 * It must be connected to a SoVtkRenderer.
 *
 * \see SoVtkRenderer
 * \see SoVtkActor
 * \see SoVtkAssembly
 * \see SoVtkImageActor
 *
 * 
 */
#ifndef _SO_VTK_ACTOR2D_H_
#define _SO_VTK_ACTOR2D_H_

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include <xip/inventor/vtk/SoSFVtkObject.h>
#include <vtkActor2D.h>

class SoVtkActor2D : public SoNode
{
	SO_NODE_HEADER(SoVtkActor2D);

 public:

	/// Constructor.
	SoVtkActor2D();

	/// Input Mapper
	SoSFVtkObject Mapper;

	///Class initialization.
	static void initClass();

	/// Get the current actor.
	vtkActor2D *getActor2D() const;

protected:

	/// Destructor.
	virtual ~SoVtkActor2D();

	virtual void GLRender(SoGLRenderAction *action);
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);

private:

	/// Pointer to the vtkActor2D object.
	vtkActor2D	*mActor;
};

#endif // _SO_VTK_ACTOR2D_H_


