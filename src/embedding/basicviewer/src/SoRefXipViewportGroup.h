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
*/#ifndef SOREFXIPVIEWPORTGROUP_H
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
