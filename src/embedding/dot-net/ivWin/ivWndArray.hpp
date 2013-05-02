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
