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

/**
*	@file	SoXipLutColorBar.cpp
*	@brief	Implementation of the SoXipLutColorBar class
*	@author	Julien Gein
**/

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/errors/SoMemoryError.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoIndexedTriangleStripSet.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include "SoXipLutColorBar.h"

SO_NODE_SOURCE( SoXipLutColorBar );

SoXipLutColorBar::SoXipLutColorBar()
{
	SO_NODE_CONSTRUCTOR( SoXipLutColorBar );

	SO_XIP_KIT_ADD_ENTRY( mTopSeparator, SoSeparator, this );

	// Camera
	SO_XIP_KIT_ADD_ENTRY( mCamera, SoOrthographicCamera, mTopSeparator );

	// Coordinates
	SO_XIP_KIT_ADD_ENTRY( mCoord, SoCoordinate3, mTopSeparator );

	// Texture Quad
	SO_XIP_KIT_ADD_ENTRY( mTextureSeparator, SoSeparator, mTopSeparator );
    SO_XIP_KIT_ADD_ENTRY( mTexture, SoXipTexture, mTextureSeparator );	
	SO_XIP_KIT_ADD_ENTRY( mTexCoord, SoTextureCoordinate2, mTextureSeparator );
	SO_XIP_KIT_ADD_ENTRY( mTriangleSet, SoIndexedTriangleStripSet, mTextureSeparator );

	// Border
	SO_XIP_KIT_ADD_ENTRY( mBorderSeparator, SoSeparator, mTopSeparator );
	SO_XIP_KIT_ADD_ENTRY( mBorderColor, SoBaseColor, mBorderSeparator );
	SO_XIP_KIT_ADD_ENTRY( mBorderLines, SoIndexedLineSet, mBorderSeparator );

    // Bottom Label
    SO_XIP_KIT_ADD_ENTRY( mBottomTextSeparator, SoSeparator, mTopSeparator );
    SO_XIP_KIT_ADD_ENTRY( mBottomTextOffset, SoTranslation, mBottomTextSeparator );
    SO_XIP_KIT_ADD_ENTRY( mBottomText, SoXipText2, mBottomTextSeparator );

    // Top Label
    SO_XIP_KIT_ADD_ENTRY( mTopTextSeparator, SoSeparator, mTopSeparator );
    SO_XIP_KIT_ADD_ENTRY( mTopTextOffset, SoTranslation, mTopTextSeparator );
    SO_XIP_KIT_ADD_ENTRY( mTopText, SoXipText2, mTopTextSeparator );

	SO_NODE_DEFINE_ENUM_VALUE( BarPosition, LEFT );
	SO_NODE_DEFINE_ENUM_VALUE( BarPosition, RIGHT );
	SO_NODE_DEFINE_ENUM_VALUE( BarPosition, TOP );
	SO_NODE_DEFINE_ENUM_VALUE( BarPosition, BOTTOM );

	SO_NODE_SET_SF_ENUM_TYPE( position, BarPosition );

	SO_NODE_ADD_FIELD( position, (RIGHT) );
	SO_NODE_ADD_FIELD( origin, (0, 0) );
	SO_NODE_ADD_FIELD( size, (0, 0) );
	SO_NODE_ADD_FIELD( showAlpha, (FALSE) );
	SO_NODE_ADD_FIELD( borderColor, (1, 1, 1) );
	SO_NODE_ADD_FIELD( bottomLabel, ("") );
	SO_NODE_ADD_FIELD( topLabel, ("") );
	
	mCoord->set( "point [ 0 0 0, 1 0 0, 1 1 0, 0 1 0 ]" );
	mTexCoord->set( "point [ 0 0, 0 1, 1 1, 1 0 ]" );
	mBorderLines->set( "coordIndex [0, 1, 2, 3, 0, -1]" );
	mTriangleSet->set( "coordIndex [0, 1, 2, -1, 0, 2, 3, -1]" );	

	mBorderColor->getField( "rgb" )->connectFrom( &borderColor );
    mBottomText->getField( "string" )->connectFrom( &bottomLabel );
    mTopText->getField( "string" )->connectFrom( &topLabel );

    mFieldSensors[0] = new SoFieldSensor( fieldSensorCB, this );
	mFieldSensors[0]->attach( &showAlpha );
	mFieldSensors[1] = new SoFieldSensor( fieldSensorCB, this );
	mFieldSensors[1]->attach( &position );

	setOrthographicCamera();

	mReloadTexture = TRUE;
	mLutId = 0;
	mDataTexture = 0;
}

