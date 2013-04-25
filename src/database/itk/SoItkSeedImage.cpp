/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
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