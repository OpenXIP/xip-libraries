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
*/#ifndef VIEWERCORE_H
#define VIEWERCORE_H

#include <QList>

#include "definitions.h"

class QWidget;
class QDomElement;
class QString;
class SoSeparator;
class SbString;
class XipPreset;
class PresetMixerForm;
class DicomForm;

class ViewerCore
{
public:
    static ViewerCore* get();

    void loadIvFile(QString fileName);
    void loadConfigFile(QString fileName);
    QList<XipPreset*>* getPresetList();
    SoSeparator* getRootNode();

    void setDicomPath(QString path);
    QString getDicomPath();
    QString getShortDicomPath();

    void createPresetMixerForm(QWidget* parent = 0);
    void togglePresetMixerForm(bool show);
    const PresetMixerForm* getPresetMixerForm();

    void createDicomForm(QWidget* parent = 0, QList<NameGroupElementPair>* _dicomElements = 0);
    void toggleDicomForm(bool show);
    DicomForm* getDicomForm();

    void addDicomString(QDomElement* _element);
    QList<NameGroupElementPair>* getDicomElementList();

private:
    ViewerCore();
    ~ViewerCore();

    void loadPresets(QDomElement* _element);
    void loadDicomConfig(QDomElement* _element);

    static ViewerCore* ref;
    static QString lastDicomDir_;
    QList<XipPreset*> presetList;
    static PresetMixerForm* presetMixerForm;
    static DicomForm* dicomForm;

    SoSeparator* rootNode_;

    QList<NameGroupElementPair> dicomElements;
};

#endif
