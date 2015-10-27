// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   towerattack.cpp
//  Description :   towerattack.cpp for implementation of towerattack.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes
#include <vector>
#include "d3dx9.h"
#include "d3d9.h"

// Local Includes
#include "../../player objects/tank.h"
#include "../../player objects/playermanager.h"
#include "../../player objects/player.h"

// This Includes
#include "towerattack.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
*
* Constructor for CTowerAttack
*
* @author				Cameron MacIntosh
*
*/
CTowerAttack::CTowerAttack()
{

}

/**
*
* Deconstructor for CTowerAttack
*
* @author				Cameron MacIntosh
*
*/
CTowerAttack::~CTowerAttack()
{

}

/**
*
* sets the starting values for the instance
*
* @author				Cameron MacIntosh
* @param _pOwnerTower	The tower that owns the AI
*
*/
bool
CTowerAttack::Initialise(CTower *_pOwnerTower)
{
	if(_pOwnerTower!=0)
	{
		m_pTower = _pOwnerTower;
		return (true);
	}
	return false;
}

/**
* Processes the state
*   rotates the turret, and fires at enemies
*   if there are no enemies in range, switches to idle
*  
* @author				Cameron MacIntosh
* @param _fDeltaTick	Time between frames
*/
void
CTowerAttack::Process(float32 _fDeltaTick)
{
	std::vector<CTank*> vecTankInRange;
	//select enemies in range.
	for (uint32 i = 0; i < 8; ++i)
	{
		CTank* pTank = CPlayerManager::GetPlayerManagerInstance().GetPlayer(i)->GetTank();

		if((pTank->GetPowerUp() != POWERUP_INVISIBILITY)||(pTank->HasFlag()))
		{
            if (!pTank->GetAlive()) continue; 
			if (pTank->GetFacePosition() == m_pTower->GetFacePosition() &&
				pTank->GetTeam() != m_pTower->GetTeam() )
			{
				vecTankInRange.push_back(pTank);
			}
		}
	}

	uint32 uiTargetTotal = static_cast<uint32>(vecTankInRange.size());
	float32 lastShield = 9999.9f;
	//for enemies within range
	if(0<uiTargetTotal)
	{
		//set the desired target
		CTank* pTarget = 0;
		bool flagHeld = false;
		for(uint32 i = 0; i < uiTargetTotal; ++i)
		{
			CTank* pTank = vecTankInRange[i];
			if(!flagHeld)
			{
				if(pTank->HasFlag())
				{
					pTarget = pTank;
					flagHeld = true;
				}
				else if(lastShield>pTank->GetCurrentShield())
				{
					pTarget = pTank;
					lastShield = pTank->GetCurrentShield();
				}
			}
		}

		//calculate the distance to the enemy
		const D3DXVECTOR2& vec2TankPos = pTarget->GetPosition2D();
		//EFacePosition eTankFace = pTarget->GetFacePosition();

		D3DXVECTOR2 vecDist;
		vecDist.x = (m_pTower->GetX() + 0.5f) - vec2TankPos.x;
		vecDist.y = (m_pTower->GetY() + 0.5f) - vec2TankPos.y;
		//D3DXVec2Length(&vecDist);

		float32 fTurretAngle = atan2(vecDist.y, vecDist.x) - 1.57079633f;

		m_pTower->RotateTurret(fTurretAngle, _fDeltaTick);
		m_pTower->Shoot();
	}
	else
	{
		//as no enemy is within range, change the tower state to idle
		m_pTower->SetAIState(TOWERAI_STATE_IDLE);
	}
}