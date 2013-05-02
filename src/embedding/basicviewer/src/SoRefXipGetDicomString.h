#ifndef SOREFXIPGETDICOMSTRING_H
#define SOREFXIPGETDICOMSTRING_H

class QString;
class SoSFUShort;
class SoMFString;

class SoRefXipGetDicomString
{
public:
    SoRefXipGetDicomString(QString nodeName);
    ~SoRefXipGetDicomString();

    void setGroup(unsigned short group);
    unsigned short getGroup();

    void setElement(unsigned short element);
    unsigned short getElement();

    QString getOutput();

private:
    SoSFUShort* fldGroup;
    SoSFUShort* fldElement;
    SoMFString* fldOutput;

};

#endif