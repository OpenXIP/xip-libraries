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
*/#ifndef PRESETSLOT_H
#define PRESETSLOT_H

#include <QFrame>

class XipPreset;
class PresetButton;
QT_BEGIN_NAMESPACE
class QPainter;
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class PresetSlot : public QFrame
{
    Q_OBJECT

public:
    PresetSlot(QWidget* parent = 0);
    ~PresetSlot();

    XipPreset* getPreset() { return refPreset; }

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

private:
    XipPreset* refPreset;
    PresetButton* refPresetButton;

signals:
    void sigGotPreset();
};

#endif
