// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   hardcoremode.cpp
//  Description :   hardcoremode.cppfor implementation of hardcoremode.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../Entity structures/Player Objects/player.h"
#include "../../Entity structures/Player Objects/tank.h"
#include "../../Entity structures/Player Objects/bullet.h"
#include "../../Entity structures/Player Objects/mine.h"
#include "../../Entity structures/Player Objects/empbomb.h"
#include "../../Entity structures/Terrain Objects/flag.h"
#include "../../Entity structures/Terrain Objects/tower/tower.h"
#include "../../Entity structures/particle/emittermanager.h"

// This Includes

#include "hardcoremode.h"

// Static Variables

// Static Function Prototypes


// Implementation
CHardcoreMode::CHardcoreMode()
{

}

CHardcoreMode::~CHardcoreMode()
{

}

/**
*
* This function is called once their is a collision between a player and a mine
* It sets their shield to 0, if their shield was already 0 then the player dies
*
* @Author Michael McQuarrie
* @param _pPlayerHit is the player hit by the mine
* @param _pMineFire is the player who layed the mine
* 
*/
void
CHardcoreMode::MineCollision(CTank *_pPlayerHit, CMine *_pMineFire)
{
	if(_pPlayerHit->GetAlive() && false == _pPlayerHit->IsTransitioning())
	{
		_pMineFire->AddTankHit(_pPlayerHit);

		// If player has no shield.
		if(0.0f >= _pPlayerHit->GetCurrentShield())
		{
			//Kill Them
			DestroyTank(_pPlayerHit);
			_pPlayerHit->PlayerDead();

			//Killed a team member
			if(_pPlayerHit->GetTeam() == _pMineFire->GetOwner()->GetTeam())
			{
				_pMineFire->GetOwner()->TeamKilled();
				_pMineFire->GetOwner()->SubtractPic();
			}
			else
			{
				//Normal things happen
				//CEmitterManager::GetInstance().AddEmitter(30, _pMineFire->GetOwner()->GetPosition(), PARTICLE_SPIRAL,
						//_pMineFire->GetOwner()->GetTeam(), 0, 0, _pMineFire->GetOwner());
				 _pMineFire->GetOwner()->AddPic();
				 _pMineFire->GetOwner()->EnemyKilled();
			}
		}
		else
		{
			// If tank has an over shield, set that to zero.
			if(POWERUP_OVERSHIELD == _pPlayerHit->GetPowerUp())
			{
				_pPlayerHit->DecrementShield(_pPlayerHit->GetCurrentOverShield());
			}
			// Otherwise set normal shield to zero.
			else
			{
				_pPlayerHit->DecrementShield(_pPlayerHit->GetCurrentShield());
			}
		}
	}

}
/**
*
* This function is called once there is a collision between an EMP and a player.
* It sets their shield to 0 and shuts them down
*
* @Author Michael McQuarrie
* @param _pPlayerHit is the player hit by the EMP
* @param _pEMPFire is the player who fired the EMP
* 
*/

void
CHardcoreMode::EMPCollision(CTank *_pPlayerHit, CEMPBomb *_pEMPFire)
{
	if(_pPlayerHit->GetAlive() && _pEMPFire->GetAlive() && false == _pPlayerHit->IsTransitioning())
	{
		if (_pEMPFire->GetCurrentDistance() >= _pEMPFire->GetMaxDistance() )
		{
			_pEMPFire->AddTankHit(_pPlayerHit);

			// If tank has an over shield, set that to zero.
			if(POWERUP_OVERSHIELD == _pPlayerHit->GetPowerUp())
			{
				_pPlayerHit->DecrementShield(_pPlayerHit->GetCurrentOverShield());
			}
			// Otherwise set normal shield to zero.
			else
			{
				_pPlayerHit->DecrementShield(_pPlayerHit->GetCurrentShield());
			}

				_pPlayerHit->Shutdown();
		}
	}
}
/**
* 
* @author Michael McQuarrie
* @param CBullet* _pBullet
* @param CTank* _pTankHit
* @return void
*/
void
CHardcoreMode::BulletTankCollision(CBullet* _pBullet, CTank* _pTankHit)
{
	if(_pTankHit->GetAlive() && _pBullet->GetAlive())
	{
		#ifdef _DEBUG
		// If the player is invincible, don't kill them...
		if(false == HasCheatMode(CHEAT_INVINCIBILITY))
		{
		#endif // _DEBUG

		ETeam eTeam;
		if(OWNER_TANK == _pBullet->GetOwnerType())
		{
			eTeam = _pBullet->GetTankOwner()->GetTeam();
		}
		else if(OWNER_TOWER == _pBullet->GetOwnerType())
		{
			eTeam = _pBullet->GetTowerOwner()->GetTeam();
		}

		if(true == _pBullet->GetAlive())
		{
			// If player is dead...
			if(0.0f >= _pTankHit->GetCurrentShield() && false == _pTankHit->IsTransitioning())
			{
				// Kill the tank.
				DestroyTank(_pTankHit);
				_pTankHit->PlayerDead();

				// Give owner a pic for killing opponent.
				if(OWNER_TANK == _pBullet->GetOwnerType())
				{
					//If the player kills a team member 
					if(_pBullet->GetTankOwner()->GetTeam() == _pTankHit->GetTeam())
					{
						//Take away a pic
						_pBullet->GetTankOwner()->TeamKilled();
						_pBullet->GetTankOwner()->SubtractPic();
					}
					else
					{
						//Normal things happen
						//CEmitterManager::GetInstance().AddEmitter(30, _pBullet->GetTankOwner()->GetPosition(), PARTICLE_SPIRAL,
							//_pBullet->GetTankOwner()->GetTeam(), 0, 0, _pBullet->GetTankOwner());
						_pBullet->GetTankOwner()->AddPic();
						_pBullet->GetTankOwner()->EnemyKilled();
					}
				}
				
			}
			// Else decrement the shield...
			else
			{
				_pTankHit->DecrementShield(_pBullet->GetDamage());
			}

			// Set the bullet to dead.
			_pBullet->SetAlive(false);
			CEmitterManager::GetInstance().AddEmitter(10, _pBullet->GetPosition(), PARTICLE_BULLET_WALL, TEAM_NEUTRAL,0,0,0,_pBullet);
		}

		#ifdef _DEBUG
		}
		#endif // _DEBUG
	}
}

/*
* BulletTowerCollision
* @author Michael McQuarrie
* @param _pBullet the bullet to collide with the tower
* @param _pTower is the tower that is being hit.
* @return void
*/
void
CHardcoreMode::BulletTowerCollision(CBullet *_pBullet, CTower *_pTowerHit)
{
	if(OWNER_TANK == _pBullet->GetOwnerType())
	{
		_pTowerHit->TakeDamage(_pBullet->GetDamage());
	}
	_pBullet->SetAlive(false);

}

/*
* EMPTowerCollision
* @author Michael McQuarrie
* @param _pEMP			the emp bomb that collided
* @param _pTower the tower that collided
* @return void
*/
void
CHardcoreMode::EMPTowerCollision(CEMPBomb *_pEMP, CTower *_pTower)
{
	//Shutdown the tower
	_pEMP->SetCurrentDistance(_pEMP->GetMaxDistance() );
	_pTower->TakeEMP();
}