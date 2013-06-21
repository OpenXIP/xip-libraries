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
/*
 * \file SoVtkActor.cpp
 *
 * \brief XIP wrapping of SoVtkActor
 *
 * \author Sylvain Jaume (Siemens Corporate Research), Francois Huguet
 */

#include "SoVtkActor.h"
#include "SoVtkUtils.h"

#include "vtkMapper.h"
#include "vtkTexture.h"
#include "vtkProperty.h"

#include <Inventor/elements/SoLocalBBoxMatrixElement.h>

SO_NODE_SOURCE(SoVtkActor);

SoVtkActor::SoVtkActor()
{
	SO_NODE_CONSTRUCTOR(SoVtkActor);
	
	mActor = vtkActor::New();
	mActor->Register(0);

	vtkActor *aActor = vtkActor::New();
	double x[3];

	SO_NODE_ADD_FIELD( Mapper, (0) );
	SO_NODE_ADD_FIELD( Property, (0) );
	SO_NODE_ADD_FIELD( BackfaceProperty, (0) );
	SO_NODE_ADD_FIELD( Texture, (0) );

	SO_NODE_ADD_FIELD(Origin, (0, 0, 0));
	aActor->GetOrigin(x);
	Origin.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Orientation, (0, 0, 0));
	aActor->GetOrientation(x);
	Orientation.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Position, (0, 0, 0));
	aActor->GetPosition(x);
	Position.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Scale, (0, 0, 0));
	aActor->GetScale(x);
	Scale.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Pickable, (0));
	Pickable.setValue(aActor->GetPickable());

	SO_NODE_ADD_FIELD(Visibility, (0));
	Visibility.setValue(aActor->GetVisibility());
	
	aActor->Delete();
}

SoVtkActor::~SoVtkActor()
{
	if( mActor )
	{
		mActor->UnRegister(0);
		mActor->Delete();
		mActor = 0;
	}
}

void SoVtkActor::initClass()
{
	SO_NODE_INIT_CLASS(SoVtkActor, SoNode, "SoNode");
}

void SoVtkActor::getBoundingBox(SoGetBoundingBoxAction *action)
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

void SoVtkActor::GLRender(SoGLRenderAction *action)
{
	try
	{
		// Get the input type(s)
		SoVtkObject *mapperPtr = Mapper.getValue();

		if (mapperPtr && mapperPtr->getPointer()->IsA("vtkMapper"))
			mActor->SetMapper(vtkMapper::SafeDownCast(mapperPtr->getPointer()));
		if ( !mapperPtr )
			mActor->SetMapper(0);

		SoVtkObject *propPtr = Property.getValue();

		if (propPtr && propPtr->getPointer()->IsA("vtkProperty"))
			mActor->SetProperty(vtkProperty::SafeDownCast(propPtr->getPointer()));
		if ( !propPtr )
			mActor->SetProperty(0);

		SoVtkObject *backpropPtr = BackfaceProperty.getValue();

		if (backpropPtr && backpropPtr->getPointer()->IsA("vtkProperty"))
			mActor->SetBackfaceProperty(vtkProperty::SafeDownCast(backpropPtr->getPointer()));
		if ( !backpropPtr )
			mActor->SetBackfaceProperty(0);

		SoVtkObject *texturePtr = Texture.getValue();

		if (texturePtr && texturePtr->getPointer()->IsA("vtkTexture"))
			mActor->SetTexture(vtkTexture::SafeDownCast(texturePtr->getPointer()));
		if ( !texturePtr )
			mActor->SetTexture(0);

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


vtkActor *
SoVtkActor::getActor() const
{
	return mActor;
}



