#ifndef SOREFXIPLUT_H
#define SOREFXIPLUT_H

#include <Inventor/sensors/SoFieldSensor.h>

class QString;
class QColor;
class SoSFColor;
class SoSFFloat;

class SoRefXipLut
{
public:
    SoRefXipLut(QString nodeName);
    ~SoRefXipLut();

    void setColorTop(QColor topColor);
    void setColorMiddle(QColor middleColor);
    void setColorBottom(QColor bottomColor);
    void setRampWidth(float width);
    void setRampCenter(float center);

    void setRampWidthCB(SoSensorCB* func, void* data);
    void setRampCenterCB(SoSensorCB* func, void* data);
    void setColorBottomCB(SoSensorCB* func, void* data);
    void setColorMiddleCB(SoSensorCB* func, void* data);
    void setColorTopCB(SoSensorCB* func, void* data);

    QColor getColorTop();
    QColor getColorMiddle();
    QColor getColorBottom();
    float getRampWidth();
    float getRampCenter();

private:
    SoSFColor* fldColorBottom;
    SoSFColor* fldColorMiddle;
    SoSFColor* fldColorTop;

    SoSFFloat* fldRampWidth;
    SoSFFloat* fldRampCenter;

    SoFieldSensor* senRampWidth;
    SoFieldSensor* senRampCenter;
    SoFieldSensor* senColorBottom;
    SoFieldSensor* senColorMiddle;
    SoFieldSensor* senColorTop;
};

#endif