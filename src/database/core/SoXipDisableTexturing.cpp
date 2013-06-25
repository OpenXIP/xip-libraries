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

#include <xip/inventor/coregl/SoXipGlowElement.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>

#include "SoXipDisableTexturing.h"


SO_NODE_SOURCE( SoXipDisableTexturing );


// TFEditor implementation
void SoXipDisableTexturing::initClass()
{
    SO_NODE_INIT_CLASS(SoXipDisableTexturing, SoNode, "Node");
    SO_ENABLE(SoGLRenderAction,	SoGLTextureEnabledElement);
    SO_ENABLE(SoGLRenderAction,	SoXipMultiTextureElement);
}

SoXipDisableTexturing::SoXipDisableTexturing()
{
    SO_NODE_CONSTRUCTOR(SoXipDisableTexturing);

    SO_NODE_ADD_FIELD(disable1D, (TRUE));
    SO_NODE_ADD_FIELD(disable2D, (TRUE));
    SO_NODE_ADD_FIELD(disable3D, (TRUE));
    SO_NODE_ADD_FIELD(disableCubeMap, (TRUE));

    mTexUnits = 0;
    mNodeId = 0;
}

SoXipDisableTexturing::~SoXipDisableTexturing()
{
}


void SoXipDisableTexturing::GLRender(SoGLRenderAction *action)
{
    if (mNodeId == 0)
    {
        glGetIntegerv(GL_MAX_TEXTURE_UNITS, &mTexUnits);
        mTexUnits = (mTexUnits < 0) ? 0 : mTexUnits;
    }

    for (int i = 0; i < mTexUnits; i++)
    {
        /*
          NOTE: We must review what to do with SoXipMultiTextureElement
          to properly reflect the changed state. The element does
          not show any interface to disable textures and specific units,
          it is not about bind/unbind of textures!
          However, this code will only disable normal OpenGL texturing,
          it will not disable use of textures in shaders!
          
          Patric Ljung, 2009-04-09
        */
        SoXipMultiTextureElement::setUnit(action->getState(), i);

        if (disable1D.getValue() && glIsEnabled(GL_TEXTURE_1D))
            glDisable(GL_TEXTURE_1D);

        if (disable2D.getValue() && glIsEnabled(GL_TEXTURE_2D))
            glDisable(GL_TEXTURE_2D);

        if (disable3D.getValue() && glIsEnabled(GL_TEXTURE_3D))
            glDisable(GL_TEXTURE_3D);

        if (disableCubeMap.getValue() && glIsEnabled(GL_TEXTURE_CUBE_MAP))
            glDisable(GL_TEXTURE_CUBE_MAP);
    }

    SoGLTextureEnabledElement::set(action->getState(), FALSE);
}


