#include "QXipIvWidget.h"
#include "QXipIvGLWidget.h"

#include <QtGui/QMouseEvent>
#include <QTimer>

#include <Inventor/SoInteraction.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>

#include <Inventor/actions/SoActions.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseWheelEvent.h>
#include <Inventor/errors/SoErrors.h>

#include <QtOpenGL/QtOpenGL>
#include <xip/system/standard.h>
#include <QtOpenGL/QGLFramebufferObject>
#include <QtGui/QPainter>

#include "ViewerCore.h"
#include "definitions.h"

QXipIvWidget::QXipIvWidget(QWidget* parent, QGLWidget* shareWidget) : QWidget(parent)
{
	m_cursorField = 0;
	m_sceneObject = 0;
	m_mouseDownPos = QPoint(-1, -1);

	m_width = 0;
	m_height = 0;
    m_root = 0;
	m_mouseMode = RESIZE_NONE;

	m_sceneManager = 0;
	m_isSceneManagerActive = false;

	setMouseTracking(true);
	setAutoFillBackground(false);

	m_sceneManager = new SoSceneManager;
	m_sceneManager->setGLRenderAction(new SoGLRenderAction(SbViewportRegion(512, 512)));
	m_sceneManager->setRenderCallback(renderSceneCbFunc_, this);

    m_sceneManager->setSceneGraph(ViewerCore::get()->getRootNode());

	m_sceneManager->activate();
	m_isSceneManagerActive = true;

	m_GLWidget = new QXipIvGLWidget(m_sceneManager, this, shareWidget);

	m_GLWidget->show();
	m_GLWidget->setMouseTracking(true);

	QTimer* mIdleTimer = new QTimer(this);
	connect(mIdleTimer, SIGNAL(timeout()), this, SLOT(doIdleProcessing()));
	mIdleTimer->start(40);
}

void QXipIvWidget::doIdleProcessing()
{
    try
    {
        SoDB::getSensorManager()->processTimerQueue();
    }
    catch (...)
    {
        //QXipBuilderError::postException("SoSceneManager::processTimerQueue()");
    }

    try
    {
        SoDB::getSensorManager()->processDelayQueue(TRUE);
    }
    catch (...)
    {
        //QXipBuilderError::postException("SoSceneManager::processDelayQueue()");
    }
}
void QXipIvWidget::updateCursor(bool fromScene)
{
	if (fromScene)
	{
		if (!m_cursorField)
		{
			m_cursorField = dynamic_cast<SoMFString*>(SoDB::getGlobalField(SbName("XipCursor")));
		}

		if (m_cursorField)
		{
			SbString newCursor;
			m_cursorField->get1(0, newCursor);

            if (strcmp(newCursor.getString(), "\"MOVE_LINE\"") == 0)
                setCursor(Qt::SizeAllCursor);
            else if (strcmp(newCursor.getString(), "\"MOVE\"") == 0)
                setCursor(Qt::SizeAllCursor);
            else if (strcmp(newCursor.getString(), "\"ROTATE_INPLANE\"") == 0)
                setCursor(Qt::OpenHandCursor);
            else if (strcmp(newCursor.getString(), "\"ROTATE_NORMAL_VR\"") == 0)
                setCursor(Qt::OpenHandCursor);
            else if (strcmp(newCursor.getString(), "\"SEL_ROTATE\"") == 0)
                setCursor(Qt::ArrowCursor);
            else if (strcmp(newCursor.getString(), "\"SEL_ROTATE_VR\"") == 0)
                setCursor(Qt::ArrowCursor);
            else if (strcmp(newCursor.getString(), "\"SEL_ZOOM\"") == 0)
                setCursor(Qt::SizeVerCursor);
            else if (strcmp(newCursor.getString(), "\"SEL_PAN\"") == 0)
                setCursor(Qt::ArrowCursor);
            else
            {
                setCursor(Qt::ArrowCursor);
//                qDebug() << newCursor.getString();
            }
        }

//			const char* handlePtr = strstr(str.getString(), "handle\t");
//			if (handlePtr)
//			{
//				void* handle = 0;
//				if (sscanf(handlePtr, "handle\t%p", &handle) == 1)
//				{
//					if (handle)
//					{
//#ifdef WIN32
//						setCursor(QCursor((HCURSOR) handle));
//#endif /* WIN32 */
//
//#ifdef linux
//						setCursor(QCursor((Qt::HANDLE) handle));
//#endif /* LINUX */
//
//#ifdef DARWIN
//						setCursor(QCursor()); // FIXME: We must create a handle for Mac OS X
//#endif /* DARWIN */
//
//						return;
//					}
//				}
//			}
//		}
	}

	//setCursor(Qt::ArrowCursor);
}


