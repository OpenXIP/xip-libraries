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

#include <itkFastMarchingImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkFastMarchingImageFilter.h"

SO_ENGINE_SOURCE( SoItkFastMarchingImageFilter );

SoItkFastMarchingImageFilter::SoItkFastMarchingImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkFastMarchingImageFilter );
	
    // Enumerations
	SO_ENGINE_DEFINE_ENUM_VALUE( OutputPixelTypeEnum, FLOAT );
	SO_ENGINE_DEFINE_ENUM_VALUE( OutputPixelTypeEnum, UNSIGNED_SHORT );

	// Define input fields and their default values
	SO_ENGINE_SET_SF_ENUM_TYPE( OutputPixelType, OutputPixelTypeEnum );

	// Inputs
	SO_ENGINE_ADD_INPUT( OutputPixelType, (FLOAT) );
	SO_ENGINE_ADD_INPUT( Dimension, (2) );
	SO_ENGINE_ADD_INPUT( ModelMatrix, (1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ) );
	SO_ENGINE_ADD_INPUT( NormalizationFactor, (1.0) );
	SO_ENGINE_ADD_INPUT( OutputRegion, (0) );
	OutputRegion.setNum(0);
	SO_ENGINE_ADD_INPUT( OutputSpacing, (1.0) );
	SO_ENGINE_ADD_INPUT( OutputOrigin, (0) );
	OutputOrigin.setNum(0);
	SO_ENGINE_ADD_INPUT( CollectPoints, (false) );
	SO_ENGINE_ADD_INPUT( TrialPoints, () );
	SO_ENGINE_ADD_INPUT( AlivePoints, () );
	SO_ENGINE_ADD_INPUT( OverrideOutputInformation, (false) );
	SO_ENGINE_ADD_INPUT( OutputSize, (0) );
	OutputSize.setNum(0);
	SO_ENGINE_ADD_INPUT( StoppingValue, (0) );
	SO_ENGINE_ADD_INPUT( SpeedConstant, (1.0) );
}

SoItkFastMarchingImageFilter::~SoItkFastMarchingImageFilter()
{

}

void
SoItkFastMarchingImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkFastMarchingImageFilter, SoItkImageToImageFilter, "SoItkImageToImageFilter" );
}

bool
SoItkFastMarchingImageFilter::checkInput()
{
	SoItkDataImage::DataType typeIn;
	unsigned int dimension;

	if( Input0.getValue() )
	{
		typeIn = Input0.getValue()->getType();
		dimension = Input0.getValue()->getNumDimension();
	}
	else
	{
		switch( OutputPixelType.getValue() )
		{
		case FLOAT: typeIn = SoItkDataImage::FLOAT; break ;
		case UNSIGNED_SHORT: typeIn = SoItkDataImage::UNSIGNED_SHORT; break ;
		}
		dimension = Dimension.getValue();
	}

	switch( typeIn )
	{
		case SoItkDataImage::FLOAT:
		{
			switch( dimension )
			{
				case 2:
				{
					return true;
				}
				break ;
				case 3:
				{
					return true;
				}
				break ;
			}
		}
		break ;
		case SoItkDataImage::UNSIGNED_SHORT:
		{
			switch( dimension )
			{
				case 2:
				{
					return true;
				}
				break ;
				case 3:
				{
					return true;
				}
				break ;
			}
		}
		break ;
	}
	
	return false;
}

