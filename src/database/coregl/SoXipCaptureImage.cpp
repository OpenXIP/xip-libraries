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
#include <xip/inventor/coregl/SoXipCaptureImage.h>

SO_NODE_SOURCE(SoXipCaptureImage);

void SoXipCaptureImage::initClass() {
	SO_NODE_INIT_CLASS(SoXipCaptureImage, SoNode, "SoNode");
}

SoXipCaptureImage::SoXipCaptureImage() {
	SO_NODE_CONSTRUCTOR(SoXipCaptureImage);

	SO_NODE_ADD_FIELD(image, (NULL));
	SO_NODE_ADD_FIELD(format, (RGB));
	SO_NODE_ADD_FIELD(type, (UNSIGNED_BYTE));
	SO_NODE_ADD_FIELD(capture, ());
	SO_NODE_ADD_FIELD(autoCapture, (false));

	SO_NODE_DEFINE_ENUM_VALUE(Format, COLOR_INDEX);
	SO_NODE_DEFINE_ENUM_VALUE(Format, STENCIL_INDEX);
	SO_NODE_DEFINE_ENUM_VALUE(Format, DEPTH_COMPONENT);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RED);
	SO_NODE_DEFINE_ENUM_VALUE(Format, GREEN);
	SO_NODE_DEFINE_ENUM_VALUE(Format, BLUE);
	SO_NODE_DEFINE_ENUM_VALUE(Format, ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGB);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGBA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE_ALPHA);
	SO_NODE_SET_SF_ENUM_TYPE(format, Format);

	SO_NODE_DEFINE_ENUM_VALUE(Type, UNSIGNED_BYTE);
	SO_NODE_DEFINE_ENUM_VALUE(Type, BYTE);
	SO_NODE_DEFINE_ENUM_VALUE(Type, BITMAP);
	SO_NODE_DEFINE_ENUM_VALUE(Type, UNSIGNED_SHORT);
	SO_NODE_DEFINE_ENUM_VALUE(Type, SHORT);
	SO_NODE_DEFINE_ENUM_VALUE(Type, UNSIGNED_INT);
	SO_NODE_DEFINE_ENUM_VALUE(Type, INT);
	SO_NODE_DEFINE_ENUM_VALUE(Type, FLOAT);
	SO_NODE_SET_SF_ENUM_TYPE(type, Type);

	mSensorCapture = new SoFieldSensor(sensorCaptureCB, this);
	mSensorCapture->attach(&capture);

	mNeedCapture = false;

	mDataImage = NULL;
}

SoXipCaptureImage::~SoXipCaptureImage() {
	if (mDataImage) {
		mDataImage->unref();
	}

	delete mSensorCapture;
}

void SoXipCaptureImage::GLRender(SoGLRenderAction* action) {
	if (autoCapture.getValue() || mNeedCapture) {
		captureImage();

		image.setValue(mDataImage);

		mNeedCapture = false;
	}
}

void SoXipCaptureImage::captureImage() {
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	const int width = viewport[2]; // Size of the block of pixels 
	const int height = viewport[3]; // which is to be tested. 
	const int x_off = viewport[0]; // Position of block 
	const int y_off = viewport[1]; // of pixels. 

	//SoDebugError::postInfo(__FUNCTION__, "Viewport: (%d, %d, %d, %d), off: (%d, %d)", viewport[0], viewport[1], viewport[2], viewport[3], x_off, y_off);

	SbXipImageDimensions dimensions(width, height);
	SbXipImage::DataType dataType;
	SbXipImage::ComponentType compType;
	SbXipImage::ComponentLayoutType compLayout;
	int bitsStored, components;

	switch (format.getValue()) {
		case COLOR_INDEX:
		case STENCIL_INDEX:
		case DEPTH_COMPONENT:
		case LUMINANCE:
			compLayout = SbXipImage::LUMINANCE;
			compType = SbXipImage::SEPARATE;
			components = 1;
			break;
		case RED:
			compLayout = SbXipImage::RED;
			compType = SbXipImage::SEPARATE;
			components = 1;
			break;
		case GREEN:
			compLayout = SbXipImage::GREEN;
			compType = SbXipImage::SEPARATE;
			components = 1;
			break;
		case BLUE:
			compLayout = SbXipImage::BLUE;
			compType = SbXipImage::SEPARATE;
			components = 1;
			break;
		case ALPHA:
			compLayout = SbXipImage::ALPHA;
			compType = SbXipImage::SEPARATE;
			components = 1;
			break;
		case RGB:
			compLayout = SbXipImage::RGB;
			compType = SbXipImage::INTERLEAVED;
			components = 3;
			break;
		case RGBA:
			compLayout = SbXipImage::RGBA;
			compType = SbXipImage::INTERLEAVED;
			components = 4;
			break;
		case LUMINANCE_ALPHA:
			compLayout = SbXipImage::LUMINANCE_ALPHA;
			compType = SbXipImage::INTERLEAVED;
			components = 2;
			break;
		default:
			SoDebugError::post(__FUNCTION__, "Unhandled Format");
			return;
	}
	
	switch (type.getValue()) {
		case UNSIGNED_BYTE:
			dataType = SbXipImage::UNSIGNED_BYTE;
			bitsStored = 8;
			break;
		case BYTE:
			dataType = SbXipImage::BYTE;
			bitsStored = 7;
			break;
		case BITMAP:
			dataType = SbXipImage::UNSIGNED_BYTE;
			bitsStored = 1;
			break;
		case UNSIGNED_SHORT:
			dataType = SbXipImage::UNSIGNED_SHORT;
			bitsStored = 16;
			break;
		case SHORT:
			dataType = SbXipImage::SHORT;
			bitsStored = 15;
			break;
		case UNSIGNED_INT:
			dataType = SbXipImage::UNSIGNED_INT;
			bitsStored = 32;
			break;
		case INT:
			dataType = SbXipImage::INT;
			bitsStored = 31;
			break;
		case FLOAT:
			dataType = SbXipImage::FLOAT;
			bitsStored = 32;
			break;
		default:
			SoDebugError::post(__FUNCTION__, "Unhandled type");
			return;
	}

	SbXipImage *captureImage = new SbXipImage(dimensions, dataType, bitsStored, components, compType, compLayout);

	// copy the buffer
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x_off, y_off, width, height, format.getValue(), type.getValue(), captureImage->refBufferPtr());

	if (mDataImage) {
		mDataImage->unref();
	}

	mDataImage = new SoXipDataImage();
	mDataImage->ref();
	mDataImage->set(captureImage);
}

void SoXipCaptureImage::sensorCaptureCB(void *usr, SoSensor *sensor) {
	((SoXipCaptureImage*)usr)->mNeedCapture = true;
}



