//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   empDisableTest.h
//  Description :   CEmpDisableTest declaration file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifdef _DEBUG

#pragma once

#ifndef __IGFEB10_MODULE_EMPDISABLETEST_H__
#define __IGFEB10_MODULE_EMPDISABLETEST_H__

// Library Includes

// Local Includes
#include "test.h"

// Types

// Constants

// Prototypes
class CEMPBomb;
class CAIPlayer;
class CHumanPlayer;
class CTower;
class CTank;

class CEmpDisableTest: public ITest
{
	// Member Functions
public:
	CEmpDisableTest();
	~CEmpDisableTest();

	void SetUp();
	void TearDown();
	bool RunTest();

	// Functions specific to this class.
	// The AI player is set to appropriate state when hit.
	bool AiPlayerDisabledTest();
	// The tower is set to appropriate state when hit.
	bool TowerDisabledTest();
	// The human player is disabled when hit.
	bool HumanPlayerDisabledTest();

protected:

private:

	// Member Variables
public:

protected:

private:
	CHumanPlayer* m_pHumanPlayer;
	CAIPlayer* m_pAIPlayer;
	CTower* m_pTower;
	CTank* m_pGreenTank;
	CTank* m_pPurpleTank;
	CEMPBomb* m_pEmp;

};

#endif // __IGFEB10_MODULE_EMPDISABLETEST_H__
#endif // _DEBUG