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

#include <xip/inventor/core/SoSFVariant.h>

//////////////////////////////////////////////////////////////////////////////
//
// SoSFVariant class
//
//////////////////////////////////////////////////////////////////////////////

// Use standard definitions of all basic methods
SO_SFIELD_SOURCE(SoSFVariant, SbVariant, const SbVariant&);


void
SoSFVariant::initClass()
{
  SO_SFIELD_INIT_CLASS(SoSFVariant, SoSField);
}

void
SoSFVariant::setValue()
{
	value = SbVariant();
}

void
SoSFVariant::setFormat(const char * format)
{
	value.setFormat(format);
}

// Description:
//    Reads value from file. Returns FALSE on error.

SbBool
SoSFVariant::readValue(SoInput *in)
{
	SoOutput output;
	output.setHeaderString(" ");
	output.setBuffer(malloc(512), 512, realloc);
	output.setBinary(FALSE);

	int N = value.getNbTypes(); 

	for (int i = 0; i < N; i++)
	{
		char valueChar;
		SbString valueString;
		int valueInt;
		unsigned int valueUInt;
		short valueShort;
		unsigned short valueUShort;
		float valueFloat;
		double valueDouble;

		switch (value.getVariantType(i))
		{
		case SbVariant::VARIANT_CHAR:
			{
				if ( !in->read(valueChar) )
					return FALSE;
				output.write(valueChar);
			} break;
		case SbVariant::VARIANT_STRING:
			{
				if ( !in->read(valueString) )
					return FALSE;
				output.write(valueString);
			} break;
		case SbVariant::VARIANT_INT:
			{
				if ( !in->read(valueInt) )
					return FALSE;
				output.write(valueInt);
			} break;
		case SbVariant::VARIANT_U_INT:
			{
				if ( !in->read(valueUInt) )
					return FALSE;
				output.write(valueInt);
			} break;
		case SbVariant::VARIANT_SHORT:
			{
				if ( !in->read(valueShort) )
					return FALSE;
				output.write(valueShort);
			} break;
		case SbVariant::VARIANT_U_SHORT:
			{
				if ( !in->read(valueUShort) )
					return FALSE;
				output.write(valueShort);
			} break;
		case SbVariant::VARIANT_FLOAT:
			{
				if ( !in->read(valueFloat) )
					return FALSE;
				output.write(valueFloat);
			} break;
		case SbVariant::VARIANT_DOUBLE:
			{
				if ( !in->read(valueDouble) )
					return FALSE;
				output.write(valueDouble);
			} break;
		case SbVariant::DEFAULT:
			return FALSE;
			break;
		}

		if (i <= (N - 1))
			output.write(' ');
	}

	// terminate the string in the output buffer
	output.write('\0');

	void* buffer = 0;
	size_t bufferSize = 0;
	if (output.getBuffer(buffer, bufferSize))
	{
		if (buffer)
		{
			// skip header (space + 2 new lines)
			value.setField( SbString(((const char*) buffer) + 3) );
			free(buffer);
		}
	}
 
	return TRUE;
}


// Description:
//    Writes value of field to file.

void
SoSFVariant::writeValue(SoOutput *out) const
{
	out->write(value.getField().getString());
}
