#ifndef LOADIVFILE_H
#define LOADIVFILE_H

#include <QString>

class SoNode;
class SoSeparator;

class IvFileLoader
{
public:
	IvFileLoader(QString filename);
	~IvFileLoader();

	SoNode* result;
};

#endif // LOADIVFILE_H