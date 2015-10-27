// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   playermanager.h
//  Description :   Declaration for Cplayermanager
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_PLAYERMANAGER_H__
#define __IGFEB10_MODULE_PLAYERMANAGER_H__

// Library Includes
#include <vector>
// Local Includes
#include "../../defines.h"

// Types

// Prototypes
class CPlayer;
class CTank;

class CPlayerManager
{
	// Member Functions
public:

	static CPlayerManager& GetPlayerManagerInstance();
	static void DestroyInstance();

	bool Initialise();

	void Process(float32 _fDeltaTick);

	void AddPlayer(CPlayer* _pPlayer);
	CPlayer* GetPlayer(int32 _iPlayerID);

	void AddSpawnLocation(uint32 _uiX, uint32 _uiY, EFacePosition _eFace, ETeam _eTeam);

    void DestroyPlayers();

	TPoint GetRandomRespawnLocation(CTank* _pTank, ETeam _eTeam);

protected:

private:
	CPlayerManager();
	CPlayerManager(const CPlayerManager& _kr);
	~CPlayerManager();

	CPlayerManager& operator =(const CPlayerManager& _kr);

	// Member Variables
public:

protected:
    CPlayer* m_apPlayers[8];
	static CPlayerManager* s_pPlayerManager;

	/*TPoint m_atGreenSpawn[8];
	TPoint m_atPurpleSpawn[8];*/

	std::vector<TPoint> m_vecSpawnlocationsGreen;
	std::vector<TPoint> m_vecSpawnlocationsPurple;

private:
	

}; 

#endif // __IGFEB10_MODULE_PLAYERMANAGER_H__

