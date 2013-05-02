#include "IvFileLoader.h"

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
