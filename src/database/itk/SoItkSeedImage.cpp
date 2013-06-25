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
#include <itkImage.h>
#include "SoItkSeedImage.h"

SO_ENGINE_SOURCE( SoItkSeedImage );

SoItkSeedImage::SoItkSeedImage()
{
	// Do standard constructor stuff
	SO_ENGINE_CONSTRUCTOR( SoItkSeedImage );

    SO_ENGINE_ADD_INPUT( ReferenceImage, (0) );
    SO_ENGINE_ADD_INPUT( Seeds, (0, 0, 0) );
    Seeds.setNum(0);
    
    SO_ENGINE_ADD_OUTPUT( SeedImage, SoItkSFDataImage );
    mSeedImage = 0;
}

SoItkSeedImage::~SoItkSeedImage()
{
	if( mSeedImage )
	{
		mSeedImage->unref();
		mSeedImage= 0;
	}
}

void 
SoItkSeedImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkSeedImage, SoEngine, "SoEngine" );
}

void SoItkSeedImage::evaluate()
{
    if( mSeedImage )
    {
        mSeedImage->unref();
        mSeedImage = 0;        
        SO_ENGINE_OUTPUT( SeedImage, SoItkSFDataImage, setValue( 0 ) );
    }
    
    if( !ReferenceImage.getValue() )
        return ;
    
    try
	{
        SoItkDataImage* referenceImage = ReferenceImage.getValue();
        
        if( referenceImage->getNumDimension() != 2 )
        {
            SoDebugError::post( __FILE__, "Seed Images only supports 2D" );
            return ;
        }
                
        switch( referenceImage->getType() )
        {
            case SoItkDataImage::UNSIGNED_SHORT:
            {
				typedef itk::Image< unsigned short, 2 > SeedImageType;
                
				SeedImageType::IndexType index;
				index.m_Index[0] = 0;
				index.m_Index[1] = 0;

				SeedImageType::SizeType size;
				size.m_Size[0] = referenceImage->getDimension( 0 );
				size.m_Size[1] = referenceImage->getDimension( 1 );

				SeedImageType::RegionType region;
				region.SetIndex( index );
				region.SetSize( size );
                
				SeedImageType::Pointer seedImage = SeedImageType::New();
                seedImage->SetRegions( region );
                seedImage->Allocate();
                seedImage->FillBuffer( itk::NumericTraits< unsigned short >::Zero );
                seedImage->Register();
                
                // Add the seeds
                unsigned int numSeeds = Seeds.getNum();
                for( unsigned int i = 0; i < numSeeds; ++ i )
                {
                    SbVec3f v = Seeds[i];
                    referenceImage->getModelMatrix().inverse().multVecMatrix( v, v );
                    
                    itk::Index< 2 > index;
                    index.m_Index[0] = v[0] * referenceImage->getDimension(0);
                    index.m_Index[1] = v[1] * referenceImage->getDimension(1);
                    
                    seedImage->SetPixel( index, 1 );
                }

				mSeedImage = new SoItkDataImage( referenceImage->getType(), referenceImage->getNumDimension(),
					referenceImage->getModelMatrix() );
				mSeedImage->ref();
				mSeedImage->setPointer( seedImage );
            }
            break ;
            
            case SoItkDataImage::FLOAT:
            {
				typedef itk::Image< float, 2 > SeedImageType;
                
				SeedImageType::IndexType index;
				index.m_Index[0] = 0;
				index.m_Index[1] = 0;

				SeedImageType::SizeType size;
				size.m_Size[0] = referenceImage->getDimension( 0 );
				size.m_Size[1] = referenceImage->getDimension( 1 );

				SeedImageType::RegionType region;
				region.SetIndex( index );
				region.SetSize( size );
                
				SeedImageType::Pointer seedImage = SeedImageType::New();
                seedImage->SetRegions( region );
                seedImage->Allocate();
                seedImage->FillBuffer( itk::NumericTraits< float >::Zero );
                seedImage->Register();
                
                // Add the seeds
                unsigned int numSeeds = Seeds.getNum();
                for( unsigned int i = 0; i < numSeeds; ++ i )
                {
                    SbVec3f v = Seeds[i];
                    referenceImage->getModelMatrix().inverse().multVecMatrix( v, v );
                    
                    itk::Index< 2 > index;
                    index.m_Index[0] = v[0] * referenceImage->getDimension(0);
                    index.m_Index[1] = v[1] * referenceImage->getDimension(1);
                    
                    seedImage->SetPixel( index, 1 );
                }

				mSeedImage = new SoItkDataImage( referenceImage->getType(), referenceImage->getNumDimension(),
					referenceImage->getModelMatrix() );
				mSeedImage->ref();
				mSeedImage->setPointer( seedImage );
			}
			break ;
        }
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), " line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
    
    SO_ENGINE_OUTPUT( SeedImage, SoItkSFDataImage, setValue( mSeedImage ) );    
}

