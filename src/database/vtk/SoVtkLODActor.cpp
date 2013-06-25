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
 * \file SoVtkLODActor.cpp
 *
 * \brief SoVtkLODActor class implementation.
 *
 */

#include "SoVtkLODActor.h"

#include "SoVtkUtils.h"

#include "vtkMapper.h"
#include "vtkTexture.h"
#include "vtkProperty.h"

SO_NODE_SOURCE(SoVtkLODActor);

SoVtkLODActor::SoVtkLODActor()
{
	SO_NODE_CONSTRUCTOR(SoVtkActor);
	
	mActor = vtkLODActor::New();
	mActor->Register(0);

	vtkLODActor *aActor = vtkLODActor::New();
	double *x;

	SO_NODE_ADD_FIELD( Mapper, (0) );
	SO_NODE_ADD_FIELD( Property, (0) );
	SO_NODE_ADD_FIELD( BackfaceProperty, (0) );
	SO_NODE_ADD_FIELD( Texture, (0) );

	SO_NODE_ADD_FIELD(Origin, (0, 0, 0));
	x = aActor->GetOrigin();
	Origin.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Orientation, (0, 0, 0));
	x = aActor->GetOrientation();
	Orientation.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Position, (0, 0, 0));
	x = aActor->GetPosition();
	Position.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Scale, (0, 0, 0));
	x = aActor->GetScale();
	Scale.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Pickable, (0));
	Pickable.setValue(aActor->GetPickable());

	SO_NODE_ADD_FIELD(Visibility, (0));
	Visibility.setValue(aActor->GetVisibility());
	
	aActor->Delete();
}

SoVtkLODActor::~SoVtkLODActor()
{
	if( mActor )
	{
		mActor->UnRegister(0);
		mActor->Delete();
		mActor = 0;
	}
}

void SoVtkLODActor::initClass()
{
  SO_NODE_INIT_CLASS(SoVtkLODActor, SoNode, "SoNode");
}

void SoVtkLODActor::getBoundingBox(SoGetBoundingBoxAction *action)
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

void SoVtkLODActor::GLRender(SoGLRenderAction *action)
{
	try
	{
		// Get the input type(s)
		SoVtkObject *mapperPtr = Mapper.getValue();

		if (mapperPtr && mapperPtr->getPointer()->IsA("vtkMapper"))
			mActor->SetMapper(vtkMapper::SafeDownCast(mapperPtr->getPointer()));

		SoVtkObject *propPtr = Property.getValue();

		if (propPtr && propPtr->getPointer()->IsA("vtkProperty"))
			mActor->SetProperty(vtkProperty::SafeDownCast(propPtr->getPointer()));

		SoVtkObject *backpropPtr = BackfaceProperty.getValue();

		if (backpropPtr && backpropPtr->getPointer()->IsA("vtkProperty"))
			mActor->SetBackfaceProperty(vtkProperty::SafeDownCast(backpropPtr->getPointer()));

		SoVtkObject *texturePtr = Texture.getValue();

		if (texturePtr && texturePtr->getPointer()->IsA("vtkTexture"))
			mActor->SetTexture(vtkTexture::SafeDownCast(texturePtr->getPointer()));


		// Handle the other inputs
		SO_VTK_SET_FIELD_VEC3F(mActor,Position);
		SO_VTK_SET_FIELD_VEC3F(mActor,Origin);
		SO_VTK_SET_FIELD_VEC3F(mActor,Orientation);
		SO_VTK_SET_FIELD_VEC3F(mActor,Scale);

		SO_VTK_SET_FIELD_VALUE(mActor,Pickable);
		SO_VTK_SET_FIELD_VALUE(mActor,Visibility);

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
}

vtkLODActor *
SoVtkLODActor::getLODActor() const
{
	return mActor;
}
