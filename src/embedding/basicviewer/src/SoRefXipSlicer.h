#ifndef SOREFXIPSLICER_H
#define SOREFXIPSLICER_H

class QString;
class QStringList;
class SoSFEnum;
class SoSFInt32;
class SoRefXipTexture;
class SoSFEnumExtended;

class SoRefXipSlicer
{
public:
    SoRefXipSlicer(QString nodeName, SoRefXipTexture* ref = 0);
    ~SoRefXipSlicer();

    void setMode(QString mode);
    void setNumSlices(int numSlices);

    QString getMode();
    int getNumSlices();

    QStringList getModeList();

private:
    SoSFEnumExtended* fldMode;
    SoSFInt32* fldNumSlices;

    SoRefXipTexture* refTextureNode;
};

#endif