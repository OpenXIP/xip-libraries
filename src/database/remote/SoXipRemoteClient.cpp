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

// Local includes
#include "SoXipRemoteClient.h"

#include <Inventor/fields/SoSFMatrix.h>
#include <xip/inventor/remote/XipRenderActionParams.h>


SO_ENGINE_SOURCE(SoXipRemoteClient)


// --------------------------------------------------------------------------
//! Initializes this class. Called on dll initialization.
// --------------------------------------------------------------------------
void SoXipRemoteClient::initClass()
{
	
	SO_ENGINE_INIT_CLASS(SoXipRemoteClient, SoXipClientBase, "SoXipClientBase");
}

// --------------------------------------------------------------------------
//! Constructor, creates fields
// --------------------------------------------------------------------------
SoXipRemoteClient::SoXipRemoteClient()
: SoXipClientBase()
{
	// Execute inventor internal stuff for node construction.
	SO_ENGINE_CONSTRUCTOR(SoXipRemoteClient);

	SO_ENGINE_ADD_OUTPUT(connectionOutput, SFXipConnection);

    SO_ENGINE_ADD_OUTPUT(modelMatrixOutput, SoSFMatrix);

	mVolumeData = NULL;

}

// --------------------------------------------------------------------------
//! Protected destructor to cleans up internally created nodes and node sensor.
// --------------------------------------------------------------------------
SoXipRemoteClient::~SoXipRemoteClient()
{
	deleteData();
}

// --------------------------------------------------------------------------
//! delete the volume information data if exist
// --------------------------------------------------------------------------
void SoXipRemoteClient::deleteData()
{
	if(mVolumeData)
	{
		delete mVolumeData;
		mVolumeData = NULL;
	}
}

