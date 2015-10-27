//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   rulesTest.cpp
//  Description :   CRulesTest implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

#ifdef _DEBUG

// Local Includes
#include "../../Entity structures/Terrain Objects/Tower/tower.h"
#include "../../Entity structures/Player Objects/tank.h"
#include "../../Entity structures/Player Objects/empbomb.h"
#include "../../Entity structures/Player Objects/mine.h"
#include "../../Entity structures/Player Objects/bullet.h"
#include "../Totalcubedomination.h"
#include "../Game/gamestate.h"
#include "../Game/rules.h"
#include "../Totalcubedomination.h"
#include "../logging/logmanager.h"
#include "../Graphics and sound/modelmanager.h"
#include "../Graphics and sound/texturemanager.h"

// This Include
#include "rulesTest.h"

// Static Variables

// Static Function Prototypes

// Implementation

CRulesTest::CRulesTest()
: m_pGreenTank(0)
, m_pPurpleTank(0)
, m_pGreenTower(0)
, m_pPurpleTower(0)
{
}

CRulesTest::~CRulesTest()
{
}

/**
* 
* Sets up the new instances of objects needed for all tests.
* 
* @author Rebeccah Cox
* @return void
*/
void
CRulesTest::SetUp()
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

	m_pGreenTank = new CTank();
	m_pPurpleTank = new CTank();
	m_pGreenTower = new CTower();
	m_pPurpleTower = new CTower();
}

/**
* 
* Deletes all new instances of objects created for the tests. 
* 
* @author Rebeccah Cox
* @return void
*/
void
CRulesTest::TearDown()
{
	delete m_pGreenTank;
	m_pGreenTank = 0;
	delete m_pPurpleTank;
	m_pPurpleTank = 0;
	delete m_pGreenTower;
	m_pGreenTower = 0;
	delete m_pPurpleTower;
	m_pPurpleTower = 0;
}

/**
* 
* Calls all of the test functions. 
* If all of the tests pass, then this function returns true. 
* 
* @author Rebeccah Cox
* @return bool bPassed
*/
bool
CRulesTest::RunTest()
{
	bool bPassed = true;

	// Check NORMAL mode.
	// Check each weapon/explosion only affects players on the opposite team.
	if(false == EmpExplosionTest_Normal())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - EMP Explosion NORMAL = FAILED",
														LOG_MESSAGE_TEST);
		bPassed = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - EMP Explosion NORMAL = PASSED",
														LOG_MESSAGE_TEST);
	}

	if(false == MineExplosionTest_Normal())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Mine Explosion NORMAL = FAILED",
														LOG_MESSAGE_TEST);
		bPassed = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Mine Explosion NORMAL = PASSED",
														LOG_MESSAGE_TEST);
	}

	if(false == PlasmaCannonTest_Normal())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Plasma Cannon NORMAL = FAILED",
														LOG_MESSAGE_TEST);
		bPassed = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Plasma Cannon NORMAL = PASSED",
														LOG_MESSAGE_TEST);
	}

	// Check HARDCORE mode.
	// Check each weapon/explosion affects all players. 
	if(false == EmpExplosionTest_Hardcore())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - EMP Explosion HARDCORE = FAILED",
														LOG_MESSAGE_TEST);
		bPassed = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - EMP Explosion HARDCORE = PASSED",
														LOG_MESSAGE_TEST);
	}

	if(false == MineExplosionTest_Hardcore())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Mine Explosion HARDCORE = FAILED",
														LOG_MESSAGE_TEST);
		bPassed = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Mine Explosion HARDCORE = PASSED",
														LOG_MESSAGE_TEST);
	}

	if(false == PlasmaCannonTest_Hardcore())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Plasma Cannon HARDCORE = FAILED",
														LOG_MESSAGE_TEST);
		bPassed = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Plasma Cannon HARDCORE = PASSED",
														LOG_MESSAGE_TEST);
	}

	return (bPassed);
}

