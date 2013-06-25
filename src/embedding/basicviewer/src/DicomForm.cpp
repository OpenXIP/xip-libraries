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
*/#include "DicomForm.h"

#include <QMouseEvent>
#include <QDomElement>

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoField.h>

#include "SoRefXipGetDicomString.h"

DicomForm::DicomForm(QWidget* parent, QList<NameGroupElementPair>* _dicomElements) : QWidget(parent)
{
	isDraggingWindow_ = false;
	dragPosition_ = QPoint();
    dicomInfo = 0;
    dicomElements = _dicomElements;

    setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    lblTitle->setText(this->windowTitle());

    connect(btnClose, SIGNAL(clicked()), this, SLOT(sPressedClose()));
    dicomInfo = new SoRefXipGetDicomString("dicomInfo");
}

DicomForm::~DicomForm()
{
}

void DicomForm::sPressedClose()
{
    emit sigClosed();
    this->close();
}

//void DicomForm::showEvent(QShowEvent* event)
//{
//    this->update();
//}

void DicomForm::update()
{
    if (!dicomElements) return;
    this->txtDicominfo->setPlainText("");
    for (int i = 0; i < dicomElements->length(); i++)
    {
        dicomInfo->setGroup(dicomElements->at(i).getGroup());
        dicomInfo->setElement(dicomElements->at(i).getElement());
        this->txtDicominfo->appendPlainText(dicomElements->at(i).getName() + ": " + dicomInfo->getOutput());
    }
}

void DicomForm::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
	{
		dragPosition_ = event->pos();
		isDraggingWindow_ = true;
		event->accept();
    }
	else
		isDraggingWindow_ = false;
}

void DicomForm::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton && !this->isMaximized() && isDraggingWindow_)
	{
		move(frameGeometry().topLeft() + event->pos() - dragPosition_);
        event->accept();
    }
}

void DicomForm::mouseReleaseEvent(QMouseEvent* event)
{
	isDraggingWindow_ = false;
	if (event->buttons() == Qt::LeftButton)
		event->accept();
}

void DicomForm::clear()
{
    if (!dicomElements) return;
    dicomElements->clear();
    this->txtDicominfo->setPlainText("");
}

//void DicomForm::addDicomString(QString name, unsigned short group, unsigned short element)
//{
//    this->dicomElements.append(NameGroupElementPair(name, group, element));
//}