SoXipLutColorBar::~SoXipLutColorBar()
{
	delete mFieldSensors[0];
	delete mFieldSensors[1];

	if( mDataTexture )
	{
		mDataTexture->unref();
		mDataTexture = 0;
	}
}

void
SoXipLutColorBar::initClass()
{
	SO_NODE_INIT_CLASS( SoXipLutColorBar, SoXipKit, "SoXipKit" );
}

void
SoXipLutColorBar::setOrthographicCamera()
{	
	SoOrthographicCamera* ortho = (SoOrthographicCamera *) mCamera;

	if( ortho )
	{
		ortho->viewportMapping.setValue( SoOrthographicCamera::LEAVE_ALONE );
		ortho->position.setValue( SbVec3f(0.5, 0.5, 0) );
		ortho->height.setValue(1);
		ortho->nearDistance.setValue(-1);
		ortho->farDistance.setValue(1);
	}
}

void
SoXipLutColorBar::loadTexture(SbXipImage* image)
{
	if( mDataTexture )
	{
		mDataTexture->unref();
		mDataTexture = 0;
	}
		
	if( image )
	{
		try
		{
			if( image->getType() != SbXipImage::FLOAT ||
				image->getComponentLayoutType() != SbXipImage::RGBA )
			{
				SoError::post( "Invalid LUT image: expects RGBA FLOAT" );
				return ;
			}

			SbXipImage* textureImage = new SbXipImage(
				SbXipImageDimensions(4096, 1, 1),
				SbXipImage::UNSIGNED_BYTE,
				8,
				4,
				SbXipImage::INTERLEAVED,
				SbXipImage::RGBA );

			if( !textureImage )
			{
				SoMemoryError::post( "Failed to allocate texture" );
				return ;
			}

			float* imagePtr = (float *) image->refBufferPtr();
			unsigned char* texturePtr = (unsigned char *) textureImage->refBufferPtr();
	        
			double scaleFactor =  ((double) image->getDimStored()[0]) / 4096.;

			// always quantize to 12 bits for texture handling simplicity
			// (color bar doesn't have to be completely accurate)
			if (showAlpha.getValue())
			{
				for( int i = 0; i < 4096; i++ )
				{
					int index = int(i * scaleFactor);
					int i4 = 4*i;
					int index4 = 4*index;
					texturePtr[ i4   ] = imagePtr[index4  ] * 255;
					texturePtr[ i4+1 ] = imagePtr[index4+1] * 255;
					texturePtr[ i4+2 ] = imagePtr[index4+2] * 255;
					texturePtr[ i4+3 ] = imagePtr[index4+3] * 255;
				}
			}
			else
			{
				for( int i = 0; i < 4096; i++ )
				{
					int index = int(i * scaleFactor);
					int i4 = 4*i;
					int index4 = 4*index;

					texturePtr[ i4   ] = imagePtr[index4  ] * 255;
					texturePtr[ i4+1 ] = imagePtr[index4+1] * 255;
					texturePtr[ i4+2 ] = imagePtr[index4+2] * 255;
					texturePtr[ i4+3 ] = 255; //constant alpha
				}
			}
		    
			image->unrefBufferPtr();
			textureImage->unrefBufferPtr();

			mDataTexture = new SoXipDataImage;
			mDataTexture->ref();
			mDataTexture->set( textureImage );

			SoXipSFDataImage* imageField = (SoXipSFDataImage *) mTexture->getField( "image" );
			if( imageField && imageField->isOfType( SoXipSFDataImage::getClassTypeId() ) )
				imageField->setValue( mDataTexture );

			mTexture->set( "textureDimension TEXTURE_2D" );
		}
		catch (...)
		{
			SoError::post( "Unknown exception in SoXipLutColorBar::loadTexture()" );
		}
	}
}

void 
SoXipLutColorBar::fieldSensorCB( void* userData, SoSensor* sensor )
{
	((SoXipLutColorBar *) userData)->fieldChanged( ((SoFieldSensor *) sensor)->getAttachedField() );
}

void 
SoXipLutColorBar::fieldChanged( SoField* whichField )
{
	if( whichField == &showAlpha )
	{
		mReloadTexture = TRUE;
	}
	else if( whichField == &position )
	{
		if( position.getValue() == TOP || position.getValue() == BOTTOM )
			// Horizontal
			mTexCoord->set( "point [ 0 0, 1 0, 1 1, 0 1 ]" );
		else
			// Vertical
			mTexCoord->set( "point [ 0 0, 0 1, 1 1, 1 0 ]" );
	}
}

