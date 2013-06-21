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
*/#include "ViewerCore.h"

#include <Inventor/nodes/SoSeparator.h>

#include <QApplication>
#include <QDomDocument>
#include <QDomElement>
#include <QString>
#include <QRegExp>
#include <QFile>

#include "XipPreset.h"
#include "IvFileLoader.h"
#include "PresetMixerForm.h"
#include "DicomForm.h"

ViewerCore* ViewerCore::ref = 0;
QString ViewerCore::lastDicomDir_ = ".";
PresetMixerForm* ViewerCore::presetMixerForm = 0;
DicomForm* ViewerCore::dicomForm = 0;

ViewerCore::ViewerCore()
{
    rootNode_ = 0;
    this->createDicomForm();
    this->loadConfigFile("config.xml");
}

ViewerCore::~ViewerCore()
{
}

ViewerCore* ViewerCore::get()
{
    if (!ViewerCore::ref)
        ViewerCore::ref = new ViewerCore();
    return ref;
}

void ViewerCore::loadIvFile(QString fileName)
{
    if (this->rootNode_)
        rootNode_->unref();
    this->rootNode_ = new SoSeparator;
    this->rootNode_->ref();

    IvFileLoader fileLoader(fileName);
    if (fileLoader.result)
        this->rootNode_->addChild(fileLoader.result);
}

void ViewerCore::loadPresets(QDomElement* _element)
{
    for(QDomElement e = _element->firstChildElement("preset"); !e.isNull(); e = e.nextSiblingElement("preset"))
    {
        XipPreset* newPreset = new XipPreset(&e);
        this->presetList.append(newPreset);
    }
}

void ViewerCore::loadDicomConfig(QDomElement* _element)
{
    for (QDomElement e = _element->firstChildElement("dicomString"); !e.isNull(); e = e.nextSiblingElement("dicomString"))
    {
        this->addDicomString(&e);
    }
}

void ViewerCore::loadConfigFile(QString fileName)
{
    QDomDocument XmlDoc("BasicViewerConfig");

	QFile configFile(fileName);
	if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		ERROR_MSG("Error opening file: " + fileName);
		return;
	}

	if (!XmlDoc.setContent(&configFile))
	{
		configFile.close();
		ERROR_MSG("Wrong fileformat");
		return;
	}
    configFile.close();

	QDomElement root = XmlDoc.documentElement();
	if (root.tagName() != "BasicViewerConfig")
	{
		ERROR_MSG("Cannot find \"BasicViewerConfig\"-element");
		return;
	}

    QDomElement e = root.firstChildElement("presets");
    if (!e.isNull()) this->loadPresets(&e);

    e = root.firstChildElement("dicomStrings");
    if (!e.isNull()) this->loadDicomConfig(&e);
}

QList<XipPreset*>* ViewerCore::getPresetList()
{
    return &this->presetList;
}

SoSeparator* ViewerCore::getRootNode()
{
    return this->rootNode_;
}

void ViewerCore::setDicomPath(QString path)
{
    ViewerCore::lastDicomDir_ = path;
}

QString ViewerCore::getDicomPath()
{
    return ViewerCore::lastDicomDir_;
}

QString ViewerCore::getShortDicomPath()
{
    if (ViewerCore::lastDicomDir_.length() > 0)
    {
        QRegExp lastDirName("(\\\\?.*\\\\)*(.*)");
        if (lastDirName.indexIn(ViewerCore::lastDicomDir_) > -1) return lastDirName.cap(2);
    }
    return "------";
}

QList<NameGroupElementPair>* ViewerCore::getDicomElementList()
{
    return &this->dicomElements;
}

void ViewerCore::createPresetMixerForm(QWidget* parent)
{
    this->presetMixerForm = new PresetMixerForm(parent);
}

void ViewerCore::togglePresetMixerForm(bool show)
{
    if (!this->presetMixerForm) return;
    if (show) this->presetMixerForm->show(); else this->presetMixerForm->hide();
}

const PresetMixerForm* ViewerCore::getPresetMixerForm()
{
    return this->presetMixerForm;
}

void ViewerCore::createDicomForm(QWidget* parent, QList<NameGroupElementPair>* _dicomElements)
{
    this->dicomForm = new DicomForm(parent, _dicomElements);
    this->dicomForm->update();
}

void ViewerCore::toggleDicomForm(bool show)
{
    if (!this->dicomForm) return;
    if (show) this->dicomForm->show(); else this->dicomForm->hide();
}

DicomForm* ViewerCore::getDicomForm()
{
    return this->dicomForm;
}

void ViewerCore::addDicomString(QDomElement* _element)
{
    if (!_element || _element->isNull() || _element->tagName() != "dicomString") return;
    this->dicomElements.append(NameGroupElementPair(_element->attribute("name"), _element->attribute("group").toUShort(), _element->attribute("element").toUShort()));
}
