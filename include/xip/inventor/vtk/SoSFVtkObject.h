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
 * \file SoSFVtkObject.h
 * \brief SoSFVtkObject class description.
 *
 */

#ifndef SO_SF_VTK_OBJECT_H_
# define SO_SF_VTK_OBJECT_H_

# include <xip/inventor/core/SoXipSFData.h>

# include "xip/inventor/vtk/SoVtkObject.h"

/*!
 * \brief
 * SoSFVtkObject class description.
 *
 * This class implements the fields that allow the vtkObject
 * object to send data to other xip modules.
 *
 * \see SoVtkObject
 *
 */
class XIPIVVTK_API SoSFVtkObject : public SoXipSFData
{
  XIP_SFDATA_HEADER( SoSFVtkObject, SoVtkObject );
};

#endif // SO_SF_VTK_OBJECT_H_
