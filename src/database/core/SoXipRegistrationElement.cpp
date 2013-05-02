#include <xip/inventor/core/SoXipRegistrationElement.h>

SO_ELEMENT_SOURCE(SoXipRegistrationElement);

void
SoXipRegistrationElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipRegistrationElement, SoReplacedElement);
}

SoXipRegistrationElement::~SoXipRegistrationElement()
{

}

void
SoXipRegistrationElement::init(SoState *state)
{
	SoReplacedElement::init(state);

	mMatrix.makeIdentity();
}

void
SoXipRegistrationElement::set(SoState *state, SoNode *node, const SbMatrix &matrix)
{
	SoXipRegistrationElement *elt;
	elt = (SoXipRegistrationElement*)getElement(state, classStackIndex, node);

	if ( NULL!=elt )
	{
		elt->setElt(matrix);
	}
}

const SbMatrix&
SoXipRegistrationElement::get(SoState *state)
{
	const SoXipRegistrationElement *elt;
	elt = (const SoXipRegistrationElement*)getConstElement(state, classStackIndex);

	return elt->mMatrix;
}

void
SoXipRegistrationElement::print(FILE *fp) const
{
	SoReplacedElement::print(fp);
}

void
SoXipRegistrationElement::setElt(const SbMatrix &matrix)
{
	mMatrix = matrix;
}