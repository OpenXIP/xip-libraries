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
#ifndef SOXIPSUBKIT_H
#define SOXIPSUBKIT_H

#include <xip/inventor/core/SoXipKit.h>
#include <Inventor/nodes/SoGroup.h>

#define SO_XIP_KIT_ENTRY_HEADER(fieldContainerName)					\
	protected: SoNode* fieldContainerName;

#define SO_XIP_KIT_TYPE_ENTRY_HEADER(fieldContainerName,className)	\
	protected: class className* fieldContainerName;

#define SO_XIP_KIT_ADD_ENTRY(nodeName,nodeType,parent)				\
	{																\
		SoType t = SoType::fromName( SO__QUOTE(nodeType) );			\
		if( t.canCreateInstance() )									\
		{															\
			nodeName = (SoNode *) t.createInstance();				\
			SoGroup* parentGroup = (SoGroup *) parent;				\
			if( parentGroup )										\
				parentGroup->addChild( nodeName );					\
		}															\
	}

#define SO_XIP_KIT_ADD_TYPE_ENTRY(nodeName,nodeType,parent)			\
	{																\
		SoType t = SoType::fromName( SO__QUOTE(nodeType) );			\
		if( t.canCreateInstance() )									\
		{															\
			nodeName = (nodeType *) t.createInstance();				\
			SoGroup* parentGroup = (SoGroup *) parent;				\
			if( parentGroup )										\
				parentGroup->addChild( nodeName );					\
		}															\
	}

#endif // SOXIPSUBKIT_H
