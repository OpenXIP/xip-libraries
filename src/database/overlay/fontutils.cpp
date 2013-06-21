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
// code from: http://www.codeproject.com/gdi/xfont.asp
// author: Hans Dietrich

#if defined(WINDOWS) || defined(_WIN32)

#include <xip/system/standard.h>
#include <stdio.h>


///////////////////////////////////////////////////////////////////////////////
//
// GetNextNameValue()
//
// Purpose:     Get first/next name/value pair from registry
//
// Parameters:  key       - handle to open key, or predefined key
//              pszSubkey - subkey name
//              pszName   - pointer to buffer that receives the value string
//              pszData   - pointer to buffer that receives the data string
//
// Returns:     LONG - return code from registry function; ERROR_SUCCESS = success
//
// Notes:       If pszSubkey, pszName, and pszData are all NULL, then the open
//              handle will be closed.
//
//              The first time GetNextNameValue is called, pszSubkey should be
//              specified.  On subsequent calls, pszSubkey should be NULL or
//              an empty string.
//
static LONG GetNextNameValue(HKEY key, LPCTSTR pszSubkey, LPTSTR pszName, LPTSTR pszData)
{
	static HKEY hkey = NULL;	// registry handle, kept open between calls
	static DWORD dwIndex = 0;	// count of values returned
	LONG retval;

	// if all parameters are NULL then close key
	if (pszSubkey == NULL && pszName == NULL && pszData == NULL)
	{
		if (hkey)
			RegCloseKey(hkey);
		hkey = NULL;
		return ERROR_SUCCESS;
	}

	// if subkey is specified then open key (first time)
	if (pszSubkey && pszSubkey[0] != 0)
	{
		retval = RegOpenKeyEx(key, pszSubkey, 0, KEY_READ, &hkey);
		if (retval != ERROR_SUCCESS)
		{
			return retval;
		}
		dwIndex = 0;
	}
	else
	{
		dwIndex++;
	}

	*pszName = 0;
	*pszData = 0;

	TCHAR szValueName[MAX_PATH];
	DWORD dwValueNameSize = sizeof(szValueName)-1;
	BYTE szValueData[MAX_PATH];
	DWORD dwValueDataSize = sizeof(szValueData)-1;
	DWORD dwType = 0;

	retval = RegEnumValue(hkey, dwIndex, szValueName, &dwValueNameSize, NULL,
		&dwType, szValueData, &dwValueDataSize);
	if (retval == ERROR_SUCCESS)
	{
		lstrcpy(pszName, (LPTSTR)szValueName);
		lstrcpy(pszData, (LPTSTR)szValueData);
	}

	return retval;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFontFile()
//
// Purpose:     Find the name of font file from the font name
//
// Parameters:  lpszFontName     - name of font
//              lpszDisplayName  - pointer to buffer where font display name
//                                 will be copied
//              nDisplayNameSize - size of display name buffer in TCHARs
//              lpszFontFile     - pointer to buffer where font file name
//                                 will be copied
//              nFontFileSize    - size of font file buffer in TCHARs
//
// Returns:     BOOL - TRUE = success
//
// Notes:       This is *not* a foolproof method for finding the name of a
//              font file. If a font has been installed in a normal manner,
//              and if it is in the Windows "Font" directory, then this method
//              will probably work. It will probably work for most screen
//              fonts and TrueType fonts. However, this method might not work
//              for fonts that are created or installed dynamically, or that
//              are specific to a particular device, or that are not installed
//              into the font directory.
//
int GetFontFile(const char* mbFontName,
				 char* lpszDisplayName,
				 int nDisplayNameSize,
				 char* lpszFontFile,
				 int nFontFileSize)
{
	// convert to UNICODE if needed
	#ifdef _UNICODE
	TCHAR lpszFontName[2 * MAX_PATH];
	wsprintf(lpszFontName, L"%hs", mbFontName);
	#else
	LPCTSTR lpszFontName = mbFontName;
	#endif
	
	if (!lpszFontName || lpszFontName[0] == 0)
		return FALSE;

	if (!lpszDisplayName)
		return FALSE;

	if (!lpszFontFile)
		return FALSE;

	lpszDisplayName[0] = '\0';
	lpszFontFile[0] = '\0';

	TCHAR szName[2 * MAX_PATH];
	TCHAR szData[2 * MAX_PATH];

	OSVERSIONINFO osinfo;
	osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	if (!GetVersionEx(&osinfo))
		return FALSE;


	LPCTSTR szFontPath = 0;

	if (osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
		szFontPath = "Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	else
		szFontPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Fonts";

	BOOL bResult = FALSE;

	while (GetNextNameValue(HKEY_LOCAL_MACHINE, szFontPath, szName, szData) == ERROR_SUCCESS)
	{
		szName[strlen(lpszFontName)] = 0;
		if (lstrcmpi(lpszFontName, szName) == 0)
		{
			char systemDir[MAX_PATH];
			::GetWindowsDirectoryA(systemDir, MAX_PATH);

			#ifdef _UNICODE
			_snprintf(lpszDisplayName, nDisplayNameSize-1, "%S", szName);
			_snprintf(lpszFontFile, nFontFileSize-1, "%s\\Fonts\\%S", systemDir, szData);
			#else
			
			strncpy(lpszDisplayName, szName, nDisplayNameSize-1);
			//strncpy(lpszFontFile, szData, nFontFileSize-1);

			//::GetWindowsDirectory(systemDir, MAX_PATH);
			_snprintf(lpszFontFile, nFontFileSize-1, "%s\\Fonts\\%s", systemDir, szData);
            #endif
			bResult = TRUE;
			break;
		}

		szFontPath = 0;	// this will get next value, same key
	}

	GetNextNameValue(HKEY_LOCAL_MACHINE, NULL, NULL, NULL);	// close the registry key

	return bResult;
}


#else


#include <stdio.h>
#ifndef WIN32
//#include <regex.h>
#include <string>
#define MAX_PATH 216
#include <sys/stat.h> 
//#include <iostream>
//#include <cerrno>
#endif // WIN32

int GetFontFile(const char* lpszFontName, char* lpszDisplayName, int nDisplayNameSize, char* lpszFontFile, int nFontFileSize)
{
#ifndef WIN32
    /*
#ifdef __APPLE__
    char FONT_FILE[MAX_PATH] = "/usr/X11/lib/X11/fonts/TTF/";
#else //linux
    char FONT_FILE[MAX_PATH] = "/usr/share/fonts/X11/"; //"/usr/share/X11/fonts/TTF/";
#endif //__APPLE__
    regex_t reg;
	if (regcomp(&reg, FONT_FILE, REG_EXTENDED | REG_NOSUB))
	{
		return -1;
	}
	if(!regexec(&reg, lpszFontName, 0, NULL, 0))
	{
		//check whether font file is present or not
        strcat(FONT_FILE,lpszFontName);
	}
	else
	{
		//if requires font file not presend load any font file
		strcat(FONT_FILE,"luximb.ttf");
	}
    */

#ifdef __APPLE__
    const char * fontDir_0 = "/Library/Fonts";              //mac
    const char * fontDir_1 = "/usr/X11/lib/X11/fonts/TTF";  //mac
#else // __APPLE__
    const char * fontDir_0 = "/usr/share/fonts/truetype/freefont";      //ubuntu
    const char * fontDir_1 = "/usr/share/fonts/truetype/msttcorefonts"; //ubuntu
#endif // __APPLE__
    
    //may need to improve this, if we want to check more directories...
    const char * FONT_DIRS[2] = {fontDir_0, fontDir_1};
    
    //char FONT_FILE[MAX_PATH];
    std::string FONT_FILE = "/";
    FONT_FILE.append(lpszFontName);
    
    if (FONT_FILE.find(".") == std::string::npos)
    {
        //extension not yet appended
        FONT_FILE.append(".ttf");
    }
    
    int foundStat = -1;
    //file info struct
    struct stat stFileInfo;
    
    std::string fullPath;
    
    for (int i=0; i<2 && foundStat==-1; i++)
    {
        //check if directory exists
        foundStat = stat(FONT_DIRS[i], &stFileInfo);
        if (foundStat == 0)
        {
            fullPath = std::string(FONT_DIRS[i]).append(FONT_FILE.c_str());

            //check if the file is in the directory, too
            foundStat = stat(fullPath.c_str(), &stFileInfo);
            if (foundStat == 0)
            {
                continue;
            }
            //std::cout << "Could not find file: " << fullPath << " [error]: " << std::strerror(errno) << std::endl;
            foundStat = -1;
        }

    }
    
    FONT_FILE = fullPath;
    
    if (foundStat == -1)
    {
#ifdef __APPLE__
        FONT_FILE = std::string("/Library/Fonts/Arial.ttf");
#else // __APPLE__
        FONT_FILE = std::string("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
#endif // __APPLE__
    }
    
	
#endif // WIN32
	if(lpszFontFile)
		sprintf(lpszFontFile,"%s\0", FONT_FILE.c_str());
	else
		return 0;

	return 1;
}

#endif //END



