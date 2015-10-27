//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aiTest.cpp
//  Description :   CAiTest implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifdef _DEBUG

// Library Includes
#include <typeinfo>

// Local Includes
#include "../../Entity structures/Player Objects/AI/aiplayer.h"
#include "../../Entity structures/Terrain Objects/flag.h"
#include "../../Entity structures/Terrain Objects/flagplate.h"
#include "../../defines.h"
#include "../../Entity structures/Player Objects/AI/aistateIdle.h"
#include "../../Entity structures/Player Objects/AI/aistateGetflag.h"
#include "../../Entity structures/Player Objects/AI/aistateCaptureflag.h"
#include "../../Entity structures/Player Objects/AI/aistateProtectflag.h"
#include "../../Entity structures/Player Objects/AI/aistateProtectplayer.h"
#include "../../Entity structures/Player Objects/AI/aistate.h"
#include "../Totalcubedomination.h"
#include "../logging/logmanager.h"
#include "../Graphics and sound/modelmanager.h"
#include "../Graphics and sound/texturemanager.h"

// This Include
#include "aiTest.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAiTest::CAiTest()
: m_pFlag(0)
, m_pFlagPlate(0)
{
	for(int32 iPlayer = 0; iPlayer < 3; ++iPlayer)
	{
		m_apAiPlayers[iPlayer] = 0;
	}
	for(int32 iTank = 0; iTank < 3; ++iTank)
	{
		m_apAiTanks[iTank] = 0;
	}
}

CAiTest::~CAiTest()
{
}

/**
* 
* Create three instances of AI players to test with.
* Create a flag instance to test with.
* 
* @author Rebeccah Cox
* @return void
*/
void
CAiTest::SetUp()
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

	// Create AI players.
	for(int32 iPlayer = 0; iPlayer < 3; ++iPlayer)
	{
		m_apAiPlayers[iPlayer] = new CAIPlayer();
	}
	for(int32 iTank = 0; iTank < 3; ++iTank)
	{
		m_apAiTanks[iTank] = new CTank();
		m_apAiTanks[iTank]->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			m_uiTankTextureID, m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
			m_uiShieldTextureID);
	}

	// Create flag.
	m_pFlag = new CFlag();
	m_pFlagPlate = new CFlagPlate();
}

/**
* 
* Deletes all new objects that were created for the tests. 
* 
* @author Rebeccah Cox
* @return void
*/
void
CAiTest::TearDown()
{
	for(int32 iPlayer = 0; iPlayer < 3; ++iPlayer)
	{
		delete m_apAiPlayers[iPlayer];
		m_apAiPlayers[iPlayer] = 0;
	}
	for(int32 iTank = 0; iTank < 3; ++iTank)
	{
		delete m_apAiTanks[iTank];
		m_apAiTanks[iTank] = 0;
	}

	delete m_pFlag;
	m_pFlag = 0;
	delete m_pFlagPlate;
	m_pFlagPlate = 0;
}

