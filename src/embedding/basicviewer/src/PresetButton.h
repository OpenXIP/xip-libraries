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
*/#ifndef PRESETBUTTON_H
#define PRESETBUTTON_H

#include <QPushButton>

class XipPreset;
QT_BEGIN_NAMESPACE
class QPainter;
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class PresetButton : public QPushButton
{
    Q_OBJECT

public:
    PresetButton(XipPreset* _preset, QWidget* parent = 0);
    ~PresetButton();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

//protected:
//    virtual void paintEvent(QPaintEvent* event);

private:
    XipPreset* refPreset;
    QPoint dragStartPosition;

private slots:
    void setPreset();
};

#endif
