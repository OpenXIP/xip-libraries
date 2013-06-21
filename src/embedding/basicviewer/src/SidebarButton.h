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
*/#ifndef SIDEBARBUTTON_H
#define SIDEBARBUTTON_H

#include <QPushButton>

class QPainterPath;
class QPoint;

class SidebarButton : public QPushButton
{
    Q_OBJECT

public:
    SidebarButton(QWidget* parent = 0);
    ~SidebarButton();

private:
    bool mHover;

    static const QPoint ptsArrowOpened[];
    static const QPoint ptsArrowClosed[];

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void enterEvent(QEvent* event);
    virtual void leaveEvent(QEvent* event);
};


#endif
