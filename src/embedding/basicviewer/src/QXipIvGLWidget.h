#ifndef QXIPIVGLWIDGET_H
#define QXIPIVGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/qglframebufferobject.h>

class SoNode;
class SoSeparator;
class SoSceneManager;
class SoField;

class QXipIvGLWidget : public QGLWidget
{
	Q_OBJECT

public:
	QXipIvGLWidget(SoSceneManager* sceneManager, QWidget* parent, QGLWidget* shareWidget);
	
	~QXipIvGLWidget();

protected:
	virtual void paintGL();
	virtual void glInit();

	SoSceneManager* m_sceneManager;
};

#endif // QXIPIVGLWIDGET_H