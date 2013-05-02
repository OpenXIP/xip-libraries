#pragma once

#include <xip/inventor/core/xipivcore.h>

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

class XIPIVCORE_API SoXipRegistrationElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER(SoXipRegistrationElement);

public:
	// Initializes element
	virtual void init(SoState *state);

	// Sets the view matrix to the given matrix
	static void	set(SoState *state, SoNode *node, const SbMatrix &matrix);

	// Returns current matrix from the state
	static const SbMatrix &	get(SoState *state);

	// Prints element (for debugging)
	virtual void print(FILE *fp) const;

	static void initClass();

protected:
	SbMatrix mMatrix;

	// Sets the matrix in an instance
	virtual void setElt(const SbMatrix &matrix);

	virtual ~SoXipRegistrationElement();
};