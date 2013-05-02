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


#include <xip/system/standard.h>
#include "SoXipApplyLutToImage.h"
//#include "SoXipSFDataImageToSFImage.h"

#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoActions.h>
//#include <Inventor/SoPrimitiveVertex.h>
//#include <Inventor/elements/SoTextureCoordinateElement.h>
//#include <Inventor/nodes/SoMatrixTransform.h>

#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SbXipImageAdaptor.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <xip/inventor/core/SoXipDataImage.h>
//#include <xip/inventor/core/SoXipTexture.h>










SO_NODE_SOURCE( SoXipApplyLutToImage );


SoXipApplyLutToImage::SoXipApplyLutToImage()
{
	SO_NODE_CONSTRUCTOR( SoXipApplyLutToImage );

	SO_NODE_ADD_FIELD( image,  (NULL) );
	SO_NODE_ADD_FIELD( output, (NULL) );

	mCurrentImage = 0;
	mImageId = 0;
	mLutId = 0;

	mImageSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
	mImageSensor->setPriority(0);
	mImageSensor->attach(&image);
}

SoXipApplyLutToImage::~SoXipApplyLutToImage()
{
	if (mImageSensor)
	{
		delete mImageSensor;
		mImageSensor = 0;
	}

	if (mCurrentImage)
	{
		mCurrentImage->unref();
		mCurrentImage = 0;
	}
}

void SoXipApplyLutToImage::initClass()
{
	SO_NODE_INIT_CLASS( SoXipApplyLutToImage, SoNode, "Node" );

	SO_ENABLE(SoGLRenderAction,         SoXipLutElement);
	SO_ENABLE(SoPickAction,             SoXipLutElement);
	SO_ENABLE(SoCallbackAction,         SoXipLutElement);
	SO_ENABLE(SoGetBoundingBoxAction,   SoXipLutElement);
}

void SoXipApplyLutToImage::imageChanged()
{
	mImageId = 0;
	mLutId = 0;
}

void SoXipApplyLutToImage::loadTexture(SbXipImage *img, SbXipImage *lut)
{
	SbXipImage * tex = 0;

	if (mCurrentImage)
	{
		mCurrentImage->unref();
		mCurrentImage = 0;
	}

	if (lut)
		tex = createImage8Lut(img, lut);
	else
		tex = createImage8(img);

	if (tex)
	{
		// need a reference counted wrapper for this image so SoRadTexture can free by unref() after use
		mCurrentImage = new SoXipDataImage();
		if (mCurrentImage)
		{
			mCurrentImage->ref();
			mCurrentImage->set(tex);
		}
		else
		{
			// allocation of wrapper failed, need to delete image myself
			delete tex;
		}
	}
}

void SoXipApplyLutToImage::updateTexture(SoAction *action)
{
	if (!image.getValue())
	{
		mImageId = 0;

		if (mCurrentImage)
		{
			mCurrentImage->unref();
			mCurrentImage = 0;
		}
		return;
	}

	SoXipData * eltLut = (SoXipData *)SoXipLutElement::get(action->getState());

	if (image.getValue()->getDataId() == mImageId)
	{
		// if no lut or lut and image are same then no update is needed
		if (!eltLut && !mLutId)
			return;

		if (eltLut)
		{
			if (eltLut->getDataId() == mLutId)
				return;
		}
	}

	if (mCurrentImage)
	{
		mCurrentImage->unref();
		mCurrentImage = 0;
	}

	mImageId = image.getValue()->getDataId();
	mLutId = eltLut ? eltLut->getDataId() : 0;

	SbXipImage *img = image.getValue()->get();
	if (!img)
		return;

	SbXipImage *lut = 0;
	if (img->getComponents() == 1)
	{
		if (eltLut)
		{
			if (!eltLut->isOfType(SoXipDataImage::getClassTypeId()))
				return;

			lut = ((SoXipDataImage*) eltLut)->get();
		}
	}

	loadTexture(img, lut);

    if (output.getDataValue() != (SoXipData *)mCurrentImage)
        output.setDataValue((SoXipData *)mCurrentImage);
}

void SoXipApplyLutToImage::GLRender(SoGLRenderAction * action)
{
    try
    {
   		updateTexture(action);
	}
	catch (...)
    {
        SoError::post(__FILE__, "Unknown error while rendering image");
	}
}

void SoXipApplyLutToImage::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
	((SoXipApplyLutToImage*) user)->imageChanged();
}


















