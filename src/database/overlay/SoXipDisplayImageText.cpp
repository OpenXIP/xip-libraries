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
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFColor.h>
#include <xip/system/GL/gl.h>
#include <xip/inventor/core/SoXipImageTextElement.h>
#include <xip/inventor/overlay/SoXipImageTextColorElement.h>
#include "SoXipDisplayImageText.h"

SO_KIT_SOURCE( SoXipDisplayImageText );

SoXipDisplayImageText::SoXipDisplayImageText()
{
	SO_KIT_CONSTRUCTOR( SoXipDisplayImageText );

	SO_KIT_ADD_CATALOG_ENTRY( separator, SoSeparator, FALSE, this, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( orthoCamera, SoOrthographicCamera, FALSE, separator, \0 , FALSE );
	
	// upper left
	SO_KIT_ADD_CATALOG_ENTRY( separatorUL, SoSeparator, FALSE, separator, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( materialUL, SoMaterial, FALSE, separatorUL, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( translationUL, SoTranslation, FALSE, separatorUL, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( textUL, SoXipText2, FALSE, separatorUL, \0 , FALSE );

	// upper center
	SO_KIT_ADD_CATALOG_ENTRY( separatorUC, SoSeparator, FALSE, separator, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( materialUC, SoMaterial, FALSE, separatorUC, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( translationUC, SoTranslation, FALSE, separatorUC, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( textUC, SoXipText2, FALSE, separatorUC, \0 , FALSE );

	// upper right
	SO_KIT_ADD_CATALOG_ENTRY( separatorUR, SoSeparator, FALSE, separator, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( materialUR, SoMaterial, FALSE, separatorUR, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( translationUR, SoTranslation, FALSE, separatorUR, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( textUR, SoXipText2, FALSE, separatorUR, \0 , FALSE );

	// center left
	SO_KIT_ADD_CATALOG_ENTRY( separatorCL, SoSeparator, FALSE, separator, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( materialCL, SoMaterial, FALSE, separatorCL, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( translationCL, SoTranslation, FALSE, separatorCL, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( textCL, SoXipText2, FALSE, separatorCL, \0 , FALSE );
	
	// center right
	SO_KIT_ADD_CATALOG_ENTRY( separatorCR, SoSeparator, FALSE, separator, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( materialCR, SoMaterial, FALSE, separatorCR, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( translationCR, SoTranslation, FALSE, separatorCR, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( textCR, SoXipText2, FALSE, separatorCR, \0 , FALSE );

	// lower left
	SO_KIT_ADD_CATALOG_ENTRY( separatorLL, SoSeparator, FALSE, separator, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( materialLL, SoMaterial, FALSE, separatorLL, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( translationLL, SoTranslation, FALSE, separatorLL, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( textLL, SoXipText2, FALSE, separatorLL, \0 , FALSE );

	// lower center
	SO_KIT_ADD_CATALOG_ENTRY( separatorLC, SoSeparator, FALSE, separator, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( materialLC, SoMaterial, FALSE, separatorLC, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( translationLC, SoTranslation, FALSE, separatorLC, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( textLC, SoXipText2, FALSE, separatorLC, \0 , FALSE );

	// lower right
	SO_KIT_ADD_CATALOG_ENTRY( separatorLR, SoSeparator, FALSE, separator, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( materialLR, SoMaterial, FALSE, separatorLR, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( translationLR, SoTranslation, FALSE, separatorLR, \0 , FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( textLR, SoXipText2, FALSE, separatorLR, \0 , FALSE );

	SO_KIT_INIT_INSTANCE();

	SO_NODE_ADD_FIELD( on, (TRUE) );
	SO_NODE_ADD_FIELD( dogEar, (FALSE) );
}

SoXipDisplayImageText::~SoXipDisplayImageText()
{

}

void 
SoXipDisplayImageText::initClass()
{
	SO_KIT_INIT_CLASS( SoXipDisplayImageText, SoBaseKit, "BaseKit" );
}

void
SoXipDisplayImageText::GLRender( SoGLRenderAction* action )
{
	// don't do anything if turned off
	if( !on.isIgnored() && !on.getValue() )
		return ;

	SbBool notifyEnabled = isNotifyEnabled();
	enableNotify(FALSE);

	// Retrieve image text from element
	const int numPositions = 1 + SoXipImageTextElement::TP_LOWER_RIGHT - SoXipImageTextElement::TP_UPPER_LEFT;
	SbString displayText[numPositions];

	SoXipImageTextElement* elt = SoXipImageTextElement::getInstance( action->getState() );
	SoXipImageTextColorElement* colorElt = SoXipImageTextColorElement::getInstance( action->getState() );

	if( elt )
	{
		for( int i = 0; i < elt->getNum(); ++ i )
		{
			int position = elt->getPosition(i);
			displayText[position - SoXipImageTextElement::TP_UPPER_LEFT] += elt->getText(i);
			displayText[position - SoXipImageTextElement::TP_UPPER_LEFT] += "\n";
		}
	}

	for( int pos = SoXipImageTextElement::TP_UPPER_LEFT; pos <= SoXipImageTextElement::TP_LOWER_RIGHT; ++ pos )
	{
		SoNode* textNode = getTextNode( pos );
		if( !textNode )
			continue ;

		SoSFString* stringField = (SoSFString *) textNode->getField( "string" );
		if( stringField )
			stringField->setValue( displayText[pos - SoXipImageTextElement::TP_UPPER_LEFT] );

		SoNode* materialNode = getMaterialNode( pos );
		if( !materialNode )
			continue ;

		SoMFColor* colorField = (SoMFColor *) materialNode->getField( "diffuseColor" );
		if( colorField && colorElt )
			colorField->setValue( colorElt->get( (SoXipImageTextElement::TextElementPosition) pos ) );
	}

	const SbViewportRegion& vpRegion = SoViewportRegionElement::get( action->getState() );
	float aspectRatio = vpRegion.getViewportAspectRatio();

	const SbVec2s& pixels = vpRegion.getViewportSizePixels();
	int minDim = pixels[0] > pixels[1] ? pixels[1] : pixels[0];

	// do not display dicom text if segment size is less than 200
	if( minDim >= 200 )
	{
	float fontSize = SoFontSizeElement::get( action->getState() );

	const float border = 5;

	float xOffset;
	float yOffset;

	// UPPER LEFT
		xOffset = -1.f;
		yOffset =  1.f;	

		yOffset -= border * ( 2.f / (float) pixels[1] );
		xOffset += border * ( 2.f / (float) pixels[0] );

		if( aspectRatio < 1.f )
		{
			yOffset /= aspectRatio;
		}
		else if( aspectRatio > 1.f )
		{
			xOffset *= aspectRatio;
		}

		SoTranslation* transUL = (SoTranslation *) getAnyPart( "translationUL", TRUE );
		transUL->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

		SoNode* textUL = getTextNode( SoXipImageTextElement::TP_UPPER_LEFT );
		if( textUL )
		{		
			textUL->set( "justification LEFT" );
			textUL->set( "vAlignment TOP" );
		}
		
	// UPPER CENTER
		xOffset = 0.f;
		yOffset = 1.f;

		yOffset -= border * ( 2.f / (float) pixels[1] );

		if( aspectRatio < 1.f )
		{
			yOffset /= aspectRatio;
		}
		else if( aspectRatio > 1.f )
		{
			xOffset *= aspectRatio;
		}

		SoTranslation* transUC = (SoTranslation *) getAnyPart( "translationUC", TRUE );
		transUC->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

		SoNode* textUC = getTextNode( SoXipImageTextElement::TP_UPPER_CENTER );
		if( textUC )
		{		
			textUC->set( "justification LEFT" );
			textUC->set( "vAlignment TOP" );
		}

	// UPPER RIGHT
		xOffset = 1.f;
		yOffset = 1.f;

		yOffset -= border * ( 2.f / (float) pixels[1] );
		xOffset -= ( border + getDogEarSize(vpRegion) ) * ( 2.f / (float) pixels[0] );

		if( aspectRatio < 1.f )
		{
			yOffset /= aspectRatio;
		}
		else if( aspectRatio > 1.f )
		{
			xOffset *= aspectRatio;
		}

		SoTranslation* transUR = (SoTranslation *) getAnyPart( "translationUR", TRUE );
		transUR->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

		SoNode* textUR = getTextNode( SoXipImageTextElement::TP_UPPER_RIGHT );
		if( textUR )
		{		
			textUR->set( "justification RIGHT" );
			textUR->set( "vAlignment TOP" );
		}

	// CENTER LEFT
		xOffset = -1.f;
		yOffset = 0.f;

		xOffset += border * ( 2.f / (float) pixels[0] );

		if( aspectRatio < 1.f )
		{
			yOffset /= aspectRatio;
		}
		else if( aspectRatio > 1.f )
		{
			xOffset *= aspectRatio;
		}

		SoTranslation* transCL = (SoTranslation *) getAnyPart( "translationCL", TRUE );
		transCL->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

		SoNode* textCL = getTextNode( SoXipImageTextElement::TP_CENTER_LEFT );
		if( textCL )
		{		
			textCL->set( "justification LEFT" );
			textCL->set( "vAlignment CENTER" );
		}

	// CENTER RIGHT
		xOffset = 1.f;
		yOffset = 0.f;

		xOffset -= border * ( 2.f / (float) pixels[0] );

		if( aspectRatio < 1.f )
		{
			yOffset /= aspectRatio;
		}
		else if( aspectRatio > 1.f )
		{
			xOffset *= aspectRatio;
		}

		SoTranslation* transCR = (SoTranslation *) getAnyPart( "translationCR", TRUE );
		transCR->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

		SoNode* textCR = getTextNode( SoXipImageTextElement::TP_CENTER_RIGHT );
		if( textCR )
		{		
			textCR->set( "justification RIGHT" );
			textCR->set( "vAlignment CENTER" );
		}

	// LOWER RIGHT
		xOffset =  1.0f;
		yOffset = -1.0f;

		yOffset += border * ( 2.f / (float) pixels[1] );
		xOffset -= border * ( 2.f / (float) pixels[0] );

		if( aspectRatio < 1.f )
		{
			yOffset /= aspectRatio;
		}
		else if( aspectRatio > 1.f )
		{
			xOffset *= aspectRatio;
		}

		SoTranslation* transLR = (SoTranslation *) getAnyPart( "translationLR", TRUE );
		transLR->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

		SoNode* textLR = getTextNode( SoXipImageTextElement::TP_LOWER_RIGHT );
		if( textLR )
		{
			textLR->set( "justification RIGHT" );
			textLR->set( "vAlignment BOTTOM" );
		}

	// LOWER CENTRE
		xOffset =  0.f;
		yOffset = -1.f;	

		yOffset += border * ( 2.f / (float) pixels[1] );

		if( aspectRatio < 1.f )
		{
			yOffset /= aspectRatio;
		}
		else if( aspectRatio > 1.f )
		{
			xOffset *= aspectRatio;
		}

		SoTranslation* transLC = (SoTranslation *) getAnyPart( "translationLC", TRUE );
		transLC->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

		SoNode* textLC = getTextNode( SoXipImageTextElement::TP_LOWER_CENTER );
		if( textLC )
		{		
			textLC->set( "justification LEFT" );
			textLC->set( "vAlignment BOTTOM" );
		}
	
	// LOWER LEFT
		xOffset = -1.0f;
		yOffset = -1.0f;

		yOffset += border * ( 2.f / (float) pixels[1] );
		xOffset += border * ( 2.f / (float) pixels[0] );

		if( aspectRatio < 1.f )
		{
			yOffset /= aspectRatio;
		}
		else if( aspectRatio > 1.f )
		{
			xOffset *= aspectRatio;
		}

		SoTranslation* transLL = (SoTranslation *) getAnyPart( "translationLL", TRUE );
		transLL->translation.setValue( SbVec3f(xOffset, yOffset, 0) );

		SoNode* textLL = getTextNode( SoXipImageTextElement::TP_LOWER_LEFT );
		if( textLL )
		{
			textLL->set( "justification LEFT" );
			textLL->set( "vAlignment BOTTOM" );
		}

		enableNotify(notifyEnabled);

	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glDisable( GL_LIGHTING );			// disable lighting
	glDisable( GL_DEPTH_TEST );			// diable depth test

	SoBaseKit::GLRender( action );

	glPopAttrib();
	}
	else
	{
		enableNotify(notifyEnabled);
	}	
}

void 
SoXipDisplayImageText::getBoundingBox( SoGetBoundingBoxAction* action )
{
	// text does not affect bounding box
}

SoNode*
SoXipDisplayImageText::getTextNode( int position )
{
	switch( position )
	{
	case SoXipImageTextElement::TP_UPPER_LEFT: 
		return (SoNode *) getAnyPart( "textUL", TRUE );

	case SoXipImageTextElement::TP_UPPER_CENTER: 
		return (SoNode *) getAnyPart( "textUC", TRUE );

	case SoXipImageTextElement::TP_UPPER_RIGHT: 
		return (SoNode *) getAnyPart( "textUR", TRUE );

	case SoXipImageTextElement::TP_CENTER_LEFT: 
		return (SoNode *) getAnyPart( "textCL", TRUE );

	case SoXipImageTextElement::TP_CENTER_RIGHT: 
		return (SoNode *) getAnyPart( "textCR", TRUE );

	case SoXipImageTextElement::TP_LOWER_LEFT: 
		return (SoNode *) getAnyPart( "textLL", TRUE );

	case SoXipImageTextElement::TP_LOWER_CENTER: 
		return (SoNode *) getAnyPart( "textLC", TRUE );

	case SoXipImageTextElement::TP_LOWER_RIGHT: 
		return (SoNode *) getAnyPart( "textLR", TRUE );

	default:
		SoDebugError::post( "SoXipDisplayImageText::getTextNode()", "Invalid position" );
	}

	return 0;
}

SoNode*
SoXipDisplayImageText::getMaterialNode( int position )
{
	switch( position )
	{
	case SoXipImageTextElement::TP_UPPER_LEFT: 
		return (SoNode *) getAnyPart( "materialUL", TRUE );

	case SoXipImageTextElement::TP_UPPER_CENTER: 
		return (SoNode *) getAnyPart( "materialUC", TRUE );

	case SoXipImageTextElement::TP_UPPER_RIGHT: 
		return (SoNode *) getAnyPart( "materialUR", TRUE );

	case SoXipImageTextElement::TP_CENTER_LEFT: 
		return (SoNode *) getAnyPart( "materialCL", TRUE );

	case SoXipImageTextElement::TP_CENTER_RIGHT: 
		return (SoNode *) getAnyPart( "materialCR", TRUE );

	case SoXipImageTextElement::TP_LOWER_LEFT: 
		return (SoNode *) getAnyPart( "materialLL", TRUE );

	case SoXipImageTextElement::TP_LOWER_CENTER: 
		return (SoNode *) getAnyPart( "materialLC", TRUE );

	case SoXipImageTextElement::TP_LOWER_RIGHT: 
		return (SoNode *) getAnyPart( "materialLR", TRUE );

	default:
		SoDebugError::post( "SoXipDisplayImageText::getMaterialNode()", "Invalid position" );
	}

	return 0;
}

int 
SoXipDisplayImageText::getDogEarSize( const SbViewportRegion& viewportRegion ) const
{
	if( dogEar.getValue() )
	{
		SbVec2s s = viewportRegion.getViewportSizePixels();

		int minSize = std::min(s[0], s[1]);
		int dogEarSize = minSize / 8;
		if( dogEarSize < 10 )
			return 0;

		return std::min(dogEarSize, 50);
	}
	
	return 0;
}


