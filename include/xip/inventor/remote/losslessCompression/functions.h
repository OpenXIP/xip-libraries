//----------------------------------------------------------------------------------
//! cpuID
/*!
// \file    functions.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// Function used by the lossless library
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <vector>

using namespace std;

class functions
{
	public:

		inline static void *allignData(void *data)
		{
		  return (void *)(((int)data + 15) &~ 0x0F);
		}
		
		/*!
		* \brief Checks the CPU id.
		*
		* \return cpu id.
		*/
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

			if( isSse3 & 0x0000200 ) return 5;   // SSSE3
			if( isSse3 & 0x0000001 )  return 4;  // SSE3
			if( info & 0x4000000 )    return 3;  // SSE2
			if( info & 0x2000000 )     return 2; // SSE
			if( info & 0x0800000 )     return 1; // MMX
			
			return 0;  // Legacy
			  
		}

		/*!
		* \brief Resizes the size of the input vector if smaller than size. 
		*
		* \param vector to check
		* \param size
		*/
		inline static void checkSize(vector <unsigned char> *vect, unsigned int size)
		{
			if (vect->size() < size) vect->resize(size);
		}

		/*!
		* \brief Resizes the size of the input vector if smaller than size. 
		*
		* \param vector to check
		* \param size
		*/
		inline static void checkSize(vector <unsigned short> *vect, unsigned int size)
		{
			if (vect->size() < size) vect->resize(size);
		}

		/*************************************************************************
		* TIMER    (!!!copy paste from internet!!!)
		*************************************************************************/
		string Int64ToString(__int64 const& ri64, int iRadix=10);

		/*!
		* \brief Write a unsigned int to a byte stream
		*
		* \param integer to write
		* \param byte stream
		*/

		inline void WriteUInt32(const unsigned int x, unsigned char *b )
		{
		  *b =  ((x>>24)&255); b+=1;
		  *b =  ((x>>16)&255); b+=1;
		  *b =  ((x>>8)&255); b+=1;
		  *b =  (x&255); b+=1;
		}

		/*!
		* \brief Read a unsigned int from a BYTE stream
		*
		* \param byte stream 
		* \return unsigned int read from BYTE stream 
		*/
		inline unsigned int ReadUInt32(const unsigned char *buff )
		{
		  unsigned int a,b,c,d;
		  a = (((unsigned int)*buff)<<24);
		  b = (((unsigned int)*(buff+=1))<<16);
		  c = (((unsigned int)*(buff+=1))<<8);
		  d = (unsigned int)*(buff+=1);
		  return  a+b+c+d;
		}
};
#endif // _FUNCTIONS_H_
