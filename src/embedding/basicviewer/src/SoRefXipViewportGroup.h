#ifndef SOREFXIPVIEWPORTGROUP_H
#define SOREFXIPVIEWPORTGROUP_H

class QString;
class SoSFInt32;
class SoSFBool;

class SoRefXipViewportGroup
{
public:
    SoRefXipViewportGroup(QString nodeName);
    ~SoRefXipViewportGroup();

    void setCurrent(int current);
    void setMaximized(bool maximized);

    int getCurrent();
    bool getMaximized();

    void setWindow0Maximized();
    void setWindow1Maximized();
    void setWindow2Maximized();
    void setWindow3Maximized();

    void setNormalState();

private:
    SoSFInt32* fldCurrent;
    SoSFBool* fldMaximized;
};

#endif