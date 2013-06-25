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
#ifndef SOXIPCLIENTBASE_H
#define SOXIPCLIENTBASE_H

class XipStreamSockets;
class XipStreamLengthPackage;
class SoFieldSensor;

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/sensors/SoSensor.h>
#include <xip/inventor/remote/XipRequestManager.h>

#include <vector>

#if !defined(WINDOWS) && !defined(_WIN32)
	#define INVALID_SOCKET -1
#endif

//! Client node connecting to RenderNode server
class SoXipClientBase : public SoEngine
{
	//! Implements the runtime type system interface of this new node.
	SO_ENGINE_ABSTRACT_HEADER(SoXipClientBase);

public:

	//! possible state of client socket
	enum State {                
		DISCONNECTED           = 0x01,
		CONNECTED              = 0x02,
		CONNECTION_ERROR       = 0x03,
		AUTHENTIFICATION_ERROR = 0x04
	};

	//! possible state of data loading
	enum DState {                
		DATA_EMPTY = 0x01,
		DATA_OK    = 0x02,
		DATA_ERROR = 0x03
	};

	//! possible limitation of volume size 
	enum VSizelimit {                
		LIMIT    = 0x01,
		TARGET   = 0x02,
		ORIGINAL = 0x03
	};

	//@{! Fields

	//! adress of the remote server
	SoSFString serverAddress;

	//! port of the remote server  
	SoSFInt32 serverPort;

	//! Differents possibles states of the connection
	SoSFBitMask connectionState;  
	
    //! the location of the volume data on the server
    SoSFString dataLocation;

	//! Differents possibles states of the data loading
	SoSFBitMask dataState;   

	//! used to choose limitation of volume loaded
	SoSFEnum volumeTargetSize;

	//! chosen width if volume is size limited 
	SoSFInt32 volumeWidth;

	//! chosen height if volume is size limited 
	SoSFInt32 volumeHeight;

	//! chosen depth if volume is size limited 
	SoSFInt32 volumeDepth;

	//! trigger to manually update data from the server
	SoSFTrigger volumeUpdate;

	//@}


	//! Initializes this class (called on dll initialization).
	static void  initClass();


protected:
	//! This is called when an input value changes - we will use
	//! it to figure out which input was changed most recently
	virtual void inputChanged(SoField *whichField);

	//! Protected Constructor because of abstract class
	SoXipClientBase();

	//! Protected destructor
	virtual ~SoXipClientBase();

	//! Called to load wanted data from the server
	virtual int loadData();

	//! Called when field LoadDataTrigger changed
	void loadDataTriggerCall();

	//! Evaluation method
	virtual void evaluate();

	//! Used to create a radStream using the socket
	XipStreamSockets *mSocketStream;

	XipStreamLengthPackage *mStreamLength;
	/***/
	XipStreamLengthPackage *mStreamLength2;
	/***/

	//! Socket used by the client
	#if defined(WINDOWS) || defined(_WIN32)
		SOCKET mClientSocket;
	#else
		unsigned int mClientSocket;
	#endif

	//! Flag to know if the volumeUpdate trigger (button)
	//! has been touched and the volume data needs to be
	//! reloaded in the next time evaluate() is called.
	bool mNeedVolumeUpdate;

	//! Used to know if one of the fields value has change
	SbString mServerAddress;
	int mServerPort;
    SbString    mDataLocation;

	//! used to send/receive request using the stream
	XipTreeRequestSender mReqSender;
	XipTreeRequestReceiver mReqReceiver;
    std::vector<SoFieldSensor*>     mInputSensors;

	float	mRampWidth;
	float	mRampCenter;

private:
	//! Called to initialize WinSock 
	int initialize();

	//! Called to liberate socket before closing
	void finalize();

	//! Method to initialize and connect the socket
	int initializeSocket();

	//! Method to close the socket
	void disconnectSocket();

	//! Called to identify the client on the server
	int authenticate();

	//! Called to flush the stream
	void flush();

	//! Called to clean the socket before closing it
	void terminate();

	//! Called to clean the present c++ pointer
	void deletePointer();

	//! Called when field ConnectTrigger changed
	void connectTriggerCall();

	//! Called when field DeconnectTrigger changed
	void disconnectTriggerCall();

    static void fieldSensorCBFunc(void *usr, SoSensor *sensor);
};

#endif // SOXIPCLIENTBASE_H
