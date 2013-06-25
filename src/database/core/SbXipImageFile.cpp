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

#include <xip/inventor/core/SbXipImageFile.h>
#include <xip/inventor/core/XipInventorUtils.h>
#include <xip/inventor/core/XipStringUtils.h>

SbBool 
readImage( const char* file, unsigned int offset, SbXipImage& image )
{
#ifdef WIN32
    //assuming everything is done using the bad backslashes... so we convert all forward slashes to those
    const char * fileLocal = XipReplaceChar(file, '/', '\\').getString();
#else //UNIX
    //assuming the other way around since we need forward slashes now...
    const char * fileLocal = XipReplaceChar(file, '\\', '/').getString();
#endif //WIN32
	
    int r = 0;

	void* imageBufferPtr = image.refBufferPtr();
	if( imageBufferPtr )
	{
		SbString path = XipStrExpandEnv( fileLocal );
		FILE* fs = fopen( path.getString(), "rb" );
		if (!fs) 
			return FALSE;

		fseek( fs, offset, SEEK_SET );
		r = fread( imageBufferPtr, image.bufferSize(), 1, fs );

		fclose( fs );
	}
	image.unrefBufferPtr();

	return (r == 1);
}

SbBool 
writeImage( const char* file, unsigned int offset, SbXipImage& image )
{
#ifdef WIN32
    //assuming everything is done using the bad backslashes... so we convert all forward slashes to those
    const char * fileLocal = XipReplaceChar(file, '/', '\\').getString();
#else //UNIX
    //assuming the other way around since we need forward slashes now...
    const char * fileLocal = XipReplaceChar(file, '\\', '/').getString();
#endif //WIN32
    
	int r = 0;

	void* imageBufferPtr = image.refBufferPtr();
	if( imageBufferPtr )
	{
		SbString path = XipStrExpandEnv( fileLocal );
		FILE* fs = fopen( path.getString(), "wb" );
		if (!fs) 
			return FALSE;

		fseek( fs, offset, SEEK_SET );
		r = fwrite(imageBufferPtr, 1, image.bufferSize(), fs );

		fclose( fs );
	}
	image.unrefBufferPtr();

	return (r == image.bufferSize());
}


