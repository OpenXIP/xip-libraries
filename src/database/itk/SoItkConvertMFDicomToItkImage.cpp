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

#include <ItkImportImageFilter.h>
#include <Inventor/SoDB.h>
#include <xip/inventor/core/SoRadDataDicom.h>
#include <Rad/Data/RadDataObjectBase.h>
#include <Rad/Data/RadDICOMTypes.h>
#include "SoItkConvertMFDicomToItkImage.h"

SO_ENGINE_SOURCE( SoItkConvertMFDicomToItkImage );

SoItkConvertMFDicomToItkImage::SoItkConvertMFDicomToItkImage()
{
	SO_ENGINE_CONSTRUCTOR( SoItkConvertMFDicomToItkImage );

	// Inputs
	SO_ENGINE_ADD_INPUT( input, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( output, SoItkSFDataImage );
	mItkImage = 0;

	mPixelBuffer = 0;
	mBufferSize = 0;
}

void 
SoItkConvertMFDicomToItkImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkConvertMFDicomToItkImage, SoFieldConverter, "SoFieldConverter" );

	SoDB::addConverter( 
        SoRadMFDataDicom::getClassTypeId(),
		SoItkSFDataImage::getClassTypeId(),
		getClassTypeId() );
}

SoItkConvertMFDicomToItkImage::~SoItkConvertMFDicomToItkImage()
{
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
	}

	if( mPixelBuffer )
	{
		delete [] mPixelBuffer;
		mPixelBuffer = 0;
	}
}

