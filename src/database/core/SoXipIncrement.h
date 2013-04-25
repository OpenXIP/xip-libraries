#ifndef SoXipIncrement_H
#define SoXipIncrement_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipMFDataImage.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/SbLinear.h>

class SoXipDataImage;

class SoXipIncrement : public SoEngine
{
	SO_ENGINE_HEADER( SoXipIncrement );

public:
	SoXipIncrement();

	SoSFShort			sliceIndex;

	SoSFTrigger next;
	SoSFTrigger previous;

	SoEngineOutput		outSliceIndex;

	static void initClass();

protected:
	~SoXipIncrement();

	virtual void evaluate();
	virtual void inputChanged(SoField *which);
};

#endif // SoXipIncrement_H