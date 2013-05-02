// FIXME: add header

#ifndef  _SO_SF_INT64_
#define  _SO_SF_INT64_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFInt64 subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

// C-api: prefix=SoSFInt64
class INVENTOR_API SoSFInt64 : public SoSField {

    // Use standard field stuff
    SO_SFIELD_HEADER(SoSFInt64, int64_t, int64_t);

  public:
    static void		initClass();
};

#endif /* _SO_SF_INT64_ */
