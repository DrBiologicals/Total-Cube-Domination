// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateProtectplayer.h
//  Description :   Declaration for CAIStateProtectPlayer
//  Author      :   Cameron MacIntohs
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AISTATEPROTECTPLAYER_H__
#define __IGFEB10_MODULE_AISTATEPROTECTPLAYER_H__

// Library Includes

// Local Includes
#include "aistate.h"
#include "../../../defines.h"

// Types

// Prototypes

class CAIStateProtectPlayer : public CAIState
{
	// Member Functions
public:
	CAIStateProtectPlayer();
	virtual ~CAIStateProtectPlayer();
	virtual void Process(float32 _fDeltaTick);
	bool Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
		CAISubstateAttack* _pAttack);

protected:

private:

	// Member Variables
public:

protected:
	CTank* m_pFlagCarrier;
	TIPoint m_TTargetLastPos2;
private:

}; 

#endif // __IGFEB10_MODULE_AISTATEPROTECTPLAYER_H__

