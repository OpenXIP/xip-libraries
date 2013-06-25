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
#ifndef SOXIPDISPLAYIMAGETEXT_H
#define SOXIPDISPLAYIMAGETEXT_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFBool.h>

class SoXipDisplayImageText : public SoBaseKit
{
	SO_KIT_HEADER( SoXipDisplayImageText );

	SO_KIT_CATALOG_ENTRY_HEADER( separator );
	SO_KIT_CATALOG_ENTRY_HEADER( orthoCamera );

	// upper left
	SO_KIT_CATALOG_ENTRY_HEADER( separatorUL );
	SO_KIT_CATALOG_ENTRY_HEADER( materialUL );
	SO_KIT_CATALOG_ENTRY_HEADER( translationUL );
	SO_KIT_CATALOG_ENTRY_HEADER( textUL );

	// upper centre
	SO_KIT_CATALOG_ENTRY_HEADER( separatorUC );
	SO_KIT_CATALOG_ENTRY_HEADER( materialUC );
	SO_KIT_CATALOG_ENTRY_HEADER( translationUC );
	SO_KIT_CATALOG_ENTRY_HEADER( textUC );

	// upper right
	SO_KIT_CATALOG_ENTRY_HEADER( separatorUR );
	SO_KIT_CATALOG_ENTRY_HEADER( materialUR );
	SO_KIT_CATALOG_ENTRY_HEADER( translationUR );
	SO_KIT_CATALOG_ENTRY_HEADER( textUR );

	// centre left
	SO_KIT_CATALOG_ENTRY_HEADER( separatorCL );
	SO_KIT_CATALOG_ENTRY_HEADER( materialCL );
	SO_KIT_CATALOG_ENTRY_HEADER( translationCL );
	SO_KIT_CATALOG_ENTRY_HEADER( textCL );

	// centre right
	SO_KIT_CATALOG_ENTRY_HEADER( separatorCR );
	SO_KIT_CATALOG_ENTRY_HEADER( materialCR );
	SO_KIT_CATALOG_ENTRY_HEADER( translationCR );
	SO_KIT_CATALOG_ENTRY_HEADER( textCR );

	// lower left
	SO_KIT_CATALOG_ENTRY_HEADER( separatorLL );
	SO_KIT_CATALOG_ENTRY_HEADER( materialLL );
	SO_KIT_CATALOG_ENTRY_HEADER( translationLL );
	SO_KIT_CATALOG_ENTRY_HEADER( textLL );

	// lower center
	SO_KIT_CATALOG_ENTRY_HEADER( separatorLC );
	SO_KIT_CATALOG_ENTRY_HEADER( materialLC );
	SO_KIT_CATALOG_ENTRY_HEADER( translationLC );
	SO_KIT_CATALOG_ENTRY_HEADER( textLC );

	// lower right
	SO_KIT_CATALOG_ENTRY_HEADER( separatorLR );
	SO_KIT_CATALOG_ENTRY_HEADER( materialLR );
	SO_KIT_CATALOG_ENTRY_HEADER( translationLR );
	SO_KIT_CATALOG_ENTRY_HEADER( textLR );

public:
	/// Constructor
	SoXipDisplayImageText();

	SoSFBool			on;
	SoSFBool			dogEar;

	/// static initialization method
	static void initClass();

protected:
	// destructor
	virtual ~SoXipDisplayImageText();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void getBoundingBox( SoGetBoundingBoxAction* action );

	SoNode* getTextNode( int position );
	SoNode* getMaterialNode( int position );
	int getDogEarSize( const SbViewportRegion& viewportRegion ) const;

};

#endif // SOXIPDISPLAYIMAGETEXT_H
