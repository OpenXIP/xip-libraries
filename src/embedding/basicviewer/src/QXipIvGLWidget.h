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
*/#ifndef QXIPIVGLWIDGET_H
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
