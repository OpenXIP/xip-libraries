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


