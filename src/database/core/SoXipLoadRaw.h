#ifndef SOXIPLOADRAW_H
#define SOXIPLOADRAW_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFString.h>

class SoXipDataImage;

class SoXipLoadRaw : public SoEngine
{
	SO_ENGINE_HEADER( SoXipLoadRaw );

public:
	/// Voxel Type enum
	enum VoxelType
	{
		UBYTE,
		USHORT,
        SHORT,
		FLOAT32
	};

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
	/// Image model matrix
	SoSFMatrix		modelMatrix;
	/// Input file
	SoSFString		file;

	/// Output image (SoXipSFDataImage)
	SoEngineOutput	output;

	/// Constructor
	SoXipLoadRaw();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipLoadRaw();

	/// Evaluate method
	virtual void evaluate();

	/// Read instance method
	virtual SbBool readInstance( SoInput* in, unsigned short flags );

	SoXipDataImage*		mDataOutput;
};

#endif // SOXIPLOADRAW_H
