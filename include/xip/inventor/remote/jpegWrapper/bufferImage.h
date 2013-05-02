//----------------------------------------------------------------------------------
//! ImageHandler
/*!
// \file    bufferImage.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// Wrapper for the JPEG library
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------

#if !defined(__BUFFERIMAGE_H)
#define __BUFFERIMAGE_H
 

#include "memoryObj.h"

#ifdef WIN32

#include <windows.h>

#endif


#ifndef WIN32

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned long    COLORREF;

#ifndef BOOL
#define	BOOL bool
#endif

#ifndef TRUE
#define	TRUE true
#endif

#ifndef FALSE
#define	FALSE false
#endif

#endif

#ifdef __DISABLE_WARNING
#pragma warning(disable: 4244) /* conversion from '...' to '...', possible loss of data */
#endif

#include <stdio.h>
#include <stddef.h>
//#include <vector>

#include <math.h>
#include <emmintrin.h>
#include <xmmintrin.h>


/**************************************************************************************************
/ The RGBQUAD structure describes a color consisting of relative intensities of red, green, and blue
/
/ http://msdn.microsoft.com/library/en-us/gdi/bitmaps_5f8y.asp?frame=true
/*************************************************************************************************/
class bufferImage
{
typedef struct  bufferImageInfo {
	unsigned long	scanningWidth;	// unsigned long aligned scan line width
	unsigned char*	ptrToImageBits;	// pointer to the image bits
	bufferImage* pGhost;			//  points to the body
	char	Error[256];			
	unsigned char	jpegQuality;	// JPEG
	long	Xdpi;					// horizontal resolution
	long	Ydpi;					// vertical resolution
	bool	last_c_isvalid;

} IMGINFO;

public:

	/**
	 * Image (empty) constructor
	 */
	inline bufferImage()
	{
		Startup();
		Temp1 = NULL;
		Temp2 = NULL;
		Temp3 = NULL;
		mTempSize = 0;
    
	}
	
	/**
	 * Image constructor
	 */
	inline bufferImage(unsigned long width, unsigned long height, unsigned long bpp)
	{
		Startup();
		Create(width,height,bpp);
	}

	bufferImage(BuffObj * stream);
	bufferImage(unsigned char * buffer, unsigned long size);
	
	virtual ~bufferImage()
	{ 
		Destroy(); 
	};
	
	bufferImage& operator = (const bufferImage&);

	void*	Create(unsigned long width, unsigned long height, unsigned long bpp);
	bool	Destroy();
	
	/**
	* Sets the image bits to the specified value
	*/
	inline void	Clear(unsigned char bval=0)
	{
		if (HeadPalPix_Ptr == 0) return;	
		memset(info.ptrToImageBits,bval,Header.biSizeImage);
	}

	bool	Transfer(bufferImage &from);
	bool	CreateFromImgBuffPtr(unsigned char* bufferPtr,unsigned long width,unsigned long hight,
								 unsigned long bpp, unsigned long bpl);
	
	inline void	FreeMemory(void* memblock)
	{
		if (memblock)
			free(memblock);
	}

	/**
	* return the size (bytes) of the Header object
	*/
	inline long	GetSize()
	{
		return Header.biSize + Header.biSizeImage + getPalSize();
	}

	/**
	* return the pointer to pixels
	*/
	unsigned char*	getBitsPtr(unsigned long row = 0);
	
	/**
	* return the pointer of the upsampled image (8bits -> 12bits)
	*/
	unsigned char*  get8to12Ptr(unsigned long size);
	
	/**
	* return the height
	*/
	inline unsigned long getHeight() const
	{
		return Header.biHeight;
	}
	
	/**
	* return the width
	*/
	inline unsigned long getWidth() const
	{
		return Header.biWidth;
	}
	
	/**
	* return the aligned scan line width
	*/
	inline unsigned long getScanningWidth() const
	{
		return info.scanningWidth;
	}
	
	/**
	* return the bits per point
	*/
	inline unsigned short getBpp() const
	{
		return Header.biBitCount;
	}

	/**
	* return the jpeg quality (0 - 100)
	*/
	inline unsigned char GetJpegQuality() const
	{
		return info.jpegQuality;
	}	

	/**
	* set the jpeg quality (0 - 100)
	*/
	inline void	SetJpegQuality(unsigned char q)
	{
		info.jpegQuality = q;
	}

	/**
	* return the resolution of the X
	*/
	inline long	getXdpi() const 
	{
		return info.Xdpi;
	}

	/**
	* return the resolution of the Y
	*/
	inline long	getYdpi() const
	{
		return info.Ydpi;
	}

	/**
	* set the resolution of the X
	*/
	inline void	setXdpi(long dpi)
	{
		if (dpi<=0) dpi=96;
		info.Xdpi = dpi;
		Header.biXPelsPerMeter = (long) floor(dpi * 10000.0 / 254.0 + 0.5);
	}
	
	/**
	* set the resolution of the Y
	*/
	inline void	setYdpi(long dpi)
	{
		if (dpi<=0) dpi=96;
		info.Ydpi = dpi;
		Header.biYPelsPerMeter = (long) floor(dpi * 10000.0 / 254.0 + 0.5);
	}

