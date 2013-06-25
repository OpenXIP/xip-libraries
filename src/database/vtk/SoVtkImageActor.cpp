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
 * \file SoVtkImageActor.cpp
 *
 * \brief SoVtkImageActor class implementation.
 *
 */

#include "SoVtkImageActor.h"

#include "xip/inventor/vtk/SoVtkObject.h"

#include "vtkImageData.h"

SO_NODE_SOURCE(SoVtkImageActor);

SoVtkImageActor::SoVtkImageActor()
{
	SO_NODE_CONSTRUCTOR(SoVtkImageActor);

	mActor = vtkImageActor::New();
	mActor->Register(0);

	SO_NODE_ADD_FIELD( Input, (0) );
}

SoVtkImageActor::~SoVtkImageActor()
{
	if( mActor )
	{
		mActor->UnRegister(0);
		mActor->Delete();
		mActor = 0;
	}
}

void SoVtkImageActor::initClass()
{
  SO_NODE_INIT_CLASS(SoVtkImageActor, SoNode, "SoNode");
}



void SoVtkImageActor::GLRender(SoGLRenderAction *action)
{
	try
	{
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();

		if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
			mActor->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));
		if ( !inputPtr )
			mActor->SetInput(0);
		
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
}

void SoVtkImageActor::getBoundingBox(SoGetBoundingBoxAction *action)
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

vtkImageActor *
SoVtkImageActor::getImageActor() const
{
	return mActor;
}
