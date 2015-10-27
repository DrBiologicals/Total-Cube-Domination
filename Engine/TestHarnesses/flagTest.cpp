//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flagTest.cpp
//  Description :   CFlagTest implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

#ifdef _DEBUG

// Local Includes
#include "../../Entity structures/Player Objects/tank.h"
#include "../../Entity structures/Player Objects/humanplayer.h"
#include "../../Entity structures/Terrain Objects/flag.h"
#include "../../Entity structures/Terrain Objects/flagplate.h"
#include "../Totalcubedomination.h"
#include "../Game/gamestate.h"
#include "../Game/rules.h"
#include "../Totalcubedomination.h"
#include "../logging/logmanager.h"
#include "../Graphics and sound/modelmanager.h"
#include "../Graphics and sound/texturemanager.h"

// This Include
#include "flagTest.h"

// Static Variables

// Static Function Prototypes

// Implementation

CFlagTest::CFlagTest()
: m_pGreenPlayer(0)
, m_pPurplePlayer(0)
, m_pGreenTank(0)
, m_pPurpleTank(0)
, m_pFlag(0)
, m_pFlagPlate(0)
{
}

CFlagTest::~CFlagTest()
{
}

/**
* 
* Create all of the objects that the tests require. 
* 
* @author Rebeccah Cox
* @return void
*/
void
CFlagTest::SetUp()
{
	// Get models.
	m_uiTankModelID = CModelManager::GetInstance().CreateModel("models/tnk_base.x");
	m_uiTankTextureID = CTextureManager::GetInstance().CreateTexture("textures/tank_purple.png");
	m_uiFlagModelID = CModelManager::GetInstance().CreateModel("models/obj_flag.x");
	m_uiFlagTextureID = CTextureManager::GetInstance().CreateTexture("textures/obj_flag_green.png");
	m_uiFlagplateModelID = CModelManager::GetInstance().CreateModel("models/tile_flagplate.x");
	m_uiFlagplateTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_flagTile_green.png");
	m_uiOverShieldModelID = CModelManager::GetInstance().CreateModel("models/eff_emp.x");
	m_uiOverShieldTextureID = CTextureManager::GetInstance().CreateTexture("textures/tank_overshield.png");
	m_uiShieldTextureID = CTextureManager::GetInstance().CreateTexture("textures/tank_shield.png");

	m_pGreenPlayer = new CHumanPlayer();
	m_pPurplePlayer = new CHumanPlayer();

	m_pGreenTank = new CTank();
	m_pPurpleTank = new CTank();

	m_pFlag = new CFlag();
	m_pFlagPlate = new CFlagPlate();
}

/**
* 
* Delete all of the objects that were created for the tests. 
* 
* @author Rebeccah Cox
* @return void
*/
void
CFlagTest::TearDown()
{
	delete m_pGreenPlayer;
	m_pGreenPlayer = 0;
	delete m_pPurplePlayer;
	m_pPurplePlayer = 0;

	delete m_pGreenTank;
	m_pGreenTank = 0;
	delete m_pPurpleTank;
	m_pPurpleTank = 0;

	delete m_pFlag;
	m_pFlag = 0;
	delete m_pFlagPlate;
	m_pFlagPlate = 0;
}

