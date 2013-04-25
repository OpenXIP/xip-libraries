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


#include "SoXipRemoteVolume.h"

//#include <xip/data/RadDICOMTypes.h>
//#include <xip/remote/XipDataObjectBase.h>
//#include <xip/remote/XipDataConnectorBase.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/dicom/SoXipSFDataDicom.h>
//#include <xip/inventor/core/SoXipPluginLoader.h>

#ifndef MAX_PATH
	#define MAX_PATH 260
#endif

SO_ENGINE_SOURCE(SoXipRemoteVolume);

/*
*! Constructor, creates fields
*/
SoXipRemoteVolume::SoXipRemoteVolume()
{
	SO_ENGINE_CONSTRUCTOR(SoXipRemoteVolume);

	SO_ENGINE_ADD_INPUT(volumeInput, (0));

	SO_ENGINE_ADD_OUTPUT(modelMatrixOutput, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(bitsUsedOutput, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(dicomHeader, SoXipSFDataDicom);

	mStream = NULL;
	mVol = NULL;
	mDataConnector = NULL;
	mDicomData = NULL;
}

/*
*! Initializes this class. Called on dll initialization.
*/
void SoXipRemoteVolume::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipRemoteVolume, SoEngine, "Engine");
}

/*
*! Protected destructor to cleans up internally created nodes and node sensor.
*/
SoXipRemoteVolume::~SoXipRemoteVolume()
{
}



/*
*! Used to get the model matrix from the server
*/
void SoXipRemoteVolume::getModelMatrix()
{
	if(!mStream)
		return;
	
	//send the request for modelMatrix
	mReqSender.initSender(mStream, GET_VOLUME_MODELMATRIX);
	mReqSender.send();	


	// expect the  response from the server.
	mReqReceiver.initReceiver(mStream);
	mReqReceiver.receive();


	// if there is some error or the  sorting operation did not result in a valid volume.
	if( (mReqReceiver.getFirstElementId() != GET_VOLUME_MODELMATRIX))
	{
		SoError::post("RemoteVolume: Server modelMatrix request error!\n");
		return;
	}

	float *m = (float *)mReqReceiver.getElementContent(GETVOLUMEMMATRIXRESPONSE_MODELMATRIX, 16*sizeof(float));
	if(!m)
	{
		SoError::post("RemoteVolume: Server modelMatrix request error!\n");
		return;
	}

	mReqReceiver.rSwapf(m, 16);


	SO_ENGINE_OUTPUT(modelMatrixOutput, SoSFMatrix, setValue(SbMatrix (
        m[0], m[1], m[2], m[3],
        m[4], m[5], m[6], m[7], 
        m[8], m[9], m[10], m[11],
        m[12], m[13], m[14], m[15])));


}


/*
*! Used to get the bitsUsed from the server
*/
void SoXipRemoteVolume::getBitsUsed()
{
	if(!mStream)
		return;
	
	//send the request for modelMatrix
	mReqSender.initSender(mStream, GET_VOLUME_BITSUSED);
	mReqSender.send();	


	// expect the  response from the server.
	mReqReceiver.initReceiver(mStream);
	mReqReceiver.receive();


	// if there is some error or the  sorting operation did not result in a valid volume.
	if( (mReqReceiver.getFirstElementId() != GET_VOLUME_BITSUSED))
	{
		SoError::post("RemoteVolume: Server getBitsused request error!\n");
		return;
	}

	int Bits;
	if(!mReqReceiver.getUniqueIntElement(GETVOLUMEBITSUSEDRESPONSE, Bits))
	{
		SoError::post("RemoteVolume: Server getBitsused request error!\n");
		return;
	}

	mReqReceiver.rNtohl(&Bits);


	SO_ENGINE_OUTPUT(bitsUsedOutput, SoSFInt32, setValue(Bits));
}

