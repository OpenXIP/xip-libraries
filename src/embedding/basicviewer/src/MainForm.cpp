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
*/#include "MainForm.h"

#include <Inventor/SoInteraction.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include <QMouseEvent>
#include <QFileDialog>
#include <QColorDialog>

#include "PresetButton.h"
#include "XipPreset.h"
#include "PresetMixerForm.h"
#include "DicomForm.h"
#include "QXipIvWidget.h"
#include "SoRefXipLut.h"
#include "SoRefXipExaminer.h"
#include "SoRefXipMprExaminer.h"
#include "SoRefXipWindowLevelManip.h"
#include "SoRefXipLoadDicom.h"
#include "SoRefXipViewportGroup.h"
#include "SoRefXipTexture.h"
#include "SoRefXipSlicer.h"
#include "ViewerCore.h"
#include "definitions.h"

MainForm::MainForm(QWidget* parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
    vrLut = 0;
    mprExaminer0 = 0;
    mprExaminer1 = 0;
    mprExaminer2 = 0;
    vrExaminer = 0;
    mprWindowLevelManip = 0;
    vrTexture = 0;
    vrSlicer = 0;

    isUpdatingGui_ = false;
	isDraggingWindow_ = false;

	setupUi(this);
    ViewerCore::get()->createPresetMixerForm(this);
    ViewerCore::get()->createDicomForm(this, ViewerCore::get()->getDicomElementList());

    setWindowFlags(Qt::CustomizeWindowHint);

	initFields();
    initControlValues();
	initConnections();
	initCallbacks();
    initPresets();
}

MainForm::~MainForm()
{

}

void MainForm::initFields()
{
    vrLut = new SoRefXipLut("vrLut");
    mprExaminer0 = new SoRefXipMprExaminer("mprExaminer0");
    mprExaminer1 = new SoRefXipMprExaminer("mprExaminer1");
    mprExaminer2 = new SoRefXipMprExaminer("mprExaminer2");
    vrExaminer = new SoRefXipExaminer("vrExaminer");
    mprWindowLevelManip = new SoRefXipWindowLevelManip("mprWindowLevelManip");
    dicomLoader = new SoRefXipLoadDicom("dicomLoader");
    renderArea = new SoRefXipViewportGroup("renderArea");
    vrTexture = new SoRefXipTexture("vrTexture");
    vrSlicer = new SoRefXipSlicer("vrSlicer", vrTexture);
}

void MainForm::initConnections()
{
	connect(btnResetView, SIGNAL(clicked()), this, SLOT(sPressedReset()));
    connect(btnLoadModel, SIGNAL(clicked()), this, SLOT(sPressedLoadModel()));
	connect(sliWindow, SIGNAL(valueChanged(int)), this, SLOT(sChangedWindowValue(int)));
	connect(sliLevel, SIGNAL(valueChanged(int)), this, SLOT(sChangedLevelValue(int)));

    connect(sliSlicerNumSlices, SIGNAL(valueChanged(int)), this, SLOT(sChangedNumSlices(int)));
    connect(cmbSlicerMode, SIGNAL(currentIndexChanged(QString)), this, SLOT(sChangedSlicerMode(QString)));
    connect(cmbExaminerMode, SIGNAL(currentIndexChanged(QString)), this, SLOT(sChangedExaminerMode(QString)));
    connect(btnColorTop, SIGNAL(changedColor()), this, SLOT(sChangedColorTop()));
    connect(btnColorMiddle, SIGNAL(changedColor()), this, SLOT(sChangedColorMiddle()));
    connect(btnColorBottom, SIGNAL(changedColor()), this, SLOT(sChangedColorBottom()));

    connect(sliRampWidth, SIGNAL(valueChanged(int)), this, SLOT(sChangedRampWidth(int)));
    connect(sliRampCenter, SIGNAL(valueChanged(int)), this, SLOT(sChangedRampCenter(int)));
    connect(txtRampWidth, SIGNAL(returnPressed()), this, SLOT(sConfirmedRampWidth()));
    connect(txtRampCenter, SIGNAL(returnPressed()), this, SLOT(sConfirmedRampCenter()));

    connect(btnMaxTopLeft, SIGNAL(clicked()), this, SLOT(sClickedMaxTopLeft()));
    connect(btnMaxTopRight, SIGNAL(clicked()), this, SLOT(sClickedMaxTopRight()));
    connect(btnMaxBottomLeft, SIGNAL(clicked()), this, SLOT(sClickedMaxBottomLeft()));
    connect(btnMaxBottomRight, SIGNAL(clicked()), this, SLOT(sClickedMaxBottomRight()));
    connect(btnViewAll, SIGNAL(clicked()), this, SLOT(sClickedViewAll()));

    connect(txtWindow, SIGNAL(returnPressed()), this, SLOT(sConfirmedWindowValue()));
    connect(txtLevel, SIGNAL(returnPressed()), this, SLOT(sConfirmedLevelValue()));

    connect(actOpen, SIGNAL(triggered()), this, SLOT(sPressedLoadModel()));
    connect(actExit, SIGNAL(triggered()), this, SLOT(sClickedExit()));

    connect(glWidget, SIGNAL(mouseRightButtonPressed()), this, SLOT(sPressedRightButton()));

    connect(btnToggleCrossfader, SIGNAL(toggled(bool)), this, SLOT(sTogglePresetMixerForm(bool)));
    connect(btnToggleDicom, SIGNAL(toggled(bool)), this, SLOT(sToggleDicomForm(bool)));
    connect(ViewerCore::get()->getPresetMixerForm(), SIGNAL(sigClosed()), this, SLOT(sPresetMixerFormClosed()));
    connect(ViewerCore::get()->getDicomForm(), SIGNAL(sigClosed()), this, SLOT(sDicomFormClosed()));
}

