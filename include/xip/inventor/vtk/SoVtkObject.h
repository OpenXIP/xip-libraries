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
 * \file SoVtkObject.h
 *
 * \brief SoVtkObject class description.
 */

#ifndef SO_VTK_OBJECT_H_
# define SO_VTK_OBJECT_H_

# include <xip/inventor/core/SoXipData.h>
# include <xip/inventor/core/SoXipSubData.h>
# include "xipivvtk.h"
# include "vtkObject.h"

/*!
 * \brief
 * SoVtkObject class description.
 *
 * This class enables the transfer of object information between
 * Xipbuilder elements. Every class enabling information transfer
 * between xip modules is designed the same way. First,
 * SoVtk<className> objects contain pointer to the data of type
 * vtk<className> to be transfered. Secondly, SoVtkSF<className>
 * objects enable the connection to the xip fields.
 *
 * \see SoVtkSFObject
 */
class XIPIVVTK_API SoVtkObject : public SoXipData
{
	XIP_DATA_HEADER( SoVtkObject );

public:
	/// Constructor.
	SoVtkObject();

	/// Class initialization.
	static void	initClass();

	/// Set the data to the given pointer.
	void		setPointer(vtkObject *);
	/// Get the current pointer of vtkObject contained in the class instance.
	vtkObject	*getPointer() const;

protected:
	/// Destructor.
	~SoVtkObject();
	/// Pointer to the vtkObject* data.
	vtkObject	*mData;
};

#endif // SO_VTK_OBJECT_H_
