//----------------------------------------------------------------------------------
//! cpuID
/*!
// \file    fastMemTransfer.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// Fast Memory Transfers
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------
#ifndef _FASTMEMTRANSFER_H_
#define _FASTMEMTRANSFER_H_

#include <emmintrin.h>
#include <xmmintrin.h>
  

class fastMemTransfer
{
	public:
 
		inline fastMemTransfer::fastMemTransfer()
		{}
		
		inline fastMemTransfer::~fastMemTransfer()
		{}

		/*!
		* \brief Copy a buffer to another one.
		* When is possible it uses the SSE3 instructions
		*
		* \param source
		* \param destination
		* \param size in byte
		*/
		static inline void fastMemcopy(unsigned char * dst, unsigned char* src, unsigned block_size)
		{
			if( id.cpu >= 3 )
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
			else
			{
				memcpy(dst, src, block_size);
			}

		}

		/*!
		* \brief Copy a buffer to another one using SSE3 instruction  
		*
		* \param source
		* \param destination
		* \param size in byte
		* \warning  DO NOT USE WITH STANDARD LIBRARY
		*/
		static inline void memcopy_sse_Aligned(unsigned char * dst, unsigned char* src, unsigned block_size)
		{
			unsigned char *alignedPtSrc = (unsigned char *)functions::allignData(src);
			unsigned char *alignedPtDst = (unsigned char *)functions::allignData(dst);

			const __m128i* wrd_ptr = (__m128i*)alignedPtSrc;
			const __m128i* wrd_end = (__m128i*)(alignedPtSrc + block_size);
			__m128i* dst_ptr = (__m128i*)alignedPtDst;


			unsigned int nTimes ;
			
			if(block_size % 16 != 0) nTimes = ((int)(block_size/16))+1;
			else nTimes = (block_size/16);
			
			if(block_size < 16) nTimes = 1;
 			
			for(unsigned int i = 0; i < nTimes; i++ )
			{
				__m128i xmm1 = _mm_load_si128(wrd_ptr);
				_mm_store_si128(dst_ptr, xmm1);
				++dst_ptr;
				++wrd_ptr;
			}

		}
		
	
};
#endif //_FASTMEMTRANSFER_H_