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
 * \file SoVtkActor2D.cpp
 *
 * \brief SoVtkActor2D class implementation.
 *
 */

#include "SoVtkActor2D.h"

#include "vtkMapper2D.h"


SO_NODE_SOURCE(SoVtkActor2D);

SoVtkActor2D::SoVtkActor2D()
{
	SO_NODE_CONSTRUCTOR(SoVtkActor2D);
	mActor = vtkActor2D::New();
	mActor->Register(0);

	SO_NODE_ADD_FIELD( Mapper, (0) );

}

SoVtkActor2D::~SoVtkActor2D()
{
	if( mActor )
	{
		mActor->UnRegister(0);
		mActor->Delete();
		mActor = 0;
	}
}

void SoVtkActor2D::initClass()
{
  SO_NODE_INIT_CLASS(SoVtkActor2D, SoNode, "SoNode");
}

void SoVtkActor2D::getBoundingBox(SoGetBoundingBoxAction *action)
{
	SbBox3f	bbox;
	SbVec3f	center;

	if (mActor)
	{
		const double *bounds = mActor->GetBounds();
		SbBox3f bbox(bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5]);
		action->extendBy(bbox);
		action->setCenter(bbox.getCenter(), FALSE);
	}
}

void SoVtkActor2D::GLRender(SoGLRenderAction *action)
{
	try
	{
		// Get the input type(s)
		SoVtkObject *mapperPtr = Mapper.getValue();

		if (mapperPtr && mapperPtr->getPointer()->IsA("vtkMapper2D"))
			mActor->SetMapper(vtkMapper2D::SafeDownCast(mapperPtr->getPointer()));

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
}

vtkActor2D *
SoVtkActor2D::getActor2D() const
{
	return mActor;
}
