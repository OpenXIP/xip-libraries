#ifndef PRESETSLOT_H
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