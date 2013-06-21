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
#include <Inventor/actions/SoGetBoundingBoxAction.h> 
#include <Inventor/misc/SoChildList.h>

#include <xip/inventor/coregl/SoXipGlowElement.h>

#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/fields/SoSFMatrix.h>

#include "SoXipSimpleVolumeRenderKit.h"

SO_KIT_SOURCE(SoXipSimpleVolumeRenderKit);

/**
 *	Constructor
 */
SoXipSimpleVolumeRenderKit::SoXipSimpleVolumeRenderKit()
{
	SO_KIT_CONSTRUCTOR(SoXipSimpleVolumeRenderKit);

    SO_NODE_ADD_FIELD(volumeData,           (NULL));
    SO_NODE_ADD_FIELD(lutData,              (NULL));
    SO_NODE_ADD_FIELD(useComplexity,        (false));
    SO_NODE_ADD_FIELD(samplingFrequency,    (512));
    SO_NODE_ADD_FIELD(selfShading,          (false));
    SO_NODE_ADD_FIELD(gradLighting,         (false));

  //SO_KIT_ADD_CATALOG_ENTRY(partName,      partClassName,      null,  parent, right, public );
	SO_KIT_ADD_CATALOG_ENTRY(top,           SoSeparator,        FALSE, this,   \0,    TRUE);
	SO_KIT_ADD_CATALOG_ENTRY(volumeUnit,    SoXipTextureUnit,   FALSE, top,    \0,    TRUE);
    SO_KIT_ADD_CATALOG_ENTRY(volume,        SoXipTexture,       FALSE, top,    \0,    TRUE);
	SO_KIT_ADD_CATALOG_ENTRY(lutUnit,       SoXipTextureUnit,   FALSE, top,    \0,    TRUE);
    SO_KIT_ADD_CATALOG_ENTRY(lut,           SoXipTexture,       FALSE, top,    \0,    TRUE);
	SO_KIT_ADD_CATALOG_ENTRY(shader,        SoXipSlicerShader,  FALSE, top,    \0,    TRUE);
	SO_KIT_ADD_CATALOG_ENTRY(slicer,        SoXipSlicer,        FALSE, top,    \0,    TRUE);

    SO_KIT_INIT_INSTANCE();

    //setKitConnections();

    mNodeId = 0;
}


SoXipSimpleVolumeRenderKit::~SoXipSimpleVolumeRenderKit()
{
}


void SoXipSimpleVolumeRenderKit::initClass()
{
	SO_KIT_INIT_CLASS(SoXipSimpleVolumeRenderKit, SoBaseKit, "BaseKit");

}

void SoXipSimpleVolumeRenderKit::setKitConnections()
{
    SoNode * vun = getAnyPart("volumeUnit", true);
    SoNode * vol = getAnyPart("volume", true);
    SoNode * lun = getAnyPart("lutUnit", true);
    SoNode * lux = getAnyPart("lut", true);
    SoNode * sha = getAnyPart("shader", true);
    SoNode * sli = getAnyPart("slicer", true);

    if (!vun || !vol || !lun || !lux || !sha || !sli)
    {
        SoDebugError::postWarning(__FUNCTION__, "null pointers");
        return;
    }

    vol->getField("image")->connectFrom( &volumeData );

    lux->getField("image")->connectFrom( &lutData );
    lux->getField("textureDimension")->set("TEXTURE_2D");

    sha->getField("volumeUnit")->connectFrom( vun->getField("textureStage") );
    sha->getField("lutUnit")->connectFrom( lun->getField("textureStage") );
    sha->getField("shading")->connectFrom( &selfShading );
    sha->getField("lighting")->connectFrom( &gradLighting );
    sha->getField("volsize")->connectFrom( vol->getField("textureSize") );

    sli->getField("useComplexity")->connectFrom( &useComplexity );
    sli->getField("numSlices")->connectFrom( &samplingFrequency );
    
    sli->getField("slicing")->set("VIEW_ALIGNED");
    sli->getField("mode")->set("VRT");
    sli->getField("compositing")->set("BACK_TO_FRONT");

    SoDebugError::postInfo(__FUNCTION__, "kit connections set");
}




void SoXipSimpleVolumeRenderKit::GLRender(SoGLRenderAction * action)
{
    if (mNodeId != getNodeId())
        setKitConnections();

	SoBaseKit::GLRender(action); 
    mNodeId = getNodeId();
}





void SoXipSimpleVolumeRenderKit::getBoundingBox (SoGetBoundingBoxAction * action)
{
    SbVec3f unitCube[8] = {SbVec3f(0.0, 0.0, 1.0), SbVec3f(1.0, 0.0, 1.0),
                           SbVec3f(1.0, 1.0, 1.0), SbVec3f(0.0, 1.0, 1.0),
                           SbVec3f(0.0, 0.0, 0.0), SbVec3f(1.0, 0.0, 0.0),
                           SbVec3f(1.0, 1.0, 0.0), SbVec3f(0.0, 1.0, 0.0)};

    SbVec3f tVert;

	SbVec3f vertices[8];
	vertices[0] = SbVec3f( -1.f,  -1.f,  -1.f); 
	vertices[1] = SbVec3f(  1.f,  -1.f,  -1.f); 
	vertices[2] = SbVec3f(  1.f,   1.f,  -1.f); 
	vertices[3] = SbVec3f( -1.f,   1.f,  -1.f); 
	vertices[4] = SbVec3f(  1.f,   1.f,   1.f); 
	vertices[5] = SbVec3f( -1.f,   1.f,   1.f); 
	vertices[6] = SbVec3f( -1.f,  -1.f,   1.f); 
	vertices[7] = SbVec3f(  1.f,  -1.f,   1.f);


    //SbMatrix matrix = volumeTransform.getValue();
    //SbMatrix modelMat = SoModelMatrixElement::get(action->getState()).inverse();
    SbMatrix modelMat = SbMatrix::identity();
    SbBox3f bb;
    bb.makeEmpty();
    for (int i = 0; i < 8; i++)
    {
        modelMat.multVecMatrix(unitCube[i], tVert);
        //matrix.multMatrixVec(unitCube[i], tVert);
        bb.extendBy(tVert);
    }
    action->extendBy(bb);
}