/**
* 
* NORMAL game mode.
* Checks that players/towers on the same team ARE NOT affected 
*	by the EMP explosion.
* Checks that players/towers on the opposing team ARE affected 
*	by the EMP explosion. 
* 
* @author Rebeccah Cox
* @return bool bPassed
*/
bool
CRulesTest::EmpExplosionTest_Normal()
{
	bool bPassed = true;

	// Initialise green tank.
	m_pGreenTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Initialise purple tank.
	m_pPurpleTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Intialise green tower.
	//m_pGreenTower->Initialise(FACE_TOP, 0, 0);
	// Initialise purple tower.
	//m_pPurpleTower->Initialise(FACE_TOP, 0, 0);

	// Intialise green EMP.
	CEMPBomb* pEmpBomb = new CEMPBomb();
	pEmpBomb->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_pPurpleTank, D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	// Set the current shields to the max shield.
	m_pGreenTank->SetCurrentShield(m_pGreenTank->GetMaxShield());
	m_pPurpleTank->SetCurrentShield(m_pPurpleTank->GetMaxShield());
	m_pGreenTower->SetCurrentShield(m_pGreenTower->GetMaxShield());
	m_pPurpleTower->SetCurrentShield(m_pPurpleTower->GetMaxShield());

	// Detonate EMP.
	pEmpBomb->Detonate();

	// Check green objects are not damaged.
	if(m_pGreenTank->GetMaxShield() != m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() != m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	// Check purple objects are damaged.
	if(m_pGreenTank->GetMaxShield() == m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() == m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	delete pEmpBomb;
	pEmpBomb = 0;

	return (bPassed);
}

/**
* 
* NORMAL game mode.
* Checks that players/towers on the same team ARE NOT affected 
*	by the mine explosion.
* Checks that players/towers on the opposing team ARE affected 
*	by the mine explosion. 
* 
* @author Rebeccah Cox
* @return bool bPassed
*/
bool
CRulesTest::MineExplosionTest_Normal()
{
	bool bPassed = true;

	// Initialise green tank.
	m_pGreenTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Initialise purple tank.
	m_pPurpleTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Intialise green tower.
	//m_pGreenTower->Initialise(FACE_TOP, 0, 0);
	// Initialise purple tower.
	//m_pPurpleTower->Initialise(FACE_TOP, 0, 0);

	// Intialise purple mine.
	CMine* pMine = new CMine();
	pMine->Initialise(m_pPurpleTank);

	// Set the current shields to the max shield.
	m_pGreenTank->SetCurrentShield(m_pGreenTank->GetMaxShield());
	m_pPurpleTank->SetCurrentShield(m_pPurpleTank->GetMaxShield());
	m_pGreenTower->SetCurrentShield(m_pGreenTower->GetMaxShield());
	m_pPurpleTower->SetCurrentShield(m_pPurpleTower->GetMaxShield());

	// Detonate mine.
	pMine->Explode(5.0f);

	// Check green objects are not damaged.
	if(m_pGreenTank->GetMaxShield() != m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() != m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	// Check purple objects are damaged.
	if(m_pGreenTank->GetMaxShield() == m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() == m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	delete pMine;
	pMine = 0;

	return (bPassed);
}

/**
* 
* NORMAL game mode.
* Checks that players/towers on the same team ARE NOT affected 
*	by a shot from a plasma cannon.
* Checks that players/towers on the opposing team ARE affected 
*	by a shot from a plasma cannon.
* 
* @author Rebeccah Cox
* @return bool bPassed
*/
bool
CRulesTest::PlasmaCannonTest_Normal()
{
	bool bPassed = true;

	// Initialise green tank.
	m_pGreenTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Initialise purple tank.
	m_pPurpleTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Intialise green tower.
	//m_pGreenTower->Initialise(FACE_TOP, 0, 0);
	// Initialise purple tower.
	//m_pPurpleTower->Initialise(FACE_TOP, 0, 0);

	// Intialise green plasma shot (bullet).
	CBullet* pBullet = new CBullet();
	pBullet->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_pGreenTank, g_atUpRightDirectionVecs[FACE_TOP].vec3Direction,
						g_atUpRightDirectionVecs[FACE_TOP].vec3Right);
	pBullet->SetAlive(true);
	pBullet->SetDamage(10.0f);

	// Set the current shields to the max shield.
	m_pGreenTank->SetCurrentShield(m_pGreenTank->GetMaxShield());
	m_pPurpleTank->SetCurrentShield(m_pPurpleTank->GetMaxShield());
	m_pGreenTower->SetCurrentShield(m_pGreenTower->GetMaxShield());
	m_pPurpleTower->SetCurrentShield(m_pPurpleTower->GetMaxShield());

	// Shoot players.
	dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())->GetRules()
								->BulletTankCollision(pBullet, m_pGreenTank);
	pBullet->SetAlive(true);
	dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())->GetRules()
								->BulletTankCollision(pBullet, m_pPurpleTank);

	// NOTE: Need to add the collision for towers. not in rules yet.

	// Check green objects are not damaged.
	if(m_pGreenTank->GetMaxShield() != m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() != m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	// Check purple objects are damaged.
	if(m_pPurpleTank->GetMaxShield() == m_pPurpleTank->GetCurrentShield())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Plasma Cannon: Tank damage not received.",
														LOG_MESSAGE_TEST);
		bPassed = false;
	}
	if(m_pPurpleTower->GetMaxShield() == m_pPurpleTower->GetCurrentShield())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Rules Test - Plasma Cannon: Tower damage not received.",
														LOG_MESSAGE_TEST);
		bPassed = false;
	}

	delete pBullet;
	pBullet = 0;

	return (bPassed);
}

