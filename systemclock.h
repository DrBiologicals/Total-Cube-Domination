//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   systemclock.h
//  Description :   
//  Author      :   
//  Mail        :   
//

#pragma once

#if !defined(__SYSTEMCLOCK_H__)
#define __SYSTEMCLOCK_H__

#include "engine/game/clock.h"

class CSystemClock : public CClock
{
public:
	CSystemClock();
	virtual ~CSystemClock();

	//Initialises input
	virtual bool Initialise();

	//Starts the clock processing
	virtual void Process();

private:
	CSystemClock(const CSystemClock& _kr);
	CSystemClock& operator=(const CSystemClock& _kr);

protected:
	//************************************ MEMBER VARIABLES *******************************
	float32 m_fLastTime;
	float32 m_fCurrentTime;
};

#endif //__SYSTEMCLOCK_H__