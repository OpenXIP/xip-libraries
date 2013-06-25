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
 * \file SoVtkObject.cpp
 *
 * \brief SoVtkObject class implementation.
 *
 */

#include "xip/inventor/vtk/SoVtkObject.h"
#include "vtkObject.h"

XIP_DATA_SOURCE( SoVtkObject );

SoVtkObject::SoVtkObject()
{
  XIP_DATA_CONSTRUCTOR( SoVtkObject );
  mData = 0;
}

SoVtkObject::~SoVtkObject()
{
}

void
SoVtkObject::initClass()
{
  XIP_DATA_INIT_CLASS( SoVtkObject, SoXipData, "SoXipData" );
}

void
SoVtkObject::setPointer( vtkObject* data )
{
  mData = data;
}

vtkObject*
SoVtkObject::getPointer() const
{
  return mData;
}
