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

#include "SoXipPerformance.h"
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h> 
#include <xip/inventor/core/XipInventorUtils.h>
#include <assert.h>


const char* gTimingNames[] = {
	"SwapBuffer Interval\t",
	"Main loop\t\t",
	"| Process Queues\t",
	"|  | RenderScene\t",
	"|  |  | SwapBuffers\t",
	"|  |  | GLRender\t",
	"|  |  | GLRenderTrans\t",
	"|  |  | GLRenderDelay\t",	
	0
};

SO_NODE_SOURCE(SoXipPerformance);

SoXipPerformance::SoXipPerformance(void) : SoGroup()
{
	SO_NODE_CONSTRUCTOR(SoXipPerformance);
	
	SO_NODE_ADD_FIELD(enabled, (TRUE));
	SO_NODE_ADD_FIELD(updateTime, (60000));
	SO_NODE_ADD_FIELD(FramesPerSecond, (0));
	SO_NODE_ADD_FIELD(AverageFrameTime, (0));
		
	mTimer.reset();
	mFrameTimer.reset();
	
	mLastSwapCount = 0;
#ifdef WIN32
	QueryPerformanceFrequency((LARGE_INTEGER*) &mPerfFreq);
#endif
	mSwapBuffersInfo = (SoMFUInt32 *) SoDB::getGlobalField("SwapBuffersInfo");
	
	resetCounters();
}

SoXipPerformance::~SoXipPerformance()
{
}

void	SoXipPerformance::resetCounters()
{
	mFrames = 0;
	mDelayCount = 0;
	mTransCount = 0;
	memset(mMinValues, 255, sizeof(unsigned int) * TIME_MAX_VALUES);
	memset(mMaxValues, 0, sizeof(unsigned int) * TIME_MAX_VALUES);
	memset(mAverageValues, 0, sizeof(unsigned int) * TIME_MAX_VALUES);
}

void	SoXipPerformance::updateValue(int which, unsigned int value)
{
	assert(which < TIME_MAX_VALUES);

	mAverageValues[which] += value;
	if (value < mMinValues[which])
		mMinValues[which] = value;
	if (value > mMaxValues[which])
		mMaxValues[which] = value;
}

void	SoXipPerformance::computeAverages()
{
	for (int i = 0; i < TIME_MAX_VALUES; ++i)
	{
		mAverageValues[i] = (unsigned int)(mAverageValues[i] / (double) mFrames);
	}
}

void	SoXipPerformance::displayTimings()
{
	for (int i = (mSwapBuffersInfo ? 0 : TIME_GLRENDER); i < TIME_MAX_VALUES; ++i)
	{
		if ((i == TIME_GLRENDER_TRANS && mTransCount == 0) ||
			(i == TIME_GLRENDER_DELAY && mDelayCount == 0))
			continue;
		SoDebugError::postInfo("SoXipPerformance::GLRender", "%s min: %d µs, average: %d µs, max: %d µs\n", gTimingNames[i], mMinValues[i], mAverageValues[i], mMaxValues[i]);
	}
}


void SoXipPerformance::initClass(void)
{
	SO_NODE_INIT_CLASS(SoXipPerformance, SoGroup, "Group");
}


void SoXipPerformance::GLRender(SoGLRenderAction * action)
{
	// If disabled, just pass through
	if (!enabled.getValue())
	{
		SoGroup::GLRender(action);
	}
	else if (action->isRenderingDelayedPaths())
	{
		//OutputDebugStringA("     SoXipPerformance::GLRender() delayed GLRender path\n");
		// Accumulate time GLRender takes, with min and max
		mDelayCount++;
		mTimer.reset();
		SoGroup::GLRender(action);
		updateValue(TIME_GLRENDER_DELAY, mTimer.elapsed());
	}
#ifdef TGS_VERSION
	else if (action->isRenderingTranspObjs())
	{
		//OutputDebugStringA("     SoXipPerformance::GLRender() trans GLRender path\n");
		// Accumulate time GLRender takes, with min and max
		mTransCount++;
		mTimer.reset();
		SoGroup::GLRender(action);
		updateValue(TIME_GLRENDER_TRANS, mTimer.elapsed());
	}
#endif
	else
	{
		//OutputDebugStringA("     SoXipPerformance::GLRender() normal GLRender path\n");
		mFrames++;

		if (mSwapBuffersInfo)
		{
			
			const uint32_t *val = mSwapBuffersInfo->getValues(0);
			if (val)
			{
				updateValue(TIME_RENDER_SCENE, val[0]);
				updateValue(TIME_SWAPBUFFERS, val[1]);
				updateValue(TIME_MAIN_LOOP, val[4]);
				updateValue(TIME_PROCESS_QUEUES, val[5]);

#ifdef WIN32
				// Accumulate time between calls to SwapBuffers
				unsigned __int64 swapCount = *((unsigned __int64*)&val[2]);
				unsigned int musec = (1000000 * (swapCount - mLastSwapCount)) / mPerfFreq;
#else
                // Accumulate time between calls to SwapBuffers
                uint64_t swapCount = *((uint64_t *)&val[2]);
                unsigned int musec = (1000000 * (swapCount - mLastSwapCount));
#endif // WIN32

				updateValue(TIME_SWAPEND_TO_SWAPEND, musec);
				if (mLastSwapCount == swapCount)
				{
#ifdef WIN32
					OutputDebugStringA("     SoXipPerformance::GLRender()   called twice since last SwapBuffers!\n");
#else
					// #ifdef linux
					printf("     SoXipPerformance::GLRender()   called twice since last SwapBuffers!\n");
					// #endif
#endif
					SoDebugError::postInfo("SoXipPerformance::GLRender", "called twice since last SwapBuffers!\n");		
				}
				mLastSwapCount = swapCount;
			}
		}
			
		// Accumulate time GLRender takes, with min and max
		mTimer.reset();
		SoGroup::GLRender(action);
		updateValue(TIME_GLRENDER, mTimer.elapsed());

		// If running timer goes over updateTime, compute and display stats
		int elapsed = mFrameTimer.elapsed();
		unsigned int timeout = updateTime.getValue() * 1000;
		if (elapsed > timeout)
		{	
			computeAverages();
			displayTimings();
										
			// Compute and display average framerate
			mFrameTimer.reset();
			double framerate = (double)mFrames / (double)elapsed;
			SoDebugError::postInfo("SoXipPerformance::GLRender", "Average framerate: %f fps\n", framerate * 1000000);
			FramesPerSecond.setValue(framerate * 1000000);

			// Reset all the counters			
			resetCounters();
		}
	}
}


