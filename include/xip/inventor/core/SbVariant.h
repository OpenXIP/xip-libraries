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
 * \file SbVariant.h
 * \brief Declaration of the SbVariant type
 * \author Francois Huguet
 */

#ifndef SB_VARIANT_H_
#define SB_VARIANT_H_

#include <Inventor/SbString.h>
#include <string>
#include <xip/inventor/core/xipivcore.h>
using namespace std;

/*!
 * \brief
 * SbVariant class description.
 *
 * A Variant type is a type that can support several distinct types.
 * You need to precise in the constructor of your class the format of your 
 * multi-types field.
 *
 */
class XIPIVCORE_API SbVariant
{

public:

	/// Variant type list: all supported types.
	enum variantType
	{
		VARIANT_CHAR,
		VARIANT_STRING,
		VARIANT_INT,
		VARIANT_U_INT,
		VARIANT_SHORT,
		VARIANT_U_SHORT,
		VARIANT_FLOAT,
		VARIANT_DOUBLE,
		DEFAULT
	};

	/// Constructor
	SbVariant();

	/// Destructor
	~SbVariant();

	/// Egual operator (not implemented)
	bool operator ==( const SbVariant&  ) const;

	/// Keep track of the value of the field
	void setField( SbString buffer );
	const SbString& getField() const;

	/// Keep the format of the expected field
	void setFormat( const char*  );
	const SbString& getFormat() const;

	/// Method to parse the format string
	char ** split( const char* ,int * );

	/// Keep the various types to match the entered values
	void setTypes( const char* );
	char * getType( int );
	variantType getVariantType( int );
	int getNbTypes();


protected:
	SbString	mField;
	SbString	mFormat;
	char **		mTypes;
	int nbTypes;

};

#endif // SB_VARIANT_H_
