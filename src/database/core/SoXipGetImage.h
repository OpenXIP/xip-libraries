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

#ifndef SOXIPGETIMAGE_H
#define SOXIPGETIMAGE_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFShort.h>

class SoXipGetImage : public SoNode  
{
	SO_NODE_HEADER( SoXipGetImage );

public:
	SoXipGetImage();

	static void initClass();

	SoXipSFDataImage	image;
	SoSFShort			sliceIndex;
	SoSFShort			numSlices;
	SoSFShort			imageIndex;
	SoSFShort			numImages;

protected:
	virtual ~SoXipGetImage();

	void extractInfo( SoAction* action );

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );
	virtual void pick( SoPickAction* action );
	virtual void callback( SoCallbackAction* action );
};

#endif // SOXIPGETIMAGE_H
