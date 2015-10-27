//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flagTest.h
//  Description :   CFlagTest declaration file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifdef _DEBUG

#pragma once

#ifndef __IGFEB10_MODULE_FLAGTEST_H__
#define __IGFEB10_MODULE_FLAGTEST_H__

// Library Includes

// Local Includes
#include "test.h"

// Types

// Constants

// Prototypes
class CTank;
class CHumanPlayer;
class CFlag;
class CFlagPlate;

class CFlagTest: public ITest
{
	// Member Functions
public:
	CFlagTest();
	~CFlagTest();

	void SetUp();
	void TearDown();
	bool RunTest();

	// Functions specific to this class. 
	// Only players from opposing team can pick up flag.
	bool PlayerPickUpFlagTest();
	// When player carrying flag dies, the flag stays at the last known position.
	bool FlagPositionWhenDroppedTest();
	// When a player from the same team runs over flag (not at base), flag is returned to base.
	bool FlagReturnedToBaseTest();

protected:

private:

	// Member Variables
public:

protected:

private:
	CHumanPlayer* m_pGreenPlayer;
	CHumanPlayer* m_pPurplePlayer;

	CTank* m_pGreenTank;
	CTank* m_pPurpleTank;

	CFlag* m_pFlag;
	CFlagPlate* m_pFlagPlate;

};

#endif // __IGFEB10_MODULE_FLAGTEST_H__
#endif // _DEBUG