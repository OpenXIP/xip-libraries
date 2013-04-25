#ifndef SOXIPPICKRADIUSELEMENT_H
#define SOXIPPICKRADIUSELEMENT_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/elements/SoFloatElement.h>
#include <Inventor/fields/SoSFInt32.h>


//Element that will store the index of the active slice
class XIPIVCORE_API SoXipPickRadiusElement : public SoFloatElement 
{
	SO_ELEMENT_HEADER(SoXipPickRadiusElement);

public:
	// Initializes the SoRadIndexElement class
	static void    initClass();

	// Initializes element
	virtual void   init(SoState *state);

	// Sets the current index
	static void    set(SoState *state, float index);

	// get the current index
	static float   get(SoState *state);


protected:
	virtual ~SoXipPickRadiusElement();

};


#endif // SOXIPPICKRADIUSELEMENT_H