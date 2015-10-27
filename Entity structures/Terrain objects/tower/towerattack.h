// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   towerattack.h
//  Description :   Declaration for CTowerAttack
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_TOWERATTACK_H__
#define __IGFEB10_MODULE_TOWERATTACK_H__

// Library Includes

// Local Includes
#include "toweraistate.h"

// Types

// Prototypes

class CTowerAttack : public CTowerAIState
{
	// Member Functions
public:
	CTowerAttack();
	virtual ~CTowerAttack();

	virtual bool Initialise(CTower* _pOwnerTower);
	virtual void Process(float32 _fDeltaTick);

protected:

private:

	// Member Variables
public:

protected:
	
private:

}; 

#endif // __IGFEB10_MODULE_TOWERATTACK_H__

