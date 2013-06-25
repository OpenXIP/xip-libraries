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
#ifndef SOXIPCURSOR_H
#define SOXIPCURSOR_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/SbString.h>
class SoMFString;


class XIPIVCORE_API SoXipCursor
{
public:
	static void initClass();

	static void setCursor(const char *cursor = 0);
	static void setClass(const char *cursorClass = 0);
	static void update();

protected:
	static SbString mCursor;
	static SbString mCursorClass;
	static SoMFString *mCursorField;
};

#endif // SOXIPCURSOR_H
