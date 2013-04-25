/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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