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
*/#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QDebug>
#include <QMessageBox>

#define SG_FILENAME ":/images/mpr.iv"
#define OUTPUT(c) qDebug() << c
#define ERROR_MSG(c) QMessageBox(QMessageBox::Warning, "Error", c, QMessageBox::Ok).exec()
#define SET_WAITCURSOR() QApplication::setOverrideCursor(Qt::WaitCursor)
#define SET_DEFAULTCURSOR() QApplication::restoreOverrideCursor()
#define INFO(c) QMessageBox(QMessageBox::Information, "Error", c, QMessageBox::Ok).exec()

#define CONNECTFIELD(fldContainer, fieldName, varName, typeName) if (fldContainer->getField(fieldName) && fldContainer->getField(fieldName)->isOfType(typeName::getClassTypeId())) varName = (typeName*)(fldContainer->getField(fieldName)); else qWarning() << "Cannot connect field" << fieldName

static bool g_bUseDirectoryPicker = false;

struct NameGroupElementPair
{
    NameGroupElementPair(QString _name, unsigned short _group, unsigned short _element)
    {
        this->name = _name;
        this->group = _group;
        this->element = _element;
    }

    const QString getName() const
    {
        return this->name;
    }

    const unsigned short getGroup() const
    {
        return this->group;
    }

    const unsigned short getElement() const
    {
        return this->element;
    }

private:
    QString name;
    unsigned short group;
    unsigned short element;
};

#endif // DEFINITIONS_H
