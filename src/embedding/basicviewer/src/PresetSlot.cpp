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
*/#include "PresetSlot.h"

#include <QApplication>
#include <QPaintEvent>
#include <QPainter>
#include <QLayout>

#include "ViewerCore.h"
#include "XipPreset.h"
#include "PresetButton.h"

PresetSlot::PresetSlot(QWidget* parent) : QFrame(parent)
{
    this->refPreset = 0;
    this->refPresetButton = 0;
    this->setMinimumHeight(23);
    this->setMaximumHeight(23);
    this->setAcceptDrops(true);
}

PresetSlot::~PresetSlot()
{
    if (this->refPreset) delete this->refPreset;
}

void PresetSlot::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("application/x-presetbutton"))
        event->acceptProposedAction();
}

void PresetSlot::dropEvent(QDropEvent* event)
{
    if (!event->mimeData()->hasFormat("application/x-presetbutton"))
        return;
    if (this->refPreset)
    {
        delete refPreset;
        refPreset = 0;
    }
    if (this->refPresetButton)
    {
        delete refPresetButton;
        refPresetButton = 0;
    }

    QString mimeType;
    QByteArray ba = event->mimeData()->data("application/x-presetbutton");

    this->refPreset = new XipPreset(&ba);

    this->refPresetButton = new PresetButton(this->refPreset, this);
    this->layout()->addWidget(this->refPresetButton);

    event->acceptProposedAction();

    emit sigGotPreset();
}
