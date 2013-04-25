//----------------------------------------------------------------------------------
//! cpuID
/*!
// \file    differentials.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// Functions to calculate the symmetric difference between two images
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------
#ifndef _DIFFERENTIALS_H_
#define _DIFFERENTIALS_H_

#include <emmintrin.h>
#include <xmmintrin.h>
#include "functions.h"
#include "cpuID.h"

static cpuID id;

class differentials
{
	public:
		/*!
		* \brief Coumpte a symmetric difference between to input streams 
		*
		* \param fisrt input stream
		* \param second input stream
		* \param symmetric difference
		* \param input size in byte
		*/
		inline void Dif_Enc_Slices_M (unsigned char *input1, unsigned char *input2, unsigned char *output, unsigned int inputSize) //this function works fine
		{
			unsigned char init = 0;
			unsigned int inputPosition = 0;
			 
				do
				{
					output[inputPosition] =  input1[inputPosition] ^ input2[inputPosition];
					inputPosition++; 
				}
				while(inputPosition < inputSize);

		}

		inline void Dif_Dec_Slices_M_32 (unsigned int *input1, unsigned int *input2, unsigned int *output, unsigned int inputSize ) //this function works fine
		{
			unsigned char init = 0;
			unsigned int inputPosition = 0;

			do
			{
				output[inputPosition] = input1[inputPosition] ^ input2[inputPosition];
				inputPosition++;
			}
			while(inputPosition < inputSize);
		}

		/*!
		* \brief Coumpte a symmetric difference between to input streams using MMX instructions
		*
		* \param fisrt input stream
		* \param second input stream
		* \param symmetric difference
		* \param input size in byte
		*/
		inline void SymmetricDifference_Encoder_mmx (unsigned char* pSource1, unsigned char* pSource2, unsigned char* pDest, int bufferLength)
		{
			// 8 bytes are processed in one loop
			int nNumberOfLoops = bufferLength / 8;
    
			_mm_empty();                            // emms

			unsigned int temp = 0;
			for (int i = 0; i < nNumberOfLoops; i++ )
			{ 
				*((__m64*)pDest+temp) = _mm_xor_si64(*((__m64*) pSource1+temp), *((__m64*) pSource2+temp));
				temp += 1;
			}
     
			_mm_empty();                            // emms
		}

		/*// 16 BYTES ALIGNMENT IS REQUIRED
		inline void SymmetricDifference_Encoder_sse (unsigned char* pSource1, unsigned char* pSource2, unsigned char* pDest,unsigned int bufferLength)
		{
			
			if(id.cpu >= 3)
			{
				// 16 bytes are processed in one loop
				int nNumberOfLoops; 
				if(bufferLength % 16 != 0) nNumberOfLoops = (bufferLength / 16)+1;
				else nNumberOfLoops = (bufferLength / 16);
    
				const __m128* ps1_ptr = (__m128*)pSource1;
				const __m128* ps2_ptr = (__m128*)pSource2;
				__m128* dst_ptr = (__m128*)pDest;
    
				_mm_empty();                            // emms

				unsigned int temp = 0;
				for (int i = 0; i < nNumberOfLoops; i++ )
				{ 
					*dst_ptr = _mm_xor_ps(*(ps1_ptr + temp), *(ps2_ptr + temp));
					 
					temp += 1;
				}
     
				_mm_empty();// emms 
			}                       
			else
			{
				unsigned char init = 0;
				unsigned int inputPosition = 0;
			 
				do
				{
					pDest[inputPosition] =  pSource1[inputPosition] ^ pSource2[inputPosition];
					inputPosition++; 
				}
				while(inputPosition < bufferLength);

			}
		}*/

		/*!
		* \brief Coumpte a symmetric difference between to input streams. 
		* When is possible it uses the SSE2 instructions
		*
		* \param fisrt input stream
		* \param second input stream
		* \param symmetric difference
		* \param input size in byte
		*/
		static inline void SymmetricDifference_EncDec(unsigned char * src1, unsigned  char* src2, unsigned  char*dst,  unsigned block_size)
		{
	          
			if(id.cpu >= 3)
			{
				const __m128* ps1_ptr = (__m128*)src1;
				const __m128* ps2_ptr = (__m128*)src2;
				__m128* dst_ptr = (__m128*)dst;
    
				_mm_empty();	// emms

				unsigned int temp = (block_size / 16);
				unsigned int idx = 0;

				for (unsigned int i = 0; i < temp; i++ )
				{ 
					__m128i xmm1 = _mm_loadu_si128((__m128i*)(ps1_ptr + i)); 
					__m128i xmm2 = _mm_loadu_si128((__m128i*)(ps2_ptr + i));
					__m128i xmm3 = _mm_xor_si128(xmm1, xmm2);
					
					_mm_storeu_si128((__m128i*)(dst_ptr + i), xmm3);

				}
				_mm_empty();	// emms

				temp = block_size % 16;
				 
				if( temp > 0 )
				  for(unsigned int i = (block_size - temp); i < block_size; i++)
					 dst[i] = src1[i] ^ src2[i];
			}	
			else
			{
				unsigned char init = 0;
				unsigned int inputPosition = 0;
			 
				do
				{
					dst[inputPosition] =  src1[inputPosition] ^ src2[inputPosition];
					inputPosition++; 
				}
				while(inputPosition < block_size);				
			}/**/
		};

		/*!
		* \brief Coumpte a symmetric difference between to input streams using SSE2 instructions
		*
		* \param fisrt input stream
		* \param second input stream
		* \param symmetric difference
		* \param input size in byte
		* \warning ALL THE STREAMS MUST BE 16 BYTES ALIGNED!!!
		*/
		static inline void SymmetricDifference_Encoder_sse2_Aligned(unsigned char * src1, unsigned  char* src2, unsigned  char*dst,  unsigned block_size)
		{
	          
			const __m128* ps1_ptr = (__m128*)src1;
			const __m128* ps2_ptr = (__m128*)src2;
			__m128* dst_ptr = (__m128*)dst;
    
			_mm_empty();	// emms

			unsigned int temp = (block_size / 16);
			unsigned int idx = 0;

			for (unsigned int i = 0; i < temp; i++ )
			{ 
				__m128i xmm1 = _mm_load_si128((__m128i*)(ps1_ptr + i)); 
				__m128i xmm2 = _mm_load_si128((__m128i*)(ps2_ptr + i));
				__m128i xmm3 = _mm_xor_si128(xmm1, xmm2);
				
				_mm_store_si128((__m128i*)(dst_ptr + i), xmm3);

			}
			_mm_empty();	// emms

			temp = block_size % 16;
			 
			if( temp > 0 )
			  for(unsigned int i = (block_size - temp); i < block_size; i++)
			     dst[i] = src1[i] ^ src2[i];
		};


};
#endif _DIFFERENTIALS_H_