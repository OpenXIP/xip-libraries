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
*/#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
class QStackedWidget;
class QVBoxLayout;
QT_END_NAMESPACE

class SideBarWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QString pageTitle READ pageTitle WRITE setPageTitle STORED false)

public:
    SideBarWidget(QWidget* parent = 0);

    QSize sizeHint() const;

    int count() const;
    int currentIndex() const;
    QWidget* widget(int index);
    QString pageTitle() const;
    
public slots:   
    void addPage(QWidget* page);
    void insertPage(int index, QWidget* page);
    void removePage(int index);
    void setPageTitle(QString const &newTitle);
    void setCurrentIndex(int index);

signals:
    void currentIndexChanged(int index);
    void pageTitleChanged(const QString &title);

private:
    QStackedWidget* stackWidget;
    QComboBox* comboBox;
    QVBoxLayout* layout;
};

#endif
