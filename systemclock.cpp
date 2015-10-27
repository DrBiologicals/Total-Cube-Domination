//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   systemclock.cpp
//  Description :   
//  Author      :   
//  Mail        :   
//

// Library Includes
#include <windows.h>

// Local Includes

// This Include
#include "systemclock.h"

// Static Variables

// Static Function Prototypes

// Implementation
CSystemClock::CSystemClock()
: m_fLastTime(0.0f)
, m_fCurrentTime(0.0f)
{
}

CSystemClock::~CSystemClock()
{
}

bool
CSystemClock::Initialise()
{
	return (true);
}

void
CSystemClock::Process()
{
	m_fLastTime = m_fCurrentTime;
		
	m_fCurrentTime = static_cast<float32>(timeGetTime());

	if(m_fLastTime == 0.0f)
	{
		m_fLastTime = m_fCurrentTime;
	}

	m_fDeltaTick = (m_fCurrentTime - m_fLastTime) * 0.001f;

	m_fTimeElapsed += m_fDeltaTick;
}