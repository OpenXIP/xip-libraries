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
 * \file SoVtkLODActor.h
 * \brief SoVtkLODActor class description.
 *
 */

#ifndef SO_VTK_LODACTOR_H_
#define SO_VTK_LODACTOR_H_

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoNode.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>

#include "xip/inventor/vtk/SoSFVtkObject.h"
#include "vtkLODActor.h"

/*!
 * \brief
 * SoVtkLODActor is an actor that supports multiple levels of detail.
 *
 * From VTK:
 * vtkLODActor is an actor that stores multiple levels of detail (LOD)
 * and can automatically switch between them. It selects which level
 * of detail to use based on how much time it has been allocated to
 * render.
 * There are three levels of detail by default. The top level is just
 * the normal data. The lowest level of detail is a simple bounding box
 * outline of the actor. The middle level of detail is a point cloud
 * of a fixed number of points that have been randomly sampled from
 * the mapper's input data. Point attributes are copied over to the
 * point cloud. These two lower levels of detail are accomplished by
 * creating instances of a vtkOutlineFilter (low-res) and vtkMaskPoints
 * (medium-res). Additional levels of detail can be add using the AddLODMapper()
 * method.
 *
 *
 * \see SoVtkRenderer
 * \see SoVtkActor2D
 * \see SoVtkAssembly
 * \see SoVtkImageActor
 * \see SoVtkActor
 */
class SoVtkLODActor : public SoNode
{
	SO_NODE_HEADER(SoVtkLODActor);

public:

	/// Constructor.
	SoVtkLODActor();

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
	static void initClass();

	/// Get the current actor.
	vtkLODActor *getLODActor() const;


protected:

	/// Destructor.
	virtual ~SoVtkLODActor();

	/// GLRender
	virtual void GLRender(SoGLRenderAction *action);

	/// Get bounging box function
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);

private:

	/// vtkLODActor object
	vtkLODActor		*mActor;
};

#endif // SO_VTK_LODACTOR_H_