/*
*! Used to get the dicom Header from the server
*/
void SoXipRemoteVolume::getDicomHeader()
{
	if(!mStream)
		return;

    int this_part_needs_to_be_reimplemented;
	
	//if (!mDataConnector)
	//{
	//	#if defined(WINDOWS) || defined(_WIN32)
	//		mDataConnector = (XipDataConnectorBase*) SoRadPluginLoader::ref(RAD_MEM_PLUGIN);
	//	#else
	//		mDataConnector = (XipDataConnectorBase*) new radDataConnectorMem();
	//	#endif
	//}

	//if (!mDicomData && mDataConnector)
	//{
	//	RadDataObjectBase *dobject = mDataConnector->createDataObject();
	//	if(!dobject)
	//		return;

	//	// open data object
	//	dobject->open(0);

	//	wchar_t dicomString[MAX_PATH];
	//	memset(dicomString, 0, MAX_PATH);


	//	//send the request for dicomHEader
	//	mReqSender.initSender(mStream, LOAD_DICOM_ACTION);
	//	mReqSender.send();	
	//	

	//	// expect the  response from the server.
	//	mReqReceiver.initReceiver(mStream);
	//	mReqReceiver.receive();


	//	// if there is some error or the  sorting operation did not result in a valid volume.
	//	if( (mReqReceiver.getFirstElementId() != LOAD_DICOM_ACTION))
	//	{
	//		SoError::post("RemoteVolume: Server getDicomHeader request error!\n");
	//		return;
	//	}

	//	XipDicomHeader * dicomHeader = (XipDicomHeader *)mReqReceiver.getElementContent(LOADDICOMRESPONSE_HEADER, sizeof(XipDicomHeader));			
	//	if(!dicomHeader)
	//	{
	//		SoError::post("RemoteVolume: Server getDicomHeader response error!\n");
	//		return;
	//	}

	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->patientName);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->patientName,MAX_PATH);	
	//	#endif
	//	dobject->setElement(
	//						RAD_PATIENTSNAME_DICOMGROUP,
	//						RAD_PATIENTSNAME_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);

	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->patientID);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->patientID,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_PATIENTID_DICOMGROUP,
	//						RAD_PATIENTID_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);

	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->patientDOB);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->patientDOB,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_PATIENTDOB_DICOMGROUP,
	//						RAD_PATIENTDOB_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);

	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->studyDescription);
	//	#else

	//		mbstowcs(dicomString,dicomHeader->studyDescription,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_STUDY_DESCRIPTION_DICOMGROUP,
	//						RAD_STUDY_DESCRIPTION_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);

	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->studyDate);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->studyDate,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_STUDYDATE_DICOMGROUP,
	//						RAD_STUDYDATE_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);


	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->studyTime);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->studyTime,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_STUDYTIME_DICOMGROUP,
	//						RAD_STUDYTIME_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);

	//	
	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->seriesDescription);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->seriesDescription,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_SERIES_DESCRIPTION_DICOMGROUP,
	//						RAD_SERIES_DESCRIPTION_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);

	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->seriesDate);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->seriesDate,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_SERIES_DATE_DICOMGROUP,
	//						RAD_SERIES_DATE_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);

	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->seriesTime);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->seriesTime,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_SERIES_TIME_DICOMGROUP,
	//						RAD_SERIES_TIME_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);
	//						
	//	#if defined(WINDOWS) || defined(_WIN32)
	//		swprintf(dicomString, L"%S", dicomHeader->modality);
	//	#else
	//		mbstowcs(dicomString,dicomHeader->modality,MAX_PATH);
	//	#endif
	//	dobject->setElement(
	//						RAD_MODALITY_DICOMGROUP,
	//						RAD_MODALITY_DICOMELEMENT,
	//						RadDataObjectBase::STRING,
	//						1,
	//						sizeof(dicomString),
	//						dicomString);

	//	mDicomData = new SoRadDataDicom;
	//	mDicomData->ref();
	//	mDicomData->set(mDataConnector, dobject);
	//}

	//// update output
	//SO_ENGINE_OUTPUT(dicomHeader, SoRadSFDataDicom, setValue(mDicomData));

}


/*
*! This is called when an input value changes - we will use
*! it to figure out which input was changed most recently
*/
void SoXipRemoteVolume::inputChanged(SoField *whichField)
{
	SoEngine::inputChanged(whichField);
}

/*
*! Evaluation method
*/
void SoXipRemoteVolume::evaluate()
{
	SoXipDataConnection *vol = volumeInput.getValue();
	if(vol && mVol != vol)
	{
		XipDataConnection * sVol = vol->get();
		if(sVol)
		{
			mStream = sVol->mStream;
		}

		getModelMatrix();
		//getBitsUsed();
		//getDicomHeader();

		mVol = vol;
	}
}
