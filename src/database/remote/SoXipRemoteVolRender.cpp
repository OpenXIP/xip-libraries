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


#include "SoXipRemoteVolRender.h"
#include "SoXipClientElement.h"

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h> 
#include <Inventor/sensors/SoAlarmSensor.h>
#include <Inventor/elements/SoClipPlaneElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoGLLightIdElement.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <xip/inventor/core/SoXipMprPlaneElement.h>
#include <xip/inventor/core/SoXipLutElement.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/system/GL/gl.h>

#include "PreciseTimer.h"

#include <math.h>
#include <sstream>


SO_NODE_SOURCE(SoXipRemoteVolRender);

static bufferImage img;

// --------------------------------------------------------------------------
//! Constructor, creates fields
// --------------------------------------------------------------------------
SoXipRemoteVolRender::SoXipRemoteVolRender()
{
	SO_NODE_CONSTRUCTOR(SoXipRemoteVolRender);

	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(mergeOpenGL, (TRUE));
	SO_NODE_ADD_FIELD(blend, (TRUE));
	SO_NODE_ADD_FIELD(volumeInput, (0));
	SO_NODE_ADD_FIELD(bitsUsed, (12));
	SO_NODE_ADD_FIELD(compQty, (85));
	SO_NODE_ADD_FIELD(planeId, (0));
	SO_NODE_ADD_FIELD(fps, ("fps 0.0"));

	SO_NODE_DEFINE_ENUM_VALUE(comp, UNCOMPRESSED);
	//SO_NODE_DEFINE_ENUM_VALUE(comp, COMPRESSED);
	SO_NODE_SET_SF_ENUM_TYPE(compType, comp);

	SO_NODE_ADD_FIELD(compType, (UNCOMPRESSED));

	SO_NODE_ADD_FIELD(fullQualityMpr, (FALSE));

	SO_NODE_DEFINE_ENUM_VALUE(smart, NONE);
	SO_NODE_DEFINE_ENUM_VALUE(smart, SMART_1);
	SO_NODE_DEFINE_ENUM_VALUE(smart, SMART_2);
	SO_NODE_DEFINE_ENUM_VALUE(smart, AUTO);
	SO_NODE_SET_SF_ENUM_TYPE(smartMode, smart);

	SO_NODE_ADD_FIELD(smartMode, (SMART_1));
	SO_NODE_ADD_FIELD(smartFpsThreshold, (11));
	SO_NODE_ADD_FIELD(lowQualityThreshold, (3.5));

	mIsRenderModeColor = FALSE;
	//mClipPlaneTable = NULL;
	//mLut = NULL;
	mStream = NULL;
	mVolumeBuffer = NULL;
	//mGrayVolumeBuffer = NULL;
	mSizeVolumeBuffer = 0;
	//mSizeGrayVolumeBuffer = 0;
	//mNbClipPlane = 0;
	mIsAllocatedManually = false;
	mRemoteModelMatrix = NULL;
	//mIsMpr = false;
	//mIsthickness = 0;
	//mSizeThickness = 0.0;

	//mCompiledTabLut = NULL;
	//mSizeLut = 0;
	//mCompiledTabAlpha = NULL;
	//mSizeTabAlpha = 0;

	compression = 1;

	//mprFlag = false;
 
	//planeId = 0;
	//mprLowQuality =false;
 	//smartPlaneCompression = false;

	quality = 0.0;
	firstTime = true;

	//requireHQ =	new SoAlarmSensor();
    //requireHQ = NULL;
	//lastFrameHQ = true;
	//fromCallback = false;

	//thresholdBuffer.resize(4);
	//smartThresholdTemp.resize(4);
	//for(int i = 0; i < 4; i++)
	//{
	//	thresholdBuffer[i] = 0.0;
	//	smartThresholdTemp[i] = 0.0;
	//}

	//thresholdIdx = 0;

	float threshold = 2.5;
	
	//mprBuffer.reserve(1000064);
	//mVolumeBufferOut.reserve(1000064);
	//grayVolumeBufferTmp.reserve(1000064);
	//Temp.reserve(1000064);

	//mClientValidate = new clientValid();

	//mClientValidate->cvRLE = false;
	//mClientValidate->cvHUFF = false;
	//mClientValidate->cvDRLE = false;
	//mClientValidate->cvDHUFF = false;
	//mClientValidate->cvLOSSYJ = false;

    mLutId = 0;
	mValidate = false;
 }

// --------------------------------------------------------------------------
//! Initializes this class. Called on dll initialization.
// --------------------------------------------------------------------------
void SoXipRemoteVolRender::initClass()
{
	SO_NODE_INIT_CLASS(SoXipRemoteVolRender, SoShape, "Shape");

	SO_ENABLE(SoGLRenderAction,       SoClipPlaneElement); 
	SO_ENABLE(SoGLRenderAction,       SoComplexityElement); 
	SO_ENABLE(SoGLRenderAction,       SoXipRenderModeElement); 
	SO_ENABLE(SoGLRenderAction,       SoProjectionMatrixElement); 
	SO_ENABLE(SoGLRenderAction,       SoViewingMatrixElement); 
	SO_ENABLE(SoGLRenderAction,       SoViewportRegionElement); 
	SO_ENABLE(SoGLRenderAction,       SoXipLutElement); 
    SO_ENABLE(SoGLRenderAction,       SoXipClientElement); 
	SO_ENABLE(SoGLRenderAction,       SoLazyElement); 
	SO_ENABLE(SoGLRenderAction,       SoGLLightIdElement); 
	SO_ENABLE(SoGLRenderAction,       SoXipMprPlaneElement);
    SO_ENABLE(SoGLRenderAction,       SoViewVolumeElement);

	SO_ENABLE(SoRayPickAction,		  SoXipRenderModeElement); 
	SO_ENABLE(SoRayPickAction,        SoProjectionMatrixElement); 
	SO_ENABLE(SoRayPickAction,        SoViewingMatrixElement); 
    SO_ENABLE(SoRayPickAction,        SoViewVolumeElement);
}
 
/*
* Protected destructor to cleans up internally created nodes and node sensor.
*/
SoXipRemoteVolRender::~SoXipRemoteVolRender()
{
	//deleteClipPlanes();
	deleteColorBuffer();
	//deleteGrayBuffer();

	if(mRemoteModelMatrix)
	{
		delete mRemoteModelMatrix;
		mRemoteModelMatrix = NULL;
	}
}
 
