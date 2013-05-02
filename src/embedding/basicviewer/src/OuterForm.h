#ifndef OUTERFORM_H
#define OUTERFORM_H

#include <QtGui/QWidget>
#include <QMainWindow>
#include "ui_OuterForm.h"

class MainForm;

class OuterForm : public QWidget, private Ui::OuterForm
{
	Q_OBJECT

public:
    OuterForm(QWidget* parent = 0, Qt::WFlags flags = 0);
    ~OuterForm();

//    void setChildWidget(MainForm* child);

private:
	Ui::OuterForm ui;

	bool isDraggingWindow_;
	QPoint dragPosition_;
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void resizeEvent(QResizeEvent* event);

private slots:
	void sPressedClose();
	void sPressedMaximize();
    void sChangedDicomDir(QString newDicomDir);
};

#endif // OUTERFORM_H
