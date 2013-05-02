#ifndef XIPPRESET_H
#define XIPPRESET_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoField.h>

#include <QDomElement>
#include <QString>
#include <QWidget>
#include <QDebug>

#include "definitions.h"

class FieldValuePair
{
public:
    friend QDataStream& operator << (QDataStream& _ds, const FieldValuePair& fieldValuePair)
    {
        _ds << QString(fieldValuePair.fieldName_.getString()) << QString(fieldValuePair.fieldValue_.getString());
        return _ds;
    }

    FieldValuePair(QDataStream& _ds)
    {
        QString tmpName, tmpValue;
        _ds >> tmpName >> tmpValue;
        fieldName_ = tmpName.toAscii();
        fieldValue_ = tmpValue.toAscii();
    }

    FieldValuePair(QString _fieldName, QString _fieldValue)
    {
        fieldName_ = _fieldName.toAscii();
        fieldValue_ = _fieldValue.toAscii();
    }

    SbString getName()
    {
        return fieldName_;
    }

    const char* getValue()
    {
        return fieldValue_.getString();
    }

private:
    SbString fieldName_;
    SbString fieldValue_;
};

class NodePreset
{
public:
    friend QDataStream& operator << (QDataStream& _ds, const NodePreset& nodePreset)
    {
        _ds << QString(nodePreset.getName().getString()) << nodePreset.getList()->length();

        for(int i = 0; i < nodePreset.getList()->length(); i++)
        {
            _ds << *nodePreset.getList()->at(i);
        }
        return _ds;
    }

    NodePreset(QDataStream& _ds)
    {
        int fieldValueListCount = 0;
        QString tmpNodeName;

        _ds >> tmpNodeName >> fieldValueListCount;
        nodeName_ = tmpNodeName.toAscii();
        for (int i = 0; i < fieldValueListCount; i++)
        {
            fieldValueList.append(new FieldValuePair(_ds));
        }
    }

    NodePreset(QDomElement* _element)
    {
        nodeName_ = _element->attribute("name").toAscii();
        for(QDomElement f = _element->firstChildElement("field"); !f.isNull(); f = f.nextSiblingElement("field"))
        {
            this->AddFieldValuePair(f.attribute("name"), f.attribute("value"));
        }
    }

    ~NodePreset()
    {
        while (!fieldValueList.isEmpty()) delete fieldValueList.takeFirst();
    }

    void AddFieldValuePair(QString _fieldName, QString _fieldValue)
    {
        fieldValueList.append(new FieldValuePair(_fieldName, _fieldValue));
    }

    SbString getName() const
    {
        return nodeName_;
    }

    const QList<FieldValuePair*>* getList() const
    {
        return &fieldValueList;
    }

private:
    SbString nodeName_;
    QList<FieldValuePair*> fieldValueList;
};

class XipPreset
{
public:
    XipPreset(QDomElement* _element)
    {
        if (_element && !_element->isNull() && _element->tagName() == "preset")
        {
            this->presetName_ = _element->attribute("name");
            this->grpBoxName_ = _element->attribute("groupBox");

            for(QDomElement n = _element->firstChildElement("node"); !n.isNull(); n = n.nextSiblingElement("node"))
            {
                affectedNodeList_.append(new NodePreset(&n));
            }
        }
    }

    XipPreset(QByteArray* _ba)
    {
        if (_ba)
        {
            int affectedNodeListCount = 0;
            QDataStream dataStream(_ba, QIODevice::ReadOnly);
            
            dataStream >> presetName_ >> grpBoxName_ >> affectedNodeListCount;
            for (int i = 0; i < affectedNodeListCount; i++)
            {
                affectedNodeList_.append(new NodePreset(dataStream));
            }
        }
    }

    ~XipPreset()
    {
        while (!affectedNodeList_.isEmpty()) delete affectedNodeList_.takeFirst();
    }

    QString getName()
    {
        return QString(presetName_);
    }

    QString getGroupBoxName()
    {
        return grpBoxName_;
    }

    void setPreset()
    {
        SoNode* fldContainer;
        SoField* tmpField;

        for(int i = 0; i < affectedNodeList_.length(); i++)
        {
            if (!(fldContainer = SoNode::getByName(affectedNodeList_[i]->getName())))
            {
                ERROR_MSG("Cannot find node \"" + QString(affectedNodeList_[i]->getName().getString()) + "\"");
                continue;
            }
            
            for (int j = 0; j < affectedNodeList_[i]->getList()->length(); j++)
            {
                if (!(tmpField = fldContainer->getField(affectedNodeList_[i]->getList()->at(j)->getName())))
                {
                    ERROR_MSG("Cannot find field \"" + QString(affectedNodeList_[i]->getList()->at(j)->getName().getString()) + "\" in node \"" + QString(affectedNodeList_[i]->getName().getString()) + "\"");
                    continue;
                }
                if (!tmpField->set(affectedNodeList_[i]->getList()->at(j)->getValue()))
                    ERROR_MSG("Failed to set field \"" + QString(affectedNodeList_[i]->getList()->at(j)->getName().getString()) + "\"'s value to \"" + QString(affectedNodeList_[i]->getList()->at(j)->getValue()) + "\"");
                tmpField->touch();
            }
        }
    }

    const QList<NodePreset*>* getNodeList()
    {
        return &affectedNodeList_;
    }

    QByteArray toByteArray()
    {
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << presetName_ << grpBoxName_ << affectedNodeList_.length();
        for(int i = 0; i < affectedNodeList_.length(); i++)
        {
            dataStream << *affectedNodeList_.at(i);
        }
        return itemData;
    }

private:
    QString presetName_;
    QString grpBoxName_;
    QList<NodePreset*> affectedNodeList_;
};

#endif