/*
* called when a scene bounding box is computed
*/
void SoXipRemoteVolRender::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
	//if(!mStream)
	//{
	//	//-----------------------------------
	//	// update connection information
	//	SoXipDataConnection *vol = volumeInput.getValue();
	//	if(vol)
	//	{
	//		XipDataConnection * sVol = vol->get();
	//		if(sVol)
	//			mStream = sVol->mStream;
	//	}
	//    
 //       if(!mStream) return;
	//}

    center.setValue(0.5, 0.5, 0.5);
    box.setBounds(0, 0, 0, 1, 1, 1);

    return;

	//float m[16];

	//try
	//{
	//	//send the request for modelMatrix	
	//	mReqSender.initSender(mStream, GET_VOLUME_MODELMATRIX);
	//	mReqSender.send();	
	//	// expect the  response from the server.
	//	// expect the load response from the server.Special request without asking for the volume buffer
	//	mReqReceiver.initReceiver(mStream);
	//	mReqReceiver.receive();
	//		// if there is some error or the  sorting operation did not result in a valid volume.
	//	if( (mReqReceiver.getFirstElementId() != GET_VOLUME_MODELMATRIX))
	//	{
	//		SoError::post("ComputeBBox: Server modelMatrix request error!\n");
	//		return;
	//	}

	//	mprFlag = false;

	//	memTransfers.fastMemcopy((unsigned char *)&m[0], (unsigned char *)mReqReceiver.getElementContent(GETVOLUMEMMATRIXRESPONSE_MODELMATRIX, 16*sizeof(float)),16*sizeof(float));				
	//	if(!&m[0])
	//	{
	//		SoError::post("ComputeBBox: Server modelMatrix request error!\n");
	//		return;
	//	}
	//	mReqReceiver.rSwapf(&m[0], 16);
	//		
	//	//SbMatrix * remoteModelMatrix = new SbMatrix(
	//	//m[0], m[4], m[8], m[12],
	//	//m[1], m[5], m[9], m[13], 
	//	//m[2], m[6], m[10], m[14],
	//	//m[3], m[7], m[11], m[15]);

 //       SbMatrix * remoteModelMatrix = new SbMatrix(
 //           m[0], m[1], m[2], m[3],
 //           m[4], m[5], m[6], m[7], 
 //           m[8], m[9], m[10], m[11],
 //           m[12], m[13], m[14], m[15]);

 //      
	//	
	//	if(mRemoteModelMatrix != remoteModelMatrix)
	//	{
	//		mRemoteModelMatrix = remoteModelMatrix;
	//	 
	//	}
	//	/*mRemoteModelMatrix = new SbMatrix(
	//		m[0], m[4], m[8], m[12],
	//		m[1], m[5], m[9], m[13], 
	//		m[2], m[6], m[10], m[14],
	//		m[3], m[7], m[11], m[15]);*/
	//}
	//catch (...)
	//{
	//	SoError::post("ComputeBBox: Caught Unknown while requesting model matrix!\n");
	//		if(mRemoteModelMatrix)
	//	{
	//		delete mRemoteModelMatrix;
	//		mRemoteModelMatrix = NULL;
	//	}
	//	return;
	//}

	//box.makeEmpty();
	//center = SbVec3f(0, 0, 0);

 //   SbMatrix mat = mRemoteModelMatrix->transpose();

	//for (int s = 0; s < 8; s++)
	//{
	//	SbVec3f out;
 //       SbVec3f in((s&1) ? 1 : 0, (s&2) ? 1 : 0, (s&4) ? 1 : 0);
	//	mat.multMatrixVec(in, out);
	//	box.extendBy(out);
	//}

	//center = (box.getMax() - box.getMin()) / 2;
}

/*
*! called whenever the scene is rendered
*/
void SoXipRemoteVolRender::GLRender(SoGLRenderAction * action)
{	
	if(!mValidate)
	if(clientValidation()==0)
	{
		mValidate = true;
		#if _DEBUG
			SoDebugError::postInfo("Client IS validated", "");
		#endif
	}
	doAction(action);
	SoShape::GLRender(action);
}

/*
*! callback method
*/
void SoXipRemoteVolRender::callback(SoCallbackAction *action)
{	
	doAction(action);
	SoShape::callback(action);
}

/*
*! called when picking
*/
void SoXipRemoteVolRender::pick(SoPickAction *action)
{
	doAction(action);
	SoShape::pick(action);
}

/*
*! called when ray picking
*/
void SoXipRemoteVolRender::rayPick(SoRayPickAction *action)
{
	rayPickAction(action);
	SoShape::rayPick(action);
}

/*
*! called when last frame required is lossy compressed
*/
void
SoXipRemoteVolRender::fullQualityFlagCallback(void *data, SoSensor *action)
{
 //   SoXipRemoteVolRender* thisPtr = ((SoXipRemoteVolRender *)data);

	//if (!thisPtr)
	//	return;

	//thisPtr->fromCallback = true;
 //	try
	//{
	//	if(thisPtr->getInputParams() == 0)
	//	{
	//		if(thisPtr->render() != 0)
	//		{	
	//			return;
	//			SoError::post("Error on fullQualityFlagCallback()");	
	//		}
	//		else
	//		{
	//			#if _DEBUG
	//				SoDebugError::postInfo("Callback: ","");
	//			#endif
	//			
	//			thisPtr->smartPlaneCompression = false;
 //				thisPtr->fps.setValue(thisPtr->smartFpsThreshold.getValue());
	//		}
	//	}
	//}
	//catch (...)
	//{
	//	SoError::post("Caught Unknown Exception during callback rendering!\n");
	//}

	////draw the image buffer on the screen
	//thisPtr->drawImage();

}

/*
*! This implements generic traversal of SoRadRemoteVolRender node, used in
*  both of the above methods.
*/
void SoXipRemoteVolRender::doAction(SoAction * action)
{
	if (!action || !on.getValue()) return;

	// if not of type SoGLRenderAction or no volRenderAction, exit here
	if (!action->isOfType(SoGLRenderAction::getClassTypeId()))
		return;

	//render a new image of the volume only if something change in parameters
	//and if there is no errors
	try
	{

		if(getElements(action) == 0)
		{
			if(getInputParams() == 0)
			{
				static CPreciseTimer oPreciseTimer;
				oPreciseTimer.StartTimer();

				if(render() != 0)
				{	
					return;	
				}
			}
		}
	}
	catch (...)
	{
		SoError::post("Caught Unknown Exception during rendering!\n");
	}

    //draw the image buffer on the screen
    drawImage();
}

/*
*! Call to delete the volume color buffer if exist
*/
void SoXipRemoteVolRender::deleteColorBuffer()
{
	if(mVolumeBuffer && mIsAllocatedManually)
	{
		delete mVolumeBuffer;
		mVolumeBuffer = NULL;
		mSizeVolumeBuffer = 0;
		mIsAllocatedManually = false;
	}
}

///*
//*! Call to delete the volume gray buffer if exist
//*/
//void SoXipRemoteVolRender::deleteGrayBuffer()
//{
//	//if(mGrayVolumeBuffer)
//	//{
//	//	mGrayVolumeBuffer = NULL;
//	//	mSizeGrayVolumeBuffer = 0;
//	//}
//}

/*
*! RGBA byte buffer allocation
*/
void SoXipRemoteVolRender::RGBAallocation(unsigned int colorBufferSize)
{
	if(!mIsAllocatedManually || (colorBufferSize > mSizeVolumeBuffer))
	{
		deleteColorBuffer();
		mVolumeBuffer = new unsigned char[colorBufferSize];
		mSizeVolumeBuffer = colorBufferSize;
		mIsAllocatedManually = true;
	}
}

