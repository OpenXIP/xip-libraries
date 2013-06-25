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
#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/remote/xipivremote.h>

#include "SoXipClientBase.h"
#include "SoXipDataConnection.h"
#include "SoXipRemoteClient.h"
#include "SoXipRemoteVolRender.h"
#include "SoXipRemoteLut.h"
#include "SoXipClientElement.h"

int XIPIVREMOTE_API xipivremote_init()
{
	static bool isInit = false;
	if(isInit)
		return 1;
	isInit = true;

	xipivcore_init();

    SoXipClientElement::initClass();
    SoXipClientBase::initClass();
	SFXipConnection::initClass();
	SoXipRemoteClient::initClass();
	SoXipRemoteVolRender::initClass();
	SoXipRemoteLut::initClass();

	return 1;
}

#ifdef WIN32

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
		xipivremote_init();

	return TRUE;
}

#else //UNIX

static int initted = FALSE;    // a little protection--probably unnecessary
void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{

	int err;



	xipivremote_init();


	initted = TRUE;
	//return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
   //printf ("fini print.\n");
}

//forcing initialization through static member (as workaround)
static const bool initMe = xipivremote_init();


#endif //WIN32
