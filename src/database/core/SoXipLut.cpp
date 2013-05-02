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

#include <fstream>
#include "SoXipLut.h"
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoMemoryError.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/XipStringUtils.h>


struct colorRGBA
{
    float r;
    float g;
    float b;
    float a;
};

struct colorRGB
{
    float r;
    float g;
    float b;
};


SO_NODE_SOURCE(SoXipLut);


SoXipLut::SoXipLut()
{
	SO_NODE_CONSTRUCTOR(SoXipLut);

	mNumElements  = -1;
	mLutData = 0;
	mNodeId = 0;

    SO_NODE_ADD_FIELD(LUTDataImage, (NULL));

	SO_NODE_DEFINE_ENUM_VALUE(InputType, RAMP);
	SO_NODE_DEFINE_ENUM_VALUE(InputType, TRAPEZOID);
	SO_NODE_DEFINE_ENUM_VALUE(InputType, FILE);
	SO_NODE_DEFINE_ENUM_VALUE(InputType, ARRAY);
	SO_NODE_DEFINE_ENUM_VALUE(InputType, RAMP_FILE);
    SO_NODE_DEFINE_ENUM_VALUE(InputType, RAMP_ARRAY);
	SO_NODE_SET_SF_ENUM_TYPE(inputMode, InputType);
	SO_NODE_ADD_FIELD( inputMode, (RAMP) );

	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, DEFAULT);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, CONSTANT);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, INTENSITY);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, RAMP_MINMAX);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, STEP_RAMP);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, STEP_CENTER);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, STEP_SECOND);
	SO_NODE_SET_SF_ENUM_TYPE(alphaMode, AlphaType);
	SO_NODE_ADD_FIELD( alphaMode, (DEFAULT) );

	SO_NODE_DEFINE_ENUM_VALUE(FileType, FLOAT_COMMA);
	SO_NODE_DEFINE_ENUM_VALUE(FileType, FLOAT_SPACE);
	SO_NODE_DEFINE_ENUM_VALUE(FileType, BYTE_COMMA);
	SO_NODE_DEFINE_ENUM_VALUE(FileType, BYTE_SPACE);
	SO_NODE_SET_SF_ENUM_TYPE(fileMode, FileType);
	SO_NODE_ADD_FIELD(fileMode, (BYTE_SPACE));

	SO_NODE_DEFINE_ENUM_VALUE(OutputType, COLOR_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(OutputType, COLOR);
	SO_NODE_DEFINE_ENUM_VALUE(OutputType, LUMINANCE);
	SO_NODE_SET_SF_ENUM_TYPE(outputMode, OutputType);
	SO_NODE_ADD_FIELD(outputMode, (COLOR_ALPHA));

	SO_NODE_ADD_FIELD( bitsUsed, (0) );
//	SO_NODE_ADD_FIELD( constantAlpha, (FALSE));

	SO_NODE_ADD_FIELD( rampWidth, (1.f) );
	SO_NODE_ADD_FIELD( rampCenter, (0.5f) );
	SO_NODE_ADD_FIELD( alphaFactor, (1.f) );
	SO_NODE_ADD_FIELD( slopeWidth, (1.f) );
	SO_NODE_ADD_FIELD( slopeCenter, (0.5f) );
	SO_NODE_ADD_FIELD( colorBottom, (SbColor(0, 0, 0)) );
	SO_NODE_ADD_FIELD( colorMiddle, (SbColor(0.5, 0.5, 0.5)) );
	SO_NODE_ADD_FIELD( colorTop, (SbColor(1, 1, 1)) );

	SO_NODE_ADD_FIELD( fileIn, ("") );
	SO_NODE_ADD_FIELD( fileEntries, (0) );

	SO_NODE_ADD_FIELD( arrayColor, (SbColor(0,0,0)));
	SO_NODE_ADD_FIELD( arrayAlpha, (0));

	SO_NODE_ADD_FIELD( invertColor, (FALSE));

	arrayColor.setNum(0);
	arrayAlpha.setNum(0);

	SoField *fields[] =
	{
		&rampWidth,
		&rampCenter,
		&alphaFactor,
		&slopeWidth,
		&slopeCenter,
		&colorBottom,
		&colorMiddle,
		&colorTop,
		&bitsUsed,
		&inputMode,
		&outputMode,
		&fileIn,
		&fileEntries,
		&arrayColor,
		&arrayAlpha,
        &alphaMode,
		&invertColor
	};

	if (!mLutData)
	{
		mLutData = new SoXipDataImage;
		mLutData->ref();
	}
}


SoXipLut::~SoXipLut()
{
	if (mLutData)
	{
		mLutData->unref();
		mLutData = 0;
	}
}


