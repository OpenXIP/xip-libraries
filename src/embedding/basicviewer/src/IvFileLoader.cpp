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
*/#include "IvFileLoader.h"

#include <Inventor/SoInput.h>
#include <QFile>

#include "definitions.h"

IvFileLoader::IvFileLoader(QString _fileName)
{
	SoInput loadModel;
	result = 0;

    QFile file(_fileName.toAscii());
    if (!file.exists()) { ERROR_MSG("File \"" + _fileName.toAscii() + "\" doesn't exist."); return; }
    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    loadModel.setBuffer(ba.data_ptr()->data, ba.size());
    if (!SoDB::read(&loadModel, this->result)) ERROR_MSG("Error reading model by database!");
}

IvFileLoader::~IvFileLoader() { }
