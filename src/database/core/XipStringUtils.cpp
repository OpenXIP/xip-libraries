#include <string>
#include <xip/inventor/core/XipStringUtils.h>

SbString XipStrExpandEnv(const char *strIn)
{
	std::string str(strIn);
	int pos = 0;
	int start = 0;
	int end = 0;

	while ((start = static_cast<int>(str.find("$(", pos))) >= 0)
	{
		end = str.find(")", start);
		if (end <= 0) break;

		std::string var = str.substr(start + 2, end - start - 2);
		const char *varValue = ::getenv(var.c_str());
		if (varValue)
		{
			str.erase(start, end - start + 1);
			str.insert(start, varValue);

			pos = start + strlen(varValue);
		}
		else pos = end;
	}

	return SbString(str.c_str());
}