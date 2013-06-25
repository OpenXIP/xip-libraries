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
