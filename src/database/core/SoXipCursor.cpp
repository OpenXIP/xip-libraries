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

#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/fields/SoMFString.h>

SbString SoXipCursor::mCursor;
SbString SoXipCursor::mCursorClass;
SoMFString * SoXipCursor::mCursorField = 0;


void SoXipCursor::initClass()
{
    //on linux this additional init was required
    //this could potentially be related to our statically (forced) approach to call the init method of each library on unix systems - we may want to review this... 
	mCursor = SbString("");
	mCursorClass = SbString("");

	if (!mCursorField)
	{
		mCursorField = (SoMFString*) SoDB::createGlobalField(SbName("XipCursor"), SoMFString::getClassTypeId());
		update();
	}
}


void SoXipCursor::setCursor(const char *cursor)
{
	mCursor = SbString(cursor ? cursor : "");

	update();
}


void SoXipCursor::setClass(const char *cursorClass)
{
	mCursorClass = SbString(cursorClass ? cursorClass : "");

	update();
}

void SoXipCursor::update()
{
	if (mCursorField)
	{
		mCursorField->setNum(2);
		mCursorField->set1Value(0, mCursor);
		mCursorField->set1Value(1, mCursorClass);
	}
}
