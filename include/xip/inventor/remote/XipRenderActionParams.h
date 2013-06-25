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
#ifndef XIPRENDERACTIONPARAMS_H
#define XIPRENDERACTIONPARAMS_H



// This file declares the necessary data structures for remote rendering. //
#ifndef _MAX_PATH
#include <stdlib.h>
#endif

#include <stdio.h>

// enum identifying the action identifiers
// The client and server will communicate in the context of a given action identifier.
enum XipParamId
{
	MIN_PARAM_ID = 1,
	LOGON_ACTION = MIN_PARAM_ID,
	CLIENT_VALIDATION,
	SMARTCLIENT_LOGON_ACTION,
	//SORT_ACTION,						
	LOAD_VOLUME_ACTION,					
	LOAD_DICOM_ACTION,
	RENDER_ACTION,	
    LUT_ACTION,
	MAP_IMAGE,
	TEST_ECHO,
	GET_PARAM,
	RAYPICK_ACTION,
	//LOAD_PLUGIN_ACTION,
	//UNLOAD_PLUGIN_ACTION,
	GET_VOLUME_MODELMATRIX,
	GET_VOLUME_BITSUSED,
	CLOSE_ACTION,
	MAX_PARAM_ID
};


// enum identifying the Uid Type to be sorted
// This enum must accompany the instance uid string while requesting for sorting from the client.
enum XipUidType
{
	MIN_UID_TYPE = 1,
    STUDY_UID  = MIN_UID_TYPE,
	SERIES_UID,
	IMAGE_UID,
	MAX_UID_TYPE = IMAGE_UID
};


// enum identifying Render Modes
enum XipRenderMode
{
	MIN_RENDER_MODE,
	XIP_RENDERMODE_MPR,
	XIP_RENDERMODE_MAXIP,
	XIP_RENDERMODE_MINIP,
	XIP_RENDERMODE_SSD,
	XIP_RENDERMODE_SSD_COLOR,
	XIP_RENDERMODE_VRT_COLOR,
	XIP_RENDERMODE_DRR,
	MAX_RENDER_MODE
};

// enum identifying Volume
enum XipVolumeRender
{
	NORMAL_MODE,
	SUBSAMPLED_MODE,
};

// enum identifying Compression
enum XipCompressionMode
{
	UNCOMPRESSED_MODE = 1,
	LOSSLESSLY_HUFF_MODE = 2,
	LOSSLESSLY_RLE_MODE = 3,
	LOSSLESSLY_DIFFERENTIAL = 4,
	LOSSY = 6,
	LOSSLESSLY_COMBO_MODE = 7,
};


// Volume Header. 
// The client and server uses this structure for passing the volume information.
// The server sends this structure filled, as a response to the sorting request from the client.
// The client sends this structure filled when requesting for volume data from the server.
struct XipVolumeHeader
{
	float	modelMatrix[16];
	int		width;
	int		height;
	int		depth;
	int		bitsUsed;
	int		samplesPerPixel;
};

// The extended version is used only when the entire volume is sent to the client
// It contains all the informations about the used compression algorithm
struct XipVolumeHeaderExt
{
	float	modelMatrix[16];
	int		width;
	int		height;
	int		depth;
	int		bitsUsed;
	int		samplesPerPixel;
	int		compressionType;
	int		subCompressionType;
};


// Volume Header. 
// The client and server uses this structure for passing the volume information.
// The information about the compression are added.
struct XipVolumeCompression
{
	int		compressionType;
	int		subCompressionType;
};

// Dicom Header for passing the dicom information.
// The server sends this structure as a response to the dicomHeader request from the client.
struct XipDicomHeader 
{
	char patientName[500];
	char patientID[66];
	char patientDOB[20];
	char patientSex[20];
	char patientAge[20];

	char studyDescription[66];
	char studyDate[20];
	char studyTime[20];
	char studyId[66];
	char modality[17];

	char seriesDescription[66];
	char seriesId[66];
	char seriesDate[20];
	char seriesTime[17];
};


