#ifndef SOXIPCOMPOSEMFDICOM_H
#define SOXIPCOMPOSEMFDICOM_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/dicom/SoXipSFDataDicom.h>

class SoXipComposeMFDicom : public SoEngine
{
	SO_ENGINE_HEADER( SoXipComposeMFDicom );

public:
	SoXipComposeMFDicom();

	SoXipSFDataDicom	input0;
	SoXipSFDataDicom	input1;
	SoXipSFDataDicom	input2;
	SoXipSFDataDicom	input3;
	SoXipSFDataDicom	input4;
	SoXipSFDataDicom	input5;
	SoXipSFDataDicom	input6;
	SoXipSFDataDicom	input7;

	SoEngineOutput		output;

	static void initClass();

protected:
	~SoXipComposeMFDicom();

	virtual void evaluate();
};

#endif // SOXIPCOMPOSEMFDICOM_H