void SoXipLut::initClass()
{
	SO_NODE_INIT_CLASS(SoXipLut, SoNode,  "Node");

	SO_ENABLE(SoGLRenderAction, SoXipLutElement);
	SO_ENABLE(SoPickAction,     SoXipLutElement);
	SO_ENABLE(SoCallbackAction, SoXipLutElement);
}


void SoXipLut::updateColorAlpha()
{
	int i;
	SbXipImage *lut = new SbXipImage(SbXipImageDimensions(mNumElements, 1), SbXipImage::FLOAT, 32, 4, SbXipImage::INTERLEAVED, SbXipImage::RGBA);
	mLutData->set(lut);
	void *ptr = lut->refBufferPtr();
	colorRGBA* rgbaBuffer = (colorRGBA*) ptr;
	
	switch (inputMode.getValue())
	{
	case RAMP:
	case TRAPEZOID:
		{
			int start = static_cast<int>(( rampCenter.getValue() - 0.5 * rampWidth.getValue() ) * mNumElements);
			int end = static_cast<int>(( rampCenter.getValue() + 0.5 * rampWidth.getValue() ) * mNumElements);

			start = start > 0 ? start : 0;
			end = end <= mNumElements ? end : mNumElements;

			int start2 = mNumElements;
			int end2   = mNumElements;

			if (inputMode.getValue() == TRAPEZOID)
			{
				start2 = static_cast<int>(( slopeCenter.getValue() - 0.5 * slopeWidth.getValue() ) * mNumElements);
				start2 = start2 > 0 ? start2 : 0;
				if (start2 < end) 
					start2 = end;

				end2 = static_cast<int>(( slopeCenter.getValue() + 0.5 * slopeWidth.getValue() ) * mNumElements);
				end2 = end2 < mNumElements ? end2 : mNumElements - 1;
			}

			int colorCenter = static_cast<int>(start + ( end - start ) * 0.5f);

			SbColor cBottom = colorBottom.getValue();
			SbColor cMiddle = colorMiddle.getValue();
			SbColor cTop = colorTop.getValue();

			for( i = 0; i < start; i++ )
			{
				rgbaBuffer[ i ].r = 0;
				rgbaBuffer[ i ].g = 0;
				rgbaBuffer[ i ].b = 0;
				rgbaBuffer[ i ].a = 0;
			}
			
			float ratio = 1.f / ( (float) end - start );

			for( i = start; i < colorCenter; i++ )
			{
				// scale of ramp
				float value = ( i - start ) * ratio;

				// blend factor 0 -> 1 from start to center of ramp
				float b = (float) ( i - start ) / (float) ( colorCenter - start );

				rgbaBuffer[ i ].r = ( 1 - b ) * cBottom[ 0 ] + b * cMiddle[ 0 ];
				rgbaBuffer[ i ].g = ( 1 - b ) * cBottom[ 1 ] + b * cMiddle[ 1 ];
				rgbaBuffer[ i ].b = ( 1 - b ) * cBottom[ 2 ] + b * cMiddle[ 2 ];

                //rgbaBuffer[ i ].a = alphaFactor.getValue()* ((0.212671f * rgbaBuffer[i].r) + (0.71516f * rgbaBuffer[i].g) + (0.072169f * rgbaBuffer[i].b));

				rgbaBuffer[ i ].a = alphaFactor.getValue() * value;
			}

			for( i = colorCenter; i < end; i++ )
			{
				// scale of ramp
				float value = ( i - start ) * ratio;

				// blend factor 0 -> 1 from center to end of ramp
				float b = (float) ( i - colorCenter ) / (float) ( end - colorCenter );

				rgbaBuffer[ i ].r = ( 1 - b ) * cMiddle[ 0 ] + b * cTop[ 0 ];
				rgbaBuffer[ i ].g = ( 1 - b ) * cMiddle[ 1 ] + b * cTop[ 1 ];
				rgbaBuffer[ i ].b = ( 1 - b ) * cMiddle[ 2 ] + b * cTop[ 2 ];
				
                //rgbaBuffer[ i ].a = alphaFactor.getValue()* ((0.212671f * rgbaBuffer[i].r) + (0.71516f * rgbaBuffer[i].g) + (0.072169f * rgbaBuffer[i].b));

				rgbaBuffer[ i ].a = alphaFactor.getValue() * value;
			}

			for( i = end; i < start2; i++ )
			{
				rgbaBuffer[ i ].r = cTop[ 0 ];
				rgbaBuffer[ i ].g = cTop[ 1 ];
				rgbaBuffer[ i ].b = cTop[ 2 ];

                //rgbaBuffer[ i ].a = alphaFactor.getValue()* ((0.212671f * rgbaBuffer[i].r) + (0.71516f * rgbaBuffer[i].g) + (0.072169f * rgbaBuffer[i].b));

				rgbaBuffer[ i ].a = alphaFactor.getValue();
			}

			colorCenter = static_cast<int>(start2 + ( end2 - start2 ) * 0.5f);
			ratio = 1.f / ( (float) end2 - start2 );

			for( i = start2; i < colorCenter; i++ )
			{
				// scale of ramp
				float value = ( i - start2 ) * ratio;

				// blend factor 0 -> 1 from start to center of ramp
				float b = (float) ( i - start2 ) / (float) ( colorCenter - start2 );

				rgbaBuffer[ i ].r = ( 1 - b ) * cTop[ 0 ] + b * cMiddle[ 0 ];
				rgbaBuffer[ i ].g = ( 1 - b ) * cTop[ 1 ] + b * cMiddle[ 1 ];
				rgbaBuffer[ i ].b = ( 1 - b ) * cTop[ 2 ] + b * cMiddle[ 2 ];

                //rgbaBuffer[ i ].a = alphaFactor.getValue()* ((0.212671f * rgbaBuffer[i].r) + (0.71516f * rgbaBuffer[i].g) + (0.072169f * rgbaBuffer[i].b));

				rgbaBuffer[ i ].a = alphaFactor.getValue() * (1.f - value);
			}

			for( i = colorCenter; i < end2; i++ )
			{
				// scale of ramp
				float value = ( i - start2 ) * ratio;

				// blend factor 0 -> 1 from center to end of ramp
				float b = (float) ( i - colorCenter ) / (float) ( end2 - colorCenter );

				rgbaBuffer[ i ].r = ( 1 - b ) * cMiddle[ 0 ] + b * cBottom[ 0 ];
				rgbaBuffer[ i ].g = ( 1 - b ) * cMiddle[ 1 ] + b * cBottom[ 1 ];
				rgbaBuffer[ i ].b = ( 1 - b ) * cMiddle[ 2 ] + b * cBottom[ 2 ];
				
                //rgbaBuffer[ i ].a = alphaFactor.getValue()* ((0.212671f * rgbaBuffer[i].r) + (0.71516f * rgbaBuffer[i].g) + (0.072169f * rgbaBuffer[i].b));

				rgbaBuffer[ i ].a = alphaFactor.getValue() * (1.f - value);
			}

			for( i = end2; i < mNumElements; i++ )
			{
				rgbaBuffer[ i ].r = 0;
				rgbaBuffer[ i ].g = 0;
				rgbaBuffer[ i ].b = 0;
				rgbaBuffer[ i ].a = 0.;
			}

			if (invertColor.getValue())
			{
				for( i = 0; i < mNumElements; i++ )
				{
					rgbaBuffer[ i ].r = 1 - rgbaBuffer[ i ].r;
					rgbaBuffer[ i ].g = 1 - rgbaBuffer[ i ].g;
					rgbaBuffer[ i ].b = 1 - rgbaBuffer[ i ].b;
					//rgbaBuffer[ i ].a = 1 - rgbaBuffer[ i ].a;
				}
			}

			adjustAlpha(rgbaBuffer, mNumElements, start, end);

		} break;
	case ARRAY:
		{
			if (arrayColor.getNum() == arrayAlpha.getNum())
			{
                int num = arrayColor.getNum();
                num = (num < mNumElements) ? num : mNumElements;
                int i;
				for (i = 0; i < num; ++i)
				{
					rgbaBuffer[i].r = arrayColor[i][0];
					rgbaBuffer[i].g = arrayColor[i][1];
					rgbaBuffer[i].b = arrayColor[i][2];
					rgbaBuffer[i].a = arrayAlpha[i];
				}
                for (i=num; i<mNumElements; ++i)
                {
                    rgbaBuffer[i].r = rgbaBuffer[i].g = rgbaBuffer[i].b = rgbaBuffer[i].a = 0;
                }
			}
			else // ambiguous input, set to default zero
			{
				lut->zero();
			}
		} break;
    case RAMP_ARRAY:
        {
            if (arrayColor.getNum() != arrayAlpha.getNum())
            {
                lut->zero();			
                return;
            }
            int cmap_size = arrayColor.getNum();
            if (cmap_size == 0)
            {
                cmap_size = mNumElements;
            }

            colorRGBA* cmap = new colorRGBA[cmap_size];
            int i;
            for (i = 0; i < cmap_size; ++i)
            {
                cmap[i].r = arrayColor[i][0];
                cmap[i].g = arrayColor[i][1];
                cmap[i].b = arrayColor[i][2];
                cmap[i].a = arrayAlpha[i];
            }

            int start = static_cast<int>(( rampCenter.getValue() - 0.5 * rampWidth.getValue() ) * mNumElements);
            int end = static_cast<int>(( rampCenter.getValue() + 0.5 * rampWidth.getValue() ) * mNumElements);

            start = start > 0 ? start : 0;
            end = end <= mNumElements ? end : mNumElements;

            int colorCenter = start + ( end - start ) * 0.5f;

            for (i = 0; i < start; ++i)
            {
                rgbaBuffer[ i ].r = 0;
                rgbaBuffer[ i ].g = 0;
                rgbaBuffer[ i ].b = 0;
                rgbaBuffer[ i ].a = 0;
            }

            float ratio = 1.f / ( (float) end - start );

            for (i = start; i < end; ++i)
            {
                // scale of ramp

                const float value = ( i - start ) * ratio;
                const float pos = value * (cmap_size - 1);
                const int k = static_cast<int>(floor(pos)); 
                const float fpos = pos - k;

                const float vr_min = cmap[k].r, vr_max = cmap[k+1].r;
                const float vg_min = cmap[k].g, vg_max = cmap[k+1].g;
                const float vb_min = cmap[k].b, vb_max = cmap[k+1].b;
                const float va_min = cmap[k].a, va_max = cmap[k+1].a;

                rgbaBuffer[ i ].r = vr_min + fpos * (vr_max - vr_min);
                rgbaBuffer[ i ].g = vg_min + fpos * (vg_max - vg_min);
                rgbaBuffer[ i ].b = vb_min + fpos * (vb_max - vb_min);
                rgbaBuffer[ i ].a = alphaFactor.getValue() * (va_min + fpos * (va_max - va_min));

            }

            const int idx_max = cmap_size - 1;

            for (i = end; i < mNumElements; ++i)
            {
                rgbaBuffer[ i ].r = cmap[ idx_max ].r;
                rgbaBuffer[ i ].g = cmap[ idx_max ].g;
                rgbaBuffer[ i ].b = cmap[ idx_max ].b;
                rgbaBuffer[ i ].a = alphaFactor.getValue() * cmap[ idx_max ].a;
            }
            delete[] cmap;

            adjustAlpha(rgbaBuffer, mNumElements, start, end);

        } break;

	case FILE:
		{
			if (fileEntries.getValue() <= 0 || fileIn.getValue().getLength() <= 0)
			{
				lut->zero();			
				return;
			}
			int cmap_size = fileEntries.getValue();
			if (cmap_size == 0)
			{
				cmap_size = mNumElements;
				fileEntries.setValue(mNumElements);
			}
			if (cmap_size != mNumElements)
			{
				colorRGBA* buf = new colorRGBA[cmap_size];

				loadFromFile(buf);

				for (i = 0; i < mNumElements; ++i)
				{	
					int index = i * cmap_size / mNumElements;
					memcpy(rgbaBuffer + i, buf + index, sizeof(colorRGBA));
				}
				delete[] buf;
			}
			else
			{
				loadFromFile(rgbaBuffer);
			}

		} break;
	case RAMP_FILE:
		{
			if (fileEntries.getValue() <= 0 || fileIn.getValue().getLength() <= 0)
			{
				lut->zero();			
				return;
			}
			int cmap_size = fileEntries.getValue();
			if (cmap_size == 0)
			{
				cmap_size = mNumElements;
				fileEntries.setValue(mNumElements);
			}
			
			colorRGBA* cmap = new colorRGBA[cmap_size];
			loadFromFile(cmap);

			int start = static_cast<int>(( rampCenter.getValue() - 0.5 * rampWidth.getValue() ) * mNumElements);
			int end = static_cast<int>(( rampCenter.getValue() + 0.5 * rampWidth.getValue() ) * mNumElements);

			start = start > 0 ? start : 0;
			end = end <= mNumElements ? end : mNumElements;

			int colorCenter = start + ( end - start ) * 0.5f;
			
			for (i = 0; i < start; ++i)
			{
				rgbaBuffer[ i ].r = 0;
				rgbaBuffer[ i ].g = 0;
				rgbaBuffer[ i ].b = 0;
				rgbaBuffer[ i ].a = 0;
			}
			
			float ratio = 1.f / ( (float) end - start );

			for (i = start; i < end; ++i)
			{
				// scale of ramp
				
				const float value = ( i - start ) * ratio;
				const float pos = value * (cmap_size - 1);
				const int k = static_cast<int>(floor(pos)); 
				const float fpos = pos - k;
				
				const float vr_min = cmap[k].r, vr_max = cmap[k+1].r;
				const float vg_min = cmap[k].g, vg_max = cmap[k+1].g;
				const float vb_min = cmap[k].b, vb_max = cmap[k+1].b;
				const float va_min = cmap[k].a, va_max = cmap[k+1].a;
				
				rgbaBuffer[ i ].r = vr_min + fpos * (vr_max - vr_min);
				rgbaBuffer[ i ].g = vg_min + fpos * (vg_max - vg_min);
				rgbaBuffer[ i ].b = vb_min + fpos * (vb_max - vb_min);
				rgbaBuffer[ i ].a = alphaFactor.getValue() * (va_min + fpos * (va_max - va_min));

			}

			const int idx_max = cmap_size - 1;

			for (i = end; i < mNumElements; ++i)
			{
				rgbaBuffer[ i ].r = cmap[ idx_max ].r;
				rgbaBuffer[ i ].g = cmap[ idx_max ].g;
				rgbaBuffer[ i ].b = cmap[ idx_max ].b;
                rgbaBuffer[ i ].a = alphaFactor.getValue() * cmap[ idx_max ].a;
			}
			delete[] cmap;

			adjustAlpha(rgbaBuffer, mNumElements, start, end);

		} break;
	}

	lut->unrefBufferPtr();
}


