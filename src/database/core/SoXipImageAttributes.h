#ifndef SORADIMAGEATTRIBUTES_H
#define SORADIMAGEATTRIBUTES_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <xip/inventor/core/SoXipSFDataImage.h>


class SoXipImageAttributes : public SoEngine
{
	SO_ENGINE_HEADER(SoXipImageAttributes);

public:
	SoXipImageAttributes();
	static void initClass();

	SoXipSFDataImage image;
	SoEngineOutput	 modelMatrix;
	SoEngineOutput	 width;
	SoEngineOutput	 height;
	SoEngineOutput	 depth;
	SoEngineOutput	 bitsStored;

	SoEngineOutput	 defaultOrientation;

	SoEngineOutput	 orthoScanOrientation;
	SoEngineOutput	 orthoOrientation1;
	SoEngineOutput	 orthoOrientation2;
	SoEngineOutput	 orthoOrientation3;

	SoEngineOutput	 defaultCenter;

protected:
	virtual ~SoXipImageAttributes();
	virtual void evaluate();
};


#endif // SORADIMAGEATTRIBUTES_H
