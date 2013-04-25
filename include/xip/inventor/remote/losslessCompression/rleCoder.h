//----------------------------------------------------------------------------------
//! cpuID
/*!
// \file    rleCoder.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// Run Length Encoder/Decoder
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------
#ifndef __SORADRLE_H_
#define __SORADRLE_H_

#include <emmintrin.h>
#include <xmmintrin.h>

class rleCoder
{
	public:

		rleCoder::rleCoder();

		/*!
		* \brief Compresses a block of data using a Run Length Encoder.
		*
		* \param unsigned char *inSrc  : source
		* \param unsigned int inputSize: size in byte
		* \param unsigned char *outDst : destination (compressed data)
		*/
		int rleCoder::RLE_C( unsigned char *inSrc, unsigned int inputSize, unsigned char *outDst);

		/*!
		* \brief Uncompresses a block of data using a Run Length Decoder.
		*
		* \param unsigned char *inSrc  : source
		* \param unsigned int inputSize: size in byte
		* \param unsigned char *outDst : destination (uncompressed data)
		*/
		void rleCoder::RLE_U( unsigned char *inSrc, unsigned int inputSize, unsigned char *outDst);
	
	private:
		
		/*! 
		* Creates the histogram of the input source
		*/
		void rleCoder::createHistogram( unsigned char *inSrc, unsigned int *histo, unsigned int inputSize )
		{
			unsigned int i = 0;
			if( cpuID >= 3)
			{ 	
				const unsigned mask = 0x00000000;
				__m128i m1 = _mm_set_epi32 (mask, mask, mask, mask);
				for( i = 0; i < 64; ++ i ) _mm_storeu_si128((__m128i*)&histo[i],m1);
				for( i = 0; i < inputSize; ++ i )   ++ histo[ inSrc[ i ] ];
			}
			else
			{
				for(   i = 0; i < 256; ++ i ) 
					histo[ i ] = 0;
				for( i = 0; i < inputSize; ++ i ) 
					++ histo[ inSrc[ i ] ];				
			}
		};

		/*! 
		* Finds the marker. It is the less probable symbol on the source
		* The marker is used during the compression if the coded symbol is repeated. 
		* 
		*/
		inline  unsigned int rleCoder::findTheMarker(unsigned int *histo)
		{
			unsigned int mark = 0;
			for(unsigned int i = 1; i < 256; ++ i )
			{
				if( histo[ i ] < histo[ mark ] ) mark = i;
			}
			return mark;
		};

		/*! 
		* Codes a repeated symbol.
		*/
		inline  int rleCoder::isRepeated(unsigned char *outDst, unsigned int outputPosition, 
									     unsigned int mark, unsigned int cnt)
		{
			for(unsigned int i = 0; i <= cnt; ++ i ) 	
				outDst[ outputPosition ++ ] = mark;

			return outputPosition;
		};

		/*! 
		* Codes a non repeated symbol.
		*/
		inline  int rleCoder::isNotRepeated(unsigned char *outDst, unsigned int outputPosition, 
									        unsigned char sym, unsigned int cnt)
		{
			for(unsigned int i = 0; i <= cnt; ++ i ) outDst[ outputPosition ++ ] = sym;

			return outputPosition;
		};

		/*! 
		* Counter.
		*/
		inline  int rleCoder::counter(unsigned int cnt, unsigned int inputPos)
		{
			return (((cnt & 127) << 8) + inputPos);
		};

		/*! 
		* Write on the output stream a repeated symbol.
		*/
		void isNotRepeatedWrite( unsigned char *outDst, unsigned int *outputPosition,
									 unsigned char mark, unsigned char sym );
		 
		/*! 
		* Write on the output stream a non repeated symbol.
		*/
		void isRepeatedWrite( unsigned char *outDst, unsigned int *outputPosition, unsigned char mark,
						          unsigned char sym, unsigned int cnt );

	protected:
		int cpuID;
};

#endif // __SORADRLE_H_