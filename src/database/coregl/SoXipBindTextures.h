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

#ifndef SO_XIP_BIND_TEXTURES_H
#define SO_XIP_BIND_TEXTURES_H


/**
 *  Component       : XIP
 *  Name            : SoXipFbo
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Takes a multi field int filled with texture
 *                      ID's. Textures get bound on avaliable units
 *                      and the units becomes a mf output.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>


class SoXipBindTextures : public SoNode
{
    SO_NODE_HEADER(SoXipBindTextures);

	/**	
	 *	Enum for internal texture dimension
	 */
	enum TextureDimension {
		TEXTURE_1D = GL_TEXTURE_1D,
		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_3D = GL_TEXTURE_3D
	};

public:

    SoXipBindTextures();
    ~SoXipBindTextures();

    static void initClass();

    void assignTextures(SoGLRenderAction* action);
    void bindTextures(SoGLRenderAction* action);
    void syncOutput();

    // field variables
	SoSFEnum    textureDimension;
    SoMFInt32   attachmentHandles;
    SoSFInt32   texture0Output;
    SoSFInt32   texture1Output;
    SoSFInt32   texture2Output;
    SoSFInt32   texture3Output;
    SoSFInt32   texture4Output;
    SoSFInt32   texture5Output;
    SoSFInt32   texture6Output;
    SoSFInt32   texture7Output;

protected:
    virtual void    GLRender(SoGLRenderAction* action);

private:

    static const    GLenum avaliableColorTargets[16];

    int             mNumTextures;
    int             mTexHandles[16];
    int             mTexUnits[16];

    bool            mNeedsSync;
    unsigned int    mNodeId;
};

#endif // SO_XIP_CLEAR_BUFFERS_H