void
SoXipLutColorBar::GLRender( SoGLRenderAction* action )
{
	if( !action || !action->getState() )
		return ;

	if( !size.getValue()[0] || !size.getValue()[1] )
		return ;
    
    try
    {
		// Update LUT Texture
	    SoXipData* data = SoXipLutElement::get( action->getState() );       
	    if( !data )
            return ; 

	    if( !data->isOfType( SoXipDataImage::getClassTypeId() ) )
	    {
		    SoDebugError::post( __FILE__, "Invalid Lut Image" );
		    return ;
	    }

		if( data->getDataId() != mLutId )
			mReloadTexture = TRUE;

	    if( mReloadTexture )
	    {
		    loadTexture( ((SoXipDataImage *) data)->get() );

		    mReloadTexture = false;

		    mLutId = data->getDataId();
	    }

		// Set Geometries
		SbViewportRegion viewport = SoViewportRegionElement::get( action->getState() );
		SbVec2s viewportSize = viewport.getViewportSizePixels();

		SoMFVec3f* pointField = ((SoMFVec3f *) mCoord->getField( "point" ));
		SbVec3f* coords = pointField->startEditing();

		BarPosition barPos = (BarPosition) position.getValue();
		SbVec2f barOrigin = origin.getValue();
		SbVec2f barSize = size.getValue();

		coords[0] = SbVec3f( barOrigin[0], barOrigin[1], 0 );
		coords[1] = SbVec3f( barOrigin[0] + barSize[0], barOrigin[1], 0 );
		coords[2] = SbVec3f( barOrigin[0] + barSize[0], barOrigin[1] + barSize[1], 0 );
		coords[3] = SbVec3f( barOrigin[0], barOrigin[1] + barSize[1], 0 );

        // Labels
        SoSFVec3f* bOffset = ((SoSFVec3f *) mBottomTextOffset->getField( "translation" ));
        SoSFVec3f* tOffset = ((SoSFVec3f *) mTopTextOffset->getField( "translation" ));

        SbVec3f offsetUp(0, 6. / (float) viewportSize[1], 0);
        SbVec3f offsetDown(0, -6. / (float) viewportSize[1], 0);

        if( barPos == LEFT )
        {
            bOffset->setValue( coords[0] + offsetDown );
            tOffset->setValue( coords[3] + offsetUp );
            
            mBottomText->set( "justification LEFT" );
            mBottomText->set( "vAlignment TOP" );
            mTopText->set( "justification LEFT" );
            mTopText->set( "vAlignment BOTTOM" );			
        }
        else if( barPos == RIGHT )
        {
            bOffset->setValue( coords[1] + offsetDown );
            tOffset->setValue( coords[2] + offsetUp );

            mBottomText->set( "justification RIGHT" );
            mBottomText->set( "vAlignment TOP" );
            mTopText->set( "justification RIGHT" );
            mTopText->set( "vAlignment BOTTOM" );			
        }
        else if( barPos == TOP )
        {
            bOffset->setValue( coords[3] + offsetUp );
            tOffset->setValue( coords[2] + offsetUp );

            mBottomText->set( "justification LEFT" );
            mBottomText->set( "vAlignment BOTTOM" );
            mTopText->set( "justification RIGHT" );
            mTopText->set( "vAlignment BOTTOM" );
        }
        else if( barPos == BOTTOM )
        {
            bOffset->setValue( coords[0] + offsetDown );
            tOffset->setValue( coords[1] + offsetDown );

            mBottomText->set( "justification LEFT" );
            mBottomText->set( "vAlignment TOP" );
            mTopText->set( "justification RIGHT" );
            mTopText->set( "vAlignment TOP" );
        }
		pointField->finishEditing();

		// Call rendering
		GLRenderSub( action );
    }
	catch (...)
    {
        SoError::post(__FILE__, "Unknown error while loading raw image");
        return;
    }
}

void
SoXipLutColorBar::GLRenderSub( SoGLRenderAction* action )
{
	glPushAttrib( GL_ENABLE_BIT );
	glDisable( GL_DEPTH_TEST );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	// Render children
	SoXipKit::GLRender( action );

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );

	glPopAttrib();
}