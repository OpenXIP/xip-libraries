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

#include <iostream>
#include <iomanip>

#include "XipRenderTask.h"
#include <xip/inventor/remote/XipStream.h>
#include <xip/inventor/remote/XipRenderActionParams.h>
#include <xip/inventor/remote/losslessCompression/losslessCompression.h>
#include <xip/inventor/remote/losslessCompression/fastMemTransfer.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include "OIVUtils.h"
//#include "cimg.h"

#define XIP_MAX_CLIENT_REQUEST_SIZE	1024

static bufferImage img;
static losslessCompression compressorObj;
static fastMemTransfer memTransfers;

//using namespace cimg_library;
using namespace std; 
/**
 *   The default constructor
 *
 *  \param stream Pointer to the socket encaptulation
 */
XipRenderTask::XipRenderTask(XipStreamBase *stream)
{
	#if _DEBUG
		fprintf(stderr, "renderTask CONSTRUCTOR.\n");
	#endif

	newVolume = 0;

	if(!stream)
	{
        //throw RadException(__LINE__, __FILE__, RadException::INVALID_PARAM_ERROR, L"No stream object specified.");
        return;
	}

	mStream = stream;
	reqSender.initSender(stream, -1);
	reqReceiver.initReceiver(stream);

    mRenderer = NULL;

	mCvISSMART = false;

    this->initialize();
}

/**
 *   The default destructor
 */
XipRenderTask::~XipRenderTask()
{
	#if _DEBUG
		fprintf(stderr, "renderTask DESTRUCTOR.\n");
	#endif

    if ( mRenderer )
    {
        delete mRenderer;
        mRenderer = NULL;
    }
}

void XipRenderTask::initialize()
{
    SoDB::init();

    loadDLLs();

    mRenderer = new XipRenderAction;
}

void XipRenderTask::loadDLLs()
{
    HINSTANCE   xipIVCore   = NULL;
    HINSTANCE   xipIVCoreGl = NULL;
    HINSTANCE   xipIVSlicer = NULL;
    HINSTANCE   xipIVDicom  = NULL;

    xipIVCore = ::LoadLibrary("xipivcore.dll");
    if ( NULL==xipIVCore ) printf("Error: cannot load xipivcore.dll!\n");

    xipIVCoreGl = ::LoadLibrary("xipivcoregl.dll");
    if ( NULL==xipIVCoreGl ) printf("Error: cannot load xipivcoregl.dll!\n");

    xipIVSlicer = ::LoadLibrary("xipivrenderer.dll");
    if ( NULL==xipIVSlicer ) printf("Error: cannot load xipivrenderer.dll!\n");

    xipIVDicom = ::LoadLibrary("xipivdicom.dll");
    if ( NULL==xipIVDicom ) printf("Error: cannot load xipivdicom.dll!\n");
}

/**
 * Task entry point
 */ 
void XipRenderTask::run()
{
	// process client requests
	bool endStream = false;
	int sent;
	do
	{
		try
		{
			reqReceiver.receive();
			if(processRequest() == 0)
				endStream = true;
		}
		catch(...)
		{
			fprintf(stderr, "Caught unknown exception while processing client request of type %d.\n", reqReceiver.getFirstElementId());
			char errCode = 0;
			sent = mStream->send(&errCode, sizeof(errCode), 0);
			endStream = true;
		}

	} while(!endStream);
}


/**
 * Prcesses a client request (called by run() ).
 */ 
