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
