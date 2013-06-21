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
#ifndef XIPRENDERACTION_H
#define XIPRENDERACTION_H

#pragma warning ( disable : 4786 )

#include <xip/inventor/remote/XipRequestManager.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
 
class XipRenderAction
{
public:
		
	/// default constructor
	XipRenderAction();

	/// Destructor
	virtual ~XipRenderAction();

	/// Returns the volume buffer and buffer size after volume rendering
 	virtual int renderVolume(XipTreeRequestReceiver &reqReceiver, unsigned char*& buffer);

    virtual int setLut(XipTreeRequestReceiver &reqReceiver);

    void getModelMatrix(float *m);

    /// load dicom data
    void loadDicom(const char* location);

	void setLutRampWidth(float width);

	void setLutRampCenter(float center);

	enum VolRenderActionType
	{
		ACTION_MPR,
		ACTION_MAXIP,
		ACTION_MINIP,
		ACTION_SSD,
		ACTION_SSD_COLOR,
		ACTION_SSD_COLOR_PERSPECTIVE,
		ACTION_VRT_COLOR,
		ACTION_VRT_COLOR_PERSPECTIVE,
		ACTION_DRR,
		ACTION_NUM_ACTIONS
	};

protected:
    SoSeparator*            mRoot;                  
    SoEngine*               mOffScreenRenderer;
    SoNode*                 mImage;
	SoSFNode*				mRenderNode;
    SoSFTrigger*            mTrigger;

    SoSeparator*            mGraph;
    SoNode*                 mSwitch;
	SoNode*					mVrtLut;
    SoNode*                 mMprLut;
    SoNode*                 mSlicer;

    SoOrthographicCamera*   mCamera;
    SoEngine*               mDicomLoader;
    SoEngine*               mVolumeData;

    int						mCurrentRenderAction;
    short                   mMode;                              // Rendering mode

protected:
	/// Initialize data object
	virtual void initialize();

	/// Deletes the data object
	virtual void terminate();

    /// Read .iv scene graph file
    SoSeparator* readSceneGraph(const char* filename);

    /// Get rendering result from the off-screen renderer
    unsigned char* getOutput(int &bufSize);

    /// Set off-screen window size
    void setWindowWidth(SoEngine* renderer, int w);
   
    void setWindowHeight(SoEngine* renderer, int h);

    /// Set matrix
    void setMatrix(SoNode* matrixNode, float *m);

    /// set the rendering mode of slicer
    void setMode(short mode);

};

#endif	// XIPRENDERACTION_H