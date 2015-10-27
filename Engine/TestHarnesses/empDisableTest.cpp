//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   empDisableTest.cpp
//  Description :   CEmpDisableTest implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

#ifdef _DEBUG

// Local Includes
#include "../../Entity structures/Player Objects/empbomb.h"
#include "../../Entity structures/Player Objects/tank.h"
#include "../../Entity structures/Player Objects/AI/aiplayer.h"
#include "../../Entity structures/Player Objects/AI/aistateDisabled.h"
#include "../../Entity structures/Player Objects/humanplayer.h"
#include "../../Entity structures/Terrain Objects/Tower/tower.h"
#include "../../Entity structures/Terrain Objects/Tower/towerdisabled.h"
#include "../Totalcubedomination.h"
#include "../logging/logmanager.h"
#include "../logging/logdebugoutput.h"
#include "../logging/logfile.h"
#include "../Graphics and sound/modelmanager.h"
#include "../Graphics and sound/texturemanager.h"

// This Include
#include "empDisableTest.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEmpDisableTest::CEmpDisableTest()
: m_pHumanPlayer(0)
, m_pAIPlayer(0)
, m_pTower(0)
, m_pGreenTank(0)
, m_pPurpleTank(0)
, m_pEmp(0)
{
}

CEmpDisableTest::~CEmpDisableTest()
{
}

/**
* 
* Create one instance of a human player, an AI player, and a tower that are 
*	in one team.
* Create one instance of a human player in the opposing team, to fire the 
*	EMP bomb.
* 
* @author Rebeccah Cox
* @return void
*/
void
CEmpDisableTest::SetUp()
{
	// Get models.
	m_uiTankModelID = CModelManager::GetInstance().CreateModel("models/tnk_base.x");
	m_uiTankTextureID = CTextureManager::GetInstance().CreateTexture("textures/tank_purple.png");
	m_uiFlagModelID = CModelManager::GetInstance().CreateModel("models/obj_flag.x");
	m_uiFlagTextureID = CTextureManager::GetInstance().CreateTexture("textures/obj_flag_green.png");
	m_uiFlagplateModelID = CModelManager::GetInstance().CreateModel("models/tile_flagplate.x");
	m_uiFlagplateTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_flagTile_green.png");
	m_uiOverShieldModelID = CModelManager::GetInstance().CreateModel("models/eff_emp.x");
	m_uiOverShieldTextureID = CTextureManager::GetInstance().CreateTexture("textures/eff_emp.png");

	m_pHumanPlayer = new CHumanPlayer();
	m_pAIPlayer = new CAIPlayer();
	m_pTower = new CTower();
	m_pGreenTank = new CTank();
	m_pPurpleTank = new CTank();
	m_pEmp = new CEMPBomb();
}

/**
*
* Deletes all of the newly allocated memory assigned for tests.  
* 
* @author Rebeccah Cox
* @return void
*/
void
CEmpDisableTest::TearDown()
{
	delete m_pHumanPlayer;
	m_pHumanPlayer = 0;
	delete m_pAIPlayer;
	m_pAIPlayer = 0;

	delete m_pTower;
	m_pTower = 0;

	delete m_pGreenTank;
	m_pGreenTank = 0;
	delete m_pPurpleTank;
	m_pPurpleTank = 0;

	delete m_pEmp;
	m_pEmp = 0;
}

