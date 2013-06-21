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
#ifndef SOXIPREMOTEVOLRENDER_H
#define SOXIPREMOTEVOLRENDER_H
 
#ifdef WIN32
#include<fstream>
#include<iostream>
#endif

#include <xip/system/standard.h>

 
#include <vector>

#include <Inventor/nodes/SoShape.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbColor.h>
#include <Inventor/nodes/SoEventCallback.h>

#include "SoXipDataConnection.h"

#include <xip/inventor/remote/XipRenderActionParams.h>
#include <xip/inventor/remote/XipRequestManager.h>
#include <xip/inventor/core/SoXipRenderModeElement.h>

#include <xip/inventor/remote/jpegWrapper/bufferImage.h>
#include <xip/inventor/remote/losslessCompression/losslessCompression.h>
#include <xip/inventor/remote/losslessCompression/fastMemTransfer.h>

class SbXipImage;

//! volume renderer connecting to remote server
class SoXipRemoteVolRender : public SoShape
{
	//! Implements the runtime type system interface of this new node.
	SO_NODE_HEADER(SoXipRemoteVolRender);

public:
	//! Constructor
	SoXipRemoteVolRender();

	//! Initializes this class (called on dll initialization).
	static void initClass();

	//@{! Fields

	//! to activate or no the rendering 
	SoSFBool on;

	//! to activate or no opengl merging
	SoSFBool mergeOpenGL;

	//! to activate or no blending
	SoSFBool blend;

	//! input containing volume information
	SFXipConnection volumeInput;

	//! input containing bit used for volume display
	SoSFInt32 bitsUsed;

	enum comp {                
		UNCOMPRESSED		= 0x01
		//COMPRESSED			= 0x02,
	};

    SoSFEnum compType;

	SoSFInt32 compQty;

	SoSFInt32 planeId;

	SoSFBool fullQualityMpr;

	enum smart {              
		NONE		= 0x01,
		SMART_1		= 0x02,
		SMART_2		= 0x03,
		AUTO		= 0x04,
	};

    SoSFEnum smartMode;

	SoSFFloat smartFpsThreshold;

	SoSFFloat lowQualityThreshold;

	SoSFString fps;

	//@}

	//! Send information to the server and get the image back
	int render();

protected:

	static void fullQualityFlagCallback(void *data, SoSensor *action);
	
	//! Protected destructor
	virtual ~SoXipRemoteVolRender();

	//! Generates primitives representing the volume (no need to be implemented)
	virtual void generatePrimitives(SoAction *action) {};

	//! This computes the bounding box and center of the volume. 
	virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

	//! This implements the inventor actions. 
	virtual void GLRender(SoGLRenderAction * action);
	virtual void callback(SoCallbackAction *action);
	virtual void pick(SoPickAction *action);
	virtual void rayPick(SoRayPickAction *action);


    //! This implements generic traversal of SoRadRemoteVolRender node, used in
    //! both of the above methods.
	virtual void doAction(SoAction * action);

    //! This implements the method called in case of a raypickaction
	void rayPickAction(SoAction * action);

	//! Get the information we need to ask a image of the required volume to the server
	int getElements(SoAction * action);

	//! Gather the information in the good structure before sending it to the server
	int getInputParams();
	
	int compressionMap(int compression);

	//! Draw the image
	void drawImage();

	////! Call to delete the clipPlanes
	////void deleteClipPlanes();

	//! Call to delete the volume buffer if exist
	void deleteColorBuffer();
	//void deleteGrayBuffer();

	void RGBAallocation(unsigned int colorBufferSize);

	int clientValidation();

	//! class containing information to send/receive to the server 
	XipTreeRequestSender mReqSender;
	XipTreeRequestReceiver mReqReceiver;

	//! cliplanes to be applied to the volume
	//SbPlane *mClipPlaneTable;
	//int mNbClipPlane;

	//! stream used to load the volume form the server
	XipStreamBase *mStream;

	//! render quality
	double mRenderQuality;

	//! full lossy
	int mFullLossy;
	
	//! compression quality
	int mCompressionQuality;
	
	//! callback Request
	//int mCallbackRequest;

	//! render mode
	SoXipRenderModeElement::RenderModes mRenderMode;
	SbBool mIsRenderModeColor;

	//! transform matrix
	SbMatrix mTransformMatrix;

	//! projection matrix
	SbMatrix mProjMatrix;

	//! view matrix
	SbMatrix mViewMatrix;

	//! viewport 
	float mViewport[4];

    SbVec3f     mCamPosition;
    SbRotation  mCamOrientation;
    float       mCamRatio;
    float       mCamNearDistance;
    float       mCamFarDistance;
    float       mCamFocalDistance;
    float       mCamHeight;


	//! LUT
	//SbXipImage *mLut;
	//int mSizeLut;
	int mBitsUsed;

	////! material information
	//SbColor mSurfaceColor;	
	//float mAmbient;
	//float mSpecular;
	//float mShineness;
	//float mDiffuse;


	//! light
	//bool mLightEnabled;
	//int mIsLightOn;

	//! MPR
	//bool mIsMpr;
	//SbMatrix mMprModelMatrix;
	//SbVec3f mMprCenter;
	//int mIsthickness;
	//double mSizeThickness;
	//double mScalingFactor;
	//double mPlanarModel[16];

	//! buffer containing the color image rendered in the server
	void* mVolumeBuffer;
	int mSizeVolumeBuffer;
	bool mIsAllocatedManually;

	//! buffer for gray image
	//void* mGrayVolumeBuffer;
	//int mSizeGrayVolumeBuffer;

	//! compression mode
	int compression;
	
	//! int plane info;
	//int plane;
	//bool mprFlag;

	//std::vector <unsigned char> mprBuffer;
	//std::vector <unsigned char> mVolumeBufferOut;
	//std::vector <unsigned char> grayVolumeBufferTmp;
	//std::vector <unsigned char> Temp;

	//bool mprLowQuality;
 	//bool smartPlaneCompression;
	//bool fullComplexity;
	//bool lastFrameHQ;

	//SoAlarmSensor *requireHQ;

private:

	//! elements used as tmp for request sending for optimization
	short mRenderModeT;
	int mRcWidth;
	int mRcHeight;
	int mViewportTab[4];

	float mTransfM[16];
	float mViewM[16];
	float mProjM[16];

	SbMatrix * mRemoteModelMatrix;

	uint32_t mLutId;
	//unsigned char * mCompiledTabLut;
	//unsigned char * mCompiledTabAlpha;
	//int mSizeTabAlpha;

	double quality;
	int alpha;

	//! FPS
	bool firstTime;
	float elapse;
	float mFramePerSecond;
 

	//! Compression threshold
	//SbVec3f deltaView;
	//vector <float> thresholdBuffer;
	//vector <float> smartThresholdTemp;
	//unsigned int thresholdIdx;
	//bool fromCallback;
	//int smartFlag;

	//! Client Validation
	int mValid;

	//struct clientValid
	//{
	//	bool cvRLE;
	//	bool cvHUFF;
	//	bool cvDRLE;
	//	bool cvDHUFF;
	//	bool cvLOSSYJ;
	//};

	//clientValid *mClientValidate;
	bool mValidate;
	
	//! compression
	//losslessCompression compressorObj;

	//! Fast Memory Transfers
#ifndef WIN64
	fastMemTransfer memTransfers;
#endif // WIN64
};

#endif // SOXIPREMOTEVOLRENDER_H
