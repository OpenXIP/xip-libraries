#ifndef SOXIPDECOMPOSEMFIMAGE_H
#define SOXIPDECOMPOSEMFIMAGE_H

#include <xip/inventor/core/SoXipMFDataImage.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/engines/SoSubEngine.h>

class SoXipDecomposeMFImage : public SoEngine
{
	SO_ENGINE_HEADER( SoXipDecomposeMFImage );

public:
	SoXipDecomposeMFImage();

	SoXipMFDataImage	input;
	SoSFShort			index;

	SoEngineOutput		output;

	static void initClass();

protected:
	~SoXipDecomposeMFImage();

	virtual void evaluate();
};

#endif // SOXIPDECOMPOSEMFIMAGE_H