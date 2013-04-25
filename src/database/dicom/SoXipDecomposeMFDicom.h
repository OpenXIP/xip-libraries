#ifndef SOXIPDECOMPOSEMFDICOM_H
#define SOXIPDECOMPOSEMFDICOM_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>

class SoXipDecomposeMFDicom : public SoEngine
{
	SO_ENGINE_HEADER( SoXipDecomposeMFDicom );

public:
	SoXipDecomposeMFDicom();

	SoXipMFDataDicom	input;
	SoSFShort			index;

	SoEngineOutput		output;

	static void initClass();

protected:
	~SoXipDecomposeMFDicom();

	virtual void evaluate();
};

#endif // SOXIPDECOMPOSEMFDICOM_H