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

/*!
 * \file SbVariant.cpp
 * \brief Implementation of the SbVariant type
 * \author Francois Huguet
 */

#include <xip/inventor/core/SbVariant.h>
#ifdef linux
	#include <string.h>
	#include <inttypes.h>
#endif

SbVariant::SbVariant()
{
}

SbVariant::~SbVariant()
{
}

void
SbVariant::setField( SbString buffer )
{
	mField = buffer;
}

const SbString&
SbVariant::getField() const
{
    return mField;
}


void
SbVariant::setFormat( const char* format )
{
	mFormat = SbString(format);
	setTypes(format);
}

const SbString&
SbVariant::getFormat() const
{
    return mFormat;
}

void
SbVariant::setTypes( const char* format )
{
	char ** types;
	int length = 256;
	types = split(format,&nbTypes);
	mTypes = (char **) malloc(length * sizeof(char *));
	for (int i=0; i < nbTypes; i++)
	{
		mTypes[i]=(char *) malloc(length * sizeof(char ));
		#ifdef WIN32
		strcpy_s(mTypes[i],length,types[i]);
		#else
		// #ifdef linux
			strncpy(mTypes[i],types[i],length);
		// #endif
		#endif
	}
}

char *
SbVariant::getType( int index )
{
	return mTypes[index];
}

SbVariant::variantType 
SbVariant::getVariantType( int index )
{
	char * type = getType(index);
			
	if (!strcmp(type,"double"))
	{
		return VARIANT_DOUBLE;
	}
	else if (!strcmp(type,"float"))
	{
		return VARIANT_FLOAT;
	}
	else if (!strcmp(type,"short"))
	{
		return VARIANT_SHORT;
	}
	else if (!strcmp(type,"int"))
	{
		return VARIANT_INT;
	}
	else if (!strcmp(type,"long"))
	{
		return VARIANT_INT;
	}
	else if (!strcmp(type,"unsigned short"))
	{
		return VARIANT_U_SHORT;
	}
	else if (!strcmp(type,"unsigned int"))
	{
		return VARIANT_U_INT;
	}
	else if (!strcmp(type,"char"))
	{
		return VARIANT_CHAR;
	}
	else if (!strcmp(type,"char*"))
	{
		return VARIANT_STRING;
	}
	return DEFAULT;
}

int 
SbVariant::getNbTypes()
{
	return nbTypes;
}

char ** 
SbVariant::split( const char* string, int *nb )
{
	int i=0;
	char seps[] = " ";
	char* pch;
	char *next_token;

	// Get the length of the string and allocate memory to store types
	int length = 256;//strlen(string);
	//if (length < 1) length = 256;
	char** members;
	members = (char **) malloc(length * sizeof(char *));
	
	char *test = new char[length+1];
	#ifdef WIN32
	strcpy_s(test,length+1,string);
	pch = strtok_s(test,seps,&next_token);
	#else
	// #ifdef linux
		strncpy(test,string,length+1);
		pch = strtok_r(test,seps,&next_token);
	// #endif
	#endif

	if (pch !=  NULL ) 
	{
		members[i]=(char *) malloc(length * sizeof(char ));
		#ifdef WIN32
		strcpy_s(members[i],length,pch);
		#else
		// #ifdef linux
			strncpy(members[i],pch,length);
		// #endif
		#endif
	}

	while (pch != NULL)
	{
		#ifdef WIN32
		pch = strtok_s(NULL,seps,&next_token);
		#else
		// #ifdef linux
			pch = strtok_r(NULL,seps,&next_token);
		// #endif
		#endif
		
		i++;

		if (pch !=  NULL ) 
		{
			members[i]=(char *) malloc(length * sizeof(char ));
			members[i]=new char[length+1];
			#ifdef WIN32
			strcpy_s(members[i],length,pch);
			#else
			// #ifdef linux
				strncpy(members[i],pch,length);
			// #endif
			#endif
		}		
	}
	*nb = i;

	return members;
}


bool 
SbVariant::operator ==( const SbVariant& rhs ) const
{
	return true;
}