/*
*! Get the information we need to ask a image of the required volume to the server
*/
int SoXipRemoteVolRender::getElements(SoAction * action)
{
	if (!action) return -1;

	// get action state
	SoState* state = action->getState();
	 
	if (!state)	return -1;

	// used to know if one or more elements change since last rendering
	bool hasParamChanged = false;	
	  
	// get clipplanes elements
	//const SoClipPlaneElement *clipPlaneElement = SoClipPlaneElement::getInstance(state);
	//int NumPlane = clipPlaneElement->getNum();

	//if (NumPlane > 0)
	//{
	//	if(NumPlane != mNbClipPlane)
	//	{
	//		deleteClipPlanes();
	//		mNbClipPlane = NumPlane;
	//		mClipPlaneTable = new SbPlane[mNbClipPlane];
	//		hasParamChanged = true;
	//	}

	//	for(int i=0; i<mNbClipPlane; i++)
	//	{
	//		if(mClipPlaneTable[i] != clipPlaneElement->get(i))
	//		{
	//			mClipPlaneTable[i] = clipPlaneElement->get(i);
	//			hasParamChanged = true;
	//		}
	//	}
	//}


	////-----------------------------------
	////update render quality
	//quality = SoComplexityElement::get(state)  * 2.f;
	//
	//if(mRenderQuality != quality)
	//{
	//	mRenderQuality = quality;
	//	hasParamChanged = true;
	//}

	//-----------------------------------	
	//update render mode
	SoXipRenderModeElement::RenderModes rMode = SoXipRenderModeElement::get(state);
	if(mRenderMode != rMode)
	{
		mRenderMode = rMode;
		hasParamChanged = true;
	}

	////-----------------------------------
	//// update model transformation 
	//SbMatrix TMatrix = SoBBoxModelMatrixElement::get(state);
	//if(mTransformMatrix != TMatrix)
	//{
	//	mTransformMatrix = TMatrix;
	//	hasParamChanged = true;
	//}

	////-----------------------------------
	//// update projection matrix
	//SbMatrix PMatrix = SoProjectionMatrixElement::get(state);
	//if(mProjMatrix != PMatrix)
	//{
	//	mProjMatrix = PMatrix;
	//	hasParamChanged = true;
	//}


	////-----------------------------------
	//// update viewing matrix
	//SbMatrix VMatrix = SoViewingMatrixElement::get(state);
	//if(mViewMatrix != VMatrix)
	//{
	//	mViewMatrix = VMatrix;
	//	hasParamChanged = true;
	//}

    SbViewVolume viewVolume = SoViewVolumeElement::get(state);
    SbMatrix viewMat, projMat;
    viewVolume.getMatrices(viewMat, projMat);
    viewMat = viewMat.transpose();

    SbVec3f pos = viewVolume.getProjectionPoint();
    if ( mCamPosition != pos )
    {
        mCamPosition = pos;
        hasParamChanged = true;
    }

    SbVec3f t,s;
    SbRotation r, so;
    viewMat.getTransform(t, r, s, so);
    if ( mCamOrientation!=r )
    {
        mCamOrientation = r;
        hasParamChanged = true;
    }

    float ratio = viewVolume.getWidth()/viewVolume.getHeight();
    if ( mCamRatio!=ratio )
    {
        mCamRatio = ratio;
        hasParamChanged = true;
    }

    float zNear = viewVolume.getNearDist();
    if ( mCamNearDistance!=zNear )
    {
        mCamNearDistance = zNear;
        hasParamChanged = true;
    }

    float zFar = zNear + viewVolume.getDepth();
    if ( mCamFarDistance != zFar )
    {
        mCamFarDistance = zFar;
        hasParamChanged = true;
    }

    if ( mCamHeight != viewVolume.getHeight() )
    {
        mCamHeight = viewVolume.getHeight();
        hasParamChanged = true;
    }

    //SbVec3f projPoint = viewVolume.projPoint;
    //SoDebugError::postInfo("SoXipRemoteVolRender::getElements", "projPoint = %f %f %f", projPoint[0], projPoint[1], projPoint[2]);

    //SbVec3f projDir = viewVolume.projDir;
    //SoDebugError::postInfo("SoXipRemoteVolRender::getElements", "projDir = %f %f %f", projDir[0], projDir[1], projDir[2]);

    //SoXipExaminer* examiner = (SoXipExaminer*)SoNode::getByName(SbName("examiner"));
    //SoOrthographicCamera* oc = (SoOrthographicCamera*)(examiner->getCamera());

    //SbRotation rot1(viewVolume.projDir, SbVec3f(0.0f, 0.0f, -1.0f));
    //const float *val = oc->orientation.getValue().getValue();
    //SoDebugError::postInfo("SoXipRemoteVolRender::getElements", "%f %f %f %f", val[0], val[1], val[2], val[3]);

	//-----------------------------------
	// update viewport
	SbViewportRegion viewPortRegion = SoViewportRegionElement::get(state);

	float viewP0 = viewPortRegion.getViewportOriginPixels()[0];
	float viewP1 = viewPortRegion.getViewportOriginPixels()[1];
	float viewP2 = viewPortRegion.getViewportSizePixels()[0];
	float viewP3 = viewPortRegion.getViewportSizePixels()[1];


	if(mViewport[0] != viewP0)
	{
		mViewport[0] = viewP0;
		hasParamChanged = true;
	}

	if(mViewport[1] != viewP1)
	{
		
		mViewport[1] = viewP1;
		hasParamChanged = true;
	}

	if(mViewport[2] != viewP2)
	{
		//int check = (int)viewP2 % 4;
		//mViewport[2] = viewP2 - check; 
		mViewport[2] = viewP2;
		hasParamChanged = true;
	}
	

	if(mViewport[3] != viewP3)
	{
		mViewport[3] = viewP3;
		hasParamChanged = true;
	}

	//-----------------------------------
	// update LUT
	//SoXipData *lut = SoXipLutElement::get(state);
	//if (lut)
	//{
	//	uint32_t testLut = lut->getDataId();
	//	if(testLut != mLutId)
	//	{
	//		hasParamChanged = true;
	//		mLutId = testLut;
 //       }
 //   }

    bool clienthasChanged = SoXipClientElement::get(state);
    if(clienthasChanged)
    {
        hasParamChanged = true;
    }

	//		SbXipImage* ptLut = ((SoXipDataImage*) lut)->get();
	//		if(ptLut)
	//		{
	//			SbXipImageDimensions dimLut = ptLut->getDimStored();
	//			int sizeLut = dimLut[0] * dimLut[1] * dimLut[2];
	//			mLut = ptLut;

	//			if(sizeLut > mSizeLut)
	//			{
	//				mSizeLut = sizeLut;

	//				if(mCompiledTabLut)
	//					delete mCompiledTabLut;

	//				mCompiledTabLut = new unsigned char[mSizeLut*4];
	//			}

	//			
	//			unsigned char * ptrTabLut = mCompiledTabLut;
	//			const float * radLutBuffer = (float *) mLut->refBufferPtr();
	//			for(int i=0; i<mSizeLut*4; i++)
	//			{
	//				*ptrTabLut++ = (*radLutBuffer++ * 255.0);
	//			}
	//		}
	//	}
	//}
	
	//-----------------------------------
	// update bitUsed
	int bitUsed = bitsUsed.getValue();
	if(mBitsUsed != bitUsed)
	{
		mBitsUsed = bitUsed;
		hasParamChanged = true;
		//shouldChangeAlphaTab = true;
	}

	////-----------------------------------
	//// update material
	//SbColor lazyColor = SoLazyElement::getDefaultDiffuse();


	//// Setup the default values
	//float Ambient = 0.25f;
	//float Specular = 0.3f;
	//float Shineness = 64.0f;
	//float Diffuse = 0.6f;
	//SbColor SurfaceColor = lazyColor;	

	//SoLazyElement *lazyElem = SoLazyElement::getInstance( state );
	//
	//// Use external material when it is available.
	//if( lazyElem )
	//{
	//	float r, g, b;

	//	//get all the color properties from Lazy Element.
	//	SbColor ambColor, specColor, diffColor;

	//	//ambient
	//	ambColor = lazyElem->getAmbient( state );
	//	ambColor.getValue( r, g, b );
	//	Ambient = 0.30 * r + 0.59 * g + 0.11 * b;

	//	//specular
	//	specColor = lazyElem->getSpecular( state );
	//	specColor.getValue( r, g, b ); 
	//	Specular = 0.30 * r + 0.59 * g + 0.11 * b;

	//	//diffuse
	//	if (lazyElem->getNumDiffuse())
	//	{
	//		diffColor = lazyElem->getDiffuse( state, 0 );
	//		diffColor.getValue( r, g, b ); 
	//		Diffuse = 0.30 * r + 0.59 * g + 0.11 * b;
	//	}

	//	//shineness
	//	Shineness = lazyElem->getShininess( state ) * 128.0;

	//	//surface color
	//	if (lazyElem->getNumDiffuse() > 0)
	//	{
	//		SurfaceColor = lazyElem->getDiffuse( state, lazyElem->getNumDiffuse() - 1);
	//	}
	//	else
	//	{
	//		SurfaceColor = lazyElem->getDefaultDiffuse();
	//	}
	//}

	//if(mAmbient != Ambient)
	//{
	//	mAmbient = Ambient;
	//	hasParamChanged = true;
	//}

	//if(mSpecular != Specular)
	//{
	//	mSpecular = Specular;
	//	hasParamChanged = true;
	//}

	//if(mShineness != Shineness)
	//{
	//	mShineness = Shineness;
	//	hasParamChanged = true;
	//}

	//if(mDiffuse != Diffuse)
	//{
	//	mDiffuse = Diffuse;
	//	hasParamChanged = true;
	//}

	//if(mSurfaceColor != SurfaceColor)
	//{
	//	mSurfaceColor = SurfaceColor;
	//	hasParamChanged = true;
	//}



	//-----------------------------------
	// update connection information
	XipStreamBase *Stream = 0;

	SoXipDataConnection *vol = volumeInput.getValue();
	if(vol)
	{
		XipDataConnection * sVol = vol->get();
		if(sVol)
		{
			Stream = sVol->mStream;
		}
	}

	if(mStream != Stream)
	{
		mStream = Stream;
		hasParamChanged = true;
	}

	////-----------------------------------
	//// update light
	//GLboolean isLightEnabled;

	//int lightIndex = SoGLLightIdElement::get( state );
	//if( lightIndex >= 0 )
	//	isLightEnabled = glIsEnabled( GL_LIGHT0 + lightIndex );
	//else
	//	isLightEnabled = FALSE;

	//isLightEnabled &= (SoLazyElement::getLightModel(state) == SoLazyElement::PHONG);

	//if(mLightEnabled != (isLightEnabled == TRUE))
	//{
	//	mLightEnabled = (isLightEnabled == TRUE);
	//	hasParamChanged = true;
	//}



	//-----------------------------------
	// update MPR
	int mprPlanes = 0;
	SoXipMprPlaneElement *mprElement = SoXipMprPlaneElement::getInstance(state);
	

	//smartFlag = smartMode.getValue();
	//if (mprElement)
	//{
	//	mprPlanes = mprElement->getNum();
	//	
	//	if (mprPlanes > 0)
	//	{ 
	//		if(!mIsMpr)
	//		{
	//			mIsMpr = true;
	//			hasParamChanged = true;	
	//		}
	//		SbMatrix mprModel = mprElement->getMatrix(mprPlanes - 1);
	//		
	//		if(mMprModelMatrix != mprModel)
	//		{
	//			mMprModelMatrix = mprModel;
	//			hasParamChanged = true;			
	//		}
	//		SbVec3f mprCenter = mprElement->getCenter(mprPlanes - 1);
	//		
	//		
	//		// using AUTO mode if the fps are less than smartFpsThreshold the SMART_2 mode will
	//		// be activated
	//		if( smartFlag == AUTO )
	//			if (mFramePerSecond < smartFpsThreshold.getValue()) smartFlag = SMART_2;
	//			else smartFlag = SMART_1;
	//	
	//		if(smartFlag!=NONE)
	//		{
	//			if(mMprCenter != mprCenter)
	//			{
	//				if(!firstTime)
	//				{	
 //
	//					bool Xchanges = false, Ychanges = false, Zchanges = false; 
	//					bool A = false, B = false, C = false;

	//					SbVec3f deltaCenter = mprCenter - mMprCenter ;
	//					if(fabs(deltaCenter[0]) > 0.0001) Xchanges = true;
	//					if(fabs(deltaCenter[1]) > 0.0001) Ychanges = true;
	//					if(fabs(deltaCenter[2]) > 0.0001) Zchanges = true;

	//					smartPlaneCompression = false;	
	//						
	//					switch(smartFlag)
	//					{
	//													
	//						case SMART_1:
	//						{
	//							if((Zchanges)||(Xchanges)||(Ychanges))	smartPlaneCompression = true;
	//														
	//							SbVec3f viewChanges;

	//							float * pView = mViewMatrix.operator float *();
	//							viewChanges.setValue(pView[12], pView[13], pView[14]);

	//							SbVec3f differences = viewChanges - deltaView;

	//							if(fabs(differences[2]) < lowQualityThreshold.getValue()) smartPlaneCompression = false;

	//							if((fullQualityMpr.getValue()) && (quality < 1.0))smartPlaneCompression = false;
	//							break;
	//						}
	//						case SMART_2:
	//						{
	//							if((fullQualityMpr.getValue()) && (quality < 1.0))smartPlaneCompression = false;
	//							else if((Zchanges)||(Xchanges)||(Ychanges))	smartPlaneCompression = true;
	//							break;
	//						}
	//					}//switch

	//				}
	//				else firstTime = false;
	//				
	//				mMprCenter = mprElement->getCenter(mprPlanes - 1);

	//				float * pView = mViewMatrix.operator float *();
	//				deltaView.setValue(pView[12], pView[13], pView[14]);	

	//			}
	//		}		
	//	}	
	//	else
	//	{
	//		smartPlaneCompression = false;
	//	}
	//}	
	
	//if(shouldChangeAlphaTab)
	//{
	//	int numEntries = 1 << mBitsUsed;
	//	int tmpEntries = numEntries >> 4;
	//	
	//	if(mSizeTabAlpha < mViewport[2] * mViewport[3])
	//	{
	//		if(mCompiledTabAlpha)
	//			delete mCompiledTabAlpha;

	//		mSizeTabAlpha = mViewport[2] * mViewport[3];
	//		mCompiledTabAlpha = new unsigned char [mSizeTabAlpha];
	//	}

	//	unsigned char  maxAlpha = mCompiledTabLut[numEntries*4 - 1];
	//	unsigned char * ptrTabAlpha = mCompiledTabAlpha;

	//	for(int i=0; i< mSizeTabAlpha; i++)
	//		*ptrTabAlpha++ = min(maxAlpha, (int)((1.0 / (tmpEntries)) * i * maxAlpha));

	//}

	// callback timer setup
	if(hasParamChanged)
	{
		//if(((mRenderQuality!=1.0)||(smartPlaneCompression))&&(mRenderMode == SoXipRenderModeElement::MPR))
		//{
		//	requireHQ->setFunction(fullQualityFlagCallback);
		//	requireHQ->setData(this);
		//	requireHQ->setTimeFromNow(0.5); 
		//	requireHQ->schedule();
		//	return 0;
		//}
		//else
		//{
		//	// if is the callback is scheduled and a lossy image is required by the client 
		//	// the callback will be unscheduled.
		//	if (requireHQ->isScheduled()) requireHQ->unschedule();
		//	return 0;
		//}		
        return 0;
	}
	else
		return 1;
}


