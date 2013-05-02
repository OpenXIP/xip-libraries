#ifndef DEFINITIONS_H
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