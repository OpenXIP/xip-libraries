#ifndef SORADRENDERMODEELEMENT_H
#define SORADRENDERMODEELEMENT_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/elements/SoInt32Element.h>


class XIPIVCORE_API SoXipRenderModeElement : public SoInt32Element 
{
	SO_ELEMENT_HEADER(SoXipRenderModeElement);

public:
    enum RenderModes
	{
		MPR,
		MAXIP,
		MINIP,
		SSD,
		SSD_COLOR,
		VRT_COLOR,
		DRR,
		MPR_AND_GRAD_SEGMENT
	};

	// Initializes the SoRadRenderModeElement class
	static void initClass();

	// Initializes element
	virtual void init(SoState *state);

	// Sets the current temperature in the state to the given
	// temperature (in degrees Fahrenheit)
	static void set(SoState *state, SoNode *node, RenderModes mode);

	// Returns the current temperature from the state
	static RenderModes get(SoState *state);

	// Returns the default temperature
	static RenderModes getDefault() { return MPR; }

private:
	virtual ~SoXipRenderModeElement();
};

#endif // SORADRENDERMODEELEMENT_H