void SoXipLut::updateColor()
{
	SbXipImage *lut = new SbXipImage(SbXipImageDimensions(mNumElements, 1),
		SbXipImage::FLOAT, 32, 3, SbXipImage::INTERLEAVED, SbXipImage::RGB);
	mLutData->set(lut);

	void *ptr = lut->refBufferPtr();
	colorRGB* rgbBuffer = (colorRGB*) ptr;

	switch (inputMode.getValue())
	{
	case FILE:
		{
			lut->zero();
			//loadFromFile(rgbaBuffer);
			SoError::post("Loading of RGB lookup tables is currently unsupported.\n");
		} break;
	case RAMP:
	case TRAPEZOID:
		{
			int i;
			int start = static_cast<int>(( rampCenter.getValue() - 0.5 * rampWidth.getValue() ) * mNumElements);
			int end = static_cast<int>(( rampCenter.getValue() + 0.5 * rampWidth.getValue() ) * mNumElements);

			start = start > 0 ? start : 0;
			end = end <= mNumElements ? end : mNumElements;

			int start2 = mNumElements;
			int end2   = mNumElements;

			if (inputMode.getValue() == TRAPEZOID)
			{
				start2 = static_cast<int>(( slopeCenter.getValue() - 0.5 * slopeWidth.getValue() ) * mNumElements);
				start2 = start2 > 0 ? start2 : 0;
				if (start2 < end) 
					start2 = end;

				end2 = static_cast<int>(( slopeCenter.getValue() + 0.5 * slopeWidth.getValue() ) * mNumElements);
				end2 = end2 < mNumElements ? end2 : mNumElements - 1;
			}

			int colorCenter = static_cast<int>(start + ( end - start ) * 0.5f);

			SbColor cBottom = colorBottom.getValue();
			SbColor cMiddle = colorMiddle.getValue();
			SbColor cTop = colorTop.getValue();

			for( i = 0; i < start; i++ )
			{
				rgbBuffer[ i ].r = 0;
				rgbBuffer[ i ].g = 0;
				rgbBuffer[ i ].b = 0;
			}
			
			float ratio = 1.f / ( (float) end - start );

			for( i = start; i < colorCenter; i++ )
			{
				// blend factor 0 -> 1 from start to center of ramp
				float b = (float) ( i - start ) / (float) ( colorCenter - start );

				rgbBuffer[ i ].r = ( 1 - b ) * cBottom[ 0 ] + b * cMiddle[ 0 ];
				rgbBuffer[ i ].g = ( 1 - b ) * cBottom[ 1 ] + b * cMiddle[ 1 ];
				rgbBuffer[ i ].b = ( 1 - b ) * cBottom[ 2 ] + b * cMiddle[ 2 ];
			}

			for( i = colorCenter; i < end; i++ )
			{
				// blend factor 0 -> 1 from center to end of ramp
				float b = (float) ( i - colorCenter ) / (float) ( end - colorCenter );

				rgbBuffer[ i ].r = ( 1 - b ) * cMiddle[ 0 ] + b * cTop[ 0 ];
				rgbBuffer[ i ].g = ( 1 - b ) * cMiddle[ 1 ] + b * cTop[ 1 ];
				rgbBuffer[ i ].b = ( 1 - b ) * cMiddle[ 2 ] + b * cTop[ 2 ];
			}

			for( i = end; i < start2; i++ )
			{
				rgbBuffer[ i ].r = cTop[ 0 ];
				rgbBuffer[ i ].g = cTop[ 1 ];
				rgbBuffer[ i ].b = cTop[ 2 ];
			}

			colorCenter = static_cast<int>(start2 + ( end2 - start2 ) * 0.5f);
			ratio = 1.f / ( (float) end2 - start2 );

			for( i = start2; i < colorCenter; i++ )
			{
				// blend factor 0 -> 1 from start to center of ramp
				float b = (float) ( i - start2 ) / (float) ( colorCenter - start2 );

				rgbBuffer[ i ].r = ( 1 - b ) * cTop[ 0 ] + b * cMiddle[ 0 ];
				rgbBuffer[ i ].g = ( 1 - b ) * cTop[ 1 ] + b * cMiddle[ 1 ];
				rgbBuffer[ i ].b = ( 1 - b ) * cTop[ 2 ] + b * cMiddle[ 2 ];
			}

			for( i = colorCenter; i < end2; i++ )
			{
				// blend factor 0 -> 1 from center to end of ramp
				float b = (float) ( i - colorCenter ) / (float) ( end2 - colorCenter );

				rgbBuffer[ i ].r = ( 1 - b ) * cMiddle[ 0 ] + b * cBottom[ 0 ];
				rgbBuffer[ i ].g = ( 1 - b ) * cMiddle[ 1 ] + b * cBottom[ 1 ];
				rgbBuffer[ i ].b = ( 1 - b ) * cMiddle[ 2 ] + b * cBottom[ 2 ];
			}

			for( i = end2; i < mNumElements; i++ )
			{
				rgbBuffer[ i ].r = 0;
				rgbBuffer[ i ].g = 0;
				rgbBuffer[ i ].b = 0;
			}
		} break;
	case ARRAY:
		{
			if (arrayColor.getNum() == arrayAlpha.getNum())
			{
                int num = arrayColor.getNum();
                num = (num < mNumElements) ? num : mNumElements;
                int i;
				for (i = 0; i < num; ++i)
				{
					rgbBuffer[i].r = arrayColor[i][0];
					rgbBuffer[i].g = arrayColor[i][1];
					rgbBuffer[i].b = arrayColor[i][2];
				}
                for (i=num; i<mNumElements; ++i)
                {
                    rgbBuffer[i].r = rgbBuffer[i].b = rgbBuffer[i].b = 0;
                }
			}
			else
			{
				lut->zero();
			}
		} break;
	case RAMP_FILE:
		{
			lut->zero();
			SoError::post("RAMP_FILE can not be used to produce an RGB output.\n");
		} break;
	}

	lut->unrefBufferPtr();
}


