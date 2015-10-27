// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateCaptureflag.h
//  Description :   Declaration for CAIStateCaptureFlag
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AISTATECAPTUREFLAG_H__
#define __IGFEB10_MODULE_AISTATECAPTUREFLAG_H__

// Library Includes

// Local Includes
#include "aistate.h"
#include "../../../defines.h"

// Types

// Prototypes

class CAIStateCaptureFlag : public CAIState
{
	// Member Functions
public:
	CAIStateCaptureFlag();
	virtual ~CAIStateCaptureFlag();
	virtual void Process(float32 _fDeltaTick);
	bool Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
		CAISubstateAttack* _pAttack);

protected:

private:

	// Member Variables
public:

protected:

private:

}; 

#endif // __IGFEB10_MODULE_AISTATECAPTUREFLAG_H__