// enum identifying elements of the request
enum XipTreeRequestElementId
{
	//--------------------------
	// Logon Request
	LOGONREQUEST_STRBUFFERSIZE = MAX_PARAM_ID,				//int
	LOGONREQUEST_CLIENTSTR,									//char[LOGONREQUEST_STRBUFFERSIZE]
	
	//--------------------------
	// Logon Response	
	LOGONRESPONSE_ACCEPTED,									//int
	
	//--------------------------
	// Sorting Request
	// sent by the client during the sorting request.	
	SORTREQUEST_BUFFERSIZE,									//int
	SORTREQUEST_UIDTYPE,									//radUidType
	SORTREQUEST_BUFFER,										//char[SORTREQUEST_BUFFERSIZE]
	
	//--------------------------
	// Sorting Response
	// sent by the server as a response to sorting request.
	// Based on the volume count, the client must take appropriate action.If volume count is non-zero,
	// the client may use the volume header information for subsequent volume loading request.	
	SORTRESPONSE_VOLUMECOUNT,								//int
	SORTRESPONSE_VOLUMEHEADER,								//radVolumeHeader
	
	//--------------------------
	// Load Request
	// sent by the client as a request for loading the volume.
	// The server uses this information, sub-samples the original volume and send a loading response indicating
	// the availability of volume data.	
	LOADREQUEST_VOLUMEHEADER = SORTRESPONSE_VOLUMEHEADER,	//radVolumeHeader

	//--------------------------
	// Load Response
	// sent by the server as a response to loadVolume request.
	// If the volume data is available, then the server sets the loadRequestAccepted variable to 1 else 0;	
	LOADRESPONSE_ACCEPTED,									//int
	LOADRESPONSE_MODELMATRIX,								//double[16]

	//--------------------------
	// Load Dicom Response
	// sent by the server as a response to loadDicom request.
    LOADDICOMRESPONSE_VOLUMECOUNT,                              //Volume count
    LOADDICOMRESPONSE_VOLUMEHEADER,                             //Volume Header
	LOADDICOMRESPONSE_DICOMHEADER,								//Dicom Header
    DICOM_LOCATIONSIZE,
    DICOM_LOCATION,

	LUT_RAMP_WIDTH,											//float
	LUT_RAMP_CENTER,										//float
	LUT_RAMP_WIDTH_ACCEPTED,								//int
	LUT_RAMP_CENTER_ACCEPTED,								//int

	//--------------------------
	// Rendering Request
	// sent by the client as a request for high quality rendering image.
	RENDERACTION_RENDERQUALITY,								//double     
	RENDERACTION_COMPRESSIONQUALITY,						//int
	RENDERACTION_RENDERQUALITY_VALUE,						//int
	RENDERACTION_CALLBACK_FLAG,
	RENDERACTION_COMPRESSIONTYPE,							//int    

	RENDERACTION_RENDERMODE,								//short
	RENDERACTION_MPRPLANE,									//short  

	RENDERACTION_ALPHAHANDLING,								//int

	RENDERACTION_CUTPLANE,
	RENDERACTION_CUTPLANECOEFFS,							//double[4]
	RENDERACTION_CUTPLANETHICKNESS,							//double

	RENDERACTION_CROPBOX,
	RENDERACTION_CROPBOXCOEFFS,								//double[6]

	RENDERACTION_TRANSFORMMATRIX,							//double[16]

	RENDERACTION_CAMERA,
	RENDERACTION_PROJECTIONMATRIX,							//float[16]
	RENDERACTION_VIEWDIRECTIONMATRIX,						//double[16]
	RENDERACTION_VIEWPORT,									//int[4]
	RENDERACTION_LIGHTENABLED,								//bool
    RENDERACTION_CAMERA_POSITION,                           // float[3]
    RENDERACTION_CAMERA_ORIENTATION,                        // float[4]
    RENDERACTION_CAMERA_NEARDIST,                           // float
    RENDERACTION_CAMERA_FARDIST,                            // float
    RENDERACTION_CAMERA_RATIO,                              // float
    RENDERACTION_CAMERA_HEIGHT,                             // float

