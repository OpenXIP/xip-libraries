// FIXME: add header

#ifndef  _SO_MF_INT64_
#define  _SO_MF_INT64_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFInt64 subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

// C-api: prefix=SoMFInt64
class INVENTOR_API SoMFInt64 : public SoMField {

    // Use standard field stuff
    SO_MFIELD_HEADER(SoMFInt64, int64_t, int64_t);

  public:
    static void		initClass();

  private:
    // Returns number of ASCII values to write per output line
    virtual int		getNumValuesPerLine() const;

    // Write/Read the values as a block of data
    virtual void	writeBinaryValues(SoOutput *out) const;
    virtual SbBool	readBinaryValues(SoInput *in, int numToRead);
};

#endif /* _SO_MF_INT64_ */
