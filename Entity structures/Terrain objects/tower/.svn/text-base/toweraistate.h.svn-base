// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   toweraistate.h
//  Description :   Declaration for CTowerAIState
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_TOWERAISTATE_H__
#define __IGFEB10_MODULE_TOWERAISTATE_H__

// Library Includes

// Local Includes
#include "../../../defines.h"
#include "tower.h"

// Types

// Prototypes

class CTowerAIState
{
	// Member Functions
public:
	CTowerAIState();
	virtual ~CTowerAIState();

	virtual bool Initialise(CTower* _pOwnerTower);
	virtual void Process(float32 _fDeltaTick) = 0;

protected:

private:

	// Member Variables
public:

protected:
	CTower* m_pTower;

private:

}; 

#endif // __IGFEB10_MODULE_TOWERAISTATE_H__

