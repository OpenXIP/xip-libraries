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
#include <xip/inventor/coregl/SoXipDrawImage.h>

SO_NODE_SOURCE(SoXipDrawImage);

void SoXipDrawImage::initClass() {
	SO_NODE_INIT_CLASS(SoXipDrawImage, SoNode, "SoNode");
}

SoXipDrawImage::SoXipDrawImage() {
	SO_NODE_CONSTRUCTOR(SoXipDrawImage);

	SO_NODE_ADD_FIELD(inputImage, (NULL));
	SO_NODE_ADD_FIELD(format, (RGB));

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
}

void SoXipDrawImage::GLRender(SoGLRenderAction* action) {
	SoXipDataImage *dataImage = inputImage.getValue();

	if (dataImage) {
		dataImage->ref();
		drawImage(dataImage->get());
		dataImage->unref();
	}
}

void SoXipDrawImage::drawImage(SbXipImage *image) {
	int dataType;
	const SbXipImageDimensions &dim = image->getDimStored();

	switch (image->getType()) {
		case SbXipImage::UNSIGNED_BYTE:
			dataType = GL_UNSIGNED_BYTE;
			break;
		case SbXipImage::BYTE:
			dataType = GL_BYTE;
			break;
		case SbXipImage::UNSIGNED_SHORT:
			dataType = GL_UNSIGNED_SHORT;
			break;
		case SbXipImage::SHORT:
			dataType = GL_SHORT;
			break;
		case SbXipImage::UNSIGNED_INT:
			dataType = GL_UNSIGNED_INT;
			break;
		case SbXipImage::INT:
			dataType = GL_INT;
			break;
		case SbXipImage::FLOAT:
			dataType = GL_FLOAT;
			break;
		default:
			SoDebugError::post(__FUNCTION__, "Unhandled type");
			return;
	}

	// copy the buffer
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels(dim[0], dim[1], format.getValue(), dataType, image->refBufferPtr());
}


