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
/*
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Classes:
 |	SoMFDouble
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <xip/inventor/extra/SoMFDouble.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////
//
// SoMFDouble class
//
/////////////////////////////////////////////////////////////////////

// Use standard definitions of all basic methods
SO_MFIELD_SOURCE_MALLOC(SoMFDouble, double, double);

/////////////////////////////////////////////////////////////////////
//
// Description:
//    Reads one (indexed) value from file. Returns FALSE on error.
//
// Use: private

SbBool
SoMFDouble::read1Value(SoInput *in, int index)
//
/////////////////////////////////////////////////////////////////////
{
    return in->read(values[index]);
}

/////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes one (indexed) value to file.
//
// Use: private

void
SoMFDouble::write1Value(SoOutput *out, int index) const
//
/////////////////////////////////////////////////////////////////////
{
    out->write(values[index]);
}

/////////////////////////////////////////////////////////////////////
//
// Description:
//    Returns number of ASCII values to write per output line.
//
// Use: private

int
SoMFDouble::getNumValuesPerLine() const
//
/////////////////////////////////////////////////////////////////////
{
    return 4;
}

/////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes array of binary values to file as one chunk.
//
// Use: private

void
SoMFDouble::writeBinaryValues(SoOutput *out) const

//
/////////////////////////////////////////////////////////////////////
{
    out->writeBinaryArray(values, num);
}

/////////////////////////////////////////////////////////////////////
//
// Description:
//    Reads array of binary values from file as one chunk.
//
// Use: private

SbBool
SoMFDouble::readBinaryValues(SoInput *in, int numToRead)
//
/////////////////////////////////////////////////////////////////////
{
    return (in->readBinaryArray(values, numToRead));
}
