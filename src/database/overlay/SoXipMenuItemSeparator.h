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
#ifndef SOXIPMENUITEMSEPARATOR_H
#define SOXIPMENUITEMSEPARATOR_H

#include "SoXipMenuItemBase.h"

class SoXipMenuItemSeparator : public SoXipMenuItemBase
{
	SO_NODE_HEADER( SoXipMenuItemSeparator );

	SO_XIP_KIT_ENTRY_HEADER( mFaceSeparator );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mVertices, SoVertexProperty );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mFaces, SoIndexedFaceSet );

	SO_XIP_KIT_ENTRY_HEADER( mLineSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mLineMaterial );
	SO_XIP_KIT_ENTRY_HEADER( mLineStyle );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mLineCoords, SoCoordinate3 );
	SO_XIP_KIT_ENTRY_HEADER( mLineSet );
	

public:
	SoXipMenuItemSeparator();

	static void initClass();

	virtual float getWidth() const;
	virtual float getHeight() const;

protected:
	~SoXipMenuItemSeparator();

};

#endif // SOXIPMENUITEMSEPARATOR_H
