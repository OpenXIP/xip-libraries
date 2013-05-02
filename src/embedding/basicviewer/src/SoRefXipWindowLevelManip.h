#ifndef SOREFXIPWINDOWLEVELMANIP_H
#define SOREFXIPWINDOWLEVELMANIP_H

#include <Inventor/sensors/SoFieldSensor.h>

class QString;
class SoSFFloat;

class SoRefXipWindowLevelManip
{
public:
    SoRefXipWindowLevelManip(QString nodeName);
    ~SoRefXipWindowLevelManip();

    void setWindow(float newWindow);
    void setLevel(float newLevel);

    void setWindowCB(SoSensorCB* func, void* data);
    void setLevelCB(SoSensorCB* func, void* data);

    float getWindow();
    float getLevel();

    void resetValues();

private:
	SoSFFloat* fldWindow;
	SoSFFloat* fldLevel;

    SoFieldSensor* senWindow;
    SoFieldSensor* senLevel;

    float initialWindow;
    float initialLevel;
};

#endif