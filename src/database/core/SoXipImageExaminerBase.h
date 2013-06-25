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

#ifndef SOXIPIMAGEEXAMINERBASE_H
#define SOXIPIMAGEEXAMINERBASE_H

#include <xip/inventor/core/SoXipSubKit.h>

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/sensors/SoTimerSensor.h>

class SoOrthographicCamera;

class SoXipImageExaminerBase : public SoXipKit
{
	SO_NODE_ABSTRACT_HEADER( SoXipImageExaminerBase );

	SO_XIP_KIT_ENTRY_HEADER( mCamera );
	SO_XIP_KIT_ENTRY_HEADER( mImageSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mImage );

public:
	enum ModeType
	{
		NONE,
		PANZOOM,
		SHIFT,
		SCROLL,
		SHIFTSCROLL
	};

	enum ScrollScopeType
	{
		ALL_IMAGES,
		CURRENT_IMAGE
	};

	SoXipImageExaminerBase();

	SoSFBool					drawImage;	
	SoSFShort					imageIndex;
	SoSFTrigger					previousImage;
	SoSFTrigger					nextImage;
	SoSFShort					sliceIndex;
	SoSFTrigger					previousSlice;
	SoSFTrigger					nextSlice;
	SoSFTrigger					viewAll;
	SoSFFloat					viewAllScale;
	SoSFEnum					mode;
	SoSFMatrix					plane;
	SoSFEnum					scrollScope;

	static void initClass();

protected:
	~SoXipImageExaminerBase();

	virtual unsigned int getNumImages() const = 0;
	virtual unsigned int getNumSlices( unsigned int imageIndex ) const = 0;

	// Return the number of slices of the given dicom data
	//int getNumSlices( SoXipDataDicom* dicomData );

	virtual void GLRender( SoGLRenderAction* action );
	virtual void rayPick( SoRayPickAction* action );
	virtual void handleEvent( SoHandleEventAction* action );

	virtual void inputChanged( SoField* whichField );

	void increaseImageIndex( int count );
	void decreaseImageIndex( int count );

	void increaseSliceIndex( int count );
	void decreaseSliceIndex( int count );

	void updatePlane();

	virtual SoOrthographicCamera* getCamera();
	virtual void updateCamera();
	virtual void adjustCamera( SoGLRenderAction* action, const SbMatrix& model );
	virtual void tiltCamera( const SbRotation& rot );

	virtual void setElement( SoAction* action );
	virtual void saveViewInformation( SoHandleEventAction* action );

	void onAnimationTimer();
	void startAnimation( const SbVec2f& step );
	void stopAnimation();
    
    SbMatrix					mImageModelMatrix;

	SbPlaneProjector			mPlaneProj;
	SbViewVolume				mViewVolume;
	SbViewportRegion			mViewport;	
	SbVec2f						mLastMousePosition;
	SbBool						mViewAll;
	SbBool						mPan;
	SbBool						mAnimate;
	int							mShiftOrScroll;
	SbVec2f						mAnimateStep;
	SbVec2f						mAnimatePosition;
	int							mAnimateChange;
    SbBool                      mAnimateLock[2];

private:
	static void fieldSensorCB( void*, SoSensor* );

    SoFieldSensor*				mFieldSensors[6];
	SoFieldSensor*				mImageSensor;

    static void animationSensorCB( void*, SoSensor* );

    SoTimerSensor*				mAnimationSensor;

};

#endif	// SOXIPIMAGEEXAMINERBASE_H

