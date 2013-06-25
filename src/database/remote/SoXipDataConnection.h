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
#ifndef SO_XIP_DATACONNECTION_H
#define SO_XIP_DATACONNECTION_H

#include <Inventor/fields/SoSubField.h>
#include <xip/inventor/core/SoXipSFData.h>
#include <xip/inventor/core/SoXipData.h>
#include <xip/inventor/core/SoXipSubData.h>
#include <xip/inventor/remote/XipStream.h>

class XipDataConnection
{
public:

	//stream used to load volume form the server
	XipStreamBase	*mStream;

	XipDataConnection()
    : mStream(NULL)
    {
    }

    XipDataConnection(XipStreamBase *stream)
    : mStream(stream)
    {
    }
};


class SoXipDataConnection : public SoXipData
{
	XIP_DATA_HEADER(SoXipDataConnection);

public:
	SoXipDataConnection();
	static void initClass();

	virtual XipDataConnection *get() const;
	virtual void set(XipDataConnection *connection);

protected:
	virtual ~SoXipDataConnection();

	XipDataConnection *mConnection;
};


class SFXipConnection : public SoXipSFData 
{

	XIP_SFDATA_HEADER(SFXipConnection, SoXipDataConnection);
};


#endif // SO_XIP_DATACONNECTION_H

