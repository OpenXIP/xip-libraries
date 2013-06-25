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
/**
*	@file	SoXipMarkerSet.cpp
*	@brief	Implementation of the SoXipMarkerSet class
*	@author	Julien Gein
*	@author	Thomas Moeller
**/

#include <xip/inventor/overlay/SbXipMarkerShapes.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoPointSizeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include "SoXipMarkerSet.h"

SO_NODE_SOURCE( SoXipMarkerSet );

SoXipMarkerSet::SoXipMarkerSet()
{
	SO_NODE_CONSTRUCTOR( SoXipMarkerSet );

	SO_NODE_DEFINE_ENUM_MARKER_VALUES( markerType );
	SO_NODE_SET_SF_ENUM_TYPE( marker, markerType );	
	SO_NODE_ADD_FIELD( marker, (0) );

	mCoord = new SoCoordinate3;
	if( mCoord )
		mCoord->ref();

	mFaceSet = new SoFaceSet;
	if( mFaceSet ) 
		mFaceSet->ref();

	mTranslation = new SoTranslation;
	if( mTranslation )
		mTranslation->ref();

	mScale = new SoScale;
	if( mScale ) 
		mScale->ref();

	mRotation = new SoRotation;
	if( mRotation ) 
		mRotation->ref();
}

SoXipMarkerSet::~SoXipMarkerSet()
{
	if( mCoord )
	{
		mCoord->unref();
		mCoord = 0;
	}
	if( mFaceSet )
	{
		mFaceSet->unref();
		mFaceSet = 0;
	}
	if( mTranslation )
	{
		mTranslation->unref();
		mTranslation = 0;
	}
	if( mScale )
	{
		mScale->unref();
		mScale = 0;
	}
	if( mRotation )
	{
		mRotation->unref();
		mRotation= 0;
	}
}

void 
SoXipMarkerSet::initClass()
{
	SO_NODE_INIT_CLASS( SoXipMarkerSet, SoShape, "Shape" );
}

void 
SoXipMarkerSet::GLRender( SoGLRenderAction* action )
{
	if (mCoord && mFaceSet && mScale && mTranslation && mRotation)
	{
		float pointSize = SoPointSizeElement::get(action->getState());
		SbViewportRegion vp = SoViewportRegionElement::get(action->getState());
		SbViewVolume vVol = SoViewVolumeElement::get(action->getState());

		// world to pixel scale
		float scaleFactorY = pointSize * vVol.getHeight() / (float) vp.getViewportSizePixels()[1];
		float scaleFactorX = pointSize * vVol.getWidth() / (float) vp.getViewportSizePixels()[0];
		mScale->scaleFactor.setValue(0.5f * scaleFactorX, 0.5f * scaleFactorY, 1);

		// world to screen rotation
		SbMatrix affine, proj;
		vVol.getMatrices(affine, proj);
		SbVec3f t, s;
		SbRotation rot, so;
		affine.inverse().getTransform(t, rot, s, so);
		mRotation->rotation.setValue(rot);

		// number of coordinates
		const SoCoordinateElement	*ce = (const SoCoordinateElement *) SoCoordinateElement::getInstance(action->getState());
		int numPts = 0;
		if (ce)
		{
			numPts = ce->getNum();
		}

		SbXipMarkerShapes::getVertices(marker.getValue(), mCoord->point);
		SbXipMarkerShapes::getNumVertices(marker.getValue(), mFaceSet->numVertices);

		for (int i = 0; i < numPts; i++)
		{
			mTranslation->translation.setValue(ce->get3(i));

			action->getState()->push();
			action->traverse(mTranslation);
			action->traverse(mRotation);
			action->traverse(mScale);
			action->traverse(mCoord);
			action->traverse(mFaceSet);
			action->getState()->pop();
		}
	}
}

void 
SoXipMarkerSet::computeBBox( SoAction* action, SbBox3f& box, SbVec3f& center )
{
	const SoCoordinateElement* ce = (const SoCoordinateElement *) SoCoordinateElement::getInstance( action->getState() );

	if( ce )
	{
		for( int i = 0; i < ce->getNum(); ++ i )
			box.extendBy( ce->get3(i) );
	}

	center = box.getCenter();
}

void 
SoXipMarkerSet::generatePrimitives( SoAction* )
{

}
