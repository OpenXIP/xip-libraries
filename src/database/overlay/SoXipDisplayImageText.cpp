/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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
		if( colorField )
			colorField->setValue( colorElt->get( (SoXipImageTextElement::TextElementPosition) pos ) );
	}

	const SbViewportRegion& vpRegion = SoViewportRegionElement::get( action->getState() );
	float aspectRatio = vpRegion.getViewportAspectRatio();

	const SbVec2s& pixels = vpRegion.getViewportSizePixels();
	int minDim = pixels[0] > pixels[1] ? pixels[1] : pixels[0];

	// do not display dicom text if segment size is less than 200
	if( minDim < 200 )
		return ;

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
		
	// UPPER CENTRE
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

	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glDisable( GL_LIGHTING );			// disable lighting
	glDisable( GL_DEPTH_TEST );			// diable depth test

	SoBaseKit::GLRender( action );

	glPopAttrib();
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
