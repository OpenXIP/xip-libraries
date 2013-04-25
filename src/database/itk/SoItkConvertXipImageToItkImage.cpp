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

#include <itkImportImageFilter.h>
#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>
#include <Inventor/SoDB.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include "SoItkConvertXipImageToItkImage.h"

SO_ENGINE_SOURCE( SoItkConvertXipImageToItkImage );

SoItkConvertXipImageToItkImage::SoItkConvertXipImageToItkImage()
{
	SO_ENGINE_CONSTRUCTOR( SoItkConvertXipImageToItkImage );

	// Inputs
	SO_ENGINE_ADD_INPUT( input, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( output, SoItkSFDataImage );

	mItkImage = 0;
}

void 
SoItkConvertXipImageToItkImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkConvertXipImageToItkImage, SoFieldConverter, "SoFieldConverter" );

	SoDB::addConverter( SoXipSFDataImage::getClassTypeId(),
		SoItkSFDataImage::getClassTypeId(),
		getClassTypeId() );
}

SoItkConvertXipImageToItkImage::~SoItkConvertXipImageToItkImage()
{
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
	}
}

void
SoItkConvertXipImageToItkImage::evaluate()
{	
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
		SO_ENGINE_OUTPUT( output, SoItkSFDataImage, setValue(0) );
	}

	SoXipDataImage* radImage = input.getValue();
	if( !radImage )
		return ;

    SbXipImage* inputImage = radImage->get();
	if( inputImage->getType() != SbXipImage::UNSIGNED_SHORT &&
		inputImage->getType() != SbXipImage::FLOAT &&
		inputImage->getType() != SbXipImage::SHORT &&
		inputImage->getType() != SbXipImage::UNSIGNED_BYTE )
	{
		SoDebugError::post( __FILE__, "Itk image only supports UNSIGNED_SHORT, SHORT, UNSIGNED_BYTE or FLOAT" );
		return ;
	}

	try
	{
		SbXipImage* inputImage = radImage->get();
		SbXipImageDimensions dimensions = inputImage->getDimStored();

		unsigned int imageDimension = 2;
		if( dimensions[2] > 1 )
			++ imageDimension;

		if( inputImage->getComponentLayoutType() != SbXipImage::LUMINANCE && 
			inputImage->getComponentLayoutType() != SbXipImage::RGB && 
			inputImage->getComponentLayoutType() != SbXipImage::RGBA )
		{
			SoDebugError::post( __FILE__, "Image format not supported yet" );
			SoDebugError::post( __FILE__, "Rad To Itk only works with LUMINANCE, RGB and RGBA" );
			return ;
		}

		#define CREATE_RADITK_IMAGE( Type, TypeFlag, ComponentLayoutFlag, Dimension )	\
		{																				\
			Type* pixelBuffer = (Type *) inputImage->refBufferPtr();					\
																						\
			typedef itk::ImportImageFilter< Type, Dimension > ImportFilterType;			\
																						\
			ImportFilterType::SizeType size;											\
			ImportFilterType::IndexType start;											\
			double origin[ Dimension ];													\
			double spacing[ Dimension ];												\
																						\
			for( unsigned int d = 0; d < Dimension; ++ d )								\
			{												                            \
				size[d]    = dimensions[d];												\
				start[d]   = 0;															\
				origin[d]  = 0;															\
				spacing[d] = 1;															\
			}																			\
																						\
			ImportFilterType::RegionType region;										\
			region.SetIndex( start );													\
			region.SetSize( size );														\
																						\
			ImportFilterType::Pointer importFilter = ImportFilterType::New();			\
			importFilter->SetRegion( region );											\
			importFilter->SetOrigin( origin );											\
			importFilter->SetSpacing( spacing );										\
			importFilter->SetImportPointer(	pixelBuffer, size[0] * size[1], false );	\
			importFilter->Update();														\
																						\
			/* Since Itk objects are reference-counted, we need to manually   */		\
			/* increment the reference count of the resulting image, to avoid */		\
			/* the importFilter instance to destroy it.                       */		\
			/*                                                                */		\
			importFilter->GetOutput()->Register();										\
																						\
			mItkImage = new SoItkDataImage( TypeFlag, ComponentLayoutFlag, Dimension,	\
				inputImage->getModelMatrix() );											\
			mItkImage->ref();															\
			mItkImage->addRef( radImage );												\
			mItkImage->setPointer( importFilter->GetOutput() );							\
		}

		switch( imageDimension )
		{
			case 2:
			{
				switch( inputImage->getType() )                                      
				{
					case SbXipImage::UNSIGNED_SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned short, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::FLOAT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( float, SoItkDataImage::FLOAT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( short, SoItkDataImage::SHORT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::UNSIGNED_BYTE:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned char, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
				}
			}
			break;
			case 3:
			{
				switch( inputImage->getType() )                                      
				{
					case SbXipImage::UNSIGNED_SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned short, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::FLOAT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( float, SoItkDataImage::FLOAT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( short, SoItkDataImage::SHORT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::UNSIGNED_BYTE:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned char, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
				}
			}
			break;
		}
#undef CREATE_RADITK_IMAGE
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
SoItkConvertXipImageToItkImage::getInput( SoType type )
{
	if( type == SoXipSFDataImage::getClassTypeId() )
	{
		return &input;
	}

	SoDebugError::post( __FILE__, "SoItkConvertXipImageToItkImage::getOutput() : unresolved input" );
	return 0;
}

SoEngineOutput* 
SoItkConvertXipImageToItkImage::getOutput( SoType type )
{
	if( type == SoItkSFDataImage::getClassTypeId() )
	{
		return &output;
	}

	SoDebugError::post( __FILE__, "SoItkConvertXipImageToItkImage::getOutput() : unresolved output" );
	return 0;
}