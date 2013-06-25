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
*/

#ifndef PRESETMIXERFORM_H
#define PRESETMIXERFORM_H

#include <QtGui/QWidget>
#include <QList>
#include <QListIterator>
#include <QDebug>
#include "ui_PresetMixerForm.h"

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>

#include "definitions.h"

class PresetMixerForm : public QWidget, private Ui::FormPresetMixer
{
    Q_OBJECT

    struct FieldTypeValues
    {
        FieldTypeValues(SbName _type, SbString _valA)
        {
            valid = false;
            fieldType = _type;
            valueA = _valA;
        }

        SbName getType() { return fieldType; }
        SbString getValueA() { return valueA; }
        SbString getValueB() { return valueB; }

        void checkValueB(SbName _type, SbString _value)
        {
            if (!_type.getLength() || _type != fieldType) return;
            valueB = _value;
            valid = true;
        }

        bool isValid()
        {
            return valid;
        }

    private:
        bool valid;
        SbName fieldType;
        SbString valueA;
        SbString valueB;
    };

    class MutualFieldGeneric
    {
    public:
        MutualFieldGeneric()
        {
        }

        virtual void setField(float factor) { }
    };

    class MutualFieldFloat : public MutualFieldGeneric
    {
    public:
        MutualFieldFloat(SoNode* _fieldContainer, SbName _fieldName, SbString _valA, SbString _valB)
        {
            if (_fieldContainer->getField(_fieldName) && _fieldContainer->getField(_fieldName)->isOfType(SoSFFloat::getClassTypeId())) field = (SoSFFloat*)(_fieldContainer->getField(_fieldName));
            valA = QString(_valA.getString()).toFloat();
            valB = QString(_valB.getString()).toFloat();
        }

        void setField(float factor)
        {
            field->setValue((1 - factor) * valA + factor * valB);
        }

    private:
        SoSFFloat* field;
        float valA;
        float valB;
    };

    class MutualFieldColor : public MutualFieldGeneric
    {
    public:
        MutualFieldColor(SoNode* _fieldContainer, SbName _fieldName, SbString _valA, SbString _valB)
        {
            if (_fieldContainer->getField(_fieldName) && _fieldContainer->getField(_fieldName)->isOfType(SoSFColor::getClassTypeId())) field = (SoSFColor*)(_fieldContainer->getField(_fieldName));
            if (sscanf(_valA.getString(), "%f %f %f", &valA_R, &valA_G, &valA_B) < 3) { valA_R = 0; valA_G = 0; valA_B = 0; }
            if (sscanf(_valB.getString(), "%f %f %f", &valB_R, &valB_G, &valB_B) < 3) { valB_R = 0; valB_G = 0; valB_B = 0; }
        }

        void setField(float factor)
        {
            field->setValue((1 - factor) * valA_R + factor * valB_R, (1 - factor) * valA_G + factor * valB_G, (1 - factor) * valA_B + factor * valB_B);
        }

    private:
        SoSFColor* field;
        float valA_R;
        float valA_G;
        float valA_B;
        float valB_R;
        float valB_G;
        float valB_B;
    };

    class MutualNode
    {
    public:
        MutualNode(SbName _nodeName)
        {
            fldContainer = SoNode::getByName(_nodeName);
        }

        ~MutualNode()
        {
            while (!fieldValues.isEmpty()) delete fieldValues.takeFirst();
        }

        void setFields(float _factor)
        {
            for(int i = 0; i < fieldValues.length(); i++)
            {
                fieldValues.at(i)->setField(_factor);
            }
        }

        void addFieldValuePair(SbName typeName, SbName _fieldName, SbString _valA, SbString _valB)
        {
            if (!fldContainer) return;
            if (typeName == "SFFloat") this->fieldValues.append(new MutualFieldFloat(fldContainer, _fieldName, _valA, _valB));
            else if (typeName == "SFColor") this->fieldValues.append(new MutualFieldColor(fldContainer, _fieldName, _valA, _valB));
        }

        int getCount()
        {
            return fieldValues.length();
        }

    private:
        SbString nodeName;
        SoNode* fldContainer;
        QList<MutualFieldGeneric*> fieldValues;
    };

public:
    PresetMixerForm(QWidget* parent = 0);
    ~PresetMixerForm();

    QList<MutualNode*> mutualNodes;

private:
    bool isDraggingWindow_;
    QPoint dragPosition_;

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void sChangedCrossfade(int _value);
    void sChangedPreset();
    void sPressedClose();

signals:
    void sigClosed();
};

#endif