void SoXipLut::updateGray()
{
	SbXipImage *lut = new SbXipImage(SbXipImageDimensions(mNumElements, 1),
		SbXipImage::FLOAT, 32, 1, SbXipImage::INTERLEAVED, SbXipImage::LUMINANCE);
	mLutData->set(lut);

	void *ptr = lut->refBufferPtr();
	float* grayBuffer = (float*) ptr;

	switch (inputMode.getValue())
	{
	case FILE:
		{
			lut->zero();
			//loadFromFile(rgbaBuffer);
			SoError::post("Loading of gray lookup tables is currently unsupported.\n");
		} break;

	case RAMP:
	case TRAPEZOID:
		{
			int i;
			int start = static_cast<int>(( rampCenter.getValue() - 0.5 * rampWidth.getValue() ) * mNumElements);
			int end = static_cast<int>(( rampCenter.getValue() + 0.5 * rampWidth.getValue() ) * mNumElements);

			start = start > 0 ? start : 0;
			end = end < mNumElements ? end : mNumElements - 1;

			int start2 = mNumElements - 1;
			int end2   = mNumElements - 1;

			if (inputMode.getValue() == TRAPEZOID)
			{
				start2 = static_cast<int>(( slopeCenter.getValue() - 0.5 * slopeWidth.getValue() ) * mNumElements);
				start2 = start2 > 0 ? start2 : 0;
				if (start2 < end) 
					start2 = end;

				end2 = static_cast<int>(( slopeCenter.getValue() + 0.5 * slopeWidth.getValue() ) * mNumElements);
				end2 = end2 < mNumElements ? end2 : mNumElements - 1;
			}

			int colorCenter = static_cast<int>(start + ( end - start ) * 0.5f);

			SbColor cBottom = colorBottom.getValue();
			SbColor cMiddle = colorMiddle.getValue();
			SbColor cTop = colorTop.getValue();

			for( i = 0; i < start; i++ )
			{
				grayBuffer[i] = 0;
			}
			
			float ratio = 1.f / ( (float) end - start );

			for( i = start; i < colorCenter; i++ )
			{
				// scale of ramp
				float value = ( i - start ) * ratio;

				// blend factor 0 -> 1 from start to center of ramp
				float b = (float) ( i - start ) / (float) ( colorCenter - start );

				float red = ( 1 - b ) * cBottom[ 0 ] + b * cMiddle[ 0 ];
				float green = ( 1 - b ) * cBottom[ 1 ] + b * cMiddle[ 1 ];
				float blue = ( 1 - b ) * cBottom[ 2 ] + b * cMiddle[ 2 ];

				// 0.299r + 0.587g + 0.114b
				grayBuffer[ i ] = 0.299 * red + 0.587 * green + 0.114 * blue;
			}

			for( i = colorCenter; i < end; i++ )
			{
				// blend factor 0 -> 1 from center to end of ramp
				float b = (float) ( i - colorCenter ) / (float) ( end - colorCenter );

				float red = ( 1 - b ) * cMiddle[ 0 ] + b * cTop[ 0 ];
				float green = ( 1 - b ) * cMiddle[ 1 ] + b * cTop[ 1 ];
				float blue = ( 1 - b ) * cMiddle[ 2 ] + b * cTop[ 2 ];

				// 0.299r + 0.587g + 0.114b
				grayBuffer[ i ] = 0.299 * red + 0.587 * green + 0.114 * blue;
			}

			for( i = end; i < start2; i++ )
			{
				// 0.299r + 0.587g + 0.114b
				grayBuffer[ i ] = 0.299 * cTop[ 0 ] + 0.587 * cTop[ 1 ] + 0.114 * cTop[ 2 ];
			}

			colorCenter = static_cast<int>(start2 + ( end2 - start2 ) * 0.5f);
			ratio = 1.f / ( (float) end2 - start2 );

			for( i = start2; i < colorCenter; i++ )
			{
				// blend factor 0 -> 1 from start to center of ramp
				float b = (float) ( i - start2 ) / (float) ( colorCenter - start2 );

				float red = ( 1 - b ) * cTop[ 0 ] + b * cMiddle[ 0 ];
				float green = ( 1 - b ) * cTop[ 1 ] + b * cMiddle[ 1 ];
				float blue = ( 1 - b ) * cTop[ 2 ] + b * cMiddle[ 2 ];

				// 0.299r + 0.587g + 0.114b
				grayBuffer[ i ] = 0.299f * red + 0.587f * green + 0.114f * blue;
			}

			for( i = colorCenter; i < end2; i++ )
			{
				// blend factor 0 -> 1 from center to end of ramp
				float b = (float) ( i - colorCenter ) / (float) ( end2 - colorCenter );

				float red = ( 1 - b ) * cMiddle[ 0 ] + b * cBottom[ 0 ];
				float green = ( 1 - b ) * cMiddle[ 1 ] + b * cBottom[ 1 ];
				float blue = ( 1 - b ) * cMiddle[ 2 ] + b * cBottom[ 2 ];

				// 0.299r + 0.587g + 0.114b
				grayBuffer[ i ] = 0.299f * red + 0.587f * green + 0.114f * blue;
			}

			for( i = end2; i < mNumElements; i++ )
			{
				grayBuffer[ i ] = 0.f;
			}
		} break;
		
	case ARRAY:
		{
			if (arrayColor.getNum() == arrayAlpha.getNum())
			{
                int num = arrayColor.getNum();
                num = (num < mNumElements) ? num : mNumElements;
                int i;
				for (i = 0; i < num; ++i)
				{
					float red = arrayColor[i][0];
					float green = arrayColor[i][1];
					float blue = arrayColor[i][2];

					// 0.299r + 0.587g + 0.114b
					grayBuffer[ i ] = 0.299f * red + 0.587f * green + 0.114f * blue;

				}
                for (i=num; i<mNumElements; ++i)
                {
                    grayBuffer[i] = 0;
                }
			}
			else
			{
				lut->zero();
			}
		} break;
	case RAMP_FILE:
		{
			lut->zero();
			SoError::post("RAMP_FILE can not be used to produce a LUMINANCE output.\n");
		} break;
	}

	lut->unrefBufferPtr();
}


