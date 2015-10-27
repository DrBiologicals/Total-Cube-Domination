//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   performancecounter.cpp
//  Description :   
//  Author      :   
//  Mail        :   
//

// Library Includes
#include <windows.h>

// Local Includes

// This Include
#include "performanceclock.h"

// Static Variables

// Static Function Prototypes

// Implementation
CPerformanceClock::CPerformanceClock()
: m_iLastTime(0)
, m_iCurrentTime(0)
, m_dTimeScale(0.0)
{
}

CPerformanceClock::~CPerformanceClock()
{
}

bool
CPerformanceClock::Initialise()
{
	LARGE_INTEGER PerformanceFrequency;

	BOOL bPerformanceCounterExists = QueryPerformanceFrequency(&PerformanceFrequency);

	if (bPerformanceCounterExists)
	{
		m_dTimeScale = 1.0f / PerformanceFrequency.QuadPart;
	}

	return (bPerformanceCounterExists != FALSE);
}

void
CPerformanceClock::Process()
{
	m_iLastTime = m_iCurrentTime;

	LARGE_INTEGER PerformanceCounter;

    //DWORD_PTR dwAffinityMask;

    //dwAffinityMask = SetThreadAffinityMask(GetCurrentThread(), 1);

	QueryPerformanceCounter(&PerformanceCounter);

    //SetThreadAffinityMask(GetCurrentThread(), dwAffinityMask);

	m_iCurrentTime = PerformanceCounter.QuadPart;

	if(m_iLastTime == 0)
	{
		m_iLastTime = m_iCurrentTime;
	}

	m_fDeltaTick = static_cast<float32>((m_iCurrentTime - m_iLastTime) * m_dTimeScale);

	m_fTimeElapsed += m_fDeltaTick;
}