/*
*! Gather the information in the good structure before sending it to the server
*/
int SoXipRemoteVolRender::getInputParams()
{	
	mReqSender.initSender(mStream, RENDER_ACTION);

	//if(smartPlaneCompression ) 
	//	mFullLossy = 1;
	//else 
	//	mFullLossy = 0;

	//mReqSender.rHtonl(&mFullLossy);
	//mReqSender.addChildElement(RENDER_ACTION, RENDERACTION_RENDERQUALITY, sizeof(int), &mFullLossy);

	// check the lossy compression quality parameter
	// and apply constrains on it.
	//if((compQty.getValue()>25)&&(compQty.getValue()<86))
	//{
	//	mCompressionQuality = compQty.getValue();
	//}
	//else if(compQty.getValue()<26)
	//{
	//	mCompressionQuality = 26;
	//	compQty.setValue(26);
	//}
	//else if(compQty.getValue()>85)
	//{
	//	mCompressionQuality = 85;
	//	compQty.setValue(85);
	//}

	//mReqSender.rHtonl(&mCompressionQuality);
	//mReqSender.addNextElement(RENDERACTION_RENDERQUALITY, RENDERACTION_COMPRESSIONQUALITY, sizeof(int), &mCompressionQuality);


	//// render quality
	//if(quality == 1.0)
	//	fullComplexity=true;
	//else 
	//	fullComplexity = false;
	//
	//mReqSender.rSwapd(&mRenderQuality);
	//mReqSender.addNextElement(RENDERACTION_RENDERQUALITY, RENDERACTION_RENDERQUALITY_VALUE, sizeof(double), &mRenderQuality);


	//if(fromCallback) mCallbackRequest = 1;
	//else mCallbackRequest =0;

	//mReqSender.rHtonl(&mCallbackRequest);
	//mReqSender.addChildElement(RENDER_ACTION, RENDERACTION_CALLBACK_FLAG, sizeof(int), &mCallbackRequest);

	 
	//render mode
	switch(mRenderMode)
	{
		case SoXipRenderModeElement::MPR:		mRenderModeT = XIP_RENDERMODE_MPR; mIsRenderModeColor = FALSE; break;
		case SoXipRenderModeElement::MAXIP:		mRenderModeT = XIP_RENDERMODE_MAXIP; mIsRenderModeColor = FALSE; break;
		case SoXipRenderModeElement::MINIP:		mRenderModeT = XIP_RENDERMODE_MINIP; mIsRenderModeColor = FALSE; break;
		case SoXipRenderModeElement::SSD:		mRenderModeT = XIP_RENDERMODE_SSD; mIsRenderModeColor = FALSE; break;
		case SoXipRenderModeElement::SSD_COLOR:	mRenderModeT = XIP_RENDERMODE_SSD_COLOR; mIsRenderModeColor = TRUE; break;
		case SoXipRenderModeElement::VRT_COLOR:	mRenderModeT = XIP_RENDERMODE_VRT_COLOR; mIsRenderModeColor = TRUE; break;
		case SoXipRenderModeElement::DRR:		mRenderModeT = XIP_RENDERMODE_DRR; mIsRenderModeColor = FALSE; break;
		default:
			SoError::post("Unsupported rendering mode!\n");
			return -1;
	}
	
	mReqSender.rHtons(&mRenderModeT);
	mReqSender.addChildElement(RENDER_ACTION, RENDERACTION_RENDERMODE, sizeof(short), &mRenderModeT);

	compression = compType.getValue();
	

	//// map the compression request
	//if (compression != UNCOMPRESSED)
	//{
	//	if (mRenderMode == SoXipRenderModeElement::MPR)
	//	{	
	//		if(smartPlaneCompression && (smartFlag != NONE))
	//			compression = LOSSY;
	//		else 
	//			compression = LOSSLESSLY_DIFFERENTIAL;
	//	}		
	//	else
	//	{
	//		if (quality != 1) 
	//			compression = LOSSY;
	//		else 
	//			compression = LOSSLESSLY_HUFF_MODE;
	//	}
	//
	//
	//	if(fromCallback)
	//	{
	//		fromCallback = false;
	//		compression = LOSSLESSLY_DIFFERENTIAL;
	//	}
	//}

	int compr =  compressionMap(compression);
	mReqSender.rHtonl(&compr);
	mReqSender.addChildElement(RENDER_ACTION, RENDERACTION_COMPRESSIONTYPE, sizeof(int), &compr);

	//plane = planeId.getValue();
	//mReqSender.rHtonl(&plane);
	//mReqSender.addNextElement(RENDERACTION_RENDERQUALITY, RENDERACTION_MPRPLANE, sizeof(int), &plane);

	//alpha = blend.getValue();
	//mReqSender.rHtonl(&alpha);
	//mReqSender.addNextElement(RENDERACTION_RENDERQUALITY, RENDERACTION_ALPHAHANDLING, sizeof(int), &alpha);

	//int mprReset = 0;
	//if(!mprFlag) mprReset = 1;
	//else mprReset = 0;

	//mReqSender.rHtonl(&mprReset);
	//mReqSender.addNextElement(RENDERACTION_RENDERQUALITY, RENDERACTION_MPRRESET, sizeof(int), &mprReset);

	// rendering context size
	mRcWidth = mViewport[2];
	mRcHeight = mViewport[3];

	mReqSender.addNextElement(RENDERACTION_RENDERMODE, RENDERACTION_RC);
	mReqSender.rHtonl(&mRcWidth);
	mReqSender.addChildElement(RENDERACTION_RC, RENDERACTION_RCWIDTH, sizeof(int), &mRcWidth);
	mReqSender.rHtonl(&mRcHeight);
	mReqSender.addChildElement(RENDERACTION_RC, RENDERACTION_RCHEIGHT, sizeof(int), &mRcHeight);

	//// LUT and material
	//if(	setLUT() == 0)
	//{	
	//	mReqSender.rHtons(mThreshold,2);
	//	mReqSender.addNextElement(RENDERACTION_RC, RENDERACTION_THRESHOLD, 2*sizeof(short), mThreshold);

	//	mReqSender.rSwapf(mColorBuffer, 12);
	//	mReqSender.addNextElement(RENDERACTION_THRESHOLD, RENDERACTION_COLOR, 12*sizeof(float), mColorBuffer);

	//	mReqSender.rSwapd(mMaterial, 4);
	//	mReqSender.addNextElement(RENDERACTION_COLOR, RENDERACTION_MATERIAL, 4*sizeof(double), mMaterial);		
	//}

	// camera
	mReqSender.addNextElement(RENDERACTION_RC, RENDERACTION_CAMERA);

	// viewport
	mViewportTab[0] = 0;
	mViewportTab[1] = 0;
	mViewportTab[2] = mViewport[2];
	mViewportTab[3] = mViewport[3];
	mReqSender.rHtonl(mViewportTab,4);
	mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_VIEWPORT, 4*sizeof(int), mViewportTab);

	//// light 
	//mIsLightOn = (int)mLightEnabled;
	//mReqSender.rHtonl(&mIsLightOn);
	//mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_LIGHTENABLED, sizeof(int), &mIsLightOn);
	
	//// view, transform and projection matrix
	//float * transPointer = mTransformMatrix.operator float *();
	//float * viewPointer = mViewMatrix.operator float *();
	//float * ProjPointer = mProjMatrix.operator float *();

	//
	//for(int i=0; i<16; i++)
	//{
	//	mTransfM[i] = transPointer[i];
	//	mViewM[i] = viewPointer[i];
	//	mProjM[i] = ProjPointer[i];
	//}


	//mReqSender.rSwapf(mTransfM, 16);
	//mReqSender.rSwapf(mViewM, 16);
	//mReqSender.rSwapf(mProjM, 16);

	//mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_PROJECTIONMATRIX, 16*sizeof(float), mProjM);
	//mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_VIEWDIRECTIONMATRIX, 16*sizeof(float), mViewM);
	//mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_TRANSFORMMATRIX, 16*sizeof(float), mTransfM);

    float camPos[3];
    camPos[0] = mCamPosition[0];
    camPos[1] = mCamPosition[1];
    camPos[2] = mCamPosition[2];
    mReqSender.rSwapf(camPos, 3);
    mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_CAMERA_POSITION, 3*sizeof(float), camPos);

    float camOri[4];
    const float* ptr = mCamOrientation.getValue();
    camOri[0] = ptr[0];
    camOri[1] = ptr[1];
    camOri[2] = ptr[2];
    camOri[3] = ptr[3];
    mReqSender.rSwapf(camOri, 4);
    mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_CAMERA_ORIENTATION, 4*sizeof(float), camOri);

    float zNear = mCamNearDistance;
    mReqSender.rSwapf(&zNear);
    mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_CAMERA_NEARDIST, sizeof(float), &zNear);

    float zFar = mCamFarDistance;
    mReqSender.rSwapf(&zFar);
    mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_CAMERA_FARDIST, sizeof(float), &zFar);

    float ratio = mCamRatio;
    mReqSender.rSwapf(&ratio);
    mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_CAMERA_RATIO, sizeof(float), &ratio);

    float height = mCamHeight;
    mReqSender.rSwapf(&height);
    mReqSender.addChildElement(RENDERACTION_CAMERA, RENDERACTION_CAMERA_HEIGHT, sizeof(float), &height);




	//// mpr
	//if(mIsMpr && mRenderMode == SoXipRenderModeElement::MPR)
	//{

	//	mReqSender.addNextElement(RENDERACTION_TRANSFORMMATRIX, RENDERACTION_MPR);

	//	mReqSender.rHtonl(&mIsthickness);
	//	mReqSender.addChildElement(RENDERACTION_MPR, RENDERACTION_MPRPLANARTHICKNESSUSED, sizeof(int), &mIsthickness);
	//	mReqSender.rSwapd(&mSizeThickness);		
	//	mReqSender.addChildElement(RENDERACTION_MPR, RENDERACTION_MPRPLANARTHICKNESS, sizeof(double), &mSizeThickness);
	//	
	//	mReqSender.addChildElement(RENDERACTION_MPR, RENDERACTION_MPRPLANEWIDTH, sizeof(int), &mViewportTab[2]);
	//	mReqSender.addChildElement(RENDERACTION_MPR, RENDERACTION_MPRPLANEHEIGHT, sizeof(int), &mViewportTab[3]);


	//	SbVec3f t, s;
	//	SbRotation r, so;
	//	mMprModelMatrix.getTransform(t, r, s, so);

	//	const float *m = mMprModelMatrix.operator float*();
	//	for(int i=0; i<16; i++)
	//		mPlanarModel[i] = *m++;

	//	mScalingFactor = s[1] / mViewport[3];

	//	mReqSender.rSwapd(&mScalingFactor);
	//	mReqSender.addChildElement(RENDERACTION_MPR, RENDERACTION_SURFACESCALINGFACTOR, sizeof(double), &mScalingFactor);
	//	mReqSender.rSwapd(mPlanarModel, 16);		
	//	mReqSender.addChildElement(RENDERACTION_MPR, RENDERACTION_SURFACEMODELMATRIX, 16*sizeof(double), mPlanarModel);
	//	
	//}

	// send the render action request
	mReqSender.send();

	return 0;
}