void SoXipLut::loadFromFile(void *buffer)
{
	colorRGBA *lut = (colorRGBA *) buffer;

	if (fileEntries.getValue() <= 0 || fileIn.getValue().getLength() <= 0)
		return;

	SbString fileName = XipStrExpandEnv(fileIn.getValue().getString());
	
#ifdef WIN32
    //assuming everything is done using the bad backslashes... so we convert all forward slashes to those
    const char * fileLocal = XipReplaceChar(fileName.getString(), '/', '\\').getString();
#else //UNIX
    //assuming the other way around since we need forward slashes now...
    const char * fileLocal = XipReplaceChar(fileName.getString(), '\\', '/').getString();
#endif //WIN32

	std::ifstream input(fileLocal, std::ios::in);
	if (!input)
	{
		SoError::post("Unable to open file '%s'", fileLocal); //fileIn.getValue().getString()
		return;
	}

	int numEntries = fileEntries.getValue();

	for (int i = 0; i < numEntries; ++i )
	{
		// Read the RGBA information
		char comma;
		switch (fileMode.getValue())
		{
		case BYTE_SPACE:
			input >> lut[ i ].r >> lut[ i ].g >> lut[ i ].b >> lut[ i ].a;
			lut[i].r /= 255.0f;
			lut[i].g /= 255.0f;
			lut[i].b /= 255.0f;
			lut[i].a /= 255.0f;
			break;
		case BYTE_COMMA:
			input >> lut[ i ].r >> comma >> lut[ i ].g >> comma >> lut[ i ].b >> comma >> lut[ i ].a;
			lut[i].r /= 255.0f;
			lut[i].g /= 255.0f;
			lut[i].b /= 255.0f;
			lut[i].a /= 255.0f;
			break;
		case FLOAT_SPACE:
			input >> lut[ i ].r >> lut[ i ].g >> lut[ i ].b >> lut[ i ].a;
			break;
		case FLOAT_COMMA:
			input >> lut[ i ].r >> comma >> lut[ i ].g >> comma >> lut[ i ].b >> comma >> lut[ i ].a;
			break;
		default:
			break;
		}
	}
	input.close();
}


