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

/*[ Compilation unit ----------------------------------------------------------

Component:
	prototype

Name:
	ivWndArray.hpp

Author:
	Thomas Moeller; Siemens AG SCR IM

Language:
	C++

Creation Date:
	December 27, 2002

Description:
	Declaration of ivWndArray class.

Requirement Key:


Hazard Key:
	None

Include:
	

	Copyright (C) Siemens AG 2008-2008 All Rights Reserved

-----------------------------------------------------------------------------*/
/*] END */

#ifndef IVTWIN32WNDWARRAY_HPP
#define IVTWIN32WNDWARRAY_HPP

#include <windows.h>


/*[ Class ---------------------------------------------------------------------

Name:
	ivWndArray - Utility class to manage a list of windows.

Description:
	Utility class for managing a list of windows. This class is used by ivtWin32Wnd
    to map Windows window messages back to a class that has created the window.
	
Base Classes:

Include:
	#include <IVT/Kernel/SceneGraph/ivtWin32Wnd.hpp>

Requirement Key:

  
Hazard Key:
	None

API:
	no

Derivable:
	yes

-----------------------------------------------------------------------------*/
class ivWndArray
/*] END Class */
{
public:
    ivWndArray();
    virtual ~ivWndArray();

	virtual bool add(HWND hWnd, void *ptr);
	virtual bool remove(HWND hWnd);
	virtual void *getPtr(HWND hWnd) const;
	virtual HWND getDefaultWnd() const;
	virtual bool isEmpty() const;

protected:
	int getSize() const;

    struct ArrayType
	{
		HWND hWnd;
		void *ptr;
	} mWindows[16];
};

#endif
