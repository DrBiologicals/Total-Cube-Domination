//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   rulesTest.h
//  Description :   CRulesTest declaration file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifdef _DEBUG

#pragma once

#ifndef __IGFEB10_MODULE_RULESTEST_H__
#define __IGFEB10_MODULE_RULESTEST_H__

// Library Includes

// Local Includes
#include "test.h"

// Types

// Constants

// Prototypes
class CTank;
class CTower;

class CRulesTest: public ITest
{
	// Member Functions
public:
	CRulesTest();
	~CRulesTest();

	void SetUp();
	void TearDown();
	bool RunTest();

	// Functions specific to this class.

	// Check NORMAL mode.
	// Check each weapon/explosion only affects players on the opposite team.
	bool EmpExplosionTest_Normal();
	bool MineExplosionTest_Normal();
	bool PlasmaCannonTest_Normal();

	// Check HARDCORE mode.
	// Check each weapon/explosion affects all players. 
	bool EmpExplosionTest_Hardcore();
	bool MineExplosionTest_Hardcore();
	bool PlasmaCannonTest_Hardcore();

protected:

private:

	// Member Variables
public:

protected:

private:
	CTank* m_pGreenTank;
	CTank* m_pPurpleTank;
	CTower* m_pGreenTower;
	CTower* m_pPurpleTower;

};

#endif // __IGFEB10_MODULE_RULESTEST_H__
#endif // _DEBUG