/** 
* 
* This test will check:
*	- The AI player is set to "Disable" when hit.
*	- The tower is set to "Disable" when hit.
*	- The human player does not respond to controls/input when hit.
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CEmpDisableTest::RunTest()
{
	bool bPassedTest = true;

	// The AI player is set to appropriate state when hit.
	if(false == AiPlayerDisabledTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("EMP Disable Test - AI Player = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("EMP Disable Test - AI Player = PASSED", LOG_MESSAGE_TEST);
	}
	// The tower is set to appropriate state when hit.
	if(false == TowerDisabledTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("EMP Disable Test - Tower = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("EMP Disable Test - Tower = PASSED", LOG_MESSAGE_TEST);
	}
	// The human player is disabled when hit.
	if(false == HumanPlayerDisabledTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("EMP Disable Test - Human Player = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("EMP Disable Test - Human PLayer = PASSED", LOG_MESSAGE_TEST);
	}

	return (bPassedTest);
}

/**
* 
* The AI player is in the radius of an EMP explosion from the opposing team. 
* The AI player's state should now be set to disabled. The player should be 
*	disabled for two seconds. If both of these factors are true, then the test 
*	has passed. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CEmpDisableTest::AiPlayerDisabledTest()
{
	bool bPassedTest = false;

	// Initialise a green AI player.
	m_pGreenTank->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	m_pAIPlayer->Initialise(m_pGreenTank, 0, TEAM_GREEN);

	// Initialise an EMP, and set the owner to be the purple player.
	m_pPurpleTank->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	m_pEmp->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_pPurpleTank, D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	// Detonate the EMP.
	m_pEmp->Detonate();

	// Process the objects.
	m_pEmp->Process(0.0f);
	m_pGreenTank->Process(0.0f);
	m_pAIPlayer->Process(0.0f);

	// If the AI player's state is now disabled...
	if(AI_STATE_DISABLED == m_pAIPlayer->GetCurrentStateEnum()
		&& typeid(CAIStateDisabled) == typeid(m_pAIPlayer->GetCurrentState()))
	{
		// Test has passed.
		bPassedTest = true;
	}

	return (bPassedTest);
}

/**
* 
* The tower is in the radius of an EMP explosion from the opposing team. 
* The tower's state should now be set to disabled. The tower should be 
*	disabled for four seconds. If both of these factors are true, the the 
*	test has passed. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CEmpDisableTest::TowerDisabledTest()
{
	bool bPassedTest = false;

	// Initialise a tower to TEAM_GREEN.
	//m_pTower->Initialise(FACE_TOP, 0, 0, TEAM_GREEN, 11, 11);

	// Initialise an EMP to TEAM_PURPLE.
	m_pPurpleTank->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	m_pEmp->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_pPurpleTank, D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	// Detonate the EMP.
	m_pEmp->Detonate();

	// Process the tower.
	m_pEmp->Process(0.0f);
	m_pPurpleTank->Process(0.0f);
//	m_pTower->Process(0.0f);

	// If the tower's AI state is disabled...
	if(TOWERAI_STATE_DISABLED == m_pTower->GetCurrentAIStateEnum()
		&& typeid(CTowerDisabled) == typeid(m_pTower->GetCurrentAIState()))
	{
		// Test has passed.
		bPassedTest = true;
	}

	return (bPassedTest);
}

/**
* 
* The human player is in the radius of an EMP explosion from the opposing team. 
* The human player should not respond to any input from the keyboard or controller 
*	while disabled. The player should be disabled for two seconds. If both of 
*	these factors are true, then the test has passed. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CEmpDisableTest::HumanPlayerDisabledTest()
{
	bool bPassedTest = false;

	// Initialise a human player and tank to TEAM_PURPLE.
	m_pPurpleTank->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	m_pHumanPlayer->Initialise(m_pPurpleTank, 0, 0, TEAM_PURPLE);

	// Initialise an EMP to TEAM_GREEN.
	m_pGreenTank->Initialise(D3DXVECTOR3(2.0f, 2.0f, 2.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	m_pEmp->Initialise(D3DXVECTOR3(2.0f, 2.0f, 2.0f), m_pGreenTank, D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	// Detonate the EMP.
	m_pEmp->Detonate();

	// Process the objects.
	m_pEmp->Process(0.0f);
	m_pPurpleTank->Process(0.0f);
	//m_pHumanPlayer->Process(0.0f);

	// If the human player is set to disabled...
	if(true == m_pHumanPlayer->GetIfDisabled())
	{
		// Test has passed.
		bPassedTest = true;
	}

	return (bPassedTest);
}

#endif // _DEBUG