/*
*! Send information to the server and get the image back
*/
int SoXipRemoteVolRender::render()
{
	if(!mStream) return -1;

	mReqReceiver.initReceiver(mStream);

	// expect the rendering response from the server.If rendering is done, 
	// then start receiving the rendering context buffer.

	mReqReceiver.receive();

	// if there is some error or the  sorting operation did not result in a valid volume.
	if( (mReqReceiver.getFirstElementId() != RENDER_ACTION))
	{
		//there is some error or the  rendering operation is not successful.
		SoError::post("Server render request error!\n");
		return -1;		
	}

	int renderDone;
	bool res = mReqReceiver.getUniqueIntElement(RENDERACTIONRESPONSE_DONE, renderDone);
	mReqReceiver.rNtohl(&renderDone);
	if(!res || (renderDone ==0 ))
	{
		//there is some error or the  rendering operation is not successful.
		SoError::post("Server render request error!\n");
		return -1;		
	}

	//-----------------------------------------------------------
	// Now the client shall request the image buffer from server

	// compute color buffer size
	int totElements=mViewport[2] * mViewport[3];
	//int colorBufferSize = totElements * 4;
    int colorBufferSize = totElements * 3;
	int received = 0;

	// compute 8/16 bit Gray buffer size
	int nbBits = (mBitsUsed % 8 > 0) ? 1 : 0;
	nbBits += mBitsUsed / 8;
	unsigned int grayBufferSize = totElements * nbBits;

	
	//! buffer for gray image
	void* grayVolumeBuffer = NULL;

	//! buffers for color image
	void* alphaChannel = NULL;
	void* rgbChannels = NULL;
	
	//compression = compType.getValue();

    	{
    		deleteColorBuffer();

    		// receive image buffer from server
            colorBufferSize = renderDone;
            mVolumeBuffer = new char[colorBufferSize];
            if(!mVolumeBuffer)
            {
                SoError::post("Server render request error!\n");
                return -1;
            }
            memcpy(mVolumeBuffer, mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFER, colorBufferSize), colorBufferSize);    					
            mSizeVolumeBuffer = colorBufferSize;
            mIsAllocatedManually = true;
    	}

	//switch(compression)
	//{
	//case UNCOMPRESSED:
	//	//if (mIsRenderModeColor)
	//	{
	//		deleteColorBuffer();

	//		// receive image buffer from server
	//		mVolumeBuffer = mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFER, colorBufferSize);
	//					
	//		if(!mVolumeBuffer)
	//		{
	//			SoError::post("Server render request error!\n");
	//			return -1;
	//		}
	//	}
	//	//else
	//	//{
	//	//	// RGBA byte buffer allocation
	//	//	RGBAallocation(colorBufferSize);
	//	//	
	//	//	// receive image buffer from server			
	//	//	mGrayVolumeBuffer = mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFER, grayBufferSize);
	//	//			
	//	//	if(!mGrayVolumeBuffer)
	//	//	{
	//	//		SoError::post("Server render request error!\n");
	//	//		return -1;
	//	//	}

	//	//	if (mLut)
	//	//	{	
	//	//		applyLUT((unsigned char *)mGrayVolumeBuffer,totElements, nbBits);
	//	//	}
	//	//}
	//	return 0;
	//	break;

	//case LOSSLESSLY_HUFF_MODE:
	//	// request buffer from the server depending of the render mode
	//	if (mIsRenderModeColor)
	//	{
	//		deleteColorBuffer();
	//		 
	//		// receive image buffer from server
	//		int dim;
	//		mReqReceiver.getUniqueIntElement(RENDERACTIONRESPONSE_BUFFERDIM, dim);
	//		mReqReceiver.rNtohl(&dim);
	//		
	//		mReqReceiver.getUniqueIntElement(RENDERACTIONRESPONSE_DONE, renderDone);
	//		mReqReceiver.rNtohl(&renderDone);
	//		mVolumeBuffer = mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFER,  dim);

	//		if(mVolumeBufferOut.size() < colorBufferSize) mVolumeBufferOut.resize(colorBufferSize);
	//		
	//		compressorObj.HUFFMAN_U((unsigned char*)mVolumeBuffer,dim, &mVolumeBufferOut[0]   ,colorBufferSize );
	//		
	//		mVolumeBuffer = &mVolumeBufferOut[0];
	//		
	//		if(!mVolumeBuffer)
	//		{
	//			SoError::post("Server render request error!\n");
	//			return -1;
	//		}
	//	}
	//	else
	//	{
	//		// RGBA byte buffer allocation
	//		RGBAallocation(colorBufferSize);
	//		 
	//		// receive image buffer from server
	//		/***********************************************************/
	//		int dim;
	//		mReqReceiver.getUniqueIntElement(RENDERACTIONRESPONSE_BUFFERDIM, dim);
	//		mReqReceiver.rNtohl(&dim);
	//		if(grayVolumeBufferTmp.size() < grayBufferSize) grayVolumeBufferTmp.resize(grayBufferSize);
	//		
	//		grayVolumeBuffer = mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFER,dim);
	//		
	//		compressorObj.HUFFMAN_U((unsigned char*)grayVolumeBuffer,dim ,&grayVolumeBufferTmp[0]   ,grayBufferSize );
	//		/***********************************************************/

	//		if(!grayVolumeBuffer)
	//		{
	//			SoError::post("Server render request error!\n");
	//			return -1;
	//		}

	//		// apply color lookup table to convert the gray buffer to color buffer
	//		if (mLut)
	//		{	
	//			applyLUT((unsigned char *)&grayVolumeBufferTmp[0],totElements, nbBits);
	//		}
	//		
	//	}
	//	return 0;
	//	break;
	//	case LOSSLESSLY_DIFFERENTIAL: // used only with MPR: supports only grayscale images
	//	// request buffer from the server depending of the render mode
	//
	//		// RGBA byte buffer allocation
	//		RGBAallocation(colorBufferSize);

	//		int dim;
	//		mReqReceiver.getUniqueIntElement(RENDERACTIONRESPONSE_BUFFERDIM, dim);
	//		mReqReceiver.rNtohl(&dim);

	//		int rleDim;
	//		mReqReceiver.getUniqueIntElement(RENDERACTIONRESPONSE_RLEDIM, rleDim);
	//		mReqReceiver.rNtohl(&rleDim);

	//		grayVolumeBuffer = mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFER,  dim);

	//		 if(mprBuffer.size() < grayBufferSize) mprBuffer.resize(grayBufferSize); 

	//		if(!mprFlag)
	//		{
	//			mprFlag = true;
	//			compressorObj.HUFFMAN_U((unsigned char*)grayVolumeBuffer,dim, &mprBuffer[0]   ,grayBufferSize );
	//		}
	//		else
	//		{
	//			compressorObj.HUFFMAN_U_Diff((unsigned char*)grayVolumeBuffer, dim, &mprBuffer[0] ,grayBufferSize );
	//		}

	//		if(!grayVolumeBuffer)
	//		{
	//			SoError::post("Server render request error!\n");
	//			return -1;
	//		}

	//		// apply color lookup table to convert the gray buffer to color buffer
	//		if (mLut)
	//		{	
	//			applyLUT((unsigned char *)&mprBuffer[0],totElements, nbBits);
	//		}
	//	
	//	
	//	return 0;
	//	break;
	//	
	//	case LOSSY:
	//	if (mIsRenderModeColor)
	//	{
	//		deleteColorBuffer();

	//		/************ LOSSLESS decompression ************/
	//		if (blend.getValue())
	//		{
	//			if(Temp.size() < totElements) Temp.resize(totElements);
	//			unsigned int alphaDim = compressorObj.ReadUInt32((unsigned char *)mReqReceiver.getElementContent(RENDERACTIONRESPONSE_ALPHADIM, sizeof(unsigned int)));
	//			alphaChannel = mReqReceiver.getElementContent(RENDERACTIONRESPONSE_ALPHABUFFER,alphaDim);
	//			
	//			compressorObj.HUFFMAN_U((unsigned char*)alphaChannel, alphaDim, &Temp[0], totElements );
	//		}
	//		/************************************************/
	//		
	//		//////////// receiving rgb channels from server  /////////////
	//		unsigned int rgbDim = compressorObj.ReadUInt32((unsigned char *)mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFERDIM, sizeof(unsigned int)));
	//			
	//		rgbChannels = mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFER,rgbDim);
 //      				
	//		if(!rgbChannels)
	//		{
	//			SoError::post("Server render request error!\n");
	//			return -1;
	//		}
	//		// create the memory object used to decode the lossy compressed image.
	//		// and makes it point to the uncompressed image pointer
	//		MemoryObj imageGlBuffer((unsigned char *)rgbChannels,mViewport[2]*mViewport[3]*3);
	//		imageGlBuffer.OpenMemObj();
	//			
	//		//decode the lossy compressed image received from the server
	//		img.decodeBuffer(&imageGlBuffer);

	//		//////////////// Alpha channel restoring ////////////////////
	//		mVolumeBuffer =imageGlBuffer.getBufferPtr();
	//		int i = 0;
	//		int rgb = 0;
	//	 	unsigned char alpha = 255;
	//		// RGB+A
	//		if(blend.getValue())
	//		{
	//			img.restoreBuffer((unsigned char *)mVolumeBuffer, &Temp[0], colorBufferSize);
	//		}
	//		else
	//		{
	//			img.restoreBuffer((unsigned char *)mVolumeBuffer, 255, colorBufferSize);
	//		}
	//								
	//		if(!mVolumeBuffer)
	//		{
	//			SoError::post("Server render request error!\n");
	//			return -1;
	//		}
	//	}
	//	else
	//	{
	//		// RGBA byte buffer allocation
	//		RGBAallocation(colorBufferSize);

	//		unsigned int dim = compressorObj.ReadUInt32((unsigned char *)mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFERDIM, sizeof(unsigned int)));
	//			
	//		grayVolumeBuffer = mReqReceiver.getElementContent(RENDERACTIONRESPONSE_BUFFER,dim);
	//		img.decodeBuffer((unsigned char *)grayVolumeBuffer,mViewport[2]*mViewport[3]);

	//		grayVolumeBuffer = (unsigned char *)img.get8to12Ptr(mViewport[2]*mViewport[3]);

	//		if(!grayVolumeBuffer)
	//		{
	//			SoError::post("Server render request error!\n");
	//			return -1;
	//		}

	//		// apply color lookup table to convert the gray buffer to color buffer
	//		if (mLut)
	//		{	
	//			applyLUT((unsigned char *)grayVolumeBuffer,totElements, nbBits);
	//		}

	//	}
	//	return 0;
	//	break;
	//}
	
	return 0;
}

