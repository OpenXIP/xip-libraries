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

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <xip/inventor/core/SoXipDataImageElement.h>

#include "SoXipGetImage.h"

SO_NODE_SOURCE( SoXipGetImage );

SoXipGetImage::SoXipGetImage()
{
	SO_NODE_CONSTRUCTOR( SoXipGetImage );

	SO_NODE_ADD_FIELD( image, (0) );
	SO_NODE_ADD_FIELD( sliceIndex, (-1) );
	SO_NODE_ADD_FIELD( numSlices, (-1) );
	SO_NODE_ADD_FIELD( imageIndex, (-1) );
	SO_NODE_ADD_FIELD( numImages, (-1) );
}

SoXipGetImage::~SoXipGetImage()
{
}

void
SoXipGetImage::initClass()
{
	SO_NODE_INIT_CLASS( SoXipGetImage, SoNode, "Node" );
}

void
SoXipGetImage::extractInfo( SoAction* action )
{
	SoXipDataImage* dataImage = SoXipDataImageElement::get( action->getState() );
	if( image.getValue() != dataImage )
		image.setValue( dataImage );

	unsigned short sliceIndex = SoXipDataImageElement::getSliceIndex( action->getState() );
	if( this->sliceIndex.getValue() != sliceIndex )
		this->sliceIndex.setValue( sliceIndex );

	unsigned short numSlices = SoXipDataImageElement::getNumSlices( action->getState() );
	if( this->numSlices.getValue() != numSlices )
		this->numSlices.setValue( numSlices );

	unsigned short imageIndex = SoXipDataImageElement::getImageIndex( action->getState() );
	if( this->imageIndex.getValue() != imageIndex )
		this->imageIndex.setValue( imageIndex );

	unsigned short numImages = SoXipDataImageElement::getNumImages( action->getState() );
	if( this->numImages.getValue() != numImages )
		this->numImages.setValue( numImages );
}

void
SoXipGetImage::GLRender( SoGLRenderAction* action )
{
	extractInfo( action );
}

void
SoXipGetImage::handleEvent( SoHandleEventAction* action )
{
	extractInfo( action );
}

void
SoXipGetImage::pick( SoPickAction* action )
{
	extractInfo( action );
}

void
SoXipGetImage::callback( SoCallbackAction* action )
{
	extractInfo( action );
}
