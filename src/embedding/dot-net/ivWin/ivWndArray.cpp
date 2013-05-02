/*[ Compilation unit ----------------------------------------------------------

Component:
	prototype

Name:
	ivWndArray.cpp

Author:
	Thomas Moeller; Siemens AG SCR IM

Language:
	C++

Creation Date:
	December 27, 2002

Description:
	Implementation of ivWndArray class.

Requirement Key:


Hazard Key:
	None

Include:
	

	Copyright (C) Siemens AG 2008-2008 All Rights Reserved

-----------------------------------------------------------------------------*/
/*] END */

#pragma unmanaged

#include "stdafx.h"
#include <windows.h>
#include "ivWndArray.hpp"


/*[ Method --------------------------------------------------------------------

Name:
	ivWndArray::ivWndArray

Description:
	Constructor.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
ivWndArray::ivWndArray()
/*] END Method */
{
	for (int i = 0; i < this->getSize(); i++)
	{
		mWindows[i].hWnd = 0;
		mWindows[i].ptr = NULL;
	}	
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWndArray::~ivWndArray

Description:
	Destructor.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
ivWndArray::~ivWndArray()
/*] END Method */
{
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWndArray::add

Description:
	Adds a window to the array.

Arguments:
  - hWnd
    Window handle.
  - ptr
    Class pointer associated with handle.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
bool ivWndArray::add(HWND hWnd, void *ptr)
/*] END Method */
{
	for (int i = 0; i < this->getSize(); i++)
	{
		if (!mWindows[i].hWnd)
		{
			mWindows[i].hWnd = hWnd;
			mWindows[i].ptr = ptr;

			return TRUE;
		}
	}

	return FALSE;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWndArray::remove

Description:
	Removes a window from the array.

Arguments:
  - hWnd
    Window handle.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
bool ivWndArray::remove(HWND hWnd)
/*] END Method */
{
	for (int i = 0; i < this->getSize(); i++)
	{
		if (mWindows[i].hWnd == hWnd)
		{
			mWindows[i].ptr = NULL;
			mWindows[i].hWnd = NULL;

			return TRUE;
		}
	}

	return FALSE;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWndArray::getPtr

Description:
	Retrieves a class pointer associated with a window handle. If the provided
	window handle is NULL the first window in the list is returned.

Arguments:
  - hWnd
    Window handle.

Return:
    Class pointer or NULL if window does not exist.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void* ivWndArray::getPtr(HWND hWnd) const
/*] END Method */
{
	for (int i = 0; i < this->getSize(); i++)
	{
		if (mWindows[i].hWnd)
		{
			if (!hWnd || (mWindows[i].hWnd == hWnd))
			{
				return mWindows[i].ptr;
			}
		}
	}

	return NULL;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWndArray::getDefaultWnd

Description:
	Retrieves the window handle of the default window. The default window is the
	first window in the window list whose handle is not zero.

Return:
    Default window's window handle.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
HWND ivWndArray::getDefaultWnd() const
/*] END Method */
{
	for (int i = 0; i < this->getSize(); i++)
	{
		if (mWindows[i].hWnd)
		{
			return mWindows[i].hWnd;
		}
	}

	return NULL;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWndArray::isEmpty

Description:
	Indicates is the array of windows is empty.

Return:
    Returns TRUE if the array is empty, otherwise FALSE.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
bool ivWndArray::isEmpty() const
/*] END Method */
{
	for (int i = 0; i < this->getSize(); i++)
	{
		if (mWindows[i].hWnd)
		{
			return FALSE;
		}
	}

	return TRUE;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWndArray::getSize

Description:
	Returns the max. size of the window array.

Return:
    Max. size of the window array.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
inline int ivWndArray::getSize() const
/*] END Method */
{
	return (sizeof(mWindows) / sizeof(ArrayType));
}