	RENDERACTION_RC,
	RENDERACTION_RCWIDTH,									//int
	RENDERACTION_RCHEIGHT,									//int

	RENDERACTION_LUT,
	RENDERACTION_LUTSIZE,									//int
	RENDERACTION_LUTBUFFER,									//float array

	RENDERACTION_THRESHOLD,									//short[2]

	RENDERACTION_COLOR,										//float[3][4]

	RENDERACTION_MATERIAL,									//double[4]

	RENDERACTION_MPR,
	RENDERACTION_MPRPLANARTHICKNESSUSED,					//bool
	RENDERACTION_MPRPLANARTHICKNESS,						//double
	RENDERACTION_MPRPLANEWIDTH,								//int
	RENDERACTION_MPRPLANEHEIGHT,							//int
	RENDERACTION_SURFACESCALINGFACTOR,						//double
	RENDERACTION_SURFACEMODELMATRIX,						//double[16]

	RENDERACTION_SCROLL,
	RENDERACTION_SCROLLSIZE,								//int
	RENDERACTION_SCROLLSLABRESOLUTION,						//int
	RENDERACTION_SCROLLEXPAND,								//int
	RENDERACTION_SHRINK,									//int

	//--------------------------
	// Rendering Response
	// sent by the server as a response to rendering request.
	// If the renderer could render the high quality volume, then the server sets 
	// the renderActionDone variable to 1 else 0;
	RENDERACTIONRESPONSE_DONE,								//int
	RENDERACTIONRESPONSE_ALPHADIM,							//char[]
	RENDERACTIONRESPONSE_ALPHABUFFER,						//char[]
	RENDERACTIONRESPONSE_BUFFERDIM,							//char[]
	RENDERACTIONRESPONSE_BUFFER,							//char[]
	RENDERACTIONRESPONSE_LASTFRAME,							//int
    RENDERACTIONRESPONSE_BUFFERSIZE,                        //int

    // LUT
    LUTACTION_LUTNAMESIZE,
    LUTACTION_LUTNAME,
    LUTACTION_INPUTMODE,
    LUTACTION_ALPHAMODE,
    LUTACTION_FILEMODE,
    LUTACTION_OUTPUTMODE,
    LUTACTION_BITSUSED,
    LUTACTION_RAMPWIDTH,
    LUTACTION_RAMPCENTER,
    LUTACTION_ALPHAFACTOR,
    LUTACTION_SLOPEWIDTH,
    LUTACTION_SLOPECENTER,
    LUTACTION_COLORBOTTOM,
    LUTACTION_COLORMIDDLE,
    LUTACTION_COLORTOP,
    LUTACTION_FILENAMESIZE,
    LUTACTION_FILENAME,
    LUTACTION_FILEENTRIES,
    LUTACTIONRESPONSE_DONE,
	
	//--------------------------
	// Map Image Request
	MAPIMAGEREQUEST_FILENAME,								//wchar_t[_MAX_PATH]
	MAPIMAGEREQUEST_OFFSET,									//unsigned int
	MAPIMAGEREQUEST_SHARENAME,								//wchar_t[128]
	MAPIMAGEREQUEST_WIDTH,									//int
	MAPIMAGEREQUEST_HEIGHT,									//int
	MAPIMAGEREQUEST_PIXELDATATYPE,							//int
	MAPIMAGEREQUEST_BITSUSED,								//int
	MAPIMAGEREQUEST_READONLYFLAG,							//int
	MAPIMAGEREQUEST_TOTPLANES,								//int
	MAPIMAGEREQUEST_COMPTYPE,								//int
	MAPIMAGEREQUEST_COMPLAYOUT,								//int
	MAPIMAGEREQUEST_BYTEALIGNMENT,							//int
	MAPIMAGEREQUEST_MATRIX,									//double[16]
	MAPIMAGEREQUEST_LASTINSTACK,							//int
	
