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
#include <xip/system/standard.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/errors/SoErrors.h>
#include "SoXipLutTexture.h"

SO_NODE_SOURCE(SoXipLutTexture);

/**
 *	Constructor
 */	
SoXipLutTexture::SoXipLutTexture()
{
	SO_NODE_CONSTRUCTOR(SoXipLutTexture);

	SO_NODE_ADD_FIELD(interpolation, (TRUE));
	SO_NODE_ADD_FIELD(preMultiplyRGB, (TRUE));
	SO_NODE_ADD_FIELD(opacityCorrection, (TRUE));
	SO_NODE_ADD_FIELD(samplingRate, (1.0f));
	SO_NODE_ADD_FIELD(useComplexity, (FALSE));
	SO_NODE_ADD_FIELD(textureSize, (SbVec2s(0, 0)));

	mTextureId = 0;
    mLutId = 0;
	mBuf = 0;
	mTexSize = SbVec2s(0,0);
}

/**
 *	Destructor
 */	
SoXipLutTexture::~SoXipLutTexture()
{
	if (mTextureId)
		glDeleteTextures(1, &mTextureId);
	if (mBuf)
		delete[] mBuf;
}

/**	
 *	Initializes the class
 */
void SoXipLutTexture::initClass()
{
	SO_NODE_INIT_CLASS(SoXipLutTexture, SoNode,  "Node");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction,	SoXipMultiTextureElement);
	SO_ENABLE(SoGLRenderAction, SoXipLutElement);
	SO_ENABLE(SoGLRenderAction, SoComplexityElement);
}

void SoXipLutTexture::GLRender(SoGLRenderAction *action)
{
	SoState *state = action->getState();
	if (!state)
		return;

	try
    {
		// Create the texture id 
		if (!mTextureId)
			glGenTextures(1, &mTextureId);

		//	Get the current LUT element
	    SoXipDataImage* image = (SoXipDataImage *) SoXipLutElement::get(state);
    	
	    if (image)
	    {
			glPushAttrib(GL_ENABLE_BIT);
			//	Enable OpenInventor texture
			SoGLTextureEnabledElement::set(state, TRUE);
			// Bind the texture
			SoXipMultiTextureElement::bindTexture(state, GL_TEXTURE_2D, mTextureId);

		    if (!image->isOfType(SoXipDataImage::getClassTypeId()))
		    {
			    SoDebugError::post(__FILE__, "Invalid Lut Image");
			    return;
		    }
			
			bool preMultiply = static_cast<bool>(preMultiplyRGB.getValue());
			bool alphaCorrection = static_cast<bool>(opacityCorrection.getValue());
			float sRate = samplingRate.getValue();
			if (useComplexity.getValue())
			{
				float complexity = SoComplexityElement::get(state);
				// Inventor complexity usually ranges from 0.1 -> 0.5, remap to 0.2 -> 1.0
				sRate *= 2.f * complexity;
			}
			
			bool update = false;
			if (preMultiply != mPreMultiply ||
				alphaCorrection != mAlphaCorrection)
			{
				update = true;
				mPreMultiply = preMultiply;
				mAlphaCorrection = alphaCorrection;
			}
			if (mAlphaCorrection && sRate != mSampleRate)
			{
				update = true;
				mSampleRate = sRate;
			}
		 
			//	New LUT
		    if (update || image->getDataId() != mLutId)
		    {
				// update lut id for next time
			    mLutId = image->getDataId();

				SbXipImage *img = image->get();
				if (img)
				{
					SbVec2s texSize;
					// Get the number of elements and make sure it's valid
					int totLutElements = img->getDimStored()[0];
					if (!totLutElements)
					{
						SoDebugError::postInfo(__FILE__, "Invalid LUT Image: 0 elements");
						return;
					}
					else if (totLutElements <= 4096)
						texSize = SbVec2s(totLutElements, 1);
					else if (totLutElements == 65536)
						texSize = SbVec2s(256, 256);
					else
					{
						SoDebugError::postInfo(__FILE__, "Invalid LUT Image: %d elements", totLutElements);
						return;
					}				

					// Resize texture if different number of elements
					if (mTexSize != texSize)
					{
						mTexSize = texSize;
						textureSize.setValue(mTexSize);
						resizeTexture(img);
					}
					updateTexture(img);
				}
			}
			glPopAttrib();
		}
    }
	//	Handle exceptions
    catch (...)
    {
        SoDebugError::post(__FILE__, "Unknown Exception");
        return;
    }
}


void	SoXipLutTexture::resizeTexture(SbXipImage *image)
{
	glTexImage2D(GL_TEXTURE_2D,		// target
		       0,					// level
		       GL_RGBA_FLOAT16_ATI,	// internal
		       mTexSize[0],			// width
		       mTexSize[1],			// height
		       0,					// border
		       GL_RGBA,				// format
		       GL_FLOAT,			// type
		       0);

	//	set the texture parameters for OpenGL
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GLint intr = interpolation.getValue() ? GL_LINEAR : GL_NEAREST;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, intr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, intr);

	if (mBuf)
		delete mBuf;
	mBuf = new float[mTexSize[0] * mTexSize[1] * 4];
}

void	SoXipLutTexture::updateTexture(SbXipImage *image)
{
	if (image->getType() != SbXipImage::FLOAT ||
		image->getComponentLayoutType() != SbXipImage::RGBA)
	{
		SoDebugError::postInfo(__FILE__, "Invalid LUT Image: expecting RGBA Float");
		return;
	}
	
	//	Get the pixel buffer of the LUT
	const float* buf = (float *) image->refBufferPtr();
	if (!buf)
		return;

	float factor = 1.0f / mSampleRate; // baseline (HQ) factor
	
	// Pre-multiply colors by alpha
	for (int i = 0; i < image->getDimStored()[0]; ++i)
	{
		float alpha = buf[(i << 2) + 3];
		if (mAlphaCorrection)
			alpha = 1.0f - pow(1.0f - alpha, factor);
		mBuf[(i << 2) + 0] = buf[(i << 2) + 0] * (mPreMultiply ? alpha : 1.0f);
		mBuf[(i << 2) + 1] = buf[(i << 2) + 1] * (mPreMultiply ? alpha : 1.0f);
		mBuf[(i << 2) + 2] = buf[(i << 2) + 2] * (mPreMultiply ? alpha : 1.0f);
		mBuf[(i << 2) + 3] = alpha;
	}
	image->unrefBufferPtr();

	// Save unpack alignment
	int align;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &align);
	// Set optimal unpack alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, getPackAlignment(mTexSize[0]));
	// Upload texture
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mTexSize[0], mTexSize[1], GL_RGBA, GL_FLOAT, mBuf);	
	// Restore unpack alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, align);
}