void MainForm::initControlValues()
{
    emit changedDicomDir(dicomLoader->getName());

    sliSlicerNumSlices->setValue(vrSlicer->getNumSlices());

    cmbSlicerMode->clear();
    cmbSlicerMode->addItems(vrSlicer->getModeList());
    cmbSlicerMode->setCurrentIndex(cmbSlicerMode->findText(vrSlicer->getMode()));

    cmbExaminerMode->clear();
    cmbExaminerMode->addItems(vrExaminer->getModeList());
    cmbExaminerMode->setCurrentIndex(cmbExaminerMode->findText(vrExaminer->getMode()));

    cbColorTopChanged(this, 0);
    cbColorMiddleChanged(this, 0);
    cbColorBottomChanged(this, 0);

    cbLevelChanged(this, 0);
    cbWindowChanged(this, 0);

    cbRampWidthChanged(this, 0);
    cbRampCenterChanged(this, 0);

    cbDicomNameChanged(this, 0);
}

void MainForm::initCallbacks()
{
    vrExaminer->setModeCB(&cbModeChanged, this);
    mprWindowLevelManip->setWindowCB(&cbWindowChanged, this);
    mprWindowLevelManip->setLevelCB(&cbLevelChanged, this);
    vrLut->setRampWidthCB(&cbRampWidthChanged, this);
    vrLut->setRampCenterCB(&cbRampCenterChanged, this);
    vrLut->setColorBottomCB(&cbColorBottomChanged, this);
    vrLut->setColorMiddleCB(&cbColorMiddleChanged, this);
    vrLut->setColorTopCB(&cbColorTopChanged, this);
    dicomLoader->setNameCB(&cbDicomNameChanged, this);
}

void MainForm::initPresets()
{
    for (int i = 0; i < ViewerCore::get()->getPresetList()->length(); i++)
    {
        PresetButton* newPresetButton = new PresetButton(ViewerCore::get()->getPresetList()->at(i));
        QGroupBox* tmpGrpBox = this->findChild<QGroupBox*>(ViewerCore::get()->getPresetList()->at(i)->getGroupBoxName());
        if (!tmpGrpBox)
        {
            ERROR_MSG("Cannot find groupbox \"" + ViewerCore::get()->getPresetList()->at(i)->getGroupBoxName() + "\"");
            continue;
        }
        if (!tmpGrpBox->layout())
        {
            ERROR_MSG("Groupbox \"" + ViewerCore::get()->getPresetList()->at(i)->getGroupBoxName() + "\" has no layout");
            continue;
        }
        tmpGrpBox->layout()->addWidget(newPresetButton);
    }
}

