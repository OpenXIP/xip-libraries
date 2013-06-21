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

#ifndef SOXIPPERFORMANCE_H
#define SOXIPPERFORMANCE_H

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <xip/inventor/core/xipivcore.h>
#include <xip/system/standard.h>


class ivtTimer
{
public:
	ivtTimer()
	{
		reset();
#ifdef WIN32
		QueryPerformanceFrequency((LARGE_INTEGER*) &mFreq);
#else
        gettimeofday(&mStartTime, &tz);
#endif
	}

	~ivtTimer()
	{
	}

	void reset()
	{
#ifdef WIN32
		QueryPerformanceCounter((LARGE_INTEGER*) &mStartTime);
#else
        gettimeofday(&mStartTime, &tz);
#endif
	}
	
	unsigned int elapsed()
	{

#ifdef WIN32
		unsigned int r;
		unsigned __int64 stop;

		QueryPerformanceCounter((LARGE_INTEGER*) &stop);
		
		r = (unsigned int) (((stop - mStartTime) * 1000000) / mFreq);
#else
        unsigned int r;
        struct timeval stop;
        gettimeofday(&stop, &tz);
        //in microsec
        r= (unsigned int)(stop.tv_sec * (1000*1000)+ stop.tv_usec) - (mStartTime.tv_sec * (1000*1000)+ mStartTime.tv_usec);
#endif // WIN32

		return r;
		
	};

		protected:
#ifdef WIN32
	unsigned __int64 mStartTime;
	unsigned __int64 mFreq;
#else
    struct timeval  mStartTime;
    struct timezone tz;
#endif // WIN32
};


#define	TIME_SWAPEND_TO_SWAPEND	0
#define TIME_MAIN_LOOP			1
#define TIME_PROCESS_QUEUES		2
#define TIME_RENDER_SCENE		3
#define TIME_SWAPBUFFERS		4
#define TIME_GLRENDER			5
#define TIME_GLRENDER_TRANS		6
#define TIME_GLRENDER_DELAY		7
#define TIME_MAX_VALUES			8

class SoXipPerformance : public SoGroup 
{
	SO_NODE_HEADER(SoXipPerformance);

public:
	static void initClass();
	SoXipPerformance();

	//virtual SoNode *getChildByType(const SoType &type) const;
	
	SoSFBool		enabled;
	SoSFInt32		updateTime;
	SoSFFloat		FramesPerSecond;
	SoSFFloat		AverageFrameTime;
	
protected:
	virtual ~SoXipPerformance();
	virtual void GLRender(SoGLRenderAction * action);
	void		resetCounters();
	void		updateValue(int which, unsigned int value);
	void		computeAverages();
	void		displayTimings();

	SoMFUInt32			*mSwapBuffersInfo;
#ifdef WIN32
	unsigned __int64	mLastSwapCount;
#else
	uint64_t            mLastSwapCount;
#endif

	unsigned int		mMinValues[TIME_MAX_VALUES];
	unsigned int		mMaxValues[TIME_MAX_VALUES];
	unsigned int		mAverageValues[TIME_MAX_VALUES];

	unsigned int		mTransCount;
	unsigned int		mDelayCount;
	
	unsigned int		mFrames;
#ifdef WIN32
	unsigned __int64	mPerfFreq;
#endif

	ivtTimer		mTimer, mFrameTimer;
};

#endif // SOXIPPERFORMANCE_H