int XipRenderTask::processRequest()
{
	int requestId = reqReceiver.getFirstElementId();
	int res = 1;

	switch (requestId)
	{
	case TEST_ECHO:
		{
			#if _DEBUG
				printf("Process TEST_ECHO.\n");
			#endif

			// send back test reply
			const int replySize = 4 * 512 * 512;
			void *ptr = malloc(replySize);
			if (ptr)
			{
				memset(ptr, 128, replySize);
				mStream->send((const char *) ptr, replySize, 0);
				free(ptr);
			}
			else
			{
				char c = 1;
				mStream->send(&c, 1, 0);
			}
		} break;

	case LOGON_ACTION:
		{
			#if _DEBUG
				printf("Process LOGON_ACTION.\n");
			#endif

			if (!logon())
			{
				printf("Client authentication failed.");
                return res;
			}
		} break;
	
	case CLIENT_VALIDATION:
		{
			#if _DEBUG
				printf("Process CLIENT_VALIDATION.\n");
			#endif
			if(!validation())
			{
				//throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"Client Validation action failed.");
                return res;
			}
		} break;

	case SMARTCLIENT_LOGON_ACTION:
		{
			#if _DEBUG
				printf("Process SMARTCLIENT_VALIDATION.\n");
			#endif
			if(!smartValidation())
			{
				//throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"Client Validation action failed.");
                return res;
			}
		} break;/**/

	case RENDER_ACTION:
		{
			#if _DEBUG
				printf("Process RENDER_ACTION.\n");
			#endif
			//static CPreciseTimer oPreciseTimer;
			//oPreciseTimer.StartTimer();

			if(render() == -1)
			{
				printf("Render action failed.\n");
                return res;
			}
			//__int64 i64Diff = oPreciseTimer.GetTime();
			//oPreciseTimer.StopTimer();
			//float elapse = (float)(i64Diff);
			//elapse = elapse * (0.000001);
			//float fps = 1/elapse;
			

		} break;

    case LUT_ACTION:
        {
#if _DEBUG
            printf("Process LUT_ACTION.\n");
#endif
            setLut();
        }
        break;

	case LOAD_DICOM_ACTION:
		{
			#if _DEBUG
				printf("Process LOAD_DICOM_ACTION.\n");
			#endif

            loadDicom();
			//patientInfo();
		} break;

	case RAYPICK_ACTION:
		{
			#if _DEBUG
				printf("Process RAYPICK_ACTION.\n");
			#endif

			raySurfaceIntersections();
		} break;

	case GET_VOLUME_MODELMATRIX:
		{
			#if _DEBUG
				printf("Process GET_VOLUME_MODELMATRIX.\n");
			#endif

			getModelMatrix();
		} break;

	case GET_VOLUME_BITSUSED:
		{
			#if _DEBUG
				printf("Process GET_VOLUME_BITSUSED.\n");
			#endif

			getBitsUsed();
		} break;

	case CLOSE_ACTION:
		{
			#if _DEBUG
				printf("Process CLOSE_ACTION.\n");
			#endif
			res = 0;
		} break;
	default:
		{
#if _DEBUG
			printf("Invalid or unsupported client request %d.\n", requestId);
#endif
            return 0;
		}		
	}

	return res;
}


/**
 * Waits for client authentification, which is required for CARC
 */
bool XipRenderTask::logon()
{
	return true;
}

/**
 * Client validation, which is required for a correst parameter setup
 */
bool XipRenderTask::validation()
{
	int valid;

	bool cvRLE = reqReceiver.getUniqueIntElement(CLIENTVALIDATION_RLE, valid);
	bool cvHUFF = reqReceiver.getUniqueIntElement(CLIENTVALIDATION_HUFFMAN, valid);
	bool cvDRLE = reqReceiver.getUniqueIntElement(CLIENTVALIDATION_DIFFERENTIAL_RLE, valid);
	bool cvDHUFF = reqReceiver.getUniqueIntElement(CLIENTVALIDATION_DIFFERENTIAL_HUFFMAN, valid);
	bool cvLOSSYJ = reqReceiver.getUniqueIntElement(CLIENTVALIDATION_LOSSY_JPEG, valid);

	mCvISSMART = reqReceiver.getUniqueIntElement(CLIENTVALIDATION_IS_SMART, valid);

	bool cvVAL = reqReceiver.getUniqueIntElement(VALIDATED, valid);
	
	if(!cvVAL)
		return false;
	
	//send the response that the validation is done
	int accepted = 1;  
	
	reqSender.initSender(mStream, CLIENT_VALIDATION);

	reqSender.rHtonl(&accepted);
	reqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_ACCEPTED, sizeof(int), &accepted);
	
	int supported = 1;

	if(cvRLE)                    reqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_RLE, 4, &supported);
	if(cvHUFF)  { supported = 1; reqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_HUFFMAN, 4, &supported); }
	if(cvDRLE)  { supported = 1; reqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_DIFFERENTIAL_RLE, 4, &supported); }
	if(cvDHUFF) { supported = 1; reqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_DIFFERENTIAL_HUFFMAN, 4, &supported); }
	if(cvLOSSYJ){ supported = 1; reqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_LOSSY_JPEG, 4, &supported); }

	if(mCvISSMART){ supported = 1; reqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_IS_SMART, 4, &supported); }


	reqSender.send();


	//RAD_TRACE("radRenderTask: Validation for Remote Renderer accepted.");

	return true;
}

