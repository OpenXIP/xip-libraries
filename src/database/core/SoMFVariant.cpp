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
 * \file SoMFVariant.cpp
 * \brief Implementation of the SoMFVariant field
 * \author Francois Huguet
 */

#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/core/SoMFVariant.h>

#define OPEN_BRACE_CHAR		'['
#define CLOSE_BRACE_CHAR	']'
#define VALUE_SEPARATOR_CHAR	','
#define VALUE_CHUNK_SIZE	32

//////////////////////////////////////////////////////////////////////////////
//
// SoMFVariant class
//
//////////////////////////////////////////////////////////////////////////////

// Use standard definitions of all basic methods
SO_MFIELD_SOURCE(SoMFVariant, SbVariant, const SbVariant &);

void
SoMFVariant::initClass()
{
  SO_MFIELD_INIT_CLASS(SoMFVariant, SoMField);
}


void
SoMFVariant::setValue()
{
	makeRoom(1);
	values[0] = SbVariant();
}

void
SoMFVariant::setFormat(const char * format)
{
	values[0].setFormat(format);
}


SbBool
SoMFVariant::read1Value(SoInput *in, int index)
{
	SoOutput output;
	output.setHeaderString(" ");
	output.setBuffer(malloc(512), 512, realloc);
	output.setBinary(FALSE);

	int N = values[0].getNbTypes(); 

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

		switch (values[0].getVariantType(i))
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
			values[index].setField( SbString(((const char*) buffer) + 3) );
			free(buffer);
		}
	}
 
	return TRUE;

}

SbBool
SoMFVariant::readValue(SoInput *in)
{
	char	c;
	int	curIndex = 0;

	// Check for multiple field values
	if (in->read(c) && c == OPEN_BRACE_CHAR) 
	{
	    // Check for no values: just an open and close brace
	    if (in->read(c) && c == CLOSE_BRACE_CHAR)
		;					// Do nothing now

	    else 
		{
			in->putBack(c);

			while (TRUE) 
			{
		    // Make some room at end if necessary
				if (curIndex >= getNum())
					makeRoom(getNum() + VALUE_CHUNK_SIZE);
				
				if (! read1Value(in, curIndex++))
					break;

				if (! in->read(c))
					break;

				if (c == VALUE_SEPARATOR_CHAR) 
				{
					// See if this is a trailing separator (right before 
					// the closing brace). This is legal, but ignored.
					if (in->read(c)) 
					{
						if (c == CLOSE_BRACE_CHAR)
							break;
						else
							in->putBack(c);
					}
				}

				else if (c == CLOSE_BRACE_CHAR)
					break;

			}
			// If extra space left over, nuke it
			if (curIndex < getNum())
				makeRoom(curIndex);
	    }
		if (curIndex < getNum())
			makeRoom(curIndex);
	}
	else 
	{
	    // Try reading 1 value
	    in->putBack(c);
	    makeRoom(1);
	    if (! read1Value(in, 0))
			return FALSE;
	}
    
    return TRUE;
}

void
SoMFVariant::write1Value(SoOutput *out, int index) const
{
	out->write(values[index].getField().getString());
}

void
SoMFVariant::writeValue(SoOutput *out) const
{
    int	i=0;

	if (this->num == 1)
	{
	    write1Value(out, 0);
	}
	else 
	{
	    int	numOnLine = 0, maxOnLine = 6;

	    out->write(OPEN_BRACE_CHAR);
	    out->write(' ');

	    out->incrementIndent(4);

	    for (i = 0; i < num; i++) 
		{
			write1Value(out, i);

			if (i < num - 1) 
			{
				out->write(VALUE_SEPARATOR_CHAR);
				
				if (++numOnLine == maxOnLine && ! out->isCompact()) 
				{
					out->write('\n');
					out->indent();
					out->write(' ');
					numOnLine = 0;
				}
				else
				out->write(' ');
			}
	    }

	    out->write(CLOSE_BRACE_CHAR);
	    out->decrementIndent(4);
	}
}
