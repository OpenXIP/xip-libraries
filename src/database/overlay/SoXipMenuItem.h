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
#ifndef SOXIPMENUITEM_H
#define SOXIPMENUITEM_H

#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFUInt32.h>
#include "SoXipMenuItemBase.h"

class SoXipMenuItem : public SoXipMenuItemBase
{
	SO_NODE_HEADER( SoXipMenuItem );

	SO_XIP_KIT_TYPE_ENTRY_HEADER( mVertices, SoVertexProperty );
	SO_XIP_KIT_TYPE_ENTRY_HEADER(    mFaces, SoIndexedFaceSet );

	SO_XIP_KIT_ENTRY_HEADER( mIconOffset );
	SO_XIP_KIT_ENTRY_HEADER( mIconSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mIconSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mIconComplexity );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mIconTexture, SoXipIcon );
	SO_XIP_KIT_ENTRY_HEADER( mIconTextCoords );
	SO_XIP_KIT_ENTRY_HEADER( mIconCoords );
	SO_XIP_KIT_ENTRY_HEADER( mIconFaces );

	SO_XIP_KIT_ENTRY_HEADER( mTextSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mTextOffset );
	SO_XIP_KIT_ENTRY_HEADER( mTextMaterial );
	SO_XIP_KIT_ENTRY_HEADER( mText );

public:
	SoXipMenuItem();

	static void initClass();

	virtual float getWidth() const;
	virtual float getHeight() const;

	virtual void updateCaption();
	virtual void updateIcon();

protected:
	~SoXipMenuItem();

	virtual void GLRender( SoGLRenderAction* action );

	virtual void onEnable();
	virtual void onFocus();

};

#endif // SOXIPMENUITEM_H