/*
*! Draw the image
*/
void SoXipRemoteVolRender::drawImage()
{
	if(!mVolumeBuffer)
	{
		SoError::post("Caught Unknown Exception during rendering!\n");
		return;
	}

	glPushAttrib(GL_TRANSFORM_BIT | GL_ENABLE_BIT);

	int maxClipPlanes;
	glGetIntegerv(GL_MAX_CLIP_PLANES, &maxClipPlanes);
	for (int i = 0; i < maxClipPlanes; i++)
	{
		glDisable(GL_CLIP_PLANE0 + i);
	}

	//enable or disable blending
	if (blend.getValue())
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);

	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2i(-1, -1);

    //SoError::post("before draw pixles!\n");

    if ( (4*(int)mViewport[2]*(int)mViewport[3])==mSizeVolumeBuffer )
	    glDrawPixels((int)mViewport[2], (int)mViewport[3], GL_RGBA, GL_UNSIGNED_BYTE, mVolumeBuffer);
    else
        glDrawPixels((int)mViewport[2], mSizeVolumeBuffer/(4*(int)mViewport[2]), GL_RGBA, GL_UNSIGNED_BYTE, mVolumeBuffer);
    //glDrawPixels(mViewport[2], mViewport[3], GL_RGBA, GL_UNSIGNED_BYTE, mVolumeBuffer);

    //SoError::post("after draw pixels!\n");

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glPopAttrib();
}