/**
* 
* This test will check:
*	- When an AI player is initialised/created, the current AI state is set to "Idle".
*	- AI players choose the appropriate state, after the Idle state.
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CAiTest::RunTest()
{
	bool bPassedTest = true;

	// Run test to check if AI players are initially set to the "Idle" state.
	if(false == InitialisedToIdleStateTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - Initialised to Idle = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - Initialised to Idle = PASSED", LOG_MESSAGE_TEST);
	}

	// Run test to check if AI players choose "GetFlag" state in correct circumstance.
	if(false == GetFlagStateTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - GetFlag State = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - GetFlag State = PASSED", LOG_MESSAGE_TEST);
	}

	// Run test to check if AI players choose "CaptureFlag" state in correct circumstance.
	if(false == CaptureFlagStateTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - CaptureFlag State = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - CaptureFlag State = PASSED", LOG_MESSAGE_TEST);
	}

	// Run test to check if AI players choose "ProtectFlag" state in correct circumstance.
	if(false == ProtectFlagStateTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - ProtectFlag State = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - ProtectFlag State = PASSED", LOG_MESSAGE_TEST);
	}

	// Run test to check if AI players choose "ProtectPlayer" state in correct circumstance.
	if(false == ProtectPlayerStateTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - ProtectPlayer State = FAILED", LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("AI Test - ProtectPlayer State  = PASSED", LOG_MESSAGE_TEST);
	}

	return (bPassedTest);
}

/**
* 
* One AI player is initialised, the current state of the AI player must be "Idle" to 
*	pass this test. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CAiTest::InitialisedToIdleStateTest()
{
	bool bPassedTest = false;
	TPoint* pPoint = new TPoint();

	// This is not a valid position, but it does not matter in this test. 
	pPoint->vec3Point.x = 0.0f;
	pPoint->vec3Point.y = 0.0f;
	pPoint->vec3Point.z = 0.0f;

	// Initialise the AI player.
	m_apAiPlayers[0]->Initialise(m_apAiTanks[0], 0, TEAM_GREEN);

	// Once the player is initialised, if it's current state is Idle, then the test has passed. 
	// Check the enum value stored in AI player is Idle.
	if(AI_STATE_IDLE == m_apAiPlayers[0]->GetCurrentStateEnum())
	{
		bPassedTest = true;
	}
	// Check the CAIState pointer is pointing to an instance of Idle.
	CAIState* pState = m_apAiPlayers[0]->GetCurrentState();
	if(0 != pState)
	{
		if(typeid(*pState) == typeid(CAIStateIdle))
		{
			bPassedTest = true;
		}
	}

	delete pPoint;
	pPoint = 0;

	return (bPassedTest);
}

/**
* 
* Two AI players, and a flag (opposite teams) are initialised. The flag is on it's flag plate, not held by a player.
* One AI player's state should be set to "GetFlag" in this circumstance. If the state is correct, 
*	the test will pass.
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CAiTest::GetFlagStateTest()
{
	bool bPassedTest = false;
	TPoint* pPoint = new TPoint();

	// This is not a valid position, but it does not matter in this test. 
	pPoint->vec3Point.x = 0.0f;
	pPoint->vec3Point.y = 0.0f;
	pPoint->vec3Point.z = 0.0f;

	// Initialise two AI players to green, one to protect the flag, one to test.
	m_apAiPlayers[0]->Initialise(m_apAiTanks[0], 0, TEAM_GREEN);
	m_apAiPlayers[0]->Initialise(m_apAiTanks[1], 1, TEAM_GREEN);

	// Initialise a flag plate.
	m_pFlagPlate->Initialise(FACE_TOP, 10, 10, TEAM_PURPLE, m_uiFlagplateTextureID, m_uiFlagplateModelID);
	// Initialise a flag to purple.
	m_pFlag->Initialise(0, 0, TEAM_PURPLE, m_pFlagPlate);

	// Process the AI player, so that it goes out of the Idle state, and switches to the 
	//	state it thinks is appropriate. 
	m_apAiPlayers[0]->Process(0.0f);
	m_apAiPlayers[1]->Process(0.0f);

	// Check both AI players' current states.
	// If one AI player's state is now Idle, test has passed.
	if(AI_STATE_IDLE == m_apAiPlayers[0]->GetCurrentStateEnum())
	{
		if(typeid(CAIStateIdle*) == typeid(m_apAiPlayers[0]->GetCurrentState()))
		{
			bPassedTest = true;
		}
	}
	else if(AI_STATE_IDLE == m_apAiPlayers[1]->GetCurrentStateEnum())
	{
		if(typeid(CAIStateIdle*) == typeid(m_apAiPlayers[1]->GetCurrentState()))
		{
			bPassedTest = true;
		}
	}

	delete pPoint;
	pPoint = 0;

	return (bPassedTest);
}

/**
* 
* Two AI players, and a flag (opposite teams) are initialised. The first AI player 
*	is set to protect the flag. The flag is set to be held by the second AI player. 
* The second AI player's state should be set to "CaptureFlag" in this circumstance. 
* If the state is correct, the test will pass.
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CAiTest::CaptureFlagStateTest()
{
	bool bPassedTest = false;

	// Initialise two AI players to TEAM_GREEN.
	m_apAiPlayers[0]->Initialise(m_apAiTanks[0], 0, TEAM_GREEN);
	m_apAiPlayers[1]->Initialise(m_apAiTanks[1], 0, TEAM_GREEN);

	// Initialise a flag plate and flag to TEAM_PURPLE.
	m_pFlagPlate->Initialise(FACE_TOP, 0, 0, TEAM_PURPLE, m_uiFlagplateModelID, m_uiFlagplateTextureID);
	m_pFlag->Initialise(0, 0, TEAM_PURPLE, m_pFlagPlate);

	// Set first player to have the flag.
	m_apAiPlayers[0]->GetTank()->SetFlag(m_pFlag);

	// Call the players' process functions.
	m_apAiPlayers[0]->Process(0.0f);
	m_apAiPlayers[1]->Process(0.0f);

	// Check the second player's current AI state.
	if((AI_STATE_CAPTUREFLAG == m_apAiPlayers[0]->GetCurrentStateEnum()
		&& typeid(CAIStateCaptureFlag) == typeid(m_apAiPlayers[0]->GetCurrentState()))
		|| (AI_STATE_CAPTUREFLAG == m_apAiPlayers[1]->GetCurrentStateEnum()
		&& typeid(CAIStateCaptureFlag) == typeid(m_apAiPlayers[1]->GetCurrentState())))
	{
		// If the current state is CaptureFlag, test has passed.
		bPassedTest = true;
	}

	return (bPassedTest);
}

/**
* 
* One AI player, and a flag (same team) are initialised. The flag is set at it's flag 
*	plate. The AI player's state should be set to "ProtectFlag" in this circumstance. 
* If it is set to this state, the test will pass.
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CAiTest::ProtectFlagStateTest()
{
	bool bPassedTest = false;

	// Initialise an AI player to TEAM_GREEN.
	m_apAiPlayers[0]->Initialise(m_apAiTanks[0], 0, TEAM_GREEN);

	// Initialise a flag plate and flag to TEAM_GREEN.
	m_pFlagPlate->Initialise(FACE_TOP, 0, 0, TEAM_GREEN, m_uiFlagplateModelID, m_uiFlagplateTextureID);
	m_pFlag->Initialise(0, 0, TEAM_GREEN, m_pFlagPlate);

	// Call the player's process function.
	m_apAiPlayers[0]->Process(0.0f);

	// Check the player's current AI state.
	if((AI_STATE_PROTECTFLAG == m_apAiPlayers[0]->GetCurrentStateEnum()
		&& typeid(CAIStateProtectFlag) == typeid(m_apAiPlayers[0]->GetCurrentState()))
		|| (AI_STATE_PROTECTFLAG == m_apAiPlayers[1]->GetCurrentStateEnum()
		&& typeid(CAIStateProtectFlag) == typeid(m_apAiPlayers[1]->GetCurrentState())))
	{
		// If the current state is ProtectFlag, test has passed.
		bPassedTest = true;
	}

	return (bPassedTest);
}

/**
* 
* Three AI players, and a flag (same team) are initialised. The first AI player's state 
*	protects the flag. The flag is set to be held by the second AI player. The third AI 
*	player's state should be set to "ProtectPlayer" in this circumstance. If the state of 
*	the third player is correct, the test will pass.
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CAiTest::ProtectPlayerStateTest()
{
	bool bPassedTest = false;

	// Initialise three AI players to TEAM_GREEN.
	m_apAiPlayers[0]->Initialise(m_apAiTanks[0], 0, TEAM_GREEN);
	m_apAiPlayers[1]->Initialise(m_apAiTanks[1], 0, TEAM_GREEN);
	m_apAiPlayers[2]->Initialise(m_apAiTanks[2], 0, TEAM_GREEN);

	// Initialise a flag to TEAM_GREEN.
	m_pFlagPlate->Initialise(FACE_TOP, 0, 0, TEAM_GREEN, m_uiFlagplateModelID, m_uiFlagplateTextureID);
	m_pFlag->Initialise(0, 0, TEAM_GREEN, m_pFlagPlate);

	// Set the second player to have the flag.
	m_apAiPlayers[1]->GetTank()->SetFlag(m_pFlag);

	// Call all of the players' process functions.
	m_apAiPlayers[0]->Process(0.0f);
	m_apAiPlayers[1]->Process(0.0f);
	m_apAiPlayers[2]->Process(0.0f);

	// Check the player AI states.
	// If player one is set to ProtectFlag:
	if(AI_STATE_PROTECTFLAG == m_apAiPlayers[0]->GetCurrentStateEnum()
		&& typeid(CAIStateProtectFlag) == typeid(m_apAiPlayers[0]->GetCurrentState()))
	{
		// Check if third player's state is ProtectPlayer.
		if(AI_STATE_PROTECTPLAYER == m_apAiPlayers[2]->GetCurrentStateEnum()
		&& typeid(CAIStateProtectPlayer) == typeid(m_apAiPlayers[2]->GetCurrentState()))
		{
			// If it is, the test has passed.
			bPassedTest = true;
		}
	}
	// Else if player three is set to ProtectFlag:
	else if(AI_STATE_PROTECTFLAG == m_apAiPlayers[2]->GetCurrentStateEnum()
		&& typeid(CAIStateProtectFlag) == typeid(m_apAiPlayers[2]->GetCurrentState()))
	{
		// Check if third player's state is ProtectPlayer.
		if(AI_STATE_PROTECTPLAYER == m_apAiPlayers[0]->GetCurrentStateEnum()
		&& typeid(CAIStateProtectPlayer) == typeid(m_apAiPlayers[0]->GetCurrentState()))
		{
			// If it is, the test has passed.
			bPassedTest = true;
		}
	}

	return (bPassedTest);
}

#endif // _DEBUG