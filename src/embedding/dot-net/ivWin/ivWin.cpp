// This is the main DLL file.

#include "stdafx.h"
#using <mscorlib.dll>
#using <System.dll>
#include <vcclr.h>
#include <windows.h>
#include "ivWin.h"
#include "ivThreadWnd.hpp"
#include <memory>

#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/SoInput.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/nodes/SoNode.h>



namespace Renderer
{


static char *convertToMbs(String ^str)
{
	if (!str) return 0;

	pin_ptr<const wchar_t> wch = PtrToStringChars(str);

	size_t convertedChars = 0;
	size_t sizeInBytes = ((str->Length + 1) * 2);
	errno_t err = 0;
	char *ch = new char[sizeInBytes];
	err = wcstombs_s(&convertedChars, ch, sizeInBytes, wch, sizeInBytes);
	if (err != 0)
	{
		if (ch) delete [] ch;
		return 0;
	}

	return ch;
}


void splitName(String ^name, std::string &node, std::string &field)
{
	char *tmp = 0;

	node.erase();
	field.erase();

	std::auto_ptr<char> str(convertToMbs(name));
	if (!str.get()) return;

	// find delimiter dot that separates field from node
	char *delim = strchr(str.get(), '.');
	if (!delim)
	{
		node = std::string(str.get());
	}
	else
	{
		*delim = 0;
		field = std::string(delim + 1);
		node = std::string(str.get());
	}
}


ivChildWindow::ivChildWindow()
{
	mWindow = 0;

	if (!SoDB::isInitialized())
	{
		SoDB::init();
		SoInteraction::init();
	}
}


ivChildWindow::~ivChildWindow()
{
	destroy();
}


bool ivChildWindow::create(IntPtr parent, String^ instance)
{
	// already initialized
	if (mWindow) return false;

	pin_ptr<const wchar_t> instanceStr = PtrToStringChars(instance);
	HWND hWnd = (HWND) parent.ToPointer();

	RECT rect;
	::GetClientRect(hWnd, &rect);

	mWindow = new ivThreadWnd(instanceStr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hWnd, WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	if (!mWindow)
		return false;

	return (mWindow->createWindow() == TRUE);
}


void ivChildWindow::destroy()
{
	if (mWindow)
	{
		delete mWindow;
		mWindow = 0;
	}
}


void ivChildWindow::show(bool visible)
{
	if (mWindow)
	{
		mWindow->showWindow(visible ? SW_SHOW : SW_HIDE);
	}
}


bool ivChildWindow::loadGraph(String^ graph)
{
	std::auto_ptr<char> str(convertToMbs(graph));
	if (!str.get() || !mWindow) return false;

	SoSeparator *rootNode = mWindow->getRoot();
	if (!rootNode) return false;
	rootNode->removeAllChildren();

	SoInput in;
	if (strncmp(str.get(), "#Inventor V2.1", 14) == 0)
	{
		in.setBuffer(str.get(), strlen(str.get())); // string
	}
	else
	{
		in.openFile(str.get()); // file
	}

	SoSeparator *topNode = SoDB::readAll(&in);
	if (topNode)
	{
		rootNode->addChild(topNode);
	}

	return true;
}


bool ivChildWindow::loadLibraries(String^ libs)
{
	// pre-load all libraries given in the arguments (separated by comma)
	bool loaded = true;
	pin_ptr<const wchar_t> wch = PtrToStringChars(libs);
	std::wstring libraries(wch);

	while (libraries.length() > 0)
	{
		int pos = libraries.find(',');
		std::wstring tmp = libraries.substr(0, pos > 0 ? pos : libraries.length());
		libraries.erase(0, pos > 0 ? pos + 1 : libraries.length());

		HMODULE hm = ::LoadLibraryW(tmp.c_str());
		if (!hm)
		{
			loaded = false;
			char errMsg[2 * MAX_PATH];
			DWORD err = ::GetLastError();
			LPSTR s = 0;
			if (FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
					err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &s, 0, NULL) == 0)
			{ 
				// failed
				_snprintf_s(errMsg, 2 * MAX_PATH, "radAppletInventor: Failed to load library '%S' - %d\n", tmp.c_str(), err, err);
				::OutputDebugStringA(errMsg);
			}
			else
			{ 
				// succeeded
				_snprintf_s(errMsg, 2 * MAX_PATH, "radAppletInventor: Failed to load library '%S' - %d / %s", tmp.c_str(), err, s);
				::OutputDebugStringA(errMsg);
				::LocalFree(s);
			}
		}
	}

	return loaded;
}


String^ ivChildWindow::get(String^ param)
{
	std::string nodeName, fieldName;
	splitName(param, nodeName, fieldName);

	SoFieldContainer *node = SoNode::getByName(nodeName.c_str());
	if (!node)
	{
		// maybe an engine?
		node = SoEngine::getByName(nodeName.c_str());
	}

	if (node)
	{
		if (fieldName.length() == 0)
		{
			// no field specified, return pointer to class
			char address[20];
			_snprintf_s(address, 20, "0x%p", node);

			return gcnew String(address);
		}
		else
		{
			SoField *field = node->getField(fieldName.c_str());
			if (field)
			{
				SbString str;
				field->get(str);

				return gcnew String(str.getString());
			}
		}
	}

	return "";
}


bool ivChildWindow::set(String^ param, String^ value)
{
	// set generic OIV parameter
	bool isValueSet = false;
	std::string nodeName, fieldName;
	splitName(param, nodeName, fieldName);

	SoFieldContainer *node = SoNode::getByName(nodeName.c_str());
	if (!node)
	{
		// maybe an engine?
		node = SoEngine::getByName(nodeName.c_str());
	}

	if (node)
	{
		std::auto_ptr<char> str(convertToMbs(value));
		if (str.get())
		{
			SoField *field = node->getField(fieldName.c_str());
			if (field)
			{
				if (strlen(str.get()) > 0)
				{
					SbString valueString;
					field->get(valueString);

					if (valueString != SbString(str.get()))
					{
						if (field->set(str.get()))
							isValueSet = true;
					}
				}
				else
				{
					field->touch();
					isValueSet = false;
				}
			}
			else
			{
				if (node->set(str.get()))
					isValueSet = false;
			}
		}
	}

	return isValueSet;
}

}
