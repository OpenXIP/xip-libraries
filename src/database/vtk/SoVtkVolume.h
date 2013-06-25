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
 * \file SoVtkVolume.h
 *
 * \brief SoVtkVolume class description.
 *
 */

#ifndef SO_VTK_VOLUME_H_
# define SO_VTK_VOLUME_H_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSubNode.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include <Inventor/fields/SoSFVec3f.h>

#include "xip/inventor/vtk/SoSFVtkObject.h"
#include "vtkVolume.h"

/*!
 * \brief
 * SoVtkVolume class description.
 *
 * A SoVtkVolume gets the mapping information from a SoVtkDataMapper,
 * and its properties from a SoVtkDataVolumeProperty. It must be
 * attached to a SoVtkRenderer or a SoVtkAssembly to be renderered.
 *
 * \see SoVtkRenderer
 * \see SoVtkAssembly
 * \see SoVtkDataMapper
 * \see SoVtkDataVolumeProperty
 *
 */
class SoVtkVolume : public SoNode
{
	SO_NODE_HEADER(SoVtkVolume);

public :
    /// Constructor.
    SoVtkVolume();

	/// Mapper input
	SoSFVtkObject	Mapper;
	/// Property input
	SoSFVtkObject	Property;

	// Other inputs
	/// Position
	SoSFVec3f		Position;
	/// Origin
	SoSFVec3f		Origin;

	/// Class initialization.
	static void		initClass();

	/// Get the current volume.
	vtkVolume			*getVolume() const;


protected :
    /// Destructor.
    virtual			~SoVtkVolume();
	
	/// GLRender
	virtual void		GLRender(SoGLRenderAction *action);

	/// Get bounging box function
	virtual void		getBoundingBox(SoGetBoundingBoxAction *action);

private :

    vtkVolume			*mVolume;
};

#endif // SO_VTK_VOLUME_H_



