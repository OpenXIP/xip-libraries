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

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SbXipImageFile.h>
#include <Inventor/errors/SoMemoryError.h>
#include "SoXipLoadRaw.h"
#include <xip/inventor/core/SbXipDirtyFieldList.h>

SO_ENGINE_SOURCE( SoXipLoadRaw );

SoXipLoadRaw::SoXipLoadRaw()
{
	SO_ENGINE_CONSTRUCTOR( SoXipLoadRaw );

	SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, UBYTE );
	SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, USHORT );
    SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, SHORT );
	 SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, FLOAT32 );
	SO_ENGINE_SET_SF_ENUM_TYPE( voxelType, VoxelType );

	SO_ENGINE_ADD_INPUT( voxelType, (UBYTE) );
	SO_ENGINE_ADD_INPUT( width, (0 ));
	SO_ENGINE_ADD_INPUT( height, (0) );
	SO_ENGINE_ADD_INPUT( depth, (0) );
	SO_ENGINE_ADD_INPUT( bitsUsed, (8) );
	SO_ENGINE_ADD_INPUT( modelMatrix, (SbMatrix::identity()) );
	SO_ENGINE_ADD_INPUT( file, ("") );

	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage);

	mDataOutput = 0;
}

SoXipLoadRaw::~SoXipLoadRaw()
{
	SbXipDirtyFieldList::remove( &file );

	if( mDataOutput )
	{
		mDataOutput->unref();
		mDataOutput = 0;
	}
}

void 
SoXipLoadRaw::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipLoadRaw, SoEngine, "Engine" );
}

void
SoXipLoadRaw::evaluate()
{
	// Reset the previous outputs
	if( mDataOutput )
	{
		mDataOutput->unref();
		mDataOutput = 0;
		SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(0) );
	}

    SbXipImage* img = 0;
    try
    {
	    if( (width.getValue() > 0) &&
		    (height.getValue() > 0) &&
		    (depth.getValue() > 0) &&
		    (bitsUsed.getValue() > 0) &&
		    (file.getValue().getLength() > 0) )
	    {
            int voxelStorageType = voxelType.getValue();

            SbXipImage::DataType xipDataType;
            switch (voxelStorageType)
            {
            case UBYTE:
                xipDataType = SbXipImage::UNSIGNED_BYTE;
                break;
            case USHORT:
                xipDataType = SbXipImage::UNSIGNED_SHORT;
                break;
            case SHORT:
                xipDataType = SbXipImage::SHORT;
                break;
				case FLOAT32:
					xipDataType = SbXipImage::FLOAT;
                break;
            default:
				SoError::post( "Unsupported image type" );
				goto error;
            }

		    img = new SbXipImage(
			    SbXipImageDimensions( width.getValue(), height.getValue(), depth.getValue() ),
			    xipDataType,
			    bitsUsed.getValue(), 1, SbXipImage::SEPARATE, SbXipImage::LUMINANCE,
				modelMatrix.getValue() );

            if( !img )
            {
				SoMemoryError::post( "Error allocating image" );
				goto error;
            }

		    if( !readImage( file.getValue().getString(), 0, *img ) )
		    {
                SoError::post( "Reading raw image data from \"%s\" failed!", file.getValue().getString() );
				goto error;
			}
		    
			mDataOutput = new SoXipDataImage;
            if( !mDataOutput )
			{
				SoMemoryError::post( "Error allocating data image" );
				goto error;
			}

			mDataOutput->ref();
			mDataOutput->set( img );

			// Update output
			SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue( mDataOutput ) );
	    }
    }
	catch(...)
	{
		SoError::post( "Unknown exception: loading raw data from \"%s\" failed!",
			file.getValue().getString() );
		goto error;
	}

	return ;

// Error handling
error:
	if( mDataOutput )
	{
		mDataOutput->unref();
		mDataOutput = 0;
	}
	if( img )
	{
		delete img;
        img = 0;
	}
}

SbBool
SoXipLoadRaw::readInstance( SoInput* in, unsigned short flags )
{
	#if defined(COIN_DLL) || defined (COIN_NO_DLL)
	// SGI automatically triggers evaluate after loading but COIN doesn't
	SbXipDirtyFieldList::append(&file);
	#endif

	return SoEngine::readInstance( in, flags );
}
