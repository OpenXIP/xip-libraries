#ifndef SOSFENUMEXTENDED_H
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