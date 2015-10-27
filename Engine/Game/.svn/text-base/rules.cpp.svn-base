// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   rules.cpp
//  Description :   rules.cppfor implementation of rules.h
//  Author      :   Team A
//

// Library Includes
#include <assert.h>
#include <stdlib.h>

// Local Includes
#include "../../Entity structures/player objects/player.h"
#include "../../Entity structures/player objects/bullet.h"
#include "../../Entity structures/player objects/mine.h"
#include "../../Entity structures/player objects/empbomb.h"
#include "../../Entity structures/player objects/tank.h"
#include "../../Entity structures/Terrain Objects/flag.h"
#include "../../Entity structures/Terrain Objects/flagplate.h"
#include "../../Entity structures/Terrain Objects/wall.h"
#include "../../Entity structures/player objects/Power up/powerup.h"
#include "../../Entity structures/Terrain Objects/flamegrate.h"
#include "../../Entity structures/Terrain Objects/ammo.h"
#include "../../Entity structures/Terrain Objects/breakablebarrier.h"
#include "../../Entity structures/Terrain Objects/tower/tower.h"
#include "../../Entity structures/particle/emittermanager.h"
#include "../Totalcubedomination.h"
#include "gamestate.h"
#include "../Input/inputhandler.h"
#include "../../Entity structures/player objects/humanplayer.h"

#ifdef _DEBUG
#include "../logging/logmanager.h"
#endif // _DEBUG

// This Includes
#include "rules.h"

// Static Variables

// Static Function Prototypes

// Implementation
CRules::CRules()
: m_iTeamGreenScore(0)
, m_iTeamPurpleScore(0)
, m_eGreenFlagState(FLAG_AT_BASE)
, m_ePurpleFlagState(FLAG_AT_BASE)
{
	memset(m_abCheatModes, false, sizeof(m_abCheatModes));
}
CRules::~CRules()
{

}
bool
CRules::Initialise()
{	 
	return true;
}
int32
CRules::CheckWin()
{
	return(0);
}

void 
CRules::DestroyTank(CTank* _pTank)
{
	if(!(_pTank->IsTransitioning()))
	{
		CEmitterManager::GetInstance().AddEmitter(20, _pTank->GetPosition(), PARTICLE_EXPLODE, _pTank->GetTeam(), 0, 0);

		if (_pTank->GetFlag() )
		{
			SetFlagState(FLAG_ON_FLOOR, _pTank->GetFlag()->GetTeam() );
#ifdef _DEBUG
			CTotalCubeDomination::GetInstance().LogMessage("Flag State: FLAG_ON_FLOOR", LOG_MESSAGE_INIT);
#endif // _DEBUG
		}

		_pTank->Die();
	}
}

/*
* ChangeSide
* @author Rigardt de Vries
* @param _pTank			the tank that has to change side
* @return void
*/
void
CRules::ChangeSide(CTank *_pTank, EFacePosition _eTargetFace)
{
	_pTank->StartTransition(_eTargetFace);
}

/**
* 
* The tank's team scores a point.
* 
* PRECONDITIONS:
*	- The flag and tank are from the same team.
*	- The tank has a flag.
*	- The flag is on it's flag plate (at base)
* 
* @author Rebeccah Cox
* @param CTank* _pTank
* @param CFlag* _pFlag
* @return bool - true if team has three points.
*/
bool
CRules::CaptureFlag(CTank* _pTank, CFlag* _pFlag)
{
	if(_pTank->GetAlive())
	{
		// Precondition checks.
		assert(true == _pFlag->IsFlagOnFlagPlate() );

		if(_pTank->GetTeam() == _pFlag->GetTeam() && true == _pTank->HasFlag() )
		{
			_pTank->GetFlag()->ResetPosition();
			_pTank->GetFlag()->SetFlagPickedUp(false);
			SetFlagState(FLAG_AT_BASE, _pTank->GetFlag()->GetTeam() );
	#ifdef _DEBUG
			CTotalCubeDomination::GetInstance().LogMessage("flag state: FLAG_AT_BASE", LOG_MESSAGE_INIT);
	#endif // _DEBUG

			_pTank->RemoveFlag();
			_pTank->FlagCaptured();

			// The team NOT owning the flag have scored a goal.
			return(true);
		}
	}

	return (false);
}

