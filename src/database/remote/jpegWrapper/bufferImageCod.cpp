
#include <xip/inventor/remote/jpegWrapper/bufferImage.h>
#include <xip/inventor/remote/jpegWrapper/bufferImageJpeg.h>

/**
 * Encode the memory buffer to the Jpeg format format.
 * \param BuffObj: memory buffer 
 * \return true if is ok
 */
bool bufferImage::encodeBuffer(BuffObj *handledObj)
{
	bufferImageJPG newima;
	newima.copyPtr(this);
	if (newima.encodeBuffer(handledObj))
	{
		return true;
	} 
	else 
	{
		return false;
	}
	
		strcpy(info.Error,"encodeBuffer: Unknown format");
	return false;
}

/**
 * Decode the image from the memory buffer
 * \param buffer: memory buffer
 * \param size: size of buffer
 * \return true if is ok
 */
bool bufferImage::decodeBuffer(unsigned char * buffer, unsigned long size)
{
	MemoryObj file(buffer,size);
	return decodeBuffer(&file);
}

/**
 * Decode the image from BuffObj 
 * \param BuffObj: buffer object
 * \return true if is ok
 */
bool bufferImage::decodeBuffer(BuffObj *handledObj)
{
	bufferImageJPG newima;
	
	if (newima.decodeBuffer(handledObj)) 
	{ 
		 Transfer(newima); return true; 
	}
	
	if (newima.decodeBuffer(handledObj))
	{
		Transfer(newima);
		return true;
	} 
	else 
	{
		return false;
	}
	
	strcpy(info.Error,"decodeBuffer: Error");
	return false;
}
