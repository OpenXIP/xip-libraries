#ifndef SOREFXIPLOADDICOM_H
#define SOREFXIPLOADDICOM_H

#include <Inventor/sensors/SoFieldSensor.h>

class QString;
class SoMFString;

class SoRefXipLoadDicom
{
public:
    SoRefXipLoadDicom(QString nodeName);
    ~SoRefXipLoadDicom();

    void setName(QString name);
    void setNameCB(SoSensorCB* func, void* data);
   
    QString getName();

private:
    SoMFString* fldName;
    SoFieldSensor* senName;
};

#endif