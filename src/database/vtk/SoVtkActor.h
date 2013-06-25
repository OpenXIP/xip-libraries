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
 * \file SoVtkActor.h
 * \author Francois Huguet (francois.huguet.ext@siemens.com)
 * \brief SoVtkActor class description.
 *
 */

#ifndef SO_VTK_ACTOR_H_
#define SO_VTK_ACTOR_H_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSubNode.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>

#include "xip/inventor/vtk/SoSFVtkObject.h"
#include "vtkActor.h"

/*!
 * \brief
 * SoVtkActor class description.
 *
 * A vtkActor has a mapper as input or a texture.
 * You have then to connect it to a SoVtkRenderer or a SoVtkAssembly
 * to render it.
 *
 * \see SoVtkRenderer
 * \see SoVtkActor2D
 * \see SoVtkAssembly
 * \see SoVtkImageActor
 */
class SoVtkActor : public SoNode
{
	SO_NODE_HEADER(SoVtkActor);
 
public:
	/// Constructor.
	SoVtkActor();


	/// Mapper input
	SoSFVtkObject	Mapper;
	/// Property input
	SoSFVtkObject	Property;
	/// BackfaceProperty input
	SoSFVtkObject	BackfaceProperty;
	/// Texture input
	SoSFVtkObject	Texture;


	// Other inputs
	/// Pickable
	SoSFInt32		Pickable;
	/// Visibility
	SoSFInt32		Visibility;
	/// Position
	SoSFVec3f		Position;
	/// Origin
	SoSFVec3f		Origin;
	/// Orientation
	SoSFVec3f		Orientation;
	/// Scale
	SoSFVec3f		Scale;


	/// Class initialization.
	static void		initClass();

	/// Get the current actor.
	vtkActor*		getActor() const;


protected:

	/// Destructor.
	virtual			~SoVtkActor();

	/// GLRender
	virtual void		GLRender(SoGLRenderAction *action);

	/// Get bounging box function
	virtual void		getBoundingBox(SoGetBoundingBoxAction *action);

private:

	/// vtkActor object
	vtkActor*			mActor;
};

#endif // SO_VTK_ACTOR_H_


