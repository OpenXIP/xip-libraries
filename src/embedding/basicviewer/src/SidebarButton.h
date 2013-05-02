#ifndef SIDEBARBUTTON_H
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