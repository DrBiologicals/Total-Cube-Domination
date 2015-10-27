//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   testManager.cpp
//  Description :   CTestManager implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

#ifdef _DEBUG

// Local Includes
#include "aiTest.h"
#include "empDisableTest.h"
#include "firingEmpTest.h"
#include "flagTest.h"
#include "rulesTest.h"
#include "../Totalcubedomination.h"
#include "../logging/logmanager.h"
#include "../logging/logdebugoutput.h"
#include "../logging/logfile.h"
#include "../Graphics and sound/renderer.h"
#include "../Viewport/viewport.h"
#include "../Graphics and sound/modelmanager.h"
#include "../Graphics and sound/texturemanager.h"

// This Include
#include "testManager.h"

// Static Variables

// Static Function Prototypes

// Implementation

CTestManager::CTestManager()
{
}

CTestManager::~CTestManager()
{
}

/**
* 
* Creates an instance of each test harness and calls each harness' SetUp() function 
*	to prepare the test harnesses before running any tests.
* 
* @author Rebeccah Cox
* @return void
*/
void
CTestManager::SetUp()
{
	// Create an AI state change test harness.
	ITest* pTest = new CAiTest();
	pTest->SetUp();
	m_vecpTests.push_back(pTest);

	// Create an EMP disabling tanks/towers test harness.
	pTest = new CEmpDisableTest();
	pTest->SetUp();
	m_vecpTests.push_back(pTest);

	// Create an EMP firing test harness.
	pTest = new CFiringEmpTest();
	pTest->SetUp();
	m_vecpTests.push_back(pTest);

	// Create a flag functionality test harness.
	pTest = new CFlagTest();
	pTest->SetUp();
	m_vecpTests.push_back(pTest);

	// Create a normal vs. hardcore rules test harness.
	pTest = new CRulesTest();
	pTest->SetUp();
	m_vecpTests.push_back(pTest);

	// Set the temporary pointer to zero.
	pTest = 0;
}

/**
* 
* Calls the TearDown() function for each of the active test harnesses.
* 
* Deletes all of the new instances that were created in the SetUp() function, and sets 
*	the pointers to zero. 
* 
* @author Rebeccah Cox
* @return void
*/
void
CTestManager::TearDown()
{
	// Clean up draw queue to stop deleted objects from trying to be drawn.
	if(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0))
	{
		CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->ClearRenderQueue();
	}
	if(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(1))
	{
		CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(1)->ClearRenderQueue();
	}
	if(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(2))
	{
		CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(2)->ClearRenderQueue();
	}
	if(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(3))
	{
		CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(3)->ClearRenderQueue();
	}

	for(uint32 iTest = 0; iTest < m_vecpTests.size(); ++iTest)
	{
		delete m_vecpTests[iTest];
		m_vecpTests[iTest] = 0;
	}

	CModelManager::GetInstance().Clear();
	CTextureManager::GetInstance().Clear();
}

/**
* 
* Calls the RunTest() function on each of the test harnesses.
* Returns true if ALL of the test harnesses passed.
* Also ouputs a logging message as to which tests passed and failed.
* 
* @author Rebeccah Cox
* @return bool bPassedTest;
*/
bool
CTestManager::RunTest()
{
	bool bPassedTest = true;

	for(uint32 iTestNum = 0; iTestNum < m_vecpTests.size(); ++iTestNum)
	{
		if(false == m_vecpTests[iTestNum]->RunTest())
		{
			bPassedTest = false;
		}
		m_vecpTests[iTestNum]->TearDown();
	}

	if(true == bPassedTest)
	{
		CTotalCubeDomination::GetInstance().LogMessage("TestManager: All tests passed.", LOG_MESSAGE_TEST);
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("TestManager: Not all tests passed.", LOG_MESSAGE_TEST);
	}

	return (bPassedTest);
}

#endif // _DEBUG