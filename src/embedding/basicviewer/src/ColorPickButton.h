#ifndef COLORPICKBUTTON_H
#define COLORPICKBUTTON_H

#include <QPushButton>

class QPainter;

class ColorPickButton : public QPushButton
{
    Q_OBJECT

public:
    ColorPickButton(QWidget* parent = 0);
    ~ColorPickButton();

    void setIndent(int indent);

    void setColor(QColor color);
    QColor getColor();

private:
    QColor value;
    bool init;
    int leftIndent;
    int halfSize;
    int quartSize;

protected:
    virtual void paintEvent(QPaintEvent* event);

private slots:
    void chooseColor();

signals:
    void changedColor();
};

#endif