/**
 * Client validation, which is required for a correst parameter setup
 */
bool XipRenderTask::smartValidation()
{
 
	int valid;

	bool cvHUFF = reqReceiver.getUniqueIntElement(SMARTCLIENTLOGONREQUEST_HUFFMAN, valid);
	bool cvDHUFF = reqReceiver.getUniqueIntElement(SMARTCLIENTLOGONREQUEST_DIFFERENTIAL_HUFFMAN, valid);
	bool cvLOSSYJ = reqReceiver.getUniqueIntElement(SMARTCLIENTLOGONREQUEST_LOSSY, valid);

	mCvISSMART = reqReceiver.getUniqueIntElement(SMARTCLIENTLOGONREQUEST_IS_SMART, valid);

	bool cvVAL = reqReceiver.getUniqueIntElement(VALIDATED, valid);

	if(!cvVAL) 
		return false;
	
	//send the response that the validation is done
	int accepted = 1;  
	
	reqSender.initSender(mStream, SMARTCLIENT_LOGON_ACTION);

	reqSender.rHtonl(&accepted);
	reqSender.addChildElement(SMARTCLIENT_LOGON_ACTION, SMARTCLIENTLOGONRESPONSE_ACCEPTED, sizeof(int), &accepted);
	
	int supported = 1;

	if(cvHUFF)     reqSender.addChildElement(SMARTCLIENT_LOGON_ACTION, SMARTCLIENTLOGONREQUEST_HUFFMAN, 4, &supported);
	if(cvDHUFF)    reqSender.addChildElement(SMARTCLIENT_LOGON_ACTION, SMARTCLIENTLOGONREQUEST_DIFFERENTIAL_HUFFMAN, 4, &supported); 
	if(cvLOSSYJ)   reqSender.addChildElement(SMARTCLIENT_LOGON_ACTION, SMARTCLIENTLOGONREQUEST_LOSSY, 4, &supported); 

	if(mCvISSMART) reqSender.addChildElement(SMARTCLIENT_LOGON_ACTION, SMARTCLIENTLOGONREQUEST_IS_SMART, 4, &supported);

	reqSender.send();

	//RAD_TRACE("radRenderTask: Validation for Remote Renderer accepted.");

	return true;
}

/**
 *	Finds an intersection point with a volume surface.
 */
