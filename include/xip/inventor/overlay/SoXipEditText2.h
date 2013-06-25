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
#ifndef SOXIPEDITTEXT2_H
#define SOXIPEDITTEXT2_H

#include <string>
#include <Inventor/fields/SoSFBool.h>
#include <xip/inventor/overlay/SoXipText2.h>

class SoXipEditText2 : public SoXipText2
{
	SO_NODE_HEADER( SoXipEditText2 );

public:
	SoXipEditText2();

	SoSFBool		displayBBox;
	SoSFBool		isEditing;

	static void initClass();

protected:
	virtual ~SoXipEditText2();

	virtual SbBool isPicked( SoHandleEventAction* action ) const;

	virtual void GLRender( SoGLRenderAction *action );
	virtual void handleEvent( SoHandleEventAction* action );

	virtual void toggleEditing();
	virtual void onStringChange();

	int				mCursorPos;
	std::string		mEditString;	

private:
	static void editingSensorCB( void* userData, SoSensor* sensor );

	SoFieldSensor*	mEditingSensor;

};

#endif // SOXIPEDITTEXT2_H
