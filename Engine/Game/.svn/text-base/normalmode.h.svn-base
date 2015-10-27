// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   normalmode.h
//  Description :   Declaration for Cnormalmode
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_NORMALMODE_H__
#define __IGFEB10_MODULE_NORMALMODE_H__

// Library Includes

// Local Includes
#include "rules.h"
#include "../../Entity structures/player objects/player.h"
#include "../../Entity structures/player objects/bullet.h"
#include "../../Entity structures/player objects/mine.h"
#include "../../Entity structures/player objects/empbomb.h"
// Types

// Prototypes


class CNormalMode : public CRules
{
	// Member Functions
public:
	
	CNormalMode();
	~CNormalMode();

	virtual  bool Initialise();

	virtual int32 CheckWin();

	virtual void MineCollision(CTank* _pPlayerHit, CMine *_pMineFire);
	virtual void EMPCollision(CTank* _pPlayerHit, CEMPBomb *_pEMPFire);
	virtual void BulletTankCollision(CBullet* _pBullet, CTank* _pTankHit);
	virtual void BulletTowerCollision(CBullet* _pBullet, CTower* _pTowerHit);
	virtual void EMPTowerCollision(CEMPBomb* _pEMP, CTower* _pTower);

protected:

private:

	// Member Variables
public:

protected:

private:

}; 

#endif // __IGFEB10_MODULE_NORMALMODE_H__

