#ifndef SOREFXIPTEXTURE_H
#define SOREFXIPTEXTURE_H

class QString;
class SoSFEnum;

class SoRefXipTexture
{
public:
    SoRefXipTexture(QString nodeName);
    ~SoRefXipTexture();

    void setWrapS(QString wrapS);
    void setWrapT(QString wrapT);
    void setWrapR(QString wrapR);

    QString getWrapS();
    QString getWrapT();
    QString getWrapR();

private:
    SoSFEnum* fldWrapS;
    SoSFEnum* fldWrapT;
    SoSFEnum* fldWrapR;
};

#endif