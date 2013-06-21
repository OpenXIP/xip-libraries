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
*/#include "OuterForm.h"
#include "MainForm.h"

#include <QtGui/QApplication>
#include <QSplashScreen>

#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/engines/SoEngine.h>
#include <iostream>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/SoXip.h>
#include <Inventor/SoInventor.h>
#include <Inventor/SoDB.h>

#include "IvFileLoader.h"

#include "QExtLibraryLoaderStandalone.h"
#include "ViewerCore.h"
#include "definitions.h"
#include <QString>

#include <QFile>

QString loadDLL(QString filename)
{
	if (!QExtLibraryLoaderStandalone::loadDLL(filename)) 
		return QExtLibraryLoaderStandalone::getErrorMessage(filename) + "\n";
	return QString();
}

int main(int argc, char* argv[])
{
    QString loadIvFile(SG_FILENAME);

#if _DEBUG
    // parse commandline arguments
    for (int i = 1; i < argc; i++)
    {
        QString tmpArg(argv[i]);
        if ((tmpArg.toLower() == "-iv") && (++i < argc)) loadIvFile = argv[i];
    }
#endif

    QApplication a(argc, argv);

	Q_INIT_RESOURCE(basicviewer);
	QSplashScreen* splash = new QSplashScreen(QPixmap(":/images/splash.png"));
	splash->show();

	SoDB::init();
	SoInteraction::init();
	SoXip::init();

	QString tmpErrors;

#ifdef _DEBUG
	tmpErrors += loadDLL("xipcommond.dll");
	tmpErrors += loadDLL("xipivcored.dll");
	tmpErrors += loadDLL("xipivcoregld.dll");
	tmpErrors += loadDLL("xipivdicomd.dll");
	tmpErrors += loadDLL("xipivoverlayd.dll");
	tmpErrors += loadDLL("xipivrendererd.dll");
#else
	tmpErrors += loadDLL("xipcommon.dll");
	tmpErrors += loadDLL("xipivcore.dll");
	tmpErrors += loadDLL("xipivcoregl.dll");
	tmpErrors += loadDLL("xipivdicom.dll");
	tmpErrors += loadDLL("xipivoverlay.dll");
	tmpErrors += loadDLL("xipivrenderer.dll");
#endif

	if (!tmpErrors.isEmpty()) ERROR_MSG(tmpErrors);

    ViewerCore::get()->loadIvFile(loadIvFile);

	//MainForm* w = new MainForm(rootNode);
    OuterForm* o = new OuterForm();
    //o->setChildWidget(w);
    o->show();

    splash->finish(o);
//	splash->finish(w);
	delete splash;

    return a.exec();
}