void QXipIvWidget::mouseReleaseEvent(QMouseEvent* event)
{
	event->accept();

	if (m_mouseMode == RESIZE_NONE)
	{
		SbTime time;
		time.setToTimeOfDay();
		SoMouseButtonEvent e;
		e.setTime(time);

		switch (event->button())
		{
		    default:
		    case Qt::LeftButton:	e.setButton(SoMouseButtonEvent::BUTTON1); break;
		    case Qt::MidButton:		e.setButton(SoMouseButtonEvent::BUTTON2); break;
		    case Qt::RightButton:	e.setButton(SoMouseButtonEvent::BUTTON3); break;
		}
		if (event->modifiers() & Qt::ShiftModifier) e.setShiftDown(TRUE);
		if (event->modifiers() & Qt::ControlModifier) e.setCtrlDown(TRUE);

		e.setState(SoButtonEvent::UP);
		e.setPosition(SbVec2s(event->pos().x(), m_height - event->pos().y()));

		if (m_sceneManager->processEvent(&e))
		{
			processDelayQueue();
			updateCursor(true);
		}
		else
		{
			updateCursor(false);
		}
	}

	m_mouseMode = RESIZE_NONE;
}

void QXipIvWidget::mousePressEvent(QMouseEvent* event)
{
	//m_mouseMode = RESIZE_NONE;
	//if ((event->pos().x() > (this->width() - 10)) || (event->pos().y() > (this->height() - 10)))
	//{
	//	//if ((event->pos().x() > (this->width() - 10)) || (event->pos().y() > (this->height() - 10)))
	//	{
	//		if ((event->pos().x() > (this->width() - 10)) && (event->pos().y() > (this->height() - 10)))
	//		{
	//			m_mouseMode = RESIZE_CORNER;

	//			setCursor(Qt::SizeFDiagCursor);
	//		}
	//		else if (event->pos().x() > (this->width() - 10))
	//		{
	//			m_mouseMode = RESIZE_WIDTH;

	//			setCursor(Qt::SizeHorCursor);
	//		}
	//		else if (event->pos().y() > (this->height() - 10))
	//		{
	//			m_mouseMode = RESIZE_HEIGHT;

	//			setCursor(Qt::SizeVerCursor);
	//		}
	//	}

	//	event->accept();

	//	return;
	//}

	event->accept();

    // Pass the QT mouse button event to open inventor
	SbTime time;
	time.setToTimeOfDay();
	SoMouseButtonEvent e;
	e.setTime(time);

	switch (event->button())
	{
	    default:
	        case Qt::LeftButton:	e.setButton(SoMouseButtonEvent::BUTTON1); break;
	        case Qt::MidButton:     e.setButton(SoMouseButtonEvent::BUTTON2); break;
            case Qt::RightButton:   emit mouseRightButtonPressed(); break;
	}
	if (event->modifiers() & Qt::ShiftModifier) 
        e.setShiftDown(TRUE);
	if (event->modifiers() & Qt::ControlModifier)
        e.setCtrlDown(TRUE);
	e.setState(SoButtonEvent::DOWN);
	e.setPosition(SbVec2s(event->pos().x(), m_height - event->pos().y()));

	if (m_sceneManager->processEvent(&e))
	{
		processDelayQueue();
		updateCursor(true);
	}
	else
	{
		updateCursor(false);
	}
}

void QXipIvWidget::processDelayQueue(bool idle)
{
		SoDB::getSensorManager()->processDelayQueue(idle ? TRUE : FALSE);
}

