// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateGetflag.h
//  Description :   Declaration for CAIStateGetFlag
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AISTATERETRIEVEFLAG_H__
#define __IGFEB10_MODULE_AISTATERETRIEVEFLAG_H__

// Library Includes

// Local Includes
#include "aistate.h"
#include "../../../defines.h"
#include "pathfinder.h"

// Types

// Prototypes

class CAIStateRetrieveFlag : public CAIState
{
	// Member Functions
public:
	CAIStateRetrieveFlag();
	virtual ~CAIStateRetrieveFlag();
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

#endif // __IGFEB10_MODULE_AISTATERETRIEVEFLAG_H__

