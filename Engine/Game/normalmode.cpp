 // 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   normalmode.cpp
//  Description :   normalmode.cppfor implementation of normalmode.h
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

#include "normalmode.h"

// Static Variables

// Static Function Prototypes


// Implementation

CNormalMode::CNormalMode()
{

}
CNormalMode::~CNormalMode()
{

}
bool
CNormalMode::Initialise()
{	 
	return true;
}
/**
*
* This function checks if a team has captured 3 flags, if so then that team wins
*
* @Author Carsten Scholz
* @return Returns 0 if no one has won, if 1 Green team won if 2 purple team won.
* 
*/
int32
CNormalMode::CheckWin()
{
	return(0);
}

/**
*
* This function is called once their is a collision between a player and a mine
* It first checks if they were on the same team, if they were the mine does not explode
* It sets their shield to 0, if their shield was already 0 then the player dies
*
* @Author Carsten Scholz
* @param _pPlayerHit is the player hit by the mine
* @param _pMineFire is the player who layed the mine
* 
*/
void
CNormalMode::MineCollision(CTank *_pPlayerHit, CMine *_pMineFire)
{
	if(_pPlayerHit->GetAlive() && false == _pPlayerHit->IsTransitioning())
	{
		// If not the same team
		if(_pPlayerHit->GetTeam() != _pMineFire->GetOwner()->GetTeam())
		{
			_pMineFire->AddTankHit(_pPlayerHit);

			// If player has no shield.
			if(0.0f >= _pPlayerHit->GetCurrentShield())
			{
				CTank* pTank = _pMineFire->GetOwner();
				//Kill Them
				DestroyTank(_pPlayerHit);
				_pPlayerHit->PlayerDead();

				//CEmitterManager::GetInstance().AddEmitter(30, pTank->GetPosition(), PARTICLE_SPIRAL, pTank->GetTeam(), 0, 0, pTank);
				_pMineFire->GetOwner()->AddPic();
				_pMineFire->GetOwner()->EnemyKilled();
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
}
/**
*
* This function is called once their is a collision between an EMP and a player
* it checks if it hit a team mate then it will do nothing, if it hits an emeny it sets
* their shield to 0 and shuts them down
*
* @Author Carsten Scholz
* @param _pPlayerHit is the player hit by the mine
* @param _pEMPFire is the player who fired the EMP
* 
*/
void
CNormalMode::EMPCollision(CTank *_pPlayerHit, CEMPBomb *_pEMPFire)
{
	if(_pPlayerHit->GetAlive() && false == _pPlayerHit->IsTransitioning())
	{
		if(_pEMPFire->GetAlive())
		{
			if (_pEMPFire->GetCurrentDistance() >= _pEMPFire->GetMaxDistance() )
			{
				if (_pPlayerHit->GetTeam() != _pEMPFire->GetOwner()->GetTeam())
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
	}
}

/**
* 
* If the build is in DEBUG, and the player hit has the invincibility cheat, the player
*	does not take any damage.
* If the player-hit has no normal shield left, the player dies, and the player
*	who shot the bullet is awarded a random PIC.
* The tank's DecrementShield(..) function is called if the player-hit and the bullet fired
*	are from opposing teams (accounts for over-shield, charging, etc.).
* 
* @author Rebeccah Cox
* @param CBullet* _pBullet
* @param CTank* _pTankHit
* @return void
*/
void
CNormalMode::BulletTankCollision(CBullet* _pBullet, CTank* _pTankHit)
{
	if(_pTankHit->GetAlive() && _pBullet->GetAlive())
	{
		#ifdef _DEBUG
		// If the player is invincible, don't kill them...
		if(false == HasCheatMode(CHEAT_INVINCIBILITY))
		{
		#endif // _DEBUG

			ETeam eTeam = TEAM_PURPLE;

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
			if(_pTankHit->GetTeam() != eTeam)
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
						CTank* pTank = _pBullet->GetTankOwner();
						//CEmitterManager::GetInstance().AddEmitter(30, pTank->GetPosition(), PARTICLE_SPIRAL, pTank->GetTeam(), 0, 0, pTank);
						_pBullet->GetTankOwner()->AddPic();
						_pBullet->GetTankOwner()->EnemyKilled();
					}

					//Sets an explosion of particles

					//Displays who killed who to screen

				}
				// Else decrement the shield...
				else
				{
					_pTankHit->DecrementShield(_pBullet->GetDamage());
				}
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
* @author Carsten Scholz
* @author Rebeccah Cox - moved from the CRules class, moved SetAlive function so that bullet
*						will not pass through towers from same team.
* @param _pBullet the bullet to collide with the tower
* @param _pTower is the tower that is being hit.
* @return void
*/
void
CNormalMode::BulletTowerCollision(CBullet* _pBullet , CTower* _pTowerHit)
{
	if(OWNER_TANK == _pBullet->GetOwnerType() && true == _pBullet->GetAlive())
	{
		if(_pBullet->GetTankOwner()->GetTeam() != _pTowerHit->GetTeam())
		{
			_pTowerHit->TakeDamage(_pBullet->GetDamage());
		}
	}

	_pBullet->SetAlive(false);
}

/*
* BulletBarrierCollision
* @author Rigardt de Vries
* @param _pEMP			the emp bomb that collided
* @return void
*/
void
CNormalMode::EMPTowerCollision(CEMPBomb *_pEMP, CTower *_pTower)
{
	_pEMP->SetCurrentDistance(_pEMP->GetMaxDistance() );
	
	if(_pTower->GetTeam() != _pEMP->GetOwner()->GetTeam())
	{
		_pTower->TakeEMP();
	}
}