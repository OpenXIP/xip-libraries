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
*/#ifndef OUTERFORM_H
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
