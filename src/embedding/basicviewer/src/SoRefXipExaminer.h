#ifndef SOREFXIPEXAMINER_H
#define SOREFXIPEXAMINER_H

class QString;
class SoSFEnum;
class SoSFTrigger;
class QStringList;
class SoSFEnumExtended;

#include <Inventor/sensors/SoFieldSensor.h>

class SoRefXipExaminer
{
public:
    SoRefXipExaminer(QString nodeName);
    ~SoRefXipExaminer();

    void setOrientation(QString newOrientation);
    void triggerViewOrientation();
    void triggerViewAll();
    void resetView(QString newOrientation);

    void setMode(QString mode);
    QString getMode();
	
    QStringList getModeList();
	QStringList getOrientationList();

    void switchModes();

    void setModeCB(SoSensorCB* func, void* data);

private:
    SoSFEnumExtended* fldOrientation;
    SoSFTrigger* triViewOrientation;
    SoSFTrigger* triViewAll;
    SoSFEnumExtended* fldMode;

    SoFieldSensor* senMode;

    int maxModes;
};

#endif