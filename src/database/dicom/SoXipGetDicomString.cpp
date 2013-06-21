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
#include <Inventor/fields/SoMFString.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include "SoXipGetDicomString.h"


SO_ENGINE_SOURCE(SoXipGetDicomString);


SoXipGetDicomString::SoXipGetDicomString()
{
	SO_ENGINE_CONSTRUCTOR(SoXipGetDicomString);

	SO_ENGINE_ADD_INPUT(dicom, (0));
	SO_ENGINE_ADD_INPUT(item, (DATASET));
	SO_ENGINE_ADD_INPUT(group, (0));
	SO_ENGINE_ADD_INPUT(element, (0));
	SO_ENGINE_ADD_INPUT(searchIntoSub, (TRUE));

	SO_ENGINE_ADD_OUTPUT(string, SoMFString);

	SO_ENGINE_DEFINE_ENUM_VALUE(itemType, METAINFO);
	SO_ENGINE_DEFINE_ENUM_VALUE(itemType, DATASET);
	SO_ENGINE_SET_SF_ENUM_TYPE(item, itemType);

	dicom.setNum(0);
}


void SoXipGetDicomString::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipGetDicomString, SoEngine, "Engine");
}


SoXipGetDicomString::~SoXipGetDicomString()
{
}


void SoXipGetDicomString::evaluate()
{
	SoMFString results;

	for (int i = 0; i < dicom.getNum(); i++)
	{
		SbString v;

		if (dicom[i])
		{
			if ((item.getValue() == DATASET) && !dicom[i]->getDataset().isNull())
			{
				SbXipDicomItem dataset(dicom[i]->getDataset());
				dataset.findAndGet(SbXipDicomTagKey(group.getValue(), element.getValue()), v, searchIntoSub.getValue());
			}
			else if ((item.getValue() == METAINFO) && !dicom[i]->getMetaInfo().isNull())
			{
				SbXipDicomItem dataset(dicom[i]->getMetaInfo());
				dataset.findAndGet(SbXipDicomTagKey(group.getValue(), element.getValue()), v, searchIntoSub.getValue());
			}
		}

		results.set1Value(results.getNum(), v);
	}

	if (results.getNum() > 0)
		SO_ENGINE_OUTPUT(string, SoMFString, setValues(0, results.getNum(), results.getValues(0)); _eng_out_temp->setNum(results.getNum()))
	else
		SO_ENGINE_OUTPUT(string, SoMFString, setNum(0));
}
