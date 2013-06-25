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
#include <xip/inventor/coregl/SoXipGetTransform.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoTextureMatrixElement.h>

SO_NODE_SOURCE(SoXipGetTransform);

SoXipGetTransform::SoXipGetTransform() {
	SO_NODE_CONSTRUCTOR(SoXipGetTransform);

	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, PROJECTION);
	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, MODEL);
	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, VIEW);
	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, MODELVIEW);
	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, MODELVIEWPROJECTION);
	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, TEXTURE);
	SO_NODE_SET_SF_ENUM_TYPE(matrixType, MatrixType);

	SO_NODE_ADD_FIELD(matrixType, (MODELVIEW));
	SO_NODE_ADD_FIELD(matrix, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(invert, (false));
}

void SoXipGetTransform::initClass() {
	SO_NODE_INIT_CLASS(SoXipGetTransform, SoNode, "SoNode");
}

void SoXipGetTransform::setMatrix(const SbMatrix &m) {
	if (invert.getValue())
		matrix.setValue(m.inverse());
	else
		matrix.setValue(m);
}

void SoXipGetTransform::GLRender(SoGLRenderAction* action) {
	switch (matrixType.getValue()) {
		case PROJECTION:
			setMatrix(SoProjectionMatrixElement::get(action->getState()));
			break;
		case MODEL:
			setMatrix(SoModelMatrixElement::get(action->getState()));
			break;
		case VIEW:
			setMatrix(SoViewingMatrixElement::get(action->getState()));
			break;
		case MODELVIEW:
			{
				SbMatrix product(SoModelMatrixElement::get(action->getState()));
				product *= SoViewingMatrixElement::get(action->getState());
				setMatrix(product);
			}
			break;
		case MODELVIEWPROJECTION:
			{
				SbMatrix product(SoModelMatrixElement::get(action->getState()));
				product *= SoViewingMatrixElement::get(action->getState());
				product *= SoProjectionMatrixElement::get(action->getState());
				setMatrix(product);
			}
			break;
		case TEXTURE:
			setMatrix(SoTextureMatrixElement::get(action->getState()));
			break;
	}
}



