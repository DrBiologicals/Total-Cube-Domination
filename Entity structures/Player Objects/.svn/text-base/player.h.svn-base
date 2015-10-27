// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   player.h
//  Description :   Declaration for Cplayer
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//
// Edited by Michael McQuarrie

#ifndef __IGFEB10_MODULE_PLAYER_H__
#define __IGFEB10_MODULE_PLAYER_H__

// Library Includes

// Local Includes
#include "../entity.h"
#include "../../defines.h"

// Types

// Prototypes
class CTank;

class CPlayer : public CEntity
{
	// Member Functions
public:
	CPlayer();
	virtual ~CPlayer();

	virtual bool Initialise(CTank* _pTank, int32 _iIDNumber, ETeam _eTeam);

	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	virtual int32 GetPlayerID();

	virtual ETeam GetTeam();

	virtual CTank* GetTank();

	virtual bool IsHuman() const;

	float32 GetRespawnTimer();
	void SetRespawnTimer(float32 _fTime);

protected:

private:

	// Member Variables
public:

protected:
	ETeam m_eTeam;
	int32 m_iPlayerID;
	CTank* m_pTank;
	bool m_bIsHuman;

	float32 m_fRespawnTimer;
private:

}; 

#endif // __IGFEB10_MODULE_PLAYER_H__

