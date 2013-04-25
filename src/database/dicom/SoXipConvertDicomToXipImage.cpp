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

#include <Inventor/SoDB.h>
#include <Inventor/errors/SoErrors.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>

#include "SoXipConvertDicomToXipImage.h"


//////////////////////////////////////////////////////////////////////
// SoXipConvertMFDicomToMFImage
//////////////////////////////////////////////////////////////////////


SO_ENGINE_SOURCE(SoXipConvertMFDicomToMFImage);

void SoXipConvertMFDicomToMFImage::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertMFDicomToMFImage,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoXipMFDataDicom::getClassTypeId(),
                      SoXipMFDataImage::getClassTypeId(),
                      getClassTypeId());
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoXipConvertMFDicomToMFImage::SoXipConvertMFDicomToMFImage()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertMFDicomToMFImage);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));
   input.setNum(0);

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoXipMFDataImage);
}

SoXipConvertMFDicomToMFImage::~SoXipConvertMFDicomToMFImage()
{

}

// This is the evaluation routine.
void SoXipConvertMFDicomToMFImage::evaluate()
{
	// Remove previous data
	mData.setNum(0);

	// Reset output
	SO_ENGINE_OUTPUT( output, SoXipMFDataImage, setNum(0) );

	int size = input.getNum();
	for( int i = 0; i < size; ++ i )
	{
		SoXipDataDicom* in = input[i];
		if( !in )
			continue ;

		// convert dicom data to xip image
		SbXipImage* image = new SbXipImage();
		if( !image )
		{
			SoMemoryError::post( "SbXipImage" );
			continue ;
		}

		// error is already posted by getPixelData when returning FALSE
		if( !in->getPixelData( *image ) )
			continue ;

		// create instance of SoXipDataImage
		SoXipDataImage* dataImage = new SoXipDataImage();
		dataImage->set( image );

		// Add a reference to the original dicom image
		dataImage->addRef( in );

		mData.set1Value( mData.getNum(), dataImage );
	}

	SO_ENGINE_OUTPUT( output, SoXipMFDataImage, copyFrom( mData ) );
}

// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.

SoField *SoXipConvertMFDicomToMFImage::getInput(SoType)
{
   return &input;
}

// This does the same for the output.

SoEngineOutput *SoXipConvertMFDicomToMFImage::getOutput(SoType)
{
   return &output;
}


//////////////////////////////////////////////////////////////////////
// SoXipConvertMFDicomToSFImage
//////////////////////////////////////////////////////////////////////


SO_ENGINE_SOURCE(SoXipConvertMFDicomToSFImage);


void SoXipConvertMFDicomToSFImage::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertMFDicomToSFImage,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoXipMFDataDicom::getClassTypeId(),
                      SoXipSFDataImage::getClassTypeId(),
                      getClassTypeId());
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SoXipConvertMFDicomToSFImage::SoXipConvertMFDicomToSFImage()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertMFDicomToXipImage);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoXipSFDataImage);

   mOutputImage = 0;
}

SoXipConvertMFDicomToSFImage::~SoXipConvertMFDicomToSFImage()
{
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}
}

// This is the evaluation routine.
void SoXipConvertMFDicomToSFImage::evaluate()
{
	// set output to NULL
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(0));

	// clear existing data
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}

	int numSlices = input.getNum();

	// if input size is zero or the slice number is not within the number of slices, return
	if (numSlices == 0)
		return;

	SoXipDataDicom* in = input[0];
	if (!in)
		return;

	// convert dicom data to xip image
	SbXipImage *img = new SbXipImage();
	if (!img)
	{
		SoMemoryError::post("SbXipImage");
		return;
	}

	// error is already posted by getPixelData when returning FALSE
	if (!in->getPixelData(*img))
		return;

	// create instance of SoXipDataImage
	mOutputImage = new SoXipDataImage();
	mOutputImage->ref();
	mOutputImage->set(img);

	// Add a reference to the original dicom image
	mOutputImage->addRef( in );

	// update output
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(mOutputImage));
}

// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.
SoField *SoXipConvertMFDicomToSFImage::getInput(SoType)
{
   return &input;
}

// This does the same for the output.
SoEngineOutput *SoXipConvertMFDicomToSFImage::getOutput(SoType)
{
   return &output;
}


//////////////////////////////////////////////////////////////////////
// SoXipConvertSFDicomToSFImage
//////////////////////////////////////////////////////////////////////

SO_ENGINE_SOURCE(SoXipConvertSFDicomToSFImage);


void SoXipConvertSFDicomToSFImage::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertSFDicomToSFImage,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoXipSFDataDicom::getClassTypeId(),
                      SoXipSFDataImage::getClassTypeId(),
                      getClassTypeId());
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SoXipConvertSFDicomToSFImage::SoXipConvertSFDicomToSFImage()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertSFDicomToSFImage);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoXipSFDataImage);

   mOutputImage = 0;
}


SoXipConvertSFDicomToSFImage::~SoXipConvertSFDicomToSFImage()
{
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}
}


// This is the evaluation routine.
void SoXipConvertSFDicomToSFImage::evaluate()
{
	// set output to NULL
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(0));

	// clear existing data
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}

	SoXipDataDicom *in = input.getValue();
	if (!in)
		return;

	// convert dicom data to xip image
	SbXipImage *img = new SbXipImage();
	if (!img)
	{
		SoMemoryError::post("SbXipImage");
		return;
	}

	// error is already posted by getPixelData when returning FALSE
	if (!in->getPixelData(*img))
		return;

	// create instance of SoXipDataImage
	mOutputImage = new SoXipDataImage();
	mOutputImage->ref();
	mOutputImage->set(img);

	// Add a reference to the original dicom image
	mOutputImage->addRef( in );

	SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(mOutputImage) );
}


// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.
SoField *SoXipConvertSFDicomToSFImage::getInput(SoType)
{
   return &input;
}


// This does the same for the output.
SoEngineOutput *SoXipConvertSFDicomToSFImage::getOutput(SoType)
{
   return &output;
}