// creates an UNSIGNED_BYTE image of any given input image
SbXipImage * SoXipApplyLutToImage::createImage8(SbXipImage *in)
{
	const SbXipImageDimensions dim = in->getDimStored();
	const int components = in->getComponents();

	SbXipImage::ComponentLayoutType compLayout;
	switch (components)
	{
	case 1:	compLayout = SbXipImage::LUMINANCE; break;
	case 2:	compLayout = SbXipImage::LUMINANCE_ALPHA; break;
	case 3:	compLayout = SbXipImage::RGB; break;
	case 4:	compLayout = SbXipImage::RGBA; break;
	default:
		// unsupported
		return 0;
	}

	SbXipImage *out = new SbXipImage(dim, SbXipImage::UNSIGNED_BYTE, 8, components, 
		SbXipImage::INTERLEAVED, compLayout, in->getModelMatrix());
	SbXipImageInterleavedPixelPtr<unsigned char> outPtr(out);

	switch (in->getType())
	{
	case SbXipImage::UNSIGNED_BYTE:
		{
			SbXipImageInterleavedPixelPtr<unsigned char> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c);
		} break;
	case SbXipImage::BYTE:
		{
			SbXipImageInterleavedPixelPtr<char> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c) + 128;
		} break;
	case SbXipImage::UNSIGNED_SHORT:
		{
			int shift = in->getBitsStored() - 8;
			SbXipImageInterleavedPixelPtr<unsigned short> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c) >> shift;
		} break;
	case SbXipImage::SHORT:
		{
			int shift = in->getBitsStored() - 8;
			SbXipImageInterleavedPixelPtr<short> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = (inPtr(y, x, c) + 32768) >> shift;
		} break;
	case SbXipImage::FLOAT:
		{
			SbXipImageInterleavedPixelPtr<float> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c) * 255.f;
		} break;
	case SbXipImage::DOUBLE:
		{
			SbXipImageInterleavedPixelPtr<double> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = inPtr(y, x, c) * 255.;
		} break;
	}

	return out;
}

// creates an UNSIGNED_BYTE image of any given input image
SbXipImage * SoXipApplyLutToImage::createImage8Lut(SbXipImage *in, SbXipImage *lut)
{
	// convert LUT into UNSIGNED BYTE
	SbXipImage *lut8 = createImage8(lut);
	
	if (!lut8)
	{
		SoDebugError::postInfo(__FILE__, "createImage8 failed");
		return 0;
	}
	
	unsigned char *lut8Ptr = (unsigned char *) lut8->refBufferPtr();

	const SbXipImageDimensions dim = in->getDimStored();
	const int components = lut->getComponents();

	SbXipImage::ComponentLayoutType compLayout;
	switch (components)
	{
	case 1:	compLayout = SbXipImage::LUMINANCE; break;
	case 2:	compLayout = SbXipImage::LUMINANCE_ALPHA; break;
	case 3:	compLayout = SbXipImage::RGB; break;
	case 4:	compLayout = SbXipImage::RGBA; break;
	default:
		// unsupported
		return 0;
	}

	SbXipImage *out = new SbXipImage(dim, SbXipImage::UNSIGNED_BYTE, 8, components, 
		SbXipImage::INTERLEAVED, compLayout, in->getModelMatrix());
	SbXipImageInterleavedPixelPtr<unsigned char> outPtr(out);

	switch (in->getType())
	{
	case SbXipImage::UNSIGNED_BYTE:
		{
			SbXipImageInterleavedPixelPtr<unsigned char> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
				{
					unsigned char val = inPtr(y, x);
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = lut8Ptr[components * val + c];
				}
		} break;
	case SbXipImage::UNSIGNED_SHORT:
		{
			SbXipImageInterleavedPixelPtr<unsigned short> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
				{
					unsigned short val = inPtr(y, x);
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = lut8Ptr[components * val + c];
				}
		} break;
	case SbXipImage::SHORT:
		{
			SbXipImageInterleavedPixelPtr<short> inPtr(in);
			for (int y = 0; y < dim[1]; y++)
				for (int x = 0; x < dim[0]; x++)
				{
					unsigned short val = (inPtr(y, x) + 32768);
					for (int c = 0; c < components; c++)
						outPtr(y, x, c) = lut8Ptr[components * val + c];
				}
		} break;
	}

	lut8->unrefBufferPtr();
	delete lut8;

	return out;
}


