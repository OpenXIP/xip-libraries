#include <xip/inventor/core/SoXipPickRadiusElement.h>

SO_ELEMENT_SOURCE(SoXipPickRadiusElement);

////////////////////////////////////////////////////////////////////////

SoXipPickRadiusElement::~SoXipPickRadiusElement()
{
}

void
SoXipPickRadiusElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipPickRadiusElement, SoFloatElement);	
}

void
SoXipPickRadiusElement::init(SoState *)
{
	data = 0;
}

void
SoXipPickRadiusElement::set(SoState *state, float index)
{
	SoFloatElement::set(classStackIndex, state, index);
}

float SoXipPickRadiusElement::get(SoState *state)
{
	return SoFloatElement::get(classStackIndex, state);
}