void SoXipLut::doAction(SoAction *action)
{
	int newBitsUsed = bitsUsed.getValue();
	if (newBitsUsed <= 0) return;

	if (mLutData)
		if (!mLutData->get())
            mNodeId = 0;

	if (!mLutData)
        mNodeId = 0;

	if ((mNodeId != getNodeId()) || !mNodeId)
	{
		// need to update
		mNumElements = 1 << newBitsUsed;

		if (mLutData)
		{
			mLutData->unref();
			mLutData = 0;
		}

		mLutData = new SoXipDataImage;
		mLutData->ref();

		// Make sure width/center values are useable
		if (rampCenter.getValue() > 1.0f)
			rampCenter.setValue(1.0f);
		else if (rampCenter.getValue() < 0.0f)
			rampCenter.setValue(0.0f);
		if (rampWidth.getValue() < 0.0f)
			rampWidth.setValue(0.0f);

		// Update the LUT
		switch(outputMode.getValue())
		{
		case COLOR_ALPHA:	updateColorAlpha(); break;
		case COLOR:			updateColor(); break;
		case LUMINANCE:		updateGray(); break;
		}

        LUTDataImage.setValue(mLutData);
		mNodeId = getNodeId();
	}

	SoXipLutElement::set(action->getState(), this, mLutData);
}


