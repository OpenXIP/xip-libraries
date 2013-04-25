#ifndef SoXipDecomposeVec6_H
#define SoXipDecomposeVec6_H

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

class SoXipDecomposeVec6 : public SoEngine
{
	SO_ENGINE_HEADER( SoXipDecomposeVec6 );

public:
	SoXipDecomposeVec6();

	SoSFMatrix			modelMatrix;
	SoSFPlane			plane;
	SoXipSFDataImage    image;
	SoSFShort			sliceIndex;
	SoMFInt32			inVOI;

	SoEngineOutput		output;
	SoEngineOutput		numSlices;
	SoEngineOutput		xmin;
	SoEngineOutput		xmax;
	SoEngineOutput		ymin;
	SoEngineOutput		ymax;
	SoEngineOutput		zmin;
	SoEngineOutput		zmax;

	static void initClass();

protected:
	~SoXipDecomposeVec6();

	virtual void evaluate();

	SoXipDataImage*		mImageData;
	SoXipMFDataImage	mOutputs;	

};

#endif // SoXipDecomposeVec6_H