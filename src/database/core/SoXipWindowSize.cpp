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

#include "SoXipWindowSize.h"
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>


SO_NODE_SOURCE(SoXipWindowSize);

SoXipWindowSize::SoXipWindowSize() 
{
	SO_NODE_CONSTRUCTOR(SoXipWindowSize);

	SO_NODE_ADD_FIELD(width, (0));
	SO_NODE_ADD_FIELD(height, (0));
	SO_NODE_ADD_FIELD(pixelScale, (SbVec2f(0, 0)));
}

void SoXipWindowSize::initClass() 
{
	SO_NODE_INIT_CLASS(SoXipWindowSize, SoNode, "SoNode");
}

void SoXipWindowSize::GLRender(SoGLRenderAction* action) 
{
	SbViewportRegion vp = SoViewportRegionElement::get(action->getState());
	SbViewVolume vv = SoViewVolumeElement::get(action->getState());

	enableNotify(FALSE);

	width.setValue(vp.getViewportSizePixels()[0]);
	height.setValue(vp.getViewportSizePixels()[1]);

	pixelScale.setValue(SbVec2f(
		vp.getViewportSizePixels()[0] > 0 ? vv.getWidth()  / (float) vp.getViewportSizePixels()[0] : 1,
		vp.getViewportSizePixels()[1] > 1 ? vv.getHeight() / (float) vp.getViewportSizePixels()[1] : 1));

	enableNotify(TRUE);
}

