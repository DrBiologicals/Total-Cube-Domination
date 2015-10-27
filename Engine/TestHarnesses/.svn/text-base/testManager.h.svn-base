//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   testManager.h
//  Description :   CTestManager declaration file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifdef _DEBUG

#pragma once

#ifndef __IGFEB10_MODULE_TESTMANAGER_H__
#define __IGFEB10_MODULE_TESTMANAGER_H__

// Library Includes
#include <vector>

// Local Includes
#include "test.h"

// Types

// Constants

// Prototypes

class CTestManager: public ITest
{
	// Member Functions
public:
	CTestManager();
	~CTestManager();

	void SetUp();
	void TearDown();
	bool RunTest();

protected:

private:

	// Member Variables
public:

protected:

private:
	std::vector<ITest*> m_vecpTests;

};

#endif // __IGFEB10_MODULE_TESTMANAGER_H__
#endif // _DEBUG