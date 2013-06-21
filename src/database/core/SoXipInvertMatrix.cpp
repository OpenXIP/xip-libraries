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

#include "SoXipInvertMatrix.h"

SO_ENGINE_SOURCE(SoXipInvertMatrix);

SoXipInvertMatrix::SoXipInvertMatrix() {
	SO_ENGINE_CONSTRUCTOR(SoXipInvertMatrix);

	SO_ENGINE_ADD_INPUT(matrix, (SbMatrix::identity()));
    SO_ENGINE_ADD_OUTPUT(inverse, SoSFMatrix);
}


void SoXipInvertMatrix::initClass() {
	SO_ENGINE_INIT_CLASS(SoXipInvertMatrix, SoEngine, "Engine");
}


void SoXipInvertMatrix::evaluate() {
#if 0
	SbMatrix result(left.getValue());
	result.multRight(right.getValue());
	SO_ENGINE_OUTPUT(output, SoSFMatrix, setValue(result));
    SO_ENGINE_OUTPUT(inverse, SoSFMatrix, setValue(result.inverse()));
#else
    SO_ENGINE_OUTPUT(inverse, SoSFMatrix, setValue(matrix.getValue().inverse()));
#endif
}
