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
#include "SoXipGetCameraProperties.h"
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>

SO_NODE_SOURCE(SoXipGetCameraProperties);

SoXipGetCameraProperties::SoXipGetCameraProperties() {
	SO_NODE_CONSTRUCTOR(SoXipGetCameraProperties);

    SO_NODE_ADD_FIELD(camPos, (SbVec3f(0.0,0.0,0.0)));
	SO_NODE_ADD_FIELD(camDir, (SbVec3f(0.0,0.0,0.0)));
	SO_NODE_ADD_FIELD(viewport, (SbVec4f(0.0,0.0,0.0,0.0)));
}

void SoXipGetCameraProperties::initClass() {
	SO_NODE_INIT_CLASS(SoXipGetCameraProperties, SoNode, "SoNode");

    SO_ENABLE(SoGLRenderAction, SoViewingMatrixElement);
	SO_ENABLE(SoGLRenderAction, SoModelMatrixElement);
	SO_ENABLE(SoGLRenderAction, SoViewVolumeElement);
	SO_ENABLE(SoGLRenderAction, SoViewportRegionElement);
}

void SoXipGetCameraProperties::GLRender(SoGLRenderAction* action)
{
    /*
	SbMatrix mMV = SoModelMatrixElement::get(action->getState()) * SoViewingMatrixElement::get(action->getState());
    SbMatrix mv = mMV.transpose();
    mv = mv.inverse();
    SbVec3f cc(0.0,0.0,0.0);
    SbVec3f wc;
    mv.multMatrixVec(cc, wc);
    */
    SbViewVolume vv = SoViewVolumeElement::get( action->getState() );

    mCamPos = vv.getSightPoint(0.0);
    if (mCamPos != camPos.getValue())
        camPos.setValue( mCamPos );

    mCamDir = vv.getSightPoint(1.0) - vv.getSightPoint(0.0);
    if (mCamDir != camDir.getValue() )
        camDir.setValue( mCamDir );

    SbViewportRegion vpr = SoViewportRegionElement::get( action->getState() );
    SbVec2s orig = vpr.getViewportOriginPixels();
    SbVec2s wh = vpr.getViewportSizePixels();
    SbVec4f vp = SbVec4f( (float)orig[0], (float)orig[1], (float)wh[0], (float)wh[1] );

    mViewport = vp;
    if (mViewport != viewport.getValue())
        viewport.setValue( mViewport );
}

