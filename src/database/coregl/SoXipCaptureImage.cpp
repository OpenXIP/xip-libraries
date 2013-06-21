/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
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



