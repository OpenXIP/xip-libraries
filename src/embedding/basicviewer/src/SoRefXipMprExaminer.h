#ifndef SOREFXIPMPREXAMINER_H
#define SOREFXIPMPREXAMINER_H

class QString;
class SoSFEnum;
class SoSFTrigger;

class SoRefXipMprExaminer
{
public:
    SoRefXipMprExaminer(QString nodeName);
    ~SoRefXipMprExaminer();

    void setOrientation(QString newOrientation);
    void triggerViewOrientation();
    void triggerViewAll();
    void resetView(QString newOrientation);

private:
    SoSFEnum* fldOrientation;
    SoSFTrigger* triViewOrientation;
    SoSFTrigger* triViewAll;
};

#endif