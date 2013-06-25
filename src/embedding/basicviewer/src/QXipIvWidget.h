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
*/#ifndef QXIPIVWIDGET_H
#define QXIPIVWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/qglframebufferobject.h>

class SoNode;
class SoSeparator;
class SoSceneManager;
class SoField;
class SoMFString;

class QXipIvWidget : public QWidget
{
	Q_OBJECT

public:
	QXipIvWidget(QWidget* parent = 0, QGLWidget* shareWidget = 0);
	virtual ~QXipIvWidget();

	virtual void setRoot(SoNode* node);
	virtual void resizeEvent(QResizeEvent* event);

	virtual QGLWidget* getGLWidget() const;
	virtual void resizeGL(int width, int height);

    void processDelayQueue(bool idle = false);

protected:
	virtual void paintEvent(QPaintEvent* event);

	virtual void closeEvent(QCloseEvent* event);

	virtual void updateCursor(bool fromScene);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);

    virtual void mouseLeaveEvent(QMouseEvent* event);


	SoSeparator* m_root;
	SoNode* m_sceneObject;
	QPoint m_mouseDownPos;

	bool m_isSceneManagerActive;
	quint64 m_IdleTimer;
	SoSceneManager* m_sceneManager;

	int m_width;
	int m_height;
	SoMFString* m_cursorField;

	enum { RESIZE_NONE, RESIZE_WIDTH, RESIZE_HEIGHT, RESIZE_CORNER } m_mouseMode;

	QGLWidget* m_GLWidget;

signals:
    void mouseRightButtonPressed();

private:
	static void renderSceneCbFunc_(void* user, class SoSceneManager*);

private slots:
	void doIdleProcessing();
};

#endif // QXIPIVWIDGET_H
