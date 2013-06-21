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
 |	SoSFDouble
 |
 |   Author(s)		: Paul S. Strauss
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#include <xip/inventor/extra/SoSFDouble.h>

/////////////////////////////////////////////////////////////////////
//
// SoSFDouble class
//
/////////////////////////////////////////////////////////////////////

// Use standard definitions of all basic methods
SO_SFIELD_SOURCE(SoSFDouble, double, double);

/////////////////////////////////////////////////////////////////////
//
// Description:
//    Reads value from file. Returns FALSE on error.
//
// Use: private

SbBool
SoSFDouble::readValue(SoInput *in)
//
/////////////////////////////////////////////////////////////////////
{
    return in->read(value);
}

/////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes value of field to file.
//
// Use: private

void
SoSFDouble::writeValue(SoOutput *out) const
//
/////////////////////////////////////////////////////////////////////
{
    out->write(value);
}
