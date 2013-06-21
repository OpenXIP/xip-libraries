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
