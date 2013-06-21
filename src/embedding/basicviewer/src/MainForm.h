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
*/#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "ui_MainForm.h"

class SoSeparator;
class QXipIvWidget;
class SoSensor;
class SoRefXipLut;
class SoRefXipExaminer;
class SoRefXipMprExaminer;
class SoRefXipWindowLevelManip;
class SoRefXipLoadDicom;
class SoRefXipViewportGroup;
class SoRefXipTexture;
class SoRefXipSlicer;

class MainForm : public QMainWindow, private Ui::MainFormClass
{
	Q_OBJECT

public:
	MainForm(QWidget* parent = 0, Qt::WFlags flags = 0);
	~MainForm();

private:
	Ui::MainFormClass ui;

    QXipIvWidget* refXipIvWidget;

	void initFields();
	void initConnections();
    void initControlValues();
	void initCallbacks();
    void initPresets();

    SoRefXipLut* vrLut;
    SoRefXipMprExaminer* mprExaminer0;
    SoRefXipMprExaminer* mprExaminer1;
    SoRefXipMprExaminer* mprExaminer2;
    SoRefXipExaminer* vrExaminer;
    SoRefXipWindowLevelManip* mprWindowLevelManip;
    SoRefXipLoadDicom* dicomLoader;
    SoRefXipViewportGroup* renderArea;
    SoRefXipTexture* vrTexture;
    SoRefXipSlicer* vrSlicer;

    bool isUpdatingGui_;
	bool isDraggingWindow_;
	QPoint dragPosition_;
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void resizeEvent(QResizeEvent* event);

    static void cbModeChanged(void* user, SoSensor* sensor);
	static void cbWindowChanged(void* user, SoSensor* sensor);
	static void cbLevelChanged(void* user, SoSensor* sensor);
    static void cbRampWidthChanged(void* user, SoSensor* sensor);
    static void cbRampCenterChanged(void* user, SoSensor* sensor);
    static void cbColorBottomChanged(void* user, SoSensor* sensor);
    static void cbColorMiddleChanged(void* user, SoSensor* sensor);
    static void cbColorTopChanged(void* user, SoSensor* sensor);
    static void cbDicomNameChanged(void* user, SoSensor* sensor);

signals:
    void changedDicomDir(QString newDicomDir);

private slots:
	void sPressedReset();
    void sPressedLoadModel();
	void sChangedWindowValue(int newValue);
	void sChangedLevelValue(int newValue);
    void sTogglePresetMixerForm(bool show);
    void sPresetMixerFormClosed();
    void sToggleDicomForm(bool show);
    void sDicomFormClosed();

    void sChangedExaminerMode(QString mode);
    void sChangedNumSlices(int numSlices);
    void sChangedSlicerMode(QString mode);
    void sChangedColorTop();
    void sChangedColorMiddle();
    void sChangedColorBottom();

    void sClickedMaxTopLeft();
    void sClickedMaxTopRight();
    void sClickedMaxBottomLeft();
    void sClickedMaxBottomRight();
    void sClickedViewAll();

    void sConfirmedWindowValue();
    void sConfirmedLevelValue();

    void sChangedRampWidth(int newValue);
    void sChangedRampCenter(int newValue);
    void sConfirmedRampWidth();
    void sConfirmedRampCenter();

    void sPressedRightButton();

    void sClickedExit();
};

#endif // MAINFORM_H
