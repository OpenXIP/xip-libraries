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
*/#include "PresetButton.h"

#include <QApplication>
#include <QPaintEvent>
#include <QPainter>

#include "ViewerCore.h"
#include "XipPreset.h"

PresetButton::PresetButton(XipPreset* _preset, QWidget* parent) : QPushButton(parent)
{
    this->refPreset = _preset;
    this->setText(this->refPreset->getName());
    this->setMinimumHeight(23);
    this->setMaximumHeight(23);
    connect(this, SIGNAL(clicked()), this, SLOT(setPreset()));
}

PresetButton::~PresetButton() { }

void PresetButton::setPreset()
{
    this->refPreset->setPreset();
}

//void PresetButton::paintEvent(QPaintEvent* event)
//{
//    QPushButton::paintEvent(event);
//    QPainter painter(this);
//    if (!init)
//    {
//        float tmpQuarter = this->height() / 4.0;
//        quartSize = (int)tmpQuarter;
//        if (this->height() % 2 == 0)
//            halfSize = (int)(tmpQuarter * 2.0);
//        else
//            halfSize = (int)(tmpQuarter * 2.0 + 1.0);
//        init = true;
//    }
//    painter.setPen(QColor(0, 0, 0));
//    painter.setBrush(this->value);
//    painter.drawRect(leftIndent, quartSize, halfSize, halfSize);
//}

void PresetButton::mousePressEvent(QMouseEvent* event)
{
    QPushButton::mousePressEvent(event);

    if (event->button() == Qt::LeftButton)
    dragStartPosition = event->pos();
}

void PresetButton::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;

    mimeData->setData("application/x-presetbutton", this->refPreset->toByteArray());

    drag->setMimeData(mimeData);

    QPixmap pixmap(this->size());
    this->render(&pixmap);
    drag->setPixmap(pixmap);
    drag->setHotSpot(dragStartPosition);

    //this->hide();

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

    delete drag;

    //if (dropAction == Qt::MoveAction) this->close();
    //else this->show();

    this->setDown(false);
}