void
SoItkConvertMFDicomToItkImage::evaluate()
{	
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
	}

	SO_ENGINE_OUTPUT( output, SoItkSFDataImage, setValue(0) );

	if( input.getNum() == 0 )
		return ;

    SoRadDataDicom* dicom = input[0];
    if( !dicom )
        return ;
    
	try
	{
		RadDataObjectBase* dobject = dicom->getDataObject();
        
		unsigned short height;
		dobject->getElement(
			RAD_IMAGE_ROWS_DICOMGROUP,
			RAD_IMAGE_ROWS_DICOMELEMENT,
			RadDataObjectBase::UINT16,
			1,
			sizeof( height ),
			&height );

        unsigned short width;
		dobject->getElement(
			RAD_IMAGE_COLUMNS_DICOMGROUP,
			RAD_IMAGE_COLUMNS_DICOMELEMENT,
			RadDataObjectBase::UINT16,
			1,
			sizeof( width ),
			&width );
                
        unsigned short bitsAllocated;
		dobject->getElement(
			RAD_IMAGE_BITSALLOCATED_DICOMGROUP,
			RAD_IMAGE_BITSALLOCATED_DICOMELEMENT,
			RadDataObjectBase::UINT16,
			1,
			sizeof( bitsAllocated ),
			&bitsAllocated );

		double spacing[2];
		dobject->getElement(
			RAD_IMAGE_PIXELSPACING_DICOMGROUP,
			RAD_IMAGE_PIXELSPACING_DICOMELEMENT,
			RadDataObjectBase::FLT64,
			2,
			sizeof( spacing ),
			spacing );

		double imagePositionPatient[3];
		dobject->getElement(
			RAD_IMAGE_POSITIONPATIENT_DICOMGROUP,
			RAD_IMAGE_POSITIONPATIENT_DICOMELEMENT,
			RadDataObjectBase::FLT64,
			3,
			sizeof( imagePositionPatient ),
			imagePositionPatient );

		double imageOrientationPatient[6];
		dobject->getElement(
			RAD_IMAGE_ORIENTATIONPATIENT_DICOMGROUP,
			RAD_IMAGE_ORIENTATIONPATIENT_DICOMELEMENT,
			RadDataObjectBase::FLT64,
			6,
			sizeof( imageOrientationPatient ),
			imageOrientationPatient );
            
        SbVec3f v1( imageOrientationPatient[0], 
            imageOrientationPatient[1], 
            imageOrientationPatient[2] );
        SbVec3f v2( imageOrientationPatient[3], 
            imageOrientationPatient[4], 
            imageOrientationPatient[5] );

		SbVec3f normal = v1.cross( v2 );

		// Compose model matrix
		SbMatrix rotation = SbMatrix(
			imageOrientationPatient[0], imageOrientationPatient[1], imageOrientationPatient[2], 0,
			imageOrientationPatient[3], imageOrientationPatient[4], imageOrientationPatient[5], 0,
			normal[0], normal[1], normal[2], 0,
			0, 0, 0, 1
        );
            
        SbMatrix translation;
		translation.setTranslate( SbVec3f( imagePositionPatient[0], imagePositionPatient[1], imagePositionPatient[2] ) );
        SbMatrix scale;
		scale.setScale( SbVec3f( spacing[0] * width, spacing[1] * height, 1.0 ) );
        
        SbMatrix model = scale * rotation * translation;
        
        if( bitsAllocated > 8 )
        {
			unsigned int new_size = width * height;
			if( !mPixelBuffer || mBufferSize != new_size )
			{
				if( mPixelBuffer )
					delete [] mPixelBuffer;
	            mPixelBuffer = new unsigned short[ new_size ];
				mBufferSize = new_size;
			}

            dobject->getElement(
				RAD_IMAGE_PIXEL_DATA_DICOMGROUP,
				RAD_IMAGE_PIXEL_DATA_DICOMELEMENT,
				RadDataObjectBase::UINT16,
				width * height,
				width * height * sizeof( unsigned short ),
                mPixelBuffer );
            
            typedef itk::ImportImageFilter< unsigned short, 2 > ImportFilterType;
            
            ImportFilterType::SizeType size;
            size[0] = width;
            size[1] = height;
            
            ImportFilterType::IndexType start;
            start[0] = 0;
            start[1] = 0;
            
            double origin[ 2 ];
            origin[0] = 0;
            origin[1] = 0;
            
            double spacing[ 2 ];
            spacing[0] = 1;
            spacing[1] = 1;
            
            ImportFilterType::RegionType region;
            region.SetIndex( start );
            region.SetSize( size );
            
            ImportFilterType::Pointer importFilter = ImportFilterType::New();
            importFilter->SetRegion( region );
            importFilter->SetOrigin( origin );
            importFilter->SetSpacing( spacing );
            importFilter->SetImportPointer(	(unsigned short *) mPixelBuffer,
				size[0] * size[1], false );
            importFilter->Update();
            
            /* Since Itk objects are reference-counted, we need to manually   */
            /* increment the reference count of the resulting image, to avoid */
            /* the importFilter instance to destroy it.                       */
            /*                                                                */
            importFilter->GetOutput()->Register();
            
            mItkImage = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 2,
                model );
            mItkImage->ref();
            mItkImage->setPointer( importFilter->GetOutput() );
        }
        else
        {
            SoDebugError::post( __FILE__, "Support for Char Images is currently disabled in RadItk" );
            return ;            
        }
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), "line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown exception" );
		return ;
	}

	SO_ENGINE_OUTPUT( output, SoItkSFDataImage, setValue( mItkImage ) );
}

SoField* 
SoItkConvertMFDicomToItkImage::getInput( SoType type )
{
	if( type == SoRadMFDataDicom::getClassTypeId() )
	{
		return &input;
	}

	SoDebugError::post( __FILE__, "SoItkConvertMFDicomToItkImage::getOutput() : unresolved input" );
	return 0;
}

SoEngineOutput* 
SoItkConvertMFDicomToItkImage::getOutput( SoType type )
{
	if( type == SoItkSFDataImage::getClassTypeId() )
	{
		return &output;
	}

	SoDebugError::post( __FILE__, "SoItkConvertMFDicomToItkImage::getOutput() : unresolved output" );
	return 0;
}