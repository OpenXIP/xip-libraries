#include "QXipIvGLWidget.h"

#include <QtGui/QMouseEvent>

#include <Inventor/SoInteraction.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>

#include <Inventor/actions/SoActions.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseWheelEvent.h>
#include <Inventor/errors/SoErrors.h>

#include <QtOpenGL/QtOpenGL>
#include <xip/system/standard.h>
#include <QtOpenGL/QGLFramebufferObject>
#include <QtGui/QPainter>

#include "definitions.h"

QXipIvGLWidget::QXipIvGLWidget(SoSceneManager* sceneManager, QWidget* parent, QGLWidget* shareWidget) : 
	  QGLWidget(QGLFormat(QGL::AlphaChannel|QGL::StencilBuffer|QGL::DepthBuffer|QGL::Rgba), parent, shareWidget)
{
	setAutoBufferSwap(false);
	m_sceneManager = sceneManager;
}

QXipIvGLWidget::~QXipIvGLWidget()
{
}

void QXipIvGLWidget::paintGL()
{
    try
    {
	    m_sceneManager->render();
    }
    catch (...)
    {
    }
	swapBuffers();
}

void QXipIvGLWidget::glInit()
{
	QGLWidget::glInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
}