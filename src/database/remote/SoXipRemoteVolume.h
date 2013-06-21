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
#ifndef SO_XIP_REMOTEVOLUME_H
#define SO_XIP_REMOTEVOLUME_H


#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include "SoXipDataConnection.h"

#include <xip/inventor/remote/XipRenderActionParams.h>
#include <xip/inventor/remote/XipRequestManager.h>

class XipDataConnectorBase;
class SoXipDataDicom;

//! volume renderer connecting to remote server
class SoXipRemoteVolume : public SoEngine
{
	//! Implements the runtime type system interface of this new node.
	SO_ENGINE_HEADER(SoXipRemoteVolume);

public:
	//! Constructor
	SoXipRemoteVolume();

	//! Initializes this class (called on dll initialization).
	static void initClass();

	//@{! Fields

	//! input containing volume information
	SFXipConnection volumeInput;

	//@}

	//! model matrix output field
	SoEngineOutput modelMatrixOutput;

	//! bits used output field
	SoEngineOutput bitsUsedOutput;

	//! dicom header field
	SoEngineOutput dicomHeader;

protected:
	//! Protected destructor
	virtual ~SoXipRemoteVolume();


	//! stream used to load the volume form the servler
	XipStreamBase *mStream;

	//! class containing information to send/receive to the server 
	XipTreeRequestSender mReqSender;
	XipTreeRequestReceiver mReqReceiver;

	//! This is called when an input value changes - we will use
	//! it to figure out which input was changed most recently
	virtual void inputChanged(SoField *whichField);

	//! Evaluation method
	virtual void evaluate();
 
private:

	//! Used to get needed information from the server
	void getModelMatrix();
	void getBitsUsed();
	void getDicomHeader();

	SoXipDataConnection  *mVol;
	SoXipDataDicom		 *mDicomData;
	XipDataConnectorBase *mDataConnector;
};

#endif // SO_XIP_REMOTEVOLUME_H
