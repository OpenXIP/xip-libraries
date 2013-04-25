/*
*  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
*  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
*  (XIP) was created with NCI funding and is part of the caBIG(tm) 
*  initiative. The software subject to this notice and license 
*  includes both human readable source code form and machine 
*  readable, binary, object code form (the "caBIG(tm) Software").
*  
*  This caBIG(tm) Software License (the "License") is between 
*  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
*  person or an entity, and all other entities that control, are 
*  controlled by, or are under common control with the entity.  
*  "Control" for purposes of this definition means (i) the direct or 
*  indirect power to cause the direction or management of such 
*  entity, whether by contract or otherwise, or (ii) ownership of 
*  fifty percent (50%) or more of the outstanding shares, or (iii) 
*  beneficial ownership of such entity.
*  
*  LICENSE.  Provided that You agree to the conditions described 
*  below, caBIG(tm) Participant grants You a non-exclusive, 
*  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
*  transferable and royalty-free right and license in its rights in 
*  the caBIG(tm) Software, including any copyright or patent rights 
*  therein that may be infringed by the making, using, selling, 
*  offering for sale, or importing of caBIG(tm) Software, to (i) 
*  use, install, access, operate, execute, reproduce, copy, modify, 
*  translate, market, publicly display, publicly perform, and 
*  prepare derivative works of the caBIG(tm) Software; (ii) make, 
*  have made, use, practice, sell, and offer for sale, and/or 
*  otherwise dispose of caBIG(tm) Software (or portions thereof); 
*  (iii) distribute and have distributed to and by third parties the 
*  caBIG(tm) Software and any modifications and derivative works 
*  thereof; and (iv) sublicense the foregoing rights set out in (i), 
*  (ii) and (iii) to third parties, including the right to license 
*  such rights to further third parties.  For sake of clarity, and 
*  not by way of limitation, caBIG(tm) Participant shall have no 
*  right of accounting or right of payment from You or Your 
*  sublicensees for the rights granted under this License.  This 
*  License is granted at no charge to You.  Your downloading, 
*  copying, modifying, displaying, distributing or use of caBIG(tm) 
*  Software constitutes acceptance of all of the terms and 
*  conditions of this Agreement.  If you do not agree to such terms 
*  and conditions, you have no right to download, copy, modify, 
*  display, distribute or use the caBIG(tm) Software.
*  
*  1.	Your redistributions of the source code for the caBIG(tm) 
*      Software must retain the above copyright notice, this list 
*      of conditions and the disclaimer and limitation of 
*      liability of Article 6 below.  Your redistributions in 
*      object code form must reproduce the above copyright notice, 
*      this list of conditions and the disclaimer of Article 6 in 
*      the documentation and/or other materials provided with the 
*      distribution, if any.
*  2.	Your end-user documentation included with the 
*      redistribution, if any, must include the following 
*      acknowledgment: "This product includes software developed 
*      by Siemens Corporate Research Inc."  If You do not include 
*      such end-user documentation, You shall include this 
*      acknowledgment in the caBIG(tm) Software itself, wherever 
*      such third-party acknowledgments normally appear.
*  3.	You may not use the names "Siemens Corporate Research, 
*      Inc.", "The National Cancer Institute", "NCI", "Cancer 
*      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
*      products derived from this caBIG(tm) Software.  This 
*      License does not authorize You to use any trademarks, 
*  	service marks, trade names, logos or product names of 
*      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
*      required to comply with the terms of this License.
*  4.	For sake of clarity, and not by way of limitation, You may 
*      incorporate this caBIG(tm) Software into Your proprietary 
*      programs and into any third party proprietary programs.  
*      However, if You incorporate the caBIG(tm) Software into 
*      third party proprietary programs, You agree that You are 
*      solely responsible for obtaining any permission from such 
*      third parties required to incorporate the caBIG(tm) 
*      Software into such third party proprietary programs and for 
*      informing Your sublicensees, including without limitation 
*      Your end-users, of their obligation to secure any required 
*      permissions from such third parties before incorporating 
*      the caBIG(tm) Software into such third party proprietary 
*      software programs.  In the event that You fail to obtain 
*      such permissions, You agree to indemnify caBIG(tm) 
*      Participant for any claims against caBIG(tm) Participant by 
*      such third parties, except to the extent prohibited by law, 
*      resulting from Your failure to obtain such permissions.
*  5.	For sake of clarity, and not by way of limitation, You may 
*      add Your own copyright statement to Your modifications and 
*      to the derivative works, and You may provide additional or 
*      different license terms and conditions in Your sublicenses 
*      of modifications of the caBIG(tm) Software, or any 
*      derivative works of the caBIG(tm) Software as a whole, 
*      provided Your use, reproduction, and distribution of the 
*      Work otherwise complies with the conditions stated in this 
*      License.
*  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
*      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
*      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
*      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
*      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
*      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
*      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
*      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
*      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
*      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
*      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
*      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
*      THE POSSIBILITY OF SUCH DAMAGE.
*  
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