/**
* 
* HARDCORE game mode.
* Checks that players from both teams are affected from any EMP explosion. 
* 
* @author Rebeccah Cox
* @return bool bPassed
*/
bool
CRulesTest::EmpExplosionTest_Hardcore()
{
	bool bPassed = true;

	// Initialise green tank.
	m_pGreenTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Initialise purple tank.
	m_pPurpleTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Intialise green tower.
	//m_pGreenTower->Initialise(FACE_TOP, 0, 0);
	// Initialise purple tower.
	//m_pPurpleTower->Initialise(FACE_TOP, 0, 0);

	// Intialise green EMP.
	CEMPBomb* pEmpBomb = new CEMPBomb();
	pEmpBomb->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_pPurpleTank, -D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	// Set the current shields to the max shield.
	m_pGreenTank->SetCurrentShield(m_pGreenTank->GetMaxShield());
	m_pPurpleTank->SetCurrentShield(m_pPurpleTank->GetMaxShield());
	m_pGreenTower->SetCurrentShield(m_pGreenTower->GetMaxShield());
	m_pPurpleTower->SetCurrentShield(m_pPurpleTower->GetMaxShield());

	// Detonate EMP.
	pEmpBomb->Detonate();

	// Check green objects are damaged.
	if(m_pGreenTank->GetMaxShield() == m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() == m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	// Check purple objects are damaged.
	if(m_pGreenTank->GetMaxShield() == m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() == m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	delete pEmpBomb;
	pEmpBomb = 0;

	return (bPassed);
}

/**
* 
* HARDCORE game mode.
* Checks that players from both teams are affected from any mine explosion. 
* 
* @author Rebeccah Cox
* @return bool bPassed
*/
bool
CRulesTest::MineExplosionTest_Hardcore()
{
	bool bPassed = true;

	// Initialise green tank.
	m_pGreenTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Initialise purple tank.
	m_pPurpleTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Intialise green tower.
	//m_pGreenTower->Initialise(FACE_TOP, 0, 0);
	// Initialise purple tower.
	//m_pPurpleTower->Initialise(FACE_TOP, 0, 0);

	// Intialise purple mine.
	CMine* pMine = new CMine();
	pMine->Initialise(m_pPurpleTank);

	// Set the current shields to the max shield.
	m_pGreenTank->SetCurrentShield(m_pGreenTank->GetMaxShield());
	m_pPurpleTank->SetCurrentShield(m_pPurpleTank->GetMaxShield());
	m_pGreenTower->SetCurrentShield(m_pGreenTower->GetMaxShield());
	m_pPurpleTower->SetCurrentShield(m_pPurpleTower->GetMaxShield());

	// Detonate mine.
	pMine->Explode(5.0f);

	// Check green objects are damaged.
	if(m_pGreenTank->GetMaxShield() == m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() == m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	// Check purple objects are damaged.
	if(m_pGreenTank->GetMaxShield() == m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() == m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	delete pMine;
	pMine = 0;

	return (bPassed);
}

/**
* 
* HARDCORE game mode.
* Checks that players from both teams are affected from a shot from a plasma cannon. 
* 
* @author Rebeccah Cox
* @return bool bPassed
*/
bool
CRulesTest::PlasmaCannonTest_Hardcore()
{
	bool bPassed = true;

	// Initialise green tank.
	m_pGreenTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Initialise purple tank.
	m_pPurpleTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	// Intialise green tower.
	//m_pGreenTower->Initialise(FACE_TOP, 0, 0);
	// Initialise purple tower.
	//m_pPurpleTower->Initialise(FACE_TOP, 0, 0);

	// Intialise green plasma shot (bullet).
	CBullet* pBullet = new CBullet();
	pBullet->Initialise(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_pGreenTank, g_atUpRightDirectionVecs[FACE_TOP].vec3Direction,
						g_atUpRightDirectionVecs[FACE_TOP].vec3Right);

	// Set the current shields to the max shield.
	m_pGreenTank->SetCurrentShield(m_pGreenTank->GetMaxShield());
	m_pPurpleTank->SetCurrentShield(m_pPurpleTank->GetMaxShield());
	m_pGreenTower->SetCurrentShield(m_pGreenTower->GetMaxShield());
	m_pPurpleTower->SetCurrentShield(m_pPurpleTower->GetMaxShield());

	// Shoot players.
	dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())->GetRules()
								->BulletTankCollision(pBullet, m_pGreenTank);
	dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())->GetRules()
								->BulletTankCollision(pBullet, m_pPurpleTank);

	// NOTE: Need to add the collision for towers. not in rules yet.

	// Check green objects are damaged.
	if(m_pGreenTank->GetMaxShield() == m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() == m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	// Check purple objects are damaged.
	if(m_pGreenTank->GetMaxShield() == m_pGreenTank->GetCurrentShield())
	{
		bPassed = false;
	}
	if(m_pGreenTower->GetMaxShield() == m_pGreenTower->GetCurrentShield())
	{
		bPassed = false;
	}

	delete pBullet;
	pBullet = 0;

	return (bPassed);
}

#endif // _DEBUG