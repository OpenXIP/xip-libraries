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