/*
void
SoItkSeedImage::onChangeSeeds()
{
    SoItkDataImage* referenceImage = ReferenceImage.getValue();
    
    if( !referenceImage )
        return ;
    
    if( mSeedImage )        
    {
        switch( mSeedImage->getType() )
        {
            case SoItkDataImage::UNSIGNED_SHORT:
            {
                typedef itk::Image< unsigned short, 2 > SeedImageType;
                SeedImageType::Pointer seedImage = static_cast< SeedImageType* >(
                    mSeedImage->getPointer );
                
                // Reset the previous image
                seedImage->FillBuffer( itk::NumericTraits< unsigned short >::Zero );
                
                // Add the seeds
                unsigned int numSeeds = Seeds.getNum();
                for( unsigned int i = 0; i < numSeeds; ++ i )
                {
                    SbVec3f v = Seeds[i];
                    referenceImage->getModelMatrix().inverse().multVecMatrix( v, v );
                    
                    itk::Index< 2 > index;
                    index.m_Index[0] = v[0] * referenceImage.getDimension(0);
                    index.m_Index[1] = v[1] * referenceImage.getDimension(1);
                    
                    seedImage->SetPixel( index, 1 );
                }
            }
            break ;
            
            case SoItkDataImage::FLOAT:
            {
                typedef itk::Image< float, 2 > SeedImageType;
                SeedImageType::Pointer seedImage = static_cast< SeedImageType* >(
                    mSeedImage->getPointer );
                
                // Reset the previous image
                seedImage->FillBuffer( itk::NumericTraits< float >::Zero );
                
                // Add the seeds
                unsigned int numSeeds = Seeds.getNum();
                for( unsigned int i = 0; i < numSeeds; ++ i )
                {
                    SbVec3f v = Seeds[i];
                    referenceImage->getModelMatrix().inverse().multVecMatrix( v, v );
                    
                    itk::Index< 2 > index;
                    index.m_Index[0] = v[0] * referenceImage.getDimension(0);
                    index.m_Index[1] = v[1] * referenceImage.getDimension(1);
                    
                    seedImage->SetPixel( index, 1 );
                }
            }
            break ;
        }
    }
    else
    {
        createImage();
    }
}

void
SoItkSeedImage::createImage()
{
    if( mSeedImage )
    {
        mSeedImage->unref();
        mSeedImage = 0;        
    }
    
    if( !ReferenceImage.getValue() )
    {
        SoDebugError::post( __FILE__, "Must specify a reference image" );
        return ;
    }
    
    try
	{
        SoItkDataImage* referenceImage = ReferenceImage.getValue();
        
        if( referenceImage.getNumDimension() != 2 )
        {
            SoDebugError::post( __FILE__, "Seed Images only supports 2D" );
            return ;
        }
        
        typedef itkImageBase< 2 > BaseImageType;
        BaseImageType::Pointer seedImage = BaseImageType::New();
        
        SeedImageType::IndexType index;
        index.m_Index[0] = 0;
        index.m_Index[1] = 0;
        SeedImageType::SizeType size;
        size.m_Size[0] = referenceImage->getDimension( 0 );
        size.m_Size[1] = referenceImage->getDimension( 1 );

        ImageRegionType region;
        region.SetIndex( index );
        region.SetSize( size );
        
        switch( referenceImage->getType() )
        {
            case SoItkDataImage::UNSIGNED_SHORT:
            {
                typedef itkImage< unsigned short, 2 > SeedImageType;
                
                SeedImageType::Pointer us_image =
                    static_cast< SeedImageType::Pointer >( seedImage );
                us_image->SetRegions( region );
                us_image->Allocate();
                us_image->FillBuffer( itk::NumericTraits< unsigned short >::Zero );
                us_image->Register();
            }
            break ;
            
            case SoItkDataImage::FLOAT:
            {
                typedef itkImage< float, 2 > SeedImageType;
                
                SeedImageType::Pointer us_image =
                    static_cast< SeedImageType::Pointer >( seedImage );
                us_image->SetRegions( region );
                us_image->Allocate();
                us_image->FillBuffer( itk::NumericTraits< float >::Zero );
                us_image->Register();
            }
            break ;
            
        }
        
        mSeedImage = new SoItkDataImage( referenceImage->getType(), referenceImage->getNumDimension(),
            referenceImage->getModelMatrix() );
        mSeedImage->ref();
        mSeedImage->setPointer( seedImage );
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), " line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
}

*/
