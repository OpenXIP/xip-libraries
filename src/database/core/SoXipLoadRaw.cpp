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

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SbXipImageFile.h>
#include <Inventor/errors/SoMemoryError.h>
#include "SoXipLoadRaw.h"
#include <xip/inventor/core/SbXipDirtyFieldList.h>

SO_ENGINE_SOURCE( SoXipLoadRaw );

SoXipLoadRaw::SoXipLoadRaw()
{
	SO_ENGINE_CONSTRUCTOR( SoXipLoadRaw );

	SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, UBYTE );
	SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, USHORT );
    SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, SHORT );
	 SO_ENGINE_DEFINE_ENUM_VALUE( VoxelType, FLOAT32 );
	SO_ENGINE_SET_SF_ENUM_TYPE( voxelType, VoxelType );

	SO_ENGINE_ADD_INPUT( voxelType, (UBYTE) );
	SO_ENGINE_ADD_INPUT( width, (0 ));
	SO_ENGINE_ADD_INPUT( height, (0) );
	SO_ENGINE_ADD_INPUT( depth, (0) );
	SO_ENGINE_ADD_INPUT( bitsUsed, (8) );
	SO_ENGINE_ADD_INPUT( modelMatrix, (SbMatrix::identity()) );
	SO_ENGINE_ADD_INPUT( file, ("") );

	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage);

	mDataOutput = 0;
}

SoXipLoadRaw::~SoXipLoadRaw()
{
	SbXipDirtyFieldList::remove( &file );

	if( mDataOutput )
	{
		mDataOutput->unref();
		mDataOutput = 0;
	}
}

void 
SoXipLoadRaw::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipLoadRaw, SoEngine, "Engine" );
}

void
SoXipLoadRaw::evaluate()
{
	// Reset the previous outputs
	if( mDataOutput )
	{
		mDataOutput->unref();
		mDataOutput = 0;
		SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(0) );
	}

    SbXipImage* img = 0;
    try
    {
	    if( (width.getValue() > 0) &&
		    (height.getValue() > 0) &&
		    (depth.getValue() > 0) &&
		    (bitsUsed.getValue() > 0) &&
		    (file.getValue().getLength() > 0) )
	    {
            int voxelStorageType = voxelType.getValue();

            SbXipImage::DataType xipDataType;
            switch (voxelStorageType)
            {
            case UBYTE:
                xipDataType = SbXipImage::UNSIGNED_BYTE;
                break;
            case USHORT:
                xipDataType = SbXipImage::UNSIGNED_SHORT;
                break;
            case SHORT:
                xipDataType = SbXipImage::SHORT;
                break;
				case FLOAT32:
					xipDataType = SbXipImage::FLOAT;
                break;
            default:
				SoError::post( "Unsupported image type" );
				goto error;
            }

		    img = new SbXipImage(
			    SbXipImageDimensions( width.getValue(), height.getValue(), depth.getValue() ),
			    xipDataType,
			    bitsUsed.getValue(), 1, SbXipImage::SEPARATE, SbXipImage::LUMINANCE,
				modelMatrix.getValue() );

            if( !img )
            {
				SoMemoryError::post( "Error allocating image" );
				goto error;
            }

		    if( !readImage( file.getValue().getString(), 0, *img ) )
		    {
                SoError::post( "Reading raw image data from \"%s\" failed!", file.getValue().getString() );
				goto error;
			}
		    
			mDataOutput = new SoXipDataImage;
            if( !mDataOutput )
			{
				SoMemoryError::post( "Error allocating data image" );
				goto error;
			}

			mDataOutput->ref();
			mDataOutput->set( img );

			// Update output
			SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue( mDataOutput ) );
	    }
    }
	catch(...)
	{
		SoError::post( "Unknown exception: loading raw data from \"%s\" failed!",
			file.getValue().getString() );
		goto error;
	}

	return ;

// Error handling
error:
	if( mDataOutput )
	{
		mDataOutput->unref();
		mDataOutput = 0;
	}
	if( img )
	{
		delete img;
        img = 0;
	}
}

SbBool
SoXipLoadRaw::readInstance( SoInput* in, unsigned short flags )
{
	#if defined(COIN_DLL) || defined (COIN_NO_DLL)
	// SGI automatically triggers evaluate after loading but COIN doesn't
	SbXipDirtyFieldList::append(&file);
	#endif

	return SoEngine::readInstance( in, flags );
}