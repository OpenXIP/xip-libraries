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
*/#ifndef SOREFXIPSLICER_H
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
