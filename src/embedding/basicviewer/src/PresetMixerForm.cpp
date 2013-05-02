#include "PresetMixerForm.h"

#include <QSet>
#include <QMouseEvent>

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoField.h>

#include "XipPreset.h"


PresetMixerForm::PresetMixerForm(QWidget* parent) : QWidget(parent)
{
	isDraggingWindow_ = false;
	dragPosition_ = QPoint();

    setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    lblTitle->setText(this->windowTitle());

    connect(sliCrossfade, SIGNAL(valueChanged(int)), this, SLOT(sChangedCrossfade(int)));
    connect(presetA, SIGNAL(sigGotPreset()), this, SLOT(sChangedPreset()));
    connect(presetB, SIGNAL(sigGotPreset()), this, SLOT(sChangedPreset()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(sPressedClose()));
}

PresetMixerForm::~PresetMixerForm()
{
    while (!mutualNodes.isEmpty()) delete mutualNodes.takeFirst();
}

void PresetMixerForm::sPressedClose()
{
    emit sigClosed();
    this->close();
}

void PresetMixerForm::sChangedCrossfade(int _value)
{
    float factor = _value * 0.01;

    for(int i = 0; i < mutualNodes.length(); i++)
    {
        mutualNodes.at(i)->setFields(factor);
    }
}

void PresetMixerForm::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		dragPosition_ = event->pos();
		isDraggingWindow_ = true;
		event->accept();
    }
	else
		isDraggingWindow_ = false;
}

void PresetMixerForm::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton && !this->isMaximized() && isDraggingWindow_)
	{
		move(frameGeometry().topLeft() + event->pos() - dragPosition_);
        event->accept();
    }
}

void PresetMixerForm::mouseReleaseEvent(QMouseEvent* event)
{
	isDraggingWindow_ = false;
	if (event->buttons() == Qt::LeftButton)
		event->accept();
}

void PresetMixerForm::sChangedPreset()
{
    while (!mutualNodes.isEmpty()) delete mutualNodes.takeFirst();
    if ((!presetA->getPreset()) || (!presetB->getPreset()))
        return;

    QMap<QString, QMap<QString, FieldTypeValues*> > tmpCompareList;

    // iterate over nodes of preset a
    for(int j = 0; j < presetA->getPreset()->getNodeList()->length(); j++)
    {
        NodePreset* nodePreset = presetA->getPreset()->getNodeList()->at(j);
        SoNode* fldContainer = SoNode::getByName(nodePreset->getName());
        if (!fldContainer) continue;
        if (!tmpCompareList.contains(QString(nodePreset->getName().getString())))
            tmpCompareList.insert(QString(nodePreset->getName().getString()), QMap<QString, FieldTypeValues*>());
        QMap<QString, FieldTypeValues*>* catalogEntry = &tmpCompareList[QString(nodePreset->getName().getString())];
        // iterate over fields of current node of preset a
        for(int i = 0; i < nodePreset->getList()->length(); i++)
        {
            FieldValuePair* fieldValuePair = nodePreset->getList()->at(i);
            if (!catalogEntry->contains(QString(fieldValuePair->getName().getString())))
            {
                SoType tmpType;
                if (fldContainer->getField(fieldValuePair->getName())) tmpType = fldContainer->getField(fieldValuePair->getName())->getTypeId(); else continue;
                FieldTypeValues* fieldTypeValues = new FieldTypeValues(tmpType.getName(), SbString(fieldValuePair->getValue()));

                catalogEntry->insert(QString(fieldValuePair->getName().getString()), fieldTypeValues);
            }
            //else
            //{
            //    // dupe field warning
            //}
        }
    }

    // iterate over nodes of preset b
    for(int j = 0; j < presetB->getPreset()->getNodeList()->length(); j++)
    {
        NodePreset* nodePreset = presetB->getPreset()->getNodeList()->at(j);
        SoNode* fldContainer = SoNode::getByName(nodePreset->getName());
        if (!fldContainer) continue;
        if (!tmpCompareList.contains(QString(nodePreset->getName().getString()))) continue;
        QMap<QString, FieldTypeValues*>* catalogEntry = &tmpCompareList[QString(nodePreset->getName().getString())];
        // iterate over fields of current node of preset b
        for(int i = 0; i < nodePreset->getList()->length(); i++)
        {
            FieldValuePair* fieldValuePair = nodePreset->getList()->at(i);
            if (catalogEntry->contains(QString(fieldValuePair->getName().getString())))
            {
                SoType tmpType;
                if (fldContainer->getField(fieldValuePair->getName())) tmpType = fldContainer->getField(fieldValuePair->getName())->getTypeId(); else continue;
                catalogEntry->value(QString(fieldValuePair->getName().getString()))->checkValueB(tmpType.getName(), fieldValuePair->getValue());
            }
        }
    }

    QMapIterator<QString, QMap<QString, FieldTypeValues*> > itNodes(tmpCompareList);
    while (itNodes.hasNext())
    {
        itNodes.next();
        MutualNode* newMutualNode = new MutualNode(SbName(itNodes.key().toAscii()));
        QMapIterator<QString, FieldTypeValues*> itFields(itNodes.value());
        while (itFields.hasNext())
        {
            itFields.next();
            if (itFields.value()->isValid()) newMutualNode->addFieldValuePair(itFields.value()->getType(), SbName(itFields.key().toAscii()), itFields.value()->getValueA(), itFields.value()->getValueB());
            delete itFields.value();
        }
        if (newMutualNode->getCount()) mutualNodes.append(newMutualNode); else delete newMutualNode;
    }
}