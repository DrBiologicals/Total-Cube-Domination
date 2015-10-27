// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   playermanager.cpp
//  Description :   playermanager.cppfor implementation of playermanager.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//
// Library Includes
#include <cstdlib>

// Local Includes
#include "player.h"
#include "tank.h"

#ifdef _DEBUG
#include "../../engine/totalcubedomination.h"
#include "../../engine/logging/logmanager.h"
#include "../../igutils.h"
#endif // _DEBUG

// This Includes
#include "playermanager.h"

// Static Variables
CPlayerManager* CPlayerManager::s_pPlayerManager = 0;

// Static Function Prototypes

// Implementation


CPlayerManager::CPlayerManager()
{
    memset(&m_apPlayers, 0, sizeof(m_apPlayers) );
}

CPlayerManager::~CPlayerManager()
{
	for (uint32 iPlayers = 0; iPlayers < 8; ++iPlayers)
	{
		delete m_apPlayers[iPlayers];
		m_apPlayers[iPlayers] = 0;
	}
}

/*
* 
* @author Michael McQuarrie
* @return bool
*/
bool
CPlayerManager::Initialise()
{
	
	return (true);
}

/*
* 
* @author Michael McQuarrie
* @param _fDeltaTick
* @return void
*/
void
CPlayerManager::Process(float32 _fDeltaTick)
{
	for (uint32 iPlayers = 0; iPlayers < 8; ++iPlayers)
	{
		m_apPlayers[iPlayers]->Process(_fDeltaTick);
	}
}

/*
* 
* @author Michael McQuarrie
* @param _pPlayer The player to add
* @return void
*/
void 
CPlayerManager::AddPlayer(CPlayer* _pPlayer)
{
    for (int32 i = 0; i < 8; ++i)
    {
        if (m_apPlayers[i] == 0)
        {
	        m_apPlayers[i] = _pPlayer;
            return;
        }
    }
}

/*
* 
* @author Michael McQuarrie
* @param _iPlayer The players ID
* @return CPlayer* A pointer to the player requested
*/
CPlayer* 
CPlayerManager::GetPlayer(int32 _iPlayerID)
{
	return (m_apPlayers[_iPlayerID]);
}

/*
* Destroys all the players.
* @author Rigardt de Vries
* @return void
*/
void
CPlayerManager::DestroyPlayers()
{
    if (!m_apPlayers[0])
    {
        return ;

    }
    for (uint32 ui = 0; ui < 8; ++ui)
    {
        delete m_apPlayers[ui];
        m_apPlayers[ui] = 0;
    }

	m_vecSpawnlocationsGreen.clear();
	m_vecSpawnlocationsPurple.clear();
}

/*
* 
* @author Michael McQuarrie
* 
* @return CPlayerManager& the Player Manager
*/
CPlayerManager&
CPlayerManager::GetPlayerManagerInstance()
{
	if(s_pPlayerManager == 0)
	{
		s_pPlayerManager = new CPlayerManager;
	}

	return(*s_pPlayerManager);
}

/*
* DestroyInstance
* @author Michael McQuarrie
* 
* @return void
*/
void
CPlayerManager::DestroyInstance()
{
	delete s_pPlayerManager;
	s_pPlayerManager = 0;
}

/*
* This function adds a spawn location to the spawn location vector
* @author Rigardt de Vries
* @param _rPoint				the location to be added into the vector
* @return void
*/
void 
CPlayerManager::AddSpawnLocation(uint32 _uiX, uint32 _uiY, EFacePosition _eFace, ETeam _eTeam)
{
	TPoint tLocation;

	tLocation.vec3Point = g_atUpRightDirectionVecs[_eFace].vec3Up * 22.5f;

	tLocation.vec3Point += g_atUpRightDirectionVecs[_eFace].vec3Right * ((_uiX * 3.0f) - 21.0f);

	tLocation.vec3Point -= g_atUpRightDirectionVecs[_eFace].vec3Direction * ((_uiY * 3.0f) - 21.0f);

	tLocation.eFacePosition = _eFace;

	if (_eTeam == TEAM_GREEN)
	{
		m_vecSpawnlocationsGreen.push_back(tLocation);
	}
	else
	{
		m_vecSpawnlocationsPurple.push_back(tLocation);
	}
}

/**
* 
* 
* 
* @author Rebeccah Cox
* @param ETeam _eTeam
* @return 
*/
TPoint
CPlayerManager::GetRandomRespawnLocation(CTank* _pTank, ETeam _eTeam)
{
	//for(uint32 uiTank = 0; uiTank < 8; ++uiTank)
	{
		// green team respawn availability check
		if(TEAM_GREEN == _eTeam)
		{
			uint32 uiRandNum = rand() % static_cast<uint32>(m_vecSpawnlocationsGreen.size());

			return (m_vecSpawnlocationsGreen[uiRandNum]);
		}
		// purple team respawn availability check
		else
		{
			uint32 uiRandNum = rand() % static_cast<uint32>(m_vecSpawnlocationsPurple.size());

			return (m_vecSpawnlocationsPurple[uiRandNum]);
		}
	}
}
