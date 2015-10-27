// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   powerupmanager.h
//  Description :   Declaration for Cpowerupmanager
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_POWERUPMANAGER_H__
#define __IGFEB10_MODULE_POWERUPMANAGER_H__

// Library Includes

// Local Includes
#include "powerup.h"

// Types

// Prototypes

class CPowerUpManager
{
	// Member Functions
public:
	static CPowerUpManager& GetInstance();
	static void DestroyInstance();

	bool Initialise();
	void Process(float32 _fDeltaTick);

	bool InitialiseRandomPowerup();
	CPowerUp* GetPowerup();

	void AddSpawnLocation(EFacePosition _eFace, int32 _iX, int32 _iY);

protected:

private:
	CPowerUpManager();
	CPowerUpManager(const CPowerUpManager& _kr);
	~CPowerUpManager();

	CPowerUpManager& operator =(const CPowerUpManager& _kr);

	// Member Variables
public:

protected:
	static CPowerUpManager* s_pInstance;

	CPowerUp* m_pPowerUp;

	std::vector<TPoint> m_vecSpawnLocations;

	float32 m_fSpawnPowerUpTimer;

	uint32 m_uiPowerUpModelID;
	uint32 m_uiInvisPowerUpTextureID;
    uint32 m_uiOverShieldPowerUpTextureID;

private:

}; 

#endif // __IGFEB10_MODULE_POWERUPMANAGER_H__