void QXipIvWidget::mouseMoveEvent(QMouseEvent* event)
{
	QWidget* pWidget = parentWidget()->parentWidget();

//    qDebug() << "QXipIvWidget::mouseMoveEvent";

	bool onResizeBorder = false;

	//if (!event->buttons())
	//{
	//	if ((event->pos().x() > (this->width() - 10)) || (event->pos().y() > (this->height() - 10)))
	//	{
	//		if ((event->pos().x() > (this->width() - 10)) || (event->pos().y() > (this->height() - 10)))
	//		{
	//			if ((event->pos().x() > (this->width() - 10)) && (event->pos().y() > (this->height() - 10)))
	//			{
	//				setCursor(Qt::SizeFDiagCursor);
	//				onResizeBorder = true;
	//			}
	//			else if (event->pos().x() > (this->width() - 10))
	//			{
	//				setCursor(Qt::SizeHorCursor);
	//				onResizeBorder = true;
	//			}
	//			else if (event->pos().y() > (this->height() - 10))
	//			{
	//				setCursor(Qt::SizeVerCursor);
	//				onResizeBorder = true;
	//			}
	//		}
	//	}
	//}

	switch (m_mouseMode)
	{
	case RESIZE_NONE:
		if (!onResizeBorder)
		{
			event->accept();

			SbTime time;
			time.setToTimeOfDay();
			SoLocation2Event e;
			e.setTime(time);
			if (event->modifiers() & Qt::ShiftModifier)
				e.setShiftDown(TRUE);
			if (event->modifiers() & Qt::ControlModifier)
				e.setCtrlDown(TRUE);
			e.setPosition(SbVec2s(event->pos().x(), m_height - event->pos().y()));
			if (m_sceneManager->processEvent(&e))
			{
				processDelayQueue();
				updateCursor(true);
			}
			else
			{
				updateCursor(false);
			}
		} break;
	case RESIZE_WIDTH:
		{
			pWidget->resize(mapTo(pWidget, event->pos()).x() + 3, pWidget->size().height());
			event->accept();
		} break;
	case RESIZE_HEIGHT:
		{
			pWidget->resize(pWidget->size().width(), mapTo(pWidget, event->pos()).y() + 3);
			event->accept();
		} break;
	case RESIZE_CORNER:
		{
			pWidget->resize(mapTo(pWidget, event->pos()).x() + 3, mapTo(pWidget, event->pos()).y() + 3);
			event->accept();
		} break;
	}
}

void QXipIvWidget::mouseLeaveEvent(QMouseEvent* event)
{
    qDebug() << "Mouse leave event";
}


void QXipIvWidget::wheelEvent(QWheelEvent* event)
{
// TODO: Find a solution for Linux and Mac
#if WIN32
    SbTime time;
    time.setToTimeOfDay();
    SoMouseWheelEvent e;
    e.setTime(time);
    if (event->modifiers() & Qt::ShiftModifier)
        e.setShiftDown(TRUE);
    if (event->modifiers() & Qt::ControlModifier)
        e.setCtrlDown(TRUE);
//#if WIN32
    e.setDelta(event->delta());
    e.setDelta(event->delta() / 120);
	e.setPosition( SbVec2s(event->pos().x(), this->height() - event->pos().y() ) );
//#endif
    if (m_sceneManager->processEvent(&e))
    {
        processDelayQueue();
        updateCursor(true);
    }
    else
    {
        updateCursor(false);
    }
#endif
}

QXipIvWidget::~QXipIvWidget()
{
}

void QXipIvWidget::closeEvent(QCloseEvent* event)
{
}

void QXipIvWidget::setRoot(SoNode* node)
{
	if (m_root)
	{
		m_root->removeAllChildren();

		if (node)
		{
			m_root->addChild(node);
		}
	}
}

void QXipIvWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
	resizeGL(width(), height());
}

void QXipIvWidget::paintEvent(QPaintEvent* event)
{
}

void QXipIvWidget::resizeGL(int width, int height)
{
	m_width = width;
	m_height = height;

	m_GLWidget->resize(m_width, m_height);

	m_sceneManager->setWindowSize(SbVec2s(m_width, m_height));
	m_sceneManager->setSize(SbVec2s(m_width, m_height));
	m_sceneManager->setViewportRegion(SbViewportRegion(m_width, m_height));
}

QGLWidget* QXipIvWidget::getGLWidget() const
{
	return m_GLWidget;
}

void QXipIvWidget::renderSceneCbFunc_(void* user, class SoSceneManager*)
{
	QXipIvWidget* thisPtr = (QXipIvWidget*) user;

	//thisPtr->update();
	thisPtr->m_GLWidget->repaint();
}
