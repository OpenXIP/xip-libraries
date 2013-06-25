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
#ifndef  SOXIPSUBDATA_H
#define  SOXIPSUBDATA_H

#include <Inventor/SbString.h>

#define XIP_DATA_INIT_CLASS(classname, parentclass, parentname) \
    classname::classTypeId = SoType::createType(parentclass::getClassTypeId(), SbName(SO__QUOTE(classname)));

#define XIP_DATA_HEADER(classname) \
	public: \
		static SoType getClassTypeId(void); \
		virtual SoType getTypeId(void) const; \
	private: \
		static SoType classTypeId

#define XIP_DATA_SOURCE(classname) \
	SoType classname::getClassTypeId(void) { return classname::classTypeId; } \
	SoType classname::getTypeId(void) const { return classname::classTypeId; } \
	SoType classname::classTypeId;

#define XIP_DATA_CONSTRUCTOR(className)	\
	// nothing to do for the constructor so far


#endif /* SOXIPSUBDATA_H */

