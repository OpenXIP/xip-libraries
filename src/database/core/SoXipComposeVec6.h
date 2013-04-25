#ifndef SoXipComposeVec6_H
#define SoXipComposeVec6_H

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

class SoXipComposeVec6 : public SoEngine
{
	SO_ENGINE_HEADER( SoXipComposeVec6 );

public:
	SoXipComposeVec6();

	SoSFPlane			plane;
	SoXipSFDataImage    image;
	SoSFShort			xmin;
	SoSFShort			xmax;
	SoSFShort			ymin;
	SoSFShort			ymax;
	SoSFShort			zmin;
	SoSFShort			zmax;
	SoSFShort			sliceIndex;

	SoEngineOutput		output;
	SoEngineOutput		numSlices;
	SoEngineOutput		outSliceIndex;
	SoEngineOutput		outVOI;

	static void initClass();

protected:
	~SoXipComposeVec6();

	virtual void evaluate();

	SoXipDataImage*		mImageData;
	SoXipMFDataImage	mOutputs;	

};

#endif // SoXipComposeVec6_H