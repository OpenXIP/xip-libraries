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
 * \file SoVtkMatrix4x4.h
 *\brief Declaration of the SoVtkMatrix4x4 engine
 * 
 */
#ifndef SO_VTK_MATRIX4x4_H_
#define SO_VTK_MATRIX4x4_H_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFMatrix.h>

#include "vtkMatrix4x4.h"
#include "xip/inventor/vtk/SoSFVtkObject.h"

/*!
 * \brief
 * SoVtkMatrix4x4 wraps vtkMatrix4x4.
 * 
 * From VTK:
 * Represent and manipulate 4x4 transformation matrices.
 * vtkMatrix4x4 is a class used to represent and manipulate 4x4 matrices.
 * Specifically, it is designed to work on 4x4 transformation matrices found
 * in 3D rendering using homogeneous coordinates [x y z w].
 * 
 * \see
 * SoVtkTransform
 */
class SoVtkMatrix4x4 : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkMatrix4x4 );

public:	
	/// Constructor
	SoVtkMatrix4x4();
	/// Class initialization
	static void	initClass();
	/// Input Matrix
	SoSFMatrix	Matrix;

	/// SoVtkObject
	SoEngineOutput	Output; 

protected:
	/// Destructor
	~SoVtkMatrix4x4();
	/// Output matrix
	SoVtkObject	*mOutput;
	/// Evaluate function
	virtual void	evaluate();
	
private :
	/// vtkMatrix4x4 object
	vtkMatrix4x4	*mMat;

};

#endif // SO_VTK_MATRIX4x4_H_



