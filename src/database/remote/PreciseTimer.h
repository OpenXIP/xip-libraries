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
#ifndef _PRECISETIMER_H_
#define _PRECISETIMER_H_

#include <string>
#include <algorithm>
#include <xip/system/standard.h>

#include <xip/system/standard.h>

#ifdef linux
// gettimeofday is the function which return time in microsecond. 
//B'se of interface provided __int64 is used rather than double to store the value of time.

# include <sys/time.h>
# include <iostream>

#endif /* linux */

using namespace std;

//More precise Timer for measuring time intervals in microseconds.
//The performance of this Timer is dependent on the performance of the system.
class CPreciseTimer
{
public:
	//CONSTRUCTOR
	CPreciseTimer();

	bool SupportsHighResCounter();
	void StartTimer();
	void StopTimer();
	int64_t GetTime();

private:
	
	//Auxiliary Functions
	void UpdateElapsed();
	string Int64ToString(int64_t const& ri64, int iRadix);

	//Member variables
	bool m_bRunning;	
	int64_t m_i64Start;
	int64_t m_i64Elapsed;

	//Some auxiliary variables
	int64_t m_i64Counts;

	#ifdef WIN32
	LARGE_INTEGER m_liCount;
		static __int64 sm_i64Freq;
	#else
	// #ifdef linux
		struct timeval  m_liCount;
		struct timezone tz;
	// #endif
	#endif

	//Static Variables
	static bool sm_bInit;
	static bool sm_bPerformanceCounter;

};

inline bool CPreciseTimer::SupportsHighResCounter()
{
	return sm_bPerformanceCounter;
}

//Auxiliary Function
inline void CPreciseTimer::UpdateElapsed()
{

#ifdef WIN32

	if(true == sm_bPerformanceCounter)
	{
		QueryPerformanceCounter(&m_liCount);
		m_i64Counts = ((__int64)m_liCount.HighPart << 32) + (__int64)m_liCount.LowPart;
		//Transform in microseconds
		(m_i64Counts *= 1000000) /= sm_i64Freq;
	}
	else
		//Transform milliseconds to microseconds
		m_i64Counts = (__int64)GetTickCount() * 1000;
	if(m_i64Counts > m_i64Start)
		m_i64Elapsed = m_i64Counts - m_i64Start;
	else
		//Eliminate possible number overflow (0x7fffffffffffffff is the maximal __int64 positive number)
		m_i64Elapsed = (0x7fffffffffffffff - m_i64Start) + m_i64Counts;

#else
// # ifdef linux

	gettimeofday(&m_liCount, &tz);
	m_i64Counts= (int64_t)m_liCount.tv_sec * (1000*1000) + (int64_t)m_liCount.tv_usec;

	if(m_i64Counts > m_i64Start)
		m_i64Elapsed = m_i64Counts - m_i64Start;

/*	else
		//Eliminate possible number overflow (0x7fffffffffffffff is the maximal __int64 positive number)
		m_i64Elapsed = ( (__int64)0x7fffffffffffffff - m_i64Start) + m_i64Counts;*/

// # endif
#endif
}

#endif // _PRECISETIMER_H_