/*
*! This implements the method called in case of a raypickaction
*/
void SoXipRemoteVolRender::rayPickAction(SoAction * action)
{
	if (!action) return;

	// get action state
	SoState* state = action->getState();
	if (!state) return;

	if (!action->isOfType(SoRayPickAction::getClassTypeId()))
		return;

	//if(!mRemoteModelMatrix)
	//{

	//	if(!mStream)
	//	{
	//		//-----------------------------------
	//		// update connection information
	//		SoXipDataConnection *vol = volumeInput.getValue();
	//		if(vol)
	//		{
	//			XipDataConnection * sVol = vol->get();
	//			if(sVol)
	//				mStream = sVol->mStream;
	//		}

	//		if(!mStream)
	//			return;
	//	}

	//	float m[16];
	//	try
	//	{
	//		//send the request for modelMatrix	
	//		mReqSender.initSender(mStream, GET_VOLUME_MODELMATRIX);
	//		mReqSender.send();	


	//		// expect the  response from the server.
	//		// expect the load response from the server.Special request without asking for the volume buffer
	//		mReqReceiver.initReceiver(mStream);
	//		mReqReceiver.receive();


	//		// if there is some error or the  sorting operation did not result in a valid volume.
	//		if( (mReqReceiver.getFirstElementId() != GET_VOLUME_MODELMATRIX))
	//		{
	//			SoError::post("ComputeBBox: Server modelMatrix request error!\n");
	//			return;
	//		}

	//		memTransfers.fastMemcopy((unsigned char *)&m[0], (unsigned char *)mReqReceiver.getElementContent(GETVOLUMEMMATRIXRESPONSE_MODELMATRIX, 16*sizeof(float)),16*sizeof(float));				

	//		if(!m)
	//		{
	//			SoError::post("ComputeBBox: Server modelMatrix request error!\n");
	//			return;
	//		}

	//		mReqReceiver.rSwapf(&m[0], 16);
	//		
	//		mRemoteModelMatrix = new SbMatrix(
 //                          m[0], m[1], m[2], m[3],
 //                          m[4], m[5], m[6], m[7], 
 //                          m[8], m[9], m[10], m[11],
 //                          m[12], m[13], m[14], m[15]);
	//	}
	//	catch (...)
	//	{
	//		SoError::post("rayPickAction :Caught Unknown while requesting model matrix!\n");

	//		if(mRemoteModelMatrix)
	//		{
	//			delete mRemoteModelMatrix;
	//			mRemoteModelMatrix = NULL;
	//		}
	//		return;
	//	}
	//}


	//SoRayPickAction *pickAction = (SoRayPickAction*) action;
	//pickAction->setObjectSpace();

	//float nearDistance = pickAction->getViewVolume().getNearDist();
	//float farDistance = pickAction->getViewVolume().getDepth();
	//SbLine line = pickAction->getLine();
	//SbVec3f start = line.getPosition() + nearDistance * line.getDirection();
	//SbVec3f end = start + (farDistance + nearDistance) * line.getDirection();


	//SoXipRenderModeElement::RenderModes rMode = SoXipRenderModeElement::get(state);
	//if (rMode == SoXipRenderModeElement::MPR)
	//{
	//	SbMatrix PMatrix = SoProjectionMatrixElement::get(state);
	//	SbMatrix VMatrix = SoViewingMatrixElement::get(state);

	//	SbMatrix ma = (PMatrix * VMatrix).inverse();

	//	SbVec3f t; SbRotation r; SbVec3f s; SbRotation so;
	//	ma.getTransform(t, r, s, so);

	//	SbVec3f axis; float radians;
	//	r.getValue(axis, radians);

	//	SbPlane plane(axis, t);

	//	SbVec3f pos;
	//	if (plane.intersect(line, pos))
	//	{
	//		// check if intersection lies within the bounding box of the volume

	//		SbVec3f minVec(0, 0, 0), maxVec(1, 1, 1);
	//		mRemoteModelMatrix->multMatrixVec(minVec, minVec);
	//		mRemoteModelMatrix->multMatrixVec(maxVec, maxVec);
	//		SbBox3f box(minVec, maxVec);

	//		if (box.intersect(pos))
	//		{
	//			pickAction->addIntersection(pos);
	//		}
	//	}
	//}
}

