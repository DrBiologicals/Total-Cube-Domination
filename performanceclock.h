//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   performanceclock.h
//  Description :   
//  Author      :   
//  Mail        :   
//

#pragma once

#if !defined(__PERFORMANCECLOCK_H__)
#define __PERFORMANCECLOCK_H__

#include "engine/game/clock.h"

class CPerformanceClock : public CClock
{
public:
	CPerformanceClock();
	virtual ~CPerformanceClock();

	//Initialises input
	virtual bool Initialise();

	//Starts the clock processing
	virtual void Process();

private:
	CPerformanceClock(const CPerformanceClock& _kr);
	CPerformanceClock& operator=(const CPerformanceClock& _kr);

protected:
	//************************************ MEMBER VARIABLES *******************************
	int64 m_iLastTime;
	int64 m_iCurrentTime;
	float64 m_dTimeScale;
};

#endif //__PERFORMANCECLOCK_H__