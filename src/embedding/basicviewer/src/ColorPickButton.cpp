#include "ColorPickButton.h"

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
