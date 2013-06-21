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
#include "SoXipLoadDicom.h"
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoError.h> 
#include <dcmtk/dcmdata/dctk.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/core/XipStringUtils.h>


SO_ENGINE_SOURCE(SoXipLoadDicom);


void SoXipLoadDicom::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipLoadDicom, SoEngine, "Engine");
}


SoXipLoadDicom::SoXipLoadDicom()
{
	SO_ENGINE_CONSTRUCTOR(SoXipLoadDicom);

	SO_ENGINE_ADD_INPUT(name, (""));
	SO_ENGINE_ADD_OUTPUT(dicom, SoXipMFDataDicom);
}


SoXipLoadDicom::~SoXipLoadDicom()
{
	#if defined(COIN_DLL) || defined (COIN_NO_DLL)
	// SGI automatically triggers evaluate after loading but COIN doesn't
	SbXipDirtyFieldList::remove(&name);
	#endif

	unloadAll();
}


void SoXipLoadDicom::unloadAll()
{
	mLoadedData.setNum(0);
}


void SoXipLoadDicom::evaluate()
{
	unloadAll();
    
    SoMFString nameLocal;
    for (int i = 0; i < name.getNum(); i++)
	{
#ifdef WIN32
    //assuming everything is done using the bad backslashes... so we convert all forward slashes to those
    nameLocal.set1Value(i, XipReplaceChar(name[i].getString(), '/', '\\'));
#else //UNIX
    //assuming the other way around since we need forward slashes now...
    nameLocal.set1Value(i, XipReplaceChar(name[i].getString(), '\\', '/'));
#endif //WIN32
    }

	// "interpret" may replace folders with files in the folder or DICOMDIR with images
	SoMFString interpreted;
	SoXipDataDicom::interpret(nameLocal, interpreted);


	for (int i = 0; i < interpreted.getNum(); i++)
	{
		SoXipDataDicom* dicomData = new SoXipDataDicom;
		if (dicomData)
		{
			if (dicomData->open(interpreted[i].getString()))
			{
				mLoadedData.set1Value(mLoadedData.getNum(), dicomData);
			}
		}
	}

	SO_ENGINE_OUTPUT( dicom, SoXipMFDataDicom, copyFrom(mLoadedData) );
}


SbBool SoXipLoadDicom::readInstance(SoInput * in, unsigned short flags)
{
	#if defined(COIN_DLL) || defined (COIN_NO_DLL)
	// SGI automatically triggers evaluate after loading but COIN doesn't
	SbXipDirtyFieldList::append(&name);
	#endif

	return SoEngine::readInstance(in, flags);
}
