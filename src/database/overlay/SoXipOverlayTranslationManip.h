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
/**
*	@file    SoXipOverlayTranslationManip.h
*	@brief   Declaration of the SoXipOverlayTranslationManip class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYTRANSLATIONMANIP_H
#define SOXIPOVERLAYTRANSLATIONMANIP_H

#include <xip/inventor/overlay/SoXipOverlayManipBase.h>
/**
*	@class SoXipOverlayTranslationManip
*
* Implementation of a translation manipulator. When mouse cursor
* approaches a shape contour, the manipulator gets activated.
* If current selection has multiple shapes, then the translation
* is applied to all.
*
**/
class SoXipOverlayTranslationManip : public SoXipOverlayManipBase
{
	SO_NODE_HEADER( SoXipOverlayTranslationManip );

public:
	/// Constructor
	SoXipOverlayTranslationManip();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlayTranslationManip();

	virtual void handleEvent( SoHandleEventAction* action );

	/// Can translate ?
	SbBool mCanTranslate;

};

#endif // SOXIPOVERLAYTRANSLATIONMANIP_H
