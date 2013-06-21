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
#ifndef XIPRENDERTASK_H
#define XIPRENDERTASK_H

#include <winsock2.h>
#include <vector>
#include <xip/inventor/remote/XipRequestManager.h>
#include <xip/inventor/remote/jpegWrapper/bufferImage.h>
#include "XipRenderAction.h"


// forward declarations
class XipStreamBase;
struct XipDicomHeader;

class XipRenderTask  
{
public:
	XipRenderTask(XipStreamBase *stream);
	virtual ~XipRenderTask();

	virtual void run();

protected:
	virtual int processRequest();
	virtual bool logon();
	virtual bool validation();
	virtual bool smartValidation();
	virtual int  render();
    virtual void setLut();
	virtual void raySurfaceIntersections();
	virtual void getModelMatrix();
	virtual void getBitsUsed();
    virtual void loadDicom();

    void initialize();
    void loadDLLs();

    // member variables
	XipStreamBase               *mStream;
    XipTreeRequestSender        reqSender;
	XipTreeRequestReceiver      reqReceiver;

	int newVolume;
	int actualPlane ;
	int cmpQty;

	bool mCvISSMART;
	bool svTotalMismatch;

    XipRenderAction     *mRenderer;
};

#endif // XIPRENDERTASK_H
