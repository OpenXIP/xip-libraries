#ifndef PRESETBUTTON_H
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