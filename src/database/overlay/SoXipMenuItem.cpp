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