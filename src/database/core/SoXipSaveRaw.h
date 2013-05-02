#ifndef SOXIPSAVERAW_H
#define SOXIPSAVERAW_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoXipDataImage;

class SoXipSaveRaw : public SoEngine
{
	SO_ENGINE_HEADER( SoXipSaveRaw );

public:
	/// Voxel Type enum
	enum VoxelType
	{
		UBYTE,
		USHORT,
        SHORT,
		FLOAT32
	};

	/// trigger to actually the image
	SoSFTrigger		saveImage;
	/// Voxel type
	SoSFEnum		voxelType;
	/// Image width
	SoSFShort		width;
	/// Image height
	SoSFShort		height;
	/// Image depth
	SoSFShort		depth;
	/// Image number of bits used
	SoSFShort		bitsUsed;
	/// Input file
	SoSFString		file;

	/// Output image (SoXipSFDataImage)
	SoXipSFDataImage	image;

	/// Constructor
	SoXipSaveRaw();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipSaveRaw();

	/// Input Changed method
	void inputChanged(SoField * changedField);

	/// Evaluate method
	virtual void evaluate();

	/// Read instance method
	virtual SbBool readInstance( SoInput* in, unsigned short flags );

private:
	bool mImageReady;
};

#endif // SOXIPSAVERAW_H


