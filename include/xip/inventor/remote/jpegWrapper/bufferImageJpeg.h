//----------------------------------------------------------------------------------
//! ImageHandler
/*!
// \file    bufferImageJpeg.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// Wrapper for the JPEG library
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------
#if !defined(__BUFFERIMAGEJPEG_H)
#define __BUFFERIMAGEJPEG_H

#include "bufferImage.h"


extern "C" 
{
 #include <jpeglib.h>
 #include <jerror.h>
}

class bufferImageJPG: public bufferImage
{
	public:
		bufferImageJPG();
		~bufferImageJPG();

		bool decodeBuffer(BuffObj * handledObj);
		bool encodeBuffer(BuffObj * handledObj);
 
	private:
		int counter;			// Counter
		unsigned char* ptImage;	//  Image pointer
		bufferImage *img;


    class BuffObjJpg : public jpeg_destination_mgr, public jpeg_source_mgr
	{
	public:
		enum { eBufSize = 4096 };

		BuffObjJpg(BuffObj* pFile)
		{
			memPtr = pFile;

			init_destination = InitDestination;
			empty_output_buffer = EmptyOutputBuffer;
			term_destination = TermDestination;

			init_source = InitSource;
			fill_input_buffer = FillInputBuffer;
			skip_input_data = SkipInputData;
			resync_to_restart = jpeg_resync_to_restart;
			term_source = TermSource;
			next_input_byte = NULL; //*  next byte to read from buffer 
			bytes_in_buffer = 0;	//*  number of bytes in buffer (remaining) 

			bufferPtr = new unsigned char[eBufSize];
		}
		~BuffObjJpg()
		{
			delete [] bufferPtr;
		}

		static void InitDestination(j_compress_ptr cinfo)
		{
			BuffObjJpg* pDest = (BuffObjJpg*)cinfo->dest;
			pDest->next_output_byte = pDest->bufferPtr;
			pDest->free_in_buffer = eBufSize;
		}

		static boolean EmptyOutputBuffer(j_compress_ptr cinfo)
		{
			BuffObjJpg* pDest = (BuffObjJpg*)cinfo->dest;
			if (pDest->memPtr->WriteToMem(pDest->bufferPtr,1,eBufSize)!=(size_t)eBufSize)
				ERREXIT(cinfo, JERR_FILE_WRITE);
			pDest->next_output_byte = pDest->bufferPtr;
			pDest->free_in_buffer = eBufSize;
			return TRUE;
		}

		static void TermDestination(j_compress_ptr cinfo)
		{
			BuffObjJpg* pDest = (BuffObjJpg*)cinfo->dest;
			size_t datacount = eBufSize - pDest->free_in_buffer;
			/* Write any data remaining in the buffer */
			if (datacount > 0) 
			{
				if (!pDest->memPtr->WriteToMem(pDest->bufferPtr,1,datacount))
					ERREXIT(cinfo, JERR_FILE_WRITE);
			}
			pDest->memPtr->Clean();
			/* Make sure the output is OK */
			if (pDest->memPtr->Error()) ERREXIT(cinfo, JERR_FILE_WRITE);
			return;
		}

		static void InitSource(j_decompress_ptr cinfo)
		{
			BuffObjJpg* pSource = (BuffObjJpg*)cinfo->src;
			pSource->isBeginning = TRUE;
		}

		static boolean FillInputBuffer(j_decompress_ptr cinfo)
		{
			size_t nbytes;
			BuffObjJpg* pSource = (BuffObjJpg*)cinfo->src;
			nbytes = pSource->memPtr->ReadFromMem(pSource->bufferPtr,1,eBufSize);
			if (nbytes <= 0)
			{
				if (pSource->isBeginning)	//* Treat empty source error 
					ERREXIT(cinfo, JERR_INPUT_EMPTY);
				WARNMS(cinfo, JWRN_JPEG_EOF);
				
				pSource->bufferPtr[0] = (JOCTET) 0xFF;
				pSource->bufferPtr[1] = (JOCTET) JPEG_EOI;
				nbytes = 2;
			}
			pSource->next_input_byte = pSource->bufferPtr;
			pSource->bytes_in_buffer = nbytes;
			pSource->isBeginning = FALSE;
			return TRUE;
		}

		static void SkipInputData(j_decompress_ptr cinfo, long num_bytes)
		{
			BuffObjJpg* pSource = (BuffObjJpg*)cinfo->src;
			if (num_bytes > 0)
			{
				while (num_bytes > (long)pSource->bytes_in_buffer)
				{
					num_bytes -= (long)pSource->bytes_in_buffer;
					FillInputBuffer(cinfo);
				}
				pSource->next_input_byte += (size_t) num_bytes;
				pSource->bytes_in_buffer -= (size_t) num_bytes;
			}
		}

		static void TermSource(j_decompress_ptr cinfo)
		{
			return;
		}

	private:

		BuffObj  *memPtr;
		unsigned char *bufferPtr;
		bool isBeginning;
	};
};

#endif //__BUFFERIMAGEJPEG_H
