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
#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>
#include <Inventor/SoDB.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include "SoItkConvertItkImageToXipImage.h"

SO_ENGINE_SOURCE( SoItkConvertItkImageToXipImage );

SoItkConvertItkImageToXipImage::SoItkConvertItkImageToXipImage()
{
	SO_ENGINE_CONSTRUCTOR( SoItkConvertItkImageToXipImage );

    // Inputs
	SO_ENGINE_ADD_INPUT( input, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage );

	mXipImage = 0;
}

void 
SoItkConvertItkImageToXipImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkConvertItkImageToXipImage, SoFieldConverter, "SoFieldConverter" );

	// Register this converter's type with the Inventor database
	//
	SoDB::addConverter( SoItkSFDataImage::getClassTypeId(),
		SoXipSFDataImage::getClassTypeId(),
		getClassTypeId() );
}

SoItkConvertItkImageToXipImage::~SoItkConvertItkImageToXipImage()
{
	if( mXipImage )
	{
		mXipImage->unref();
		mXipImage = 0;
	}
}

void
SoItkConvertItkImageToXipImage::evaluate()
{
	if( mXipImage )
	{
		mXipImage->unref();
		mXipImage = 0;
		SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(0) );
	}

	SoItkDataImage* radItkImage = input.getValue();
	if( !radItkImage )
		return ;

	if( radItkImage->getType() != SoItkDataImage::UNSIGNED_SHORT &&
		radItkImage->getType() != SoItkDataImage::FLOAT &&
		radItkImage->getType() != SoItkDataImage::UNSIGNED_CHAR &&
		radItkImage->getType() != SoItkDataImage::SHORT )
	{
		SoDebugError::post( __FILE__, "Itk image only supports UNSIGNED_SHORT, UNSIGNED_CHAR, SHORT or FLOAT" );
		return ;
	}

	try
	{
		#define CREATE_RAD_IMAGE( Type, TypeFlag, ComponentLayoutFlag, Dimension, NumComponents )		\
		{                                                                              					\
			typedef itk::Image< Type, Dimension > ImageType;                           					\
			ImageType* itkImage = static_cast< ImageType* >( radItkImage->getPointer() );               \
																					   					\
			ImageType::RegionType region = itkImage->GetBufferedRegion();              					\
				                                                                       					\
			SbXipImageDimensions dimensions(1, 1, 1);													\
			for( unsigned int i = 0; i < Dimension; ++ i )                             					\
				dimensions[i] = region.GetSize()[i];                                   					\
				                                                                       					\
	 		SbXipImage* image = new SbXipImage( dimensions,                            					\
				SbXipImage::TypeFlag, 12, itkImage->GetBufferPointer(),              					\
				NumComponents, SbXipImage::INTERLEAVED, SbXipImage::ComponentLayoutFlag,				\
				radItkImage->getModelMatrix() );                                       					\
																					   					\
			mXipImage = new SoXipDataImage;                                            					\
			mXipImage->ref();                                                          					\
			mXipImage->addRef( radItkImage );                                          					\
			mXipImage->set( image );                                                   					\
		}

		switch( radItkImage->getNumDimension() )
		{
			case 2: 
			{
				switch( radItkImage->getType() )
				{
					case SoItkDataImage::UNSIGNED_SHORT:
					{
						switch ( radItkImage->getComponentLayoutType())
						{
							case SoItkDataImage::LUMINANCE:
							{
								 CREATE_RAD_IMAGE( unsigned short, UNSIGNED_SHORT, LUMINANCE, 2, 1 );
							}
							break ;
							case SoItkDataImage::RGB:
							{
								CREATE_RAD_IMAGE( itk::RGBPixel<unsigned short>, UNSIGNED_SHORT, RGB, 2, 3 );
							}
							break ;
							case SoItkDataImage::RGBA:
							{
								CREATE_RAD_IMAGE( itk::RGBAPixel<unsigned short>, UNSIGNED_SHORT, RGBA, 2, 4 );
							}
							break ;						
						}
					}
					break ;
					case SoItkDataImage::FLOAT:
					{
						switch ( radItkImage->getComponentLayoutType())
						{
							case SoItkDataImage::LUMINANCE:
							{
								CREATE_RAD_IMAGE( float, FLOAT, LUMINANCE, 2, 1 );
							}
							break ;
							case SoItkDataImage::RGB:
							{
								CREATE_RAD_IMAGE( itk::RGBPixel<float>, FLOAT, RGB, 2, 3 );
							}
							break ;
							case SoItkDataImage::RGBA:
							{
								CREATE_RAD_IMAGE( itk::RGBAPixel<float>, FLOAT, RGBA, 2, 4 );
							}
							break ;						
						}
					}
					break ;
					case SoItkDataImage::UNSIGNED_CHAR:
					{
						switch ( radItkImage->getComponentLayoutType())
						{
							case SoItkDataImage::LUMINANCE:
							{
								CREATE_RAD_IMAGE( unsigned char, UNSIGNED_BYTE, LUMINANCE, 2, 1 );
							}
							break ;
							case SoItkDataImage::RGB:
							{
								CREATE_RAD_IMAGE( itk::RGBPixel<unsigned char>, UNSIGNED_BYTE, RGB, 2, 3 );
							}
							break ;
							case SoItkDataImage::RGBA:
							{
								CREATE_RAD_IMAGE( itk::RGBAPixel<unsigned char>, UNSIGNED_BYTE, RGBA, 2, 4 );
							}
							break ;						
						}
					}
					break ;
					case SoItkDataImage::SHORT:
					{
						switch ( radItkImage->getComponentLayoutType())
						{
							case SoItkDataImage::LUMINANCE:
							{
								CREATE_RAD_IMAGE( short, SHORT, LUMINANCE, 2, 1 );
							}
							break ;
							case SoItkDataImage::RGB:
							{
								CREATE_RAD_IMAGE( itk::RGBPixel<short>, SHORT, RGB, 2, 3 );
							}
							break ;
							case SoItkDataImage::RGBA:
							{
								CREATE_RAD_IMAGE( itk::RGBAPixel<short>, SHORT, RGBA, 2, 4 );
							}
							break ;						
						}
					}
					break ;
				}
			}
			break;
			case 3: 
			{
				switch( radItkImage->getType() )
				{
					case SoItkDataImage::UNSIGNED_SHORT:
					{
						switch ( radItkImage->getComponentLayoutType())
						{
							case SoItkDataImage::LUMINANCE:
							{
								 CREATE_RAD_IMAGE( unsigned short, UNSIGNED_SHORT, LUMINANCE, 3, 1 );
							}
							break ;
							case SoItkDataImage::RGB:
							{
								CREATE_RAD_IMAGE( itk::RGBPixel<unsigned short>, UNSIGNED_SHORT, RGB, 3, 3 );
							}
							break ;
							case SoItkDataImage::RGBA:
							{
								CREATE_RAD_IMAGE( itk::RGBAPixel<unsigned short>, UNSIGNED_SHORT, RGBA, 3, 4 );
							}
							break ;						
						}
					}
					break ;
					case SoItkDataImage::FLOAT:
					{
						switch ( radItkImage->getComponentLayoutType())
						{
							case SoItkDataImage::LUMINANCE:
							{
								CREATE_RAD_IMAGE( float, FLOAT, LUMINANCE, 3, 1 );
							}
							break ;
							case SoItkDataImage::RGB:
							{
								CREATE_RAD_IMAGE( itk::RGBPixel<float>, FLOAT, RGB, 3, 3 );
							}
							break ;
							case SoItkDataImage::RGBA:
							{
								CREATE_RAD_IMAGE( itk::RGBAPixel<float>, FLOAT, RGBA, 3, 4 );
							}
							break ;						
						}
					}
					break ;
					case SoItkDataImage::UNSIGNED_CHAR:
					{
						switch ( radItkImage->getComponentLayoutType())
						{
							case SoItkDataImage::LUMINANCE:
							{
								CREATE_RAD_IMAGE( unsigned char, UNSIGNED_BYTE, LUMINANCE, 3, 1 );
							}
							break ;
							case SoItkDataImage::RGB:
							{
								CREATE_RAD_IMAGE( itk::RGBPixel<unsigned char>, UNSIGNED_BYTE, RGB, 3, 3 );
							}
							break ;
							case SoItkDataImage::RGBA:
							{
								CREATE_RAD_IMAGE( itk::RGBAPixel<unsigned char>, UNSIGNED_BYTE, RGBA, 3, 4 );
							}
							break ;						
						}
					}
					break ;
					case SoItkDataImage::SHORT:
					{
						switch ( radItkImage->getComponentLayoutType())
						{
							case SoItkDataImage::LUMINANCE:
							{
								CREATE_RAD_IMAGE( short, SHORT, LUMINANCE, 3, 1 );
							}
							break ;
							case SoItkDataImage::RGB:
							{
								CREATE_RAD_IMAGE( itk::RGBPixel<short>, SHORT, RGB, 3, 3 );
							}
							break ;
							case SoItkDataImage::RGBA:
							{
								CREATE_RAD_IMAGE( itk::RGBAPixel<short>, SHORT, RGBA, 3, 4 );
							}
							break ;						
						}
					}
					break ;
				}
			}
			break;
		}
#undef CREATE_RAD_IMAGE
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

	SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue( mXipImage ) );
}

SoField* 
SoItkConvertItkImageToXipImage::getInput( SoType type )
{
	if( type == SoItkSFDataImage::getClassTypeId() )
	{
		return &input;
	}

	SoDebugError::post( __FILE__, "SoItkConvertItkImageToXipImage::getOutput() : unresolved input" );
	return 0;
}

SoEngineOutput* 
SoItkConvertItkImageToXipImage::getOutput( SoType type )
{
	if( type == SoXipSFDataImage::getClassTypeId() )
	{
		return &output;
	}

	SoDebugError::post( __FILE__, "SoItkConvertItkImageToXipImage::getOutput() : unresolved output" );
	return 0;
}