void
SoItkFastMarchingImageFilter::evaluate()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
		SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( 0 ) );
	}
	
	if( !checkInput() )
	{
		SoDebugError::post( __FILE__, "Invalid Input Types" );
		return ;
	}

	try
	{
		SoItkDataImage::DataType typeIn;
		unsigned int dimension;
		SbMatrix modelMatrix;

		if( Input0.getValue() )
		{
			typeIn = Input0.getValue()->getType();
			dimension = Input0.getValue()->getNumDimension();
			modelMatrix = Input0.getValue()->getModelMatrix();
		}
		else
		{
			switch( OutputPixelType.getValue() )
			{
			case FLOAT: typeIn = SoItkDataImage::FLOAT; break ;
			case UNSIGNED_SHORT: typeIn = SoItkDataImage::UNSIGNED_SHORT; break ;
			}
			dimension = Dimension.getValue();
			modelMatrix = ModelMatrix.getValue();
		}

		switch( typeIn )
		{
			case SoItkDataImage::FLOAT:
			{
				switch( dimension )
				{
					case 2:
					{
						typedef itk::Image< float, 2 > InputImageType;
						typedef itk::Image< float, 2 > OutputImageType;
						typedef itk::FastMarchingImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, NormalizationFactor );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, OutputRegion, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, OutputSpacing );

						SO_ITK_SET_FIELD_POINT( filter, OutputOrigin, double, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, CollectPoints );

						//SO_ITK_SET_FIELD_NODE_CONTAINER( filter, TrialPoints, float, 2 );
						SbItkNodeContainer nodes = TrialPoints.getValue();
						if( nodes.getNumElements() )
						{
							typedef itk::LevelSetNode< float, 2 > NodeType;
							typedef itk::VectorContainer< unsigned int, NodeType > NodeContainerType;
							
							NodeContainerType::Pointer nc = NodeContainerType::New();
							nc->Register();
							nc->Initialize();
							
							for( unsigned int s = 0; s < nodes.getNumElements(); ++ s )
							{
								SbVec3f v = nodes.getSeed( s );
								modelMatrix.inverse().multVecMatrix( v, v );
								
								itk::Index< 2 > SeedIndex;
								for( unsigned int i = 0; i < dimension; ++ i )
									SeedIndex.m_Index[i] = v[i] * OutputSize[i];

								NodeType node;
								node.SetValue( nodes.getLabel( s ) );
								node.SetIndex( SeedIndex );
								
								nc->InsertElement( s, node );
							}
							filter->SetTrialPoints( nc );
						}
						
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, AlivePoints, float, 2 );

						SO_ITK_SET_FIELD_VALUE( filter, OverrideOutputInformation );
						SO_ITK_SET_FIELD_SIZE( filter, OutputSize, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, StoppingValue );
						SO_ITK_SET_FIELD_VALUE( filter, SpeedConstant );
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< float, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
												
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 2, modelMatrix  );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
					case 3:
					{
						typedef itk::Image< float, 3 > InputImageType;
						typedef itk::Image< float, 3 > OutputImageType;
						typedef itk::FastMarchingImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, NormalizationFactor );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, OutputRegion, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, OutputSpacing );
						SO_ITK_SET_FIELD_POINT( filter, OutputOrigin, double, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, CollectPoints );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, TrialPoints, float, 3 );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, AlivePoints, float, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, OverrideOutputInformation );
						SO_ITK_SET_FIELD_SIZE( filter, OutputSize, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, StoppingValue );
						SO_ITK_SET_FIELD_VALUE( filter, SpeedConstant );
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< float, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 3, modelMatrix );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
				}
			}
			break ;
			case SoItkDataImage::UNSIGNED_SHORT:
			{
				switch( typeIn )
				{
					case 2:
					{
						typedef itk::Image< unsigned short, 2 > InputImageType;
						typedef itk::Image< unsigned short, 2 > OutputImageType;
						typedef itk::FastMarchingImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, NormalizationFactor );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, OutputRegion, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, OutputSpacing );
						SO_ITK_SET_FIELD_POINT( filter, OutputOrigin, double, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, CollectPoints );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, TrialPoints, unsigned short, 2 );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, AlivePoints, unsigned short, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, OverrideOutputInformation );
						SO_ITK_SET_FIELD_SIZE( filter, OutputSize, 2 );
						SO_ITK_SET_FIELD_VALUE( filter, StoppingValue );
						SO_ITK_SET_FIELD_VALUE( filter, SpeedConstant );
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< unsigned short, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 2, modelMatrix );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
					case 3:
					{
						typedef itk::Image< unsigned short, 3 > InputImageType;
						typedef itk::Image< unsigned short, 3 > OutputImageType;
						typedef itk::FastMarchingImageFilter< InputImageType, OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						SO_ITK_SET_FIELD_VALUE( filter, NormalizationFactor );
						SO_ITK_SET_FIELD_IMAGE_REGION( filter, OutputRegion, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, OutputSpacing );
						SO_ITK_SET_FIELD_POINT( filter, OutputOrigin, double, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, CollectPoints );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, TrialPoints, unsigned short, 3 );
						SO_ITK_SET_FIELD_NODE_CONTAINER( filter, AlivePoints, unsigned short, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, OverrideOutputInformation );
						SO_ITK_SET_FIELD_SIZE( filter, OutputSize, 3 );
						SO_ITK_SET_FIELD_VALUE( filter, StoppingValue );
						SO_ITK_SET_FIELD_VALUE( filter, SpeedConstant );
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< unsigned short, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 3, modelMatrix  );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
				}
			}
			break ;
		}
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), "line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}

	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( mOutput ) );
}
