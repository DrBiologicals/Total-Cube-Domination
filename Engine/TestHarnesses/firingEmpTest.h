//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   firingEmpTest.h
//  Description :   CFiringEmpTest declaration file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifdef _DEBUG

#pragma once

#ifndef __IGFEB10_MODULE_FIRINGEMPTEST_H__
#define __IGFEB10_MODULE_FIRINGEMPTEST_H__

// Library Includes

// Local Includes
#include "test.h"

// Types

// Constants

// Prototypes
class CTower;

class CFiringEmpTest: public ITest
{
	// Member Functions
public:
	CFiringEmpTest();
	~CFiringEmpTest();

	void SetUp();
	void TearDown();
	bool RunTest();

	// Functions specific to this class.
	// EMP explodes at correct distance when no object is in the way.
	bool EmpDetonationPointTest();
	// EMP explodes earlier when an object is in the way.
	bool EmpDetonateOnCollisionTest();
	// Only objects inside the radius of the explosion are disabled.
	bool EmpExplosionRadiusTest();

protected:

private:

	// Member Variables
public:

protected:

private:
	CTank* m_pGreenTank;
	CTank* m_pPurpleTank;
	CEMPBomb* m_pEmp;

};

#endif // __IGFEB10_MODULE_FIRINGEMPTEST_H__
#endif // _DEBUG