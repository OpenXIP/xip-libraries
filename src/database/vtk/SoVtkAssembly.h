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
 * \file SoVtkAssembly.h
 * \brief XIP wrapping of vtkAssembly
 * \author Sylvain Jaume (Siemens Corporate Research), Francois Huguet
 */

#ifndef SO_VTK_ASSEMBLY_H_
# define SO_VTK_ASSEMBLY_H_

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/fields/SoSFVec3f.h>

#include "vtkAssembly.h"

/*!
 * \brief
 * SoVtkAssembly class description.
 *
 * vtkAssembly is an object that groups vtkProp3Ds, its subclasses, and other assemblies into a tree-like hierarchy. The vtkProp3Ds and assemblies can then be transformed together by transforming just the root assembly of the hierarchy.
 *
 * \see SoVtkRenderer
 * \see SoVtkActor2D
 * \see SoVtkActor
 * \see SoVtkImageActor
 * \see SoVtkVolume
 */
class SoVtkAssembly : public SoGroup
{
	SO_NODE_HEADER(SoVtkAssembly);
	
public :
	/// Constructor.
	SoVtkAssembly();

	/// Position
	SoSFVec3f			Position;
	/// Origin
	SoSFVec3f			Origin;
	
	/// Class initialization.
	static void initClass();

	/// Get the current assembly.
	vtkAssembly * getAssembly() const;
	
	/// Get directly all the children of the assembly.
#if (defined linux) || defined (__APPLE__)
	void updateChildren();
#else // linux
	void SoVtkAssembly::updateChildren();
#endif // linux
protected :

	/// Destructor.
	virtual ~SoVtkAssembly();

	virtual void GLRender(SoGLRenderAction *action);
	virtual void		getBoundingBox(SoGetBoundingBoxAction *action);
	

private :

	vtkAssembly			*mAssembly;
	int					nodeId;
};

#endif // SO_VTK_ASSEMBLY_H_


