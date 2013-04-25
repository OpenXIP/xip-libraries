#ifndef SOXIPCOMPOSEMFIMAGE_H
#define SOXIPCOMPOSEMFIMAGE_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/engines/SoSubEngine.h>

class SoXipComposeMFImage : public SoEngine
{
	SO_ENGINE_HEADER( SoXipComposeMFImage );

public:
	SoXipComposeMFImage();

	SoXipSFDataImage	input0;
	SoXipSFDataImage	input1;
	SoXipSFDataImage	input2;
	SoXipSFDataImage	input3;
	SoXipSFDataImage	input4;
	SoXipSFDataImage	input5;
	SoXipSFDataImage	input6;
	SoXipSFDataImage	input7;

	SoEngineOutput		output;

	static void initClass();

protected:
	~SoXipComposeMFImage();

	virtual void evaluate();
};

#endif // SOXIPCOMPOSEMFIMAGE_H