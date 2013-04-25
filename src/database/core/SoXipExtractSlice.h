#ifndef SOXIPEXTRACTSLICE_H
#define SOXIPEXTRACTSLICE_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipMFDataImage.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/engines/SoSubEngine.h>

class SoXipDataImage;

class SoXipExtractSlice : public SoEngine
{
	SO_ENGINE_HEADER( SoXipExtractSlice );

public:
	SoXipExtractSlice();

	SoXipSFDataImage    image;
	SoSFShort			sliceIndex;

	SoEngineOutput		output;
	SoEngineOutput		numSlices;

	static void initClass();	

protected:
	~SoXipExtractSlice();

	virtual void evaluate();

	SoXipDataImage*		mImageData;
	SoXipMFDataImage	mOutputs;	

};

#endif // SOXIPEXTRACTSLICE_H