/**
* 
* If the tank and flag are on the same team, the flag is returned to base.
* If the tank and flag are from opposing teams, the flag is assigned to the tank.
* 
* @author Rebeccah Cox
* @param CTank* _pTank
* @param CFlag* _pFlag
* @return void
*/
void
CRules::GrabFlag(CTank* _pTank, CFlag* _pFlag)
{
	if(_pTank->GetAlive())
	{
		// If the tank and flag are on the same team.
		if(_pTank->GetTeam() == _pFlag->GetTeam())
		{
			// If the flag is not on it's plate.
			if(false == _pFlag->IsFlagOnFlagPlate())
			{
				// Reset the position of the flag to it's base.
				_pFlag->ResetPosition();
				SetFlagState(FLAG_AT_BASE, _pFlag->GetTeam());
	#ifdef _DEBUG
				CTotalCubeDomination::GetInstance().LogMessage("flag state: FLAG_AT_BASE", LOG_MESSAGE_INIT);
	#endif // _DEBUG
				_pFlag->SetFlagPickedUp(false);
	#ifdef _DEBUG
				CTotalCubeDomination::GetInstance().LogMessage("Tank return flag", LOG_MESSAGE_INIT);
	#endif // _DEBUG
			}
		}
		// Else the tank and flag are on opposing teams.
		else
		{
			if (_pFlag->GetFlagPickedUp() == false)
			{
				// Set the player (tank) to have the flag.
				_pTank->SetFlag(_pFlag);
				_pFlag->SetFlagPickedUp(true);
	#ifdef _DEBUG
				CTotalCubeDomination::GetInstance().LogMessage("Tank grab flag", LOG_MESSAGE_INIT);
	#endif // _DEBUG

				 // Update the HUD.
				SetFlagState(FLAG_ON_PLAYER, _pFlag->GetTeam());
	#ifdef _DEBUG
				CTotalCubeDomination::GetInstance().LogMessage("flag state: FLAG_ON_PLAYER", LOG_MESSAGE_INIT);
	#endif // _DEBUG
			}
		}
	}
}

/**
* 
* Increments the score for the team passed in by one.
* Returns true if the team that was passed in has now scored 
*	three points, and won the game. 
* 
* @author Rebeccah Cox
* @param ETeam _eTeam - the team that is being awarded a point.
* return bool - true if the team has scored three points (won the game).
*/
bool
CRules::AwardPoint(ETeam _eTeam)
{
	if(TEAM_GREEN == _eTeam)
	{
		++m_iTeamGreenScore;

		// Check for win
        if(3 == m_iTeamGreenScore 
#ifdef _DEBUG
            && true != HasCheatMode(CHEAT_NEVER_ENDING_GAME)
#endif // _DEBUG
            )
		{
			return (true);
		}
	}
	else // team is TEAM_PURPLE
	{
		++m_iTeamPurpleScore;

		// Check for win
		        if(3 == m_iTeamPurpleScore 
#ifdef _DEBUG
            && true != HasCheatMode(CHEAT_NEVER_ENDING_GAME)
#endif // _DEBUG
                )
            {
                return (true);
            }
	}

	return (false);
}

/**
* 
* Returns the current score for the team passed in.
* 
* @author Rebeccah Cox
* @param ETeam _eTeam
* @return void
*/
int32
CRules::GetScore(ETeam _eTeam)
{
	if(TEAM_GREEN == _eTeam)
	{
		return (m_iTeamGreenScore);
	}
	else // team is purple
	{
		return (m_iTeamPurpleScore);
	}
}

/**
* 
* Sets the flag state for the team passed in. 
* 
* @author Rebeccah Cox
* @param EFlagState _eFlagState - state to change to.
* @param ETeam _eTeam - which flag to change state for. 
* @return void
*/
void
CRules::SetFlagState(EFlagState _eFlagState, ETeam _eTeam)
{
	if(TEAM_GREEN == _eTeam)
	{
		m_eGreenFlagState = _eFlagState;
	}
	else // team is purple
	{
		m_ePurpleFlagState = _eFlagState;
	}
}

/**
* 
* Returns the current flag state for the team passed in.
* 
* @author Rebeccah Cox
* @param ETeam _eTeam - defines which variable is returned.
* @return EFlagState m_eGreenFlagState OR m_ePurpleFlagState
*/
EFlagState
CRules::GetFlagState(ETeam _eTeam)
{
	if(TEAM_GREEN == _eTeam)
	{
		return (m_eGreenFlagState);
	}
	else // team is purple
	{
		return (m_ePurpleFlagState);
	}
}

#ifdef _DEBUG
/**
* 
* Returns true if the cheat mode passed in is active, returns
*	false if it is not.
* 
* @author Rebeccah Cox
* @param ECheatMode _eCheat - the cheat to check
* @return bool - true if the cheat passed in is active
*/
bool
CRules::HasCheatMode(ECheatMode _eCheat)
{
	return (m_abCheatModes[_eCheat]);
}

/**
* 
* Sets the cheat mode passed in, in m_abCheatModes, to the value _bIsActive.
* 
* @author Rebeccah Cox
* @param ECheatMode _eCheat - the cheat to set.
* @param bool _bIsActive - whether the cheat is active or not.
* @return void
*/
void
CRules::SetCheatMode(ECheatMode _eCheat, bool _bIsActive)
{
	m_abCheatModes[_eCheat] = _bIsActive;
}

