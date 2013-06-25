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
#include "PreciseTimer.h"

bool CPreciseTimer::sm_bInit = false;
bool CPreciseTimer::sm_bPerformanceCounter;

#ifdef WIN32

__int64 CPreciseTimer::sm_i64Freq;

#endif

//CONSTRUCTOR
CPreciseTimer::CPreciseTimer() : m_i64Start(0), m_i64Elapsed(0), m_bRunning(false)
{
#ifdef WIN32
	//Only if not already initialized
	if(false == sm_bInit)
	{
		//Initializing some static variables dependent on the system just once
		LARGE_INTEGER liFreq;
		if(TRUE == QueryPerformanceFrequency(&liFreq))
		{
			//Only if the system is supporting High Performance
			sm_i64Freq = ((__int64)liFreq.HighPart << 32) + (__int64)liFreq.LowPart;
			sm_bPerformanceCounter = true;
		}
		else
			sm_bPerformanceCounter = false;

		sm_bInit = true;
	}
#endif //WIN32
//no need to init these for linux / mac
}

void CPreciseTimer::StartTimer()
{
#ifdef WIN32
	if(true == sm_bPerformanceCounter)
	{
		QueryPerformanceCounter(&m_liCount);
		m_i64Start = ((__int64)m_liCount.HighPart << 32) + (__int64)m_liCount.LowPart;
		//Transform in microseconds
		(m_i64Start *= 1000000) /= sm_i64Freq;
	}
	else
	{
		//Transform milliseconds to microseconds
		m_i64Start = (__int64)GetTickCount() * 1000;
	}
	m_bRunning = true;
#else
	gettimeofday(&m_liCount, &tz);
	m_i64Start= (int64_t)m_liCount.tv_sec *(1000*1000)+ (int64_t)m_liCount.tv_usec;
	m_bRunning = true;
#endif
}

void CPreciseTimer::StopTimer()
{
	UpdateElapsed();
	m_bRunning = false;
}

int64_t CPreciseTimer::GetTime()
{
	if(true == m_bRunning)
		UpdateElapsed();
	return m_i64Elapsed;
}

string CPreciseTimer::Int64ToString(int64_t const& ri64, int iRadix=10)
{
	bool bNeg = (ri64 < 0);
	int64_t i64 = ri64;
	string ostrRes;
	bool bSpecial = false;
	if(true == bNeg)
	{
		i64 = -i64;
		if(i64 < 0)
			//Special case number -9223372036854775808 or 0x8000000000000000
			bSpecial = true;
		ostrRes.append(1, '-');
	}
	int iR;
	do
	{
		iR = i64 % iRadix;
		if(true == bSpecial)
			iR = -iR;
		if(iR < 10)
			ostrRes.append(1, '0' + iR);
		else
			ostrRes.append(1, 'A' + iR - 10);
		i64 /= iRadix;
	}
	while(i64 != 0);
	//Reverse the string
	string::iterator it = ostrRes.begin();
	if(bNeg)
		it++;
	reverse(it, ostrRes.end());
	return ostrRes;
}

