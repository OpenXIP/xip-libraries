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
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include "SoXipMenuItemSeparator.h"

static const SbVec3f s_faceCoords[4] = {
	SbVec3f( 0,   0, 0 ),
	SbVec3f( 2,   0, 0 ),
	SbVec3f( 2, 0.1, 0 ),
	SbVec3f( 0, 0.1, 0 )
};

static const unsigned int s_vertexColors[4] = {
	0xccccccff, 
	0xccccccff, 
	0xccccccff, 
	0xccccccff 
};

static const int s_faceIndices[8] = { 0, 1, 2, -1, 0, 2, 3, -1 };

static const SbVec3f s_lineCoords[2] = {
	SbVec3f( 0.1, 0.05, 0 ),
	SbVec3f( 1.9, 0.05, 0 )
};

SO_NODE_SOURCE( SoXipMenuItemSeparator );

SoXipMenuItemSeparator::SoXipMenuItemSeparator()
{
	SO_NODE_CONSTRUCTOR( SoXipMenuItemSeparator );

	SO_XIP_KIT_ADD_ENTRY( mFaceSeparator,      SoSeparator, mSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mVertices, SoVertexProperty, mFaceSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY(    mFaces, SoIndexedFaceSet, mFaceSeparator );

	SO_XIP_KIT_ADD_ENTRY(   mLineSeparator,   SoSeparator, mSeparator );
	SO_XIP_KIT_ADD_ENTRY(    mLineMaterial,    SoMaterial, mLineSeparator );
	SO_XIP_KIT_ADD_ENTRY(       mLineStyle,   SoDrawStyle, mLineSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mLineCoords, SoCoordinate3, mLineSeparator );
	SO_XIP_KIT_ADD_ENTRY(         mLineSet,     SoLineSet, mLineSeparator );

	mVertices->materialBinding.setValue( SoVertexProperty::PER_VERTEX_INDEXED );
	mVertices->vertex.setNum(4);
	mVertices->vertex.setValues( 0, 4, s_faceCoords );
	mVertices->orderedRGBA.setValues( 0, 4, s_vertexColors );
	
	mFaces->coordIndex.setValues( 0, 8, s_faceIndices );
	mLineCoords->point.setValues( 0, 2, s_lineCoords );

	mLineMaterial->set( "diffuseColor 0.5 0.5 0.5" );
	mLineStyle->set( "lineWidth 1" );
}

SoXipMenuItemSeparator::~SoXipMenuItemSeparator()
{

}

void 
SoXipMenuItemSeparator::initClass()
{
	SO_NODE_INIT_CLASS( SoXipMenuItemSeparator, SoXipMenuItemBase, "SoXipMenuItemBase" );
}

float
SoXipMenuItemSeparator::getWidth() const
{
	return 2;
}

float
SoXipMenuItemSeparator::getHeight() const
{
	return 0.1;
}
