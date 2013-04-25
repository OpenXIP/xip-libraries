/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
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

#include <itkStatisticsImageFilter.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkStatisticsImageFilter.h"

SO_ENGINE_SOURCE( SoItkStatisticsImageFilter );

SoItkStatisticsImageFilter::SoItkStatisticsImageFilter()
{
	SO_ENGINE_CONSTRUCTOR( SoItkStatisticsImageFilter );
	
	// Outputs
	SO_ENGINE_ADD_OUTPUT( Sum, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( Maximum, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( Mean, SoSFFloat );
	mMaximumOutput = 0;
	SO_ENGINE_ADD_OUTPUT( MaximumOutput, SoItkSFDataDecorator );
	mSumOutput = 0;
	SO_ENGINE_ADD_OUTPUT( SumOutput, SoItkSFDataDecorator );
	SO_ENGINE_ADD_OUTPUT( Variance, SoSFFloat );
	mMeanOutput = 0;
	SO_ENGINE_ADD_OUTPUT( MeanOutput, SoItkSFDataDecorator );
	mVarianceOutput = 0;
	SO_ENGINE_ADD_OUTPUT( VarianceOutput, SoItkSFDataDecorator );
	mMinimumOutput = 0;
	SO_ENGINE_ADD_OUTPUT( MinimumOutput, SoItkSFDataDecorator );
	mSigmaOutput = 0;
	SO_ENGINE_ADD_OUTPUT( SigmaOutput, SoItkSFDataDecorator );
	SO_ENGINE_ADD_OUTPUT( Sigma, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( Minimum, SoSFFloat );
}

SoItkStatisticsImageFilter::~SoItkStatisticsImageFilter()
{
	if( mMaximumOutput )
		mMaximumOutput->unref();
	mMaximumOutput = 0;
	if( mSumOutput )
		mSumOutput->unref();
	mSumOutput = 0;
	if( mMeanOutput )
		mMeanOutput->unref();
	mMeanOutput = 0;
	if( mVarianceOutput )
		mVarianceOutput->unref();
	mVarianceOutput = 0;
	if( mMinimumOutput )
		mMinimumOutput->unref();
	mMinimumOutput = 0;
	if( mSigmaOutput )
		mSigmaOutput->unref();
	mSigmaOutput = 0;
}

void
SoItkStatisticsImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkStatisticsImageFilter, SoItkImageToImageFilter, "SoItkImageToImageFilter" );
}

bool
SoItkStatisticsImageFilter::checkInput()
{
	switch( Input0.getValue()->getType() )
	{
		case SoItkDataImage::FLOAT:
		{
			switch( Input0.getValue()->getNumDimension() )
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
			switch( Input0.getValue()->getNumDimension() )
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
SoItkStatisticsImageFilter::evaluate()
{
	if( mMaximumOutput )
	{
		mMaximumOutput->unref();
		mMaximumOutput = 0;
		SO_ENGINE_OUTPUT( MaximumOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mSumOutput )
	{
		mSumOutput->unref();
		mSumOutput = 0;
		SO_ENGINE_OUTPUT( SumOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mMeanOutput )
	{
		mMeanOutput->unref();
		mMeanOutput = 0;
		SO_ENGINE_OUTPUT( MeanOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mVarianceOutput )
	{
		mVarianceOutput->unref();
		mVarianceOutput = 0;
		SO_ENGINE_OUTPUT( VarianceOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mMinimumOutput )
	{
		mMinimumOutput->unref();
		mMinimumOutput = 0;
		SO_ENGINE_OUTPUT( MinimumOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mSigmaOutput )
	{
		mSigmaOutput->unref();
		mSigmaOutput = 0;
		SO_ENGINE_OUTPUT( SigmaOutput, SoItkSFDataDecorator, setValue( 0 ) );
	}
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
		SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( 0 ) );
	}

	if( !Input0.getValue() )
		return ;
	
	if( !checkInput() )
	{
		SoDebugError::post( __FILE__, "Invalid Input Types" );
		return ;
	}

	try
	{
		switch( Input0.getValue()->getType() )
		{
			case SoItkDataImage::FLOAT:
			{
				switch( Input0.getValue()->getNumDimension() )
				{
					case 2:
					{
						typedef itk::Image< float, 2 > OutputImageType;
						typedef itk::StatisticsImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< float, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Sum, SoSFFloat, setValue( filter->GetSum() ) ); 
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						SO_ENGINE_OUTPUT( Mean, SoSFFloat, setValue( filter->GetMean() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetSumOutput()->Register();
						mSumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mSumOutput->ref();
						mSumOutput->setPointer( filter->GetSumOutput() );
						SO_ENGINE_OUTPUT( Variance, SoSFFloat, setValue( filter->GetVariance() ) ); 
						filter->GetMeanOutput()->Register();
						mMeanOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMeanOutput->ref();
						mMeanOutput->setPointer( filter->GetMeanOutput() );
						filter->GetVarianceOutput()->Register();
						mVarianceOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mVarianceOutput->ref();
						mVarianceOutput->setPointer( filter->GetVarianceOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
						filter->GetSigmaOutput()->Register();
						mSigmaOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mSigmaOutput->ref();
						mSigmaOutput->setPointer( filter->GetSigmaOutput() );
						SO_ENGINE_OUTPUT( Sigma, SoSFFloat, setValue( filter->GetSigma() ) ); 
						SO_ENGINE_OUTPUT( Minimum, SoSFFloat, setValue( filter->GetMinimum() ) ); 
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 2,
							Input0.getValue()->getModelMatrix() );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
					case 3:
					{
						typedef itk::Image< float, 3 > OutputImageType;
						typedef itk::StatisticsImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< float, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Sum, SoSFFloat, setValue( filter->GetSum() ) ); 
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						SO_ENGINE_OUTPUT( Mean, SoSFFloat, setValue( filter->GetMean() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetSumOutput()->Register();
						mSumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mSumOutput->ref();
						mSumOutput->setPointer( filter->GetSumOutput() );
						SO_ENGINE_OUTPUT( Variance, SoSFFloat, setValue( filter->GetVariance() ) ); 
						filter->GetMeanOutput()->Register();
						mMeanOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMeanOutput->ref();
						mMeanOutput->setPointer( filter->GetMeanOutput() );
						filter->GetVarianceOutput()->Register();
						mVarianceOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mVarianceOutput->ref();
						mVarianceOutput->setPointer( filter->GetVarianceOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
						filter->GetSigmaOutput()->Register();
						mSigmaOutput = new SoItkDataDecorator( SoItkDataDecorator::FLOAT );
						mSigmaOutput->ref();
						mSigmaOutput->setPointer( filter->GetSigmaOutput() );
						SO_ENGINE_OUTPUT( Sigma, SoSFFloat, setValue( filter->GetSigma() ) ); 
						SO_ENGINE_OUTPUT( Minimum, SoSFFloat, setValue( filter->GetMinimum() ) ); 
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::FLOAT, 3,
							Input0.getValue()->getModelMatrix() );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
				}
			}
			break ;
			case SoItkDataImage::UNSIGNED_SHORT:
			{
				switch( Input0.getValue()->getNumDimension() )
				{
					case 2:
					{
						typedef itk::Image< unsigned short, 2 > OutputImageType;
						typedef itk::StatisticsImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< unsigned short, 2 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Sum, SoSFFloat, setValue( filter->GetSum() ) ); 
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						SO_ENGINE_OUTPUT( Mean, SoSFFloat, setValue( filter->GetMean() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetSumOutput()->Register();
						mSumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mSumOutput->ref();
						mSumOutput->setPointer( filter->GetSumOutput() );
						SO_ENGINE_OUTPUT( Variance, SoSFFloat, setValue( filter->GetVariance() ) ); 
						filter->GetMeanOutput()->Register();
						mMeanOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMeanOutput->ref();
						mMeanOutput->setPointer( filter->GetMeanOutput() );
						filter->GetVarianceOutput()->Register();
						mVarianceOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mVarianceOutput->ref();
						mVarianceOutput->setPointer( filter->GetVarianceOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
						filter->GetSigmaOutput()->Register();
						mSigmaOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mSigmaOutput->ref();
						mSigmaOutput->setPointer( filter->GetSigmaOutput() );
						SO_ENGINE_OUTPUT( Sigma, SoSFFloat, setValue( filter->GetSigma() ) ); 
						SO_ENGINE_OUTPUT( Minimum, SoSFFloat, setValue( filter->GetMinimum() ) ); 
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 2,
							Input0.getValue()->getModelMatrix() );
						mOutput->ref();
						mOutput->setPointer( filter->GetOutput() );
					}
					break ;
					case 3:
					{
						typedef itk::Image< unsigned short, 3 > OutputImageType;
						typedef itk::StatisticsImageFilter< OutputImageType > FilterType;
						
						FilterType::Pointer filter = FilterType::New();
						
						// Set the filter's inputs
						
						// Inherited from SoItkImageToImageFilter
						typedef itk::Image< unsigned short, 3 > InputImageType;
						SO_ITK_SET_FIELD_MDATA( filter, Input, 0, InputImageType );
						
						
						
						// Start processing the ouputs
						filter->Update();
						
						// Retrieve the filter's outputs
						SO_ENGINE_OUTPUT( Sum, SoSFFloat, setValue( filter->GetSum() ) ); 
						SO_ENGINE_OUTPUT( Maximum, SoSFFloat, setValue( filter->GetMaximum() ) ); 
						SO_ENGINE_OUTPUT( Mean, SoSFFloat, setValue( filter->GetMean() ) ); 
						filter->GetMaximumOutput()->Register();
						mMaximumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMaximumOutput->ref();
						mMaximumOutput->setPointer( filter->GetMaximumOutput() );
						filter->GetSumOutput()->Register();
						mSumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mSumOutput->ref();
						mSumOutput->setPointer( filter->GetSumOutput() );
						SO_ENGINE_OUTPUT( Variance, SoSFFloat, setValue( filter->GetVariance() ) ); 
						filter->GetMeanOutput()->Register();
						mMeanOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMeanOutput->ref();
						mMeanOutput->setPointer( filter->GetMeanOutput() );
						filter->GetVarianceOutput()->Register();
						mVarianceOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mVarianceOutput->ref();
						mVarianceOutput->setPointer( filter->GetVarianceOutput() );
						filter->GetMinimumOutput()->Register();
						mMinimumOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mMinimumOutput->ref();
						mMinimumOutput->setPointer( filter->GetMinimumOutput() );
						filter->GetSigmaOutput()->Register();
						mSigmaOutput = new SoItkDataDecorator( SoItkDataDecorator::UNSIGNED_SHORT );
						mSigmaOutput->ref();
						mSigmaOutput->setPointer( filter->GetSigmaOutput() );
						SO_ENGINE_OUTPUT( Sigma, SoSFFloat, setValue( filter->GetSigma() ) ); 
						SO_ENGINE_OUTPUT( Minimum, SoSFFloat, setValue( filter->GetMinimum() ) ); 
						filter->GetOutput()->Register();
						mOutput = new SoItkDataImage( SoItkDataImage::UNSIGNED_SHORT, 3,
							Input0.getValue()->getModelMatrix() );
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

	SO_ENGINE_OUTPUT( MaximumOutput, SoItkSFDataDecorator, setValue( mMaximumOutput ) );
	SO_ENGINE_OUTPUT( SumOutput, SoItkSFDataDecorator, setValue( mSumOutput ) );
	SO_ENGINE_OUTPUT( MeanOutput, SoItkSFDataDecorator, setValue( mMeanOutput ) );
	SO_ENGINE_OUTPUT( VarianceOutput, SoItkSFDataDecorator, setValue( mVarianceOutput ) );
	SO_ENGINE_OUTPUT( MinimumOutput, SoItkSFDataDecorator, setValue( mMinimumOutput ) );
	SO_ENGINE_OUTPUT( SigmaOutput, SoItkSFDataDecorator, setValue( mSigmaOutput ) );
	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( mOutput ) );
}