void XipRenderTask::raySurfaceIntersections()
{
//	int i;
//	//create a ray pick response object for sending to client later.
//	reqSender.initSender(mStream, RAYPICK_ACTION);
//	int rayPickSucceeded = 0;
//
//	int entries;
//	bool res = reqReceiver.getUniqueIntElement(RAYPICKREQUEST_ENTRIES, entries);
//	reqReceiver.rNtohl(&entries);
//
//	int bufferSize = 6 * entries * sizeof(double);
//	char * recvBuffer = reqReceiver.getElementContent(RAYPICKREQUEST_BUFFER, bufferSize);
//
//
//
//	if (!mVolRenderer || !mSubVolRenderer || !res || !recvBuffer)
//	{
//		// either the ray pick request parameters are zero or the volume renderer is not initialized
//		// send the response that the ray pick not succeeded.
//		reqSender.rHtonl(&rayPickSucceeded);
//		reqSender.addChildElement(RAYPICK_ACTION, RAYPICKRESPONSE_SUCCEEDED, sizeof(int), &rayPickSucceeded);
//		reqSender.send();
//		fprintf(stderr,"Error in finding ray surface intersections.\n");
//		return ;
//	}
//
//	char *resultBuffer = 0;
//	ivtStructRayPickRaysSegs rayPickParams;
//
//	try
//	{
//		IvtVector3D* dataPtr = (IvtVector3D *)recvBuffer;
//		int cnt = 0;
//		
//		rayPickParams.numEntries = entries;
//
//		rayPickParams.startRays = new IvtVector3D[entries];
//		memset(rayPickParams.startRays, 0, entries * sizeof(IvtVector3D));
//
//		rayPickParams.endRays = new IvtVector3D[entries];
//		memset(rayPickParams.endRays, 0, entries * sizeof(IvtVector3D));
//
//		rayPickParams.intersectionFlags = new BOOL32[entries];
//		memset(rayPickParams.intersectionFlags, 0, entries * sizeof(BOOL32));
//
//		rayPickParams.worldCoords = new IvtVector3D[entries];
//		memset(rayPickParams.worldCoords, 0, entries * sizeof(IvtVector3D));
//
//		rayPickParams.voxelCoords = new IvtVector3D[entries];
//		memset(rayPickParams.voxelCoords, 0, entries * sizeof(IvtVector3D));
//
//		for (i = 0; i < entries; i++)
//		{
//			rayPickParams.startRays[i]	= dataPtr[cnt++];
//			rayPickParams.endRays[i]	= dataPtr[cnt++];
//		}
//
//		// set the pointer type variable for IVT_PARAM_RAYPICK_RAYSEGS
//#ifndef VG10A
//		 
//		mSubVolRenderer->setPointer(IVT_PARAM_RAYPICK_RAYSEGS, &rayPickParams);
//		mVolRenderer->setPointer(IVT_PARAM_RAYPICK_RAYSEGS, &rayPickParams);
//		
//#endif
//
//		// send the result to client		
//		bufferSize = entries * ( 6 * sizeof(double) + sizeof(BOOL32));
//
//		resultBuffer = new char[bufferSize];
//		memset(resultBuffer, 0, bufferSize);
//
//		dataPtr = (IvtVector3D *)resultBuffer;
//		cnt = 0;
//
//		// copy the world coordinate vector array and voxel coordinate vector array
//		for (i = 0; i < entries; i++)
//		{
//			dataPtr[cnt++] = rayPickParams.worldCoords[i];
//			dataPtr[cnt++] = rayPickParams.voxelCoords[i];
//		}
//
//		char *tempBuffer = resultBuffer;
//		tempBuffer += entries * 6 * sizeof(double);
//
//		BOOL32 *intersectionFlagPtr = (BOOL32 *)tempBuffer;
//		cnt = 0;
//
//		// copy the intersection flag array
//		for (i = 0; i < entries; i++)
//		{
//			intersectionFlagPtr[cnt++] = rayPickParams.intersectionFlags[i];
//		}
//
//		// send the response that the ray pick action succeeded.
//		rayPickSucceeded = 1; // non-zero indicates the client ready to receive the ray surface intersection.
//		reqSender.rHtonl(&rayPickSucceeded);
//		reqSender.addChildElement(RAYPICK_ACTION, RAYPICKRESPONSE_SUCCEEDED, sizeof(int), &rayPickSucceeded);
//		reqSender.addChildElement(RAYPICK_ACTION, RAYPICKRESPONSE_SUCCEEDED, bufferSize, resultBuffer);
//		reqSender.send();
//
//
//		// free the memory
//		if (resultBuffer)
//		{
//			delete [] resultBuffer;
//			resultBuffer = 0;
//		}
//
//		if (rayPickParams.startRays)
//		{
//			delete [] rayPickParams.startRays;
//			rayPickParams.startRays = 0;
//		}
//
//		if (rayPickParams.endRays)
//		{
//			delete [] rayPickParams.endRays;
//			rayPickParams.endRays = 0;
//		}
//
//		if (rayPickParams.intersectionFlags)
//		{
//			delete [] rayPickParams.intersectionFlags;
//			rayPickParams.intersectionFlags = 0;
//		}
//
//		if (rayPickParams.worldCoords)
//		{
//			delete [] rayPickParams.worldCoords;
//			rayPickParams.worldCoords = 0;
//		}
//
//		if (rayPickParams.voxelCoords)
//		{
//			delete [] rayPickParams.voxelCoords;
//			rayPickParams.voxelCoords = 0;
//		}
//	}
//	//catch (RadException &e)
//	//{
//
//	//	if (resultBuffer)
//	//	{
//	//		delete [] resultBuffer;
//	//		resultBuffer = 0;
//	//	}
//
//	//	if (rayPickParams.startRays)
//	//	{
//	//		delete [] rayPickParams.startRays;
//	//		rayPickParams.startRays = 0;
//	//	}
//
//	//	if (rayPickParams.endRays)
//	//	{
//	//		delete [] rayPickParams.endRays;
//	//		rayPickParams.endRays = 0;
//	//	}
//
//	//	if (rayPickParams.intersectionFlags)
//	//	{
//	//		delete [] rayPickParams.intersectionFlags;
//	//		rayPickParams.intersectionFlags = 0;
//	//	}
//
//	//	if (rayPickParams.worldCoords)
//	//	{
//	//		delete [] rayPickParams.worldCoords;
//	//		rayPickParams.worldCoords = 0;
//	//	}
//
//	//	if (rayPickParams.voxelCoords)
//	//	{
//	//		delete [] rayPickParams.voxelCoords;
//	//		rayPickParams.voxelCoords = 0;
//	//	}
//
//	//	fprintf(stderr, "Caught RadException while finding ray surface intersection.\n");
//	//	fprintf(stderr, "RadException(source: %s, line: %d, type: %d, info: %S)\n",
//	//		e.file, e.line, e.type, e.message ? e.message : L"not available");
//	//}
//	catch(...)
//	{
//		if (resultBuffer)
//		{
//			delete [] resultBuffer;
//			resultBuffer = 0;
//		}
//
//		if (rayPickParams.startRays)
//		{
//			delete [] rayPickParams.startRays;
//			rayPickParams.startRays = 0;
//		}
//
//		if (rayPickParams.endRays)
//		{
//			delete [] rayPickParams.endRays;
//			rayPickParams.endRays = 0;
//		}
//
//		if (rayPickParams.intersectionFlags)
//		{
//			delete [] rayPickParams.intersectionFlags;
//			rayPickParams.intersectionFlags = 0;
//		}
//
//		if (rayPickParams.worldCoords)
//		{
//			delete [] rayPickParams.worldCoords;
//			rayPickParams.worldCoords = 0;
//		}
//
//		if (rayPickParams.voxelCoords)
//		{
//			delete [] rayPickParams.voxelCoords;
//			rayPickParams.voxelCoords = 0;
//		}
//
//		fprintf(stderr, "Caught unknown exception while finding ray surface intersection.\n");
//	}
//
//	return ;
}