void MainForm::sPressedRightButton()
{
    vrExaminer->switchModes();
}

void MainForm::mouseDoubleClickEvent(QMouseEvent* event)
{
    event->accept();
}

void MainForm::mousePressEvent(QMouseEvent* event)
{
	event->accept();
}

void MainForm::mouseMoveEvent(QMouseEvent* event)
{
    //event->accept();
}

void MainForm::mouseReleaseEvent(QMouseEvent* event)
{
	event->accept();
}

#pragma region Callbacks
void MainForm::cbModeChanged(void* user, SoSensor* sensor)
{
    MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    thisPtr->cmbExaminerMode->setCurrentIndex(thisPtr->cmbExaminerMode->findText(thisPtr->vrExaminer->getMode()));
    thisPtr->isUpdatingGui_ = false;
}

void MainForm::cbWindowChanged(void* user, SoSensor* sensor)
{
	MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    thisPtr->sliWindow->setValue(100 - thisPtr->mprWindowLevelManip->getWindow() * 100);
    thisPtr->txtWindow->setText(QString::number(thisPtr->mprWindowLevelManip->getWindow()));
    thisPtr->isUpdatingGui_ = false;
}

void MainForm::cbLevelChanged(void* user, SoSensor* sensor)
{
	MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    thisPtr->sliLevel->setValue(100 - thisPtr->mprWindowLevelManip->getLevel() * 100);
    thisPtr->txtLevel->setText(QString::number(thisPtr->mprWindowLevelManip->getLevel()));
    thisPtr->isUpdatingGui_ = false;
}

void MainForm::cbRampWidthChanged(void* user, SoSensor* sensor)
{
	MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    thisPtr->sliRampWidth->setValue(100 - thisPtr->vrLut->getRampWidth() * 100);
    thisPtr->txtRampWidth->setText(QString::number(thisPtr->vrLut->getRampWidth()));
    thisPtr->isUpdatingGui_ = false;
}

void MainForm::cbRampCenterChanged(void* user, SoSensor* sensor)
{
	MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    thisPtr->sliRampCenter->setValue(100 - thisPtr->vrLut->getRampCenter() * 100);
    thisPtr->txtRampCenter->setText(QString::number(thisPtr->vrLut->getRampCenter()));
    thisPtr->isUpdatingGui_ = false;
}

void MainForm::cbColorBottomChanged(void *user, SoSensor *sensor)
{
	MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    thisPtr->btnColorBottom->setColor(thisPtr->vrLut->getColorBottom());
    thisPtr->isUpdatingGui_ = false;
}

void MainForm::cbColorMiddleChanged(void* user, SoSensor* sensor)
{
	MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    thisPtr->btnColorMiddle->setColor(thisPtr->vrLut->getColorMiddle());
    thisPtr->isUpdatingGui_ = false;
}

void MainForm::cbColorTopChanged(void* user, SoSensor* sensor)
{
	MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    thisPtr->btnColorTop->setColor(thisPtr->vrLut->getColorTop());
    thisPtr->isUpdatingGui_ = false;
}

void MainForm::cbDicomNameChanged(void* user, SoSensor* sensor)
{
    MainForm* thisPtr = (MainForm*)user;
    thisPtr->isUpdatingGui_ = true;
    ViewerCore::get()->getDicomForm()->update();
    thisPtr->isUpdatingGui_ = false;
}
#pragma endregion

#pragma region Gui-Slots
void MainForm::sClickedMaxTopLeft()
{
    renderArea->setWindow1Maximized();
}
void MainForm::sClickedMaxTopRight()
{
    renderArea->setWindow2Maximized();
}
void MainForm::sClickedMaxBottomLeft()
{
    renderArea->setWindow0Maximized();
}
void MainForm::sClickedMaxBottomRight()
{
    renderArea->setWindow3Maximized();
}
void MainForm::sClickedViewAll()
{
    renderArea->setNormalState();
}

void MainForm::sChangedNumSlices(int numSlices)
{
    vrSlicer->setNumSlices(numSlices);
}

