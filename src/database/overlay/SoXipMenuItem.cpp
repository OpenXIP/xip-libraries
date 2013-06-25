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
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoMaterial.h>
#include "SoXipMenuStyleElement.h"
#include "SoXipMenuItem.h"
#include "SoXipIcon.h"

static const SbVec3f s_vertexCoords[9] = {
	SbVec3f( 0,     0, 0 ),
	SbVec3f( 1,     0, 0 ),
	SbVec3f( 2,     0, 0 ),
	SbVec3f( 0, 0.125, 0 ),
	SbVec3f( 1, 0.125, 0 ),
	SbVec3f( 2, 0.125, 0 ),
	SbVec3f( 0,  0.25, 0 ),
	SbVec3f( 1,  0.25, 0 ),
	SbVec3f( 2,  0.25, 0 )
};

static const int s_faceIndices[32] = { 
	0, 4, 3, -1, 
	1, 4, 0, -1, 
	1, 5, 4, -1, 
	2, 5, 1, -1,
	3, 7, 6, -1,
	4, 7, 3, -1,
	4, 8, 7, -1,
	5, 8, 4, -1
};

static const SbVec2f s_iconTextCoords[4] = {
	SbVec2f(0,0), 
	SbVec2f(1,0), 
	SbVec2f(1,1), 
	SbVec2f(0,1)
};

static const SbVec3f s_iconCoords[4] =
{ 
	SbVec3f(  0,   0, 0), 
	SbVec3f(0.2,   0, 0), 
	SbVec3f(0.2, 0.2, 0), 
	SbVec3f(  0, 0.2, 0)
};

static const unsigned int s_defaultColors[9]  = { 
	0xccccccff, 0xccccccff, 0xccccccff,
	0xccccccff, 0xccccccff, 0xccccccff,
	0xccccccff, 0xccccccff, 0xccccccff
};

static const unsigned int s_focusColors[9]  = { 
	0xffffaaff, 0xffffaaff, 0xffffaaff,
	0xffffaaff, 0xffffaaff, 0xffffaaff,
	0xffffaaff, 0xffffaaff, 0xffffaaff
};

SO_NODE_SOURCE( SoXipMenuItem );

SoXipMenuItem::SoXipMenuItem()
{
	SO_NODE_CONSTRUCTOR( SoXipMenuItem );	

	SO_XIP_KIT_ADD_TYPE_ENTRY( mVertices, SoVertexProperty, mSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mFaces, SoIndexedFaceSet, mSeparator );

	SO_XIP_KIT_ADD_ENTRY( mIconOffset, SoTranslation, mSeparator );
	SO_XIP_KIT_ADD_ENTRY( mIconSwitch, SoSwitch, mSeparator );
	SO_XIP_KIT_ADD_ENTRY( mIconSeparator, SoSeparator, mIconSwitch );
	SO_XIP_KIT_ADD_ENTRY( mIconComplexity, SoComplexity, mIconSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mIconTexture, SoXipIcon, mIconSeparator );
	SO_XIP_KIT_ADD_ENTRY( mIconTextCoords, SoTextureCoordinate2, mIconSeparator );
	SO_XIP_KIT_ADD_ENTRY( mIconCoords, SoVertexProperty, mIconSeparator );
	SO_XIP_KIT_ADD_ENTRY( mIconFaces, SoFaceSet, mIconSeparator );

	SO_XIP_KIT_ADD_ENTRY( mTextSeparator, SoSeparator, mSeparator );
	SO_XIP_KIT_ADD_ENTRY( mTextOffset, SoTranslation, mTextSeparator );
	SO_XIP_KIT_ADD_ENTRY( mTextMaterial, SoMaterial, mTextSeparator );
	SO_XIP_KIT_ADD_ENTRY( mText, SoXipText2, mTextSeparator );
	
	// Set the vertices for the item background
	mVertices->materialBinding.setValue( SoVertexProperty::PER_VERTEX_INDEXED );
	mVertices->orderedRGBA.setValues( 0, 9, s_defaultColors );
	mVertices->vertex.setValues( 0, 9, s_vertexCoords );

	// Set the face indices of the item background
	mFaces->coordIndex.setValues( 0, 32, s_faceIndices );	

	// Set the complexity of the icon texture to high
	mIconComplexity->set( "textureQuality 1" );

	((SoTextureCoordinate2 *) mIconTextCoords)->point.setValues( 0, 4, s_iconTextCoords );
	((SoVertexProperty*) mIconCoords)->vertex.setValues( 0, 4, s_iconCoords );
}

SoXipMenuItem::~SoXipMenuItem()
{

}

void 
SoXipMenuItem::initClass()
{
	SO_NODE_INIT_CLASS( SoXipMenuItem, SoXipMenuItemBase, "SoXipMenuItemBase" );
}

void 
SoXipMenuItem::onEnable()
{
	onFocus();
}

void 
SoXipMenuItem::onFocus()
{
	mVertices->orderedRGBA.setValues( 0, 9, 
		( isFocused() && isEnabled() ) ? s_focusColors : s_defaultColors );
}

float
SoXipMenuItem::getWidth() const
{
	return 2;
}

float
SoXipMenuItem::getHeight() const
{
	return 0.25;
}

void 
SoXipMenuItem::updateCaption()
{
	((SoSFString *) mText->getField( "string" ))->setValue( caption.getValue() );
}

void 
SoXipMenuItem::updateIcon()
{
	if( icon.getValue() != IC_NONE )
	{
		if( ((SoSwitch *) mIconSwitch)->whichChild.getValue() != 0 )
			((SoSwitch *) mIconSwitch)->whichChild.setValue(0);
		
		mIconTexture->icon.setValue( icon.getValue() );
		mIconTexture->isTransparent.setValue( TRUE );
		mIconTexture->transparentColor.setValue( 1, 0, 1 );
	}
}

void
SoXipMenuItem::GLRender( SoGLRenderAction* action )
{
	if( action->getState() )
	{
		SbXipMenuStyle style = SoXipMenuStyleElement::get( action->getState() );

		SbColor tColor = isEnabled() ? style.textColor : style.disabledTextColor;
		((SoMaterial *) mTextMaterial)->diffuseColor.setValue( tColor );

		// FIXME
		((SoTranslation *) mIconOffset)->translation.setValue( 0.05, 0.02, 0 );

		// FIXME
		SbVec3f textOffset( 0.2 /* icon width */ + 0.08, 0.15, 0 );
		((SoTranslation *) mTextOffset)->translation.setValue( textOffset );

		glPushAttrib( GL_COLOR_BUFFER_BIT );

		glEnable( GL_ALPHA_TEST );
		glAlphaFunc( GL_GREATER, 0 );

		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		SoXipKit::GLRender( action );

		glPopAttrib();
	}
}
