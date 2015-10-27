// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   powerupmanager.cpp
//  Description :   powerupmanager.cppfor implementation of powerupmanager.h
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "powerup.h"
#include "../../../engine/graphics and sound/renderer.h"
#include "../../../engine/graphics and sound/modelmanager.h"
#include "../../../engine/graphics and sound/texturemanager.h"
#include "../../../engine/totalcubedomination.h"

// This Includes
#include "powerupmanager.h"

// Static Variables
CPowerUpManager* CPowerUpManager::s_pInstance = 0;

// Static Function Prototypes

// Implementation

/**
* 
* Constructor.
* 
* @author Rebeccah Cox
*/
CPowerUpManager::CPowerUpManager()
: m_pPowerUp(0)
, m_fSpawnPowerUpTimer(0.0f)
, m_uiPowerUpModelID(0)
, m_uiInvisPowerUpTextureID(0)
, m_uiOverShieldPowerUpTextureID(0)
{
}

/**
* 
* Destructor.
* 
* @author Rebeccah Cox
*/
CPowerUpManager::~CPowerUpManager()
{
	delete m_pPowerUp;
	m_pPowerUp = 0;
}

/**
* 
* Static function. Returns the current instance of CPowerUpManager.
* If there is no current instance, then one is created.
* 
* @author Rebeccah Cox
* @return CPowerUpManager& s_pInstance.
*/
CPowerUpManager&
CPowerUpManager::GetInstance()
{
	if (!s_pInstance)
	{
		s_pInstance = new CPowerUpManager;
	}

	return (*s_pInstance);
}

/**
* 
* Static function. Deletes the current instance of CPowerUpManager and sets the 
*	member pointer to zero.
* 
* @author Rebeccah Cox
*/
void
CPowerUpManager::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = 0;
}

/**
* 
* Creates the power-up model and stores the ID number. 
* Creates the power-up textures and stores the ID numbers.
* Sets the power-up spawn locations to the TPoint values passed in.
* 
* @author Rebeccah Cox
* @param TPoint* _ptSpawnLocationOne - first power-up spawn location.
* @param TPoint* _ptSpawnLocationTwo - second power-up spawn location.
* @return bool - true if the textures and model creation are successful.
*/
bool
CPowerUpManager::Initialise()
{
	// Create model.
	m_uiPowerUpModelID = CModelManager::GetInstance().CreateModel("models/obj_powerup.x");
	if(BAD_ID == m_uiPowerUpModelID)
	{
		return (false);
	}

	// Create invisibility texture.
    m_uiInvisPowerUpTextureID = CTextureManager::GetInstance().CreateTexture("textures/obj_powerup_invisible.png");
	if(BAD_ID == m_uiInvisPowerUpTextureID)
	{
		return (false);
	}

	// Create over-shield texture.
    m_uiOverShieldPowerUpTextureID = CTextureManager::GetInstance().CreateTexture("textures/obj_powerup_overshield.png");
	if(BAD_ID == m_uiOverShieldPowerUpTextureID)
	{
		return (false);
	}

	// Start the power up spawn timer, by setting it to zero.
	InitialiseRandomPowerup();

	return (true);
}

/**
* 
* Calls CPowerUp's Process(..) function.
* If the current power-up is not active (has been picked up), then 
*	the m_fSpawnPowerUpTimer increments until it reaches the MAX_SPAWN_TIME.
* When it does, a new random power-up is initialised.
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
*/
void
CPowerUpManager::Process(float32 _fDeltaTick)
{
	if (m_pPowerUp)
	{
		m_pPowerUp->Process(_fDeltaTick);
	
		if(m_pPowerUp->IsActive() == false)
		{
			m_fSpawnPowerUpTimer += _fDeltaTick;

			if(m_fSpawnPowerUpTimer > 10.0f)
			{
				m_fSpawnPowerUpTimer = 0.0f;

				InitialiseRandomPowerup();
			}
		}
	}
}

/**
* 
* Randomly selects a number representing a power-up (0 = Invisibility or 1 = Over-Shield).
* Randomly selects a spawn location ID (index number 0 or 1 in m_atPowerUpSpawn array).
* Calls CPowerUp's Initialise function with the selected power-up type and location.
* 
* @author Rebeccah Cox
* @return bool - true if the CPowerUp Initialise(..) function returns true.
*/
bool
CPowerUpManager::InitialiseRandomPowerup()
{
	if (m_vecSpawnLocations.empty()) return (false);

	// Local varaible to store the texture ID.
	uint32 uiTextureID = 0;

	// Get a random power-up and location ID.
	uint32 uiRandPowerUp = rand() % 2;
	uint32 uiRandLocation = rand() % static_cast<uint32>(m_vecSpawnLocations.size());

	if (m_pPowerUp)
    {
        delete m_pPowerUp;
        m_pPowerUp = 0;
        m_pPowerUp = new CPowerUp;
    }
    else
    {
        m_pPowerUp = new CPowerUp;
    }

	// Work out which texture to use.
	// If the power-up ID is 0, it is invisibility.
	if(uiRandPowerUp == 0)
	{
		uiTextureID = m_uiInvisPowerUpTextureID;
	}
	// Else the power-up is 1, which is the over-shield.
	else
	{
		uiTextureID = m_uiOverShieldPowerUpTextureID;
	}

	// Initialise the power-up with the random type and location.
	if(false == m_pPowerUp->Initialise(m_vecSpawnLocations[uiRandLocation].vec3Point, static_cast<EPowerUpType>(uiRandPowerUp), 
		m_vecSpawnLocations[uiRandLocation].eFacePosition, m_uiPowerUpModelID, uiTextureID))
	{
		return (false);
	}

	//// Initialise the power-up with the random type and location.
	//if(false == m_pPowerUp->Initialise(static_cast<int32>(m_vecSpawnLocations[uiRandLocation].vec3Point.x), 
	//	static_cast<int32>(m_vecSpawnLocations[uiRandLocation].vec3Point.y), static_cast<EPowerUpType>(uiRandPowerUp), 
	//	m_vecSpawnLocations[uiRandLocation].eFacePosition, m_uiPowerUpModelID, uiTextureID))
	//{
	//	return (false);
	//}

	return true;
}

/**
* 
* Returns a pointer to the current power-up.
* 
* @author Rebeccah Cox
* @return CPowerUp* m_pPowerUp - the current instance of CPowerUp.
*/
CPowerUp* 
CPowerUpManager::GetPowerup()
{
	return(m_pPowerUp);
}

/*
* This function adds a spawn location into the powerup manager.
* @author Rigardt de Vries
* @param _rSpawnLocation			the location of the power spawn point.
* @return void
*/
void
CPowerUpManager::AddSpawnLocation(EFacePosition _eFace, int32 _iX, int32 _iY)
{
	TPoint SpawnLocation;

	SpawnLocation.eFacePosition = _eFace;

	SpawnLocation.vec3Point = g_atUpRightDirectionVecs[_eFace].vec3Up * 22.5f;
	SpawnLocation.vec3Point += g_atUpRightDirectionVecs[_eFace].vec3Right * ((_iX * 3.0f) - 21.0f);
	SpawnLocation.vec3Point -= g_atUpRightDirectionVecs[_eFace].vec3Direction * ((_iY * 3.0f) - 21.0f);

	m_vecSpawnLocations.push_back(SpawnLocation);
}