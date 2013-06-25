/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <xip/system/standard.h>
#include <xip/inventor/remote/jpegWrapper/bufferImage.h>
/**
 *! \brief  Initialize 
 */
void bufferImage::Startup()
{
	//init pointers
	HeadPalPix_Ptr = NULL;
	//init structures
	memset(&Header,0,sizeof(BITMAPINFOHEADER));
	memset(&info,0,sizeof(IMGINFO));
	info.jpegQuality = 90;
	setXdpi(120);
	setYdpi(120);

	cpuID = CPU();
}


/**
 *! \brief  Destroy image pixels, alpha channel, and buffers
 */
bool bufferImage::Destroy()
{
	if (info.pGhost==NULL)
	{
		if (HeadPalPix_Ptr) {free(HeadPalPix_Ptr); HeadPalPix_Ptr=0;}
		return true;
	}

	if (Temp1){ delete[] Temp1; Temp1 = NULL; }
	if (Temp2){ delete[] Temp2; Temp2 = NULL; }
	if (Temp3){ delete[] Temp3; Temp2 = NULL; }
	return false;
}


/**
 * ! \brief Initializes or rebuilds the image.
 */
void* bufferImage::Create(unsigned long width, unsigned long height, unsigned long bpp)
{
	if (!Destroy())
		return NULL;

	if ((width == 0) || (height == 0))
	{
		strcpy(info.Error,"bufferImage::Create : width and height must be greater than zero");
		return NULL;
	}



    if(bpp == 8) 
		Header.biClrUsed = 256;
	else
		Header.biClrUsed = 0;
 
    info.scanningWidth = ((((bpp * width) + 31) / 32) * 4);
    // initialize BITMAPINFOHEADER
	Header.biSize = sizeof(BITMAPINFOHEADER); 
    Header.biWidth = width;					
    Header.biHeight = height;				
    Header.biPlanes = 1;					// must be 1
    Header.biBitCount = (unsigned short)bpp;// from parameter
    Header.biCompression = BI_RGB;    
    Header.biSizeImage = info.scanningWidth * height;
    Header.biClrImportant = 0;

	HeadPalPix_Ptr = malloc(GetSize()); // alloc memory block to store our bitmap
    if (!HeadPalPix_Ptr){
		strcpy(info.Error,"bufferImage::Create can't allocate memory");
		return NULL;
	}

	//clear the palette
	RGBQUAD* pal=getPalPtr();
	if (pal) memset(pal,0,getPalSize());
   
    BITMAPINFOHEADER*  lpbi;
	lpbi = (BITMAPINFOHEADER*)(HeadPalPix_Ptr);
    *lpbi = Header;

	info.ptrToImageBits=getBitsPtr();

    return HeadPalPix_Ptr; //return handle to the DIB
}

/**
 * ! \brief Return the pointer to the image pixels
 */
unsigned char* bufferImage::getBitsPtr(unsigned long row)
{ 
	if (HeadPalPix_Ptr)
	{
		if (row) 
		{
			if (row<(unsigned long)Header.biHeight){
				return ((unsigned char*)HeadPalPix_Ptr + *(unsigned long*)HeadPalPix_Ptr + getPalSize() + (info.scanningWidth * row));
			} else {
				return NULL;
			}
		} 
		else 
		{
			return ((unsigned char*)HeadPalPix_Ptr + *(unsigned long*)HeadPalPix_Ptr + getPalSize());
		}
	}
	return NULL;
}

/**
 * ! \brief Add to the RGB input buffer the alpha channel buffer: RGB->RGBA
 */
bool bufferImage::restoreBuffer(unsigned char *buffer, unsigned char alpha, unsigned long bufferSize)
{
	unsigned long rgb = 0;
	if(cpuID >= 3)
	{
		for(unsigned long loop = 0 ; loop < bufferSize; loop +=8)
		{   
#ifdef WIN64 // MMX Instructions not supported by MS Visual Studio in 64-bit
                        // This code should be rewritten, call to memcpy for 3 bytes is
                        // not very efficient...
			memcpy(((unsigned char *)buffer+loop),(getBitsPtr()+(rgb+=3)) ,3);
			*((unsigned char *)buffer+loop+3) = 255;
#else
			_mm_empty();
			*(__m64*)((unsigned char *)buffer+loop) = 
			_mm_setr_pi8(*(getBitsPtr()+(rgb)),	*(getBitsPtr()+(rgb+1)), *(getBitsPtr()+(rgb+2)), alpha,
			             *(getBitsPtr()+(rgb+4)), *(getBitsPtr()+(rgb+5)), *(getBitsPtr()+(rgb+6)), alpha);
			_mm_empty();
			rgb+=6;
#endif
		}
		return true;
	}
	else
	{
		for(unsigned long loop = 0 ; loop < bufferSize; loop +=4)
		{
			memcpy(((unsigned char *)buffer+loop),(getBitsPtr()+(rgb+=3)) ,3);
			*((unsigned char *)buffer+loop+3) = 255;
		}
		return true;
	}
	return false;
}

/**
 * ! \brief Add to the RGB input buffer the alpha channel buffer: RGB->RGBA
 */
