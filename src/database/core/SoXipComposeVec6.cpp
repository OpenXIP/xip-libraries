#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include "SoXipComposeVec6.h"

SO_ENGINE_SOURCE( SoXipComposeVec6 );

SoXipComposeVec6::SoXipComposeVec6()
{
	SO_ENGINE_CONSTRUCTOR( SoXipComposeVec6 );

	SO_ENGINE_ADD_INPUT(      plane,  (SbPlane(SbVec3f(1.0, 0.0, 0.0), 0.0)));
    
	SO_ENGINE_ADD_INPUT(      image,  (0) );

	SO_ENGINE_ADD_INPUT( sliceIndex, (-1) );
	SO_ENGINE_ADD_INPUT( xmin, (-1) );
	SO_ENGINE_ADD_INPUT( xmax, (-1) );
	SO_ENGINE_ADD_INPUT( ymin, (-1) );
	SO_ENGINE_ADD_INPUT( ymax, (-1) );
	SO_ENGINE_ADD_INPUT( zmin, (-1) );
	SO_ENGINE_ADD_INPUT( zmax, (-1) );

	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage );
	SO_ENGINE_ADD_OUTPUT( numSlices, SoSFShort );
	SO_ENGINE_ADD_OUTPUT( outSliceIndex, SoSFShort );
	SO_ENGINE_ADD_OUTPUT( outVOI, SoMFInt32 );

	mImageData = 0;
}

SoXipComposeVec6::~SoXipComposeVec6()
{

}

void
SoXipComposeVec6::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipComposeVec6, SoEngine, "Engine" );
}

void
SoXipComposeVec6::evaluate()
{
	SO_ENGINE_OUTPUT(outVOI, SoMFInt32, setNum(6));

	// intersection of plane and volume

	SO_ENGINE_OUTPUT(outVOI, SoMFInt32, set1Value(0, xmin.getValue()) );
	SO_ENGINE_OUTPUT(outVOI, SoMFInt32, set1Value(1, xmax.getValue()) );

	SO_ENGINE_OUTPUT(outVOI, SoMFInt32, set1Value(2, ymin.getValue()) );
	SO_ENGINE_OUTPUT(outVOI, SoMFInt32, set1Value(3, ymax.getValue()) );

	SO_ENGINE_OUTPUT(outVOI, SoMFInt32, set1Value(4, zmin.getValue()) );
	SO_ENGINE_OUTPUT(outVOI, SoMFInt32, set1Value(5, zmax.getValue()) );
	
	// Reset outputs
    SO_ENGINE_OUTPUT( numSlices, SoSFShort, setValue(0) );
    SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(0) );

	SoXipDataImage* imageData = image.getValue();
	if( mImageData != imageData )
	{
		mImageData = image.getValue();

		// Reset previous outputs
		mOutputs.setNum(0);

		if( mImageData )
		{
			SbXipImage* image = mImageData->get();
			if( !image )
				return ;

			// Initialize outputs
			unsigned int numSlices = image->getDimStored()[2];			
			mOutputs.setNum( numSlices );

			for( unsigned int i = 0; i < numSlices; ++ i )
				mOutputs.set1Value( i, 0 );
		}
	}

	if( imageData )
	{
		SbXipImage* image = mImageData->get();
		if( !image )
			return ;

		SbXipImageDimensions dimensions = image->getDimStored();

		SbXipImageDimensions sliceDimensions = dimensions;
		sliceDimensions[2] = 1;

		int sliceIndex = this->sliceIndex.getValue();
		if( sliceIndex < 0 || sliceIndex >= dimensions[2] )
			return ;

		if( mOutputs[sliceIndex] == 0 )
		{
			// Compute the model matrix of the selected frame
			SbMatrix sliceModelMatrix = image->getModelMatrix();
			sliceModelMatrix[2][0] /= dimensions[2];
			sliceModelMatrix[2][1] /= dimensions[2];
			sliceModelMatrix[2][2] /= dimensions[2];

			sliceModelMatrix[3][0] += sliceIndex * sliceModelMatrix[2][0];
			sliceModelMatrix[3][1] += sliceIndex * sliceModelMatrix[2][1];
			sliceModelMatrix[3][2] += sliceIndex * sliceModelMatrix[2][2];

			// Pointer to the selected slice
			char* imagePtr = (char *) image->refBufferPtr();

			unsigned int cellSize;
			switch( image->getType() )
			{
			case SbXipImage::UNSIGNED_BYTE: cellSize = sizeof(unsigned char); break ;
			case SbXipImage::BYTE: cellSize = sizeof(char); break ;
			case SbXipImage::UNSIGNED_SHORT: cellSize = sizeof(unsigned short); break ;
			case SbXipImage::SHORT: cellSize = sizeof(short); break ;
			case SbXipImage::UNSIGNED_INT: cellSize = sizeof(unsigned int); break ;
			case SbXipImage::INT: cellSize = sizeof(int); break ;
			case SbXipImage::FLOAT: cellSize = sizeof(float); break ;
			case SbXipImage::DOUBLE: cellSize = sizeof(double); break ;
			}

			void* slicePtr = imagePtr + cellSize * image->getComponents() * dimensions[0] * dimensions[1] * sliceIndex;

			SbXipImage* slice = new SbXipImage( sliceDimensions, image->getType(), image->getBitsStored(), slicePtr,
				image->getComponents(), image->getComponentType(), image->getComponentLayoutType(), sliceModelMatrix,
				image->getLineAlignment() );

			image->unrefBufferPtr();

			SoXipDataImage* output = new SoXipDataImage();
			output->ref();
			output->set( slice );
			output->addRef( imageData );

			mOutputs.set1Value( sliceIndex, output );
		}

		SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(mOutputs[sliceIndex]) );
    }
}