void SoXipLut::adjustAlpha(colorRGBA* rgbaBuffer, int numElements, int start, int end)
{
	int i;

    // reset alpha value if user selects custom alpha mode
	switch (alphaMode.getValue())
	{
	case CONSTANT:
		{
			float a = alphaFactor.getValue();
			for (i = 0; i< numElements; ++i)
			{
				rgbaBuffer[ i ].a = a;
			}
		} break;
	case INTENSITY:
		{
			for (i = 0; i< numElements; ++i)
			{
				rgbaBuffer[ i ].a = alphaFactor.getValue()* ((0.212671f * rgbaBuffer[i].r) + (0.71516f * rgbaBuffer[i].g) + (0.072169f * rgbaBuffer[i].b));
			}
		} break;
	case RAMP_MINMAX:
		{
			for (i = end; i < numElements; ++i)
			{
				rgbaBuffer[ i ].a = 0;
			}
		} break;
	case STEP_RAMP:
		{
			float a = alphaFactor.getValue();
			for (i = 0; i < start; ++i)
			{
				rgbaBuffer[ i ].a = 0;
			}
			for (; i < end; ++i)
			{
				rgbaBuffer[ i ].a = a;
			}
			for (; i < numElements; ++i)
			{
				rgbaBuffer[ i ].a = 0;
			}
		} break;
	case STEP_CENTER:
		{
			float a = alphaFactor.getValue();
			for (i = 0; i < (start + 0.5 * (end - start)); ++i)
			{
				rgbaBuffer[ i ].a = 0;
			}
			for (; i < numElements; ++i)
			{
				rgbaBuffer[ i ].a = a;
			}
		} break;
	case STEP_SECOND:
		{
			float a = alphaFactor.getValue();
			rgbaBuffer[ 0 ].a = 0;
			for (i = 1; i < numElements; ++i)
			{
				rgbaBuffer[ i ].a = a;
			}
		} break;
	}
}


