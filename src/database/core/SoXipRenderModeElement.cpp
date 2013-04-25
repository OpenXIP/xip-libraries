#include <xip/inventor/core/SoXipRenderModeElement.h>


SO_ELEMENT_SOURCE(SoXipRenderModeElement);

// Initializes the SoRadRenderModeElement class.

void SoXipRenderModeElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipRenderModeElement, SoInt32Element);
}

// Destructor

SoXipRenderModeElement::~SoXipRenderModeElement()
{
}

// Initializes the first instance used in an action's state.

void SoXipRenderModeElement::init(SoState *)
{
	data = getDefault();
}

// Sets the current temperature in the state.

void SoXipRenderModeElement::set(SoState *state, SoNode *node, RenderModes mode)
{
	// Use the corresponding method on SoInt32Element to set the
	// value in the top instance in the state
	SoInt32Element::set(classStackIndex, state, node, (int32_t) mode);
}

// Returns the current temperature from the state.

SoXipRenderModeElement::RenderModes SoXipRenderModeElement::get(SoState *state)
{
	// Use the corresponding method on SoInt32Element to get the
	// value from the top instance in the state
	return (RenderModes) SoInt32Element::get(classStackIndex, state);
}
