#include "OuterForm.h"

#include <QMouseEvent>

#include "ViewerCore.h"
#include "MainForm.h"
#include "definitions.h"

OuterForm::OuterForm(QWidget* parent, Qt::WFlags flags) : QWidget(parent, flags)
{
	isDraggingWindow_ = false;
	dragPosition_ = QPoint();

    setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);

    connect(childWidget, SIGNAL(changedDicomDir(QString)), this, SLOT(sChangedDicomDir(QString)));
    connect(btnMinimize, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(btnMaximize, SIGNAL(clicked()), this, SLOT(sPressedMaximize()));
	connect(btnClose, SIGNAL(clicked()), this, SLOT(sPressedClose()));
}

OuterForm::~OuterForm()
{
}

void OuterForm::sChangedDicomDir(QString newDicomDir)
{
    this->lblTitle->setText(" - " + ViewerCore::get()->getShortDicomPath());
}

void OuterForm::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) return;
    event->accept();
    sPressedMaximize();
}

void OuterForm::mousePressEvent(QMouseEvent* event)
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

void OuterForm::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton && !this->isMaximized() && isDraggingWindow_)
	{
		move(frameGeometry().topLeft() + event->pos() - dragPosition_);
        event->accept();
    }
}

void OuterForm::mouseReleaseEvent(QMouseEvent* event)
{
	isDraggingWindow_ = false;
	if (event->buttons() == Qt::LeftButton)
		event->accept();
}

void OuterForm::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
}

void OuterForm::sPressedClose()
{
	this->close();
}

void OuterForm::sPressedMaximize()
{
	if (this->windowState() != Qt::WindowMaximized)
        showMaximized();
	else
        showNormal();
}