	/**
	* return true is a grayscale image
	*/
	inline bool	isGS()
	{
		RGBQUAD* ppal=getPalPtr();
		if(!(HeadPalPix_Ptr && ppal && Header.biClrUsed)) return false;
		for(unsigned long i=0;i<Header.biClrUsed;i++)
		{
			if (ppal[i].rgbBlue!=i || ppal[i].rgbGreen!=i || ppal[i].rgbRed!=i) return false;
		}
		return true;
	}

	/**
	* return palette size
	*/
	inline unsigned long getPalSize()
	{
		return (Header.biClrUsed * sizeof(RGBQUAD));
	}

	/**
	* return palette pointer
	*/
	inline RGBQUAD* getPalPtr() const
	{
		if ((HeadPalPix_Ptr)&&(Header.biClrUsed))
			return (RGBQUAD*)((unsigned char*)HeadPalPix_Ptr + sizeof(BITMAPINFOHEADER));
		return NULL;
	}

	/**
	* set the grayscale palette
	*/
	inline void	setGPal()
	{
		if ((HeadPalPix_Ptr==NULL)||(Header.biClrUsed==0)) return;
		RGBQUAD* pal=getPalPtr();
		for (unsigned long ni=0;ni<Header.biClrUsed;ni++)
			pal[ni].rgbBlue=pal[ni].rgbGreen = pal[ni].rgbRed = (unsigned char)(ni*(255/(Header.biClrUsed-1)));
	}

	/**
	* set the RGB palette
	*/
	inline void	setPal(unsigned long n, unsigned char *r, unsigned char *g, unsigned char *b)
	{
		if ((HeadPalPix_Ptr==NULL)||(Header.biClrUsed==0)) return;
		RGBQUAD* pal=getPalPtr();
		for (unsigned long ni=0;ni<Header.biClrUsed;ni++)
			pal[ni].rgbBlue=pal[ni].rgbGreen = pal[ni].rgbRed = (unsigned char)(ni*(255/(Header.biClrUsed-1)));
	}

	bool encodeBuffer(BuffObj * handledObj);
	bool encodeBuffer(unsigned char * &buffer, long &size);
	bool decodeBuffer(BuffObj * handledObj);
	bool decodeBuffer(unsigned char * buffer, unsigned long size);
	bool restoreBuffer(unsigned char *buffer, unsigned char alpha, unsigned long bufferSize);
	bool restoreBuffer(unsigned char *buffer, unsigned char *alpha, unsigned long bufferSize);
	
protected:
		
	void Startup();
	void copyPtr(bufferImage *src);

	void*				HeadPalPix_Ptr; //contains the header, the palette, the pixels
    BITMAPINFOHEADER    Header;			//standard header  --> FROM GDI
	IMGINFO		info;					//image information

private:

#if defined(WIN64)
    inline static int CPU()
    {
        // SSE2 is always supported on x64 architectures
        // Haven't found out how to check for SSE3 and higher...
        // Just having WIN64 is, however/perhaps, not a guarantee
        // to have SSE2 or Intel 64-bit CPU...
        return 3;
    }
#elif defined(WIN32)
		inline static int CPU() 
		{
			unsigned int info;

			unsigned int isSse3;

			__asm

			{
				mov eax, 01h

				cpuid

				mov info, edx

				mov isSse3, ecx 
			}

			#if _DEBUG
				return 0;   // Legacy
			#endif

			if( isSse3 & 0x0000200 ) return 5; // SSSE3
			if( isSse3 & 0x0000001 ) return 4; // SSE3
			if( info & 0x4000000 )   return 3; // SSE2
			if( info & 0x2000000 )   return 2; // SSE
			if( info & 0x0800000 )   return 1; // MMX
			
			return 0;  // Legacy
			  
		}
#else
    // This code needs to be revised for non Windows support
    // How to determine proper CPU type and SSE support...
    inline static int CPU()
    {
        return 0;
    }
#endif
		int cpuID;

		unsigned char* Temp1;
		unsigned char* Temp2;
		unsigned short* Temp3;
		unsigned long mTempSize;

	 
	static inline void fastMemcopy(unsigned char * dst, unsigned char* src, unsigned block_size)
		{
			 
				const __m128i* wrd_ptr = (__m128i*)src;
				const __m128i* wrd_end = (__m128i*)(src + block_size);
				__m128i* dst_ptr = (__m128i*)dst;


				unsigned int nTimes ;
				if(block_size % 16 != 0) 
					nTimes = ((int)(block_size/16))+1;
				else nTimes = (block_size/16);
				
				if(block_size < 16) nTimes = 1;
				
				
 				for(unsigned int i = 0; i < nTimes; i++ )
				{
					__m128i xmm1 = _mm_loadu_si128(wrd_ptr);
					_mm_storeu_si128(dst_ptr, xmm1);
					++dst_ptr;
					++wrd_ptr;
				}
			 
		}
};

#endif  //__BUFFERIMAGE_H
