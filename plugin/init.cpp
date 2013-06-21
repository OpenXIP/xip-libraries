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
#include <Inventor/fields/SoSubField.h>
#include "SoXipPluginSlicer.h"
#include "xipplugin.h"

int XIPPLUGIN_API xipplugin_init()
{
	SoXipPluginSlicer::initClass();
	return 1;
}

#ifdef WIN32

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		if (SoDB::isInitialized())
		{
			// automatic initialization for dynamic loading
			xipplugin_init();
		}
	}

	return TRUE;
}

#else // not WIN32

static int initted = FALSE; // a little protection--probably unnecessary

void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{
  int err;

	if (SoDB::isInitialized())
	  {
		// automatic initialization for dynamic loading
		xipplugin_init();
	  }
    
	initted = TRUE;
  //return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
	//printf ("fini print.\n");
}

#endif // WIN32

