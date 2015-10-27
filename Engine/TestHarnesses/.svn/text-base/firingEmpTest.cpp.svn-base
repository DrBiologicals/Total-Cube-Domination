//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   firingEmpTest.cpp
//  Description :   CFiringEmpTest implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

#ifdef _DEBUG

// Local Includes
#include "../Totalcubedomination.h"
#include "../logging/logmanager.h"
#include "../logging/logdebugoutput.h"
#include "../logging/logfile.h"
#include "../../Entity structures/Player Objects/tank.h"
#include "../../Entity structures/Player Objects/empbomb.h"
#include "../Totalcubedomination.h"
#include "../logging/logmanager.h"
#include "../Graphics and sound/modelmanager.h"
#include "../Graphics and sound/texturemanager.h"

// This Include
#include "firingEmpTest.h"

// Static Variables

// Static Function Prototypes

// Implementation

CFiringEmpTest::CFiringEmpTest()
: m_pGreenTank(0)
, m_pPurpleTank(0)
, m_pEmp(0)
{
}

CFiringEmpTest::~CFiringEmpTest()
{
}

/**
* 
* Creates instances of all of the objects required for 
*	the tests. 
* 
* @author Rebeccah Cox
* @return void
*/
void
CFiringEmpTest::SetUp()
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
	m_pEmp = new CEMPBomb();
}

/**
* 
* Deletes all of the newly allocated memory used for the tests. 
* 
* @author Rebeccah Cox
* @return void
*/
void
CFiringEmpTest::TearDown()
{
	delete m_pGreenTank;
	m_pGreenTank = 0;
	delete m_pPurpleTank;
	m_pPurpleTank = 0;

	delete m_pEmp;
	m_pEmp = 0;
}

