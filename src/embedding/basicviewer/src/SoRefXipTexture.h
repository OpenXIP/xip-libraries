/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/#ifndef SOREFXIPTEXTURE_H
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
