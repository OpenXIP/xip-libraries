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
#include <xip/inventor/coregl/SoXipSetTransform.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoTextureMatrixElement.h>

SO_NODE_SOURCE(SoXipSetTransform);

SoXipSetTransform::SoXipSetTransform() {
	SO_NODE_CONSTRUCTOR(SoXipSetTransform);

	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, PROJECTION);
	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, MODEL);
	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, VIEW);
	SO_NODE_DEFINE_ENUM_VALUE(MatrixType, TEXTURE);
	SO_NODE_SET_SF_ENUM_TYPE(matrixType, MatrixType);

	SO_NODE_ADD_FIELD(matrixType, (MODEL));
	SO_NODE_ADD_FIELD(matrix, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(multiply, (false));
}

void SoXipSetTransform::initClass() {
	SO_NODE_INIT_CLASS(SoXipSetTransform, SoNode, "SoNode");
}

void SoXipSetTransform::GLRender(SoGLRenderAction* action) {
	const SbBool &doMultiply = multiply.getValue();
	switch (matrixType.getValue()) {
		case PROJECTION:
			if (doMultiply) {
				SbMatrix product(SoProjectionMatrixElement::get(action->getState()));
				product *= matrix.getValue();
				SoProjectionMatrixElement::set(action->getState(), this, product);
			}
			else
				SoProjectionMatrixElement::set(action->getState(), this, matrix.getValue());
			break;
		case MODEL:
			if (doMultiply)
				SoModelMatrixElement::mult(action->getState(), this, matrix.getValue());
			else
				SoModelMatrixElement::set(action->getState(), this, matrix.getValue());
			break;
		case VIEW:
			if (doMultiply) {
				SbMatrix product(SoViewingMatrixElement::get(action->getState()));
				product *= matrix.getValue();
				SoViewingMatrixElement::set(action->getState(), this, product);
			}
			else
				SoViewingMatrixElement::set(action->getState(), this, matrix.getValue());
			break;
		case TEXTURE:
			if (doMultiply)
				SoTextureMatrixElement::mult(action->getState(), this, matrix.getValue());
			else {
				SoTextureMatrixElement::makeIdentity(action->getState(), this);
				SoTextureMatrixElement::mult(action->getState(), this, matrix.getValue());
			}
			break;
	}
}



