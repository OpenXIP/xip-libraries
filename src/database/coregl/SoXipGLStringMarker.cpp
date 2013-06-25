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
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include "SoXipGLStringMarker.h"

SO_NODE_SOURCE(SoXipGLStringMarker);

SoXipGLStringMarker::SoXipGLStringMarker() {
	SO_NODE_CONSTRUCTOR(SoXipGLStringMarker);

	SO_NODE_ADD_FIELD(string, (""));
}

void SoXipGLStringMarker::initClass() {
	SO_NODE_INIT_CLASS(SoXipGLStringMarker, SoNode, "SoNode");

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
}

void SoXipGLStringMarker::GLRender(SoGLRenderAction* action) {
  if (GLOW_GREMEDY_string_marker) {
    if (string.getValue().getLength() > 0) {
#ifndef DARWIN
      glStringMarkerGREMEDY(string.getValue().getLength(), string.getValue().getString());
#endif /* DARWIN */
    }
  }
}



