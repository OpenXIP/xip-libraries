// ivWin.h

#pragma once

using namespace System;

class ivThreadWnd;

namespace Renderer
{

	public ref class ivChildWindow
	{
	public:
		ivChildWindow();
		virtual ~ivChildWindow();

		// window
		virtual bool create(IntPtr parent, String^ instance);
		virtual void destroy();
		virtual void show(bool visible);

		// loads Inventor extension libraries
		virtual bool loadLibraries(String^ libs);

		// loads scene graph (call after window is created)
		virtual bool loadGraph(String^ graph);

		// generic parameter interfaces
		virtual String^ get(String^ param);
		virtual bool set(String^ param, String^ value);

	private:
		ivThreadWnd *mWindow;
	};

}
