#ifndef SBXIPIMAGEADAPTOR_H
#define  SBXIPIMAGEADAPTOR_H

#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/core/SbXipImage.h>


template <class T> 
class SbXipImageInterleavedPixelPtr
{
public:
	SbXipImageInterleavedPixelPtr(SbXipImage *image, int sliceIndex = 0)
	{
		mImage  = image;
		mBuffer = (unsigned char*) mImage->refBufferPtr();
		mLineLengthAllocated = mImage->getLineLengthAllocated();
		mComponents = mImage->getComponents();

		mBuffer += sliceIndex * mLineLengthAllocated * image->getDimAllocated()[1];

		#if _DEBUG
		if ((mImage->getComponentType() != SbXipImage::INTERLEAVED) && (mImage->getComponents() != 1))
		{
			SoDebugError::post(__FILE__, "SbXipImageInterleavedPixelPtr used with incompatible image!");
		}
		#endif
	};

	~SbXipImageInterleavedPixelPtr()
	{
		mImage->unrefBufferPtr();
	};

	// default access operator
	T& operator ()(const int y, const int x, const int c = 0)
	{
		return *( (T*) (mBuffer + y * mLineLengthAllocated) + x * mComponents + c) ;
	};

	const T& operator ()(const int y, const int x, const int c = 0) const
	{
		return *( (T*) (mBuffer + y * mLineLengthAllocated) + x * mComponents + c);
	};

	// for interleaved data we can also return line pointers
	T* operator [](const int i)
	{
		return (T*) (mBuffer + (i * mLineLengthAllocated));
	};

	const T* operator [](const int i) const
	{
		return (const T*) (mBuffer + (i * mLineLengthAllocated));
	};

protected:
	SbXipImage *mImage;
	unsigned char *mBuffer;
	int mLineLengthAllocated;
	int mComponents;
};


template <class T> 
class SbXipImageSeparatePixelPtr
{
public:
	SbXipImageSeparatePixelPtr(SbXipImage *image, int sliceIndex = 0)
	{
		mImage  = image;
		mBuffer = (unsigned char*) mImage->refBufferPtr();
		mLineLengthAllocated = mImage->getLineLengthAllocated();
		mComponentOffset = mLineLengthAllocated * image->getDimAllocated()[1] * image->getDimAllocated()[2];

		mBuffer += sliceIndex * mLineLengthAllocated * image->getDimAllocated()[1];

		#if _DEBUG
		if ((mImage->getComponentType() != SbXipImage::SEPARATE) && (mImage->getComponents() != 1))
		{
			SoDebugError::post(__FILE__, "SbXipImageSeparatePixelPtr used with incompatible image!");
		}
		#endif
	};

	~SbXipImageSeparatePixelPtr()
	{
		mImage->unrefBufferPtr();
	};

	T& operator ()(const int y, const int x, const int c = 0)
	{
		return *( (T*) (mBuffer + y * mLineLengthAllocated + c * mComponentOffset) + x);
	};

	const T& operator ()(const int y, const int x, const int c = 0) const
	{
		return *( (T*) (mBuffer + y * mLineLengthAllocated + c * mComponentOffset) + x);
	};

protected:
	SbXipImage *mImage;
	unsigned char *mBuffer;
	int mLineLengthAllocated;
	int mComponentOffset;
};

class SbXipImagePackedPixelSlicePtr
{
public:
	SbXipImagePackedPixelSlicePtr( SbXipImage* image, int sliceIndex )
	{
		mImage = image;
		mBuffer = (unsigned char *) image->refBufferPtr();
		mLineLengthAllocated = image->getLineLengthAllocated();
		mBuffer += sliceIndex * mLineLengthAllocated * image->getDimAllocated()[1];
	}

	~SbXipImagePackedPixelSlicePtr()
	{
		mImage->unrefBufferPtr();
	}

	unsigned char get( const int y, const int x ) const
	{
		unsigned char* ptr = mBuffer + y * mLineLengthAllocated + x / 8;
		return *ptr & ( 128 >> ( x % 8 ) );
	}

	void setTrue( const int y, const int x )
	{
		unsigned char* ptr = mBuffer + y * mLineLengthAllocated + x / 8;
		*ptr = *ptr | ( 128 >> ( x % 8 ) );
    }

	void setFalse( const int y, const int x )
	{
		unsigned char* ptr = mBuffer + y * mLineLengthAllocated + x / 8;
		*ptr = *ptr & ( 255 - ( 128 >> ( x % 8 ) ) );
	}

protected:
	SbXipImage* mImage;
	unsigned char* mBuffer;
	int mLineLengthAllocated;
    
};

class SbXipImagePackedPixelLinePtr
{
public:
	SbXipImagePackedPixelLinePtr( SbXipImage* image, int sliceIndex, int lineIndex )
	{
		mImage = image;
		mBuffer = (unsigned char *) image->refBufferPtr();
		mBuffer += image->getLineLengthAllocated() *
			( lineIndex + sliceIndex * image->getDimAllocated()[1] );
	}

	~SbXipImagePackedPixelLinePtr()
	{
		mImage->unrefBufferPtr();
	}

	unsigned char get( const int x ) const
	{
		unsigned char* ptr = mBuffer + x / 8;
		return *ptr & ( 128 >> ( x % 8 ) );
	}

	void set( const int x, unsigned char value )
	{
		value ? setTrue( x ) : setFalse( x );
	}

	void setTrue( const int x )
	{
		unsigned char* ptr = mBuffer + x / 8;
		*ptr = *ptr | ( 128 >> ( x % 8 ) );
    }

	void setFalse( const int x )
	{
		unsigned char* ptr = mBuffer + x / 8;
		*ptr = *ptr & ( 255 - ( 128 >> ( x % 8 ) ) );
	}

protected:
	SbXipImage* mImage;
	unsigned char* mBuffer;
    
};

#endif // SbXipImageADAPTOR_H
