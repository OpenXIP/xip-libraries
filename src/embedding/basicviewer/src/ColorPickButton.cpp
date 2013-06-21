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
*/#include "ColorPickButton.h"

#include <QPaintEvent>
#include <QPainter>

#include <QColorDialog>

ColorPickButton::ColorPickButton(QWidget* parent) : QPushButton(parent)
{
    init = false;
    leftIndent = 10;
    connect(this, SIGNAL(clicked()), this, SLOT(chooseColor()));
}

ColorPickButton::~ColorPickButton()
{
}

void ColorPickButton::setColor(QColor color)
{
    if (!color.isValid()) return;
    this->value = color;
    this->update();
}

QColor ColorPickButton::getColor()
{
    return this->value;
}

void ColorPickButton::setIndent(int indent)
{
    this->leftIndent = indent;
    this->update();
}

void ColorPickButton::chooseColor()
{
    QColor tmpColor = QColorDialog::getColor(this->value);
    if (!tmpColor.isValid()) return;
    this->value = tmpColor;
    this->update();
    emit this->changedColor();
}

void ColorPickButton::paintEvent(QPaintEvent* event)
{
    QPushButton::paintEvent(event);
    QPainter painter(this);
    if (!init)
    {
        float tmpQuarter = this->height() / 4.0;
        quartSize = (int)tmpQuarter;
        if (this->height() % 2 == 0)
            halfSize = (int)(tmpQuarter * 2.0);
        else
            halfSize = (int)(tmpQuarter * 2.0 + 1.0);
        init = true;
    }
    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(this->value);
    painter.drawRect(leftIndent, quartSize, halfSize, halfSize);
}
