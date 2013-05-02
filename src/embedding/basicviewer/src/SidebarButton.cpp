#include "SidebarButton.h"

#include <QPaintEvent>
#include <QPainter>
#include <QColor>

#include <QDebug>

const QPoint SidebarButton::ptsArrowOpened[] = {
    QPoint(-5, -5),
    QPoint(-5, 6),
    QPoint(5, 0)
};

const QPoint SidebarButton::ptsArrowClosed[] = {
    QPoint(5, -5),
    QPoint(5, 6),
    QPoint(-5, 0)
};

SidebarButton::SidebarButton(QWidget* parent)
{
    mHover = false;
}

SidebarButton::~SidebarButton()
{
}

void SidebarButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QBrush brush(Qt::SolidPattern);
    if (mHover)     // hover
        brush = palette().highlight();
    else            // normal
        brush = palette().button();

    painter.setPen(palette().window().color());

    QPainterPath pathEdges;
    pathEdges.moveTo(0, 0);
    pathEdges.lineTo(rect().width() - 1, rect().width() - 1);
    pathEdges.lineTo(rect().width() - 1, rect().height() - rect().width() + 1);
    pathEdges.lineTo(0, rect().height());
    pathEdges.lineTo(0, 0);

    painter.fillRect(0, 0, rect().width(), rect().height(), palette().background());
    painter.fillPath(pathEdges, brush);
    painter.drawPath(pathEdges);

    painter.translate(QPoint(rect().width() / 2, rect().height() / 2));
    painter.setPen(palette().highlightedText().color());
    painter.setBrush(palette().window());
    if (this->isChecked())
        painter.drawPolygon(ptsArrowOpened, 3);
    else
        painter.drawPolygon(ptsArrowClosed, 3);
}

void SidebarButton::enterEvent(QEvent* event)
{	
	mHover = true;
	QPushButton::enterEvent(event);
    update();
}

void SidebarButton::leaveEvent(QEvent* event) 
{
	mHover = false;
	QPushButton::leaveEvent(event);
    update();
}