void MainForm::sChangedSlicerMode(QString mode)
{
    vrSlicer->setMode(mode);
}

void MainForm::sChangedExaminerMode(QString mode)
{
    vrExaminer->setMode(mode);
}

void MainForm::sChangedColorTop()
{
    if (isUpdatingGui_) return;
    vrLut->setColorTop(btnColorTop->getColor());
}

void MainForm::sChangedColorMiddle()
{
    if (isUpdatingGui_) return;
    vrLut->setColorMiddle(btnColorMiddle->getColor());
}

void MainForm::sChangedColorBottom()
{
    if (isUpdatingGui_) return;
    vrLut->setColorBottom(btnColorBottom->getColor());
}

void MainForm::sPressedLoadModel()
{
    QString newDicomDir;

    if (g_bUseDirectoryPicker)
    {
        newDicomDir = QFileDialog::getExistingDirectory(this, "Open Dicom", ViewerCore::get()->getDicomPath());
        if (newDicomDir.isEmpty()) return;
        ViewerCore::get()->setDicomPath(newDicomDir.replace("/", "\\"));
    }
    else
    {
        newDicomDir = QFileDialog::getOpenFileName(this, "Open Dicom", ViewerCore::get()->getDicomPath());
        if (newDicomDir.isEmpty()) return;
        QFileInfo fileInfo(newDicomDir);
        newDicomDir = fileInfo.absolutePath().replace("/", "\\");
        ViewerCore::get()->setDicomPath(newDicomDir);
    }

    SET_WAITCURSOR();
    QApplication::processEvents();
    dicomLoader->setName(newDicomDir);
    emit changedDicomDir(newDicomDir);
    sPressedReset();
	SoDB::getSensorManager()->processDelayQueue(FALSE);
    SET_DEFAULTCURSOR();
}

void MainForm::sPressedReset()
{
    mprExaminer0->resetView("FEET");
    mprExaminer1->resetView("LEFT");
    mprExaminer2->resetView("POSTERIOR");
    vrExaminer->resetView("ANTERIOR");
    mprWindowLevelManip->resetValues();
}

void MainForm::sChangedWindowValue(int newValue)
{
    if (isUpdatingGui_) return;
    mprWindowLevelManip->setWindow(1.0 - newValue * 0.01);
}

void MainForm::sChangedLevelValue(int newValue)
{
    if (isUpdatingGui_) return;
    mprWindowLevelManip->setLevel(1.0 - newValue * 0.01);
}

void MainForm::sConfirmedWindowValue()
{
    if (isUpdatingGui_) return;
    mprWindowLevelManip->setWindow(txtWindow->text().toFloat());
}

void MainForm::sConfirmedLevelValue()
{
    if (isUpdatingGui_) return;
    mprWindowLevelManip->setLevel(txtLevel->text().toFloat());
}

void MainForm::sChangedRampWidth(int newValue)
{
    if (isUpdatingGui_) return;
    vrLut->setRampWidth(1.0 - newValue * 0.01);
}

void MainForm::sChangedRampCenter(int newValue)
{
    if (isUpdatingGui_) return;
    vrLut->setRampCenter(1.0 - newValue * 0.01);
}

void MainForm::sConfirmedRampWidth()
{
    if (isUpdatingGui_) return;
    vrLut->setRampWidth(txtRampWidth->text().toFloat());
}

void MainForm::sConfirmedRampCenter()
{
    if (isUpdatingGui_) return;
    vrLut->setRampCenter(txtRampCenter->text().toFloat());
}

void MainForm::sClickedExit()
{
    QApplication::exit();
}

void MainForm::sPresetMixerFormClosed()
{
    this->btnToggleCrossfader->setChecked(false);
}

void MainForm::sDicomFormClosed()
{
    this->btnToggleDicom->setChecked(false);
}

void MainForm::sTogglePresetMixerForm(bool show)
{
    ViewerCore::get()->togglePresetMixerForm(show);
}

void MainForm::sToggleDicomForm(bool show)
{
    ViewerCore::get()->toggleDicomForm(show);
}
#pragma endregion

void MainForm::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
}
