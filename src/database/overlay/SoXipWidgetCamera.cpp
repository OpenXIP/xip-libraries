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
#include <xip/system/standard.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include "SoXipWidgetCamera.h"
#include <algorithm>

SO_NODE_SOURCE( SoXipWidgetCamera );

SoXipWidgetCamera::SoXipWidgetCamera()
{
	SO_NODE_CONSTRUCTOR( SoXipWidgetCamera );

	SO_XIP_KIT_ADD_TYPE_ENTRY( mCamera, SoOrthographicCamera, this );
	SO_XIP_KIT_ADD_TYPE_ENTRY(  mScale,              SoScale, this );

	mPlaneProj = new SbPlaneProjector( FALSE );
	mPlaneProj->setPlane( SbPlane( SbVec3f(0, 0, 1), 0 ) );
}

SoXipWidgetCamera::~SoXipWidgetCamera()
{
	if( mPlaneProj )
		delete mPlaneProj;
	mPlaneProj = 0;
}

void
SoXipWidgetCamera::initClass()
{
	SO_NODE_INIT_CLASS( SoXipWidgetCamera, SoXipKit, "SoXipKit" );
}

void
SoXipWidgetCamera::updateScale()
{	
	float scale = 150.f / std::min( mViewportSize[0], mViewportSize[1] );
	mScale->scaleFactor.setValue( scale, scale, 1 );
}

void 
SoXipWidgetCamera::saveViewInformation( SoAction* action )
{
	SoState* state = action->getState();

	// Save the view volume element
	mViewVolume = SoViewVolumeElement::get( state );

	// Save the plane projector
	float distance = mViewVolume.getDepth() / 2.f;
	mPlaneProj->setViewVolume( mViewVolume );
	mPlaneProj->setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + distance ) );

	// Save the viewport
	mViewport = SoViewportRegionElement::get( state );
	mViewportSize = mViewport.getViewportSizePixels ();
}

void 
SoXipWidgetCamera::GLRender( SoGLRenderAction* action )
{
	saveViewInformation( action );
	updateScale();

	SoXipKit::GLRender( action );
}

void 
SoXipWidgetCamera::handleEvent( SoHandleEventAction* action )
{
	if( !action->getGrabber() )
	{
		saveViewInformation( action );		
		updateScale();
	}

	SoXipKit::handleEvent( action );
}

