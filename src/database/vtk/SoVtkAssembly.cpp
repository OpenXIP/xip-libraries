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
#include "SoVtkAssembly.h"

#include <Inventor/elements/SoLocalBBoxMatrixElement.h>

#include "SoVtkActor.h"
#include "SoVtkVolume.h"
#include "SoVtkActor2D.h"
#include "SoVtkImageActor.h"
#include "SoVtkLODActor.h"

#include "vtkProp3DCollection.h"

SO_NODE_SOURCE(SoVtkAssembly);

SoVtkAssembly::SoVtkAssembly()
{
	SO_NODE_CONSTRUCTOR(SoVtkAssembly);

	mAssembly = vtkAssembly::New();
	mAssembly->Register(0);

	SbVec3f vec3fInitValue(0, 0, 0);
	SO_NODE_ADD_FIELD(Origin, (vec3fInitValue));
	SO_NODE_ADD_FIELD(Position, (vec3fInitValue));

	nodeId = 0;

}

SoVtkAssembly::~SoVtkAssembly()
{
	if( mAssembly )
	{
		mAssembly->UnRegister(0);
		mAssembly->Delete();
		mAssembly = 0;
	}
}

void SoVtkAssembly::initClass()
{
  SO_NODE_INIT_CLASS(SoVtkAssembly, SoGroup, "Group");
}


void SoVtkAssembly::getBoundingBox(SoGetBoundingBoxAction *action)
{
	SbBox3f	bbox;
	SbVec3f	center;

	if (mAssembly)
	{
		const double *bounds = mAssembly->GetBounds();
		SbBox3f bbox(bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5]);
		action->extendBy(bbox);
		action->setCenter(bbox.getCenter(), FALSE);
	}
}


void SoVtkAssembly::GLRender(SoGLRenderAction *action)
{
	try
	{
		SoGroup::GLRender(action);

		if ( nodeId != getNodeId() )
		{
			nodeId = getNodeId();
			updateChildren();
		}



		// Perform setPosition and setOrigin transformations
		SbVec3f position = Position.getValue();
		SbVec3f origin = Origin.getValue();
		mAssembly->SetOrigin(origin[0], origin[1], origin[2]);
		mAssembly->SetPosition(position[0], position[1], position[2]);

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
}

void SoVtkAssembly::updateChildren()
{
	for (int i = 0; i < SoGroup::getNumChildren(); i++)
	{
		SoNode *child = SoGroup::getChild(i);
	
		if (child->isOfType(SoVtkAssembly::getClassTypeId()))
		{
			// assembly
			SoVtkAssembly *assembly = (SoVtkAssembly *) child;
			assembly->updateChildren();
		}
	}

	vtkProp3DCollection *parts = mAssembly->GetParts();

	for (int i = 0; i < parts->GetNumberOfItems(); i++)
	{
		mAssembly->RemovePart(vtkProp3D::SafeDownCast(parts->GetItemAsObject(i)));
	}

	for (int i = 0; i < SoGroup::getNumChildren(); i++)
	{
		SoNode *child = SoGroup::getChild(i);

		if (child->isOfType(SoVtkActor::getClassTypeId()))
		{
			// actor
			SoVtkActor *actor = (SoVtkActor *) child;
			mAssembly->AddPart(actor->getActor());
		}

		if (child->isOfType(SoVtkLODActor::getClassTypeId()))
		{
			// actor
			SoVtkLODActor *actor = (SoVtkLODActor *) child;
			mAssembly->AddPart(actor->getLODActor());
		}

		if (child->isOfType(SoVtkActor2D::getClassTypeId()))
		{
			// actor 2D
			SoVtkActor2D *actor = (SoVtkActor2D *) child;
			mAssembly->AddPart(vtkProp3D::SafeDownCast(actor->getActor2D()));
		}

		if (child->isOfType(SoVtkImageActor::getClassTypeId()))
		{
			// image actor
			SoVtkImageActor *actor = (SoVtkImageActor *) child;
			mAssembly->AddPart(actor->getImageActor());
		}

		if (child->isOfType(SoVtkVolume::getClassTypeId()))
		{
			// volume
			SoVtkVolume *vol = (SoVtkVolume *) child;
			mAssembly->AddPart(vol->getVolume());
		}
		
		if (child->isOfType(SoVtkAssembly::getClassTypeId()))
		{
			// assembly
			SoVtkAssembly *assembly = (SoVtkAssembly *) child;
			mAssembly->AddPart(vtkAssembly::SafeDownCast(assembly->getAssembly()));
		}
	}
}

vtkAssembly *
SoVtkAssembly::getAssembly() const
{
	return mAssembly;
}
