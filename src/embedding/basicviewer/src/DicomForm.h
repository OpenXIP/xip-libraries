#ifndef DICOMFORM_H
#define DICOMFORM_H

#include <QtGui/QWidget>
#include <QList>
#include <QListIterator>
#include <QDebug>
#include "ui_DicomForm.h"

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>

#include "definitions.h"

class SoRefXipGetDicomString;
class QDomElement;

class DicomForm : public QWidget, private Ui::FormDicom
{
    Q_OBJECT

public:
    DicomForm(QWidget* parent = 0, QList<NameGroupElementPair>* _dicomElements = 0);
    ~DicomForm();

    void clear();
    //void addDicomString(QString name, unsigned short group, unsigned short element);
    //void addDicomString(QDomElement* _element);
    void update();

private:
    bool isDraggingWindow_;
    QPoint dragPosition_;

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

    SoRefXipGetDicomString* dicomInfo;
    QList<NameGroupElementPair>* dicomElements;

protected:
    //virtual void showEvent(QShowEvent* event);

private slots:
    void sPressedClose();

signals:
    void sigClosed();
};

#endif