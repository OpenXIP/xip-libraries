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

//replaces all occurances of "searchChar" in "str" with "replChar"
SbString XipReplaceChar(const char * str, const char & searchChar, const char & replChar)
{
    std::string tmpStr(str);
    for (unsigned int i=0; i<tmpStr.size(); i++)
    {
        if ( tmpStr.at(i) == searchChar )
        {
            tmpStr[i] = replChar;
        }
    }
    return SbString(tmpStr.c_str());
}

