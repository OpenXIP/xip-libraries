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
 * \file SoVtkVolume.cpp
 *
 * \brief SoVtkVolume class implementation.
 *
 */

#include "SoVtkVolume.h"
#include "SoVtkUtils.h"

#include "vtkAbstractVolumeMapper.h"
#include "vtkVolumeProperty.h"


SO_NODE_SOURCE(SoVtkVolume);

SoVtkVolume::SoVtkVolume()
{
	SO_NODE_CONSTRUCTOR(SoVtkVolume);

	mVolume = vtkVolume::New();
    mVolume->Register(0);
	
	vtkVolume *aVolume = vtkVolume::New();
	double *x;
	
	SO_NODE_ADD_FIELD( Mapper  , (0) );
	SO_NODE_ADD_FIELD( Property, (0) );

	SO_NODE_ADD_FIELD(Origin, (0,0,0));
	x = aVolume->GetOrigin();
	Origin.setValue(x[0],x[1],x[2]);

	SO_NODE_ADD_FIELD(Position, (0,0,0));
	x = aVolume->GetPosition();
	Position.setValue(x[0],x[1],x[2]);

	aVolume->Delete();
}

SoVtkVolume::~SoVtkVolume()
{
	if( mVolume )
	{
		mVolume->UnRegister(0);
		mVolume->Delete();
		mVolume = 0;
	}
}

void SoVtkVolume::initClass()
{
	SO_NODE_INIT_CLASS(SoVtkVolume, SoNode, "SoNode");
}

void SoVtkVolume::GLRender(SoGLRenderAction *action)
{
	try
	{	
		// Get the input type(s)
		SoVtkObject *mapperPtr = Mapper.getValue();

		if (mapperPtr && mapperPtr->getPointer()->IsA("vtkAbstractVolumeMapper"))
			mVolume->SetMapper(vtkAbstractVolumeMapper::SafeDownCast(mapperPtr->getPointer()));

		if ( !mapperPtr )
			mVolume->SetMapper(0);

		SoVtkObject *propPtr = Property.getValue();

		if (propPtr && propPtr->getPointer()->IsA("vtkVolumeProperty"))
			mVolume->SetProperty(vtkVolumeProperty::SafeDownCast(propPtr->getPointer()));

		if ( !propPtr )
			mVolume->SetProperty(0);


		// Handle the other inputs
		SO_VTK_SET_FIELD_VEC3F(mVolume,Position);
		SO_VTK_SET_FIELD_VEC3F(mVolume,Origin);

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
}


vtkVolume *
SoVtkVolume::getVolume() const
{
	return mVolume;
}

void SoVtkVolume::getBoundingBox(SoGetBoundingBoxAction *action)
{
	SbBox3f	bbox;
	SbVec3f	center;

	if (mVolume)
	{
		const double *bounds = mVolume->GetBounds();
		SbBox3f bbox(bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5]);
		action->extendBy(bbox);
		action->setCenter(bbox.getCenter(), TRUE);
	}
}
