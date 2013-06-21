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
*/#ifndef SOSFENUMEXTENDED_H
#define SOSFENUMEXTENDED_H

#include <Inventor/fields/SoSFEnum.h>
#include <QStringList>

/**
  * A helper class to get access of the private Enum vlaues.
  */
class SoSFEnumExtended : public SoSFEnum
{
public:
	int getNumEnums() const 
	{
		return numEnums;
	}

	QStringList getAllEnums()
	{
		QStringList returnList;
		for (int i=0; i<numEnums; i++) {
			SbName name;
			getEnum(i, name);
			returnList.append(name.getString());
		}
		return returnList;
	}

private:

	int getEnum(const int idx, SbName &name) const
	{
		const  SbName *namePtr = 0;
		findEnumName(enumValues[idx], namePtr);
		name = *namePtr;

		return enumValues[idx];
	}
};

#endif
