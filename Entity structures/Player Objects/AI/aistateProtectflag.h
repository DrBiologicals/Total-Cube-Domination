// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateProtectflag.h
//  Description :   Declaration for CAIStateProtectFlag
//  Author      :   Cameron MacIntohs
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AISTATEPROTECTFLAG_H__
#define __IGFEB10_MODULE_AISTATEPROTECTFLAG_H__

// Library Includes

// Local Includes
#include "aistate.h"
#include "../../../defines.h"

// Types

// Prototypes

class CAIStateProtectFlag : public CAIState
{
	// Member Functions
public:
	CAIStateProtectFlag();
	virtual ~CAIStateProtectFlag();
	virtual void Process(float32 _fDeltaTick);
	bool Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
		CAISubstateAttack* _pAttack);

protected:

private:

	// Member Variables
public:

protected:
	CFlag* m_pAllyFlag;
	CFlag* m_pEnemyFlag;
	D3DXVECTOR3 mFlagPos3Last;
private:

}; 

#endif // __IGFEB10_MODULE_AISTATEPROTECTFLAG_H__

