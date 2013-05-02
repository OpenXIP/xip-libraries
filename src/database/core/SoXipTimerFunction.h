/*
  ------------------------------------------------------------------------

    SoXipTimerFunction.h

    A triggered timer function with linear, smoothstep and C2 smoothstep.

    Copyright (C) 2007 - 2008, Siemens Corporate Research, Inc.

    Authors:
      Patric Ljung, patric.ljung@siemens.com
      Stefan Wiesner, stefan.wiesner@siemens.com

  ------------------------------------------------------------------------
*/

#ifndef SO_XIP_TIMER_FUNCTION_H
#define SO_XIP_TIMER_FUNCTION_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>

#include <xip/system/standard.h>

class SoSFTime;
class SoFieldSensor;

/**
 */
class SoXipTimerFunction : public SoNode
{
    SO_NODE_HEADER(SoXipTimerFunction);

public:
    // constructor
    SoXipTimerFunction();
        
    // initialization
    static void initClass();

    // input
    SoSFEnum            function;
	SoSFEnum			playMode;
    SoSFFloat           duration;
    SoSFTrigger         start;
	SoSFTrigger			pause;
	SoSFBool			pauseOn;
	SoSFTrigger			stop;

    SoSFTrigger         syncIn;

    // output
    SoSFFloat           value;
    SoSFInt32           counter;             // Incremented when time's up


    static const float  cmTimeScale;

    virtual void GLRender(SoGLRenderAction * action);

protected:

    // destructor
    virtual ~SoXipTimerFunction();

    virtual void inputChanged(SoField * which);

    SoFieldSensor **    mInputSensors;
    int                 mInputSensorCount;

    static void fieldSensorCBFunc(void * user, SoSensor * sensor);

private:
    float               mValue;

	bool				mStarted;
	SoSFTime *          mRealTime;
    
#ifdef WIN32
	//unsigned __int64 mStartTime;
    int64_t      		mStartTime;
	int64_t				mElapsedTime;
    double              mPerfFreq;
#else
    struct timeval  mStartTime;
    struct timeval  mElapsedTime;
    struct timezone tz;
#endif // WIN32
	

    enum FUNCTION_TYPES {
        C0 = 0,
        C1 = 1,
        C2 = 2
    };

	enum MODE_TYPES {
		ONCE,
		LOOP
	};
};


// local Variables:
//   mode: c++
//   indent-tabs-mode: nil
//   c-indentation-style: k&r
//   c-basic-offset: 4
// End:

#endif // SO_XIP_TIMER_FUNCTION_H


