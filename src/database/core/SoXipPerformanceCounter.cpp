#include <Inventor/SbTime.h>
#include <Inventor/errors/SoDebugError.h>
#include "SoXipPerformanceCounter.h"
//#include <xip/platform.h>	// timeval


SO_ENGINE_SOURCE(SoXipPerformanceCounter);


SoXipPerformanceCounter::SoXipPerformanceCounter()
{
	SO_ENGINE_CONSTRUCTOR(SoXipPerformanceCounter);

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	SO_ENGINE_ADD_INPUT(min, (0));
	SO_ENGINE_ADD_INPUT(max, (1));
	SO_ENGINE_ADD_INPUT(step, (1));
	SO_ENGINE_ADD_INPUT(on, (FALSE));
	SO_ENGINE_ADD_INPUT(frequency, (1));
	SO_ENGINE_ADD_INPUT(timeIn, (SbTime(&tv)));
	SO_ENGINE_ADD_INPUT(reset, (0));
	
	SO_ENGINE_ADD_OUTPUT(output, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(syncOut, SoSFTrigger);

	mCounter = 0;

	tv.tv_sec = 1;
	mDeltaTime = SbTime(&tv);

	enableNotify(FALSE);
}


void SoXipPerformanceCounter::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipPerformanceCounter, SoEngine, "Engine");
}


SoXipPerformanceCounter::~SoXipPerformanceCounter()
{
}


void SoXipPerformanceCounter::inputChanged (SoField *which)
{
	SbBool syncEnabled = FALSE;
	SbBool outputEnabled = FALSE;

	if (which == &timeIn)
	{
		if (timeIn.getValue() < mStartTime)
		{
			// rollover, reset start time
			mStartTime = timeIn.getValue();
		}

		if (timeIn.getValue() >= (mStartTime + mDeltaTime))
		{
			mStartTime = timeIn.getValue();
			outputEnabled = TRUE;

			mCounter += step.getValue();
			if (mCounter >= max.getValue())
			{
				mCounter = min.getValue();
				
				syncEnabled = TRUE;
			}
		}
	}
	else if (which == &on)
	{
		if (on.getValue())
		{
			SoField *pc = SoDB::getGlobalField("realTime");
			if (pc)
			{
				timeIn.connectFrom(pc);
			}
			else
			{
				SoDebugError::post("SoXipPerformanceCounter::inputChanged", "Cannot connect to global field \"performanceCounter\".");
			}

			mStartTime = timeIn.getValue();
		}
		else
		{
			timeIn.disconnect();
		}
	}
	else if (which == &reset)
	{
		mCounter = reset.getValue();
		mStartTime = timeIn.getValue();
	}
	else if (which == &frequency)
	{
		mDeltaTime = SbTime(frequency.getValue());
	}

	output.enable(outputEnabled);
	syncOut.enable(syncEnabled);
}


void SoXipPerformanceCounter::evaluate()
{
	SO_ENGINE_OUTPUT(output, SoSFInt32, setValue(mCounter));
	SO_ENGINE_OUTPUT(syncOut, SoSFTrigger, touch());
}

