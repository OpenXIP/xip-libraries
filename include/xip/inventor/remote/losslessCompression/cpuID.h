//----------------------------------------------------------------------------------
//! cpuID
/*!
// \file    cpuID.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// To retrieve the cpu's ID
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------
#ifndef _CPUID_H_
#define _CPUID_H_

class cpuID
{
	public:
		cpuID();
		
		/*!
		* \brief Checks the CPU id.
		*
		* \return cpu id.
		*/
 		inline int CPU() 
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

		int cpuID::cpu;	
 
};
#endif // _CPUID_H_
