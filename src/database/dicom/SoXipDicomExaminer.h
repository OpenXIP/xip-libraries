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
#ifndef SOXIPDICOMEXAMINER_H
#define SOXIPDICOMEXAMINER_H

#include <xip/inventor/core/SoXipSubKit.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/sensors/SoTimerSensor.h>

class SoOrthographicCamera;
class SoXipConvertMFDicomToSFDicom;
class SoXipDicomExtractSlice;

class SoXipDicomExaminer : public SoXipKit
{
	SO_NODE_HEADER( SoXipDicomExaminer );

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

	SoXipDicomExaminer();

	SoSFBool					drawImage;
	SoXipMFDataDicom			images;
	SoSFShort					imageIndex;
	SoSFTrigger					previousImage;
	SoSFTrigger					nextImage;
	SoSFShort					sliceIndex;
	SoSFTrigger					previousSlice;
	SoSFTrigger					nextSlice;
	SoSFTrigger					viewAll;
	SoSFFloat					viewAllScale;
	SoSFEnum					mode;
	SoSFMatrix					boundingBox;
	SoSFTrigger					viewBoundingBox;

	SoSFPlane					planeSlice ;

	static void initClass();

protected:
	SoXipConvertMFDicomToSFDicom	*mSelectionEngine;
	SoXipDicomExtractSlice			*mDicomExtract;
	SoSFShort						numSlices;

	SbMatrix						mImageModelMatrix;
	SbPlaneProjector				mPlaneProj;
	SbViewVolume					mViewVolume;
	SbViewportRegion				mViewport;
	SoFieldSensor*					mFieldSensors[8];
	SbVec2f							mLastMousePosition;
	SbBool							mViewAll;
	SbBool							mPan;
	SbBool							mViewBoundingBox;


	SbBool						mAnimate;
	float						mAnimateHStep;
	float						mAnimateHPosition;
	float						mAnimateVStep;
	float						mAnimateVPosition;
	int							mAnimateChange;

protected:
	~SoXipDicomExaminer();

	// Return the number of slices of the given dicom data
	int getNumSlices( SoXipDataDicom* dicomData );

	virtual void GLRender( SoGLRenderAction* action );
	virtual void rayPick( SoRayPickAction* action );
	virtual void handleEvent( SoHandleEventAction* action );

	virtual void inputChanged( SoField* whichField );

	void increaseImageIndex( int count );
	void decreaseImageIndex( int count );

	void increaseSliceIndex( int count );
	void decreaseSliceIndex( int count );

	virtual SoOrthographicCamera* getCamera();
	virtual void updateCamera();
	virtual void adjustCamera( SoGLRenderAction* action, const SbMatrix& model );
	virtual void tiltCamera( const SbRotation& rot );

	virtual void setElement( SoAction* action );
	virtual void saveViewInformation( SoHandleEventAction* action );

	void onAnimationTimer();
	void startAnimation( float animateHStep, float animateVStep );
	void stopAnimation();

private:
	SoFieldSensor*				mImageSensor;
	SoTimerSensor*				mAnimationSensor;

private:
	static void fieldSensorCB( void*, SoSensor* );
	static void animationSensorCB( void*, SoSensor* );

};

#endif	// SOXIPDICOMEXAMINER_H
