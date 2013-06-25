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
#include "SoXipSaveRaw.h"
#include <xip/inventor/core/SbXipDirtyFieldList.h>

SO_ENGINE_SOURCE( SoXipSaveRaw );

SoXipSaveRaw::SoXipSaveRaw()
{
	SO_ENGINE_CONSTRUCTOR( SoXipSaveRaw );

	SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, UBYTE );
	SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, USHORT );
    SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, SHORT );
	 SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, FLOAT32 );
	SO_ENGINE_SET_SF_ENUM_TYPE( voxelType, VoxelType );

	SO_ENGINE_ADD_INPUT( saveImage, () );

	SO_ENGINE_ADD_INPUT( image, (0));
	SO_ENGINE_ADD_INPUT( file, ("") );

	SO_ENGINE_ADD_INPUT( voxelType, (UBYTE) );
	SO_ENGINE_ADD_INPUT( width, (0 ));
	SO_ENGINE_ADD_INPUT( height, (0) );
	SO_ENGINE_ADD_INPUT( depth, (0) );
	SO_ENGINE_ADD_INPUT( bitsUsed, (8) );

	

	mImageReady = false;
}

SoXipSaveRaw::~SoXipSaveRaw()
{
	SbXipDirtyFieldList::remove( &file );
}

void 
SoXipSaveRaw::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipSaveRaw, SoEngine, "Engine" );
}

void
SoXipSaveRaw::inputChanged(SoField * changedField)
{
	try
    {
		//only save the image whenever someone presses the save button!
		if (changedField == &saveImage)
		{
			mImageReady = true;
			//I know this should never EVER be done, but in this case - the hard drive can hardly request this engine to write anything.... can it?
			evaluate();
		}else
		{
			mImageReady = false;
			if(changedField == &image)
			{
				//we can evaluate, if the image has the expected values and display them to the user...
				evaluate();
			}
		}
	}
    catch (...)
    {
        SoError::post(__FUNCTION__, "Unknown Exception");
    }
}

void
SoXipSaveRaw::evaluate()
{
	try
	{
		//check if there is data in the input image that is supposed to be stored as a raw file...
		SoXipDataImage * dataImage = image.getValue();
		if(dataImage)
		{
			SbXipImage * img = dataImage->get();
			if(img)
			{
				width.setValue( (short)img->getDimStored()[0] );
				height.setValue( (short)img->getDimStored()[1] );
				depth.setValue( (short)img->getDimStored()[2] );
				bitsUsed.setValue( (short)img->getBitsStored() );

				switch( img->getType() )
				{
				case SbXipImage::UNSIGNED_BYTE:
					voxelType.setValue(UBYTE);
					break;
				case SbXipImage::UNSIGNED_SHORT:
					voxelType.setValue(USHORT);
					break;
				case SbXipImage::SHORT:
					voxelType.setValue(SHORT);
					break;
				case SbXipImage::FLOAT:
					voxelType.setValue(FLOAT32);
					break;
				default:
					SoError::post( "Unsupported image input type" );
				}

				//only save the image whenever someone presses the save button!
				if(mImageReady)
				{
					//do we have an output file path defined
					if(file.getValue().getLength() > 0)
					{
						if( !writeImage( file.getValue().getString(), 0, *img ) )
						{
							SoError::post( "Writing raw image data into \"%s\" failed!", file.getValue().getString() );
						}
					}else
					{
						SoError::post( "No path specified to save image!" );
					}
				}
				
			}else
			{
				SoMemoryError::post( "Error getting image" );
			}
		}

	}catch(...)
	{
		SoError::post( "Unknown exception: saving raw data to \"%s\" failed!",
			file.getValue().getString() );
	}

}



SbBool
SoXipSaveRaw::readInstance( SoInput* in, unsigned short flags )
{
	#if defined(COIN_DLL) || defined (COIN_NO_DLL)
	// SGI automatically triggers evaluate after loading but COIN doesn't
	SbXipDirtyFieldList::append(&file);
	#endif

	return SoEngine::readInstance( in, flags );
}

