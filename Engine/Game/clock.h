//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   clock.h
//  Description :   Header file for clock class
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

#pragma once

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

class CClock
{
public:
	//Construct and Destruct
	CClock();
	virtual ~CClock();

	//Initialises input
	virtual bool Initialise() = 0;

	//Starts the clock processing
	virtual void Process() = 0;

	//Gets the delta tick
	float32 GetDeltaTick();
	float32 GetTimeElapsed();

private:
	CClock(const CClock& _kr);
	CClock& operator=(const CClock& _kr);

protected:
	//************************************ MEMBER VARIABLES *******************************
	float32 m_fDeltaTick;
	float32 m_fTimeElapsed;
};

#endif //__CLOCK_H__