/**
* 
* If the player is player one (ID = 0), then each of the cheat keys are checked,
*	and if any are triggered, the cheat mode is set to true.
* This function only handles the cheats that are ongoing (not one value change once), 
*	which are: invisibility, never ending game, and invincibility.
* 
* @author Rebeccah Cox
* @param CPlayer* _pPlayer - the player that the cheats affect.
* @return void
*/
void
CRules::CheckCheatModeKeys(CPlayer* _pPlayer)
{
	// Cheats only apply to player one.
	if(0 == _pPlayer->GetPlayerID())
	{
		if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_CHEATINVINC))
		{
			SetCheatMode(CHEAT_INVINCIBILITY, true);
		}
		if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_CHEATNEVEREND))
		{
			SetCheatMode(CHEAT_NEVER_ENDING_GAME, true);
		}
		if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_CHEATINVIS))
		{
			SetCheatMode(CHEAT_INVISIBILITY, true);
		}
	}
}
#endif // _DEBUG

/*
* BulletWallCollision
* @author Carsten Scholz
* @param _pBullet           the bullet to collided with wall
* @return void
*/
void
CRules::BulletWallCollision(CBullet* _pBullet)
//CRules::BulletWallCollision(CBullet* _pBullet/*, CWall* _pWallHit*/)
{
	if(true == _pBullet->GetAlive())
	{
		_pBullet->SetAlive(false);
		CEmitterManager::GetInstance().AddEmitter(10, _pBullet->GetPosition(), PARTICLE_BULLET_WALL, TEAM_NEUTRAL,0,0,0,_pBullet); // YES
	}
}

/*
* BulletBarrierCollision
* @author Rigardt de Vries
* @author Rebeccah Cox		- added check for only tank bullets to cause damage.
* @param _pBullet			the bullet that hit the barrier
* @param _pBarrier			the barrir that is hit
* @return void
*/
void
CRules::BulletBarrierCollision(CBullet* _pBullet, CBreakableBarrier* _pBarrier)
{
	if(true == _pBullet->GetAlive())
	{
		_pBullet->SetAlive(false);

		// Only damage if owner is a tank.
		if(OWNER_TANK == _pBullet->GetOwnerType())
		{
			_pBarrier->Damage(static_cast<int32>(_pBullet->GetDamage() ) );
			CEmitterManager::GetInstance().AddEmitter(10, _pBullet->GetPosition(), PARTICLE_BULLET_WALL, TEAM_NEUTRAL,0,0,0,_pBullet);
		}
	}
}

/*
* BulletBarrierCollision
* @author Rigardt de Vries
* @param _pEMP			the emp bomb that collided
* @return void
*/
void
CRules::EMPWallCollision(CEMPBomb *_pEMP)
{
	_pEMP->SetCurrentDistance(_pEMP->GetMaxDistance() );
}


/*
* ResetScore
* @author Rigardt de Vries
* @return void
*/
void
CRules::ResetScore()
{
    m_iTeamGreenScore = 0;
    m_iTeamPurpleScore = 0;
}

/*
* FlameGrateCollision Checks if the flame grate is currently active, if it is it does 20 damage a second.
*
* @author Carsten Scholz
* @author Rebeccah Cox - rewrote the else statement to use tank's decrement shield function, and flame 
*							grate's get damage function, to avoid repetitive code.
* @param _pTank the tank being hit by the particles from the flame grate
* @return void
*/
void
CRules::FlameGrateCollision(CTank* _pTank, CFlameGrate* _pFlameGrate, float32 _fDeltaTick)
{
	if(_pTank->GetAlive())
	{
		if(_pFlameGrate->GetActive() == true)
		{
			if(_pTank->GetCurrentShield() == 0.0f)
			{
				DestroyTank(_pTank);
			}
			else
			{
				_pTank->DecrementShield(_pFlameGrate->GetDamagePerSecond() * _fDeltaTick);
			}
		}	
	}
}

/**
* 
* If the ammo plate can be triggered, one EMP is added to the tank pointer passed in.
* The tank's AddEMP() function is called, which checks for the max EMP values, so do not 
*	need to check here.
* 
* @author Rebeccah Cox
* @param CTank* _pTank
* @param CAmmo* _pAmmoPlate
* @return void
*/
void
CRules::AmmoPlateCollision(CTank* _pTank, CAmmo* _pAmmoPlate)
{
	if(_pTank->GetAlive())
	{
		// If ammoplate can be triggered...
		if(true == _pAmmoPlate->CanBeTriggered()
			&& (_pTank->GetTeam() == _pAmmoPlate->GetTeam()
			|| TEAM_NEUTRAL == _pAmmoPlate->GetTeam()))
		{
			_pAmmoPlate->Trigger();
			_pTank->RechargeEMP();
		}
	}
}

void
CRules::PowerupCollision(CTank* _pTank, CPowerUp* _pPowerUp)
{
	_pTank->SetPowerUp(_pPowerUp->GetPowerUpType());
}

