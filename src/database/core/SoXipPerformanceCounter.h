#ifndef SOXIPPERFORMANCECOUNTER_H
#define SOXIPPERFORMANCECOUNTER_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFTrigger.h>


class SoXipPerformanceCounter : public SoEngine
{
	SO_ENGINE_HEADER(SoXipPerformanceCounter);

public:
	SoXipPerformanceCounter();
	static void initClass();

	SoSFInt32		min;
	SoSFInt32		max;
	SoSFInt32		step;
	SoSFBool		on;
	SoSFFloat		frequency;
	SoSFTime		timeIn;
	SoSFInt32		reset;
	
	SoEngineOutput	output;
	SoEngineOutput	syncOut;

protected:
	virtual ~SoXipPerformanceCounter();
	virtual void evaluate();
	virtual void inputChanged (SoField *which);

	int    mCounter;
	SbTime mStartTime;
	SbTime mDeltaTime;
};

#endif // SOXIPPERFORMANCECOUNTER_H