/**
* 
* Calls all of the test functions, and returns true if all of 
*	the tests returned true.
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CFiringEmpTest::RunTest()
{
	bool bPassedTest = true;

	// EMP explodes at correct distance when no object is in the way.
	if(false == EmpDetonationPointTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Firing EMP Test - Detonation Point = FAILED",
														LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Firing EMP Test - Detonation Point = PASSED",
														LOG_MESSAGE_TEST);
	}

	// EMP explodes earlier when an object is in the way.
	if(false == EmpDetonateOnCollisionTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Firing EMP Test - Detonate On Collision = FAILED",
														LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Firing EMP Test - Detonate On Collision = PASSED",
														LOG_MESSAGE_TEST);
	}

	// Only objects inside the radius of the explosion are disabled.
	if(false == EmpExplosionRadiusTest())
	{
		CTotalCubeDomination::GetInstance().LogMessage("Firing EMP Test - Explosion Radius = FAILED",
														LOG_MESSAGE_TEST);
		bPassedTest = false;
	}
	else
	{
		CTotalCubeDomination::GetInstance().LogMessage("Firing EMP Test - Explosion Radius = PASSED",
														LOG_MESSAGE_TEST);
	}

	return (bPassedTest);
}

/*
* One human player is initialised to shoot an EMP round. The EMP 
*	detonates after travelling 12 game units (4 tiles), if it does 
*	not encounter any obstacles. If it denotes at the correct 
*	distance, then the test has passed.
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CFiringEmpTest::EmpDetonationPointTest()
{
	bool bPassedTest = false;

	// Local variable for the starting position of the EMP/tank.
	D3DXVECTOR3 vec3StartPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec3EndPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Initialise a tank to TEAM_PURPLE.
	m_pPurpleTank->Initialise(vec3StartPosition, m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);

	// Shoot an EMP.
	m_pPurpleTank->ShootEMP();
	//temp.
	m_pPurpleTank->GetEMPBomb()->Initialise(m_pPurpleTank->GetPosition(), m_pPurpleTank,
											D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	// Process the emp until it detonates.
	int32 iMaxProcess = 200;
	int32 iCount = 0;
	while(true == m_pPurpleTank->GetEMPBomb()->GetAlive() && iCount < iMaxProcess)
	{
		// Update end position.
		vec3EndPosition.x = m_pPurpleTank->GetEMPBomb()->GetWorldMatrix()._41;
		vec3EndPosition.y = m_pPurpleTank->GetEMPBomb()->GetWorldMatrix()._42;
		vec3EndPosition.z = m_pPurpleTank->GetEMPBomb()->GetWorldMatrix()._43;

		// Process.
		m_pPurpleTank->GetEMPBomb()->Process(0.0f);
		++iCount;
	}

	// Find the length/magnitude of the vector.
	float32 fDistance = sqrt((vec3EndPosition.x * vec3EndPosition.x)
						+ (vec3EndPosition.y * vec3EndPosition.y)
						+ (vec3EndPosition.z * vec3EndPosition.z));

	// If the distance was 12 game units, then the test has passed.
	// (giving a bit of leeway for the 12 unit length).
	if(10 < fDistance && 14 > fDistance)
	{
		bPassedTest = true;
	}

	return (bPassedTest);
}

/*
* Two tanks will be initialised, one to shoot the EMP, and 
*	one to be the obstacle.
* When the EMP round collides with an object before it has reached 
*	the normal detonation point, it will detonate early. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CFiringEmpTest::EmpDetonateOnCollisionTest()
{
	bool bPassedTest = false;

	// Local to store the EMP's last known position.
	D3DXVECTOR3 vec3EMPPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec3TankStartPos = g_atUpRightDirectionVecs[FACE_TOP].vec3Direction * 3.0f;

	D3DXVECTOR3 vec3TankMinPos;
	vec3TankMinPos.x = vec3TankStartPos.x - 1.0f;
	vec3TankMinPos.y = vec3TankStartPos.y - 1.0f;
	vec3TankMinPos.z = vec3TankStartPos.z - 1.0f;

	D3DXVECTOR3 vec3TankMaxPos;
	vec3TankMaxPos.x = vec3TankStartPos.x + 1.0f;
	vec3TankMaxPos.y = vec3TankStartPos.y + 1.0f;
	vec3TankMaxPos.z = vec3TankStartPos.z + 1.0f;

	// Initialise a tank to TEAM_GREEN.
	m_pGreenTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);

	// Initialise a tank to TEAM_PURPLE.
	// Position is set in the path of the first tank's direction vector.
	m_pPurpleTank->Initialise(vec3TankStartPos, m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);

	// Shoot an EMP.
	m_pGreenTank->ShootEMP();

	// Process the EMP until it detonates.
	int32 iMaxProcess = 200;
	int32 iCount = 0;
	while(true == m_pGreenTank->GetEMPBomb()->GetAlive() && iCount < iMaxProcess)
	{
		// Update end position.
		vec3EMPPosition.x = m_pGreenTank->GetEMPBomb()->GetWorldMatrix()._41;
		vec3EMPPosition.y = m_pGreenTank->GetEMPBomb()->GetWorldMatrix()._42;
		vec3EMPPosition.z = m_pGreenTank->GetEMPBomb()->GetWorldMatrix()._43;

		// Process.
		m_pGreenTank->GetEMPBomb()->Process(0.0f);
		++iCount;
	}

	// Check if the EMP detonated at the purple tanks position.
	if(vec3EMPPosition > vec3TankMinPos && vec3EMPPosition < vec3TankMaxPos)
	{
		bPassedTest = true;
	}

	return (bPassedTest);
}

/**
* 
* Two tanks will be initialised. One tank will be inside the area where the EMP explosion should 
*	be. The other tank will be just outside of the explosion radius. 
* If the objects inside the radius are affected, and the objects outside 
*		the radius are not affected, then the test has passed. 
* 
* @author Rebeccah Cox
* @return bool bPassedTest
*/
bool
CFiringEmpTest::EmpExplosionRadiusTest()
{
	bool bPassedTest = true;

	// Positions for objects.
	D3DXVECTOR3 vec3InRadius = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vec3OutOfRadius = D3DXVECTOR3(20.0f, 20.0f, 20.0f);

	// Initialise two tanks.
	m_pGreenTank->Initialise(vec3InRadius, m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	m_pGreenTank->SetCurrentShield(m_pGreenTank->GetMaxShield());
	m_pPurpleTank->Initialise(vec3OutOfRadius, m_uiTankTextureID,
		m_uiTankModelID, TEAM_GREEN, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);
	m_pPurpleTank->SetCurrentShield(m_pPurpleTank->GetMaxShield());

	// temp tank to own emp.
	CTank* pEMPTank = new CTank();
	pEMPTank->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_uiTankTextureID,
		m_uiTankModelID, TEAM_PURPLE, FACE_TOP, m_uiOverShieldModelID, m_uiOverShieldTextureID,
		m_uiShieldTextureID);

	// Initialise an EMP.
	m_pEmp->Initialise(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pEMPTank, D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	// Detonate the EMP.
	m_pEmp->Detonate();

	// Process the objects.
	m_pEmp->Process(0.0f);
	m_pGreenTank->Process(0.0f);
	m_pPurpleTank->Process(0.0f);

	// Check that the objects in the radius were affected.
	if(m_pGreenTank->GetCurrentShield() == m_pGreenTank->GetMaxShield())
	{
		bPassedTest = false;
	}

	// Check that the objects out of the radius were not affected.
	if(m_pPurpleTank->GetCurrentShield() != m_pPurpleTank->GetMaxShield())
	{
		bPassedTest = false;
	}

	delete pEMPTank;
	pEMPTank = 0;

	return (bPassedTest);
}

#endif // _DEBUG