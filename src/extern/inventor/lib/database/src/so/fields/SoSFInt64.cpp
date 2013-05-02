// FIXME: add header, add __int64 support to SoInput and SoOutput

#include <Inventor/fields/SoSFInt64.h>
#include <stdlib.h>

#include <xip/system/standard.h>

//////////////////////////////////////////////////////////////////////////////
//
// SoSFInt64 class
//
//////////////////////////////////////////////////////////////////////////////

// Use standard definitions of all basic methods
SO_SFIELD_SOURCE(SoSFInt64, int64_t, int64_t);


//////////////////////////////////////////////////////////////////////////////
void	SoSFInt64::initClass()
{
	SO__FIELD_INIT_CLASS(SoSFInt64, "SFInt64", SoSField);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Reads value from file. Returns FALSE on error.
//
// Use: private

SbBool
SoSFInt64::readValue(SoInput *in)
//
////////////////////////////////////////////////////////////////////////
{
    //return in->read(value);
    SbString input;
    SbBool res = in->read(input);
    value = _strtoi64(input.getString(), NULL, 10);
    return res;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Writes value of field to file.
//
// Use: private

void
SoSFInt64::writeValue(SoOutput *out) const
//
////////////////////////////////////////////////////////////////////////
{
    //out->write(value);
    char buffer[65];
    _i64toa(value, buffer, 10); 
    out->write(buffer);
}