/**
* 
* Runs all of the tests in this class, and returns true if all of the tests return true. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CFlagTest::RunTest()
{
	bool bPassedTest = true;

	// Only players from opposing team can pick up flag.
	if(false == PlayerPickUpFlagTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Flag Test - Pick Up Flag = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Flag Test - Pick Up Flag = PASSED", LOG_MESSAGE_TEST);
	}

	// When player carrying flag dies, the flag stays at the last known position.
	if(false == FlagPositionWhenDroppedTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Flag Test - Position When Dropped = FAILED",
														LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Flag Test - Position When Dropped = PASSED",
														LOG_MESSAGE_TEST);
	}

	// When a player from the same team runs over flag (not at base), flag is returned to base.
	if(false == FlagReturnedToBaseTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Flag Test - Returned To Base = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Flag Test - Returned To Base = PASSED", LOG_MESSAGE_TEST);
	}

	return (bPassedTest);
}

/**
* 
* Checks if a flag initialised at it's base can be picked 
*	up by a player from the opposing team, and does nothing 
*	if a player from the same team collides with it. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CFlagTest::PlayerPickUpFlagTest()
{
	bool bPassedTest = false;

	// Initialise a green flag and flag plate.
	m_pFlagPlate->Initialise(FACE_TOP, 7, 7, TEAM_GREEN, m_uiFlagplateTextureID, m_uiFlagplateModelID);
	m_pFlag->Initialise(m_uiFlagModelID, m_uiFlagTextureID, TEAM_GREEN, m_pFlagPlate);

	// Initialise a purple player.
	m_pPurpleTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);

	// Cause a collsion between the player and the flag.
	dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())->GetRules()
								->GrabFlag(m_pPurpleTank, m_pFlag);

	// Check the player now has the flag.
	if(true == m_pPurpleTank->HasFlag())
	{
		bPassedTest = true;
	}

	return (bPassedTest);
}

/**
* 
* Checks that if a player is carrying a flag, the flag stays 
*	at the last position that the player was at. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CFlagTest::FlagPositionWhenDroppedTest()
{
	bool bPassedTest = false;

	// Initialise a purple player.
	m_pPurpleTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);

	// Initialise a green flag.
	m_pFlagPlate->Initialise(FACE_TOP, 7, 7, TEAM_GREEN, m_uiFlagplateTextureID, m_uiFlagplateModelID);

	m_pFlag->Initialise(m_uiFlagModelID, m_uiFlagTextureID, TEAM_GREEN, m_pFlagPlate);

	// Set the player to have the flag.
	m_pPurpleTank->SetFlag(m_pFlag);

	// Process tank, so that flag position updates.
	m_pPurpleTank->Process(0.0f);

	// Store the player position.
	const D3DXVECTOR3* pPosition = &m_pPurpleTank->GetPosition();

	// Kill the player.
	m_pPurpleTank->SetAlive(false);

	// Process the flag.
	m_pFlag->Process(0.0001f);

	D3DXVECTOR3 pFlagPosition = m_pFlag->GetPosition();
	// Check that the flag stays at the same position.
	//if(m_pFlag->GetPosition() == pPosition)
	if(pFlagPosition.x == pPosition->x
		&& pFlagPosition.y == pPosition->y
		&& pFlagPosition.z == pPosition->z)
	{
		bPassedTest = true;
	}

	return (bPassedTest);
}

/**
* 
* Checks that when a flag is not at it's flag plate (not carried), and a player 
*	from the same team collides with it, then it is teleported back to the flag 
*	plate. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CFlagTest::FlagReturnedToBaseTest()
{
	bool bPassedTest = false;

	// Initialise a green flag and flag plate.
	m_pFlagPlate->Initialise(FACE_TOP, 7, 7, TEAM_GREEN, m_uiFlagplateTextureID, m_uiFlagplateModelID);
	m_pFlag->Initialise(m_uiFlagModelID, m_uiFlagTextureID, TEAM_GREEN, m_pFlagPlate);

	// Initialise a green player.
	m_pGreenTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID, m_uiTankModelID, TEAM_GREEN, FACE_TOP,
								m_uiOverShieldModelID, m_uiOverShieldTextureID, m_uiShieldTextureID);

	// Place the flag at a position not on the flag plate.
	m_pFlag->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// Cause the player and flag to collide.
	dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())->GetRules()
								->GrabFlag(m_pGreenTank, m_pFlag);

	// Check that the flag has spawned back at it's flag plate position.
	if(true == m_pFlag->IsFlagOnFlagPlate())
	{
		bPassedTest = true;
	}

	return (bPassedTest);
}

#endif // _DEBUG