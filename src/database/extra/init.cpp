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
//#include <xip/system/GL/gl.h>
// #include "SoDoubleCalculator.h"

#include <xip/inventor/extra/xipivextra.h>
#include <Inventor/SoDB.h>

int XIPIVEXTRA_API xipivextra_init()
{
  static bool isInit = false;
  if (isInit)
    return 1;
  isInit = true;

  SoDB::init();

  //initialize elements
  // SoDoubleCalculator::initClass();

  return 1;
}

#ifdef WIN32

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        // automatic initialization for dynamic loading
        xipivextra_init();
    }

    return TRUE;
}

#else // WIN32

static int initted = FALSE; // a little protection--probably unnecessary

void __attribute__ ((constructor)) _init(void)
// don't write this if DllMain is to be used
{
    int err;

    // automatic initialization for dynamic loading
    xipivextra_init();
    
    initted = TRUE;
}

void __attribute__ ((destructor)) _fini(void)
{
}

//forcing initialization through static member (as workaround)
static const bool initMe = xipivextra_init();

#endif // WIN32