/**
 * Called for each rendering request
 */
int XipRenderTask::render()
{
    //create a render action response object for sending to client later.
    reqSender.initSender(mStream, RENDER_ACTION);

    int renderActionDone = 0;
    if ( NULL==mRenderer )
    {
        // either the render action parameters are zero or the volume renderer is not initialized
        // send the response that the rendering not succeeded.
        reqSender.rHtonl(&renderActionDone);
        reqSender.addChildElement(RENDER_ACTION, RENDERACTIONRESPONSE_DONE, sizeof(int), &renderActionDone);
        reqSender.send();
        printf("Unable to perform rendering.\n");
        return -1;
    }
    
    try
    {
        unsigned char* buffer = NULL;
        int bufSize = mRenderer->renderVolume(reqReceiver, buffer);

        if ( NULL==buffer )
        {
            reqSender.rHtonl(&renderActionDone);
            reqSender.addChildElement(RENDER_ACTION, RENDERACTIONRESPONSE_DONE, sizeof(int), &renderActionDone);
            reqSender.send();
            printf("Unable to perform rendering.\n");
            return -1;
        }
        else
        {
            // rendering done.
            // send the response that the rendering succeeded.
            renderActionDone = bufSize; // non-zero indicates the client ready to receive the rendering context buffer
            reqSender.rHtonl(&renderActionDone);
            reqSender.addChildElement(RENDER_ACTION, RENDERACTIONRESPONSE_DONE, sizeof(int), &renderActionDone);
            reqSender.addChildElement(RENDER_ACTION, RENDERACTIONRESPONSE_BUFFER, bufSize, buffer);
            reqSender.send();
            return 0;
        }
    }
    catch (...)
    {
    	printf("Exception!\n");
    }


	return -1;
}

