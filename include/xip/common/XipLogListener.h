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

#ifndef XIPLOGLISTENER_H
#define XIPLOGLISTENER_H

#include <xip/common/XipCommon.h>
#include <xip/common/XipLog.h>

#include <stdio.h>
#include <map>

class XIPCOMMON_API XipLogListener
{

public:
    // Constructor.
    XipLogListener(){}

    // Destructor.
    virtual ~XipLogListener(){}

    virtual void handleError(const XipLogEntry& entry) = 0;
    virtual void set(int property, const wchar_t* value) = 0;

    //set the log type below which to record
    //void setLogLevel(XipLogLevel level) {XipLog::sGlobalLogLevel = level;}

private:
};

#endif