//-----------------------------------------------------------------------------
// Called to load wanted data from the server
// return 0 when data are loaded correctly and -1 else
//-----------------------------------------------------------------------------
int SoXipRemoteClient::loadData()
{
	if(connectionState.getValue() != CONNECTED || !mStreamLength)
		return -1;
	
	//get the length of the UID to be sorted.
	//int len = dataID.getValue().getLength() + 1;

	////send the request for sorting
	//mReqSender.initSender(mStreamLength, SORT_ACTION);
	//mReqSender.rHtonl(&len);
	//mReqSender.addChildElement(SORT_ACTION, SORTREQUEST_BUFFERSIZE, sizeof(int), &len);
	//int uidType = STUDY_UID;
	//mReqSender.rHtonl(&uidType);
	//mReqSender.addChildElement(SORT_ACTION, SORTREQUEST_UIDTYPE, sizeof(int), &uidType);
	//mReqSender.addChildElement(SORT_ACTION, SORTREQUEST_BUFFER, dataID.getValue().getLength() + 1, (void*)dataID.getValue().getString());
	//mReqSender.send();
	//

	//// At this point, the server sorts the data objects, create the first IvtVolume in the first Group
	//// and the returns the header of the created volume in the radSortResponseParams structure.
	//// The struct also contains the volume count resulted in the sorting operation.
	//mReqReceiver.receive();

	//// if there is some error or the  sorting operation did not result in a valid volume.
	//if( (mReqReceiver.getFirstElementId() != SORT_ACTION))
	//	return -1;

	//int volumeCount;
	//bool res = mReqReceiver.getUniqueIntElement(SORTRESPONSE_VOLUMECOUNT, volumeCount);
	//mReqReceiver.rNtohl(&volumeCount);
	//if(!res)
	//	return -1;

    int len = dataLocation.getValue().getLength()+1;
    if ( len>1 )
    {
        mReqSender.initSender(mStreamLength, LOAD_DICOM_ACTION);
        mReqSender.rHtonl(&len);
        mReqSender.addChildElement(LOAD_DICOM_ACTION, DICOM_LOCATIONSIZE, sizeof(int), &len);
        mReqSender.addChildElement(LOAD_DICOM_ACTION, DICOM_LOCATION, dataLocation.getValue().getLength()+1, (void*)dataLocation.getValue().getString());
        mReqSender.send();

        mReqReceiver.receive();
        if ( mReqReceiver.getFirstElementId()!=LOAD_DICOM_ACTION ) return -1;

        int volumeCount = 0;

        if ( !mReqReceiver.getUniqueIntElement(LOADDICOMRESPONSE_VOLUMECOUNT, volumeCount) )
        {
            return -1;
        }
        mReqReceiver.rNtohl(&volumeCount);

        XipVolumeHeaderExt * volumeHeader = (XipVolumeHeaderExt *)mReqReceiver.getElementContent(LOADDICOMRESPONSE_VOLUMEHEADER, sizeof(XipVolumeHeader));
        if(!volumeHeader)
            return -1;

        mReqReceiver.rSwapf(volumeHeader->modelMatrix, 16);
        mReqReceiver.rNtohl(&volumeHeader->height);
        mReqReceiver.rNtohl(&volumeHeader->width);
        mReqReceiver.rNtohl(&volumeHeader->depth);
        mReqReceiver.rNtohl(&volumeHeader->bitsUsed);
        mReqReceiver.rNtohl(&volumeHeader->samplesPerPixel);
        deleteData();
        mVolumeData = new XipDataConnection(mStreamLength);

        SoXipDataConnection * volOutput = new SoXipDataConnection();
        volOutput->set(mVolumeData);

        SO_ENGINE_OUTPUT(connectionOutput, SFXipConnection, setValue(volOutput));

        SbMatrix mat;
        float* ptr = mat.operator float *();
        for (int i=0; i<16; i++)
        {
            ptr[i] = volumeHeader->modelMatrix[i];
        }

        SO_ENGINE_OUTPUT(modelMatrixOutput, SoSFMatrix, setValue(mat));
    }
    else
    {
        deleteData();
        SO_ENGINE_OUTPUT(connectionOutput, SFXipConnection, setValue(NULL));
        SO_ENGINE_OUTPUT(modelMatrixOutput, SoSFMatrix, setValue(SbMatrix::identity()));
        return -1;
    }


	//{
	//	// Now the client shall request for a volume data passing a volume header.
	//	// Currently, the server supports only sub-sampling of volume dimension. However the pixel depth will be same.
	//	
	//	mReqSender.initSender(mStreamLength, LOAD_VOLUME_ACTION);
	//	
	//	// initializes the volumeHeader from what is obtained from sorting response		.
	//	// put the size values to 0 in order to tell the server we don't need the volume buffer
	//	volumeHeader->width = 0;
	//	volumeHeader->height = 0;
	//	volumeHeader->depth = 0;


	//	mReqSender.rSwapf(volumeHeader->modelMatrix, 16);
	//	mReqSender.rHtonl(&volumeHeader->height);
	//	mReqSender.rHtonl(&volumeHeader->width);
	//	mReqSender.rHtonl(&volumeHeader->depth);
	//	mReqSender.rHtonl(&volumeHeader->bitsUsed);
	//	mReqSender.rHtonl(&volumeHeader->samplesPerPixel);


	//	mReqSender.addChildElement(LOAD_VOLUME_ACTION, LOADREQUEST_VOLUMEHEADEREXT, sizeof(XipVolumeHeaderExt), volumeHeader);
	//	mReqSender.send();



	//	// expect the load response from the server.Special request without asking for the volume buffer
	//	mReqReceiver.receive();

	//	// if there is some error or the  sorting operation did not result in a valid volume.
	//	if( (mReqReceiver.getFirstElementId() != LOAD_VOLUME_ACTION))
	//		return -1;

	//	int loadRequestAccepted;
	//	bool resLoad = mReqReceiver.getUniqueIntElement(LOADRESPONSE_ACCEPTED, loadRequestAccepted);
	//	mReqReceiver.rNtohl(&loadRequestAccepted);
	//	if(!resLoad || (loadRequestAccepted != 1))
	//		return -1;
	//}


	//output the connection if everything is ok

	// return 0 if everything is OK
	return 0;
}