void XipRenderTask::setLut()
{
    reqSender.initSender(mStream, LUT_ACTION);

    int done = mRenderer->setLut(reqReceiver);
    //int done = 1;
    reqSender.rHtonl(&done);
    reqSender.addChildElement(LUT_ACTION, LUTACTIONRESPONSE_DONE, sizeof(int), &done);
    reqSender.send();
}

/**
 *	called to get the model matrix and send it to the client 
 */
void XipRenderTask::getModelMatrix()
{
	reqSender.initSender(mStream, GET_VOLUME_MODELMATRIX);
	float modelMatrix[16]; 

    mRenderer->getModelMatrix(modelMatrix);

    reqSender.rSwapf(modelMatrix, 16);
	reqSender.addChildElement(GET_VOLUME_MODELMATRIX, GETVOLUMEMMATRIXRESPONSE_MODELMATRIX, 16*sizeof(float), modelMatrix);
	reqSender.send();
}

/**
 *	called to get the bit depth and send it to the client 
 */
void XipRenderTask::getBitsUsed()
{
}

void XipRenderTask::loadDicom()
{
    // read dicom location 
    int len = 0;
    if ( !reqReceiver.getUniqueIntElement(DICOM_LOCATIONSIZE, len) )
    {
        return;
    }
    reqReceiver.rNtohl(&len);
    if ( len>1 && mRenderer ) 
    {
        char *str = reqReceiver.getElementContent(DICOM_LOCATION, len);
        mRenderer->loadDicom(str);
    }

    //create a Load response object for sending to client later.
    reqSender.initSender(mStream, LOAD_DICOM_ACTION);

    int volumeCount = 1;
    reqSender.rHtonl(&volumeCount);
    reqSender.addChildElement(LOAD_DICOM_ACTION, LOADDICOMRESPONSE_VOLUMECOUNT, sizeof(int), &volumeCount);

    XipVolumeHeader volHeader;
    volHeader.width = 512;
    volHeader.height = 512;
    volHeader.depth = 512;
    volHeader.bitsUsed = 12;

    mRenderer->getModelMatrix(volHeader.modelMatrix);
    reqSender.rSwapf(volHeader.modelMatrix, 16);
    reqSender.rHtonl(&volHeader.height);
    reqSender.rHtonl(&volHeader.width);
    reqSender.rHtonl(&volHeader.depth);
    reqSender.rHtonl(&volHeader.bitsUsed);
    reqSender.rHtonl(&volHeader.samplesPerPixel);

    reqSender.addChildElement(LOAD_DICOM_ACTION, LOADDICOMRESPONSE_VOLUMEHEADER, sizeof(XipVolumeHeader), &volHeader);

    reqSender.send();   
}