	//--------------------------
	// Get param Request
	GETPARAMREQUEST_PARAMTYPE,								//radGetParamType
	GETPARAMREQUEST_PARAMID,								//int
	GETPARAMREQUEST_PARAMLENGTH,							//int

	//--------------------------
	// Get param Response
	// sent by the server as a response to get param request.
	// If the current render action could get the param value, then the server sets 
	// the paramReceived variable to 1 else 0;
	GETPARAMRESPONSE_RECEIVED,								//int
	GETPARAMRESPONSE_BUFFER,								//tab[GETPARAMREQUEST_PARAMLENGTH]

	//--------------------------
	// Ray pick Request
	RAYPICKREQUEST_ENTRIES,									//int
	RAYPICKREQUEST_BUFFER,									//double[6*RAYPICKREQUEST_ENTRIES]
	
	//--------------------------
	// Ray pick Response
	// sent by the server as a response to ray pick request.
	// If the current render action could get the ray surface intersections , then the server sets 
	// the rayPickSuccedded variable to 1 else 0;
	RAYPICKRESPONSE_SUCCEEDED,								//int
	RAYPICKRESPONSE_BUFFER,									//double[6*RAYPICKREQUEST_ENTRIES+bool]
	
	//--------------------------
	// Load Plugin Request
	LOADPLUGINREQUEST_BUFFERSIZE,							//int
	LOADPLUGINREQUEST_PLUGINTYPE,							//radPluginType
	LOADPLUGINREQUEST_PLUGINNAME,							//char[LOADPLUGINREQUEST_BUFFERSIZE]
	
	//--------------------------
	// Load Plugin Response
	LOADPLUGINRESPONSE_LOADED,								//int

	//--------------------------
	// Unload Plugin Request
	UNLOADPLUGINREQUEST_PLUGINTYPE,							//radPluginType
	
	//--------------------------
	// Unload Plugin Response
	UNLOADPLUGINRESPONSE_UNLOAD,							//int
	
	//--------------------------
	//Get Volume ModelMatrix Response
	GETVOLUMEMMATRIXRESPONSE_NEWVOLUME,						//int
	GETVOLUMEMMATRIXRESPONSE_MODELMATRIX,					//double[16]

	//--------------------------
	//Get Volume ModelMatrix Response
	GETVOLUMEBITSUSEDRESPONSE,								//int

	RENDERACTION_MPRRESET,
	RENDERACTION_MPRQUALITY,								//short
	LOADREQUEST_VOLUMEHEADEREXT,							//int
	RENDERACTIONRESPONSE_RLEDIM,							//int
	RENDERACTIONRESPONSE_ACTUALPLANE,						//int
	RENDERACTION_RENDERFULL_LOSSY,							//int

	//--------------------------
	// Client validation Request
	CLIENTVALIDATION_RLE,									//int
	CLIENTVALIDATION_HUFFMAN,								//int
	CLIENTVALIDATION_DIFFERENTIAL_RLE,						//int
	CLIENTVALIDATION_DIFFERENTIAL_HUFFMAN,					//int
	CLIENTVALIDATION_LOSSY_JPEG,							//int
	VALIDATED,												//int
	CLIENTVALIDATION_ACCEPTED,								//int
	CLIENTVALIDATION_IS_SMART,								//int

	//--------------------------
	// Smart client validation Request
	SMARTCLIENTLOGONREQUEST_HUFFMAN,						//int
	SMARTCLIENTLOGONREQUEST_DIFFERENTIAL_HUFFMAN,			//int
	SMARTCLIENTLOGONREQUEST_LOSSY,							//int
	SMARTCLIENTLOGONREQUEST_IS_SMART,						//int
	SMARTCLIENTLOGONRESPONSE_ACCEPTED,						//int
};


enum XipGetParamType
{
	P_INT,
	P_UNSIGNED_INT,
	P_DOUBLE
};


enum XipPluginType
{
	DATA_PLUGIN,
	SORT_PLUGIN,
};



#endif //XIPENDERACTIONPARAMS_H