// map the compression algorithms requests
int SoXipRemoteVolRender::compressionMap(int compression) 
{
	int map;

	switch(compression)
	{
		case UNCOMPRESSED_MODE:	map = 1; break;
		case LOSSLESSLY_HUFF_MODE:	map = 2; break;
		case LOSSLESSLY_RLE_MODE:	map = 3; break;
		case LOSSLESSLY_DIFFERENTIAL:	map = 4; break;
		case LOSSY:	map = 6; break;
		case LOSSLESSLY_COMBO_MODE:	map = 7; break;
	}
	
	return map;
	
}


/*
* Called to validate the client on the server
* return 0 if validation is accepted and -1 else
*/
int SoXipRemoteVolRender::clientValidation()
{
    if(!mStream)
    {
        //-----------------------------------
        // update connection information
        SoXipDataConnection *vol = volumeInput.getValue();
        if(vol)
        {
            XipDataConnection * sVol = vol->get();
            if(sVol)
                mStream = sVol->mStream;
        }

        if(!mStream) return-1;

        mReqReceiver.initReceiver(mStream);
    }
	
	try
	{
		mReqSender.initSender(mStream, CLIENT_VALIDATION);

		int a=1;
        mReqSender.rHtonl(&a);
		mReqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_RLE, sizeof(int), &a);
		mReqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_HUFFMAN, sizeof(int), &a);
		mReqSender.addChildElement(CLIENT_VALIDATION, CLIENTVALIDATION_DIFFERENTIAL_HUFFMAN, sizeof(int), &a);
		mReqSender.addChildElement(CLIENT_VALIDATION, VALIDATED, sizeof(int), &a);

		mReqSender.send();

	
		// expect the validation response from the server
        mReqReceiver.initReceiver(mStream);
		mReqReceiver.receive();
		if(mReqReceiver.getFirstElementId() != CLIENT_VALIDATION)
			return -1;

		 
		bool res = mReqReceiver.getUniqueIntElement(CLIENTVALIDATION_ACCEPTED, mValid);
		mReqReceiver.rNtohl(&mValid);

		//int valid;

		//mClientValidate->cvRLE = mReqReceiver.getUniqueIntElement(CLIENTVALIDATION_RLE, valid);
		//mClientValidate->cvHUFF = mReqReceiver.getUniqueIntElement(CLIENTVALIDATION_HUFFMAN, valid);
		//mClientValidate->cvDRLE = mReqReceiver.getUniqueIntElement(CLIENTVALIDATION_DIFFERENTIAL_RLE, valid);
		//mClientValidate->cvDHUFF = mReqReceiver.getUniqueIntElement(CLIENTVALIDATION_DIFFERENTIAL_HUFFMAN, valid);
 	// 	mClientValidate->cvLOSSYJ = mReqReceiver.getUniqueIntElement(CLIENTVALIDATION_LOSSY_JPEG, valid);

		if(res && (mValid == 1))
		{
			return 0;
		}

	}
	catch (...)
	{
		SoError::post("Caught Unknown Exception while client authentification!\n");
	}

	// validate is refused.
	return -1;
}