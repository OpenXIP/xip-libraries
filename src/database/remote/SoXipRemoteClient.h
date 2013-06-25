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
#ifndef __SOXIPREMOTECLIENT_H__
#define __SOXIPREMOTECLIENT_H__

// Local includes
#include "SoXipClientBase.h"
#include "SoXipDataConnection.h"

#include <Inventor/fields/SoSFBool.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <Inventor/fields/SoSFMatrix.h>

//! Derived client class
class SoXipRemoteClient : public SoXipClientBase
{
	//! Implements the runtime type system interface of this new node.
	SO_ENGINE_HEADER(SoXipRemoteClient);

public:
	//! Constructor
	SoXipRemoteClient();

	//! Initializes this class (called on dll initialization).
	static void  initClass();

    //! volume model matrix
    SoEngineOutput modelMatrixOutput;

	//! Connection engine output field
	SoEngineOutput connectionOutput;

protected:
	//! Protected destructor
	virtual ~SoXipRemoteClient();

	//! Called to load wanted data from the server
	virtual int loadData();

private:

	// Simple volume
	XipDataConnection *mVolumeData;



	//! delete the volume information data if exist
	void deleteData();

	
	//! Stored volume loaded from the server
	SoXipDataImage *dataVolume;

	//! Called to detach the SoIvtDataVolume from the client
	void unrefData();
};

#endif // __SOXIPREMOTECLIENT_H__