bool bufferImage::restoreBuffer(unsigned char *buffer, unsigned char *alpha, unsigned long bufferSize)
{
	unsigned int rgbCount = 0,aCount = 0;
	if(cpuID >= 3)
	{
		for(unsigned long loop = 0 ; loop < bufferSize; loop +=8)
		{   
#ifdef WIN64 // MMX Instructions not supported by MS Visual Studio in 64-bit
                        // This code should be rewritten, call to memcpy for 3 bytes is
                        // not very efficient...
			memcpy(((unsigned char *)buffer+loop),(getBitsPtr()+(rgbCount+=3)) ,3);
			*((unsigned char *)buffer+loop+3) = *(alpha+(aCount+=1));
#else
			_mm_empty();
			*(__m64*)((unsigned char *)buffer+loop) = 
			_mm_setr_pi8(*(getBitsPtr()+(rgbCount)), *(getBitsPtr()+(rgbCount+1)), *(getBitsPtr()+(rgbCount+2)), *(alpha+aCount),
			             *(getBitsPtr()+(rgbCount+4)), *(getBitsPtr()+(rgbCount+5)), *(getBitsPtr()+(rgbCount+6)), *(alpha+aCount+1));
			_mm_empty();
			rgbCount+=6;
			aCount+=2;
#endif
		}
		return true;
	}
	else
	{
		for(unsigned long loop = 0 ; loop < bufferSize; loop +=4)
		{
			memcpy(((unsigned char *)buffer+loop),(getBitsPtr()+(rgbCount+=3)) ,3);
			*((unsigned char *)buffer+loop+3) = *(alpha+(aCount+=1));
			
		}
		return true;
	}
	return false;
}

/**
 * ! \brief Return the pointer to the image pixels
 * previously a conversion to 12 bit is made
 */
unsigned char* bufferImage::get8to12Ptr(unsigned long size)
{ 
	unsigned char* ptr = NULL;
	if (HeadPalPix_Ptr)
	{
		ptr = ((unsigned char*)HeadPalPix_Ptr + *(unsigned long*)HeadPalPix_Ptr + getPalSize());

		if(Header.biBitCount == 8)
		{
			if(mTempSize < size*2)
			{
				delete[] Temp3;
				Temp3 = new unsigned short[size*2];

				mTempSize = size * 2;
			}
			for(unsigned long i = 0; i<size  ; i++)
			{
				Temp3[i] = ( (float)*(ptr+i)/255 ) * 4095;
			}
			return (unsigned char*)&Temp3[0];

		}
		return ptr;
	}


	return NULL;
}

/**
 * ! \brief Transfers the image from an existing source image. The source becomes empty.
 */
bool bufferImage::Transfer(bufferImage &from)
{
	if (!Destroy())
		return false;

	memcpy(&Header,&from.Header,sizeof(BITMAPINFOHEADER));
	memcpy(&info,&from.info,sizeof(IMGINFO));

	HeadPalPix_Ptr = from.HeadPalPix_Ptr;
	memset(&from.Header,0,sizeof(BITMAPINFOHEADER));
	memset(&from.info,0,sizeof(IMGINFO));
	from.HeadPalPix_Ptr =  NULL;
	return true;
}

/**
 * (this) points to the same HeadPalPix_Ptr owned by (*from), the image remains in (*from)
 * but (this) has the access to the pixels.
 */
void bufferImage::copyPtr(bufferImage *from)
{
	if (from)
	{
		memcpy(&Header,&from->Header,sizeof(BITMAPINFOHEADER));
		memcpy(&info,&from->info,sizeof(IMGINFO));
		HeadPalPix_Ptr = from->HeadPalPix_Ptr;
		info.pGhost=from;
	}
}


/**
 * ! \brief Creates an image from a generic input buffer
 * if the image is 12 bits a conversion to 8bits is made
 */
bool bufferImage::CreateFromImgBuffPtr(unsigned char* pArray, unsigned long width,unsigned long height,unsigned long bpp, unsigned long bpl )
{
	if (pArray==NULL) 
		return false;
	if (!((bpp==8)||(bpp==24))) 
		return false;

	if (!Create(width,height,bpp)) 
		return false;

	unsigned char * ptArray = NULL;

	if (bpp<24) 
	{

		const unsigned int bufferSize = (width * height * 2);
		
		if(mTempSize < bufferSize*2)
		{
			delete[] Temp1;
			Temp1 = new unsigned char[bufferSize*2];
			delete[] Temp2;
			Temp2 = new unsigned char[bufferSize*2];
			delete[] Temp3;
			Temp3 = new unsigned short[bufferSize*2];

			mTempSize = bufferSize*2;
		}

		if(cpuID >= 3)
		{
			fastMemcopy ((unsigned char*)&Temp3[0], (unsigned char*)pArray, bufferSize);
		}
		else
		{
			memcpy((unsigned char*)&Temp3[0], (unsigned char*)pArray, bufferSize);
		}

		unsigned long i;
		for(i = 0; i < (width * height); i++)
		{
			Temp3[i] = (((float)Temp3[i]/4095 )) * 255;
		}	
		 
		if(cpuID >= 3)
		{
			fastMemcopy ((unsigned char*)&Temp1[0], (unsigned char*)&Temp3[0], bufferSize);	
		}
		else
		{
			memcpy((unsigned char*)&Temp1[0], (unsigned char*)&Temp3[0], bufferSize);
		}
		
		for(i = 0; i<(width * height); i++) Temp2[i] = Temp1[i*2];

        setGPal();
		ptArray = &Temp2[0];
	}
	else
	{
		ptArray = pArray;
	}

	unsigned char *dst = NULL;
	unsigned char *src = NULL;


	for (unsigned long y = 0; y<height; y++) 
	{
		dst = info.ptrToImageBits + y * info.scanningWidth;
		
		src = ptArray + y * bpl;
		
		memcpy (dst, src, std::min(info.scanningWidth,bpl));	
	}
	return true;
}
